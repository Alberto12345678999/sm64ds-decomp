#ifndef DAOBJUKIYUKA_C_H
#define DAOBJUKIYUKA_C_H

#include "types.h"
#include "Platform.h"

/* daObjUkiyuka_c -- an intermediate the ROM's RTTI names and the tree did not.
 *
 *     Actor -> Platform -> daObjUkiyuka_c -> FloatingFloorLllSmall  (daObjFl_Ukiyuka_c)
 *                                         -> FloatingFloorBfs       (daObjKm2_Ukishima_c)
 *
 * type_info 0x02109104 (ov002), vtable 0x0210912c (ov002).
 *
 * ukiyuka = 浮き床, a floating floor, and slot 6 of its own vtable is exactly
 * that: a platform that bobs on a trig table and pauses when it passes its rest
 * height. func_ov002_020b6494 reads all four fields below and nothing else
 * above 0x320 --
 *
 *     if (DecIfAbove0_Short(&mDwellTimer)) return;      // paused this frame
 *     mPhase += 0x100;                                  // one step round the table
 *     mPosY  -= (mAmplitude * data_02082214[(mPhase >> 4) * 2]) >> 12;
 *     if (mPosY - mRestPosY == 0) mDwellTimer = 0x3c;   // rest for 60 frames
 *
 * -- so mRestPosY is the height it settles back to, mAmplitude scales the table,
 * mPhase is the angle, and mDwellTimer is the pause. The names are read off that
 * arithmetic; the offsets and widths are the measurement.
 *
 * SIZE 0x32c, AND THE TWO CHILDREN DISAGREEING IS WHAT PROVES IT. They allocate
 * different literals -- FloatingFloorBfs 812 = 0x32c, FloatingFloorLllSmall
 * 816 = 0x330 -- which read for a while as a contradiction blocking this class.
 * It is the opposite. A base's size is fixed, so the SMALLER child bounds it from
 * above, and 0x32c is also exactly where mDwellTimer ends. The two meet with
 * nothing left over, so the base is 0x32c with no tail padding and the extra word
 * in the larger child is that child's own -- a u8 at 0x32c, see
 * include/FloatingFloorLllSmall.h. Two children that agreed on one literal could
 * not have separated the base from its tail this cleanly.
 *
 * DESTRUCTOR IS INLINE, like Platform's above it: neither child's destructor
 * contains a `bl` to this one. The out-of-line pair at 0x020b63e0 (D1) and
 * 0x020b6388 (D0) exists because slots 16/17 of the table need an address.
 */

struct daObjUkiyuka_c : Platform {
    u8  pad_31e[0x2];          /* Platform's tail padding, reused */
    s32 mRestPosY;             /* 0x320 */
    s32 mAmplitude;            /* 0x324 */
    s16 mPhase;                /* 0x328 */
    u16 mDwellTimer;           /* 0x32a */

    virtual ~daObjUkiyuka_c() {}
};

typedef char daObjUkiyuka_c_size_must_be_0x32c[sizeof(daObjUkiyuka_c) == 0x32c ? 1 : -1];

#endif
