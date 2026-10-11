//cpp
/* Model -- the model-class translation unit. The cartridge split this file
   by class name: it claims the contiguous run 0x02016254..0x020171C8 --
   ModelAnim2, BlendModelAnim, ModelAnim and the Model/ModelBase family,
   written back-to-front because mwccarm emits .text in reverse source order
   under default deferred codegen.

   The three MI classes' destructors are the one shape a member definition
   cannot produce here: defining ~ModelAnim, ~BlendModelAnim or ~ModelAnim2
   emits that class's whole MI vtable group, whose _ZTS/_ZTI records spell
   the project name where the cartridge homes the dExt* one
   (notes/model-rtti-names.md) -- an emitted record no manifest policy can
   license, the forced split BlendModelAnim.json already records. Those
   dtors are written below as free functions spelling out the member dtor's
   synthesized steps -- both vptr stores, the +0x50 secondary base and the
   primary base destroyed through their D2s, D0 appending the class
   operator delete. The six _ZThn80_ destructor thunks stay with their
   enrolled shards: only a member dtor def emits adjustor thunks, and a
   written adjustor compiles to a `bx ip` tail call, not the cartridge's
   `ldr ip; add r0,r0,ip; b`.

   With RTTI off the member-defined key functions ~Model and ~ModelBase
   emit only their vtables, which deadstrip-data onto the cartridge
   records; the member-defined ctors and non-key virtuals emit nothing. */

#include "common.h"          /* flat Matrix4x3 view first: Model's ctor copy */
#include "BlendModelAnim.h"  /* completes ModelAnim then BlendModelAnim */
#include "ModelAnim2.h"      /* completes ModelAnim2 last */
#include "Heap.h"            /* Heap::Reallocate for func_02017060 */

#pragma RTTI off   /* emitted _ZTS/_ZTI could never match the dExt* homes */

extern "C" {
/* local extern: no header declares it; delete veneer for the family's buffers */
void func_0203cbc0(void *ptr);
/* local extern: no header declares it; sizes the transforms buffer off the
   file. Spelled the way func_02046564.c defines it */
u32 func_02046564(BMD_File *file);
/* local extern: no header declares it; initializes ModelComponents over the
   file. Spelled the way func_020462d0.c's callers agreed it */
void func_020462d0(ModelComponents *data, BMD_File *file, void *buffer);
/* local extern: no header declares it; data.transforms-bone walk in Virtual10.
   Spelled the way func_02045074.c's callers agreed it */
void func_02045074(ModelComponents *data, BMD_Bone *bones);
/* local extern: no header declares it; blends verts toward the old pose.
   Spelled (char *) the way func_0204531c.c defines it */
void func_0204531c(char *data, int weight);
/* local extern: no header declares it; polygon-mode setter on the components.
   Spelled (void *) the way func_02046234.c defines its mode */
void func_02046234(ModelComponents *data, void *mode);
/* local extern: no header declares it; polygon-id setter on the components.
   Spelled (void *) the way func_02046008.c defines its id */
void func_02046008(ModelComponents *data, void *id);
/* local extern: no header declares it; opacity walk over the materials */
void func_020461b4(ModelComponents *data, u32 a);
/* local extern: no header declares it; sizes the unk_6c blend buffer off the
   file. Spelled the way func_020462bc.c defines it (the size rides home in a
   pointer-shaped return) */
struct E *func_020462bc(int *file);
/* local extern: no header declares it; initializes ModelComponents' side of
   the blend buffer. Spelled (int *, int) the way func_020462b4.c defines it */
void func_020462b4(int *data, int buf);
/* local extern: decl_common.h's copy is the same mangled spelling; no
   namespace-Memory header declares operator_new2 */
void *_ZN6Memory13operator_new2Ej(u32 size);
/* local extern: no header declares it; global new veneer func_02016e70 uses */
void *_Znwj(u32 size);
/* local extern: no header declares it; the file loader LoadAndSetFile uses.
   Spelled (int) the way LoadFile.c defines it */
int LoadFile(int ov0ID);
/* local extern: no header declares it; the new-size helper func_02017060
   uses. Spelled (int *) the way func_020469e0.c defines it */
int func_020469e0(int *ptr);
/* local extern: no header declares it; ModelBase's destructor frees the file */
void Deallocate(void *ptr);
/* local extern: no header declares it; the camera-space matrix Render uses */
extern Matrix4x3 data_0209b3ec;
/* local extern: no header declares it */
void MulMat4x3Mat4x3(const Matrix4x3 *m1, const Matrix4x3 *m0, Matrix4x3 *mF);
/* local extern: no header declares it; the VRAM-side helpers these veneers
   forward to (func_0201628c/func_020162a4/func_020169d8/func_020169f4/
   func_02016a04/func_02016a14/func_02016aac all do obj+8 adjustors).
   func_02045e2c's 4th param stays int: the def takes short but func_020162a4
   passes a computed 32-bit value and int produces the ROM's codegen (banked
   param row). The four 1-param spellings are deliberate under-declarations
   -- the +8 thunks forward their callers' r1/r2 untouched, which C cannot
   express (banked arity rows) */
void func_02045e2c(int obj, int i, int a, int b);
void func_02045e70(char *p);
void func_02045ec4(void *self, u32 value, int index);
void func_02045ef8(char *p);
void func_02045f80(char *p);
void func_0204605c(char *p);
/* Fix12 by-value speed: the real signature carries Fix12<int> (wall 6az) */
void _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(dExtFrameCtrl_c *self, u16 numFrames, s32 flags, s32 speed, u16 startFrame);
/* defined below; declared here for the call sites above their definitions */
int func_020165c4(BlendModelAnim *self, char *file);
int func_02016ff4(ModelBase *self, BMD_File *file, int c, int d);
u32 func_02017060(void *ptr);
void func_02016b24(struct Obj *o, u32 mask);
}

