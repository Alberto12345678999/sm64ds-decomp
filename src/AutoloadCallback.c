/* AutoloadCallback at 0x020049ec -- NitroSDK crt0's _start_AutoloadDoneCallback.
 * do_autoload branches here once every autoload block is in place, with r0
 * pointing at the module params (BuildInfo). The SDK's default does nothing; a
 * program that needs to act at that point supplies its own. pret/pokediamond's
 * crt0.c spells this default as an asm `bx lr' with the same signature.
 *
 * It keeps dsd's name: `dsd rom config` (0.11) looks up the symbols
 * "AutoloadCallback" and "BuildInfo" by name in the linked ELF and stops if
 * either is missing, so neither can take its SDK spelling. */
void AutoloadCallback(void *argv[]) {}
