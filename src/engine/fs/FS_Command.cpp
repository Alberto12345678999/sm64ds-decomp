//cpp
/* The file system's command dispatch (the Nitro SDK's fs_command.c),
 * arm9 .text 0x0205c5e4..0x0205c7c4.
 *
 * FSi_TranslateCommand runs one command for a file. The archive's proc gets
 * the command first when proc_flag has its bit; the default table
 * fsi_default_command (src/engine/fs/FS_CommandDefault.cpp) runs it when proc
 * leaves it to the default. FSi_ReleaseCommand takes a finished file off its
 * archive's list and wakes anyone waiting on it. pret's pokediamond
 * FS_command.c defines the same two functions in the same order; mwccarm
 * emits them in reverse, so FSi_TranslateCommand sits lower in the ROM.
 *
 * This SDK is older than pret's: FSi_ReleaseCommand takes no interrupt lock
 * and clears only BUSY|CANCEL|SYNC|ASYNC (0xf; pret's mask also covers
 * its OPERATING bit), and the thread queues are 16-bit masks of thread ids.
 */
#include "types.h"
#include "IRQ.h"
#include "nitro/os/thread.h"

extern "C" {

#define FS_FILE_STATUS_SYNC 0x00000004
#define FS_FILE_STATUS_COMMAND_MASK 0x0000000f /* BUSY | CANCEL | SYNC | ASYNC */

#define FS_ARCHIVE_FLAG_IS_ASYNC 0x00000100
#define FS_ARCHIVE_FLAG_IS_SYNC 0x00000200

#define FS_RESULT_SUCCESS 0
#define FS_RESULT_FAILURE 1
#define FS_RESULT_UNSUPPORTED 4
#define FS_RESULT_PROC_ASYNC 6
#define FS_RESULT_PROC_DEFAULT 7
#define FS_RESULT_PROC_UNKNOWN 8

typedef struct FSArchive FSArchive;
typedef struct FSFile FSFile;

typedef int (*FS_ARCHIVE_PROC_FUNC)(FSFile *p_file, int command);

/* NitroSDK FSFile, this SDK's layout, as far as this file reads it. */
struct FSFile {
    FSFile *prev;   /* 0x00 -- link.prev */
    FSFile *next;   /* 0x04 -- link.next */
    FSArchive *arc; /* 0x08 */
    u32 stat;       /* 0x0c */
    int command;    /* 0x10 */
    int error;      /* 0x14 */
    u16 queue;      /* 0x18 -- OSThreadQueue: a synchronous caller sleeps here */
};

/* NitroSDK FSArchive, this SDK's layout, as far as this file reads it. */
struct FSArchive {
    char pad_00[0xc];
    u16 sync_q; /* 0x0c -- OSThreadQueue: a synchronous caller waits here */
    u16 stat_q; /* 0x0e */
    u32 flag;   /* 0x10 */
    char pad_14[0x34];
    FS_ARCHIVE_PROC_FUNC proc; /* 0x48 */
    u32 proc_flag;             /* 0x4c -- which commands go to proc */
};

typedef char FSArchive_size_must_be_0x50[sizeof(FSArchive) == 0x50 ? 1 : -1];

extern int (*fsi_default_command[])(FSFile *p_file);

void FSi_CutFromList(FSFile *elem);

// @symbol FSi_ReleaseCommand
void FSi_ReleaseCommand(FSFile *p_file, int ret) {
    FSi_CutFromList(p_file);
    p_file->stat &= ~FS_FILE_STATUS_COMMAND_MASK;
    p_file->error = ret;
    OS_WakeupThread(&p_file->queue);
}

// @symbol FSi_TranslateCommand
int FSi_TranslateCommand(FSFile *p_file, int command) {
    FSArchive *p_arc;
    u32 stat;
    int ret;
    int bit;
    u32 irq;
    int sync;
    int busy;

    /* sync/sync_mode/busy stay materialized 0/1 locals: testing the bit
       directly, != 0, or an inline predicate each shrinks the function
       (0x188-0x19c) */

    stat = p_file->stat;
    sync = 1;
    p_arc = p_file->arc;
    bit = 1 << command;
    if ((stat & FS_FILE_STATUS_SYNC) == 0)
        sync = 0;

    if (sync) {
        p_arc->flag |= FS_ARCHIVE_FLAG_IS_SYNC;
    } else {
        p_arc->flag |= FS_ARCHIVE_FLAG_IS_ASYNC;
    }

    if (p_arc->proc_flag & bit) {
        ret = p_arc->proc(p_file, command);
        switch (ret) {
        case FS_RESULT_SUCCESS:
        case FS_RESULT_FAILURE:
        case FS_RESULT_UNSUPPORTED:
            p_file->error = ret;
            break;
        case FS_RESULT_PROC_UNKNOWN:
            p_arc->proc_flag &= ~bit;
            ret = FS_RESULT_PROC_DEFAULT;
            break;
        }
    } else {
        ret = FS_RESULT_PROC_DEFAULT;
    }

    if (ret == FS_RESULT_PROC_DEFAULT)
        ret = fsi_default_command[command](p_file);

    if (ret == FS_RESULT_PROC_ASYNC) {
        int sync_mode = (p_file->stat & FS_FILE_STATUS_SYNC) ? 1 : 0;
        if (sync_mode != 0) {
            u16 *queue;
            irq = IRQ::Disable();
            queue = &p_arc->sync_q;
            while ((busy = (p_arc->flag & FS_ARCHIVE_FLAG_IS_SYNC) ? 1 : 0) != 0)
                OS_SleepThread(queue);
            ret = p_file->error;
            IRQ::Restore(irq);
        }
    } else {
        int sync_mode = (p_file->stat & FS_FILE_STATUS_SYNC) ? 1 : 0;
        if (sync_mode == 0) {
            p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_ASYNC;
            FSi_ReleaseCommand(p_file, ret);
        } else {
            p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_SYNC;
            p_file->error = ret;
        }
    }

    return ret;
}
}
