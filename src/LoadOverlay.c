#include "types.h"
void func_02018c00(void *dst, int a, int id);
int func_0203d7b8(void);
struct Pair;
void FS_GetOverlayFileID(struct Pair *dst, char *src);
void Crash(void);
void FS_LoadOverlay(int a, int id);
/* A loaded-overlay slot (see func_02017e60.c): the overlay id, 0xffffffff
   when the slot is free, and the RAM range the overlay occupies. */
struct OverlaySlot {
    u32 id;
    u32 start;
    u32 size;
};
extern struct OverlaySlot data_0209d3c4[12];
struct Pair {
    int a;
    int b;
};
/* NitroSDK FSOverlayInfo: FS_LoadOverlayInfo (func_02018c00) copies the
   0x20-byte table header and stores the target processor at +0x20;
   FS_GetOverlayFileID reads header.file_id (+0x18). */
typedef struct FSOverlayInfoHeader {
    u32 id;
    u8 *ram_address;
    u32 ram_size;
    u32 bss_size;
    void *sinit_init;
    void *sinit_init_end;
    u32 file_id;
    u32 compressed : 24;
    u32 flag : 8;
} FSOverlayInfoHeader;
typedef struct FSOverlayInfo {
    FSOverlayInfoHeader header;
    u32 target;
} FSOverlayInfo;
typedef char FSOverlayInfo_size_must_be_0x24[sizeof(FSOverlayInfo) == 0x24 ? 1 : -1];
void LoadOverlay(int id) {
    u32 start;
    struct OverlaySlot *slot;
    u32 i;
    u32 total;
    struct Pair pair;
    FSOverlayInfo info;
    struct OverlaySlot *r;
    u32 end;
    func_02018c00(&info, 0, id);
    if (func_0203d7b8() != 0) {
        return;
    }
    FS_GetOverlayFileID(&pair, (char *)(&info));
    slot = 0;
    total = info.header.ram_size + info.header.bss_size;
    start = (u32)info.header.ram_address;
    end = start + total;
    for (r = data_0209d3c4, i = 0; i < 12; r++, i++) {
        if (r->id == 0xffffffff) {
            if (slot == 0) {
                slot = r;
            }
        } else if (((r->start + r->size) > start) && (end > r->start)) {
            Crash();
        }
    }

    if (slot != 0) {
        slot->id = id;
        slot->start = start;
        slot->size = total;
    }
    FS_LoadOverlay(0, id);
    func_0203d7b8();
}
