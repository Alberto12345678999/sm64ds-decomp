# dScMgBase_c slots 18-35 — the keystone map

`include/dScMgBase_c.h` says: *"Slots 18-35 are eighteen further virtuals new at this
class; their signatures are not reconstructed yet, so they stay undeclared."*

That single sentence is what caps every minigame class's emitted vtable. mwcc emits a
table only as long as the slots it has been told about, so `dScMgSingle3DBase_c` emits
18 slots where the cartridge has 36 — a byte-exact **prefix**, not a disagreement, but
not ownable either. The same cap applies to all 32 descendants of `dScMgBase_c`.

## The map (read out of `_ZTV11dScMgBase_c`, ov004:0x020bc0c0)

| slot | +off | ROM body | existing `recovered name:` | shape in the legacy source |
|---|---|---|---|---|
| 18 | 0x48 | ov004:0x020b299c | `OnYoshiTryEat` — **corrected 2026-08-31** | `int(int)` \*\* — **DECLARED** |
| 19 | 0x4C | ov004:0x020b2994 | `OnTurnIntoEgg` | `int(void)`, `return 1;` |
| 20 | 0x50 | ov004:0x020b2990 | `Virtual50` | `void(void)` |
| 21 | 0x54 | ov004:0x020b298c | `OnGroundPounded` | `void(void)` |
| 22 | 0x58 | ov004:0x020ae198 | `OnAttacked1` | `int(void)` |
| 23 | 0x5C | ov004:0x020ae1a0 | `OnAttacked2` | `int(void)` |
| 24 | 0x60 | ov004:0x020ae140 | `OnKicked` | `int(Obj*)` |
| 25 | 0x64 | ov004:0x020ae128 | `OnPushed` | `int(void*)` |
| 26 | 0x68 | ov004:0x020b04e0 | `OnHitByCannonBlastedChar` | `int(void)`, `return 0;` |
| 27 | 0x6C | ov004:0x020af27c | `OnHitByMegaChar` | `void(void*)` |
| 28 | 0x70 | ov004:0x020af04c | `OnHitFromUnderneath` | `void(Obj*)` |
| 29 | 0x74 | ov004:0x020af094 | `OnAimedAtWithEgg` | `void(Obj*)` |
| 30 | 0x78 | ov004:0x020aeed8 | `OnAimedAtWithEggReturnVec` | `void(char*)` |
| 31 | 0x7C | ov004:0x020b2880 | `Kill` | `void(void)` |
| 32 | 0x80 | ov004:0x020b27f4 | `AfterClsn` | `void(void)` |
| 33 | 0x84 | ov004:0x020b265c | *(none)* → `Virtual84` | `void(char *obj)` |
| 34 | 0x88 | ov004:0x020ae3b4 | *(none)* → `Virtual88` | `void(char*,int,int,int,int)` |
| 35 | 0x8C | ov004:0x020ad660 | *(none)* → `Virtual8C` | `int(int*)` |

Fourteen of the eighteen carry a `recovered name:` comment in the legacy source, so
this is far less speculative than the header's wording suggests. Slot 18 has a name
too, from a different direction — see the next section. The three still unnamed (33,
34, 35) take the tree's established `Virtual<hex offset>` convention
(`include/fBase_c.h:143` — `Virtual34`, `Virtual38`).

\*\* The shape column records what the *legacy free function* looks like — except for
slot 18, which is now **measured** rather than read off the legacy shape:

- **Arity is `(int)`, not `()`.** All 24 free-function bodies are written `void(void)`
  or `void(char *self)`, but 13 of them read r1 and branch on it — `dScMgTeresa_c`
  takes an entirely different path when it is 0. Twelve unrelated classes do not read
  a garbage register by coincidence. The *base's* body ignores it, and that proves
  nothing either way: an unused argument is simply never read. Only an override that
  actually reads a parameter is evidence, and it gives a **lower** bound.
  `include/dActor_c.h:131` declares it with no parameter and is therefore **wrong for
  this branch** — a naming hint, never a signature authority.
