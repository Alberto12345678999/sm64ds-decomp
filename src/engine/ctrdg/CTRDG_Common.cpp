//cpp
/* Cartridge-slot common code (the Nitro SDK's ctrdg_common.c),
 * arm9 .text 0x0206a318..0x0206a600.
 *
 * pret/pokediamond's NitroSDK CTRDG_common.c has these seven functions in this
 * order, with the same bodies: CTRDGi_InitCommon, CTRDG_IsExisting,
 * CTRDGi_ChangeLatestAccessCycle, CTRDGi_RestoreAccessCycle,
 * CTRDGi_LockByProcessor, CTRDGi_UnlockByProcessor, CTRDGi_SendtoPxi. The
 * rest of that file (the CTRDG_IsAgbCartridge family, CTRDG_IsPulledOut, the
 * CTRDG_CpuCopy and CTRDG_Read routines, CTRDG_Enable) is not in this ROM.
 *
 * mwccarm defers C bodies and emits them in reverse, so the ROM runs
 * bottom-up: CTRDGi_SendtoPxi at 0x0206a318, CTRDGi_InitCommon at 0x0206a5c0.
 *
 * The lock-info and access-cycle records are int arrays; see
 * nitro/ctrdg/ctrdg_common.h.
 */
#include "types.h"
#include "IRQ.h"
#include "nitro/ctrdg/ctrdg_common.h"
#include "nitro/os/spinLock.h"

extern "C" {

// local extern: no header declares these yet.
extern void CpuSet(void *src, void *dst, u32 ctrl); // SVC_CpuClear
extern int IPCSend(u32 tag, u32 data, u32 reply);   // PXI_SendWordByFifo
extern void WaitByLoop(int count);                  // SVC_WaitByLoop

/* CTRDGi_Work: the ARM7's ack halfword, then the lock ID. */
extern u8 data_020a9de0[];

/* NitroSDK CTRDGHeader: the GBA cartridge header at HW_CTRDG_ROM. */
struct CTRDGHeader {
    u32 startAddress;      /* 0x00 */
    u8 nintendoLogo[0x9c]; /* 0x04 */
    char titleName[12];    /* 0xa0 */
    u32 gameCode;          /* 0xac */
    u16 makerCode;         /* 0xb0 */
    u8 isRomCode;          /* 0xb2 */
    u8 machineCode;        /* 0xb3 */
    u8 deviceType;         /* 0xb4 */
    u8 exLsiID[3];         /* 0xb5 */
    u8 reserved_A[4];      /* 0xb8 */
    u8 softVersion;        /* 0xbc */
    u8 complement;         /* 0xbd */
    u16 moduleID;          /* 0xbe */
};

#define HW_CTRDG_ROM 0x08000000
#define CTRDG_IS_ROM_CODE 0x96
/* Where a cartridge that is not ROM code keeps its module ID. */
#define CTRDG_MODULE_ID_IMAGE (*(u16 *)0x0801fffe)

/* NitroSDK CTRDGModuleInfo, at HW_CTRDG_MODULE_INFO_BUF (0x027ffc30). */
struct CTRDGModuleInfo {
    u16 moduleID;          /* 0x0 */
    u8 exLsiID[3];         /* 0x2 */
    u8 isAgbCartridge : 1; /* 0x5 */
    u8 detectPullOut : 1;
    u8 : 6;
    u8 pad6[2];
    u32 gameCode; /* 0x8 */
};

void CTRDGi_InitCommon(void) {
    u32 local = 0;
    CpuSet(&local, data_020a9de0, 0x5000001);
    *(u16 *)(data_020a9de0 + 2) = (u16)OS_GetLockID();
}

int CTRDG_IsExisting(void) {
    int lockInfo[2];
    int cycle[2];
    int ret = 1;
    CTRDGModuleInfo *cip = (CTRDGModuleInfo *)0x27ffc30;
    CTRDGHeader *chp = (CTRDGHeader *)HW_CTRDG_ROM;

    if (cip->moduleID == 0xffff)
        return 0;
    if (cip->detectPullOut == 1)
        return 0;

    CTRDGi_LockByProcessor(((u16 *)data_020a9de0)[1], lockInfo);
    CTRDGi_ChangeLatestAccessCycle(cycle);

    if ((chp->isRomCode == CTRDG_IS_ROM_CODE && cip->moduleID != chp->moduleID) ||
        (chp->isRomCode != CTRDG_IS_ROM_CODE && cip->moduleID != CTRDG_MODULE_ID_IMAGE) ||
        (cip->gameCode != chp->gameCode && cip->isAgbCartridge)) {
        ret = 0;
        cip->detectPullOut = 1;
    }

    CTRDGi_RestoreAccessCycle(cycle);
    CTRDGi_UnlockByProcessor(((u16 *)data_020a9de0)[1], lockInfo);
    return ret;
}

void CTRDGi_ChangeLatestAccessCycle(int *cycle) {
    cycle[0] = (*(volatile u16 *)0x4000204 & 0xc) >> 2;
    cycle[1] = (*(volatile u16 *)0x4000204 & 0x10) >> 4;
    *(volatile u16 *)0x4000204 = (*(volatile u16 *)0x4000204 & ~0xc) | 0xc;
    *(volatile u16 *)0x4000204 = *(volatile u16 *)0x4000204 & ~0x10;
}

void CTRDGi_RestoreAccessCycle(int *cycle) {
    volatile u16 *reg = (volatile u16 *)0x4000204;
    *reg = (cycle[0] << 2) | (*reg & ~0xc);
    *reg = (cycle[1] << 4) | (*reg & ~0x10);
}

void CTRDGi_LockByProcessor(u16 lockID, int *info) {
    for (;;) {
        info[1] = IRQ::Disable();
        info[0] = OS_ReadOwnerOfLockCartridge() & OS_MAINP_LOCKED_FLAG;
        if (info[0] != 0)
            return;
        if (OS_TryLockCartridge(lockID) == 0)
            return;
        IRQ::Restore(info[1]);
        WaitByLoop(1);
    }
}

void CTRDGi_UnlockByProcessor(u16 lockID, int *info) {
    if (info[0] == 0)
        OS_UnLockCartridge(lockID);
    IRQ::Restore(info[1]);
}

void CTRDGi_SendtoPxi(u32 data) {
    while (IPCSend(0xd, data, 0) != 0)
        WaitByLoop(1);
}
}
