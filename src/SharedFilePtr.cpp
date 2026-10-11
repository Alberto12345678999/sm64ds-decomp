//cpp
/* arm9/SharedFilePtr -- the shared-file handle and its loader block at .text
 * 0x020178e4..0x02017e0c, folded from twenty-two legacy shards. mwccarm emits
 * .text in reverse source order, so the definitions below run ROM-descending:
 *
 *   SharedFilePtr::Load      0x02017c54
 *   func_02017c24            0x02017c24  (extern "C", frees filePtr)
 *   SharedFilePtr::LoadFile  0x02017bc4
 *   SharedFilePtr::Release   0x02017b64
 *   func_02017b4c            0x02017b4c  (extern "C", fileID rides through r1)
 *   SharedFilePtr_Destruct_Clsn / Destruct_TexSeq / Destruct_Anim /
 *   SharedFilePtr_Construct_TexSeq / func_020179b4 .. func_02017ae4
 *                          0x020178e4..0x02017b34  (extern "C" helpers)
 *   SharedFilePtr::Construct / ReallocateModelFile
 *                          0x0201799c / 0x02017a8c
 *   TextureSequence::LoadFile / dExtFrameCtrl_c::LoadFile /
 *   Model::LoadFile / dBgW_Kc::LoadFile
 *                          0x020178e4 / 0x0201794c / 0x02017a3c / 0x02017afc
 *                          (other-system members, kept under their mangled
 *                          names per the original file's layout)
 *
 * Fields: +0x0 u16 fileID, +0x2 u8 numRefs, +0x4 void *filePtr (the layout
 * src/_ZN13SharedFilePtr4LoadEv.cpp already used). Release/LoadFile keep the
 * raw-offset bodies they matched with. include/SharedFilePtr.h stays fieldless
 * on purpose; the TU-local shadow below is what the member definitions use.
 */
#include "types.h"
#include "TextureSequence.h"
#include "dExtFrameCtrl_c.h"
#include "Model.h"
#include "dBgW_Kc.h"

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
void *func_02017e34(void *c);
unsigned int func_02017060(void *ptr);
}

struct SharedFilePtr {
    unsigned short fileID;
    unsigned char numRefs;
    void *filePtr;

    void Release();
    void *LoadFile();
    void *Load();
    SharedFilePtr &Construct(unsigned int fileID);
    unsigned int ReallocateModelFile();
};

#ifndef SM64DS_PLATFORM_PC
/* The host port does not compile this body: Load is the card seam, and
   port/hal/fs.cpp supplies its own SharedFilePtr::Load member over the
   host file system. */
// @symbol _ZN13SharedFilePtr4LoadEv
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

// @symbol func_02017c24
extern "C" void func_02017c24(SharedFilePtr *self)
{
    data_0209d3bc = self->fileID;
    _ZN6Memory10DeallocateEPv(self->filePtr);
    self->filePtr = 0;
}

// @symbol _ZN13SharedFilePtr8LoadFileEv
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

// @symbol _ZN13SharedFilePtr7ReleaseEv
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
// @symbol func_02017b4c
extern "C" void *func_02017b4c(void *self, unsigned int fileID)
{
    func_02017e48(self, fileID);
    return self;
}
#endif

#ifndef SM64DS_PLATFORM_PC
/* The destructor variants all run the release helper at 0x02017e34, which
   stashes fileID and hands the handle back. func_02017e34 is DS-only: the HAL
   provides the same seams through SharedFilePtr members. */
// @symbol SharedFilePtr_Destruct_Clsn
extern "C" void *SharedFilePtr_Destruct_Clsn(void *x)
{
    func_02017e34(x);
    return x;
}
#endif

/* dBgW_Kc::LoadFile(SharedFilePtr&) at 0x02017afc -- static.
 * Loads the KCL collision file through the shared handle; on the first
 * reference patches its internal offsets, then returns the file pointer. */
// @symbol _ZN7dBgW_Kc8LoadFileER13SharedFilePtr
char *dBgW_Kc::LoadFile(SharedFilePtr &ptr)
{
    u8 refs;
    char *file;

    ptr.LoadFile();
    refs = ptr.numRefs;
    file = (char *)ptr.filePtr;
    if (refs == 1 && file != 0) {
        UpdateFileOffsets(*(KCL_File *)file);
    }
    return file;
}

#ifndef SM64DS_PLATFORM_PC
/* func_02017ae4 .. func_02017ab4 -- the fileID ride-through construct variants
   and one more destructor variant. The fileID rides through r1 untouched;
   returns self. func_02017e48 / func_02017e34 are DS-only, and the HAL
   provides the ABI-portable Construct instead. */
// @symbol func_02017ae4
extern "C" void *func_02017ae4(void *self, unsigned int fileID)
{
    func_02017e48(self, fileID);
    return self;
}

// @symbol func_02017acc
extern "C" void *func_02017acc(void *self, unsigned int fileID)
{
    func_02017e48(self, fileID);
    return self;
}

