#ifndef NITRO_CTRDG_COMMON_H
#define NITRO_CTRDG_COMMON_H

/*
 * The cartridge-slot common routines, under the NitroSDK's own names. The
 * bodies are ctrdg_common.c, in src/engine/ctrdg/CTRDG_Common.cpp.
 *
 * The SDK's CTRDGLockByProc {locked, irq} and CTRDGRomCycle {c1, c2} records
 * are two words each, which every caller keeps in an int array, so they are
 * int * here.
 *
 * The parameters are unnamed on purpose: a named parameter in a shared
 * declaration costs every including C++ file an @NNN number.
 */

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void CTRDGi_InitCommon(void);
int CTRDG_IsExisting(void);
void CTRDGi_ChangeLatestAccessCycle(int *);
void CTRDGi_RestoreAccessCycle(int *);
void CTRDGi_LockByProcessor(u16, int *);
void CTRDGi_UnlockByProcessor(u16, int *);
void CTRDGi_SendtoPxi(u32);

#ifdef __cplusplus
}
#endif

#endif /* NITRO_CTRDG_COMMON_H */
