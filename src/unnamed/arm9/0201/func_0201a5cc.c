/* The two create hooks a scene installs, as src/runtime/actor/ActorBase.cpp
   declares them and as their own definitions in func_0201a614.c define them:
   func_0201a694 is `int (int actorID)` and func_0201a614 is `void (int actorID)`.
   Both used to be declared `void (void)` here and both tables `void *`, which
   contradicted every other spelling of the same interface. */
extern int func_0201a694(int actorID);
extern void func_0201a614(int actorID);
extern int (*data_020a4b58)(int actorID);
extern void (*data_020a4b5c)(int actorID);

void func_0201a5cc(void)
{
    data_020a4b58 = func_0201a694;
    data_020a4b5c = func_0201a614;
}
