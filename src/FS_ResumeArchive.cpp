//cpp
/* NitroSDK FS_archive.c FS_ResumeArchive: if the archive is suspended
 * (FS_ARCHIVE_FLAG_SUSPEND, 8), clear the flag and pick up its next command
 * (FSi_NextCommand), all with interrupts off; once they are
 * restored, run a command that came back (FSi_ExecuteAsyncCommand). Returns whether
 * the archive was not suspended. */
#include "IRQ.h"

extern "C" {

enum Bool { FALSE, TRUE };

typedef struct FSFile FSFile;

/* NitroSDK FSArchive, the field touched here (FSi_NextCommand.cpp's name). */
typedef struct FSArchive FSArchive;

struct FSArchive {
    char pad_00[0x10];
    int flag; /* 0x10 */
};

extern FSFile *FSi_NextCommand(FSArchive *p_arc);
extern void FSi_ExecuteAsyncCommand(FSFile *p_file);

int FS_ResumeArchive(FSArchive *p_arc) {
    FSFile *p_file = 0;
    unsigned int enabled;
    enum Bool suspended;
    enum Bool running;

    enabled = IRQ::Disable();
    suspended = (enum Bool)((p_arc->flag & 8) != 0);
    running = (enum Bool)(suspended == FALSE);
    if (running == FALSE) {
        p_arc->flag &= ~8;
        p_file = FSi_NextCommand(p_arc);
    }
    IRQ::Restore(enabled);
    if (p_file != 0)
        FSi_ExecuteAsyncCommand(p_file);
    return running;
}
}
