/* NitroSDK's FSFileID: the archive and the file id inside it. */
struct FSFileID {
    int arc, file_id;
};
extern void myFS_ConvertPathToFileID(struct FSFileID *buf, int x);
extern void func_02018474(struct FSFileID p, int b, int c);

/* Read up to size bytes of the ROM file at path into dst (func_02018474).
   func_0203ad84 reads "/BUILDTIME" this way. */
void func_02018434(int path, int dst, int size) {
    struct FSFileID fileId;
    myFS_ConvertPathToFileID(&fileId, path);
    func_02018474(fileId, dst, size);
}
