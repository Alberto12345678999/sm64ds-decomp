//cpp
#include "Ov007Sprite.h"

extern "C" {
int func_ov007_020c3d1c(void *);

/* Frees a sprite func_ov007_020c44e4 built: its frames array, then the
 * sprite. r4 keeps the callers' char * spelling; the int return is the
 * free hook's tail call. */
int func_ov007_020c44c4(char *r4) {
    Ov007Sprite *sprite = (Ov007Sprite *)r4;
    func_ov007_020c3d1c(sprite->frames);
    return func_ov007_020c3d1c(r4);
}
}
