# Snowman initializer adoption and remaining initializer disposition

Candidate: this commit. Base: `67bf07bbb364e06fe50de726ee2b2e99c51d1696`. Producer/integration owner:
`codex-overlay-root1016`; source scope tracks issue #2476. Independent acceptance
is recorded separately. This is a local candidate; no PR/merge is implied.

Adopt the Snowman-body fold from PR #3937, exact head
`e8dfc11bc8912f2d51fc945990efe945cf8f4618`. Apply only its actor source/manifest
and corresponding ov072 delinks/symbol rows. Snowman-head and baby-penguin
storage changes from that PR are not imported. Retire the leftover
`__sinit_ov072_02122018.c`, which the PR unenrolled but left tracked.

The adopted wrapper initially emitted **one byte**, because SharedFilePtr's
shared declaration is deliberately empty. Retail uses an eight-byte handle:
the actual SharedFilePtr implementation has u16 file ID, u8 reference count,
padding and a pointer. The local wrapper now reserves two u32 words, with a
target sizeof assertion. It is a reconstructed ABI wrapper, not recovered RTTI.
The model definition precedes six state records (twelve PMFs), then the reach
and landing vectors, preserving retail initialization order.

The candidate owns init 02122018..021221f8, ctor 02122708..0212270c and BSS
02122b20..02122bc4, in addition to its existing text/data. Compiler-generated
registration nodes are rebound from this candidate's actual initializer
relocations, not copied blindly from the imported @810/@811/@812 spellings.
The manifest retains canonical @174/@175/@176 destinations. No shared headers
or declaration/credit baselines are edited.

## Final proof

Pending terminal final checks; this section is updated before committing.
The text-oriented tubuild verifier sees 29/29 exact actor functions but reports
the generated initializer/ancestor metadata as extras. It is not the intact-
object acceptance gate. Production rombuild and its owned-range/storage gates
must prove the initializer, ctor, data and BSS. Prepush's direct raw-object
initializer check has five blind ABI/temp imports; that warning is not a pass
for those relocations. The final linked intact section comparison must close it.

## All 36 active initializers at the base

Snapshot disposition; refresh queue/PR heads before claiming the next scope.
No absence of a direct file claim is treated as permission to overwrite an
existing class/range owner. Root owns follow-through after those dependencies.

| Overlay / initializer | Disposition and next prerequisite |
|---|---|
|002 02100560|Mixed actor resources; investigate multi-owner boundaries; ov002 config held by enemy-switch-tu-1003.|
|002 02100f84|Kurumajiku vectors; class held by yegg-native-three-method-continuation1014; config reserved.|
|002 021019d0|Large Player resource initializer; typed resource recovery and reserved config required.|
|002 02107370|Demo resources; config reservation prerequisite.|
|002 02107f88|SoundObj tables; owner issue2410-sound-playsub1015 and config reserved.|
|002 0210804c|HUD-map vector; use d_map owner evidence, not adjacent actor; config reserved.|
|004 020b9ad0|Credit-coin array in unit020b4aa4; interior ranges held by minigame-statecalls-readable-0922.|
|004 020b9b24|Options-panel records; compose #3939.|
|006 0212f660|Puff array; compose minigame naming/readability PRs #3939/#3940/#3949/#3955.|
|006 0212f6b4|Trampoline Mario/resources; compose existing minigame PRs.|
|006 0212fc7c|Trampoline line/ring records; #3939/#3940/#3949/#3955 overlap.|
|006 0212fd48|Bomroom PMFs; minigame-bomroom-readable-0922 reservation and existing PRs.|
|006 02130a04|Empty four-byte initializer; retain unassigned without a curated owner witness.|
|006 021322bc|Roulette records; compose #3937/#3939/#3940/#3955.|
|009 02112524|MC-water resources/vectors; pr2747-repair-0918 owns source/config.|
|019 021127a4|Penguin racer; sound continuation reservation and #3937.|
|021 02113500|NewsLift handles/vectors; compose #3937 storage and #3942 body changes.|
|022 02112f78|UkiKi handles; yegg class reservation and pr2484-final-main-0911 config reservation.|
|022 02113050|Rolling-log handles; existing combined TU emits another initializer; prove dual ownership; config reserved.|
|030 02114924|Monkey resources; sound continuation reservation and #3937.|
|062 0211cf30|Holhei resources; yegg continuation reservation.|
|065 0211c110|Yurei Mucho/projectile resources; yegg continuation reservation.|
|072 02122018|Adopted/corrected in this candidate from #3937; old shard retired.|
|072 021221f8|Snowman head; sound continuation reservation and #3937 storage.|
|072 02122414|Baby penguin; compose #3937 initializer/storage changes.|
|075 0211bb00|Scene callback and step tables; finish typed entry-scene globals first.|
|075 0211c51c|Separate dEntObj embedded mesh; recover that owner, compose #3937 consumer.|
|077 0212749c|Spiny animation/states; shadowback-spiny-0920 reservation and #3937/#3938/#3951.|
|078 02126660|Bombking; compose #3937 storage and #3951 body changes.|
|079 02127a10|Bullet Bill and launcher resources; prove combined ownership; yegg reservation.|
|084 02130558|Red Bob-omb resources; yegg reservation.|
|084 02130654|Piranha/FPkn shared resources; yegg and sound continuation reservations.|
|085 0212f2a8|Toad resources; sound continuation reservation.|
|085 0212f3a0|Peach already folded and old shard deleted in #3937; reuse that candidate.|
|100 021474e8|Ibl resources/states; yegg reservation.|
|102 0214de70|Bob-omb resources/vectors; yegg reservation.|

The best subsequent isolated initializer fold is the ov004 coin array after its
interior ownership resolves: init 020b9ad0..020b9b24, ctor 020b9dec..020b9df0,
registration node 020bfa28..020bfa34, and twenty 0x24-byte Sprite records
020bfa34..020bfd04. Its constructor/destructor/cleanup tail is
020b67bc..020b67e8. The manifest anchors both boundaries through initializer
references. Generated array initialization is still an unmeasured recipe;
verify all 43 existing functions and storage before adopting it.

This candidate removes four shards total: 653 -> 649 (614 ordinary, 35 initializer).
It does not claim completion of all overlay reconstruction. No merges authorized.