/* Only the header word SetAnim reads; Animation::UpdateFileOffsets' shard
   spells the pointer fields instead. */
struct BCA_File {
    u16 unk_00;
    u16 numFrames;
};

extern "C" void *data_020a0ea0;

extern Matrix4x3 IDENTITY_MATRIX4X3;

extern "C" {
extern int data_0209cef8[];
extern int data_0209cef0;
extern int data_0208e738;
/* decl_common.h's int[] spelling is the plurality; the records are 0xc-byte
   CommonModelData, so uses cast. */
extern int data_0209cefc[];
/* local extern: the MI groups' primary and secondary vptrs are what the
   free dtors store; decl_common.h spells them unsigned int[]. */
extern unsigned int _ZTV9ModelAnim[];
extern unsigned int _ZTV14BlendModelAnim[];
extern unsigned int _ZTV10ModelAnim2[];
/* local extern: base-subobject destruction needs the D2 variant, which a
   qualified-id call cannot spell (it always picks the complete-object
   D1), so the free dtors call the mangled base dtors directly. Their real
   declarations are the member dtors in the class headers. */
dExtFrameCtrl_c *_ZN15dExtFrameCtrl_cD2Ev(dExtFrameCtrl_c *thiz);
Model *_ZN5ModelD2Ev(Model *thiz);
}

/* 0xc-byte records in the common model data array at data_0209cefc, counted
   by data_0209cef8. func_02016e70 fills the two owned slots; the destructors
   and CleanCommonModelDataArr free them. */
struct CommonModelData {
    BMD_File *file;              /* 0x00 */
    ModelComponents *components; /* 0x04 - pooled entry (_Znwj 0x14); delete2 */
    void *buffer;                /* 0x08 - transforms buffer; func_0203cbc0 */
};

namespace cstd { int fdiv(int a, int b); }

// @symbol _ZN9ModelBaseC2Ev
ModelBase::ModelBase() : modelFile(0) {}

