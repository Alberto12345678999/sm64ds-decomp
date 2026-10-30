typedef struct {
    unsigned char pad[0x18];
    unsigned int src;
    unsigned int dst;
    unsigned int size;
} CardXferState;

extern CardXferState cardi_common;

extern void CARDi_SetRomOp(unsigned int a, unsigned int b);
extern int CARDi_ReadFromCache(char *self);

int CARDi_ReadCard(char *self) {
    CardXferState *g = &cardi_common;
    unsigned int *buf;
    unsigned int *altBuf = (unsigned int *)(self + 0x20);
    volatile unsigned int *romctrl = (volatile unsigned int *)0x40001A4;
    volatile unsigned int *fifoData = (volatile unsigned int *)0x4100010;
    unsigned int mask = (unsigned int)-0x200;

    for (;;) {
        unsigned int src = g->src;
        unsigned int aligned = src & mask;
        unsigned int i;
        unsigned int status;
        unsigned int cmd;

        if (aligned == src && (g->dst & 3) == 0 && g->size >= 0x200) {
            buf = (unsigned int *)g->dst;
        } else {
            buf = altBuf;
            *(unsigned int *)(self + 8) = aligned;
        }

        CARDi_SetRomOp((aligned >> 8) | 0xb7000000, aligned << 0x18);

        cmd = *(unsigned int *)(self + 4);
        i = 0;
        *romctrl = cmd;
        do {
            status = *romctrl;
            if (status & 0x800000) {
                unsigned int val = *fifoData;
                if (i < 0x200) {
                    buf[i] = val;
                    i++;
                }
            }
        } while (status & 0x80000000);

        if (buf == (unsigned int *)*(volatile unsigned int *)&cardi_common.dst) {
            cardi_common.src += 0x200;
            cardi_common.dst += 0x200;
            cardi_common.size -= 0x200;
            if (cardi_common.size == 0) return cardi_common.size;
        } else {
            int rc = CARDi_ReadFromCache(self);
            if (rc == 0) return rc;
        }
    }
}
