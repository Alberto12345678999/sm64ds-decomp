/* NitroSDK FSi_ExecuteSyncCommand(p_file): run the file's command through
 * FSi_TranslateCommand and release it with the result (FSi_ReleaseCommand),
 * start the archive's next queued command (FSi_NextCommand,
 * FSi_ExecuteAsyncCommand), and report whether the file's error is
 * FS_RESULT_SUCCESS (0). Only the FSFile fields read here are spelled out. */
typedef struct FSArchive FSArchive;

typedef struct FSFile FSFile;

struct FSFile {
    char pad_00[8];
    FSArchive *arc;    /* 0x08 */
    unsigned int stat; /* 0x0c */
    int command;       /* 0x10 */
    int error;         /* 0x14 */
};

extern int FSi_TranslateCommand(FSFile *p_file, int command);
extern void FSi_ReleaseCommand(FSFile *p_file, int ret);
extern FSFile *FSi_NextCommand(FSArchive *p_arc);
extern void FSi_ExecuteAsyncCommand(FSFile *p_file);

int FSi_ExecuteSyncCommand(FSFile *p_file) {
    FSFile *p_target;
    int ret = FSi_TranslateCommand(p_file, p_file->command);
    FSi_ReleaseCommand(p_file, ret);
    p_target = FSi_NextCommand(p_file->arc);
    if (p_target != 0)
        FSi_ExecuteAsyncCommand(p_target);
    return p_file->error == 0;
}
