/* data_ov007_02104ba0: the picker scene func_ov007_020b9880 allocates;
 * slot 0 is the touch picker. */
struct S { char *picker; };

/* The 0xd0-byte touch picker func_ov007_020c690c builds; names as in
 * func_ov007_020c684c, only the slots this function touches. */
typedef struct {
    int x, y, z;
} Vec3;
typedef struct Ov007Picker {
    char pad_00[0x70];
    Vec3 pos;       /* 0x70 */
    Vec3 restPos;   /* 0x7c */
    Vec3 posOffset; /* 0x88: func_ov007_020c5188 adds it to pos for one step */
} Ov007Picker;

extern struct S *data_ov007_02104ba0;
/* The typed picker view of the scene's slot 0. */
#define PICKER ((Ov007Picker *)data_ov007_02104ba0->picker)

extern void func_ov007_020c5c14(char *self, char *out);
extern void func_ov007_020c64c4(char *c, int b);
extern void func_ov007_020c62cc(char *a, int b);
extern void func_ov007_020c55bc(char *c, int a, int b);
extern void func_ov007_020c56bc(char *c, int a, int b, int d, int e, int f);

void func_ov007_020bbc08(int mode, int a1, int a2)
{
    char *p;

    switch (mode) {
    case 0:
    case 1:
        if (mode == 1) {
            func_ov007_020c5c14(data_ov007_02104ba0->picker, (char *)&PICKER->pos);
        }
        p = data_ov007_02104ba0->picker;
        func_ov007_020c64c4(p, 0);
        func_ov007_020c62cc(p, 1);
        func_ov007_020c55bc(data_ov007_02104ba0->picker, 0x1000, 0x1000);
        PICKER->posOffset.y = 0;
        PICKER->posOffset.x = PICKER->posOffset.y;
        break;

    case 2:
        func_ov007_020c56bc(data_ov007_02104ba0->picker, 1, a1, a2 / 2, a2 / 2, 8);
        break;

    case 3:
        func_ov007_020c56bc(data_ov007_02104ba0->picker, 2, a1, a2, a2, 6);
        break;
    }
}
