int func_0203da9c(void);
int GetPlayerFlagByte(int handle, int i);
void func_0203db3c(int i, unsigned char v);

/* If handle is this console's index, clears bits 4-6 of its link
   settings byte 0, the field IsPlayerWarping reads. Player::
   func_ov002_020c2e78 calls it when that field is set but the player
   is not in state data_ov002_02110154; otherwise it copies the field
   into mTeleportId. */
void func_02020388(int handle)
{
    if(handle != func_0203da9c()) return;
    int v = GetPlayerFlagByte(handle, 0);
    func_0203db3c(0, (unsigned char)(v & ~0x70));
}
