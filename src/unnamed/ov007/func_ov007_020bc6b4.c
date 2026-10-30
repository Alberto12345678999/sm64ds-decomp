#include "Ov007Model.h"

extern void *func_ov007_020c92ac(void);

/* Binds the model's bone animations: n BCA files and a fresh
 * func_ov007_020c92ac player. */
void func_ov007_020bc6b4(Ov007Model *m, struct BCA_File **files, int n) {
    m->numBoneAnims = n;
    m->boneAnims = files;
    m->boneAnim = func_ov007_020c92ac();
}
