/* NitroSDK's FSFileID: the archive and the file id inside it. */
struct FSFileID {
    int arc, file_id;
};

extern void FS_InitFile(int *s);
extern int myFS_OpenFileFast(int buf, struct FSFileID ab);
extern void Crash(void);
extern int func_020184e0(int *buf, unsigned int c, unsigned int d);

/* Open the file whose FSFileID arrives as arc and fileId (func_02018434
   passes the struct by value), crash if it will not open, and read up to
   size bytes of it into dst (func_020184e0). */
int func_02018474(int arc, int fileId, int dst, int size, ...) {
    int file[0x11];
    FS_InitFile(file);
    if (myFS_OpenFileFast((int)file, *(struct FSFileID *)&arc) == 0) {
        Crash();
        return 0;
    }
    return func_020184e0(file, dst, size);
}
