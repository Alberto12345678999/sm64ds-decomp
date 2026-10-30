extern void func_0205dc0c(int a, int b);
extern void func_02018c00(void *rgn, int a, int b);
extern int func_0203d7b8(void);
extern void func_02017fd0(void *rgn);

/* A loaded-overlay slot (see func_02017e60.c). */
typedef struct Entry {
    int id;
    int start;
    int size;
} Entry;

extern Entry data_0209d3c4[];

/* UnloadOverlay for an overlay that may not be loaded: free its slot, and if
   it had one, unload ARM9 overlay `key` (func_0205dc0c, NitroSDK's
   FS_UnloadOverlay) and, unless func_0203d7b8 says otherwise, poison its
   RAM (func_02017fd0). Where UnloadOverlay crashes on an overlay with no
   slot, this returns. */
void func_02017e94(int key) {
    char rgn[0x28];
    Entry *found = 0;
    unsigned int i;
    for (i = 0; i < 0xc; i++) {
        Entry *e = &data_0209d3c4[i];
        if (e->id == key) {
            e->id = -1;
            e->start = 0;
            found = e;
            e->size = 0;
        }
    }
    if (found == 0)
        return;
    func_0205dc0c(0, key);
    func_02018c00(rgn, 0, key);
    if (func_0203d7b8() != 0)
        return;
    func_02017fd0(rgn);
}
