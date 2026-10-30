//cpp
#include "Ov007Sprite.h"

extern "C" {

void func_ov007_020bfe4c(char *camera, int x, int y, int z, Vector3 *out);

/* Places a sprite in the world: unprojects its screen position at its depth
 * through the camera into pos. r0 and r1 keep the callers' char * and int
 * spellings; `sprite` is the typed view. */
void func_ov007_020c4388(char *r0, int r1) {
    Ov007Sprite *sprite = (Ov007Sprite *)r0;
    func_ov007_020bfe4c((char *)r1, sprite->screenX, sprite->screenY, sprite->depth, &sprite->pos);
}
}
