extern unsigned short data_020a1154[];

/* Flag 0x2000 of player 0's input record (data_020a1154 +0x0c): the load
   signal player 0 raises once every present child has posted its load
   request (func_0203d918), and drops when none has. */
int func_0203d8fc(void) {
    return (data_020a1154[6] & 0x2000) != 0;
}
