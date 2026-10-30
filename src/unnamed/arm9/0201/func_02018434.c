/* NitroSDK's FSFileID: the archive and the file id inside it. */
struct P {
    int a, b;
};
extern void myFS_ConvertPathToFileID(struct P *buf, int x);
extern void func_02018474(struct P p, int b, int c);

/* Read up to a2 bytes of the ROM file at path a0 into a1 (func_02018474).
   func_0203ad84 reads "/BUILDTIME" this way. */
void func_02018434(int a0, int a1, int a2) {
    struct P buf;
    myFS_ConvertPathToFileID(&buf, a0);
    func_02018474(buf, a1, a2);
}
