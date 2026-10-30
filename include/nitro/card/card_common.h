#ifndef NITRO_CARD_COMMON_H
#define NITRO_CARD_COMMON_H

/*
 * The card access common routines, under the NitroSDK's own names. The
 * bodies are card_common.c, in src/engine/card/CARD_Common.cpp.
 *
 * CARDi_SetTask takes the task the card thread runs. CARDi_LockResource and
 * CARDi_UnlockResource are static in pret's card_common.c and only that file
 * calls them, so they are not declared here. Here they are global:
 * config/arm9/symbols.txt binds both globally, and a static definition fails
 * the intact-TU link check.
 *
 * The parameters are unnamed on purpose: a named parameter in a shared
 * declaration costs every including C++ file an @NNN number.
 */

#include "types.h"
#include "nitro/os/thread.h"

#ifdef __cplusplus
extern "C" {
#endif

struct CARDiCommon;
/* A card-thread task: CARDi_SetTask hands it cardi_common. */
typedef void (*CARDiTask)(struct CARDiCommon *);

/* NitroSDK CARDiCommon (cardi_common, data_020a8180), this SDK's layout.
 * pret's revision adds request-type, retry and mode fields. */
typedef struct CARDiCommon {
    int *cmd;                /* 0x00 -- the PXI command block; word 0 is the result */
    s32 command;             /* 0x04 */
    volatile int lock_owner; /* 0x08 -- OS_LOCK_ID_ERROR when free */
    volatile int lock_ref;   /* 0x0c */
    u16 lock_queue;          /* 0x10 -- OSThreadQueue */
    u16 pad12;               /* 0x12 */
    int lock_target;         /* 0x14 -- CARD_TARGET_* */
    u32 src;                 /* 0x18 */
    u32 dst;                 /* 0x1c */
    u32 len;                 /* 0x20 */
    u32 dma;                 /* 0x24 -- the DMA channel; ~0 for none */
    u32 callback;            /* 0x28 -- MIDmaCallback */
    u32 callback_arg;        /* 0x2c */
    CARDiTask task_func;     /* 0x30 */
    volatile u32 flag;       /* 0x34 -- CARD_STAT_* */
    int priority;            /* 0x38 */
    OSThread thread;         /* 0x3c -- the card task thread */
    OSThread *cur_th;        /* 0xd0 -- the thread the request runs on */
    u16 busy_q;              /* 0xd4 -- OSThreadQueue */
} CARDiCommon;

void CARDi_SetTask(CARDiTask);
void CARDi_InitCommon(void);
int CARDi_WaitAsync(void);
void CARD_LockRom(u16);
void CARD_UnlockRom(u16);
void CARD_LockBackup(u16);
void CARD_UnlockBackup(u16);

#ifdef __cplusplus
}
#endif

#endif /* NITRO_CARD_COMMON_H */
