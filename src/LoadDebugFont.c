#include "types.h"
/* local extern: C file cannot include GX.h. */
extern void LoadBG1Char(const void *src, u32 offset, u32 size);
/* local extern: C file cannot include GX.h. */
extern void LoadBGPltt(const void *src, u32 offset, u32 size);
extern void func_02023408(void);

extern const void *data_0208a178;
extern const void *data_0208c178;

void LoadDebugFont(void)
{
    LoadBG1Char(&data_0208a178, 0, 0x2000);
    LoadBGPltt(&data_0208c178, 0x1a0, 0x60);
    func_02023408();
}
