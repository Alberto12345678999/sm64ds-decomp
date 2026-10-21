extern void *func_ov007_020c9388(int initialState);
extern char *func_ov007_020c023c(void);
extern int func_ov007_020c241c(int a);
extern char *func_ov007_020c2068(void);
extern char *func_ov007_020c2304(void);
extern void *func_ov007_020c908c(void *r5);
extern int func_ov007_020c3df4(int a, void *b);
extern void func_02059eb0(unsigned char *dst);
extern char *data_ov007_0210342c;

/* The 0x3c-byte record allocated below; only the slot this file seeds. */
typedef struct Ov007Settings {
    char pad_00[0x3a];
    unsigned char language; /* 0x3a: seeded below from the owner-info language */
} Ov007Settings;

/* data_ov007_0210342c: the overlay's manager, names as in func_ov007_020afc44,
 * func_ov007_020b1718 and func_ov007_020b1cf0. This function builds every
 * slot spelled here. Left raw: +0xe8, cleared here and tested by
 * func_ov007_020b283c/func_ov007_020be850 with no role evidenced yet. */
typedef struct Ov007Work {
    char pad_00[4];
    void *states[3]; /* 0x04: func_ov007_020c9388(0 / -1 / 1) */
    char pad_10[0x18];
    Ov007Settings *settings; /* 0x28 */
    char pad_2c[4];
    char *cameras[2]; /* 0x30: func_ov007_020c023c */
    int lights[2];    /* 0x38: func_ov007_020c241c(0/1) */
    char pad_40[0x10];
    char *touch; /* 0x50: func_ov007_020c2068 */
    char *pad;   /* 0x54: func_ov007_020c2304 */
    char pad_58[0xc];
    int tweenOut[2]; /* 0x64: bound as tweens[i]->out */
    void *tweens[2]; /* 0x6c: func_ov007_020c908c */
} Ov007Work;

typedef char Ov007Work_size_must_be_0x74[sizeof(Ov007Work) == 0x74 ? 1 : -1];

/* The extern keeps the tree's char * spelling (the declaration-agreement
 * gate); the typed view is reached through a cast macro. */
#define WORK ((Ov007Work *)data_ov007_0210342c)

void func_ov007_020b6a84(void)
{
    unsigned char buf[0x54];
    int v;

    WORK->states[0] = func_ov007_020c9388(0);
    WORK->states[1] = func_ov007_020c9388(-1);
    WORK->states[2] = func_ov007_020c9388(1);
    WORK->cameras[0] = func_ov007_020c023c();
    WORK->cameras[1] = func_ov007_020c023c();
    WORK->lights[0] = func_ov007_020c241c(0);
    WORK->lights[1] = func_ov007_020c241c(1);
    WORK->touch = func_ov007_020c2068();

    WORK->pad = func_ov007_020c2304();
    WORK->tweens[0] = func_ov007_020c908c((void *)&WORK->tweenOut[0]);
    WORK->tweens[1] = func_ov007_020c908c((void *)&WORK->tweenOut[1]);

    WORK->settings = (Ov007Settings *)func_ov007_020c3df4(0, (void *)0x3c);

    /* The owner-info language (0 Japanese ... 5 Spanish) to the menu's own
     * numbering. */
    func_02059eb0(buf);
    v = buf[0];
    switch (v) {
    case 0:
    case 1:
        WORK->settings->language = 1;
        break;
    case 2:
        WORK->settings->language = 2;
        break;
    case 3:
        WORK->settings->language = 3;
        break;
    case 4:
        WORK->settings->language = 5;
        break;
    case 5:
        WORK->settings->language = 4;
        break;
    default:
        WORK->settings->language = 0;
        break;
    }
    *(int *)(data_ov007_0210342c + 0xe8) = 0;
}
