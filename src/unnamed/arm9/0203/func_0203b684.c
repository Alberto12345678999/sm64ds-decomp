/* Zero data_020a0db0 and data_020a0db4 at boot (func_0201a054). The text
   boxes (Message2.cpp, Message3.cpp), dScStage_c::RenderBouncingArrows and
   the Monte Carlo cards blink on data_020a0db0's low bits, and the star
   select spins a model by it, so it reads as a running frame count. */
extern int data_020a0db0, data_020a0db4;
void func_0203b684(void) {
    data_020a0db0 = 0;
    data_020a0db4 = 0;
}
