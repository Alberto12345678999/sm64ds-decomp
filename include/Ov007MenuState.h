#ifndef OV007_MENU_STATE_H
#define OV007_MENU_STATE_H

#include "types.h"

/* Reconstructed layout and name, not recovered class identity. The four
 * controller helpers and their menu callers agree on this 16-byte record. */
typedef struct Ov007MenuState {
    s16 currentState;
    s16 requestedState; /* -1: no pending request */
    s32 stateWork;      /* caller-owned phase/flags, cleared on state entry */
    s16 lastTickState;
    s16 previousState; /* reset seeds initialState - 1 */
    u32 stateTicks;    /* saturates; some effect callers also seed this */
} Ov007MenuState;

typedef char Ov007MenuState_size_must_be_16[sizeof(Ov007MenuState) == 16 ? 1 : -1];

#endif