/* One definition emits D2, D0 and D1: the vptr store and the modelFile
   release are the class's one written obligation; D0 follows with the
   ModelBase operator delete (Memory::operator_delete2). */
// @symbol _ZN9ModelBaseD2Ev
// @symbol _ZN9ModelBaseD0Ev
// @symbol _ZN9ModelBaseD1Ev
ModelBase::~ModelBase()
{
    if (modelFile != 0) {
        Deallocate(modelFile);
    }
}

// @symbol func_02017060
extern "C" u32 func_02017060(void *ptr)
{
    if (!ptr)
        return 0;
    Heap *heap = (Heap *)data_020a0ea0;
    heap->_Sizeof(ptr);
    u32 newSize = func_020469e0((int *)ptr);
    return heap->Reallocate(ptr, newSize);
}

/* Loads the file offsets, calls the object's DoSetFile through vtable slot 2,
   and on success reallocs the file down to its reported size. */
// @symbol func_02016ff4
extern "C" int func_02016ff4(ModelBase *self, BMD_File *file, int c, int d)
{
    int ret;
    if (!file) return 0;
    Model::UpdateFileOffsets(*file);
    ret = self->DoSetFile((char *)file, c, d);
    if (ret) func_02017060(file);
    return ret;
}

// @symbol _ZN9ModelBase7SetFileEP8BMD_Fileii
int ModelBase::SetFile(BMD_File *file, int a, int b)
{
    return DoSetFile((char *)file, a, b);
}

// @symbol _ZN5Model14LoadAndSetFileEtii
void Model::LoadAndSetFile(u16 ov0ID, int a, int b)
{
    BMD_File *file = (BMD_File *)::LoadFile(ov0ID);
    modelFile = file;
    func_02016ff4(this, file, a, b);
}

// @symbol _ZN5Model23AddToCommonModelDataArrER8BMD_File
void *Model::AddToCommonModelDataArr(BMD_File &file)
{
    CommonModelData *p = (CommonModelData *)data_0209cefc;
    int i = 0;
    int n = data_0209cef8[0];
    while (i < n) {
        if (&file == p->file) return p;
        i++;
        p++;
    }
    p->file = &file;
    p->components = 0;
    p->buffer = 0;
    data_0209cef8[0] = data_0209cef8[0] + 1;
    if (data_0208e738 == 0) return p;
    LoadTexAndPal(file);
    return p;
}

/* Get-or-create the pooled ModelComponents entry for the pointer-holding
   siblings (dExtCommonModel_c/dExtShadowModel_c): their data slot at +0x8 is
   one of these records, not an embed. */
// @symbol func_02016e70
extern "C" void *func_02016e70(void *file)
{
    CommonModelData *e;
    void *b;

    e = (CommonModelData *)Model::AddToCommonModelDataArr(*(BMD_File *)file);
    if (e->components == 0) {
        e->components = (ModelComponents *)_Znwj(0x14);
        if (e->components == 0) return 0;
        e->buffer = _ZN6Memory13operator_new2Ej(func_02046564((BMD_File *)file));
        b = e->buffer;
        if (b == 0) {
            _ZN6Memory16operator_delete2EPv(e->components);
            e->components = 0;
            return 0;
        }
        func_020462d0(e->components, (BMD_File *)file, b);
    }
    return e->components;
}

/* Frees every record of the common model data array, then resets the count
   and the related global to zero. */
// @symbol CleanCommonModelDataArr
extern "C" void CleanCommonModelDataArr(void)
{
    CommonModelData *e = (CommonModelData *)data_0209cefc;
    int i = 0;

    if (data_0209cef8[0] > 0) {
        do {
            if (e->buffer)
                func_0203cbc0(e->buffer);
            if (e->components)
                _ZN6Memory16operator_delete2EPv(e->components);
            i++;
            e++;
        } while (i < data_0209cef8[0]);
    }

    data_0209cef8[0] = 0;
    data_0209cef0 = 0;
}

