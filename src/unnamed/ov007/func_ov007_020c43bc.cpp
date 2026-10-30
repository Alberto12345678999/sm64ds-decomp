//cpp
#include "types.h"
#include "cstd.h"
#include "nitro/fx/fx.h"
#include "Ov007Sprite.h"
#include "Ov007Camera.h"

extern s16 data_02082214[];

/* Sizes the sprite in world space for the camera: its pixel width and
 * height times |depth| * sin(fovy) / (cos(fovy) * 0x60), 0x60 being half the
 * screen's 192 lines (data_02082214 holds sine/cosine pairs). */
extern "C" void func_ov007_020c43bc(Ov007Sprite *sprite, Ov007Camera *camera) {
    int x = sprite->depth;
    int i = (camera->fovy >> 4) << 1;
    int j = i + 1;
    s16 cosFov = data_02082214[j];
    if (x < 0)
        x = -x;
    s16 sinFov = data_02082214[i];
    sprite->worldWidth =
        cstd::fdiv(FX_MUL((sprite->width << 12), FX_MUL(sinFov, x)), cosFov * 0x60);
    x = sprite->depth;
    i = (camera->fovy >> 4) << 1;
    j = i + 1;
    cosFov = data_02082214[j];
    if (x < 0)
        x = -x;
    sinFov = data_02082214[i];
    sprite->worldHeight =
        cstd::fdiv(FX_MUL((sprite->height << 12), FX_MUL(sinFov, x)), cosFov * 0x60);
}
