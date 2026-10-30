/* NitroSDK CARD_GetBackupTotalSize: data_020a8760 is the backup spec
 * CARD_IdentifyBackup selected from the table at 0x020867bc ({type,
 * total_size, sect_size, ...}). */
extern int *data_020a8760;
int CARD_GetBackupTotalSize(void) {
    return data_020a8760[1];
}
