//cpp
/* The Kuppa script interpreter: the cutscene sequencer behind the intro, the
 * castle-fall scene, the star-get camera moves, the ending flight and the
 * staff roll. One TU for the arm9 run 0x0200e494..0x0200f0bc.
 *
 * A script is a run of variable-length command records, ended by a record
 * of size 0:
 *
 *   +0  u8   size of this record in bytes
 *   +1  u8   command (KuppaScriptCommand)
 *   +2  s16  first frame the command runs on, unaligned
 *   +4  s16  last frame, unaligned; negative means "until the script ends"
 *   +6  ...  the command's arguments, unaligned
 *
 * Every frame ProcessKuppaScript walks the whole running script and runs
 * each record whose window holds gKuppaScriptFrame. A record keeps the
 * script alive while it is still to come or open-ended; once none does,
 * and no level load is pending, the script ends.
 *
 * Commands 0..3 drive a player (the command is the character) through
 * Player's own command table; 4 drives the camera's; 0x12 and up drive a
 * daDemo_c cutscene actor whose param1 is the command. ProcessKuppaScript
 * handles the rest itself.
 *
 * The scripts are .data. Their embedded pointers are patched in at boot by
 * __sinit_02073e6c, which also constructs data_0209b294, the fader this file
 * drives. That initializer and the scripts are not part of this file.
 *
 * The file is ROM-ascending under `#pragma defer_codegen off`, which also
 * keeps ProcessKuppaScript's opt_common_subs bracket to that one function.
 */

#pragma defer_codegen off
#include "types.h"
#include "dActor_c.h"
#include "dFdColor_c.h"
#include "dScene_c.h"
#include "Player.h"
#include "PlayerInput.h"
#include "SaveData.h"
#include "Sound.h"

struct dCamera_c;
struct daDemo_c;

enum KuppaScriptCommand {
    KS_PLAYER_LAST = 3,           /* 0..3: a player, by character */
    KS_CAMERA = 4,                /* the camera's command table */
    KS_SKIP_ON_INPUT = 5,         /* a button press or a new touch fades the scene out */
    KS_JUMP = 6,                  /* continue with another script */
    KS_MUSIC = 7,                 /* start a music sequence */
    KS_SOUND = 8,                 /* Sound::Play2D(1, id) */
    KS_SOUND_2 = 9,               /* Sound::Play2D(2, id) */
    KS_MESSAGE = 0xa,             /* open a message on the first frame, close it on the last */
    KS_LOAD_LEVEL = 0xb,          /* load a level, then resume a script there */
    KS_WHITE_FADE_FORWARD = 0xc,  /* data_0209b294 from its start, 14 frames */
    KS_WHITE_FADE_BACKWARD = 0xd, /* data_0209b294 from its end, 80 frames */
    KS_BLACK_FADE_FORWARD = 0xe,  /* data_0209b294 from its start, 30 frames */
    KS_BLACK_FADE_BACKWARD = 0xf, /* data_0209b294 from its end, 80 frames */
    KS_SCENE_FADE = 0x10,         /* data_0209b294 handed to the scene's faders */
    KS_WATERFALL_SOUNDS = 0x11,   /* re-enable the waterfall sounds */
    KS_DEMO_FIRST = 0x12          /* 0x12 and up: a daDemo_c, by param1 */
};

