//cpp
#include "types.h"
#include "G2.h"

extern "C" {

extern s32 GetLanguageIndex(void);
extern u32 LoadCompressedFileAt(u32 fileID, void *target);

extern u32 data_0208a10c[];
extern u32 data_0208a134[];

/* Loads the sub-engine BG graphics: per-language BG2 characters (and BG3
 * characters at +0x6000, both indexed by GetLanguageIndex()), file 0x8405 at
 * BG3 characters +0x3000, files 0x9802, 0x9800 and 0x8408 into BG2 screen
 * memory at +0x800, +0x2000 and +0x2800, and file 0x8407 as BG3's screen.
 * func_0200f13c loads the main-engine side. */
void func_0200f220(void) {
    s32 idx;
    idx = GetLanguageIndex();
    LoadCompressedFileAt(data_0208a10c[idx], G2S::GetBG2CharPtr());
    idx = GetLanguageIndex();
    LoadCompressedFileAt(data_0208a134[idx], (char *)G2S::GetBG3CharPtr() + 0x6000);
    LoadCompressedFileAt(0x8405, (char *)G2S::GetBG3CharPtr() + 0x3000);
    LoadCompressedFileAt(0x9802, (char *)G2S::GetBG2ScrPtr() + 0x800);
    LoadCompressedFileAt(0x9800, (char *)G2S::GetBG2ScrPtr() + 0x2000);
    LoadCompressedFileAt(0x8408, (char *)G2S::GetBG2ScrPtr() + 0x2800);
    LoadCompressedFileAt(0x8407, G2S::GetBG3ScrPtr());
}
}
