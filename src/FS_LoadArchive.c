/* NitroSDK FS_archive.c FS_LoadArchive: point a registered archive at its
 * data. base is the offset reads add, fat/fat_size and fnt/fnt_size the two
 * tables (each also kept in a _bak copy), and read_func/write_func the media callbacks, defaulting to the
 * memory ones (func_0205d2dc, func_0205d2b0). Table reads go through
 * read_func, no table memory is loaded yet, and the archive is marked
 * FS_ARCHIVE_FLAG_LOADED (2). Always TRUE. */
extern void func_0205d2dc(void);
extern void func_0205d2b0(void);

int FS_LoadArchive(int *p_arc, int base, int fat, int fat_size, int fnt, int fnt_size,
                   int read_func, int write_func) {
    p_arc[7] = base;                                            /* 0x1c base */
    p_arc[9] = fat_size;                                        /* 0x24 fat_size */
    p_arc[0xc] = fat;                                           /* 0x30 fat_bak */
    p_arc[8] = p_arc[0xc];                                      /* 0x20 fat */
    p_arc[0xb] = fnt_size;                                      /* 0x2c fnt_size */
    p_arc[0xd] = fnt;                                           /* 0x34 fnt_bak */
    p_arc[0xa] = p_arc[0xd];                                    /* 0x28 fnt */
    p_arc[0xf] = read_func ? read_func : (int)func_0205d2dc;    /* 0x3c */
    p_arc[0x10] = write_func ? write_func : (int)func_0205d2b0; /* 0x40 */
    p_arc[0x11] = p_arc[0xf];                                   /* 0x44 table_func */
    p_arc[0xe] = 0;                                             /* 0x38 load_mem */
    p_arc[4] |= 2;                                              /* 0x10 flag */
    return 1;
}
