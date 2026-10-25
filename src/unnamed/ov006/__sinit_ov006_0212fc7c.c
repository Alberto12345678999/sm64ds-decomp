/* Runtime asset handles resolved through the overlay 0 file table. */
enum sinit_ov006_0212fc7c_AssetId {
    ASSET_RINGA_BMD = 0x021a,
    ASSET_RINGB_BMD = 0x021b,
    ASSET_RINGC_BMD = 0x021c
};

extern void __cxa_vec_ctor(void *a, int b, int c, void *d, void *e);
extern void func_020731dc(void *object, void *b, void *node);
extern int func_02017acc(void *a, int b);
/* TrmpLine::~TrmpLine() and TrmpLine::TrmpLine() (include/TrmpLine.h), by
   their linker names: this is a C file. */
extern void *_ZN8TrmpLineD1Ev(void *self);
extern void *_ZN8TrmpLineC1Ev(void *self);
extern int TrmpLine_CleanupAll(void);
extern int func_02017ab4(void);
struct SharedFilePtr;

extern int sTrmpLines[];
extern int data_ov006_021408cc[];
extern struct SharedFilePtr sTrmpItemRingAModelFile;
extern int sTrmpItemRingAModelFileDtorRec[];
extern struct SharedFilePtr sTrmpItemRingBModelFile;
extern int sTrmpItemRingBModelFileDtorRec[];
extern struct SharedFilePtr sTrmpItemRingCModelFile;
extern int sTrmpItemRingCModelFileDtorRec[];

void __sinit_ov006_0212fc7c(void) {
    __cxa_vec_ctor(sTrmpLines, 4, 0x32c, (void *)_ZN8TrmpLineC1Ev, (void *)_ZN8TrmpLineD1Ev);
    func_020731dc(0, (void *)TrmpLine_CleanupAll, data_ov006_021408cc);
    func_02017acc(&sTrmpItemRingAModelFile, ASSET_RINGA_BMD);
    func_020731dc(&sTrmpItemRingAModelFile, (void *)func_02017ab4, sTrmpItemRingAModelFileDtorRec);
    func_02017acc(&sTrmpItemRingBModelFile, ASSET_RINGB_BMD);
    func_020731dc(&sTrmpItemRingBModelFile, (void *)func_02017ab4, sTrmpItemRingBModelFileDtorRec);
    func_02017acc(&sTrmpItemRingCModelFile, ASSET_RINGC_BMD);
    func_020731dc(&sTrmpItemRingCModelFile, (void *)func_02017ab4, sTrmpItemRingCModelFileDtorRec);
}
