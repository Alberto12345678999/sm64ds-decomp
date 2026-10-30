/* NitroSDK FS_file.c FS_Init. data_020a8058 is the file's is_init. */
extern int data_020a8058;
extern void FSi_InitRom(unsigned int default_dma_no);

void FS_Init(int default_dma_no) {
    if (!data_020a8058) {
        data_020a8058 = 1;
        FSi_InitRom(default_dma_no);
    }
}
