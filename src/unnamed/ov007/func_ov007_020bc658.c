#include "dExtModel_c.h"
#include "Ov007Model.h"

extern void *func_ov007_020c92ac(void);
extern void func_02046b64(void *modelFile, void *file);

/* Binds the model's texture-SRT animations: n BTA files, a fresh
 * func_ov007_020c92ac player, and each nonzero file prepared against the
 * model's BMD file. */
void func_ov007_020bc658(Ov007Model *m, struct BTA_File **files, int n) {
    int i;

    m->numTexSrtAnims = n;
    m->texSrtAnims = files;
    m->texSrtAnim = func_ov007_020c92ac();
    for (i = 0; i < n; i++) {
        if (m->texSrtAnims[i])
            func_02046b64(m->model->modelFile, m->texSrtAnims[i]);
    }
}
