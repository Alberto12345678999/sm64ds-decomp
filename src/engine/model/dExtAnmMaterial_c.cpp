//cpp
/* dExtAnmMaterial_c -- Animation child driving BMA-file playback. Cartridge
   class: _ZTV17dExtAnmMaterial_c at 0x0208e7f4 (two slots, the destructor
   pair); the cartridge RTTI names it dExtAnmMaterial_c. TU claims
   0x0201577c..0x0201587c, the whole class run in delinks order. Written
   back-to-front: mwccarm emits .text in reverse source order under default
   deferred codegen.

   leftovers:
   - SetFile keeps its mangled spelling (Fix12<int> by value, wall 6az).
     SetAnimation is the scalar method. The member declarations are real.
   - func_02046e28 and func_020470e8 stay extern "C" helpers with no
     declaring header; Prepare's ROM body is a 0xc long-call veneer, so it
     calls func_020470e8 with that function's own two-argument signature.
   - RTTI stays off: the cartridge names the class dExtAnmMaterial_c, so
     the emitted _ZTS/_ZTI records would have no configured home. */
#include "dExtAnmMaterial_c.h"

/* The cartridge spells this class dExtAnmMaterial_c and its base
   dExtFrameCtrl_c, so the compiler-emitted _ZTS17dExtAnmMaterial_c /
   _ZTI17dExtAnmMaterial_c / _ZTS9Animation / _ZTI9Animation records would be
   homeless under either spelling. Compiling with RTTI off emits no
   records at all; the vtable preamble's typeinfo word deadstrips with the
   rest of the data sections. */
#pragma RTTI off

extern "C" void func_020470e8(BMD_File *model, BMA_File *file);
extern "C" void func_02046e28(ModelComponents *model, BMA_File *file, int frame);

// @symbol _ZN17dExtAnmMaterial_cC1Ev
dExtAnmMaterial_c::dExtAnmMaterial_c()
{
    file = 0;
}

// @symbol _ZN17dExtAnmMaterial_cD1Ev
dExtAnmMaterial_c::~dExtAnmMaterial_c()
{
}

// @symbol _ZN17dExtAnmMaterial_c7SetFileER8BMA_Filei5Fix12IiEj
extern "C" void _ZN17dExtAnmMaterial_c7SetFileER8BMA_Filei5Fix12IiEj(dExtAnmMaterial_c *self, BMA_File *file, s32 flags, s32 speed, u16 startFrame)
{
    if (file == self->file) {
        self->SetFlags(flags);
        self->speed = speed;
    } else {
        self->file = file;
        self->SetAnimation(file->numFrames, flags, speed, startFrame);
    }
}

// @symbol _ZN17dExtAnmMaterial_c6UpdateER15ModelComponents
void dExtAnmMaterial_c::Update(ModelComponents &model)
{
    func_02046e28(&model, file, (u16)((u32)currFrame >> 12));
}

/* The ROM body is a 0xc long-call veneer (ldr ip, [pc]; bx ip); the
   registers pass through untouched, so the matched func_020470e8.c's
   own two-argument signature is the call surface. Prepare is static:
   no this. */
// @symbol _ZN17dExtAnmMaterial_c7PrepareER8BMD_FileR8BMA_File
void dExtAnmMaterial_c::Prepare(BMD_File &model, BMA_File &animFile)
{
    func_020470e8(&model, &animFile);
}
