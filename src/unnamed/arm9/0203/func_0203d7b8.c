extern unsigned short data_020a0f1c;
/* Whether a file read has failed (link error bit 0x80 of data_020a0f1c,
   set by func_0203d7d4). LoadOverlay, UnloadOverlay and func_02017e94
   then leave the overlay's RAM alone, and dScMb_c waits on it. */
int func_0203d7b8(void) { return (data_020a0f1c & 128) != 0; }
