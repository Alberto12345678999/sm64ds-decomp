#include "nitro/fs/overlay.h"
/* NitroSDK FS_LoadOverlayImage: open the overlay's file by its file_id,
 * clear the overlay's RAM image (FS_ClearOverlayImage), read
 * the whole file to ram_address (myFS_ReadFile), then pass the target
 * processor, RAM address, ROM offset and RAM size to func_0206d32c.
 *
 * FSFile follows src/engine/fs/FS_CommandDefault.cpp's view (prop.file at 0x1c), padded to
 * the SDK's 0x48. */
typedef struct FSFileProp {
    unsigned own_id; /* 0x00 */
    unsigned top;    /* 0x04 */
    unsigned bottom; /* 0x08 */
    unsigned pos;    /* 0x0c */
} FSFileProp;

typedef struct FSFile {
    char pad_00[0x1c];
    FSFileProp prop; /* 0x1c -- prop.file */
    char pad_2c[0x1c];
} FSFile;

typedef char FSFile_size_must_be_0x48[sizeof(FSFile) == 0x48 ? 1 : -1];

typedef struct Pair {
    int a;
    int b;
} Pair;

extern void FS_InitFile(void *s);
extern Pair FS_GetOverlayFileID(const FSOverlayInfo *p_ovi);
extern int myFS_OpenFileFast(void *a, Pair bc);
extern void FS_ClearOverlayImage(FSOverlayInfo *p_ovi);
extern int myFS_ReadFile(void *a, int b, int c);
extern int func_0206d32c(int target, unsigned int ramAddress, unsigned int romOffset,
                         unsigned int ramSize);
extern int FS_CloseFile(void *self);

int func_02018b64(FSOverlayInfo *ovi) {
    FSFile file;
    Pair fileId;

    FS_InitFile(&file);
    fileId = FS_GetOverlayFileID(ovi);
    if (myFS_OpenFileFast(&file, fileId) == 0)
        return 0;

    FS_ClearOverlayImage(ovi);
    myFS_ReadFile(&file, (int)ovi->header.ram_address, file.prop.bottom - file.prop.top);

    {
        int ramSize = ovi->header.ram_size;
        int romOffset = file.prop.top;
        int ramAddress = (int)ovi->header.ram_address;
        /* the plain `ovi->target != 0` changes the .text bytes */
        int flag = (int)((ovi->target == 0) ? (char *)0 : (char *)1);
        func_0206d32c(flag, ramAddress, romOffset, ramSize);
    }

    FS_CloseFile(&file);
    return 1;
}
