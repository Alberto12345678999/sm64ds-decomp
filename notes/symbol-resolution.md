# Resolving unlinkable symbol references from relocation evidence

A recovered source can byte-match its function and still be unlinkable, because it
names a symbol nothing defines. `eligible.py` rule 5 rejects those, and 243 enrolled
files sat there. This is the procedure that clears them without guessing, and the
line where it stops.

## The evidence chain

Nothing here is inferred from a name. For each reference site:

1. Compile the file; the object's relocation gives an **offset** into the function.
2. The delink entry gives the function's **ROM address**; offset + address = the site.
3. `config/**/relocs.txt` has a record for that exact site: the **target address**
   and the **candidate modules**.
4. If dsd names one module, that is the answer. If it names several (overlays share
   a RAM slot, so an address can be valid in more than one), break the tie by shape —
   a vtable has offset-to-top `0` at `-8`, a pointer-looking typeinfo at `-4`, and is
   not in `.bss`.
5. Replace the name with a symbol that **already exists** at that (module, address).

The replacement resolves to the address the ROM's own relocation names, so the linked
word equals the ROM word by construction. Then rule 5, the byte compare, and 106/106
confirm it independently.

Every step can fail closed, and each refusal is a file left alone rather than a guess:
no reloc record; ≠1 identifiable candidate; no existing symbol at the target; or one
name used for two different targets within a file.

## Why the obvious shortcut is wrong

The first attempt skipped all of this and added the 7 missing `_ZTV*` names to
symbols.txt at the addresses `build/rtti.json` gave. It went **101/106**.

`_ZTV10dBgActor_c` is wanted at **four different addresses** — ov015 `0x21148dc`,
ov080 `0x2128338`, ov091 `0x21351fc`, ov098 `0x213c5bc` — and it fails for **two
independent reasons**, which is worth separating because only one of them is about
vtables at all.

Three of the four are genuine per-overlay copies: a base class gets its own vtable
emitted into every overlay that uses it, so no single global symbol can address them
all. That is why these were missing from symbols.txt rather than merely unnamed, and
why the tree spells them `data_ov080_02128338` with the module baked in.

The fourth is not a `dBgActor_c` copy. ov015 `0x21148dc` is `_ZTV11FallBlockWf` — the
class's *own* vtable — and the recovered source had simply mislabelled it. A
destructor's first vptr store is always the object's own vtable, so the name written
there was wrong before any question of overlays arose. **The alias could not have
worked even if every base class had exactly one vtable**, because one of the four
sites was never asking for `dBgActor_c` in the first place. Resolving per-site against
relocs.txt fixes both failures at once; a global alias fixes neither.

The calibration that licensed it measured the wrong thing: rtti.json and symbols.txt
agree on the *address convention* in 136/136 cases, but every one of those was a
**co-located** record. It said nothing about *module attribution*, and the 7 in
question were precisely the non-co-located ones. **A control drawn only from cases
that already work cannot license the cases that do not.**

## What it recovered

Destructors turned out to be self-validating. The three consecutive stores to `t[0]`
are the destructor walking its hierarchy, re-assigning the vptr at each level, and the
resolution lands on exactly that shape without being told to:

```c
t[0] = (int)_ZTV12FallBlockLll;      /* own vtable,        ov022 */
t[0] = (int)data_ov080_02128338;     /* dBgActor_c, base,  ov080 */
t[0] = (int)_ZTV8Platform;           /* Platform,   base,  ov002 */
```

17 files, all byte-exact.

A second pass over the remaining unresolvable files found 69 more with a derivable
substitution, but only part of that is safe:

| category | count | verdict |
|---|---|---|
| literal identifier in a `.c` source | 46 subs / 16 files | **done** — 10 landed, 1 renamed instead, 5 collided |
| literal identifier in a `.cpp` source | — / 10 files | **refused**, see below |
| no such identifier — compiler-mangled | 79 subs / 43 files | **refused**, needs types |

## Substitute toward the name, not away from it

One of the 16 went the wrong direction and is worth stating as a rule. `func_02009374`
called `Vec3_DistSq`, which nothing defined because symbols.txt spelled that address
`func_0203cf94`. Substituting gave a file that linked and a source that had forgotten
what the function was.

Both names denote the same single address, so the choice of which to keep is free —
and the informative one is available. It went the other way instead: symbols.txt now
names 0x0203cf94 `Vec3_DistSq`, `src/func_0203cf94.c` was `git mv`d to match, and
`func_02009374.c` reverted to exactly its original text. The body settles that the
name is right rather than plausible — three squared component differences summed and
shifted `>> 12`, which is a Fix12 squared distance and nothing else.

So before substituting, ask which of the two names carries more meaning. Prefer
renaming the ROM symbol whenever the target is a **single** address; substitute only
when it is not. That condition is exactly what the failed alias experiment measured:
`_ZTV10dBgActor_c` is wanted at four addresses and so can never be one global symbol,
while a lone main-module function can always simply be named.

## Where it stops, and why

**C++ sources are refused.** In C the identifier *is* the symbol, so writing a mangled
name is safe. In C++ it is not: declaring `_ZN5Actor10FindWithIDEj` without
`extern "C"` makes the compiler mangle the already-mangled name a second time. That is
the `_Z43_ZN9ModelAnim7SetAnimE...` shape already sitting unresolvable in this tree —
the fix would create more of the defect it is meant to clear.

**Shadow-struct mangles are refused.** `_ZN12WithMeshClsn4InitEP5ActoriiPvi` appears
nowhere in any source. It is what mwcc mangles from

```cpp
struct WithMeshClsn { void Init(Actor *a, int b, int c, void *d, int e); };
```

whose guessed parameter types produce a symbol the ROM does not have. There is no
identifier to rename; the real signature is
`...4InitEP5Actor5Fix12IiES3_P10Vector3_16S5_`, and getting there means correcting the
declared types. That is type reconstruction — the C++ conversion workstream's job, and
the same "the enemy is the shadow struct" problem as everywhere else.

**Declaration collisions are refused.** 5 of the 16 C files failed to compile because
the replacement name is already declared elsewhere with a different type:

```
_ZN6Memory16operator_delete2EPv redeclared
  was declared as: 'void (void *)'
  now declared as: 'void (struct Obj *)'
```

Each needs a per-file decision about which declaration is right. Reverted.

## One detail that matters

Declarations are **cloned** from wherever the old name was declared, then renamed —
never synthesised. A data symbol's declared type decides how the compiler indexes it:
`extern int G0[]` used as `G0[3]` is a different access from `extern char G0[]`.
Inventing a declaration could change codegen while the name looked correct; cloning
cannot.

## Result

10,800 → **10,828** source-built (**+28**), 106/106 exact throughout. 332 files remain
un-built; the largest remaining category is the shadow-struct signatures above.

The baseline here is 10,800, not the 10,715 in [objisolate.md](objisolate.md) — object
isolation had already taken it from 10,715 to 10,800 (+85) before any symbol was
resolved. **The two notes describe consecutive steps, not parallel ones**, so their
gains add to +113 rather than +198; reading either table as measuring from 10,715
double-counts isolation's 85. This note's own +28 is 17 vtable references plus 11 C
renames.
