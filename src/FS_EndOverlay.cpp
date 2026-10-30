//cpp
/* NitroSDK FS_overlay.c FS_EndOverlay, an older revision than pret's: with
 * interrupts disabled, unlink every __global_destructor_chain entry whose
 * destructor lies in the overlay's image or whose object lies in its bss,
 * run the ones unlinked, and repeat until a pass finds none. Then hand the
 * target, address and size to func_0206cf98. */
#include "types.h"
#include "IRQ.h"
#include "nitro/fs/overlay.h"

extern "C" {

struct MWiDestructorChain {
    struct MWiDestructorChain *next;
    u32 dtor;
    u32 obj;
};

extern struct MWiDestructorChain *__global_destructor_chain;

enum Flag { F0, F1 };

void func_0206cf98(int a, u32 b, u32 c);

void FS_EndOverlay(FSOverlayInfo *p_ovi) {
    struct MWiDestructorChain *prev;
    struct MWiDestructorChain *head;
    struct MWiDestructorChain *tail;
    u32 region_top, image_bottom, region_bottom;
    u32 saved;
    struct MWiDestructorChain *base;
    struct MWiDestructorChain *p;
    struct MWiDestructorChain *next;
    struct MWiDestructorChain **chain = &__global_destructor_chain;

    for (;;) {
        head = 0;
        region_top = (u32)p_ovi->header.ram_address;
        image_bottom = (u32)p_ovi->header.ram_address + p_ovi->header.ram_size;
        /* the bss end: the image end plus the total size less the image */
        region_bottom =
            image_bottom +
            (u32)((int)(p_ovi->header.ram_size + p_ovi->header.bss_size) - p_ovi->header.ram_size);
        tail = 0;
        saved = IRQ::Disable();
        prev = 0;
        base = *chain;
        p = base;
        while (p) {
            u32 dtor, obj;
            dtor = p->dtor;
            next = p->next;
            obj = p->obj;
            if ((dtor >= region_top && dtor < image_bottom) ||
                (obj >= image_bottom && obj < region_bottom)) {
                if (tail)
                    tail->next = p;
                else
                    head = p;
                if (base == p) {
                    *chain = next;
                    base = next;
                }
                p->next = 0;
                tail = p;
                if (prev)
                    prev->next = next;
            } else {
                prev = p;
            }
            p = next;
        }
        IRQ::Restore(saved);
        if (head == 0)
            break;
        do {
            void (*dtor)(u32);
            dtor = (void (*)(u32))head->dtor;
            next = head->next;
            if (dtor)
                dtor(head->obj);
            head = next;
        } while (head);
    }
    {
        u32 target = p_ovi->target;
        u32 size = p_ovi->header.ram_size;
        u32 addr = (u32)p_ovi->header.ram_address;
        enum Flag flag = (target == 0) ? F0 : F1;
        func_0206cf98(flag, addr, size);
    }
}
}