- **Return type is `int`, not `void`.** `dScMgCoin_c::OnYoshiTryEat` is a real *member*
  definition ending `return 0;`; declaring `void` would have changed its bytes. The
  return type is not mangled, so the 24 free functions are unaffected. This is the same
  trap `dActor_c.h` documents for slots 21, 24 and 27 — re-measure each remaining slot
  against a real override before treating its legacy `void` as settled.

`config/arm9/overlays/ov006/symbols.txt` named Coin's override
`_ZN11dScMgCoin_c13OnYoshiTryEatEv` — **wrong arity, corrected to `...Ei`.**

For slots 24, 25, 27, 28, 29, 30, 33, 34 and 35 the leading parameter in the legacy
source is really `this`; it becomes implicit when the free function turns into a method.

## Slot 18 is `OnYoshiTryEat`, not `Virtual48` (measured 2026-08-31)

Two independent sources agree, and neither of them is this table:

1. **`include/dActor_c.h:131`** declares `virtual int OnYoshiTryEat(); /* slot 18 */`,
   and a dozen further headers repeat the declaration at the same index — BabyPenguin,
   BlueFlame, BobOmb, BookShot, Coin, Crate, CrazedCrate, `daDossyCap_c`, `daEyBm_c`,
   `daKpFr_c`, `daKrb_c`, `daKrpa_c`, `daObjMarioCap_c`, `daTrs_c`. `dActor_c` sits on
   the *other* branch of `fBase_c` (`fBase_c → dBase_c → dActor_c`, where this family
   is `fBase_c → dBase_c → dScene_c → dScMgBase_c`), so on its own this would only be
   suggestive.

2. **The cartridge.** Walking `_ZTV11dScMgCoin_c` (ov006:0x0213bf50) against
   `_ZTV11dScMgBase_c` (ov004:0x020bc0c0), 36 slots each, `dScMgCoin_c` overrides
   exactly three: 16 and 17 (the destructor pair) and **18, with ov006:0x020de5b0** —
   which `config/arm9/overlays/ov006/symbols.txt:545` **already names**
   `_ZN11dScMgCoin_c13OnYoshiTryEatEv`. That name was recovered and landed before this
   table existed, and it lands on this branch's slot 18.

So the `Virtual48` placeholder was wrong. The claim further down — "slot 18 stays
unnamed on both sides, which is consistent rather than a gap" — was consistent for the
wrong reason: two sources that both happened to lack the name, not two sources that
agreed there was none to have.

Watch the address point when reproducing this. A `_ZTV*` address in `symbols.txt`
**is** the address point, so slot *i* sits at `addr + 4*i` with no preamble to skip.
Adding `objisolate.VTABLE_PREAMBLE` (8) on top shifts every reading by two slots and
makes the destructor pair look like slots 18 and 19.

## The signature template for slots 18-30: `include/dActor_c.h:120-151`

`dActor_c`'s new-slot block is on the other branch but at **identical indices**, and
all thirteen names 18..30 agree with the `recovered name:` comments on this class's own
ov004 bodies. It is the ready-made declaration block for PR B:

