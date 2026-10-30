extern int data_020a0f94;
/* The link status data_020a0f94: 0 idle, 1 error, 2 starting, 3 running
   as parent, 4 running as child (func_0203fdac copies the target mode
   into it). */
int func_02040714(void) { return data_020a0f94; }
