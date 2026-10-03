// @symbol func_ov006_0211e72c
/* Hide and Boo Seek (dScMgTeresa_c block): draws the 16 Boo sprites. Each
 * 0x24-byte slot at +0x4660 holds a position (x, y in 20.12), a translucency
 * flag, a visible flag, an OAM priority and an animation/frame pair that picks
 * the sprite's attribute block from a table of seven frames per animation.
 * Visible slots go through OAM::Render at unit scale, forced semi-transparent
 * (mode 1) when the flag is set and in the attribute's own mode (-1) otherwise.
 *
 * Provenance: first drafted from nearmiss/db.jsonl (divergence 27) and kept on
 * main as a decompiled-not-matched draft; matched 2026-10-02 under mwccarm
 * 2004/b56 by addressing each field off the walking row pointer, shifting x
 * and y where they are read, and declaring the mode between the frame index
 * and the y read. */
typedef unsigned char u8;

extern void _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiES3_ii(
    int draw, void *attr, int x, int y, int palette, int priority,
    int sx, int sy, int rotation, int mode);
extern void *data_ov006_0213a964[];

void func_ov006_0211e72c(char *row)
{
    int i;

    for (i = 0; i < 16; i++) {
        if (*(u8 *)(row + 0x4000 + 0x67a) != 0) {
            void **frames = data_ov006_0213a964;
            int translucent = *(u8 *)(row + 0x4000 + 0x676);
            int x = *(int *)(row + 0x4000 + 0x660) >> 12;
            int frame = *(u8 *)(row + 0x4000 + 0x67d);
            int anim = *(u8 *)(row + 0x4000 + 0x67e);
            int idx = anim * 7 + frame;
            int mode = -1;
            int y = *(int *)(row + 0x4000 + 0x664) >> 12;
            int priority = *(u8 *)(row + 0x4000 + 0x67b);

            if (translucent != 0)
                mode = 1;
            _ZN3OAM6RenderEbP7OamAttriiii5Fix12IiES3_ii(
                1, frames[idx], x, y, -1, priority, 0x1000, 0x1000, 0, mode);
        }
        row += 0x24;
    }
}
