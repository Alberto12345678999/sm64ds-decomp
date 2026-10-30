/* NitroSDK OS_ownerInfo.c OS_GetOwnerInfo: copy the owner fields of the NVRAM
 * user-info block (0x027ffc80) into an OSOwnerInfo -- language (3 bits at
 * +0x64), favourite colour (4 bits at +0x02), birthday month and day, the
 * nickname and comment lengths, then the 10-halfword nickname and
 * 26-halfword comment by MIi_CpuCopy16 (MultiCopyHalf). dst is still a byte
 * view because the three callers pass byte buffers. */
extern void MultiCopyHalf(const void *src, void *dst, unsigned int count);

struct H { unsigned short f : 3; };
struct B { unsigned char f : 4; };

void OS_GetOwnerInfo(unsigned char *dst) {
    unsigned char *base = (unsigned char *)0x27ffc80;
    dst[0] = (unsigned char)(((struct H *)(base + 0x64))->f);
    dst[1] = (unsigned char)(((struct B *)(base + 2))->f);
    dst[2] = base[3];
    dst[3] = base[4];
    *(unsigned short *)(dst + 0x18) = base[0x1a];
    *(unsigned short *)(dst + 0x4e) = base[0x50];
    MultiCopyHalf(base + 6, dst + 4, 0x14);
    MultiCopyHalf(base + 0x1c, dst + 0x1a, 0x34);
}
