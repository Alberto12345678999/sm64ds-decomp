//cpp
#include "dScEntry_c.h"
#include "Heap.h"
extern "C" {
int LoadArchive(int index);
void UnloadArchive(int index);
void func_0202deac(int level);
extern s8 data_ov075_0211c6ec[];
extern u8 data_0209f2d8;
}
void dScEntry_c::LoadCourseResources(int course) {
    mHeap::Heap_t *previousHeap = static_cast<mHeap::Heap_t *>(data_020a0eac)->SetDefault();
    LoadArchive(7);
    int selectedArchive = course + 2;
    unsigned int archive;
    for (archive = 2; archive <= 5; ++archive) {
        if (archive == (unsigned int)selectedArchive)
            continue;
        UnloadArchive(archive);
    }
    LoadArchive(selectedArchive);
    previousHeap->SetDefault();
    data_0209f2d8 = 1;
    func_0202deac(data_ov075_0211c6ec[course]);
}
