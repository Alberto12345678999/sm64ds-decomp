//cpp
/* NitroSDK fs_archive.c FSi_SendCommand(p_file, command): record the command,
 * FS_RESULT_BUSY (2) and FS_FILE_STATUS_BUSY (1). An archive that is
 * unloading (FS_ARCHIVE_FLAG_UNLOADING 0x80) releases the file as
 * FS_RESULT_CANCELED (3). Otherwise a synchronous command (the commands in
 * 0x1fc) gets FS_FILE_STATUS_SYNC (4), the file is appended to the archive's
 * command list, and an idle archive is marked running
 * (FS_ARCHIVE_FLAG_RUNNING 0x10, FS_COMMAND_ACTIVATE 9 to proc when proc_flag
 * asks for it). An asynchronous command starts at once or waits its turn; a
 * synchronous one sleeps on the file's queue until it heads the list, then
 * runs through FSi_ExecuteSyncCommand. Only the fields read here are spelled
 * out. */
#include "types.h"
#include "IRQ.h"

extern "C" {

typedef struct FSArchive FSArchive;
typedef struct FSFile FSFile;

typedef int (*FS_ARCHIVE_PROC_FUNC)(FSFile *p_file, int command);

/* NitroSDK FSFile, this SDK's layout, as far as this file reads it. */
struct FSFile {
    char pad_00[8];
    FSArchive *arc; /* 0x08 */
    u32 stat;       /* 0x0c */
    int command;    /* 0x10 */
    int error;      /* 0x14 */
    u16 queue;      /* 0x18 -- the thread queue a synchronous caller sleeps on */
};

/* NitroSDK FSArchive, this SDK's layout, as far as this file reads it. */
struct FSArchive {
    char pad_00[0x10];
    u32 flag; /* 0x10 */
    struct {
        FSFile *prev; /* 0x14 */
        FSFile *next; /* 0x18 -- the command list's head */
    } list;
    char pad_1c[0x2c];
    FS_ARCHIVE_PROC_FUNC proc; /* 0x48 */
    u32 proc_flag;             /* 0x4c -- which commands go to proc */
};

extern void FSi_ReleaseCommand(FSFile *p_file, int ret);
extern void FSi_AppendToList(FSFile *elem, FSFile *list);
extern void FSi_ExecuteAsyncCommand(FSFile *p_file);
extern void OS_SleepThread(u16 *queue);
extern int FSi_ExecuteSyncCommand(FSFile *p_file);

/* The ROM materialises each of these flag tests as 0/1 before branching on it. */
static inline int HasBits(u32 word, u32 bits) {
    return (word & bits) != 0;
}

#pragma opt_loop_invariants off
int FSi_SendCommand(FSFile *p_file, int command) {
    FSArchive *p_arc = p_file->arc;
    u32 bit = 1 << command;
    u32 saved;

    p_file->command = command;
    p_file->error = 2;
    p_file->stat |= 1;
    saved = IRQ::Disable();
    if (p_arc->flag & 0x80) {
        FSi_ReleaseCommand(p_file, 3);
        IRQ::Restore(saved);
        return 0;
    }
    if (bit & 0x1fc) {
        p_file->stat |= 4;
    }
    FSi_AppendToList(p_file, (FSFile *)&p_arc->list);
    if (!HasBits(p_arc->flag, 0x10)) {
        p_arc->flag |= 0x10;
        IRQ::Restore(saved);
        if (p_arc->proc_flag & 0x200) {
            p_arc->proc(p_file, 9);
        }
        if (!HasBits(p_file->stat, 4)) {
            FSi_ExecuteAsyncCommand(p_file);
            return 1;
        }
    } else {
        if (!HasBits(p_file->stat, 4)) {
            IRQ::Restore(saved);
            return 1;
        }
        do {
            OS_SleepThread(&p_file->queue);
        } while (p_file != p_arc->list.next);
        IRQ::Restore(saved);
    }
    return FSi_ExecuteSyncCommand(p_file);
}
}
