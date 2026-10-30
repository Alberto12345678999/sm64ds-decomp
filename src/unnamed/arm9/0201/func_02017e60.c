/* The 12 loaded-overlay slots LoadOverlay fills: the overlay id (-1 for a
   free slot) and the RAM range it occupies. */
struct OverlaySlot {
    int id, start, size;
};
extern struct OverlaySlot data_0209d3c4[];

/* Free every loaded-overlay slot. */
void func_02017e60(void) {
    unsigned int i;
    struct OverlaySlot *p = data_0209d3c4;
    for (i = 0; i < 12; i++, p++) {
        p->id = -1;
        p->start = 0;
        p->size = 0;
    }
}
