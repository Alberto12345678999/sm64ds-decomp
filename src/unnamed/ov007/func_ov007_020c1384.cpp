//cpp
extern "C" {

/* A sprite bank's 0x10-byte cell animation, as func_ov007_020c13a4 sizes
 * it; only the slots this file reads. */
typedef struct Ov007CellAnim {
    void *frames;    /* 0x00: one cell pointer per frame */
    void *durations; /* 0x04: u16 ticks per frame */
} Ov007CellAnim;

extern int func_ov007_020c3d1c(void *p);

/* Frees a cell animation's two tables. */
int func_ov007_020c1384(char *c) {
    Ov007CellAnim *anim = (Ov007CellAnim *)c;
    func_ov007_020c3d1c(anim->frames);
    return func_ov007_020c3d1c(anim->durations);
}
}
