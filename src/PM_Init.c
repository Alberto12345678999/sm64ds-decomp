/* PM_Init (the Nitro SDK's pm.c): the power-management PXI channel. */
#define PXI_FIFO_TAG_PM 8
#define PXI_PROC_ARM7 1

/* Four 8-byte entries. The tag-8 receive callback (func_0205fcfc) sets an
 * entry's flag to 1; PM_Init clears all four. */
typedef struct {
    unsigned short flag;
    short pad;
    int arg;
} PmEntry;

extern unsigned short data_020a8104; /* the init flag */
extern int data_020a8114[2];
extern PmEntry data_020a8138[4];
extern char data_020a8124;
extern int data_020a8110;
extern void func_0205fcfc(void); /* the tag-8 receive callback */
extern void PXI_Init(void);
/* func_0205ba3c PXI_IsCallbackReady, func_0205ba64 PXI_SetFifoRecvCallback
 * (src/engine/pxi/PXI_Fifo.cpp). */
extern int func_0205ba3c(int tag, int proc);
extern void func_0205ba64(int tag, void *callback);
extern void func_02058b9c(char *p);

void PM_Init(void) {
    int i;
    if (data_020a8104 != 0)
        return;
    data_020a8104 = 1;
    data_020a8114[0] = 0;
    data_020a8114[1] = 0;
    PXI_Init();
    while (func_0205ba3c(PXI_FIFO_TAG_PM, PXI_PROC_ARM7) == 0)
        ;
    func_0205ba64(PXI_FIFO_TAG_PM, (void *)func_0205fcfc);
    for (i = 0; i < 4; i++)
        data_020a8138[i].flag = 0;
    func_02058b9c(&data_020a8124);
    data_020a8110 = *(int *)0x27ffc3c;
}
