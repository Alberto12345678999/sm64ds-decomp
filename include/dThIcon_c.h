#ifndef DTHICON_C_H
#define DTHICON_C_H

#include "types.h"

/* Polymorphic touch-screen icon base. RTTI proves the dThIcon_c name and the
 * inheritance edge used by dMgPsOpt_c::TouchIcon_c. Its 0x24-byte extent is
 * fixed by each derived icon's constructor/destructor and array stride. */
struct dThIcon_c {
    u8 pad_004[0x20];

    dThIcon_c() {}
    virtual ~dThIcon_c() {}
};

typedef char dThIcon_c_size_must_be_0x24[
    sizeof(dThIcon_c) == 0x24 ? 1 : -1];

#endif
