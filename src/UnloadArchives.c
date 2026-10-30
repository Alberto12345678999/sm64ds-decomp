#include "private/arm9_archive_table.h"

extern void func_02018908(void *archive, void *heap);

/* Unload every mounted archive. Unlike UnloadArchive it leaves heap set. */
void UnloadArchives(void) {
    unsigned int i;
    ArchiveTableEntry *p = data_0208ecf4;
    for (i = 0; i < ARCHIVE_TABLE_COUNT; i++) {
        if (p->archive != 0) {
            func_02018908(p->archive, p->heap);
            p->archive = 0;
        }
        p++;
    }
}
