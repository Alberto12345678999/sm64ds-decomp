extern void (*data_0209a03c)(void *);
extern char data_0208ee60[];

/* Call the hook data_0209a03c on data_0208ee60. In the ROM it holds the
   empty func_02057e30, and nothing in src sets it. Boot (NitroStartUp)
   calls this right after OS_Init; the card IRQ (func_0204175c) calls the
   same hook. */
void func_0201a490(void)
{
    data_0209a03c(data_0208ee60);
}
