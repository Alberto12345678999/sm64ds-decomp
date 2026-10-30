//cpp
/* NitroSDK FS_archive.c FS_ReleaseArchiveName: undo
 * FS_RegisterArchiveName. A named archive is unlinked from the archive list
 * with interrupts off; its packed name and links are cleared, as is
 * FS_ARCHIVE_FLAG_REGISTER (1). If it was the current directory's archive,
 * the current directory moves to the root of the list head
 * (data_020a8048). */
#include "types.h"
#include "IRQ.h"

extern "C" {

/* NitroSDK FSArchive, as far as this function touches it. */
typedef struct FSArchive {
    u32 name;               /* 0x00 -- the packed name, 0 when unnamed */
    struct FSArchive *next; /* 0x04 */
    struct FSArchive *prev; /* 0x08 */
    u32 pad_0c;
    u32 flag; /* 0x10 */
} FSArchive;

/* NitroSDK FSDirPos, the current directory. */
typedef struct FSDirPos {
    FSArchive *arc; /* 0x00 */
    u16 own_id;     /* 0x04 */
    u16 index;      /* 0x06 */
    u32 pos;        /* 0x08 */
} FSDirPos;

extern FSDirPos data_020a804c;
extern FSArchive *data_020a8048;

void FS_ReleaseArchiveName(FSArchive *p_arc) {
    u32 enabled;
    FSArchive *link;

    if (p_arc->name == 0)
        return;
    enabled = IRQ::Disable();
    link = p_arc->next;
    if (link)
        link->prev = p_arc->prev;
    link = p_arc->prev;
    if (link)
        link->next = p_arc->next;
    p_arc->name = 0;
    p_arc->prev = 0;
    p_arc->next = p_arc->prev;
    p_arc->flag &= ~1u;
    if (data_020a804c.arc == p_arc) {
        data_020a804c.pos = 0;
        data_020a804c.index = 0;
        data_020a804c.arc = data_020a8048;
        data_020a804c.own_id = 0;
    }
    IRQ::Restore(enabled);
}
}
