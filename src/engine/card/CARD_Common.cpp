//cpp
/* Card access common code (the Nitro SDK's card_common.c),
 * arm9 .text 0x0205ff70..0x020602bc.
 *
 * pret/pokediamond's NitroSDK CARD_common.c has these nine functions in this
 * order: CARDi_SetTask, CARDi_LockResource, CARDi_UnlockResource,
 * CARDi_InitCommon, CARDi_WaitAsync, CARD_LockRom, CARD_UnlockRom,
 * CARD_LockBackup, CARD_UnlockBackup. The rest of that file (CARD_IsEnabled,
 * CARD_CheckEnabled, CARD_Enable, CARDi_TryWaitAsync, CARD_GetResultCode) is
 * not in this ROM.
 *
 * mwccarm defers C bodies and emits them in reverse, so the ROM runs
 * bottom-up: CARD_UnlockBackup at 0x0205ff70, CARDi_SetTask at 0x02060228.
 *
 * This SDK is older than pret's. CARDiCommon is smaller (no request type,
 * retry or mode fields), CARDi_InitCommon has no multiboot-child checks and
 * never calls CARD_Enable, and CARDi_SetTask resolves the relative priorities
 * 0x20 / 0x21 against the calling thread.
 */
#include "types.h"
#include "IRQ.h"
#include "CP15.h"
#include "nitro/card/card_common.h"
#include "nitro/os/spinLock.h"

extern "C" {

/* local extern: no header declares these yet. Their SDK names: Crash is
 * OS_Terminate, PXI_SetFifoRecvCallback, MultiStore32Bytes
 * MIi_CpuClearFast, func_020602bc CARDi_TaskThread and func_02060310
 * CARDi_OnFifoRecv. */
extern void Crash(void);
extern void OS_SleepThread(void *queue);
extern void OS_WakeupThread(void *queue);
extern u32 OS_GetThreadPriority(void *thread);
extern int OS_SetThreadPriority(void *thread, u32 priority);
extern void OS_WakeupThreadDirect(void *thread);
extern void OS_CreateThread(void *thread, void *func, void *arg, void *stack, u32 stackSize,
                            u32 priority);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern void MultiStore32Bytes(unsigned val, int *dst, int len);
extern void func_020602bc(void);
extern void func_02060310(int tag, int data, int err);

/* OSi_ThreadInfo; word 2 is the current thread. */
extern int data_020a6134[];

#define OS_LOCK_ID_ERROR (-3)
#define CARD_TARGET_NONE 0
#define CARD_TARGET_ROM 1
#define CARD_TARGET_BACKUP 2
#define CARD_STAT_BUSY 0x4
#define CARD_STAT_TASK 0x8
#define CARD_THREAD_PRIORITY_DEFAULT 4
/* Relative priorities: one step above / below the calling thread. */
#define CARD_THREAD_PRIORITY_HIGHER 0x20
#define CARD_THREAD_PRIORITY_LOWER 0x21

extern CARDiCommon data_020a8180; /* cardi_common */
extern int data_020a8160[];       /* cardi_arg, 0x20 bytes */
/* The word just past cardi_thread_stack (0x400 bytes): its address is the
 * stack's top. */
extern int *data_020a8760;

// @symbol CARDi_SetTask
void CARDi_SetTask(void (*task)(CARDiCommon *)) {
    CARDiCommon *const p = &data_020a8180;
    u32 priority = p->priority;
    switch (priority) {
    case CARD_THREAD_PRIORITY_HIGHER:
        priority = OS_GetThreadPriority((int *)data_020a6134[2]);
        if (priority != 0)
            priority -= 1;
        break;
    case CARD_THREAD_PRIORITY_LOWER:
        priority = OS_GetThreadPriority((int *)data_020a6134[2]);
        if (priority < 0x1f)
            priority += 1;
        break;
    }
    OS_SetThreadPriority(p->thread, priority);
    p->cur_th = p->thread;
    p->task_func = task;
    p->flag |= CARD_STAT_TASK;
    OS_WakeupThreadDirect(p->thread);
}

// @symbol CARDi_LockResource
void CARDi_LockResource(int owner, int target) {
    CARDiCommon *const p = &data_020a8180;
    unsigned int saved = IRQ::Disable();
    if (p->lock_owner == owner) {
        if (p->lock_target != target)
            Crash();
    } else {
        while (p->lock_owner != OS_LOCK_ID_ERROR)
            OS_SleepThread(&p->lock_queue);
        p->lock_owner = owner;
        p->lock_target = target;
    }
    ++p->lock_ref;
    *p->cmd = 0;
    IRQ::Restore(saved);
}

// @symbol CARDi_UnlockResource
void CARDi_UnlockResource(int owner, int target) {
    CARDiCommon *p = &data_020a8180;
    unsigned int saved = IRQ::Disable();
    if (p->lock_owner != owner || !p->lock_ref) {
        Crash();
    } else {
        if (p->lock_target != target)
            Crash();
        if (!--p->lock_ref) {
            p->lock_owner = OS_LOCK_ID_ERROR;
            p->lock_target = CARD_TARGET_NONE;
            OS_WakeupThread(&p->lock_queue);
        }
    }
    *p->cmd = 0;
    IRQ::Restore(saved);
}

// @symbol CARDi_InitCommon
void CARDi_InitCommon(void) {
    CARDiCommon *p = &data_020a8180;
    p->lock_owner = OS_LOCK_ID_ERROR;
    p->lock_ref = 0;
    p->lock_target = CARD_TARGET_NONE;
    p->cmd = data_020a8160;
    {
        /* MI_CpuFillFast's value: the ROM passes it through a stack slot. */
        volatile u32 fill = 0;
        MultiStore32Bytes(fill, data_020a8160, 0x20);
    }
    CP15::FlushAndInvalidateDataCache((unsigned int)data_020a8160, 0x20);
    p->lock_queue = 0;
    p->busy_q = 0;
    p->priority = CARD_THREAD_PRIORITY_DEFAULT;
    OS_CreateThread(p->thread, (void *)func_020602bc, 0, &data_020a8760, 0x400, p->priority);
    OS_WakeupThreadDirect(p->thread);
    PXI_SetFifoRecvCallback(0xb, (void *)func_02060310);
}

// @symbol CARDi_WaitAsync
int CARDi_WaitAsync(void) {
    CARDiCommon *const p = &data_020a8180;
    unsigned int saved = IRQ::Disable();
    while (p->flag & CARD_STAT_BUSY)
        OS_SleepThread(&p->busy_q);
    IRQ::Restore(saved);
    return *p->cmd == 0;
}

// @symbol CARD_LockRom
void CARD_LockRom(u16 lockID) {
    CARDi_LockResource(lockID, CARD_TARGET_ROM);
    OS_TryLockCard(lockID);
}

// @symbol CARD_UnlockRom
void CARD_UnlockRom(u16 lockID) {
    OS_UnlockCard(lockID);
    CARDi_UnlockResource(lockID, CARD_TARGET_ROM);
}

// @symbol CARD_LockBackup
void CARD_LockBackup(u16 lockID) {
    CARDi_LockResource(lockID, CARD_TARGET_BACKUP);
}

// @symbol CARD_UnlockBackup
void CARD_UnlockBackup(u16 lockID) {
    CARDi_UnlockResource(lockID, CARD_TARGET_BACKUP);
}
}
