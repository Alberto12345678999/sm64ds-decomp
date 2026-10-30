int func_0203da9c(void);
int GetPlayerFlagByte(int handle, int i);
void func_0203db3c(int i, unsigned char v);

/* Sets bit 3 of this console's link settings byte 0, the ready bit
   dScEntry_c::ArePlayersReady polls on every joined player through
   func_02020364. */
void func_02020334(void)
{
    int v = GetPlayerFlagByte(func_0203da9c(), 0);
    func_0203db3c(0, (unsigned char)(v | 8));
}
