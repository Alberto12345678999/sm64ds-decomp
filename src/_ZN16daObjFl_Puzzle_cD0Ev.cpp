//cpp
// @symbol _ZN16daObjFl_Puzzle_cD0Ev
/* A delete expression forces the compiler-spelled deleting destructor. */
#include "daObjFl_Puzzle_c.h"

#ifdef _MSC_VER
/* MSVC needs this flat D0 entry. Call the actual class-body destructor
 * qualified so dispatch is direct, then use the class-specific deallocator.
 * The inline body includes member/base teardown; no separate flat D1 provider
 * is supplied by this branch. The mwccarm definition below is unchanged. */
extern "C" daObjFl_Puzzle_c *_ZN16daObjFl_Puzzle_cD0Ev(daObjFl_Puzzle_c *thiz)
{
    thiz->daObjFl_Puzzle_c::~daObjFl_Puzzle_c();          /* direct member/base teardown */
    daObjFl_Puzzle_c::operator delete(thiz);  /* the class-specific delete D0 ends with */
    return thiz;
}
#else
void BowserPuzzlePiece_EmitDeletingDestructor(daObjFl_Puzzle_c *piece)
{
    delete piece;
}
#endif
