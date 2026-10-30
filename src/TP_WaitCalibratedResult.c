/* NitroSDK SPI_tp.c TP_WaitCalibratedResult: wait out the sampling
 * command (bit 1), then TP_GetCalibratedResult. */
struct TPData;
extern void TP_WaitBusy(int mask);
extern int TP_GetCalibratedResult(struct TPData *result);

int TP_WaitCalibratedResult(struct TPData *result) {
    TP_WaitBusy(1);
    return TP_GetCalibratedResult(result);
}
