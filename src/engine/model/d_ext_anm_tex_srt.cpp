//cpp
/* dExtAnmTexSRT_c -- Animation child driving BTA-file playback. Cartridge
   class: _ZTV15dExtAnmTexSRT_c at 0x0208e7c4 (two slots, the destructor
   pair); the cartridge RTTI names it dExtAnmTexSRT_c. TU claims
   0x0201587c..0x0201597c, the whole class run in delinks order. Written
   back-to-front: mwccarm emits .text in reverse source order under default
   deferred codegen.

   leftovers:
   - SetFile keeps its mangled spelling (Fix12<int> by value, wall 6az).
     SetAnimation is the scalar method. The member declarations are real.
   - func_020469e8 and func_02046b64 stay extern "C" helpers with no
     declaring header; Prepare's ROM body is a 0xc long-call veneer, so it
     calls func_02046b64 with that function's own two-argument signature.
   - RTTI stays off: the cartridge names the class dExtAnmTexSRT_c, so the
     emitted _ZTS/_ZTI records would have no configured home. */
#include "dExtAnmTexSRT_c.h"

/* The cartridge spells this class dExtAnmTexSRT_c, so the compiler-emitted
   _ZTS15dExtAnmTexSRT_c / _ZTI15dExtAnmTexSRT_c / _ZTS9Animation /
   _ZTI9Animation records would be homeless under either spelling. Compiling
   with RTTI off emits no records at all; the vtable preamble's typeinfo word
   deadstrips with the rest of the data sections. */
#pragma RTTI off

extern "C" void func_02046b64(BMD_File *model, BTA_File *file);
extern "C" void func_020469e8(ModelComponents *model, BTA_File *file, int frame);

// @symbol _ZN15dExtAnmTexSRT_cC1Ev
dExtAnmTexSRT_c::dExtAnmTexSRT_c()
{
    file = 0;
}

// @symbol _ZN15dExtAnmTexSRT_cD1Ev
dExtAnmTexSRT_c::~dExtAnmTexSRT_c()
{
}

// @symbol _ZN15dExtAnmTexSRT_c7SetFileER8BTA_Filei5Fix12IiEj
extern "C" void _ZN15dExtAnmTexSRT_c7SetFileER8BTA_Filei5Fix12IiEj(dExtAnmTexSRT_c *self, BTA_File *file, s32 flags, s32 speed, u16 startFrame)
{
    if (file == self->file) {
        self->SetFlags(flags);
        self->speed = speed;
    } else {
        self->file = file;
        self->SetAnimation(file->numFrames, flags, speed, startFrame);
    }
}

// @symbol _ZN15dExtAnmTexSRT_c6UpdateER15ModelComponents
void dExtAnmTexSRT_c::Update(ModelComponents &model)
{
    func_020469e8(&model, file, (u16)((u32)currFrame >> 12));
}

/* The ROM body is a 0xc long-call veneer (ldr ip, [pc]; bx ip); the
   registers pass through untouched, so the matched func_02046b64.c's
   own two-argument signature is the call surface. Prepare is static:
   no this. */
// @symbol _ZN15dExtAnmTexSRT_c7PrepareER8BMD_FileR8BTA_File
void dExtAnmTexSRT_c::Prepare(BMD_File &model, BTA_File &animFile)
{
    func_02046b64(&model, &animFile);
}
