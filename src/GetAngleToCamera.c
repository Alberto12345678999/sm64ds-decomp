/* data_020a1154 holds the four players' 0x24-byte input records (func_0203df40's
 * Rec). data_020a1164 is the first record's inputYaw field (0x10), so a view
 * one record long, starting there, steps to player i's. */
struct RecInputYaw {
    short inputYaw; /* Rec 0x10 -- the camera's input yaw (func_0203db0c) */
    char rest[0x24 - 2];
};
extern struct RecInputYaw data_020a1164[];

short GetAngleToCamera(int i) {
    return data_020a1164[i].inputYaw;
}
