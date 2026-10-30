#include "nitro/spi/pm.h"

extern unsigned char data_0208ee3c;
void TurnBacklightOff(void) {
    if (PM_SetBackLight(2, 0) == 0) {
        data_0208ee3c = 0;
    }
}
