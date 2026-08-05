typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;

extern void func_ov007_020c1448(int *a, int b, int c, int d, int e);
extern void func_ov007_020c1404(int *c);
extern void func_ov007_020c49bc(int a0, int a1, int a2, int a3, int s0, int s1, int s2, int s3);
extern int data_ov007_0210325c;

void func_ov007_020c4684(char *a0, int a1, int a2, int a3, int flags, s16 *pos)
{
    int sbv;
    u16 w, h;
    int sx;
    int sy;
    int fpv;
    int *tex;
    int sp18;
    int sp1C;
    s16 *p;

    sx = *(s16 *)(a0 + 0x70) << 12;
    sy = *(s16 *)(a0 + 0x72) << 12;
    fpv = sbv = 0;
    w = *(u16 *)(a0 + 0x60);
    h = *(u16 *)(a0 + 0x62);
    sp18 = (flags & 8) ? *(int *)(a0 + 0x84) : 0;
    p = pos;
    if (a2 == 0)
        return;

    tex = ((int **)*(int *)(a0 + 0x5c))[*(u16 *)(a0 + 0x5a)];
    *(volatile u32 *)0x4000480 = a1;
    if (tex != 0)
    {
        sbv = 8 << tex[5];
        fpv = 8 << tex[6];
    }
    func_ov007_020c1448(tex, 1, *(int *)(a0 + 0x64), *(int *)(a0 + 0x68), *(int *)(a0 + 0x6c));
    func_ov007_020c1404(tex);
    sp1C = sbv;
    *(volatile u32 *)0x40004a4 = ((*(int *)(a0 + 0x54) | 0x80) | (a3 << 24)) | (a2 << 16);
    if (tex != 0)
    {
        if (w == 1)
            sbv = *(u16 *)(a0 + 0xc);
        if (h == 1)
            fpv = *(u16 *)(a0 + 0xe);
    }
    *(volatile u32 *)0x4000444 = 0;
    {
        int cx = *(int *)(a0 + 0x20);
        int cy = *(int *)(a0 + 0x24);
        int tx, ty, tz, k, q1, q2;
        tx = p[0] + (-cx) / 2;
        tz = p[2];
        ty = p[1] + (-cy) / 2;
        *(volatile u32 *)0x4000470 = tx;
        *(volatile u32 *)0x4000470 = ty;
        *(volatile u32 *)0x4000470 = tz;
        k = data_ov007_0210325c;
        q1 = (int)(((s64)cx * k + 0x800) >> 12);
        q2 = (int)(((s64)cy * k + 0x800) >> 12);
        *(volatile u32 *)0x400046c = q1;
        *(volatile u32 *)0x400046c = q2;
        *(volatile u32 *)0x400046c = 0x1000;
    }
    if (!(flags & 1) && !(flags & 2))
    {
        func_ov007_020c49bc(sbv, fpv, sx, sy, w, h, sp18, sp1C);
    }
    else
    {
        int f;
        u16 yl, xl, y2, x2;
        f = *(int *)a0 & 2;
        *(volatile u32 *)0x4000500 = 1;
        if (f)
            *(volatile u32 *)0x4000480 = *(u16 *)(a0 + 0x46);
        yl = (u16)((sy << 8) >> 16);
        xl = (u16)((sx << 8) >> 16);
        *(volatile u32 *)0x4000488 = (u32)xl | (yl << 16);
        *(volatile u32 *)0x400048c = 0x10000000;
        *(volatile u32 *)0x400048c = 0;
        if (f)
            *(volatile u32 *)0x4000480 = *(u16 *)(a0 + 0x48);
        y2 = (u16)((((fpv << 12) * h + sy) << 8) >> 16);
        *(volatile u32 *)0x4000488 = xl | (y2 << 16);
        *(volatile u32 *)0x400049c = 0;
        if (f)
            *(volatile u32 *)0x4000480 = *(u16 *)(a0 + 0x4a);
        x2 = (u16)((((sbv << 12) * w + sx) << 8) >> 16);
        *(volatile u32 *)0x4000488 = (y2 << 16) | x2;
        *(volatile u32 *)0x4000498 = 0x1000;
        if (f)
            *(volatile u32 *)0x4000480 = *(u16 *)(a0 + 0x4c);
        *(volatile u32 *)0x4000488 = x2 | (yl << 16);
        *(volatile u32 *)0x400049c = 0x1000;
        *(volatile u32 *)0x4000504 = 0;
    }
    *(volatile u32 *)0x4000448 = 1;
}
