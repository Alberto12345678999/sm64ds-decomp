// @symbol func_ov006_020cf2fc
/* recovered: shared minigame 3D code (the block before dScMgAmida_c): loads the object's placement and scale matrices, then draws its 4x4 vertex patch (positions at +0x5c, packed normals at +0x2dc) as three triangle strips per face, the back face first with negated normals. */
// NONMATCHING: div 46 of 279 words. mwccarm 2004/b56, --module ov006,
// @ 0x020cf2fc size 0x45c. Size, frame, stack webs and register colouring all match;
// the residue is instruction scheduling only: in the first (back-face) strip loop the
// vertex word loads issue z, x, then y late with the pointer step beside the y load
// (ROM: x, y, z together, step after), and in the second loop the vertex pointer step
// and the row counter step trade places and the inner compare sits earlier.
// History: first drafted from nearmiss/db.jsonl (stored divergence 164) and landed
// 2026-09-14 under Tango's ruling that functionally-equivalent C drafts live on main
// with an honest banner. Rewritten 2026-10-02 with per-row vertex and normal pointers
// declared ahead of the strip counter, which turns the stack constant webs and the
// callee-saved colouring into the ROM's without any helper locals (164 -> 46).
// Counts as decompiled, not matched; tools/enroll.py leaves it out of the ROM build,
// which keeps the original bytes for this range. A byte-exact match replaces this file
// and drops the banner.
typedef volatile unsigned int vu32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

typedef struct
{
  s32 x;
  s32 y;
  s32 z;
} Vec3;

struct Matrix4x3;
extern struct Matrix4x3 data_020a0e68;
extern struct Matrix4x3 data_0209b3ec;
extern unsigned short data_ov006_0212e060[];
extern unsigned short data_ov006_0212e068[];
extern int data_ov006_0212e0b0[];
extern void *data_ov006_02140844;
extern void *data_ov006_02140814;
extern void Matrix4x3_FromTranslation(struct Matrix4x3 *m, int x, int y, int z);
extern void MulMat4x3Mat4x3(const int *a, const int *b, int *dst);
extern void Matrix4x3_ApplyInPlaceToScale(struct Matrix4x3 *m, int x, int y, int z);
extern void func_020553a4(int *m);

#define REG_MTX_MODE       (*(vu32 *)0x4000440)
#define REG_MTX_IDENTITY   (*(vu32 *)0x4000454)
#define REG_MTX_SCALE      (*(vu32 *)0x400046c)
#define REG_NORMAL         (*(vu32 *)0x4000484)
#define REG_TEXCOORD       (*(vu32 *)0x4000488)
#define REG_VTX_16         (*(vu32 *)0x400048c)
#define REG_POLYGON_ATTR   (*(vu32 *)0x40004a4)
#define REG_TEXIMAGE_PARAM (*(vu32 *)0x40004a8)
#define REG_TEXPLTT_BASE   (*(vu32 *)0x40004ac)
#define REG_DIF_AMB        (*(vu32 *)0x40004c0)
#define REG_SPE_EMI        (*(vu32 *)0x40004c4)
#define REG_BEGIN_VTXS     (*(vu32 *)0x4000500)
#define REG_END_VTXS       (*(vu32 *)0x4000504)

#define PATCH_VTX(obj) ((Vec3 *)((obj) + 0x5c))
#define PATCH_NRM(obj) ((int *)((obj) + 0x2dc))

static inline void G3_Vtx(s16 x, s16 y, s16 z)
{
  REG_VTX_16 = (u16)x | ((u16)y << 16);
  REG_VTX_16 = (u16)z;
}

#define SEND_VTX(p) G3_Vtx((s16)((p)->x >> 8), (s16)((p)->y >> 8), (s16)((p)->z >> 8))

void func_ov006_020cf2fc(char *obj)
{
  int i;
  int m2[12];
  int m1[12];
  Matrix4x3_FromTranslation(&data_020a0e68, *((int *) (obj + 8)), *((int *) (obj + 0xc)), *((int *) (obj + 0x10)));
  MulMat4x3Mat4x3((const int *) &data_020a0e68, (const int *) &data_0209b3ec, m1);
  Matrix4x3_ApplyInPlaceToScale(&data_020a0e68, *((int *) (obj + 0x2c)), *((int *) (obj + 0x30)), *((int *) (obj + 0x34)));
  MulMat4x3Mat4x3((const int *) &data_020a0e68, (const int *) &data_0209b3ec, m2);
  REG_MTX_MODE = 2;
  func_020553a4(m1);
  REG_MTX_MODE = 1;
  func_020553a4(m2);
  REG_MTX_SCALE = 0x100000;
  REG_MTX_SCALE = 0x100000;
  REG_MTX_SCALE = 0x100000;
  REG_MTX_MODE = 3;
  REG_MTX_IDENTITY = 0;
  REG_TEXIMAGE_PARAM = 0x8da70000 | ((u32) data_ov006_02140844 >> 3);
  REG_TEXPLTT_BASE = (u32) data_ov006_02140814 >> 4;
  {
    short *p31e = (short *) (obj + 0x31e);
    int sh = *p31e;
    unsigned short *dif = data_ov006_0212e060;
    volatile unsigned char *alpha = (volatile unsigned char *) (obj + 0x329);
    int pl = *alpha;
    REG_POLYGON_ATTR = (((sh + 1) << 24) | 0x82) | (pl << 16);
    {
      unsigned short *p326 = (unsigned short *) (obj + 0x326);
      unsigned idx = *p326;
      REG_DIF_AMB = dif[idx] | (data_ov006_0212e068[idx] << 16);
    }
  }
  REG_SPE_EMI = 0x8000;

  /* back face: row i then row i+1, normals negated */
  for (i = 0; i < 3; i++)
  {
    Vec3 *v0 = &PATCH_VTX(obj)[i * 4];
    Vec3 *v1 = &PATCH_VTX(obj)[(i + 1) * 4];
    int *n0 = &PATCH_NRM(obj)[i * 4];
    int *n1 = &PATCH_NRM(obj)[(i + 1) * 4];
    int k;
    REG_BEGIN_VTXS = 2;
    for (k = 0; k < 4; k++)
    {
      REG_TEXCOORD = data_ov006_0212e0b0[i * 4 + k];
      REG_NORMAL = -*n0++ & 0x3fffffff;
      SEND_VTX(v0);
      v0++;
      REG_TEXCOORD = data_ov006_0212e0b0[(i + 1) * 4 + k];
      REG_NORMAL = -*n1++ & 0x3fffffff;
      SEND_VTX(v1);
      v1++;
    }
    REG_END_VTXS = 0;
  }

  /* front face: row i+1 then row i */
  for (i = 0; i < 3; i++)
  {
    Vec3 *v0 = &PATCH_VTX(obj)[i * 4];
    Vec3 *v1 = &PATCH_VTX(obj)[(i + 1) * 4];
    int *n0 = &PATCH_NRM(obj)[i * 4];
    int *n1 = &PATCH_NRM(obj)[(i + 1) * 4];
    int k;
    REG_BEGIN_VTXS = 2;
    for (k = 0; k < 4; k++)
    {
      REG_TEXCOORD = data_ov006_0212e0b0[(i + 1) * 4 + k];
      REG_NORMAL = *n1++;
      SEND_VTX(v1);
      v1++;
      REG_TEXCOORD = data_ov006_0212e0b0[i * 4 + k];
      REG_NORMAL = *n0++;
      SEND_VTX(v0);
      v0++;
    }
    REG_END_VTXS = 0;
  }
}
