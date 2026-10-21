#include "BMD_File.h"

void *_ZN5Model27LoadCompressedTextureToVramEPcjS0_(char *a, unsigned int b, char *c);
int func_02045ad8(void *p);
unsigned int func_02045a50(const void *src, unsigned int size);

/* The mesh's material block: the same five words, in the same order, as
 * daPicGate_c's record (include/private/Ov080Mat.h), with that header's
 * names. func_ov075_0211a948 pushes it to the geometry engine. */
typedef struct EntryMeshMaterial {
    u32 texAddr; /* 0x00 */
    u32 pltAddr; /* 0x04 */
    u32 difAmb;  /* 0x08 */
    u32 speEmi;  /* 0x0c */
    u32 param;   /* 0x10 -- TEXIMAGE_PARAM format, size and pltt0 bits */
} EntryMeshMaterial;

/* func_ov075_0211afb0.c's EntryMesh view, extended by the material block;
 * only the field this file writes. */
typedef struct EntryMesh {
    u8 pad_00[0x88];
    EntryMeshMaterial mMaterial; /* 0x88 */
} EntryMesh;

/* Load the mesh's texture and palette from its BMD file into VRAM and keep
 * the addresses with the first material's colours and the texture's
 * parameter word; 0 if either load failed. */
int func_ov075_0211aa94(char *c, char *b)
{
    EntryMesh *mesh = (EntryMesh *)c;
    struct BMD_File *file = (struct BMD_File *)b;
    char *d;
    struct BMD_Texture *tex;
    struct BMD_Palette *pal;
    int sz;

    tex = file->textures;
    d = (char *)file->materials;
    pal = file->palettes;

    mesh->mMaterial.texAddr = (u32)_ZN5Model27LoadCompressedTextureToVramEPcjS0_(
        tex->data, tex->size, tex->data + tex->size);
    sz = pal->size;
    if (sz <= 8)
        mesh->mMaterial.pltAddr = func_02045ad8(pal->data);
    else
        mesh->mMaterial.pltAddr = func_02045a50(pal->data, (unsigned int)sz);
    /* d is the first BMD_Material. Its words at 0x28/0x2c are the colours
       func_ov075_0211a948 pushes to DIF_AMB/SPE_EMI, but BMD_File.h still
       has them as pad_28 (317 consumers), so they stay raw here. */
    mesh->mMaterial.difAmb = *(int *)(d + 0x28);
    mesh->mMaterial.speEmi = *(int *)(d + 0x2c);
    mesh->mMaterial.param = tex->flags;
    if (mesh->mMaterial.texAddr == 0 || mesh->mMaterial.pltAddr == 0)
        return 0;
    return 1;
}