```c
/* --- new slots, 18..30, in declaration order. Do not reorder. --- */
virtual int  OnYoshiTryEat();                      /* slot 18 */
virtual int  OnTurnIntoEgg(Player &player);        /* slot 19 */
virtual int  Virtual50();                          /* slot 20 -- vtable+0x50 */
/* Slots 21, 24 and 27 return void, NOT int. Nothing in the tree reads them,
   so only an override with early returns can tell the difference -- and one
   of each does, allocating registers differently under `int` even with r0
   untouched. Measured, not assumed; see notes/actor-core-provenance.md 9. */
virtual void OnGroundPounded(dActor_c &other);          /* slot 21 */
virtual int  OnAttacked1(dActor_c &other);              /* slot 22 */
virtual int  OnAttacked2(dActor_c &other);              /* slot 23 */
virtual void OnKicked(dActor_c &other);                 /* slot 24 */
virtual int  OnPushed(dActor_c &other);                 /* slot 25 */
virtual int  OnHitByCannonBlastedChar(dActor_c &other); /* slot 26 */
/* The `Player &` this block proposed for slot 27 was dActor_c.h's and is
   MEASURED WRONG: both real bodies open `mov r4, r0` and then write r1 before
   reading it, so no second argument register is live on entry. Declared and
   landed as the no-parameter form. */
virtual void OnHitByMegaChar();                         /* slot 27 */
/* The `dActor_c &other` this block proposed for slot 28 came from
   dActor_c.h too, and came off for the same reason -- dScMgBase_c's own body
   writes r1 before it ever reads it and touches no other argument register.
   Measured once here rather than twice: dScMgSlot1_c's override calls the base
   as its first act, so a second argument would ride through untouched. */
virtual int  OnHitFromUnderneath();                     /* slot 28 */
virtual int  OnAimedAtWithEgg();                        /* slot 29 */
/* NOT a Vector3.  dActor_c.h:151 returns one by value, and slot 29's work
   refuted the transplant: at ov004:0x020ae168 slot 30 is dispatched with r0
   still holding `this` and r1 holding the loaded function pointer, where a
   12-byte return would put a hidden result pointer in r0 and `this` in r1
   under AAPCS.  The return type is open again; `int` is a placeholder. */
virtual int  OnAimedAtWithEggReturnVec();               /* slot 30 */
```

The parameter *types* are `dActor_c &` / `Player &` on that branch; on this one the
legacy sources pass raw `char *` / `void *`. The type does not change the slot's arity,
but it does change the mangled name — so settle it before renaming the ov004 bodies,
not after.

**Slots 31-35 are not in `dActor_c.h`.** `Kill`, `AfterClsn`, `Virtual84`, `Virtual88`
and `Virtual8C` still need signatures reconstructed from their bodies. That is the
remaining unknown in PR B, and it is five slots, not eighteen.

## What PR B actually costs (census, 2026-08-31)

Walking every `_ZTV*` in the family against `_ZTV11dScMgBase_c`:

- **106 overrides at slots ≥ 18**, across **33 classes**. 100 of them fall in 18..35;
  6 sit at slot ≥ 36, on classes that add virtuals of their own on top.
- `dScMgBase_c` itself owns 18 of those — **82 are descendant-side.**

Per class: `dScMg3DEsp_c` 2, `dScMgAmida_c` 5, `dScMgBSC_c` 3, `dScMgBase_c` 18,
`dScMgBomroom_c` 1, `dScMgCard_c` 3, `dScMgCoin_c` 1, `dScMgCup_c` 2,
`dScMgCurling2_c` 1, `dScMgCurling_c` 1, `dScMgD3DBase_c` 9, `dScMgFlower_c` 1,
`dScMgHanachan_c` 1, `dScMgJump2_c` 2, `dScMgJump_c` 4, `dScMgLuigi_c` 1,
`dScMgMCarlo2_c` 2, `dScMgMCarlo_c` 2, `dScMgMemory2_c` 3, `dScMgMemory_c` 3,
`dScMgPachinko2_c` 1, `dScMgPachinko_c` 3, `dScMgPanel_c` 1, `dScMgRoulette_c` 2,
`dScMgSingle3DBase_c` 2, `dScMgSlot1_c` 4, `dScMgSlot3_c` 4, `dScMgSmartball_c` 3,
`dScMgSnowball_c` 4, `dScMgSound_c` 2, `dScMgTeresa_c` 3, `dScMgTrampoline2_c` 6,
`dScMgTrampoline_c` 6.

**This is why the change cannot be staged class by class** — but it decomposes
cleanly **slot by slot**, which is how it is actually being landed. Roughly 34 of these
classes already emit a vtable today. Declaring the base's eighteen slots *at once*
widens every one of those tables from 18 slots to 36 — and a descendant that does not
simultaneously declare its own overrides gets the *base's* body written into the
widened slot, where the cartridge holds its own. Those tables go from PARTIAL (a
byte-exact 18-slot prefix, ownable later) to **DIFFERS** (wrong bytes, a real
regression `romdata_check` will catch).

