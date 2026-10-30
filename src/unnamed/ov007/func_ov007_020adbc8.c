/* The 0x38-byte BG layer record func_ov007_020c0aa8 allocates; names as in
 * func_ov007_020adc08, only the slot this file reads. */
typedef struct Ov007BgLayer {
    char pad_00[0x10];
    void *screen; /* 0x10 */
} Ov007BgLayer;

/* The 0xc-byte record func_ov007_020adc08 builds; the manager keeps eight
 * in its layerSlots. */
typedef struct Ov007LayerSlot Ov007LayerSlot;
struct Ov007LayerSlot {
    void *state;         /* 0x00: func_ov007_020c9388's */
    Ov007BgLayer *layer; /* 0x04 */
    unsigned char kind;  /* 0x08 */
};

extern void func_ov007_020c3d1c(void *p);
extern void func_ov007_020c937c(void *state);

/* Frees a layer slot: kinds 1 and 5 own the 0x800-byte screen buffer
 * func_ov007_020adc08 allocated for them; then the state and the record. */
void func_ov007_020adbc8(Ov007LayerSlot *slot) {
    unsigned char kind = slot->kind;
    if (kind == 1 || kind == 5)
        func_ov007_020c3d1c(slot->layer->screen);
    func_ov007_020c937c(slot->state);
    func_ov007_020c3d1c(slot);
}
