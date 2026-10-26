#include "types.h"
/* recovered: shared common types */
#include "common.h"

struct dActor_c {
    unsigned char pad0[0x80];
    Vector3 scale; /* @0x80 */
};

typedef short s16;

typedef int s32;

struct dCamera_c {
    char pad[0x8c];
    struct Vector3 vec; // 0x8c
};

struct dCamera_c;

struct Vector3_16;

struct dActor_c;

extern s16 ReadUnalignedShort(const void *from); // 0x0200e768

int func_02008500(struct dActor_c *actor, const char *data) {
    Fix12i x, y, z;
    z = ReadUnalignedShort(data + 4) << 12;
    y = ReadUnalignedShort(data + 2) << 12;
    x = ReadUnalignedShort(data) << 12;
    actor->scale.x = x;
    actor->scale.y = y;
    actor->scale.z = z;
    return 1;
}

// func_020084b0 @ 0x020084b0 - dCamera_c/dActor_c member, size 0x50.
// Reads a packed unaligned Vector3_16 (x,y,z s16) from a data record,
// converts each component to Fix12i (<<12) and stores them as a Vector3
// at offset 0x8c of the target object. Returns 1.
// @symbol func_020084b0

s32 func_020084b0(struct dCamera_c *self, const unsigned char *data, int a, int b) {
    s32 y, z, x;
    z = ReadUnalignedShort(data + 4) << 12;
    y = ReadUnalignedShort(data + 2) << 12;
    x = ReadUnalignedShort(data) << 12;
    self->vec.x = x;
    self->vec.y = y;
    self->vec.z = z;
    return 1;
}

int func_02008474(struct dCamera_c *self, struct Vector3_16 *v, int a, int b) {
    func_02008500((struct dActor_c *)self, (const char *)v);
    return func_020084b0(self, (const unsigned char *)((const unsigned char *)v + 6), a, b);
}