Declaring **one** base slot only widens every table by one word. After declaring base
slots 18..k an emitted table is k+1 slots long, and for every i ≤ k that slot is right
if the class either declares its own override or genuinely inherits the base body.
Slots above k are simply not emitted — still a byte-exact prefix, never a DIFFERS. So
the atomic unit is **one base slot across the whole family**: base declaration, base
body rename, and every descendant's override declaration plus rename, together. That
is eighteen reviewable commits, not one 158-change commit.

Measured on slot 18 (2026-08-31): `module fidelity 106/106`, `ROM data from source`
unchanged at 463 verified / 251 partial / 7 differ, and `partialBytes` **9,980 →
10,100** — exactly 30 emitted vtables each one word longer, all byte-exact. No table
regressed.

**Read that number twice.** Applying the 30 descendant declarations *without* the
base declaration also builds green — 106/106, PASS, no new DIFFERS — but at **10,088**
/ 27 tables. With the base silent above slot 17, each descendant's own
`virtual int OnYoshiTryEat(int);` introduces a brand-new virtual that happens to land
at index 18 in that class, pointing at the same body: byte-identical, semantically
wrong, and invisible to every gate in this tree. The three tables that only appear
once the base declares the slot are the classes with **no** override of their own;
their bytes matching is the independent confirmation that they genuinely inherit.
The widened-table **count** is the only check that distinguishes the two.

## Three hazards, all measured

**1. Slot 35 is a cross-overlay address collision.** `func_ov002_020ad660` and
`func_ov004_020ad660` both exist, at the same address 0x020ad660, in different overlays.
Only ov002's is decompiled (`src/func_ov002_020ad660.cpp`) — and it is a *different
function*. The slot-35 body is ov004's, which has no source file. Any rename must be
scoped to the ov004 symbol alone; a filename- or address-keyed rename hits ov002's
unrelated function and every byte gate still passes. See the standing
`cross-overlay-symbol-collision` note.

**2. Each slot has to be atomic.** Declaring a virtual makes mwcc emit a vtable slot
referencing a `_ZN11dScMgBase_c*` mangled name. That symbol does not exist until the
ov004 body is renamed. A declaration without its rename leaves the link with an
undefined external; a rename without its declaration orphans it. Per slot: one commit,
or neither. Across slots, they are independent.

**3. Declaration order IS the index** — found while applying slot 18.
`dScMgSlot1_c` already declared `OnHitByMegaChar /* slot 27 */` and
`OnHitFromUnderneath /* slot 28 */`, and `dScMgAmida_c` declared `Unk36 /* slot 36 */`,
but with the base declaring nothing above 17 those comments were aspirational: the
declarations actually sat at indices 18/19 and 18. That is precisely why those two were
the last DIFFERS vtables left after PR #2081. Both of `dScMgSlot1_c`'s have since been
reconciled -- 27 with the base's slot-27 commit, 28 with slot 28's -- so that class now
declares nothing mwcc numbers for itself; `dScMgAmida_c`'s `Unk36` is the last one left,
and slot 35 lands it. A new base slot's override must be
inserted **before** any such pre-existing slot≥18 declaration, and after the class's
first declared virtual so the key function does not move. Slot 18 moved their
wrongness up one index without changing its size (Amida 4 bytes, Slot1 8); they clear
only once every intervening slot is declared.

## The per-slot worklist (measured 2026-08-31)

How large each of the remaining seventeen PRs is. Counts are descendant overrides;
every slot also carries the base declaration and the ov004 base-body rename.

