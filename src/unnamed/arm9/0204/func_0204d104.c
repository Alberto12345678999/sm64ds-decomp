/* The particle definition's child resource (func_0204a730's PtclChild; SPL's
 * SPLChildResource): the particles a particle emits. */
struct PtclChild {
    unsigned short flags; /* 0x0 */
    short pad2;
    short endScale; /* 0x4 -- a child's scale when its life ends, 0x1000 = 1.0 */
};

/* The particle definition (func_0204a730's PtclDef; SPL's SPLResource). */
struct PtclDef {
    void *data;
    void *scaleAnim;
    void *colorAnim;
    void *alphaAnim;
    void *texAnim;
    struct PtclChild *child; /* 0x14 */
};

struct Particle {
    char pad0[0x34];
    short animScale; /* 0x34 */
};

/* The child particles' scale callback (pret's SPL: SPLAnim_ChildScale): the
 * scale runs from 1.0 at birth to child->endScale at lifeRate 255. */
void func_0204d104(struct Particle *ptcl, struct PtclDef *def, int lifeRate) {
    int endScale;
    int delta;
    endScale = def->child->endScale;
    delta = (endScale - 0x1000) * (lifeRate - 0xff) / 255;
    ptcl->animScale = endScale + delta;
}
