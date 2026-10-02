//cpp
// @symbol _ZN16daObjFl_Puzzle_cD1Ev
/* Force mwccarm to emit the class-body destructor as a genuine C++ D1. */
#include "daObjFl_Puzzle_c.h"

void BowserPuzzlePiece_EmitDestructor(daObjFl_Puzzle_c *piece)
{
    piece->~daObjFl_Puzzle_c();
}