extern "C" {
/* This file's functions. Other files bind them by these C names. */
int RunDemoCommand(u8 *command, int first, int last);
dActor_c *SpawnDemoActor(u32 param1);
dActor_c *FindDemoActor(u32 param1);
int RunPlayerCommand(u8 *command, int first, int last);
dActor_c *SpawnScriptPlayer(u32 character);
dActor_c *FindScriptPlayer(u32 character);
s32 ReadUnalignedSignedInt(u8 *p);
u32 ReadUnalignedInt(u8 *p);
s16 ReadUnalignedShort(u8 *p);
u16 ReadUnalignedUshort(u8 *p);
void EndKuppaScript();
void ProcessKuppaScript();
int IsStarCameraScript3Running();
void RunStarCameraScript(s32 setting);
void StartEndingCutscene();
void StartIntroCutscene();
int RunKuppaScript(u8 *script);
int ContinueKuppaScriptIfNecessary();
void ResetKuppaScript();

/* daDemo_c's and the camera's command dispatchers. */
int func_ov002_020f7d74(daDemo_c *demo, u8 *command, int first, int last);
int func_02008550(dCamera_c *camera, u8 *command, int first, int last);
void func_0201f32c(int messageID);
void LoadLevelNoReturn(int levelID, u32 entrance, u32 arg2, u32 arg3);
void func_02011c8c();
int GetSoundMode();
void SetSoundMode(int mode);
void CollectStarInLevel(s8 levelID, s32 starID);
void DisableSoundPlayersForCredits();
u8 GetStarCameraSetting(s32 star);
}

/* Script state. */
extern u8 *gRunningKuppaScript;
extern u8 *gSavedKuppaScript; /* resumed by ContinueKuppaScriptIfNecessary */
extern u16 gKuppaScriptFrame;
extern u8 gKuppaScriptNumPlayers;
extern u32 gKuppaScriptPlayerIDs[4];
extern u32 gDemoActorIDs[16];

/* Scripts this file starts or tests for by address. */
extern u8 *data_020876e4[]; /* the star-camera scripts, by setting */
extern u8 data_02087c00[];  /* BOB_CREDITS_CUTSCENE */
extern u8 data_02088610[];  /* the ending flight */
extern u8 data_020889b0[];  /* star-camera script 3 */
extern u8 data_02088fb8[];  /* the staff roll */
extern u8 data_020890a0[];  /* INTRO_CUTSCENE */
extern u8 data_02089608[];  /* FALL_IN_FRONT_OF_CASTLE_CUTSCENE */

extern u8 data_0209f21c;               /* NUM_PLAYERS */
extern s8 data_0209f224;               /* STAR_OBTAINED_COPY */
extern u8 data_0209f250;               /* CURR_PLAYER_ID */
extern u8 data_0209f2d8;               /* CURRENT_GAMEMODE */
extern dActor_c *data_0209f394[];      /* PLAYER_ARR */
extern u32 data_0209b454;              /* NEXT_ACTOR_UPDATE_FLAGS */
extern int data_0209caa0[];            /* SaveData; [1] is flags1 */
extern dFdColor_c data_0209b294;       /* GLOBAL_FADER */
extern dFdBrightness_c *data_0209d4b0; /* KS_FADER */
extern dFdBrightness_c *data_0209f5bc; /* SCENE_FADER */
extern u8 data_0209d45c;               /* TOP_SCREEN_RELATED */
extern u8 data_0209d66c;               /* set to close the open message */
extern s8 data_02092110;               /* NEXT_LEVEL_ID */
extern u8 data_020a0e58[];             /* BUTTON_INPUT_ARR, 4 bytes a player */
extern dCamera_c *data_0209f318;       /* CAMERA */
extern int data_ov002_02110aec;        /* WATERFALL_SOUNDS_DISABLED */

/* The fader's timing slots as the ROM calls them here: with a second word,
 * 0, that include/dFader_c.h does not declare and dFdBrightness_c's bodies
 * ignore. */
struct FaderCallView {
    virtual void v0();
    virtual void v1();
    virtual void AdvanceFade();                       /* slot 2 */
    virtual int SetBackwardTime(u32 frames, int arg); /* slot 3 */
    virtual int SetForwardTime(u32 frames, int arg);  /* slot 4 */
};

/* CURRENT_GAMEMODE is 2 while the castle-fall cutscene runs:
 * ContinueKuppaScriptIfNecessary stores 2 only when it resumes
 * FALL_IN_FRONT_OF_CASTLE_CUTSCENE, and EndKuppaScript clears it once no
 * script is left to resume. */
static inline int IsCastleFallCutsceneRunning() {
    return data_0209f2d8 == 2;
}

