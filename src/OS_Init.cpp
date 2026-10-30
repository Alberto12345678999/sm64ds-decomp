//cpp
/* OS_Init (the Nitro SDK's os_init.c). The call sequence is pret's, except
 * that this older SDK has no OS_SetIrqStackChecker or
 * OSi_InitVramExclusive step, and it calls MI_SetWramBank(MI_WRAM_ARM7_ALL)
 * directly where pret calls MI_Init. */
#include "nitro/os/spinLock.h"

extern "C" {

extern void OS_InitArena(void);
extern void PXI_Init(void);
extern void OS_InitArenaEx(void);
extern void OS_InitIrqTable(void);
extern void func_02059594(void); /* OS_InitException */
extern void MI_SetWramBank(int cnt);
extern void OS_InitVAlarm(void);
extern void OS_InitThread(void);
extern void OS_InitReset(void);
extern void CTRDG_Init(void);
extern void func_02060890(void); /* CARD_Init */
extern void PM_Init(void);

// @symbol OS_Init
void OS_Init(void) {
    OS_InitArena();
    PXI_Init();
    OS_InitLock();
    OS_InitArenaEx();
    OS_InitIrqTable();
    func_02059594();
    MI_SetWramBank(3);
    OS_InitVAlarm();
    OS_InitThread();
    OS_InitReset();
    CTRDG_Init();
    func_02060890();
    PM_Init();
}

} // extern "C"
