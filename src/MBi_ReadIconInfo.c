extern void FS_InitFile(int *s);
extern int func_0205d518(int *s, int a);
extern void FS_CloseFile(int *s);
extern void FS_ReadFile(int *s, int a, int b);

/* NitroSDK MBi_ReadIconInfo (mb_gameinfo.c): read one icon file into a
   game record (MBi_MakeGameInfo): with flag set,
   0x200 bytes of character data to dst + 0x20; otherwise 0x20 bytes of
   palette to dst. Opens path with FS_InitFile and func_0205d518, and fails
   (0) on a null path, a failed open, or a file whose length (bottom - top,
   words 9 and 8 of the FSFile) is not exactly that size. Newer SDKs open
   with FS_OpenFileEx(file, path, FS_FILEMODE_R); this one takes the
   two-argument open func_0205d518. */
int MBi_ReadIconInfo(int a, int b, int flag) {
    int local[0x12];
    int sz;
    int param;

    sz = flag ? 0x200 : 0x20;
    if (flag)
        b += 0x20;

    if (a == 0)
        return 0;

    FS_InitFile(local);

    if (func_0205d518(local, a) == 0)
        return 0;

    param = local[9] - local[8];
    if (sz != param) {
        FS_CloseFile(local);
        return 0;
    }

    FS_ReadFile(local, b, sz);
    FS_CloseFile(local);
    return 1;
}
