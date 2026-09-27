#ifndef DADONKETU_C_H
#define DADONKETU_C_H

#include "types.h"
#include "daOts_c.h"

/* daDonketu_c in the ROM's RTTI. Derives from daOts_c, which owns every member this
 * header used to restate -- the ModelAnim, the dBgCh_Actr, the file table, the
 * dCcAc_c and the ShadowModel are all the base's, and daDonketu_c_classInit proves
 * it by constructing them between the two vtable stores.
 *
 * SIZE 0x400, which is the literal in daDonketu_c_classInit's fBase_c::operator new. The base
 * ends at 0x398, so everything below is daDonketu_c's own.
 *
 * SM64DS RTTI names the implementation daDonketu_c. The reconstructed
 * factory daDonketu_c_classInit (historical alias
 * Bully_Spawn) constructs it for the DONKETU
 * registry profile.
 */
struct daDonketu_c : daOts_c {
    u8  pad_398[0x64];
    /* An actor unique ID, not a count: Behavior passes it to dActor_c::FindWithID and
       increments the byte at +0x3fe of whatever comes back; InitResources zeroes it.
       Left unnamed because that is as far as the bytes go -- daBDonketu_c's u8 at the
       same offset is a different field with a different use, so the offset is no
       guide. */
    s32 mBigBullyID;                    /* 0x3fc */

    /* The destructor is defined INLINE here. Written    
    * out-of-line in `d_a_i_donketu.cpp`, the real destructor makes mwccarm emit D0 BEFORE D1, the  
    * reverse of the cartridge's order, which objisolate refuses for the whole   
    * translation unit, and it emits a third D2 body with no ROM home. The inline definition gives the retail D1/D0 pair in
    * ROM order and no D2, while Behavior -- declared out-of-line and first in   
    * the class body -- keeps this TU as the class's key-function TU, so it still
    * owns the complete _ZTV/_ZTI/_ZTS group declared in this entry's            
    * compiler_only_output.                                                      
    *                                                                            
    * TWO vptr stores and four member destructor calls come out of that one empty 
    * body: its own vptr, then daOts_c's -- inlined, because that destructor is   
    * defined in its class body -- then ShadowModel 0x370, dCcAc_c 0x33c,         
    * dBgCh_Actr 0x174 and ModelAnim 0x110 in reverse declaration order, then     
    * dEnemyBase_c. daIDonketu_c adds no member with a destructor of its own,     
    * only two bytes. D0 is that plus the inherited inline `operator delete`;     
    * slot 17 is the deleting variant. Byte-for-byte the same shape as            
    * daDonketu_c's and daBDonketu_c's, which is what three siblings sharing a    
    * base look like.                                                             
    * -------------------------------------------------------------------------- */
    // @symbol _ZN11daDonketu_cD0Ev
    // @symbol _ZN11daDonketu_cD1Ev
    virtual ~daDonketu_c() {}

    /* methods */
    int Behavior();
    int CleanupResources();
    int Render();
    int InitResources();
    virtual int UpdateRunState();
    virtual void UpdateDeathState();
    virtual void PlayStepSound();
    virtual void PlayHitSound();
    virtual void PlayShellHitSound();
    virtual void PlayDeathSound();
};

#ifndef SM64DS_PLATFORM_PC
/* ROM layout under mwccarm; host ABI divergence is tracked separately. */
typedef char daDonketu_c_size_must_be_0x400[sizeof(daDonketu_c) == 0x400 ? 1 : -1];
#endif

#endif /* DADONKETU_C_H */