/* One definition emits C1 and C2: the base-chain call to ModelBase::C2, the
   _ZTV5Model vptr store, the flat twelve-word identity copy, and the
   transformsBuf zero. The cartridge keeps both variants. */
// @symbol _ZN5ModelC2Ev
// @symbol _ZN5ModelC1Ev
Model::Model() : transformsBuf(0)
{
    mat4x3 = IDENTITY_MATRIX4X3;
}

/* One definition emits D2, D0 and D1: the vptr store and the ModelBase
   destructor call are the compiler's; the body is the class's one written
   obligation -- handing transformsBuf back through the delete veneer. D0
   follows with the ModelBase operator delete (Memory::operator_delete2). */
// @symbol _ZN5ModelD1Ev
Model::~Model()
{
    if (transformsBuf)
        func_0203cbc0(transformsBuf);
}

// @symbol _ZN5Model11UpdateVertsEv
void Model::UpdateVerts()
{
    data.UpdateVertsUsingBones();
}

// @symbol _ZN5Model9DoSetFileEPcii
int Model::DoSetFile(char *file_, int a, int b)
{
    BMD_File *file = (BMD_File *)file_;
    void *buffer;
    AddToCommonModelDataArr(*file);
    transformsBuf = _ZN6Memory13operator_new2Ej(func_02046564(file));
    buffer = transformsBuf;
    if (buffer == 0) return 0;
    func_020462d0(&data, file, buffer);
    data.UpdateVertsUsingBones();
    if (a != 0) func_02016b24((Obj *)this, 0x8000);
    if (b < 0) return 1;
    SetPolygonID(b & 0xff);
    return 1;
}

// @symbol _ZN5Model9Virtual10ER9Matrix4x3
void Model::Virtual10(Matrix4x3 &mat)
{
    /* The copy is one flat 12-word ldm/stm run in the ROM. CW copies the
       nested Matrix4x3 (Matrix3x3 + Vector3) memberwise, which is bigger,
       so it goes through a flat 12-word view instead. */
    struct Mtx12w { Fix12i m[12]; };
    *(Mtx12w *)data.transforms = *(const Mtx12w *)&mat;
    func_02045074(&data, data.modelFile->bones);
}

// @symbol _ZN5Model6RenderEPK7Vector3
void Model::Render(const Vector3 *scale)
{
    Matrix4x3 temp;
    MulMat4x3Mat4x3(&mat4x3, &data_0209b3ec, &temp);
    data.Render(&temp, (Vector3 *)scale);
}

// @symbol func_02016b24
extern "C" void func_02016b24(struct Obj *o, u32 mask)
{
    Model *self = (Model *)o;
    u32 n = self->data.modelFile->numMaterials;
    BMD_Material *p = self->data.materials;
    for (u32 i = 0; i < n; i++) {
        p->flags |= mask;
        p++;
    }
}

// @symbol func_02016acc
extern "C" void func_02016acc(char *a0, u32 mask)
{
    Model *self = (Model *)a0;
    u32 n = self->data.modelFile->numMaterials;
    BMD_Material *p = self->data.materials;
    for (u32 i = 0; i < n; i++) {
        p->flags &= ~mask;
        p++;
    }
}

// @symbol _ZN5Model12SetPolygonIDEi
void Model::SetPolygonID(int id)
{
    func_02046008(&data, (void *)id);
}

// @symbol func_02016aac
extern "C" void func_02016aac(char *self)
{
    func_0204605c(self + 8);
}

/* The base itself ends at 0x8; this addresses the derived class's components
   view at +0x8 blindly. That is only meaningful where the components are
   EMBEDDED there (Model) -- on the pointer-holding siblings this slot is a
   ModelComponents*, so the original can only ever have called this on a
   Model-shaped object. The cast preserves the ROM's this+8. */
