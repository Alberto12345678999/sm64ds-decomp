typedef int Fix12;
typedef short s16;
typedef unsigned char u8;

extern void* _ZN5Model8LoadFileER13SharedFilePtr(void* f);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void* self, void* f, int a, int b);
extern void* _ZN9Animation8LoadFileER13SharedFilePtr(void* f);
extern void _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void* anim, void* file, int b, int fix, unsigned int e);
extern void func_ov065_02118cc4(char* t);
extern void func_ov065_02118838(char* t);
extern void* _ZN12MeshCollider8LoadFileER13SharedFilePtr(void* f);
extern void _ZN18MovingMeshCollider7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(void* self, void* kcl, void* mtx, Fix12 r, short s, void* clps);
extern void func_020393d4(void* p, void* v);
extern void func_020393c4(void* p, void* v);
extern void _ZN16MeshColliderBase6EnableEP5Actor(void* self, void* a);
extern void _ZN12WithMeshClsn4InitEP5Actor5Fix12IiES3_P10Vector3_16S5_(void* self, void* a, Fix12 r, Fix12 h, void* p, void* q);
extern void _ZN18MovingCylinderClsn4InitEP5Actor5Fix12IiES3_jj(void* self, void* a, Fix12 r, Fix12 h, unsigned int e, unsigned int g);
extern void _ZN25MovingCylinderClsnWithPos4InitEP5ActorRK7Vector35Fix12IiES6_jj(void* self, void* a, void* pos, Fix12 r, Fix12 h, unsigned int e, unsigned int g);
extern void* _ZN5Actor5SpawnEjjRK7Vector3PK10Vector3_16ii(unsigned int a, unsigned int b, void* pos, void* rot, int e, int f);

extern void _ZN16MeshColliderBase16UpdatePosAndAngsERS_P5ActorR10ClsnResultR7Vector3P10Vector3_16S8_(void);
extern void func_ov065_021195bc(void);
extern void func_ov065_021195d0(void);

extern int data_ov065_0211d720;
extern int data_ov002_0210d9c0;
extern void* data_ov065_0211c080[];
extern void* data_ov065_0211d770[];
extern void* data_ov065_0211c08c[];
extern void* data_ov065_0211cd68[];

int _ZN6Dorrie13InitResourcesEv(char* c)
{
    int i;
    void* f = _ZN5Model8LoadFileER13SharedFilePtr(&data_ov065_0211d720);
    _ZN9ModelBase7SetFileEP8BMD_Fileii(c + 0xec, f, 1, -1);
    _ZN5Model8LoadFileER13SharedFilePtr(&data_ov002_0210d9c0);
    for (i = 0; i < 3; i++)
        _ZN9Animation8LoadFileER13SharedFilePtr(data_ov065_0211c080[i]);
    _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c + 0xec, data_ov065_0211d770[1], 0, 0x1000, 0);
    func_ov065_02118cc4(c);
    func_ov065_02118838(c);

    {
        int j;
        char* mtx = c + 0x150;
        char* mmc = c + 0x180;
        for (j = 0; j < 7; j++) {
            void* kcl = _ZN12MeshCollider8LoadFileER13SharedFilePtr(data_ov065_0211c08c[j]);
            _ZN18MovingMeshCollider7SetFileEP8KCL_FileRK9Matrix4x35Fix12IiEsR10CLPS_Block(
                mmc, kcl, mtx, 0x1000, *(short*)(c + 0x8e), data_ov065_0211cd68[j]);
            if ((unsigned)j <= 2) {
                func_020393d4(mmc, _ZN16MeshColliderBase16UpdatePosAndAngsERS_P5ActorR10ClsnResultR7Vector3P10Vector3_16S8_);
                if (j == 2)
                    func_020393c4(mmc, func_ov065_021195bc);
                else
                    func_020393c4(mmc, func_ov065_021195d0);
            }
            _ZN16MeshColliderBase6EnableEP5Actor(mmc, c);
            mtx += 0x200;
            mmc += 0x200;
        }
    }

    {
        *(int*)(c + 0x1194) = *(int*)(c + 0x5c);
        *(int*)(c + 0x1198) = *(int*)(c + 0x60);
        *(int*)(c + 0x119c) = *(int*)(c + 0x64);
        /* u64-mask launder: materialize add r2,sl,#0x5c; ldr/str [r2] */
        *(int*)(((int)c + 0x5c) & 0xFFFFFFFFFFFFFFFF) += 0x7d0000;
    }
    _ZN12WithMeshClsn4InitEP5Actor5Fix12IiES3_P10Vector3_16S5_(
        c + 0xf50, c, 0x1e0000, 0xa0000, 0, 0);
    _ZN18MovingCylinderClsn4InitEP5Actor5Fix12IiES3_jj(
        c + 0x110c, c, 0xdc000, 0xfa000, 2, 0x20);
    {
        int v[3];
        v[0] = 0;
        v[1] = 0x50000;
        v[2] = 0x150000;
        _ZN25MovingCylinderClsnWithPos4InitEP5ActorRK7Vector35Fix12IiES6_jj(
            c + 0x1140, c, v, 0x60000, 0x1b0000, 2, 0x400000);
    }
    {
        *(int*)(c + 0x1180) = *(int*)(c + 0x5c);
        *(int*)(c + 0x1184) = *(int*)(c + 0x60);
        *(int*)(c + 0x1188) = *(int*)(c + 0x64);
        *(short*)(c + 0x11b2) = 0;
        *(u8*)(c + 0x11b5) = 0;
        *(int*)(c + 0x118c) = 0;
        *(int*)(c + 0x1190) = 0;
        *(int*)(c + 0x11ac) = 0;
        *(int*)(c + 0x11a8) = *(int*)(c + 0x11ac);
    }
    if ((*(int*)(c + 8) & 0xff) == 1)
        *(u8*)(c + 0xe8) = 1;
    else
        *(u8*)(c + 0xe8) = 0;
    *(int*)(c + 0xd4) = 0;
    if (*(u8*)(c + 0xe8) != 0) {
        *(int*)(c + 0xd8) = 0;
        *(int*)(c + 0xdc) = 0;
        *(int*)(c + 0xe0) = 0;
        func_ov065_02118838(c);
        {
            void* a = _ZN5Actor5SpawnEjjRK7Vector3PK10Vector3_16ii(
                0xa9, 0, c + 0x5c, c + 0x8c, *(signed char*)(c + 0xcc), -1);
            if (a != 0) {
                *(int*)(c + 0xd4) = (int)a;
                *(int*)((char*)a + 0x174) = (int)c;
            } else {
                *(u8*)(c + 0xe8) = 0;
            }
        }
    }
    return 1;
}
