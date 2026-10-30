extern int GetPlayerFlagByte(int i, int n);
extern void func_0203db3c(int i, int v);

/* The writer twin of GetControllerMode: bits 0-1 of link settings byte 4
   (GetPlayerFlagByte reads player i's copy, func_0203db3c writes this
   console's) become b, the rest of player a's byte kept. dScEntry_c::
   UpdateControlSettings calls it with this console's index right after
   SetControllerMode, so the other consoles see the choice. */
void func_02020028(int a, int b)
{
    int x = GetPlayerFlagByte(a, 4);
    x = b | (x & ~3);
    func_0203db3c(4, x & 0xff);
}
