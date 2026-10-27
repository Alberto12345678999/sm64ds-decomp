#ifndef SM64DS_MATH_CALCLIB_H
#define SM64DS_MATH_CALCLIB_H

#include "common.h"

/* The arm9 scalar and vector helpers that sit just ahead of the matrix
 * library (see math/MtxStack.h): the byte timer at 0x0203add4, the linear and
 * angle steppers at 0x0203adec..0x0203b000, and the Vector3 distance/angle
 * helpers at 0x0203b770..0x0203d170. One run of the ROM, most likely one
 * library file, in the place EAD's GameCube code keeps cLib_calcTimer,
 * cLib_chaseS, cLib_addCalcAngleS2 and cLib_targetAngleY.
 *
 * Parameter types follow each DEFINITION in src/. Parameters stay unnamed: a
 * name here takes an @NNN in every includer.
 *
 * Only the helpers d_a_mky.cpp calls are declared so far. Vec3_Asr is not:
 * its definition takes a file-local struct Vec3, so no spelling here agrees
 * with it yet. The C++ steppers (UpdateAngle, ApproachLinear) are in
 * math/Approach.h. */
#include "math/Approach.h"

extern "C" {

/* Decrement *p unless it is already 0; return the new value. */
unsigned char DecIfAbove0_Byte(unsigned char *);

short Vec3_HorzAngle(const Vector3 *, const Vector3 *);
int Vec3_Dist(const Vector3 *, const Vector3 *);
int Vec3_HorzDist(const Vector3 *, const Vector3 *);
}

#endif
