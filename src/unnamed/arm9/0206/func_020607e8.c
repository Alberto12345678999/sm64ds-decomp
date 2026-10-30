extern int func_02060470(void);
extern void CARDi_Request(void *a, int b, int c);
extern void CARDi_EndTask(void *a);

void func_020607e8(void *thiz)
{
    int **pp = (int **)thiz;
    (*pp)[1] = func_02060470();
    CARDi_Request(thiz, 2, 1);
    CARDi_EndTask(thiz);
}
