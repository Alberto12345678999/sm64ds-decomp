extern int WM_GetSharedDataAddress(int a, int b, int c);

extern int data_020a0f74;
extern int data_020a0f80;

int func_0204068c(int arg0)
{
    return WM_GetSharedDataAddress(data_020a0f74, data_020a0f80, arg0);
}
