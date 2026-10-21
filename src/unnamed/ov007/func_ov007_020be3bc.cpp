//cpp
extern "C" void *func_ov007_020b7690(int i);
extern int* data_ov007_0210342c;
extern int* data_ov007_02104bc0;

/* NitroSDK's GXOamAffine: one OBJ affine matrix, its four Q8 parameters in
 * the fourth halfword of four consecutive OAM entries. */
struct GXOamAffine {
    unsigned short _0[3];
    short PA;
    unsigned short _1[3];
    short PB;
    unsigned short _2[3];
    short PC;
    unsigned short _3[3];
    short PD;
};

/* The manager's +0x74: the 0x48-byte 2D display record func_ov007_020b7594
 * allocates; names as in func_ov007_020adc08, only the slot this file reads. */
struct Ov007Display {
    char pad_00[0x14];
    /* 0x14: the sub screen's 0x400-byte OAM buffer; func_ov007_020b7384 copies
   * it to 0x07000400 (func_02056674), and +0x10 to the main screen's OAM */
    char *oamSub;
};

/* data_ov007_0210342c: the overlay's manager; only the slot this file reads. */
struct Ov007Work {
    char pad_00[0x74];
    Ov007Display *display; /* 0x74: func_ov007_020b6d40 stores func_ov007_020b7594's record */
};

/* *data_ov007_02104bc0: the 0x108-byte record func_ov007_020be50c allocates
 * (+0x00 its Ov007SpriteGroup, +0x04 its TrackingRecord array, both read by
 * func_ov007_020be684); medium-confidence name. Only the slot this file
 * reads. */
struct Ov007ParticleSprites {
    char pad_00[8];
    /* 0x08: sixteen OBJ affine matrices (PA, PB, PC, PD in Q12);
   * func_ov007_020be8b8 fills each with a uniform scale */
    int affine[16][4];
};

typedef char
    Ov007ParticleSprites_size_must_be_0x108[sizeof(Ov007ParticleSprites) == 0x108 ? 1 : -1];
typedef char GXOamAffine_size_must_be_0x20[sizeof(GXOamAffine) == 0x20 ? 1 : -1];

/* Once func_ov007_020b7690 has particle systems 0 and 1, copies the sixteen
 * affine matrices into the sub screen's OAM buffer, Q12 down to Q8. */
#pragma opt_strength_reduction off
extern "C" void func_ov007_020be3bc(void){
    char *r4 = ((Ov007Work *)data_ov007_0210342c)->display->oamSub;
    if (func_ov007_020b7690(0) == 0)
        return;
    if (func_ov007_020b7690(1) == 0)
        return;
    {
        int count = 0;
        int soff = 0;
        int doff = 0;
        do {
            int *s = (int *)((char *)((Ov007ParticleSprites *)data_ov007_02104bc0)->affine + soff);
            GXOamAffine *d = (GXOamAffine *)(r4 + (doff << 3));
            d->PA = (short)(s[0] >> 4);
            count++;
            d->PB = (short)(s[1] >> 4);
            d->PC = (short)(s[2] >> 4);
            soff += 0x10;
            d->PD = (short)(s[3] >> 4);
            doff += 4;
        } while (count < 0x10);
    }
}
