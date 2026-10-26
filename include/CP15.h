#ifndef SM64DS_CP15_H
#define SM64DS_CP15_H

/* CP15 -- the ARM946E-S system-control coprocessor's cache maintenance
 * (Nitro SDK namespace, not a class), defined as asm in
 * src/engine/cp15/CP15.cpp. The (addr, size) forms act on the range
 * [addr, addr + size); the void forms act on the whole cache. Parameters stay
 * unnamed: a name here takes an @NNN in every includer. */
namespace CP15 {
void FlushDataCache(void);
void FlushAndInvalidateDataCache(void);
void InvalidateDataCache(unsigned int, unsigned int);
void FlushDataCache(unsigned int, unsigned int);
void FlushAndInvalidateDataCache(unsigned int, unsigned int);
void DrainWriteBuffer(void);
void InvalidateInstructionCache(unsigned int, unsigned int);
}

#endif
