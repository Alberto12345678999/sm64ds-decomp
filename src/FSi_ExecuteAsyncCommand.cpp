//cpp
/* NitroSDK fs_archive.c FSi_ExecuteAsyncCommand(p_file): run the archive's
 * queued commands one after another. A synchronous file (FS_FILE_STATUS_SYNC
 * 4) is woken to run itself; otherwise the file is marked asynchronous (FS_FILE_STATUS_ASYNC 8) and
 * its command translated, stopping when the archive answers
 * FS_RESULT_PROC_ASYNC (6), and FSi_NextCommand gives the next file. Only the
 * FSFile fields read here are spelled out. */
#include "types.h"
#include "IRQ.h"
#include "nitro/os/thread.h"

typedef struct FSArchive FSArchive;
typedef struct FSFile FSFile;

struct FSFile {
    char pad_00[8];
    FSArchive *arc; /* 0x08 */
    u32 stat;       /* 0x0c */
    int command;    /* 0x10 */
    int error;      /* 0x14 */
    u16 queue;      /* 0x18 -- the thread queue a synchronous caller sleeps on */
};

extern "C" {

extern int FSi_TranslateCommand(FSFile *p_file, int command);
extern FSFile *FSi_NextCommand(FSArchive *p_arc);

void FSi_ExecuteAsyncCommand(FSFile *p_file) {
    FSArchive *p_arc = p_file->arc;
    if (p_file == 0)
        return;
    do {
        u32 saved = IRQ::Disable();
        int sync = (int)((p_file->stat & 4) != 0);
        if (sync != 0) {
            OS_WakeupThread(&p_file->queue);
            return;
        }
        p_file->stat |= 8;
        IRQ::Restore(saved);
        if (FSi_TranslateCommand(p_file, p_file->command) == 6)
            return;
        p_file = FSi_NextCommand(p_arc);
    } while (p_file != 0);
}
}
