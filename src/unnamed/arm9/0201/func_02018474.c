/* NitroSDK's FSFileID: the archive and the file id inside it. */
struct V2 {
    int x, y;
};

extern void FS_InitFile(int *s);
extern int myFS_OpenFileFast(int buf, struct V2 ab);
extern void Crash(void);
extern int func_020184e0(int *buf, unsigned int c, unsigned int d);

/* Open the file whose FSFileID arrives as a and b (func_02018434 passes the
   struct by value), crash if it will not open, and read up to d bytes of it
   into c (func_020184e0). */
int func_02018474(int a, int b, int c, int d, ...) {
    int buf[0x11];
    FS_InitFile(buf);
    if (myFS_OpenFileFast((int)buf, *(struct V2 *)&a) == 0) {
        Crash();
        return 0;
    }
    return func_020184e0(buf, c, d);
}
