//cpp
#include "types.h"

struct Heap {
    char pad0[4];
    int field4;      /* 0x4 */
    int field8;      /* 0x8 */
    int MaxAllocationUnitSize();
    static void RestoreFromTemporary();
    void _Destroy();
    void ResizeToFit();
    static Heap *InitializeSolidHeapAsDefault(u32, Heap *, int);
};

struct Memory {
    static void *Allocate(u32, int, Heap *);
};

struct ActorBase {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual int  v15();
    void MarkForDestruction();
    int Virtual34(u32 a, u32 b);

    char pad[0x48];
    Heap *heap_4c;   /* 0x4c */
};

int ActorBase::Virtual34(u32 a, u32 b)
{
    Heap* h = 0;
    u32 avail;

    if (this->heap_4c != 0)
        return 1;

    if (a != 0) {
        h = Heap::InitializeSolidHeapAsDefault(a, (Heap*)b, 0x20);
        if (h != 0) {
            u32 flagA = h->field4 & 0x10;
            if (flagA != 0)
                Memory::Allocate(0x10, 4, 0);
            int res = this->v15();
            u32 okA;
            if (flagA != 0) {
                okA = (u32)res;
            } else {
                void* allocRes = Memory::Allocate(0x10, 4, 0);
                okA = (allocRes != 0) ? (u32)res : 0;
            }
            Heap::RestoreFromTemporary();
            if (okA == 0) {
                h->_Destroy();
                h = 0;
            } else {
                u32 topA = h->field8;
                avail = topA - h->MaxAllocationUnitSize();
                avail = (avail + 0x1f) & ~0x1f;
                if (a == avail) {
                    h->ResizeToFit();
                    this->heap_4c = h;
                    return 1;
                }
            }
        }
    }

    if (h == 0) {
        h = Heap::InitializeSolidHeapAsDefault((u32)-1, (Heap*)b, 0x20);
        u32 flagB = h->field4 & 0x10;
        if (flagB != 0)
            Memory::Allocate(0x10, 4, 0);
        a = (u32)this->v15();
        if (flagB == 0) {
            void* allocRes2 = Memory::Allocate(0x10, 4, 0);
            if (allocRes2 == 0)
                a = 0;
        }
        Heap::RestoreFromTemporary();
        if (a == 0) {
            h->_Destroy();
            this->MarkForDestruction();
            return 0;
        }
        u32 topB = h->field8;
        avail = topB - h->MaxAllocationUnitSize();
        avail = (avail + 0x1f) & ~0x1f;
    }

    if (h == 0)
        goto fail;

    {
        u32 topH = h->field8;
        Heap* h2 = 0;
        u32 availInH = topH - h->MaxAllocationUnitSize();
        u32 needed = ((availInH + 0xf) & ~0xf) + 0x30;
        if (needed < ((Heap*)b)->MaxAllocationUnitSize()) {
            h2 = Heap::InitializeSolidHeapAsDefault(avail, (Heap*)b, 0x20);
        }
        if (h2 != 0) {
            if ((u32)h2 < (u32)h) {
                h->_Destroy();
                h = 0;
                int res3 = this->v15();
                u32 okC = (u32)res3;
                Heap::RestoreFromTemporary();
                if (okC == 0) {
                    h2->_Destroy();
                    h2 = h;
                }
            } else {
                Heap::RestoreFromTemporary();
                h2->_Destroy();
                h2 = 0;
            }
        }
        if (h2 != 0) {
            h2->ResizeToFit();
            this->heap_4c = h2;
            return 1;
        }
    }

    if (h != 0) {
        h->ResizeToFit();
        this->heap_4c = h;
        return 1;
    }

fail:
    this->MarkForDestruction();
    return 0;
}
