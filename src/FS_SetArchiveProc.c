/* NitroSDK FS_archive.c FS_SetArchiveProc: install proc as the archive's
 * user procedure for the commands flags selects. No flags clears proc and
 * no proc clears flags, so the two are set or unset together (FSArchive
 * proc at +0x48, proc_flag at +0x4c). FSi_InitRom installs the ROM
 * archive's procedure with it. */
void FS_SetArchiveProc(int *p_arc, int proc, int flags) {
    if (flags == 0)
        proc = 0;
    else if (proc == 0)
        flags = 0;
    p_arc[0x12] = proc;
    p_arc[0x13] = flags;
}
