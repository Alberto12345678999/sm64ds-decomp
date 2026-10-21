/* data_ov007_02104ba0: the 0x4c record func_ov007_020b9880 allocates; names
 * as in func_ov007_020b9ca8, only the slot this function reads. */
typedef struct Ov007PickerScene {
    char pad_00[0x28];
    int idleFrames; /* 0x28: frames with no touch and no key (func_ov007_020b9ca8) */
} Ov007PickerScene;

extern int* data_ov007_02104ba0[];
int func_ov007_020b8fb4(void){
    Ov007PickerScene *p = (Ov007PickerScene *)data_ov007_02104ba0[0];
    return p->idleFrames >= 0xf0;
}
