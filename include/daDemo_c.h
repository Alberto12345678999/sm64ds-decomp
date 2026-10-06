#ifndef DADEMO_C_H
#define DADEMO_C_H

#include "dActor_c.h"
#include "ModelAnim.h"

/* The model helpers nested in daDemo_c share a virtual scale-bearing base.
   That virtual base is the class shape that makes mwccarm destroy Model/ModelAnim
   before the Vector3 array and emits the retail -0x50 anmModel_c adjustment thunks. */
struct ScaleHolder {
    Vector3 mScale[1];
};

/* Cutscene actor. ROM RTTI name is daDemo_c. Factory allocates 0x104 bytes.
   The two owned render objects are selected by param1: a Model at 0xdc for the
   static variants, a ModelAnim at 0xe0 for the animated variants. */
struct daDemo_c : dActor_c {
    u8 pad_0d0[0xc];       /* 0x0d0 */
    Model *mModel;          /* 0x0dc */
    ModelAnim *mModelAnim;  /* 0x0e0 */
    u8 pad_0e4[0x1e];      /* 0x0e4 */
    u8 mOpacity;            /* 0x102 */
    u8 unk_103;             /* 0x103 */

    /* Keep the destructor first: it is the class's key function. */
    virtual ~daDemo_c();
    virtual int InitResources();
    virtual int CleanupResources();
    virtual int Behavior();
    virtual int Render();
    virtual void OnPendingDestroy();

    struct anmModel_c : ModelAnim, virtual ScaleHolder {
        virtual ~anmModel_c();
        void operator delete(void *ptr) { _ZN6Memory16operator_delete2EPv(ptr); }
    };

    struct simpleModel_c : Model, virtual ScaleHolder {
        virtual ~simpleModel_c();
        void operator delete(void *ptr) { _ZN6Memory16operator_delete2EPv(ptr); }
    };
};

#ifndef SM64DS_PLATFORM_PC
typedef char daDemo_c_size_must_be_0x104[sizeof(daDemo_c) == 0x104 ? 1 : -1];
#endif

#endif /* DADEMO_C_H */