// @symbol _ZN9ModelBase12ApplyOpacityEjj
void ModelBase::ApplyOpacity(u32 opacity, u32)
{
    func_020461b4((ModelComponents *)((char *)this + 8), opacity);
}

// @symbol _ZN5Model14SetPolygonModeEi
void Model::SetPolygonMode(int mode)
{
    func_02046234(&data, (void *)mode);
}

// @symbol _ZN5Model12HideMaterialEii
void Model::HideMaterial(int boneID, int listIdx)
{
    BMD_File *file = data.modelFile;
    BMD_Material *mats = data.materials;
    u8 *ids = file->bones[boneID].materialIds;
    mats[ids[listIdx]].flags |= 0x80000000;
}

// @symbol _ZN5Model12ShowMaterialEii
void Model::ShowMaterial(int boneID, int listIdx)
{
    BMD_File *file = data.modelFile;
    BMD_Material *mats = data.materials;
    u8 *ids = file->bones[boneID].materialIds;
    mats[ids[listIdx]].flags &= 0x7fffffff;
}

// @symbol func_02016a14
extern "C" void func_02016a14(char *self)
{
    func_02045f80(self + 8);
}

// @symbol func_02016a04
extern "C" void func_02016a04(char *self)
{
    func_02045ef8(self + 8);
}

// @symbol func_020169f4
extern "C" void func_020169f4(char *self)
{
    func_02045e70(self + 8);
}

// @symbol func_020169d8
extern "C" void func_020169d8(char *self, int index, u32 value)
{
    func_02045ec4(self + 8, value, index);
}

/* One definition emits C1 and C2 -- complete-object and base-subobject --
   and the cartridge keeps both (0x02016958 and 0x02016998). The synthesized
   body is the Model::C2 + dExtFrameCtrl_c::C2 base steps, both vptr stores
   and the written file = 0. */
// @symbol _ZN9ModelAnimC1Ev
// @symbol _ZN9ModelAnimC2Ev
ModelAnim::ModelAnim()
{
    file = 0;
}

/* ~ModelAnim's three variants as free functions (the member-def wall is in
   the banner). D1 and D2 are the same synthesized body -- no virtual bases
   -- both vptr stores, then the secondary dExtFrameCtrl_c base at +0x50
   and the Model base destroyed through their base-object D2s. D0 appends
   the class's operator delete. */
// @symbol _ZN9ModelAnimD1Ev
extern "C" ModelAnim *_ZN9ModelAnimD1Ev(ModelAnim *thiz)
{
    *(u32 *)thiz = (u32)&_ZTV9ModelAnim[2];
    *(u32 *)&static_cast<dExtFrameCtrl_c &>(*thiz) = (u32)&_ZTV9ModelAnim[11];
    _ZN15dExtFrameCtrl_cD2Ev(&static_cast<dExtFrameCtrl_c &>(*thiz));
    _ZN5ModelD2Ev(thiz);
    return thiz;
}

// @symbol _ZN9ModelAnimD0Ev
extern "C" ModelAnim *_ZN9ModelAnimD0Ev(ModelAnim *thiz)
{
    *(u32 *)thiz = (u32)&_ZTV9ModelAnim[2];
    *(u32 *)&static_cast<dExtFrameCtrl_c &>(*thiz) = (u32)&_ZTV9ModelAnim[11];
    _ZN15dExtFrameCtrl_cD2Ev(&static_cast<dExtFrameCtrl_c &>(*thiz));
    _ZN5ModelD2Ev(thiz);
    _ZN6Memory16operator_delete2EPv(thiz);
    return thiz;
}

// @symbol _ZN9ModelAnimD2Ev
extern "C" ModelAnim *_ZN9ModelAnimD2Ev(ModelAnim *thiz)
{
    *(u32 *)thiz = (u32)&_ZTV9ModelAnim[2];
    *(u32 *)&static_cast<dExtFrameCtrl_c &>(*thiz) = (u32)&_ZTV9ModelAnim[11];
    _ZN15dExtFrameCtrl_cD2Ev(&static_cast<dExtFrameCtrl_c &>(*thiz));
    _ZN5ModelD2Ev(thiz);
    return thiz;
}

