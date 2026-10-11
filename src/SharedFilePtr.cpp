//cpp
/* arm9/SharedFilePtr -- the shared-file handle's load/release band at .text
 * 0x02017b4c..0x02017e0c, folded from five legacy shards. mwccarm emits .text
 * in reverse source order, so the definitions below run ROM-descending:
 *
 *   SharedFilePtr::Load      0x02017c54
 *   func_02017c24            0x02017c24  (extern "C", frees filePtr)
 *   SharedFilePtr::LoadFile  0x02017bc4
 *   SharedFilePtr::Release   0x02017b64
 *   func_02017b4c            0x02017b4c  (extern "C", fileID rides through r1)
 *
 * Fields: +0x0 u16 fileID, +0x2 u8 numRefs, +0x4 void *filePtr (the layout
 * src/_ZN13SharedFilePtr4LoadEv.cpp already used). Release/LoadFile keep the
 * raw-offset bodies they matched with.
 */

struct Obj { char pad[0x20]; unsigned int cur; unsigned int end; char pad2[0x1c]; };

extern "C" {
extern int data_0209d3bc;

int func_020186c0(unsigned int val);
int func_02018568(int a);
unsigned int func_02018ac4(unsigned int *p);
int _ZN6Memory8AllocateEj(unsigned int size);
void DecompressLZ16(void *src, void *dst);
void func_020185c0(void *buf, unsigned int x);
void FS_CloseFile(void *a);
int _ZN6Memory8AllocateEji(unsigned int size, int align);
void CpuCopy8(void *a, void *b, unsigned int c);
void func_02018770(void);
void _ZN4CP1514FlushDataCacheEjj(unsigned int a, unsigned int b);
void Crash(void);
void _ZN4CP1527FlushAndInvalidateDataCacheEjj(unsigned int a, unsigned int b);
int func_02018d48(void *a, void *b, unsigned int c);
void _ZN6Memory10DeallocateEPv(void *p);
void *func_02017e48(void *self, unsigned int fileID);
}

struct SharedFilePtr {
    unsigned short fileID;
    unsigned char numRefs;
    void *filePtr;

    void Release();
    void *LoadFile();
    void *Load();
};

#ifndef SM64DS_PLATFORM_PC
/* The host port does not compile this body: Load is the card seam, and
   port/hal/fs.cpp supplies its own SharedFilePtr::Load member over the
   host file system. */
void *SharedFilePtr::Load()
{
    data_0209d3bc = fileID;
    int p = func_020186c0(fileID);
    if (p != 0) {
        unsigned int size;
        int mem;
        if (func_02018568(p)) {
            unsigned int *q = (unsigned int *)(p + 4);
            size = func_02018ac4(q);
            mem = _ZN6Memory8AllocateEj(size);
            DecompressLZ16(q, (void *)mem);
        } else {
            struct Obj obj;
            func_020185c0(&obj, fileID);
            size = obj.end - obj.cur;
            FS_CloseFile(&obj);
            mem = _ZN6Memory8AllocateEji(size, 0x20);
            CpuCopy8((void *)p, (void *)mem, size);
        }
        func_02018770();
        _ZN4CP1514FlushDataCacheEjj((unsigned int)mem, size);
        filePtr = (void *)mem;
        return filePtr;
    }

    struct Obj obj2;
    void *cp;
    unsigned int csize;
    int raw;
    int fsize;

    func_020185c0(&obj2, fileID);
    fsize = obj2.end - obj2.cur;
    if (fsize <= 8)
        Crash();
    raw = _ZN6Memory8AllocateEji(fsize, 0x20);
    _ZN4CP1527FlushAndInvalidateDataCacheEjj((unsigned int)raw, fsize);
    int r = func_02018d48(&obj2, (void *)raw, fsize);
    if (r != fsize)
        return 0;
    FS_CloseFile(&obj2);
    func_02018770();
    if (func_02018568(raw) != 0) {
        unsigned int t;
        cp = (void *)(raw + 4);
        t = func_02018ac4((unsigned int *)cp);
        csize = fsize - 4;
        fsize = t;
        int tmp = _ZN6Memory8AllocateEj(csize);
        CpuCopy8(cp, (void *)tmp, csize);
        _ZN6Memory10DeallocateEPv((void *)raw);
        raw = _ZN6Memory8AllocateEj(fsize);
        DecompressLZ16((void *)tmp, (void *)raw);
        _ZN6Memory10DeallocateEPv((void *)tmp);
    }
    _ZN4CP1514FlushDataCacheEjj((unsigned int)raw, fsize);
    filePtr = (void *)raw;
    return filePtr;
}
#endif

extern "C" void func_02017c24(SharedFilePtr *self)
{
    data_0209d3bc = self->fileID;
    _ZN6Memory10DeallocateEPv(self->filePtr);
    self->filePtr = 0;
}

void *SharedFilePtr::LoadFile()
{
    char *self = (char *)this;

    data_0209d3bc = *(unsigned short *)self;

    if (*(unsigned char *)(self + 2) == 0) {
        if (!Load())
            return 0;
    }

    if (*(unsigned char *)(self + 2) >= 0xff) {
        return 0;
    }

    *(unsigned char *)(self + 2) += 1;
    return *(void **)(self + 4);
}

void SharedFilePtr::Release()
{
    char *self = (char *)this;

    data_0209d3bc = *(unsigned short *)self;

    if (*(unsigned char *)(self + 2) == 0)
        return;

    *(unsigned char *)(self + 2) -= 1;

    if (*(unsigned char *)(self + 2) != 0)
        return;

    func_02017c24(this);
}

#ifndef SM64DS_PLATFORM_PC
/* fileID rides through r1 untouched; returns self. The host port never
   provides func_02017e48 -- the ride-through Construct variants are
   DS-only, and the HAL's Construct path goes through func_02017e0c. */
extern "C" void *func_02017b4c(void *self, unsigned int fileID)
{
    func_02017e48(self, fileID);
    return self;
}
#endif
