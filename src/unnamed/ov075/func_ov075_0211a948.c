// @symbol func_ov075_0211a948
/* recovered: material setup for the entry-menu grid mesh, the sub-object
 * dEntObj_c keeps at +0xe80 (func_ov075_0211afb0 calls this before it
 * draws the strips). An older banner credited this to dScEntry_c; the
 * offsets below are inside that class's icon array, not a material.
 *
 * Pushes the mesh's cached diffuse/ambient, specular/emission, texture
 * image param and palette base into the geometry engine, then a fixed
 * polygon attribute. Same Nitro G3 inline shape as func_ov080_02125460;
 * the palette shift is 3 for GX_TEXFMT_PLTT4 (2) and 4 otherwise, and the
 * format test has to complete BEFORE the palette address is loaded, so it
 * lives in its own statement.
 */
#include "types.h"
#include "private/ov075_entry_mesh.h"

// 6f: keep constant live / flip coloring
#pragma opt_propagation off

#define reg_G3_TEXIMAGE_PARAM (*(volatile u32 *)0x040004a8)
#define reg_G3_TEXPLTT_BASE   (*(volatile u32 *)0x040004ac)
#define reg_G3_DIF_AMB        (*(volatile u32 *)0x040004c0)
#define reg_G3_SPE_EMI        (*(volatile u32 *)0x040004c4)
#define reg_G3_POLYGON_ATTR   (*(volatile u32 *)0x040004a4)

static inline void G3_TexImageParam(u32 addr, u32 texFmt, u32 texGen, u32 sizeS, u32 sizeT,
                                    u32 repeat, u32 flip, u32 pltt0)
{
    reg_G3_TEXIMAGE_PARAM = (u32)((addr >> 3) | (texFmt << 26) | (texGen << 30)
        | (sizeS << 20) | (sizeT << 23) | (repeat << 16) | (flip << 18) | (pltt0 << 29));
}

static inline void G3_TexPlttBase(u32 addr, u32 texFmt)
{
    reg_G3_TEXPLTT_BASE = addr >> (4 - (texFmt == 2 ? 1 : 0));
}

void func_ov075_0211a948(char *c)
{
    EntryMesh *mesh = (EntryMesh *)c;

    reg_G3_DIF_AMB = mesh->mMaterial.difAmb;
    reg_G3_SPE_EMI = mesh->mMaterial.speEmi;
    G3_TexImageParam(mesh->mMaterial.texAddr, (mesh->mMaterial.param >> 0x1a) & 7, 0,
                     (mesh->mMaterial.param >> 0x14) & 7, (mesh->mMaterial.param >> 0x17) & 7, 0, 0,
                     (mesh->mMaterial.param >> 0x1d) & 1);
    {
        u32 fmt = (mesh->mMaterial.param >> 0x1a) & 7;
        u32 sub = (fmt == 2) ? 1 : 0;
        reg_G3_TEXPLTT_BASE = mesh->mMaterial.pltAddr >> (4 - sub);
    }
    reg_G3_POLYGON_ATTR = 0x11f0088;
}