/* Stylus down this frame with its edge bit set: the touch just began. */
static inline int IsTouchJustBegun(u32 off) {
    return gTouchHeld[off] != 0 && *(gTouchHeld + off + 1) != 0;
}

int RunDemoCommand(u8 *command, int first, int last) {
    dActor_c *demo = FindDemoActor(command[1]);
    if (demo == 0) {
        demo = SpawnDemoActor(command[1]);
        if (demo == 0)
            return 0;
    }
    return func_ov002_020f7d74((daDemo_c *)demo, command, first, last);
}

/* Spawns daDemo_c (actor 0x160) into the first free slot of gDemoActorIDs.
 * Spawn takes its position by reference; the ROM passes null for both
 * position and rotation. */
dActor_c *SpawnDemoActor(u32 param1) {
    u32 *slot = gDemoActorIDs;
    int i;
    for (i = 0; i < 16; i++, slot++) {
        if (*slot == 0) {
            dActor_c *demo = dActor_c::Spawn(0x160, param1, *(const Vector3 *)0, 0, -1, -1);
            if (demo)
                *slot = demo->uniqueID;
            return demo;
        }
    }
    return 0;
}

dActor_c *FindDemoActor(u32 param1) {
    u32 *id = gDemoActorIDs;
    int i;
    for (i = 0; i < 16; i++, id++) {
        dActor_c *demo = dActor_c::FindWithID(*id);
        if (demo && param1 == demo->param1)
            return demo;
    }
    return 0;
}

int RunPlayerCommand(u8 *command, int first, int last) {
    dActor_c *player = FindScriptPlayer(command[1]);
    if (player == 0) {
        player = SpawnScriptPlayer(command[1]);
        if (player == 0)
            return 0;
    }
    return ((Player *)player)->func_ov002_020bd664(command, first, last);
}

/* Spawns a player (actor 0xbf) for a character the script needs but the game
 * has not spawned. param1 carries the character twice (bits 0..2 and 3..5),
 * the player number at bit 6, and the spawn flags at bit 8. In the castle-fall
 * scene only unlocked characters are spawned. */
dActor_c *SpawnScriptPlayer(u32 character) {
    int flags;
    dActor_c *player;
    if (gKuppaScriptPlayerIDs[character] != 0)
        return 0;
    flags = 0x11;
    if (IsCastleFallCutsceneRunning()) {
        if (SaveData::IsCharacterUnlocked(character) == 0)
            return 0;
        flags = 0;
    }
    player = dActor_c::Spawn(
        0xbf, character | (character << 3) | (gKuppaScriptNumPlayers << 6) | (flags << 8),
        *(const Vector3 *)0, 0, -1, -1);
    if (player != 0) {
        gKuppaScriptPlayerIDs[character] = player->uniqueID;
        gKuppaScriptNumPlayers++;
    }
    return player;
}

/* The active player if it is that character, else the one the script
 * spawned. */
dActor_c *FindScriptPlayer(u32 character) {
    dActor_c *player = data_0209f394[data_0209f250];
    if (character == player->param1)
        return player;
    return dActor_c::FindWithID(gKuppaScriptPlayerIDs[character]);
}

/* Script arguments are not aligned, so they are read a byte at a time. */
s32 ReadUnalignedSignedInt(u8 *p) {
    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}

u32 ReadUnalignedInt(u8 *p) {
    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}

s16 ReadUnalignedShort(u8 *p) {
    return (s16)(p[0] | (p[1] << 8));
}

u16 ReadUnalignedUshort(u8 *p) {
    return (u16)(p[0] | (p[1] << 8));
}

/* Undoes what the script set up: the scene-specific sound state, every
 * player and daDemo_c it spawned, and the actor-update flag RunKuppaScript
 * raised. The castle-fall scene's game mode is cleared unless a script is
 * waiting to resume. */
