//cpp
/* dScStage_c::ResetMeshColliders() at 0x0202c8c0. Static: clears a global table of
 * 0x18 words and never sees an object. */
#include "dScStage_c.h"

extern "C" { extern int data_020a0c80[]; }

void dScStage_c::ResetMeshColliders(){
    int i;
    for(i=0;i<0x18;i++) data_020a0c80[i]=0;
}
