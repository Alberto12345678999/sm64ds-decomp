/* NitroSDK's FSFileID: the archive and the file id inside it. */
struct FSFileID {
    int arc, file_id;
};
extern int myFS_ConvertPathToFileID(void *out_file_id, const char *path);
extern int func_02018474(struct FSFileID fileId, int dst, int size);

/* Read up to size bytes of the ROM file at path into dst (func_02018474).
   func_0203ad84 reads "/BUILDTIME" this way. */
void func_02018434(const char *path, int dst, int size) {
    struct FSFileID fileId;
    myFS_ConvertPathToFileID(&fileId, path);
    func_02018474(fileId, dst, size);
}
