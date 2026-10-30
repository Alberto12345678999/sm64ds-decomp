extern int __aeabi_idiv(int a, int b);

/* The particle definition's scale animation (SPL's SPLScaleAnim): the scale
 * ramps start -> mid over life rates [0, in), holds mid until out, then ramps
 * mid -> end over [out, 255]. */
struct ScaleAnim {
    short start;       /* 0x0 */
    short mid;         /* 0x2 */
    short end;         /* 0x4 */
    unsigned char in;  /* 0x6 */
    unsigned char out; /* 0x7 */
};

/* The particle definition (func_0204a730's PtclDef; SPL's SPLResource), whose
 * scaleAnim slot registers this function as a particle callback. */
struct PtclDef {
    void *data;                  /* 0x00 */
    struct ScaleAnim *scaleAnim; /* 0x04 */
};

struct Particle {
    char pad0[0x34];
    short animScale; /* 0x34 -- the animated scale factor, 0x1000 = 1.0 */
};

/* The scale animation callback; pret's SPL names it SPLAnim_Scale. lifeRate
 * is the particle's animation time, 0..255. */
void func_0204d440(struct Particle *ptcl, struct PtclDef *def, int lifeRate) {
    struct ScaleAnim *anim = def->scaleAnim;
    unsigned char in = anim->in;
    unsigned char out = anim->out;
    if (lifeRate < in) {
        short start = anim->start;
        ptcl->animScale = start + __aeabi_idiv(lifeRate * (anim->mid - start), in);
        return;
    }
    if (lifeRate < out) {
        ptcl->animScale = anim->mid;
        return;
    }
    {
        short end = anim->end;
        ptcl->animScale = end + __aeabi_idiv((lifeRate - 0xff) * (end - anim->mid), 0xff - out);
    }
}