void EndKuppaScript() {
    u32 *id;
    int i;
    u8 *script = gRunningKuppaScript;
    if (script == 0)
        return;
    if (script == data_020890a0) {
        Sound::UnsetPlayerVoiceGroup();
    } else if (script == data_02088fb8) {
        func_02011c8c();
        SetSoundMode(GetSoundMode());
    }

    id = gKuppaScriptPlayerIDs;
    for (i = 0; i < 4; i++) {
        dActor_c *player = dActor_c::FindWithID(*id);
        if (player != 0) {
            player->MarkForDestruction();
            *id = 0;
        }
        id++;
    }

    gKuppaScriptNumPlayers = data_0209f21c;

    id = gDemoActorIDs;
    for (i = 0; i < 16; i++) {
        dActor_c *demo = dActor_c::FindWithID(*id);
        if (demo != 0) {
            demo->MarkForDestruction();
            *id = 0;
        }
        id++;
    }

    gRunningKuppaScript = 0;
    data_0209b454 &= ~0x20000000;
    if (IsCastleFallCutsceneRunning() && gSavedKuppaScript == 0)
        data_0209f2d8 = 0;
}

#pragma opt_common_subs off

void ProcessKuppaScript() {
    u8 *s = gRunningKuppaScript;
    u8 *next;
    int finished;
    if (s == 0)
        return;
    next = 0;
    finished = 1;
    while (*s != 0) {
        int first = ReadUnalignedShort(s + 2);
        int last = ReadUnalignedShort(s + 4);
        u16 frame = gKuppaScriptFrame;
        if (first > frame) {
            finished = 0;
        } else if (last < 0 || last >= frame) {
            u8 command = s[1];
            if (command == KS_SKIP_ON_INPUT) {
                if (data_0209f5bc->IsBetweenStartAndEnd() == 0) {
                    u32 i = gActivePlayerSlot;
                    u32 off = i * 4;
                    if (*(u16 *)(data_020a0e58 + i * 4 + 2) != 0 || IsTouchJustBegun(off)) {
                        dScene_c::StartSceneFade(1, 0, 0);
                        Sound::StopLoadedMusic_Layer1(0x3c);
                    }
                }
                finished = 0;
            } else if (command == KS_JUMP) {
                next = (u8 *)ReadUnalignedInt(s + 6);
            } else if (command == KS_MUSIC) {
                Sound::LoadAndSetMusic_Layer1(ReadUnalignedInt(s + 6));
            } else if (command == KS_SOUND) {
                Sound::Play2D(1, ReadUnalignedInt(s + 6));
            } else if (command == KS_SOUND_2) {
                func_02012790(ReadUnalignedInt(s + 6));
            } else if (command == KS_MESSAGE) {
                if (first == frame) {
                    /* Message 0xd has a variant, 0x16, for a save that has
                       unlocked neither Luigi nor Wario. */
                    first = ReadUnalignedShort(s + 6);
                    if (first == 0xd && SaveData::IsCharacterUnlocked(1) == 0 &&
                        SaveData::IsCharacterUnlocked(2) == 0)
                        first = 0x16;
                    func_0201f32c(first);
                } else if (last == frame) {
                    data_0209d66c = 1;
                }
            } else if (command == KS_LOAD_LEVEL) {
                LoadLevelNoReturn((s8)s[6], s[7], (s8)s[8], 0);
                gSavedKuppaScript = (u8 *)ReadUnalignedInt(s + 9);
                if (!IsCastleFallCutsceneRunning())
                    Sound::StopLoadedMusic_Layer1(0x3c);
                dScene_c::SetAndStopColorFader();
                data_0209d4b0 = 0;
            } else if (command == KS_WHITE_FADE_FORWARD) {
                dFdColor_c *f = &data_0209b294;
                f->SetToStart();
                f->color = 0x7fff;
                ((FaderCallView *)f)->SetForwardTime(0xe, 0);
                data_0209d4b0 = f;
            } else if (command == KS_WHITE_FADE_BACKWARD) {
                dFdColor_c *f = &data_0209b294;
                f->SetToEnd();
                f->color = 0x7fff;
                ((FaderCallView *)f)->SetBackwardTime(0x50, 0);
                data_0209d4b0 = f;
            } else if (command == KS_BLACK_FADE_FORWARD) {
                dFdColor_c *f = &data_0209b294;
                f->SetToStart();
                f->color = 0;
                ((FaderCallView *)f)->SetForwardTime(0x1e, 0);
                data_0209d4b0 = f;
            } else if (command == KS_BLACK_FADE_BACKWARD) {
                dFdColor_c *f = &data_0209b294;
                data_0209d45c = 0x10;
                f->SetToEnd();
                f->color = 0;
                ((FaderCallView *)f)->SetBackwardTime(0x50, 0);
                data_0209d4b0 = f;
            } else if (command == KS_SCENE_FADE) {
                dFdColor_c *f = &data_0209b294;
                f->SetToEnd();
                f->color = 0;
                ((FaderCallView *)f)->SetForwardTime(0x1e, 0);
                dScene_c::SetFaders(f);
            } else if (command == KS_WATERFALL_SOUNDS) {
                data_ov002_02110aec = 0;
            } else if (command == KS_CAMERA) {
                func_02008550(data_0209f318, s, first, last);
            } else if (command <= KS_PLAYER_LAST) {
                RunPlayerCommand(s, first, last);
            } else if (command >= KS_DEMO_FIRST) {
                RunDemoCommand(s, first, last);
            }
            if (last >= 0)
                finished = 0;
        }
        s += *s;
    }
    if (next != 0) {
        gRunningKuppaScript = next;
        gKuppaScriptFrame = 0;
        return;
    }
    if (finished != 0 && data_02092110 < 0) {
        EndKuppaScript();
        return;
    }
    gKuppaScriptFrame++;
    if (gKuppaScriptFrame == 0)
        gKuppaScriptFrame--;
}

