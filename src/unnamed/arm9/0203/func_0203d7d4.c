extern unsigned short data_020a0f1c;
/* Check a file operation's result: nonzero passes (1). Zero sets link
   error bit 0x80 in data_020a0f1c and returns whether this is a
   download-play child (boot type 2 at 0x27ffc40), which cannot read the
   card again; func_02018e68 then sleeps the thread (see myFS_ReadFile.c). */
int func_0203d7d4(int arg){
  int b;
  if (arg != 0) return 1;
  data_020a0f1c |= 0x80;
  b = (*(volatile unsigned short*)0x27ffc40 == 2);
  return b != 0;
}
