/* NitroSDK FS_OpenFileDirect(p_file, p_arc, image_top, image_bottom,
 * file_index): store the archive and arg.openfiledirect, send
 * FS_COMMAND_OPENFILEDIRECT (7) through FSi_SendCommand, and
 * on success mark the handle FS_FILE_STATUS_IS_FILE (0x10), not
 * FS_FILE_STATUS_IS_DIR (0x20). Field names follow the SDK's FSFile, as
 * src/engine/fs/FS_CommandDefault.cpp spells it; only the fields this function touches are
 * spelled out. */
#include "types.h"

struct FSArchive;

typedef struct FSOpenFileDirectArg {
    u32 top;    /* 0x00 */
    u32 bottom; /* 0x04 */
    u32 index;  /* 0x08 */
} FSOpenFileDirectArg;

typedef struct FSFile FSFile;

struct FSFile {
    char pad_00[8];
    struct FSArchive *arc; /* 0x08 */
    int stat; /* 0x0c */
    char pad_10[0x1c];
    union {
        FSOpenFileDirectArg openfiledirect;
    } arg; /* 0x2c */
};

extern int FSi_SendCommand(FSFile *p_file, int command);

int FS_OpenFileDirect(char *self, struct FSArchive *p_arc, u32 image_top, u32 image_bottom,
                      u32 file_index) {
    FSFile *p_file = (FSFile *)self;
    int* p;
    p_file->arc = p_arc;
    p_file->arg.openfiledirect.index = file_index;
    p_file->arg.openfiledirect.top = image_top;
    p_file->arg.openfiledirect.bottom = image_bottom;
    if (FSi_SendCommand(p_file, 7) == 0)
        return 0;
    p = &p_file->stat;
    *p |= 0x10;
    *p &= ~0x20;
    return 1;
}
