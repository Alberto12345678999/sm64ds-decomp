# dMg3DEspModel_c animation-state callback readability

Task: `minigame-esp-state-readable-0922`, [issue #2926](https://github.com/tangosdev/sm64ds-decomp/issues/2926).
Input/base: `9c6104f1f4df5554b19b3a72a9a32d0eba9361d0`.
Producer: `codex-minigame-esp-state-readable-0922`.

## Source change

This commit replaces raw member offsets in `func_ov006_020e7f04` with the
existing `dMg3DEspModel_c` layout, native `Animation::WillHitFrame` calls and
`Sound::PlayBank2_2D`. The guard field remains `unk_20c`: its meaning has not
been recovered. The return contracts now follow the actual bool/unsigned
callee declarations. The two frame checks remain ordered and conditional.

`func_ov006_020e7f5c` uses the real `mModelAnim` member instead of a fabricated
one-byte model type. Its state update assigns `mState` rather than copying a
`double`. The stored retail record at ov006 `0x0213c76c` is the direct callback
`0x020e7f04` with zero this-adjustment. The existing constructor/layout and
`Behavior()` identify the model member at `+0x0c`, its Animation base at `+0x50`,
and the invoked state member at `+0x210`. This does not recover original callback
names or claim a complete native-method reconstruction.

The exported C symbols and their machine ABI are retained. The second entry's
source parameter now names the evidenced model type. Resource-table storage,
shared headers, delinks, symbol configuration and attribution are unchanged.

## Byte proof and measured limit

The scope is two enrolled functions, ov006 `[0x020e7f04, 0x020e7fac)`: 88 and
80 bytes. Under mwccarm `2004/b56` and the production flags, copied controls and
both adopted variants emit identical complete ELF objects (792 and 808 bytes),
including symbols and relocations. Private compiler variants and hashes are
recorded in `build/esp-state-readable/probes.json` in the producer worktree.

The tested native `ModelAnim::SetAnim` call with an aggregate `Fix12<int>` speed
grows the second function from 80 to 88 bytes and changes relocations. The
adopted scalar-speed bridge agrees with the existing C definition's void result,
integer speed and u16 start frame. The native header's u32 start-frame contract
remains a separate unresolved callee-interface discrepancy; this caller supplies
zero. This one experiment does not prove every native spelling impossible.

Run exact-commit strict relocation checks, declaration/attribution/static checks
and a full ROM build before publication. Independent source review and queue
verification must refer to this commit and its tested base. Local object identity
alone is not formal acceptance. This is a focused two-callback readability change;
the broader minigame first pass and second pass remain unfinished.
