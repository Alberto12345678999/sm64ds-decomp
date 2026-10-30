typedef long long s64;
extern s64 OS_GetTick(void);
void func_0201a9fc(char *c){
    *(s64 *)(c + 0x38) = OS_GetTick();
}
