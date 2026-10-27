extern int div(int, int);
extern void func_ov007_020c9110(void* p);
extern void _ZN15ModelComponents11UpdateBonesEP8BCA_Filei(void* model, void* bca, int frame);
extern void func_0204531c(void* model, int x);

/* The 0x1c-byte animation player func_ov007_020c92ac allocates and
 * func_ov007_020c9110 ticks; names as in func_ov007_020bc02c, only the slots
 * this file reads. */
typedef struct Ov007AnimPlayer {
    char pad_00[0xc];
    short anim; /* 0x0c: index into the owner's animation table; -1 none */
    char pad_0e[2];
    unsigned short frame; /* 0x10: the whole frame func_ov007_020c9110 last reached */
} Ov007AnimPlayer;

/* The 0xa0-byte model record func_ov007_020bc6d4 allocates; names as in
 * func_ov007_020bc02c and func_ov007_020bc6d4, only the slots this file
 * touches. */
typedef struct Ov007Model {
    void *model; /* 0x00: the ModelComponents */
    char pad_04[0x10];
    void **boneAnims; /* 0x14: BCA_File table; Ov007AnimPlayer::anim indexes it */
    char pad_18[0x70];
    Ov007AnimPlayer *blendAnim; /* 0x88: the cross-fade's source pose */
    /* 0x8c: frames left of the cross-fade; func_ov007_020bc374 seeds it and
     * blendFrameCount with the same length */
    short blendFrames;
    short blendFrameCount; /* 0x8e: the cross-fade's length; blendFrames / it is the weight */
    char pad_90[8];
    int animTick; /* 0x98: 1 on the frames that step the animations */
} Ov007Model;

typedef char Ov007Model_size_must_be_0x9c[sizeof(Ov007Model) == 0x9c ? 1 : -1];

/* Poses the model from blendAnim's current frame and blends it in with
 * weight blendFrames / blendFrameCount, counting blendFrames down on the
 * frames that step the animations. c keeps the char * spelling of the
 * callers' declarations; `m` is the typed view. */
void func_ov007_020bc7dc(char* c)
{
    Ov007Model *m = (Ov007Model *)c;
    void *model = m->model;
    Ov007AnimPlayer *p = m->blendAnim;
    void *entry = m->boneAnims[p->anim];
    int quot = div(m->blendFrames << 12, m->blendFrameCount);

    if (m->animTick != 0)
        func_ov007_020c9110(m->blendAnim);

    p = m->blendAnim;
    if (p->anim != -1)
        _ZN15ModelComponents11UpdateBonesEP8BCA_Filei(model, entry, p->frame);

    func_0204531c(model, quot);

    if (m->animTick == 0)
        return;

    m->blendFrames -= 1;
    if (m->blendFrames <= 0)
        m->blendFrames = 0;
}
