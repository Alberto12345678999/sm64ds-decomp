extern void *data_0209d4ac;
extern void *data_0209d4b0;

/* Advance the scene's fader, data_0209d4ac (dScene_c sets it): vtable
   slot 2, the virtual dFader_c::AdvanceFade. The frame start
   (func_02019390) calls it every frame. */
void func_02018efc(void) {
    void **o = (void **)data_0209d4ac;
    if (!o)
        return;
    void **vt = (void **)o[0];
    ((void (*)(void *))vt[2])(o);
}

/* Advance the active transition fader, data_0209d4b0, by the same slot 2:
   either a stage wipe (dFdWipe_c, set and cleared by d_s_stage_methods.cpp)
   or the cutscene colour fader data_0209b294 (dFdColor_c), which
   KuppaScript.cpp points it at for KS_WHITE/BLACK_FADE_* and clears on
   KS_LOAD_LEVEL. The frame start (func_02019390) calls it when the scene's
   GraphCallback0 lets the frame through. */
void func_02018ec0(void) {
    void **o = (void **)data_0209d4b0;
    if (!o)
        return;
    void **vt = (void **)o[0];
    ((void (*)(void *))vt[2])(o);
}
