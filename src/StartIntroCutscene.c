typedef int s32;

extern void* data_020890a0;

extern void LoadInitialGroup(s32 group);
extern void RunKuppaScript(void* script);

void StartIntroCutscene(void)
{
    LoadInitialGroup(0x25);
    RunKuppaScript(&data_020890a0);
}
