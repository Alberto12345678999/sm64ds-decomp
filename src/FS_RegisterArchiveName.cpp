//cpp
/* NitroSDK FS_archive.c FS_RegisterArchiveName, an older revision than
 * pret's (it sets no FS_ARCHIVE_FLAG_REGISTER): with interrupts off, unless
 * an archive called name is already registered (FS_FindArchive,
 * func_0205d23c), append p_arc to the archive list data_020a8048 (the first
 * one also becomes the current directory, data_020a804c) and store its
 * packed name (FSi_GetPackedName, func_0205d304). TRUE if it was
 * registered. FSi_InitRom registers the ROM archive as "rom" with it. */
#include "IRQ.h"

extern "C" {

extern void *func_0205d23c(void *a, int b);
extern void *func_0205d304(void *a, void *b);

/* NitroSDK FSArchive, the list links this function writes. */
typedef struct FSArchive {
    void *name;             /* 0x00 -- the packed name */
    struct FSArchive *next; /* 0x04 */
    struct FSArchive *prev; /* 0x08 */
} FSArchive;

extern FSArchive *data_020a8048;

/* NitroSDK FSDirPos, the current directory. */
typedef struct FSDirPos {
    FSArchive *arc; /* 0x00 */
    short own_id;   /* 0x04 */
    short index;    /* 0x06 */
    int pos;        /* 0x08 */
} FSDirPos;

extern FSDirPos data_020a804c;

int FS_RegisterArchiveName(FSArchive *p_arc, void *name, void *name_len) {
    unsigned int enabled;
    int ret = 0;

    enabled = IRQ::Disable();

    if (func_0205d23c(name, (int)name_len) == 0) {
        if (data_020a8048 == 0) {
            data_020a8048 = p_arc;
            data_020a804c.arc = p_arc;
            data_020a804c.pos = 0;
            data_020a804c.index = 0;
            data_020a804c.own_id = 0;
        } else {
            FSArchive *tail = data_020a8048;
            while (tail->next != 0)
                tail = tail->next;
            tail->next = p_arc;
            p_arc->prev = tail;
        }
        p_arc->name = func_0205d304(name, name_len);
        ret = 1;
    }

    IRQ::Restore(enabled);
    return ret;
}
}
