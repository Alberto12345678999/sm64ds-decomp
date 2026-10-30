extern unsigned char data_020a0f08;
/* data_020a0f08, the player count the parent posts: a child copies it from
   byte 0xd of the parent's packet (func_0203ea5c), and func_0203db64 waits
   until the counted players (func_0203daac) reach it. */
int func_0203d890(void) {
    return data_020a0f08;
}
