# Cap-icon manager shared state

This commit defines six native shared BSS globals in the cap-icon request manager and gives its two consumers one declaration header. It adds 32 bytes of source-owned OV001 storage without changing existing function bytes or relocation destinations. The manager is a reconstructed owner chosen from its request/dispatch role, not a recovered original TU assignment.

Task `data-capicon-bss-native1018`, issue [4101](https://github.com/tangosdev/sm64ds-decomp/issues/4101), producer `codex-capicon-bss-native1018`, branch `data/capicon-bss-native1018`. Exact tested base is `2ce7feae14acb61960daa513f01d9c7e2dcd59ef`, the accepted CapIcon metadata predecessor from PR #4104. Queue workflow is `18af52b49b9fb5663d417bdfa86109b7b157aaa3`; the queue records this commit's immutable SHA. Independent acceptance and private PR validation are subsequent gates. No merge is authorized.

## Storage and consumers

`include/CapIconMgr.h` is included by exactly the manager and list-node sources. The existing `CapIcon.h` class definition is unchanged. C linkage preserves the six configured identities after descriptive renames:

| OV001 address | Reconstructed global | Native type | Bytes |
|---|---|---|---|
| 020ad620 | gCapIconFlashTimer | u8 | 1 |
| 020ad624 | gCapIconDispatchLocked | u8 | 1 |
| 020ad628 | gCapIconRequestFlags | u8[3] | 3 |
| 020ad62c | gCapIconDispatchFlags | u8[3] | 3 |
| 020ad630 | gCapIconCounts | u8[4] | 4 |
| 020ad634 | gCapIconListHeads | dCapIcon_c*[3] | 12 |

These 24 native NOBITS bytes plus 8 internal natural ALIGNALL(4) bytes tile `[020ad620,020ad640)`. There is no synthetic padding array, initializer, custom source alignment or terminal-fill policy. The normal object preparation orders the six complete input sections by manifest anchors; actual final providers and the entire layout are checked.

The configured incoming census contains 31 sites: 20 manager and 11 node. Their old/new target names are paired at exact function, offset, relocation type and addend; no generic relocation mask is used. The six configured Link call sites support character indices 0..2: three Dossy calls use 2; MarioCap initialization rejects indices at least 3; CapEnemy AddCap reduces an accepted value modulo 3; the other CapEnemy path uses its existing bounded character with unchanged flag bits. This does not claim safety for corrupt or unconfigured indirect inputs.

The flash timer is a 60-frame countdown; the dispatch byte is set and cleared as a lock. Flag indexing observes three entries, but both native `[3]`+alignment and `[4]` declarations reproduce the binary. The minimal observed extent is used and the original length remains unknown. Counts deliberately has four bytes: `Unlink` writes sentinel 3 to `mCharacter` before indexing counts. The reset loop clears only 0..2. The apparent anomaly is preserved, not repaired or assigned an invented purpose.

Private probes defining the same state in either TU preserve all prior output. Manager ownership is selected for readable subsystem organization; the independent reset/list consumer remains in its existing source. All six names are descriptive reconstructions.

## Preserved boundaries and debt

Accepted node metadata `[020ad450,020ad478)` remains native:37 object bytes + 3 internal alignment, full 16-byte vtable storage/public 8-byte address point and the numeric zero-size public alias. Actual prepared RTTI targets the public ABI vtable symbol plus 0; raw ABI source emission has the separate prefix-based +8 calculation. The predecessor's mistaken prepared-import prose is preserved in historical findings and fixed in the current disposition.

Following BSS `[020ad640,020ad660)` stays DSD-owned. Its two configured references at ad640/ad644 come through other shadow-model descriptor fields; the remaining ownership and extents are not guessed. ARM9 slot/player globals, encoded helpers, raw unique-ID access, CapNode overlays, integer pointer walks, the inherited helper call cast and positional codegen pragmas remain reconstruction debt. No complete original TU or whole subsystem recovery is claimed. All seven predecessor finding IDs and their earlier text are retained; partial BSS resolution does not close the ARM9/shared-type work.

## Proof and handoff

Pinned2004/b56 compilation preserves 23 prior definitions, 20 emitted functions and 113 relocations after exactly 31 global target-spelling substitutions at unchanged addresses. Both sources preserve their complete initialized objects and all method bytes; the manager adds only six NOBITS definitions. Standalone checks pass 11/11 and 7/7. Strict checks verify all 18 licensed functions with zero warnings or blocking findings; the node's two unconfigured C2/D2 variants retain the prior policy.

Final-config source-independent control and both intact-TU scratch links reproduce 106 modules and full 16 MiB ROM SHA256 `d1506e90efae5e2d2cf119926a4ac2a291bd5ca78349d09d5024e1a918c478e8`. Nine known strict-symbol diagnostics remain, with zero new. Default normal production proves nine actual providers from two prepared source objects: six BSS layouts and three retained metadata objects. The final checker separately proves 3312 manager text bytes, 780 node text bytes, full 40-byte metadata, full vtable/public alias, all 32 BSS layout bytes and excluded neighboring DSD storage. BSS proof is storage/layout ownership, not initialized-ROM payload comparison.

Private scripts/reports are in this producer worktree's `build/`: `prove-bss-native.py`, `native/proof.json`, `requests.json`, `prove-bss-production.py`, `bss-production.json`, `bss-final-ownership.json`, control/scratch/strict/static logs and the producer evidence. The original scout under `C:/tmp/sm64ds-capicon-bss-scout1018/build/capicon-bss` retains both owner/flag-length alternatives, all31 incoming sites, the two excluded shadow references and all Link-caller evidence. Only the current immutable source and freshly bound production inputs establish this candidate's acceptance; research artifacts are not substituted for final proof.

Source style, declaration agreement, exact two-source header fanout, port references, rename ledger, manifest conflicts, dead references and coverage pass. Coverage adds 32 BSS bytes with zero giveback. Incidental unrelated manifest serialization is restored only after parsed identity checks. Current intact admission is retained under `verification.linkcheck`; historical text snapshots remain explicitly separate. The experiment JSON records every finding and concrete remaining owner/issue.

The normal production run measured clean runtime commit 0320fb9af2c933e40f6e8a008ee2cf83b7665907. The final handoff/experiment commit changes documentation only. All 7,174 actual input/build/artifact bindings are rehashed afterward, and all 4,101 bound tracked inputs are compared with the final committed blobs. The earlier runtime SHA remains explicit; it is not relabeled as a rerun on the documentation descendant.

The optional broad raw-object data diagnostic retains the pre-existing ARM9 `_ZTV10dCcAcPos_c` difference in the two legacy destructor objects (two bytes per record). This is separate from the passing actual-provider, module and full-ROM gates; the diagnostic is not reported as wholly green.
