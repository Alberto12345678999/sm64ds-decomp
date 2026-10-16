struct Pair { int a, b; };
struct Dst4 { struct Pair p0, p1, p2, p3; };
struct Dst5 { struct Pair p0, p1, p2, p3, p4; };
struct Dst7 { struct Pair p0, p1, p2, p3, p4, p5, p6; };

extern struct Pair pmf_dScMgBomroom_c_Round_State0;
extern struct Pair pmf_dScMgBomroom_c_Round_State1;
extern struct Pair pmf_dScMgBomroom_c_Round_State2;
extern struct Pair pmf_dScMgBomroom_c_Round_State3;
extern struct Pair pmf_dScMgBomroom_c_Round_State4;
extern struct Pair pmf_dScMgBomroom_c_Round_SubState0;
extern struct Pair pmf_dScMgBomroom_c_Round_SubState1;
extern struct Pair pmf_dScMgBomroom_c_Round_SubState2;
extern struct Pair pmf_dScMgBomroom_c_Round_SubState3;
extern struct Pair pmf_dScMgBomroom_c_Bomb_State0;
extern struct Pair pmf_dScMgBomroom_c_Bomb_State1;
extern struct Pair pmf_dScMgBomroom_c_Bomb_State2;
extern struct Pair pmf_dScMgBomroom_c_Bomb_State3;
extern struct Pair pmf_dScMgBomroom_c_Bomb_State4;
extern struct Pair pmf_dScMgBomroom_c_Bomb_State5;
extern struct Pair pmf_dScMgBomroom_c_Bomb_State6;
extern struct Pair pmf_dScMgBomroom_c_Bomb_Roam0;
extern struct Pair pmf_dScMgBomroom_c_Bomb_Roam1;
extern struct Pair pmf_dScMgBomroom_c_Bomb_Roam2;
extern struct Pair pmf_dScMgBomroom_c_Bomb_Roam3;
extern struct Pair pmf_dScMgBomroom_c_Bomb_Roam4;
extern struct Pair pmf_dScMgBomroom_c_HatchPanel_StateIdle;
extern struct Pair pmf_dScMgBomroom_c_HatchPanel_StateAnimate;
extern struct Pair pmf_dScMgBomroom_c_HatchPanel_StateHeld;
extern struct Pair pmf_dScMgBomroom_c_HatchPanel_StateRevert;
extern struct Pair pmf_dScMgBomroom_c_PenGate_StateShut;
extern struct Pair pmf_dScMgBomroom_c_PenGate_StateOpening;
extern struct Pair pmf_dScMgBomroom_c_PenGate_StateHold;
extern struct Pair pmf_dScMgBomroom_c_PenGate_StateClosing;
extern struct Pair pmf_dScMgBomroom_c_TopDoor_StateShut;
extern struct Pair pmf_dScMgBomroom_c_TopDoor_StateOpening;
extern struct Pair pmf_dScMgBomroom_c_TopDoor_StateOpen;
extern struct Pair pmf_dScMgBomroom_c_TopDoor_StateClosing;

extern struct Dst5 data_ov006_021416e0;
extern struct Dst4 data_ov006_021416a0;
extern struct Dst7 data_ov006_02141730;
extern struct Dst5 data_ov006_02141708;
extern struct Dst4 sBomroomHatchPanelStateTable;
extern struct Dst4 sBomroomPenGateStateTable;
extern struct Dst4 sBomroomTopDoorStateTable;

void __sinit_ov006_0212fd48(void)
{
    data_ov006_021416e0.p0 = pmf_dScMgBomroom_c_Round_State0;
    data_ov006_021416e0.p1 = pmf_dScMgBomroom_c_Round_State1;
    data_ov006_021416e0.p2 = pmf_dScMgBomroom_c_Round_State2;
    data_ov006_021416e0.p3 = pmf_dScMgBomroom_c_Round_State3;
    data_ov006_021416e0.p4 = pmf_dScMgBomroom_c_Round_State4;

    data_ov006_021416a0.p0 = pmf_dScMgBomroom_c_Round_SubState0;
    data_ov006_021416a0.p1 = pmf_dScMgBomroom_c_Round_SubState1;
    data_ov006_021416a0.p2 = pmf_dScMgBomroom_c_Round_SubState2;
    data_ov006_021416a0.p3 = pmf_dScMgBomroom_c_Round_SubState3;

    data_ov006_02141730.p0 = pmf_dScMgBomroom_c_Bomb_State0;
    data_ov006_02141730.p1 = pmf_dScMgBomroom_c_Bomb_State1;
    data_ov006_02141730.p2 = pmf_dScMgBomroom_c_Bomb_State2;
    data_ov006_02141730.p3 = pmf_dScMgBomroom_c_Bomb_State3;
    data_ov006_02141730.p4 = pmf_dScMgBomroom_c_Bomb_State4;
    data_ov006_02141730.p5 = pmf_dScMgBomroom_c_Bomb_State5;
    data_ov006_02141730.p6 = pmf_dScMgBomroom_c_Bomb_State6;

    data_ov006_02141708.p0 = pmf_dScMgBomroom_c_Bomb_Roam0;
    data_ov006_02141708.p1 = pmf_dScMgBomroom_c_Bomb_Roam1;
    data_ov006_02141708.p2 = pmf_dScMgBomroom_c_Bomb_Roam2;
    data_ov006_02141708.p3 = pmf_dScMgBomroom_c_Bomb_Roam3;
    data_ov006_02141708.p4 = pmf_dScMgBomroom_c_Bomb_Roam4;

    sBomroomHatchPanelStateTable.p0 = pmf_dScMgBomroom_c_HatchPanel_StateIdle;
    sBomroomHatchPanelStateTable.p1 = pmf_dScMgBomroom_c_HatchPanel_StateAnimate;
    sBomroomHatchPanelStateTable.p2 = pmf_dScMgBomroom_c_HatchPanel_StateHeld;
    sBomroomHatchPanelStateTable.p3 = pmf_dScMgBomroom_c_HatchPanel_StateRevert;

    sBomroomPenGateStateTable.p0 = pmf_dScMgBomroom_c_PenGate_StateShut;
    sBomroomPenGateStateTable.p1 = pmf_dScMgBomroom_c_PenGate_StateOpening;
    sBomroomPenGateStateTable.p2 = pmf_dScMgBomroom_c_PenGate_StateHold;
    sBomroomPenGateStateTable.p3 = pmf_dScMgBomroom_c_PenGate_StateClosing;

    sBomroomTopDoorStateTable.p0 = pmf_dScMgBomroom_c_TopDoor_StateShut;
    sBomroomTopDoorStateTable.p1 = pmf_dScMgBomroom_c_TopDoor_StateOpening;
    sBomroomTopDoorStateTable.p2 = pmf_dScMgBomroom_c_TopDoor_StateOpen;
    sBomroomTopDoorStateTable.p3 = pmf_dScMgBomroom_c_TopDoor_StateClosing;
}
