/* The asset handle table (see func_02018a24.c). */
extern unsigned short *data_0209d3b8;

/* Record asset handle i's FAT file id (InitializeAssetHandleTable). */
void func_02018a40(unsigned int i, unsigned short v) {
    data_0209d3b8[i] = v;
}
