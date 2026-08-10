# Building C++ destructors into the ROM

`tools/objisolate.py`. Why 81 enrolled files could not link, and the four bugs
between "it compiles" and 106/106.

## The problem

A C++ destructor cannot be compiled alone. `Coin::~Coin()` yields an object with
**eight** content sections:

```
.text 0x58   _ZN4CoinD0Ev
.text 0x50   _ZN4CoinD1Ev      <- the only one this file declares
.text 0x50   _ZN4CoinD2Ev
.data 0x10   _ZTV4Coin
.data 0x6 0x7 0x8 0xc          RTTI record + type-name strings
```

Under the Itanium ABI the class vtable is emitted into the TU defining its key
function, and mwcc emits every destructor variant alongside it. dsd's linker script
selects code by section name — `_ZN4CoinD1Ev.o(.text)` — which matches **all three**
`.text` sections and would place D0 and D2 at D1's address. So `eligible.py` rejected
the object, correctly, and 81 files sat at `extra sections: .data`.

The ROM says what to keep. ov002 declares `_ZN4CoinD1Ev` size 0x50 (ours matches),
`_ZN4CoinD0Ev` size **0x64** (ours is 0x58 — the matching D0 is a separate `.c`
file), `_ZTV4Coin` at 0x021087ec already carved out as a symbol, and **no D2 at all**.

## The transformation

Keep the declared function's `.text`, zero every other content section's `sh_size`,
and rebind the survivor's references outward. Header surgery in place, never a
rewrite — the same discipline as `retarget_text_section`, for the same reason: this
build exists to compare bytes, so it must not perturb them. Nothing moves, so no
relocation offset shifts and no symbol index changes.

## The four bugs, in the order they appeared

Each was caught by a different gate, and none by the one before it.

**1. mwldarm: "sum of all symbol sizes exceed section size."** The first version
externalised only `STB_GLOBAL`/`STB_WEAK`. mwcc had emitted an inline `_ZN4PVecD1Ev`
under **`STB_LOPROC`**, a Metrowerks binding matching neither name, so its `st_size`
of 4 survived into a section that had just been zeroed. Fix: sweep every symbol in a
dropped section, whatever its binding.

**2. A poisoned object cache.** The build stored objects *post*-isolation, and
`isolate()` is idempotent — so once a buggy version had written an entry, a rebuild
served it back and declined to re-fix it. Fix: cache the **raw** compile and isolate
after fetch, plus `rombuild_cache.SCHEMA` 1 → 2 to discard the poisoned entries. Any
later change to the transformation now needs no bump at all.

**3. The vtable pointer landed 8 bytes high** — 76 functions, 34 modules, and only
the byte compare could see it:

```
Coin::~Coin       +0x4c   rom 021087ec   built 021087f4
CameraTag::~...   +0x20   rom 021085f8   built 02108600
```

Two conventions for the same name. mwcc's `_ZTV4Coin` addresses the **start** of the
vtable object, so the store into `this->vptr` relocates against it with an addend of
**8** to step over offset-to-top and typeinfo. The ROM's symbols.txt uses the other:
`_ZTV4Coin` **is** the slot array. This tree had already recorded that for
`_ZTV5Actor` (0x0208e3a4). Rebinding without adjusting adds 8 twice.

Fix: subtract `VTABLE_PREAMBLE` from the addend when externalising a `_ZTV*`
reference. Surveyed across all 81 candidates first — 69 such relocations, every one
`R_ARM_ABS32` with addend exactly 8 — and anything outside that shape is a **refusal**
rather than a guess. A secondary vtable under multiple inheritance would be the
obvious unseen case; refusing costs one function, guessing corrupts a module.

(The other 6 local references are ordinary PC-relative branches carrying ARM's
standard `-8` pipeline addend. Those need nothing.)

**4. Isolation applied where it is unsound.** `func_ov002_020bd664.cpp` has a
function-local static — `table$8` and its guard `_ZGVtable$8`, both **STB_LOCAL** in
`.bss`, both addressed by the kept function. Zeroing the section while leaving them
defined pointed those loads at offset 0 of an empty section, which the lcf still
places *at the function's own address*. The ROM supplies that `.bss` from the gap
object, so the file simply cannot be isolated.

Fix, in two halves:

* A **referenced** symbol in a dropped section becomes UNDEF regardless of binding.
* `eligible.py` rule 5 then looks it up in symbols.txt, does not find `table$8`, and
  rejects — the existing rule doing the work rather than a new special case.

