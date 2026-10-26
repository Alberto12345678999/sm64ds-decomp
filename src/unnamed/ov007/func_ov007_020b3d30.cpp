//cpp
#include "Ov007Sprite.h"
#include "Ov007Work.h"

extern "C" {
extern void func_ov007_020c43bc(void*, int);
extern char* data_ov007_0210342c;
extern unsigned char data_ov007_020d7dc8[];
extern unsigned char data_ov007_020d7dd0[];
extern unsigned char data_ov007_020d7dd1[];
extern unsigned char data_ov007_020d7ddc[];
extern unsigned char data_ov007_020d7ddd[];
extern unsigned char data_ov007_020d7dc0[];
extern short data_ov007_020d7de8[];
extern short data_ov007_020d7dea[];

#define WORK ((Ov007Work *)data_ov007_0210342c)

/* Sets up sprite `thiz` as entry idx of the data_ov007_020d7dc0..
 * data_ov007_020d7dea tables: its texture, texel origin, pixel size, shadow
 * polygon id and shadow offset, and its depth; then sizes it in world space
 * through camera 1 (func_ov007_020c43bc). */
void func_ov007_020b3d30(char* thiz, int idx){
    Ov007Sprite *sprite = (Ov007Sprite *)thiz;
    sprite->frames[0] = WORK->textures[data_ov007_020d7dc8[idx]];
    sprite->texS = data_ov007_020d7dd0[idx * 2];
    sprite->texT = data_ov007_020d7dd1[idx * 2];
    sprite->width = data_ov007_020d7ddc[idx * 2];
    sprite->height = data_ov007_020d7ddd[idx * 2];
    sprite->shadowPolygonId = data_ov007_020d7dc0[idx];
    sprite->shadowOffset[0] = data_ov007_020d7de8[idx * 2];
    sprite->shadowOffset[1] = data_ov007_020d7dea[idx * 2];
    if (idx == 1)
        sprite->depth = -0x10c0;
    else
        sprite->depth = (int)0xffffef38;
    func_ov007_020c43bc(thiz, (int)WORK->cameras[1]);
}
}
