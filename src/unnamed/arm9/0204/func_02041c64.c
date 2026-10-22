#include "private/arm9_a1fc0_file_share.h"
struct ListNode;
extern struct ListNode *func_02041b60(char *base);
extern void func_020423c8(void);

/* The parent's node for a child's request (offset, length): a loading node
 * already holding that extent, or a fresh one off the free list
 * (func_02041b60) with the extent stored and the loader thread woken
 * (func_020423c8). */
struct ListNode *func_02041c64(char *base, int a, int b)
{
    FileShareNode *node;
    node = ((FileShareParentArea *)base)->mBusyList;
    while (node != 0) {
        if (node->mState == 1 && node->mFileOffset == a && node->mFileSize == b) {
            break;
        }
        node = node->mNext;
    }
    if (node == 0) {
        node = (FileShareNode *)func_02041b60(base);
        node->mRefCount = 0;
        node->mFileOffset = a;
        node->mFileSize = b;
        func_020423c8();
    }
    return (struct ListNode *)node;
}
