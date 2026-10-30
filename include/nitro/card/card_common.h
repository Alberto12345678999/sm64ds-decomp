#ifndef NITRO_CARD_COMMON_H
#define NITRO_CARD_COMMON_H

/*
 * The card access common routines, under the NitroSDK's own names. The
 * bodies are card_common.c, in src/engine/card/CARD_Common.cpp.
 *
 * CARDi_LockResource / CARDi_UnlockResource take the lock ID as the owner
 * and a target: 1 the ROM, 2 the backup memory. CARDi_SetTask takes the task
 * the card thread runs.
 *
 * The parameters are unnamed on purpose: a named parameter in a shared
 * declaration costs every including C++ file an @NNN number.
 */

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void CARDi_SetTask(void *);
void CARDi_LockResource(int, int);
void CARDi_UnlockResource(int, int);
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