// @symbol _ZN9ModelAnim11UpdateVertsEv
void ModelAnim::UpdateVerts()
{
    s32 frame = currFrame;
    data.UpdateBones(file, (u32)(frame << 4) >> 0x10);
    data.UpdateVertsUsingBones();
}

// @symbol _ZN9ModelAnim9Virtual10ER9Matrix4x3
void ModelAnim::Virtual10(Matrix4x3 &mat)
{
    s32 frame = currFrame;
    data.UpdateBones(file, (u32)(frame << 4) >> 0x10);
    Model::Virtual10(mat);
}

// @symbol _ZN9ModelAnim6RenderEPK7Vector3
void ModelAnim::Render(const Vector3 *scale)
{
    UpdateVerts();
    Model::Render(scale);
}

// @symbol _ZN9ModelAnim9Virtual18EjPK7Vector3
void ModelAnim::Virtual18(u32 mat, const Vector3 *scale)
{
    Virtual10(*(Matrix4x3 *)mat);
    Model::Render(scale);
}

/* Refresh bones without touching verts -- UpdateVerts' first half kept
   file-local; daMoray_c calls it on a BlendModelAnim*. */
// @symbol func_020167a4
extern "C" void func_020167a4(ModelAnim *self)
{
    s32 frame = self->currFrame;
    self->data.UpdateBones(self->file, (u32)(frame << 4) >> 0x10);
}

/* SetAnim keeps its mangled spelling: wall 6az (notes/mwccarm-codegen.md)
   homes class-typed by-value parameters that a body reads, and the real
   signature carries Fix12<int>. The declaration in ModelAnim.h is the real
   one. */
// @symbol _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj
extern "C" void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(
    ModelAnim *thiz, BCA_File *animFile, s32 flags, s32 speed, u16 startFrame)
{
    if (animFile == thiz->file)
    {
        thiz->SetFlags(flags);
        thiz->speed = speed;
    }
    else
    {
        thiz->file = animFile;
        _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(
            &static_cast<dExtFrameCtrl_c &>(*thiz), animFile->numFrames, flags,
            speed, startFrame);
    }
}

/* Both this and src adjust by +0x50 for the base call: the first real
   multiple-inheritance argument conversion in the tree. */
// @symbol _ZN9ModelAnim4CopyERKS_Pc
void ModelAnim::Copy(const ModelAnim &src, char *newFile)
{
    dExtFrameCtrl_c::Copy(src);
    if (newFile != 0)
        file = (BCA_File *)newFile;
    else
        file = src.file;
}

/* One definition emits C1 and C2; the cartridge keeps C1 (0x020166d4) and
   C2 deadstrips. The synthesized body is the ModelAnim::C2 base step, both
   vptr stores, then blendWeight/unk_6c as mem-initialisers in declaration
   order. */
// @symbol _ZN14BlendModelAnimC1Ev
BlendModelAnim::BlendModelAnim() : blendWeight(0x1000), unk_6c(0) {}

/* ~BlendModelAnim's two cartridge variants as free functions (member-def
   wall in the banner; the emitted D2 has no home). The synthesized steps
   are the two vptr stores and the ModelAnim base D2; the one written
   obligation -- the conditional free of the unk_6c blend buffer -- sits
   between them, and D0 appends the class operator delete. */
// @symbol _ZN14BlendModelAnimD1Ev
extern "C" BlendModelAnim *_ZN14BlendModelAnimD1Ev(BlendModelAnim *thiz)
{
    *(u32 *)thiz = (u32)&_ZTV14BlendModelAnim[2];
    *(u32 *)&static_cast<dExtFrameCtrl_c &>(*thiz) = (u32)&_ZTV14BlendModelAnim[11];
    if (thiz->unk_6c)
        func_0203cbc0(thiz->unk_6c);
    _ZN9ModelAnimD2Ev(thiz);
    return thiz;
}

