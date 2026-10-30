struct V2 {
    int x, y;
};

extern void FS_InitFile(int *s);
extern int myFS_OpenFileFast(int buf, struct V2 ab);
extern void Crash(void);
extern int func_0201834c(int *buf, int x);
extern int myFS_ConvertPathToFileID(void *out_file_id, const char *path);

/* Load the file an FSFileID names (see func_0201834c); c nonzero flushes
   the result from the data cache. */
int func_020182ec(struct V2 file, int c, ...) {
    int buf[0x11];
    int r = 0;
    FS_InitFile(buf);
    if (myFS_OpenFileFast((int)buf, file) == 0)
        Crash();
    else
        r = func_0201834c(buf, c);
    return r;
}

/* Load the ROM file at path into a new heap block, decompressed if it is
   LZ77-tagged, and flush it from the data cache (Ov004_LoadFileByPath). */
void *func_020182bc(const char *path) {
    struct V2 file;
    myFS_ConvertPathToFileID(&file, path);
    return (void *)func_020182ec(file, 1);
}
