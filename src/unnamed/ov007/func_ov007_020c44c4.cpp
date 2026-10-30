//cpp
#include "Ov007Sprite.h"

extern "C" {
int func_ov007_020c3d1c(void *);

/* Frees a sprite func_ov007_020c44e4 built: its frames array, then the
 * sprite. The int return is the free hook's tail call. */
int func_ov007_020c44c4(Ov007Sprite *sprite) {
    func_ov007_020c3d1c(sprite->frames);
    return func_ov007_020c3d1c(sprite);
}
}