// @symbol _ZN14BlendModelAnimD0Ev
extern "C" BlendModelAnim *_ZN14BlendModelAnimD0Ev(BlendModelAnim *thiz)
{
    *(u32 *)thiz = (u32)&_ZTV14BlendModelAnim[2];
    *(u32 *)&static_cast<dExtFrameCtrl_c &>(*thiz) = (u32)&_ZTV14BlendModelAnim[11];
    if (thiz->unk_6c)
        func_0203cbc0(thiz->unk_6c);
    _ZN9ModelAnimD2Ev(thiz);
    _ZN6Memory16operator_delete2EPv(thiz);
    return thiz;
}

// @symbol _ZN14BlendModelAnim9DoSetFileEPcii
int BlendModelAnim::DoSetFile(char *file, int a, int b)
{
    char *f = file;
    int r = Model::DoSetFile(file, a, b);
    if (r == 0)
        return 0;
    return func_020165c4(this, f);
}

/* DoSetFile's tail: allocates the unk_6c blend buffer sized off the file and
   hands it plus the ModelComponents member to func_020462b4. */
// @symbol func_020165c4
extern "C" int func_020165c4(BlendModelAnim *self, char *file)
{
    self->unk_6c = _ZN6Memory13operator_new2Ej((u32)func_020462bc((int *)file));
    void *p = self->unk_6c;
    if (p == 0) return 0;
    func_020462b4((int *)&self->data, (int)p);
    return 1;
}

// @symbol _ZN14BlendModelAnim11UpdateVertsEv
void BlendModelAnim::UpdateVerts()
{
    s32 frame = currFrame;
    data.UpdateBones(file, (u32)(frame << 4) >> 0x10);
    if (blendWeight < 0x1000) {
        func_0204531c((char *)&data, blendWeight);
    } else {
        data.UpdateVertsUsingBones();
    }
}

// @symbol _ZN14BlendModelAnim9Virtual10ER9Matrix4x3
void BlendModelAnim::Virtual10(Matrix4x3 &mat)
{
    s32 frame = currFrame;
    data.UpdateBones(file, (u32)(frame << 4) >> 0x10);
    if (blendWeight < 0x1000) {
        func_0204531c((char *)&data, blendWeight);
    } else {
        Model::Virtual10(mat);
    }
}

// @symbol _ZN14BlendModelAnim6RenderEPK7Vector3
void BlendModelAnim::Render(const Vector3 *scale)
{
    UpdateVerts();
    Model::Render(scale);
}

// @symbol _ZN14BlendModelAnim9Virtual18EjPK7Vector3
void BlendModelAnim::Virtual18(u32 mat, const Vector3 *scale)
{
    Virtual10(*(Matrix4x3 *)mat);
    Model::Render(scale);
}

// @symbol _ZN14BlendModelAnim7AdvanceEv
void BlendModelAnim::Advance()
{
    dExtFrameCtrl_c::Advance();
    if (blendWeight < 0x1000) {
        /* launder: keep the RMW aliasing the member so the compiler
           re-reads it the way the ROM does */
        *(int *)(&blendWeight) += blendStep;
    }
}

// @symbol _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt
extern "C" void _ZN14BlendModelAnim7SetAnimER8BCA_Fileii5Fix12IiEt(
    BlendModelAnim *thiz, BCA_File &file, s32 numBlendFrames, s32 flags,
    s32 speed, u16 startFrame)
{
    if (&file == thiz->file)
    {
        thiz->SetFlags(flags);
        thiz->speed = speed;
    }
    else
    {
        thiz->file = &file;
        _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(
            &static_cast<dExtFrameCtrl_c &>(*thiz), file.numFrames, flags, speed,
            startFrame);
        if (numBlendFrames <= 0)
        {
            thiz->blendWeight = 0x1000;
        }
        else
        {
            thiz->blendWeight = 0;
            thiz->blendStep = cstd::fdiv(0x1000, (numBlendFrames + 1) << 12);
        }
    }
}

