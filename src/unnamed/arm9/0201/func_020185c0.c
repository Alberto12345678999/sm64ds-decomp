#include "private/arm9_archive_table.h"

struct P {
    int a;
    int b;
};

extern void FS_InitFile(int *s);
extern void func_02018598(struct P *c, unsigned int arg);
extern int myFS_OpenFileFast(int a, struct P v);
extern int LoadArchive(int idx);
extern void Crash(void);
extern int func_0204eda4(int r0, char *a, unsigned int idx);

/* Open game file id a1 into the FSFile at a0. Ids below 0x8000 are FAT ids
   in the ROM archive (func_02018598 builds the FSFileID); higher ids are
   opened inside the archive whose range holds them, mounting it first if
   needed (and recording it in data_0208eb54). Any failure is fatal. */
int func_020185c0(int a0, unsigned int a1) {
    int result = 0;

    FS_InitFile((int *)a0);

    if (a1 < 0x8000) {
        struct P arg;
        struct P v;
        func_02018598(&v, a1);
        arg.a = v.a;
        arg.b = v.b;
        result = myFS_OpenFileFast(a0, arg);
    } else {
        unsigned int i = 0;
        ArchiveTableEntry *e = data_0208ecf4;
        do {
            if (e->firstFileId <= a1 && a1 < e->endFileId) {
                if (e->archive == 0) {
                    if (LoadArchive(i) != 0)
                        data_0208eb54 = i;
                    if (e->archive == 0) {
                        Crash();
                        return 0;
                    }
                }
                result = func_0204eda4(a0, e->archive, a1 - e->firstFileId);
                break;
            }
            i++;
            e++;
        } while (i < ARCHIVE_TABLE_COUNT);
    }

    if (result == 0)
        Crash();
    return result;
}
