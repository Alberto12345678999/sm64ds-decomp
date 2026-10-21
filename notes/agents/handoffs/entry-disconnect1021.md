# Entry disconnect interface

Task `entry-disconnect1021` continues accepted `entry-async-compose1021` from main `5ca03d53816f20996724ef053628b6d6dcf214fa`. The deliverable is a verified PR; no merge is authorized.

## Recovered behavior

The function at ov075:0x02119dc4 is now `dScEntry_c::HandlePlayerDisconnect(const StepSet *resumeSteps)`. Behavior and the callbacks at 0x02117e84 and 0x02118248 all pass the scene and a three-callback step-set address. The previous declarations disagreed on return and parameter types. The new English name and `const` pointer spelling are inferred, not ROM identifiers.

The helper distinguishes a wireless error from individual disconnects. `func_02030790` writes state 6 from loss/error paths; the previous `IsVsMode` label incorrectly treated that value as a scene identity. Error handling chooses the existing message, clears behavior, optionally hides the affected display layers and render callback, darkens the screen, stops music, and suspends the player figures. Individual disconnects retain the existing peer-mask tests, message ordering, 180-tick fallback or 120-tick resume delay, and icon clearing.

Byte 0x287 is `mDisconnectHideMask`: the results callback at 0x02118378 enables and stores mask 0x0e; the ARM9 display update at 0x02019144 maps `data_0209d45c` into main DISPCNT layer bits. The class remains 0x288 bytes. `mEntObj->mSuspended` already models byte 0xf44 in the figure object.

## Native representation and measured constraint

Both EntryScene shadow layouts are removed. Native Step equality and assignments to zero replace hand-built PMF word comparisons, volatile temporaries and copy casts in disconnect handling. These ordinary null assignments reproduce the retail stack traffic automatically.

The typed `data_ov075_0211d920` declaration addresses the behavior member of `data_ov075_0211d918` at offset 8. It is an existing subobject symbol, not separate storage. Direct `.behavior` spelling produces the correct 828-byte size and destinations but swaps registers in six instructions; the existing typed subobject symbol yields exact bytes. The complete experiment is retained in the producer evidence. The materialized connection-error predicate is preserved.

The 0x02117e84 caller is compiled as C++ with its existing C linkage; it uses the native null PMF and the declared `dScene_c::StartSceneFade` interface. Source enrollment follows srcpath. The other external caller uses the real icon array and fields. The migrated caller now declares the network flag result as u8, matching its definition without changing bytes. Its readiness helper at 0x02116ce4 explicitly accepts the unused scene argument: the sole retail call at 0x02117f2c sets r0, and removing that argument changes the caller. The helper body remains unchanged. No function ownership, credit, BSS/data ownership or class-consolidation claim changes.

## Remaining scope and coordination

The RESULT factory now initializes its local native Step to zero, eliminating the last raw null-global declaration; its three existing aggregate stores and the remaining manual construction stay separate. Other callbacks, callback-table initialization and the scalar declaration of `data_ov075_0211d930` remain unreconstructed; the existing typed read cast at that boundary stays. The inferred method, exact argument spelling and retained table alias are disclosed in the header and production manifest.

The rename ledger is reserved by `issue2410-sound-playsub1015`. One proposed append-only row is prepared privately for ov075:0x02119dc4; applying it requires a bounded coordination exception. The reserved source-style exception file is unchanged: its old one-use `unk_287` allowance is now unused. Removing that allowance is deferred cleanup, not a new source-pattern exemption.

## Proof and publication

The producer's initial native function check verifies all 828 bytes and 32 strict destinations with zero blind or missing relocations. Both external callers independently pass their linked-byte check. Final evidence must cover the complete changed-header consumer set, every owned function and emitted passenger, full production ROM, declarations, formatting, enrollment and references. The queue evidence binds final terminal counts and hashes to an immutable candidate/base. Shared metadata authorization, independent acceptance and PR publication remain distinct from local byte proof.
