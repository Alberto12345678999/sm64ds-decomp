#include "types.h"
#include "Ov007Light.h"

/* Loads an enabled light into the geometry engine: its direction as three
 * 10-bit fractions into LIGHT_VECTOR (0x040004c8) and its color into
 * LIGHT_COLOR (0x040004cc), each tagged with the light number in bits 30-31.
 */
void func_ov007_020c232c(Ov007Light *light) {
    int a, b, c;
    if (light->enabled == 0)
        return;
    a = (light->dirX >> 3) & 0x3ff;
    b = (light->dirY >> 3) & 0x3ff;
    c = (light->dirZ >> 3) & 0x3ff;
    *(volatile unsigned *)0x40004c8 = a | (b << 10) | (c << 20) | (light->id << 30);
    *(volatile unsigned *)0x40004cc = (light->id << 30) | light->color;
}
