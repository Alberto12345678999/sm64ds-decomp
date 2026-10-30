//cpp
/* NitroSDK FS_archive.c FS_ResumeArchive: if the archive is suspended
 * (FS_ARCHIVE_FLAG_SUSPEND, 8), clear the flag and pick up its next command
 * (FSi_NextCommand), all with interrupts off; once they are
 * restored, run a command that came back (FSi_ExecuteAsyncCommand). Returns whether
 * the archive was not suspended. */
#include "IRQ.h"

extern "C" {

enum Bool { FALSE, TRUE };

extern void *FSi_NextCommand(void *p_arc);
extern void FSi_ExecuteAsyncCommand(void *p_cmd);

/* NitroSDK FSArchive, the field touched here (FSi_NextCommand.cpp's name). */
typedef struct FSArchive {
    char pad_00[0x10];
    int flag; /* 0x10 */
} FSArchive;

int FS_ResumeArchive(FSArchive *p_arc) {
    void *p_cmd = 0;
    unsigned int enabled;
    enum Bool suspended;
    enum Bool running;

    enabled = IRQ::Disable();
    suspended = (enum Bool)((p_arc->flag & 8) != 0);
    running = (enum Bool)(suspended == FALSE);
    if (running == FALSE) {
        p_arc->flag &= ~8;
        p_cmd = FSi_NextCommand(p_arc);
    }
    IRQ::Restore(enabled);
    if (p_cmd != 0)
        FSi_ExecuteAsyncCommand(p_cmd);
    return running;
}
}
