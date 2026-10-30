#include "private/arm9_a1fc0_file_share.h"

/* The two FSFile words of mFile that hold the open region's extent. */
typedef struct FileShareFileExtent {
    unsigned char pad_00[0x20];
    int top;    /* 0x20 */
    int bottom; /* 0x24 */
} FileShareFileExtent;

#define FILE_EXTENT(node) ((FileShareFileExtent *)(node)->mFile)

/* Find the ready node whose file covers [offset, offset + size); 0 if none.
   func_020412f0 serves an open request from it. */
FileShareNode *func_02041ce0(FileShareParentArea *area, int offset, int size) {
    FileShareNode *node = area->mReadyList;
    if (node == 0)
        return node;
    do {
        if (node->mState == 2 && offset == FILE_EXTENT(node)->top &&
            size == FILE_EXTENT(node)->bottom - FILE_EXTENT(node)->top)
            return node;
        node = node->mNext;
    } while (node != 0);
    return node;
}