The second half needed its own fix: rule 5 was intersecting the live set with
`undefined`, which is collected from a `STB_GLOBAL`/`STB_WEAK` loop, so a local never
reached it. `live` is already "undefined **and** reached by the kept function", so it
is now used directly. That change alone moved 7 files from wrongly-eligible to
correctly-rejected.

An **unreferenced** local is neither hazard: nothing outside can see it and nothing
inside asks for it, so zeroing its size is enough. Marking it undefined would invent
an import no ROM symbol could satisfy.

## Result

| | before | after |
|---|---|---|
| eligible | 10,715 | **10,800** (+85) |
| of which destructors | — | 69 |
| `.cpp` destructor files eligible | 24 of 105 | **99 of 105** |
| `extra sections` rejections | 81 | 4 |
| module fidelity | 106/106 exact | **106/106 exact** |

`python tools/eligible.py --no-isolate` reproduces the before column, so the effect
is a measurement rather than a claim. It is not a build option: rombuild always
isolates, so classifying without it describes an object the build will not produce.

10,800 is where this step ends, not where the tree ended up.
[symbol-resolution.md](symbol-resolution.md) continues from **10,800** to 10,828 by
resolving unlinkable symbol references. The two are consecutive, so the gains add to
+113; reading both tables as measuring from 10,715 double-counts the 85 above.

## What the independent review added

The −8 argument was verified far harder than the original 81-file survey managed:
**all 394** `_ZTV*` symbols in `config/arm9/**/symbols.txt`, checked against the
retail images, have word `addr-8` == 0 (offset-to-top) and word `addr-4` pointing at
a known RTTI record from `build/rtti.json`. 394/394. The slot-array convention holds
without exception, and no entry labels a secondary vtable — a secondary's non-zero
offset-to-top would have failed that check.

It also found a real hole. **The guard only inspected relocations for symbols it was
about to externalise.** A `_ZTV*` reloc whose symbol is UNDEF *from the start* is
never a candidate, so it was never checked and never corrected. Two realistic shapes
produce exactly that under 2004/b56:

* a **constructor-only TU** — the vtable's key function is the DESTRUCTOR, so a TU
  defining only `V::V()` references `_ZTV1V` without defining it, and the implicit
  vptr store still carries addend 8;
* a **derived destructor over an inline base destructor** — the object's own `_ZTV1D`
  gets corrected while the inlined `_ZTV1B` store does not.

Zero instances among the 3,352 enrolled C++ candidates, because their recovered
sources spell the vptr store explicitly (`extern int _ZTV5Scene[]`, addend 0). Both
arrive the moment a real-C++ constructor is enrolled — the direction this tree is
moving. `plan()` now checks **every** `_ZTV`/`_ZTI`/`_ZTS` reference the kept function
makes, and refuses a nonzero addend on an UNDEF one rather than correcting it: there
is no enrolled instance to verify a correction against. `tools/test_objisolate.py`
pins both cases.

Also from the review, and fixed: `isolate` moved inside `classify`'s `try` so a
malformed object is one file's verdict rather than a traceback; `mods/` exempted from
isolation entirely (a mod may legitimately carry helpers and data, and stripping them
would bind their symbols to 0 at runtime instead of failing loudly);
`retarget_text_section` now refuses a multi-`.text` object instead of renaming an
arbitrary one; and the SCHEMA-2 comment corrected — the cache stores the
*retargeted* compile, so a change to `retarget_text_section` still needs a bump.

## A follow-up that failed

Isolation left 16 files blocked on `unresolvable: _ZTV<class>`, and the obvious fix —
adding the 7 missing vtable names to symbols.txt at the addresses `build/rtti.json`
gave — took the build to **101/106** with exactly those 16 mismatching. dsd's own
reloc table says why: the vtables live in another overlay, and dsd cannot always
resolve which one.

```
from:0x021125d8 kind:load to:0x02128338 module:overlays(79,80)
from:0x02112490 kind:load to:0x0213c5bc module:overlays(6,98)
```

[symbol-resolution.md](symbol-resolution.md) owns this lesson in full — why the
136/136 calibration measured address *convention* rather than module *attribution*,
and why one of the four sites was not asking for that base class at all. It also
records how the 16 were eventually unblocked: per-site resolution against relocs.txt,
not a symbol. They are no longer blocked.

## The rule this cost the most to learn

**A clean link is not evidence.** Bug 3 linked perfectly, built a ROM, and wrote a
vptr one entry past the truth in 34 modules. Only `rombuild.py`'s byte compare
caught it — which is the same lesson already in the tree as "rombuild is the verdict,
not build_pin.verify", arriving from a new direction.
