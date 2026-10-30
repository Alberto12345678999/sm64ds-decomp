/* NitroSDK FS_archive.c FS_InitArchive: clear the 0x50-byte archive, then
 * empty its two thread queues, sync_q and stat_q. This SDK keeps a thread
 * queue as a 16-bit mask of thread ids, so emptying one is a store of 0
 * where pret's calls OS_InitThreadQueue. FSi_InitRom calls it first on the
 * ROM archive. */
extern void func_0205a588(void *dst, int value, int size);

/* NitroSDK FSArchive, as far as this function writes it. */
struct FSArchive {
    char pad_00[0xc];
    unsigned short sync_q; /* 0x0c */
    unsigned short stat_q; /* 0x0e */
};

void FS_InitArchive(struct FSArchive *p_arc) {
    func_0205a588(p_arc, 0, 0x50);
    p_arc->sync_q = 0;
    p_arc->stat_q = 0;
}
