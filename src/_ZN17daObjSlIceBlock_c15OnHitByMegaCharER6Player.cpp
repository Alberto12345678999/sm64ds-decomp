//cpp
// @symbol _ZN17daObjSlIceBlock_c15OnHitByMegaCharER6Player
#include "daObjSlIceBlock_c.h"
#include "Player.h"

/* daObjSlIceBlock_c::OnHitByMegaChar -- vtable slot 27, ov027 0x0211123c.
 *
 * Same idiom as daObjBk_Dossunbar_c/daObjBk_Lift_c/daObjIceBoard_c::OnHitByMegaChar: Player::
 * IncMegaKillCount is a real method, and the trailing unqualified Kill()
 * call dispatches virtually -- daObjSlIceBlock_c does NOT override slot 31
 * itself (relocs.txt: _ZTV17daObjSlIceBlock_c+0x7c still relocates to
 * dBgActor_c::Kill, ov002 0x020ee55c), so this reaches the inherited
 * base implementation through the vtable, same mechanism as an override
 * would. */
void daObjSlIceBlock_c::OnHitByMegaChar(Player &player)
{
    player.IncMegaKillCount();
    Kill();
}