| slot | name | base body (ov004) | descendant overrides |
|---|---|---|---|
| 18 | `OnYoshiTryEat` | 0x020b299c | **30 — this PR** |
| 19 | `OnTurnIntoEgg` | 0x020b2994 | 11 |
| 20 | `Virtual50` | 0x020b2990 | 4 |
| 21 | `OnGroundPounded` | 0x020b298c | 4 |
| 22 | `OnAttacked1` | 0x020ae198 | **0** |
| 23 | `OnAttacked2` | 0x020ae1a0 | 3 |
| 24 | `OnKicked` | 0x020ae140 | 6 |
| 25 | `OnPushed` | 0x020ae128 | 7 |
| 26 | `OnHitByCannonBlastedChar` | 0x020b04e0 | 19 |
| 27 | `OnHitByMegaChar` | 0x020af27c | 6 - **DONE**, 2 declarations |
| 28 | `OnHitFromUnderneath` | 0x020af04c | 6 - **DONE**, 2 declarations; the second and last occupied slot |
| 29 | `OnAimedAtWithEgg` | 0x020af094 | 6 - **DONE**, 2 declarations; the first since 26 with no occupied-slot trap, and the first whose NAME the ROM contradicts |
| 30 | `OnAimedAtWithEggReturnVec` | 0x020aeed8 | 6 |
| 31 | `Kill` | 0x020b2880 | 7 |
| 32 | `AfterClsn` | 0x020b27f4 | 1 |
| 33 | `Virtual84` | 0x020b265c | 19 |
| 34 | `Virtual88` | 0x020ae3b4 | 4 |
| 35 | `Virtual8C` | 0x020ad660 | 1 |

134 descendant overrides plus the base's 18 declarations. Slot 18 was the outlier;
the median slot touches six classes. **Slot 22 has no descendant overrides at all** —
base declaration and base rename only, the smallest commit in the campaign.

Four classes are intact TUs, so at every slot their override is renamed *inside*
`src/actors/<class>.cpp` rather than through a standalone source file:
`dScMgBSC_c`, `dScMgCard_c`, `dScMgMCarlo_c`, `dScMgMCarlo2_c`.

## What it unlocks

Full 36-slot vtable emission for `dScMgBase_c` and all 32 descendants, which is the
precondition for `production_mode: "intact-object"` ownership of the minigame family's
`_ZTV`/`_ZTI`/`_ZTS` instead of the `deadstrip-data` licence they carry today.

## Independent confirmation from a derived class (2026-08-30)

`ov006/dScMgBSC_c`, promoted as a 19-function TU, **overrides three of these slots**,
and its own bodies confirm the map from a second direction:

| slot | base body (ov004) | base name here | dScMgBSC_c's override |
|---|---|---|---|
| 18 | 0x020b299c | `OnYoshiTryEat` | ov006:0x02125364 |
| 19 | 0x020b2994 | `OnTurnIntoEgg` | ov006:0x0212527c |
| 21 | 0x020b298c | `OnGroundPounded` | ov006:0x02125248 |

Two independent sources agree on 19 and 21. This table was built by walking
`_ZTV11dScMgBase_c`; the override addresses come from walking `_ZTV10dScMgBSC_c`. The
promoted source carries `// recovered name: dScMgBSC_c_OnTurnIntoEgg` and
`dScMgBSC_c_OnGroundPounded` comments that were recovered *before* either walk and
land on exactly those two addresses. Slot 18 carried no recovered name on either
side, which read as consistency at the time; the section above shows it was simply
absent from both, and the name is `OnYoshiTryEat`.

**This is also the measurement of what PR B costs.** `dScMgBSC_c`'s emitted
`_ZTV10dScMgBSC_c` is 0x50 bytes -- an 8-byte preamble plus 18 slots, so slots 0..17,
stopping exactly one slot short of 18. That is not a coincidence: the class declares
virtuals only through the destructor pair at 16/17, so the compiler has no name to put
in slot 18 and truncates. The TU reaches slot 18 today through a cast to a local shim
struct (`SelfVtblShim`) because no header declares it. Declaring slots 18-35 on
`dScMgBase_c` widens this table to the full 36 and lets that cast become a real virtual
call -- but it also means `dScMgBSC_c` starts emitting 18 more slots of vtable data
that must be licensed and byte-compared, on top of the eighteen ov004 renames. Budget
for the descendants' tables, not just the base's.
