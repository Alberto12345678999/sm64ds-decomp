extern void *data_020aa3f0;
/* __register_global_object: push a static object onto the destruction
   chain at data_020aa3f0. node is the object's three-word link {next,
   destructor, object}. Every __sinit_* calls it after it constructs an
   object. __destroy_global_chain pops the chain at exit.
   The tooling aliases this address, so it keeps its func_ name. */
void func_020731dc(void *object, void *destructor, void **node)
{
    node[0] = data_020aa3f0;
    node[1] = destructor;
    node[2] = object;
    data_020aa3f0 = node;
}
