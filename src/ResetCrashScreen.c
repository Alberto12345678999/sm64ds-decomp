extern void *GetBG1ScrPtr(void);
extern void MultiStore16(unsigned short value, volatile void* dst, int count);

void ResetCrashScreen(void)
{
    volatile void *ptr = GetBG1ScrPtr();
    volatile unsigned short val = 0xff;
    MultiStore16(val, ptr, 0x800);
}
