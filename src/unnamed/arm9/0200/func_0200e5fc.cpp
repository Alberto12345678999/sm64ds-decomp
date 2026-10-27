//cpp
#include "common.h"
#include "SaveData.h"
#include "dActor_c.h"

extern "C" {

extern int data_0209b284[];
extern u8 data_0209f2d8;
extern u8 data_0209b270;

void* func_0200e5fc(u32 idx) {
    int flag;
    int b;
    void* res;
    volatile u8* pb;
    if (data_0209b284[idx] != 0) return 0;
    flag = 0x11;
    b = (data_0209f2d8 == 2) ? 1 : 0;
    if ((int)(((long long)b)) != 0) {
        if (SaveData::IsCharacterUnlocked(idx) == 0)
            return 0;
        flag = 0;
    }
    res = dActor_c::Spawn(0xbf, idx | (idx << 3) | (data_0209b270 << 6) | (flag << 8),
                          *(const Vector3 *)0, (const Vector3_16 *)0, -1, -1);
    if (res == 0) return res;
    pb = &data_0209b270;
    ((volatile int*)data_0209b284)[idx] = *((int*)res + 1);
    *pb += 1;
    return res;
}
}
