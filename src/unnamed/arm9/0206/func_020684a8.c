extern unsigned char data_020a9d2c[];
extern void func_02068484(void);

/* Reset the beacon send status data_020a9d2c: empty game-record list (+0),
   no current record (+4), state 1 (pick a record), counters cleared. The
   parent setup func_02068ae8 calls it after it clears the file table. */
void func_020684a8(void)
{
    *(int *)&data_020a9d2c[0] = 0;
    *(int *)&data_020a9d2c[4] = 0;
    data_020a9d2c[0xc] = 1;
    func_02068484();
}