#pragma opt_common_subs on

int IsStarCameraScript3Running() {
    return gRunningKuppaScript == data_020889b0;
}

/* A negative setting means "the collected star's own": GetStarCameraSetting
 * reads it from the level's per-star nibbles. */
void RunStarCameraScript(s32 setting) {
    if (setting < 0)
        setting = GetStarCameraSetting(data_0209f224);
    RunKuppaScript(data_020876e4[setting]);
}

/* Player::St_EndingFly_Main starts it once the take-off animation ends. */
void StartEndingCutscene() {
    RunKuppaScript(data_02088610);
}

void StartIntroCutscene() {
    Sound::LoadInitialGroup(0x25);
    RunKuppaScript(data_020890a0);
}

/* Starts a script unless one is running. Outside the castle-fall scene the
 * actor-update flag 0x20000000 is raised for its length. */
int RunKuppaScript(u8 *script) {
    if (gRunningKuppaScript != 0)
        return 0;

    gKuppaScriptFrame = 0;
    gRunningKuppaScript = script;
    if (!IsCastleFallCutsceneRunning())
        data_0209b454 |= 0x20000000;
    ProcessKuppaScript();
    return 1;
}

/* Runs the script a KS_LOAD_LEVEL command saved, once the new level is up. */
int ContinueKuppaScriptIfNecessary() {
    u8 *saved = gSavedKuppaScript;
    if (saved == 0)
        return 0;
    if (saved == data_02089608) {
        data_0209f2d8 = 2;
        Sound::LoadInitialGroup(0x26);
        data_0209caa0[1] &= ~0x204;
        CollectStarInLevel(7, 1);
        CollectStarInLevel(8, 1);
    } else if (saved == data_02087c00) {
        DisableSoundPlayersForCredits();
    }
    gRunningKuppaScript = 0;
    RunKuppaScript(gSavedKuppaScript);
    gSavedKuppaScript = 0;
    return 1;
}

void ResetKuppaScript() {
    int i;

    for (i = 0; i < 4; i++)
        gKuppaScriptPlayerIDs[i] = 0;
    gKuppaScriptNumPlayers = data_0209f21c;
    for (i = 0; i < 16; i++)
        gDemoActorIDs[i] = 0;
    gRunningKuppaScript = gSavedKuppaScript;
}
