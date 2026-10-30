//cpp
#include "types.h"
#include "G2.h"
#include "GX.h"

extern "C" {
s32 GetLanguageIndex(void);
u32 LoadCompressedFileAt(unsigned int fileID, void *target);
void *LoadFile(u16 fileID);
void Deallocate(void *ptr);
}

/* Per-language file IDs, indexed by GetLanguageIndex(). */
extern unsigned int data_0208a148[];
extern unsigned int data_0208a15c[];
extern unsigned int data_0208a120[];

/* Loads the main-engine BG2 graphics (language-specific character data and
 * the three screens 0x9808..0x980a), main OBJ character data at 0x2000 into
 * OBJ VRAM (0x06400000) with palette file 0x980f, and sub OBJ character data
 * at 0x800 into sub OBJ VRAM (0x06600000) with palette file 0x8400. Called from
 * src/game/stages/d_s_entry_methods.cpp and src/game/stages/d_s_mb.cpp; the
 * latter runs func_0200f220 (the sub-engine BGs) just before it. */
extern "C" void func_0200f13c(void) {
    s32 i = GetLanguageIndex();
    LoadCompressedFileAt(data_0208a148[i], G2::GetBG2CharPtr());
    LoadCompressedFileAt(0x9808, G2::GetBG2ScrPtr());
    LoadCompressedFileAt(0x9809, (char*)G2::GetBG2ScrPtr() + 0x800);
    LoadCompressedFileAt(0x980a, (char*)G2::GetBG2ScrPtr() + 0x1000);
    char *a5 = (char*)0x6400000; a5 += 0x2000;
    LoadCompressedFileAt(data_0208a15c[GetLanguageIndex()], a5);
    void *p = LoadFile(0x980f);
    GX::LoadOBJPltt(p, 0x120, 0xe0);
    Deallocate(p);
    char *a6 = (char*)0x6600000; a6 += 0x800;
    LoadCompressedFileAt(data_0208a120[GetLanguageIndex()], a6);
    void *q = LoadFile(0x8400);
    GXS::LoadOBJPltt(q, 0, 0x200);
    Deallocate(q);
}
