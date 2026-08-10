//cpp
// @symbol _ZN5SceneD1Ev
/* recovered: real C++ destructor -- the compiler emits the whole body
 *
 * The two vptr stores the hand-written version spelled out are one class each:
 * Scene's own, and then ActorDerived's, which the compiler inlines because
 * that destructor is defined in its class body. Then ActorBase's subobject
 * destructor, called rather than inlined because ActorBase's is not.
 *
 * Scene adds no members with destructors, so there is nothing between them.
 */
#include "Scene.h"

Scene::~Scene()
{
}
