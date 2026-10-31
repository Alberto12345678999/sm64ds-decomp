#include "nitro/spi/pm.h"

extern unsigned char data_0208ee3c;
void TurnBacklightOn(void) {
    if (PM_SetBackLight(2, 1) == 0) {
        data_0208ee3c = 1;
    }
}
