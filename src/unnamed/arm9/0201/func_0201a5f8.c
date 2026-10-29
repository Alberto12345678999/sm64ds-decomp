/* Run both create hooks for one scene ID: func_0201a694 is `int (int actorID)`
   and func_0201a614 is `void (int actorID)` where they are defined, in
   func_0201a614.c, and src/runtime/actor/ActorBase.cpp's function-pointer
   tables agree. This file used to spell all three `void *`, which is also why
   its own parameter read void * -- d_s_mb.cpp's caller passes the literal 6. */
extern int func_0201a694(int actorID);
extern void func_0201a614(int actorID);

void func_0201a5f8(int actorID) {
    func_0201a694(actorID);
    func_0201a614(actorID);
}
