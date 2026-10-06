/* GXS -- sub-screen VRAM upload helpers (Nitro SDK namespace, not a class).
 * Owns .text 0x02055dec..0x02055fb4: the extended-palette banked upload
 * family (EndLoadOBJExtPltt .. BeginLoadBGExtPltt). Below sits G3i's TU
 * ending at 0x02055dec; above is func_02055fb4.
 *
 * Each old shard re-declared the shared globals and DMA callees privately;
 * they are unified here. SetBankForSub*ExtPltt keep deliberately wide u32
 * extern "C" spellings (local extern): declaring them with their real u16
 * parameters makes mwccarm emit narrowing shifts at the call site.
 */

#include "types.h"

/* GX sub-screen extended palette VRAM bases */
#define GXS_OBJ_EXT_PLTT_BASE 0x068a0000u
#define GXS_BG_EXT_PLTT_BASE  0x06898000u

extern u32 data_02099fd0;
extern u32 data_020a60a4;
extern u32 data_020a60a8;

extern "C" {
extern u16 func_020540f0(void);
extern u16 func_02054118(void);
extern void func_02059fa8(int ch);
extern void func_02059fd0(int ch, int src, int dst, u32 size, void (*cb)(int), int cbarg);
extern void MultiCopy_Int(int *dst, int *src, int len);
// local extern: u16 parameter per the definition inserts narrowing shifts at the call
extern void _ZN2GX22SetBankForSubBGExtPlttEt(u32 bank);
extern void _ZN2GX23SetBankForSubOBJExtPlttEt(u32 bank);
}

namespace GXS {

// @symbol _ZN3GXS18BeginLoadBGExtPlttEv
void BeginLoadBGExtPltt()
{
    data_020a60a4 = func_02054118();
}

// @symbol _ZN3GXS13LoadBGExtPlttEPKvjj
void LoadBGExtPltt(const void* src, u32 destSlotAddr, u32 size){
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fd0(dmaId, (int)src, (int)(destSlotAddr + GXS_BG_EXT_PLTT_BASE), size, 0, 0);
    } else {
        MultiCopy_Int((int*)src, (int*)(destSlotAddr + GXS_BG_EXT_PLTT_BASE), size);
    }
}

// @symbol _ZN3GXS16EndLoadBGExtPlttEv
void EndLoadBGExtPltt(){
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fa8(dmaId);
    }
    _ZN2GX22SetBankForSubBGExtPlttEt(data_020a60a4);
    data_020a60a4 = 0;
}

// @symbol _ZN3GXS19BeginLoadOBJExtPlttEv
void BeginLoadOBJExtPltt()
{
    data_020a60a8 = func_020540f0();
}

// @symbol _ZN3GXS14LoadOBJExtPlttEPKvjj
void LoadOBJExtPltt(const void* src, u32 destSlotAddr, u32 size){
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fd0(dmaId, (int)src, (int)(destSlotAddr + GXS_OBJ_EXT_PLTT_BASE), size, 0, 0);
    } else {
        MultiCopy_Int((int*)src, (int*)(destSlotAddr + GXS_OBJ_EXT_PLTT_BASE), size);
    }
}

// @symbol _ZN3GXS17EndLoadOBJExtPlttEv
void EndLoadOBJExtPltt(){
    u32 dmaId = data_02099fd0;
    if (dmaId != (u32)-1) {
        func_02059fa8(dmaId);
    }
    _ZN2GX23SetBankForSubOBJExtPlttEt(data_020a60a8);
    data_020a60a8 = 0;
}

}
