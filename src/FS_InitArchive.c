/* NitroSDK FS_archive.c FS_InitArchive: clear the 0x50-byte archive, then
 * zero the two halfwords at +0x0c and +0x0e. pret's later revision zeroes
 * its two thread queues at this point instead; this one has the older
 * layout. FSi_InitRom calls it first on the ROM archive. */
extern void func_0205a588(void *dst, int value, int size);

/* NitroSDK FSArchive, as far as this function writes it. */
struct FSArchive {
    char pad_00[0xc];
    short hc; /* 0x0c */
    short he; /* 0x0e */
};

void FS_InitArchive(struct FSArchive *p_arc) {
    func_0205a588(p_arc, 0, 0x50);
    p_arc->hc = 0;
    p_arc->he = 0;
}
