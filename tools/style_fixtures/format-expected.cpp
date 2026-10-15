//cpp
#include "z_fixture.h"
#include "a_fixture.h"
// Preserve this comment and @symbol spelling.
// @symbol _ZN12FixtureActor4TickEv
void FixtureActor::Tick() {
    if (timer) {
        --timer;
    }
}
