# Nitro SDK file boundaries from pret's NitroSDK sources

Status: research note, 2026-10-29. Evidence for SDK TU folds in arm9 main.

## Method

pret/pokediamond carries the NitroSDK as per-file C (`arm9/lib/NitroSDK/src/*.c`,
with asm functions written as `asm void`). Each file compiles cleanly with
pokediamond's own pinned compiler (mwccarm 1.2/sp2p3, its `arm9/lib/NitroSDK/Makefile`
flags). That gives every SDK file's functions with sizes, in emitted section order.

The alignment matches each file's size sequence against the arm9 function list in
`config/arm9/symbols.txt`, address-ascending. It is a local alignment: an exact
size scores, a different size costs a little (SDK version drift), and a pret
function that is missing here costs almost nothing. Two things make such a gap
normal. pret's files hold only the functions Pokemon links, and this ROM holds only
the functions SM64DS links. An SM64DS function that pret doesn't have costs the
most, because it is the case that makes a boundary uncertain.

Diamond's SDK is about two years newer than ours, so some sizes drift. Function
order within a file has held everywhere it was checked except GX_g3x.c, where
SetFogTable and the 0x18 table loader after SetClearColor come in the other order.

## Screen on units already promoted

| pret file | aligned run | promoted TU | agrees? |
|---|---|---|---|
| GX.c | 0x02053a90.. (7 exact, GX_Init drifts 0x184 to 0x15c) | arm9/GX_Init | yes, both edges |
| GX_bgcnt.c | 0x02054d38..0x020551f0, 16/16 exact | arm9/G2 | yes, both edges |
| GX_vramcnt.c | 0x02053ea0..0x02054d38, 37 exact + 1 drift | arm9/GX_VramCnt | top edge yes; the TU also takes 3 functions below (0x02053e1c..0x02053ea0) that pret's file doesn't have |
| OS_system.c | 0x02059d08..0x02059d98, 8/8 | arm9/IRQ3 | yes; IRQ3 leaves out OS_SpinWait (func_02059d8c, the asm hatch) on purpose |
| OS_tcm.c, OS_protectionUnit.c | 1 and 2 exact | arm9/CP15_TCM, arm9/CP15_ProtectionUnit | yes |
| OS_cache.c | 0x02058bdc.., 5 exact + 1 drift | arm9/CP15 | yes |
| OS_irqTable.c + OS_interrupt.c | 0x02056c40..0x02056d64, then ..0x02057014 | arm9/OS_IrqTable + arm9/OS_Interrupt | fixed: arm9/IRQ held both files; split at 0x02056d64 (func_02057000 is OS_InitIrqTable, 0x14 here) |
| GX_load2d.c + GX_load3d.c | 0x02055dec..0x020568cc, then ..0x02056c1c | arm9/GXS + arm9/GX | no: split by namespace at 0x02056870, not at the file edge 0x020568cc |
| GX_g2.c | func_020551f0 + the 3 G2x members | arm9/G2x | partial: G2x_ChangeBlendBrightness_ (func_020551f0) is outside it |
| GX_g3x.c | 0x020553c0..0x02055998 | arm9/G3X (0x02055454..0x02055998, 13 functions) + func_020553c0.c | fixed: G3X holds the whole file except GXi_NopClearFifo128_ (func_020553c0, asm), which stays its own source because port/tools/hostgen.py skips any file with an asm block and the port hostgens G3X.cpp |

Where a promoted boundary came from TU evidence, the alignment reproduces it.
Where it came from a namespace (GXS/GX, G2x, G3X), it doesn't. Call-graph and
.rodata order failed this same screen; this method has an outside reference to
check against, and they don't.

## Unfolded shard runs that align

| pret file | run | result |
|---|---|---|
| MI_memory.c | 0x0205a448..0x0205a74c | 11/11 exact, 2 pret functions dropped by the linker: folded as arm9/MI_Memory |
| FX_mtx33.c | 0x020524f0..0x020527c0 | 6 exact, 1 extra 0x3c function here (func_02052514) |
| OS_spinLock.c | 0x02057014..0x02057410 | 17 exact, 1 drift, 1 extra (func_020570a8) |
| OS_alloc.c | 0x020590fc..0x020593a8 | 5/5 exact; func_02059040 below it is unexplained |
| OS_exception.c, OS_tick.c, OS_alarm.c | 0x020593f4..0x02059cb4 | 4, 4 and 8 exact, edges unresolved |
| SND_interface.c | 0x0205a8f0..0x0205adf8 | 21 exact, 2 drift, 3 extra |

The single-function SDK files sit between these runs: GX_state.c's GX_InitGXState
is func_02053d9c (0x80), and MI_swap.c's MI_SwapWord is func_0205a74c.
