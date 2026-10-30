extern unsigned short data_020a0f24;
/* This console's AID, data_020a0f24 (0 for the parent); func_0203fec4
   keeps it once connected and func_020402a0 clears it on a reset. */
int func_02040704(void) { return data_020a0f24; }
