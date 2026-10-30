/* data_020a1154 holds the four players' 0x24-byte input records (func_0203df40's
 * Rec). data_020a1160 is the first record's flags field (0x0c), so a view one
 * record long, starting there, steps to player i's. */
struct RecFlags {
    unsigned short flags; /* Rec 0x0c */
    unsigned char pad[0x22];
};
extern struct RecFlags data_020a1160[];

/* Whether player i's record has flag 0x8000 (func_0203df40 sets it in each
 * frame's local record, data_020a1040). */
int func_0203d950(int i) {
    return (data_020a1160[i].flags & 0x8000) != 0;
}
