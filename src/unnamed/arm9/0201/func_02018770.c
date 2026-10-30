#include "private/arm9_archive_table.h"

extern void UnloadArchive(int i);

/* Unload the archive a file lookup mounted for itself, if there is one
   (data_0208eb54 holds its index), then set the index to -1 (none). */
void func_02018770(void) {
    if (data_0208eb54 < 0) {
        return;
    }
    UnloadArchive(data_0208eb54);
    data_0208eb54 = -1;
}