// @symbol func_02017ab4
extern "C" int func_02017ab4(int x)
{
    func_02017e34((void *)x);
    return x;
}

// @symbol func_02017a9c
extern "C" int func_02017a9c(int x)
{
    func_02017e34((void *)x);
    return x;
}

/* SharedFilePtr::ReallocateModelFile() at 0x02017a8c.
 * Reallocates the loaded file to its own reported size through func_02017060,
   DS-only; the host supplies the same member from gx_upload_bridge.cpp. */
// @symbol _ZN13SharedFilePtr19ReallocateModelFileEv
unsigned int SharedFilePtr::ReallocateModelFile()
{
    return func_02017060(filePtr);
}
#endif

/* Model::LoadFile(SharedFilePtr&) at 0x02017a3c -- static.
 * Loads a BMD model through the shared handle; on the first reference patches
 * its internal offsets, registers it in the common model data array and
 * shrinks the allocation to the file's real size. */
// @symbol _ZN5Model8LoadFileER13SharedFilePtr
void *Model::LoadFile(SharedFilePtr &ptr)
{
    void *filePtr;
    ptr.LoadFile();
    filePtr = ptr.filePtr;
    if (ptr.numRefs == 1 && filePtr != 0) {
        UpdateFileOffsets(*(BMD_File *)filePtr);
        AddToCommonModelDataArr(*(BMD_File *)filePtr);
        ptr.ReallocateModelFile();
    }
    return filePtr;
}

#ifndef SM64DS_PLATFORM_PC
// @symbol func_02017a24
extern "C" void *func_02017a24(void *self, unsigned int fileID)
{
    func_02017ae4(self, fileID);
    return self;
}

// @symbol func_02017a0c
extern "C" int func_02017a0c(int x)
{
    func_02017a9c(x);
    return x;
}

/* func_020179b4 at 0x020179b4 -- loads a BMD through the shared handle and
   hands it to a ModelBase. On SetFile failure it releases the handle's
   reference and reports failure. */
// @symbol func_020179b4
extern "C" int func_020179b4(SharedFilePtr *r0, ModelBase *r1, int r2)
{
    ModelBase *model = r1;
    SharedFilePtr *filePtr = r0;
    int extra = r2;
    int result = 0;
    BMD_File *file;
    if (!model) goto done;
    file = (BMD_File *)Model::LoadFile(*filePtr);
    if (!file) goto done;
    result = model->SetFile(file, extra, -1);
    if (!result) {
        filePtr->Release();
    }
done:
    return result;
}

/* SharedFilePtr::Construct(unsigned int) at 0x0201799c.
 * Forwards to the init helper at 0x02017e48 and hands the handle back so the
 * caller can chain. The HAL provides the ABI-portable member instead. */
// @symbol _ZN13SharedFilePtr9ConstructEj
SharedFilePtr &SharedFilePtr::Construct(unsigned int fileID)
{
    func_02017e48(this, fileID);
    return *this;
}

// @symbol SharedFilePtr_Destruct_Anim
extern "C" void *SharedFilePtr_Destruct_Anim(void *x)
{
    func_02017e34(x);
    return x;
}
#endif

/* dExtFrameCtrl_c::LoadFile(SharedFilePtr&) at 0x0201794c -- static.
 * Loads a BCA animation through the shared handle; on the first reference
 * patches its internal offsets, then returns the file pointer. */
// @symbol _ZN15dExtFrameCtrl_c8LoadFileER13SharedFilePtr
char *dExtFrameCtrl_c::LoadFile(SharedFilePtr &ptr)
{
    u8 refs;
    char *file;

    ptr.LoadFile();
    refs = ptr.numRefs;
    file = (char *)ptr.filePtr;
    if (refs == 1 && file != 0) {
        UpdateFileOffsets(*(BCA_File *)file);
    }
    return file;
}

#ifndef SM64DS_PLATFORM_PC
// @symbol SharedFilePtr_Construct_TexSeq
extern "C" void *SharedFilePtr_Construct_TexSeq(void *self, unsigned int fileID)
{
    func_02017e48(self, fileID);
    return self;
}

// @symbol SharedFilePtr_Destruct_TexSeq
extern "C" void *SharedFilePtr_Destruct_TexSeq(void *x)
{
    func_02017e34(x);
    return x;
}
#endif

/* TextureSequence::LoadFile(SharedFilePtr&) at 0x020178e4 -- static.
 * Loads a BTP texture animation through the shared handle; on the first
 * reference patches its internal offsets, then returns the file pointer. */
// @symbol _ZN15TextureSequence8LoadFileER13SharedFilePtr
void *TextureSequence::LoadFile(SharedFilePtr &ptr)
{
    void *filePtr;
    ptr.LoadFile();
    filePtr = ptr.filePtr;
    if (ptr.numRefs == 1 && filePtr != 0) {
        UpdateFileOffsets(*(BTP_File *)filePtr);
    }
    return filePtr;
}

