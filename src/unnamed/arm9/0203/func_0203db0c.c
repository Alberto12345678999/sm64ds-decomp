/* data_020a1154 holds the four players' 0x24-byte input records (func_0203df40's
 * Rec). data_020a1164 is the first record's inputYaw field (0x10), so a view
 * one record long, starting there, steps to player idx's. */
struct RecInputYaw {
    unsigned short inputYaw; /* Rec 0x10 -- the camera's input yaw */
    char rest[0x24 - 2];
};
extern struct RecInputYaw data_020a1164[];

/* Set player idx's input yaw (GetAngleToCamera reads it back). */
void func_0203db0c(int idx, unsigned short val) {
    data_020a1164[idx].inputYaw = val;
}
