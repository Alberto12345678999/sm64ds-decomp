#include "types.h"
struct G9d2c {
    char pad[0xc];
    u8 state; /* 0xc */
};
extern struct G9d2c data_020a9d2c;

extern int func_02068398(void);
extern void MBi_InitSendFixedBeacon(void);
extern void MBi_SendFixedBeacon(void);
extern void MBi_InitSendVolatBeacon(void);
extern void func_02067f68(void);

/* NitroSDK MB_SendGameInfoBeacon (mb_gameinfo.c): run the beacon send
   state machine until a step sets a beacon or there is nothing to send.
   Newer SDKs pass ggid, tgid and attr down to the two send steps; in this
   one MBi_SendFixedBeacon and func_02067f68 fetch them themselves, so the
   function takes no parameters. The parent's event handler MBi_CommParentCallback
   calls it on each BEACON_SENT (0x1c). */
void MB_SendGameInfoBeacon(void) {
    for (;;) {
        switch (data_020a9d2c.state) {
        case 0:
        case 1:
            if (func_02068398() != 0)
                break;
            return;
        case 2:
            MBi_InitSendFixedBeacon();
            break;
        case 3:
            MBi_SendFixedBeacon();
            return;
        case 4:
            MBi_InitSendVolatBeacon();
            break;
        case 5:
            func_02067f68();
            return;
        case 6:
            break;
        }
    }
}
