/* NitroSDK OSi_SendToPxi (os_reset.c): send one OS command to the ARM7,
 * retrying until the FIFO takes it. */
#include "types.h"

#define PXI_FIFO_TAG_OS 12

/* local extern: no PXI header in include/ yet (src/engine/pxi/PXI_Fifo.cpp). */
extern int PXI_SendWordByFifo(unsigned int tag, unsigned int data, unsigned int err);

void OSi_SendToPxi(u16 data) {
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_OS, (u32)data << 8, 0))
        ;
}
