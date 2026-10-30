extern short data_020a1040[];
/* Store the camera's input yaw in the input record (data_020a1040 +0x10);
   dCamera_c::Behavior passes mAngleY + mInputYawLag. */
void func_0203dafc(int v) {
    data_020a1040[8] = v;
}
