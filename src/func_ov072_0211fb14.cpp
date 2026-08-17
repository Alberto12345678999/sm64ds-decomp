//cpp
struct Vector3;
struct ActorBase;
struct dActor_c {
    dActor_c *ClosestPlayer();
};
struct Player {
    int StartTalk(ActorBase &a, bool b);
};
extern "C" int Vec3_HorzDist(const void *a, const void *b);
extern "C" void func_ov072_0211fcb0(void *c, int x);

extern "C" int func_ov072_0211fb14(dActor_c *self)
{
    char *s = (char*)self;
    dActor_c *player = self->ClosestPlayer();
    char *p = (char*)player;
    if (Vec3_HorzDist(s + 0x5c, p + 0x5c) < 0x10e000) {
        if (((Player*)player)->StartTalk(*(ActorBase*)self, 1)) {
            *(dActor_c**)(s + 0x390) = player;
            func_ov072_0211fcb0(self, 1);
        }
    }
    return 1;
}
