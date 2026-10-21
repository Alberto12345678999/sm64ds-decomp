extern int func_ov007_020c3df4(int a, void *b);
extern void *func_ov007_020c8b10(void);
extern void InitialiseVramGlobals(void);
extern int func_ov007_020b3f20(int n);
extern int func_ov007_020bc6d4(int a, int b);

/* The model func_ov007_020bc6d4 builds; names as in func_ov007_020be9ac,
 * only the slot this file writes. */
typedef struct Ov007Model {
    char pad_00[0x94];
    int visible; /* 0x94: func_ov007_020bbff0 renders only while it is nonzero */
} Ov007Model;

/* The 0x14-byte screen-fade record at data_ov007_02104bd8. */
typedef struct Ov007Fade {
    void *transition;  /* 0x00: func_ov007_020c8498's Ov007Transition, built by func_ov007_020c8b10 */
    Ov007Model *model; /* 0x04: freed by func_ov007_020bfc54 through func_ov007_020bc53c */
    int flags;         /* 0x08: RequestScreenFade's second argument */
    void *onEnd;       /* 0x0c: RequestScreenFade's third; func_ov007_020bf790 copies it to Ov007Transition::onEnd */
    int request;       /* 0x10: RequestScreenFade's first; func_ov007_020bf690 runs func_ov007_020bf790 while it is set */
} Ov007Fade;

typedef char Ov007Fade_size_must_be_0x14[sizeof(Ov007Fade) == 0x14 ? 1 : -1];

extern char *data_ov007_02104bd8;
#define FADE ((Ov007Fade *)data_ov007_02104bd8)

void func_ov007_020bfcec(void)
{
    int r;

    data_ov007_02104bd8 = (char *)func_ov007_020c3df4(0, (void *)sizeof(Ov007Fade));
    FADE->transition = func_ov007_020c8b10();
    InitialiseVramGlobals();
    r = func_ov007_020b3f20(0x24);
    r = func_ov007_020bc6d4(r, 0);
    FADE->model = (Ov007Model *)r;
    FADE->model->visible = 0;
    FADE->request = 0;
    FADE->flags = 0;
    FADE->onEnd = 0;
}
