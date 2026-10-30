//cpp
#include "types.h"
#include "IRQ.h"

extern "C" {

/* NitroSDK FSArchive, the list links this function follows. */
typedef struct FSArchive {
    u32 name;               /* 0x00 -- the packed name */
    struct FSArchive *next; /* 0x04 */
} FSArchive;

extern FSArchive *data_020a8048;

u32 FSi_GetPackedName(const char *name, int name_len);

/* NitroSDK FS_archive.c FS_FindArchive: the registered archive whose packed
 * name matches name, walking the archive list data_020a8048 with interrupts
 * off; NULL if there is none. */
FSArchive *FS_FindArchive(const char *name, int name_len) {
    u32 pack = FSi_GetPackedName(name, name_len);
    u32 bak_psr = IRQ::Disable();
    FSArchive *p_arc = data_020a8048;
    while (p_arc != 0 && p_arc->name != pack) {
        p_arc = p_arc->next;
    }
    IRQ::Restore(bak_psr);
    return p_arc;
}
}
