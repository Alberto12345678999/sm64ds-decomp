/* NitroSDK's FSFileID: the archive and the file id inside it. */
struct P {
    int arc, file_id;
};
/* the ROM archive, as func_020189f0 last saw it resolve a path */
extern int data_0209d3b4;

/* Build the FSFileID for FAT file id arg in the ROM archive. */
void func_02018598(struct P *c, int arg) {
    struct P t;
    t.file_id = arg;
    t.arc = data_0209d3b4;
    *c = t;
}