/* One definition emits C1 and C2; the cartridge keeps C1 (0x020163a0) and
   C2 deadstrips. The init list puts the otherFile store before otherAnim's
   implicit dExtFrameCtrl_c::C1 construction, which is the ROM's schedule. */
// @symbol _ZN10ModelAnim2C1Ev
ModelAnim2::ModelAnim2() : otherFile(0) {}

/* ~ModelAnim2's two cartridge variants as free functions (member-def wall
   in the banner; the emitted D2 has no home). The synthesized steps are
   the two vptr stores, otherAnim's member destruction through its
   complete-object D1, and the ModelAnim base D2; D0 appends the class
   operator delete. */
// @symbol _ZN10ModelAnim2D1Ev
extern "C" ModelAnim2 *_ZN10ModelAnim2D1Ev(ModelAnim2 *thiz)
{
    *(u32 *)thiz = (u32)&_ZTV10ModelAnim2[2];
    *(u32 *)&static_cast<dExtFrameCtrl_c &>(*thiz) = (u32)&_ZTV10ModelAnim2[11];
    thiz->otherAnim.dExtFrameCtrl_c::~dExtFrameCtrl_c();
    _ZN9ModelAnimD2Ev(thiz);
    return thiz;
}

// @symbol _ZN10ModelAnim2D0Ev
extern "C" ModelAnim2 *_ZN10ModelAnim2D0Ev(ModelAnim2 *thiz)
{
    *(u32 *)thiz = (u32)&_ZTV10ModelAnim2[2];
    *(u32 *)&static_cast<dExtFrameCtrl_c &>(*thiz) = (u32)&_ZTV10ModelAnim2[11];
    thiz->otherAnim.dExtFrameCtrl_c::~dExtFrameCtrl_c();
    _ZN9ModelAnimD2Ev(thiz);
    _ZN6Memory16operator_delete2EPv(thiz);
    return thiz;
}

/* SetAnim for the second animation, fast path and all; the mangled spelling
   stays because the real signature carries Fix12<int> (wall 6az). */
// @symbol _ZN10ModelAnim213Func_020162C4Eji5Fix12IiEt
extern "C" void _ZN10ModelAnim213Func_020162C4Eji5Fix12IiEt(
    ModelAnim2 *thiz, u32 newOtherFile, s32 flags, s32 speed, u16 startFrame)
{
    if (newOtherFile == thiz->otherFile)
    {
        thiz->otherAnim.SetFlags(flags);
        thiz->otherAnim.speed = speed;
    }
    else
    {
        thiz->otherFile = newOtherFile;
        _ZN15dExtFrameCtrl_c12SetAnimationEti5Fix12IiEt(
            &thiz->otherAnim, ((BCA_File *)newOtherFile)->numFrames,
            flags, speed, startFrame);
    }
}

// @symbol func_020162a4
extern "C" void func_020162a4(int obj, int i)
{
    func_02045e2c(obj + 8, i, *(int *)(obj + 0x64),
                  (*(u32 *)(obj + 0x70) << 4) >> 16);
}

// @symbol func_0201628c
extern "C" void func_0201628c(int obj, int i)
{
    func_02045e2c(obj + 8, i, 0, 0);
}

/* The second animation is seeded from the first one's state. */
// @symbol _ZN10ModelAnim24CopyERKS_Pcj
void ModelAnim2::Copy(const ModelAnim2 &src, char *newFile, u32 newOtherFile)
{
    ModelAnim::Copy(src, newFile);
    otherAnim.Copy(src);
    if (newOtherFile)
        otherFile = newOtherFile;
    else
        otherFile = src.otherFile;
}
