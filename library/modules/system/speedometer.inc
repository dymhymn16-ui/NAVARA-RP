static Text:TD_SpeedometerLine[33];
new PlayerText:PTD_SpeedometerInfo[MAX_PLAYERS][16];
static bool:s_PlayerTextdrawLoaded[MAX_PLAYERS];

enum
{
    SPEEDO_NONE,
    SPEEDO_LIGHT,
    SPEEDO_DOORS,
    SPEEDO_LIMITE,
    SPEEDO_ENGINE,
    SPEEDO_TWINTURBO,
    SPEEDO_ALL
}

LoadGlobalFlinSpeedometerTD() {
    TD_SpeedometerLine[0] = TextDrawCreate(384.599731, 379.897186, "");
    TextDrawTextSize(TD_SpeedometerLine[0], 25.000000, 56.000030);
    TextDrawAlignment(TD_SpeedometerLine[0], 1);
    TextDrawColor(TD_SpeedometerLine[0], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[0], 0);
    TextDrawFont(TD_SpeedometerLine[0], 5);
    TextDrawSetProportional(TD_SpeedometerLine[0], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[0], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[0], 15.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[1] = TextDrawCreate(232.299758, 379.897186, "");
    TextDrawTextSize(TD_SpeedometerLine[1], 25.000000, 56.000030);
    TextDrawAlignment(TD_SpeedometerLine[1], 1);
    TextDrawColor(TD_SpeedometerLine[1], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[1], 0);
    TextDrawFont(TD_SpeedometerLine[1], 5);
    TextDrawSetProportional(TD_SpeedometerLine[1], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[1], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[1], 15.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[2] = TextDrawCreate(241.299636, 387.037872, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[2], 18.000000, 22.000000);
    TextDrawAlignment(TD_SpeedometerLine[2], 1);
    TextDrawColor(TD_SpeedometerLine[2], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[2], 255);
    TextDrawFont(TD_SpeedometerLine[2], 4);
    TextDrawSetProportional(TD_SpeedometerLine[2], 0);

    TD_SpeedometerLine[3] = TextDrawCreate(250.966461, 390.656372, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[3], 141.450378, 33.039989);
    TextDrawAlignment(TD_SpeedometerLine[3], 1);
    TextDrawColor(TD_SpeedometerLine[3], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[3], 255);
    TextDrawFont(TD_SpeedometerLine[3], 4);
    TextDrawSetProportional(TD_SpeedometerLine[3], 0);

    TD_SpeedometerLine[4] = TextDrawCreate(246.299804, 398.123046, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[4], 148.139984, 16.000000);
    TextDrawAlignment(TD_SpeedometerLine[4], 1);
    TextDrawColor(TD_SpeedometerLine[4], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[4], 255);
    TextDrawFont(TD_SpeedometerLine[4], 4);
    TextDrawSetProportional(TD_SpeedometerLine[4], 0);

    TD_SpeedometerLine[5] = TextDrawCreate(291.766632, 377.419189, "");
    TextDrawTextSize(TD_SpeedometerLine[5], 25.000000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[5], 1);
    TextDrawColor(TD_SpeedometerLine[5], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[5], 0);
    TextDrawFont(TD_SpeedometerLine[5], 5);
    TextDrawSetProportional(TD_SpeedometerLine[5], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[5], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[5], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[6] = TextDrawCreate(294.066711, 381.519439, "");
    TextDrawTextSize(TD_SpeedometerLine[6], 23.500000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[6], 1);
    TextDrawColor(TD_SpeedometerLine[6], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[6], 0);
    TextDrawFont(TD_SpeedometerLine[6], 5);
    TextDrawSetProportional(TD_SpeedometerLine[6], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[6], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[6], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[7] = TextDrawCreate(321.368408, 381.604644, "");
    TextDrawTextSize(TD_SpeedometerLine[7], 23.500000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[7], 1);
    TextDrawColor(TD_SpeedometerLine[7], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[7], 0);
    TextDrawFont(TD_SpeedometerLine[7], 5);
    TextDrawSetProportional(TD_SpeedometerLine[7], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[7], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[7], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[8] = TextDrawCreate(322.168487, 377.504394, "");
    TextDrawTextSize(TD_SpeedometerLine[8], 25.000000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[8], 1);
    TextDrawColor(TD_SpeedometerLine[8], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[8], 0);

    TextDrawFont(TD_SpeedometerLine[8], 5);
    TextDrawSetProportional(TD_SpeedometerLine[8], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[8], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[8], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[9] = TextDrawCreate(322.168487, 377.504394, "");
    TextDrawTextSize(TD_SpeedometerLine[9], 25.000000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[9], 1);
    TextDrawColor(TD_SpeedometerLine[9], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[9], 0);
    TextDrawFont(TD_SpeedometerLine[9], 5);
    TextDrawSetProportional(TD_SpeedometerLine[9], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[9], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[9], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[10] = TextDrawCreate(306.133392, 389.970886, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[10], 27.000007, 33.699989);
    TextDrawAlignment(TD_SpeedometerLine[10], 1);
    TextDrawColor(TD_SpeedometerLine[10], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[10], 255);
    TextDrawFont(TD_SpeedometerLine[10], 4);
    TextDrawSetProportional(TD_SpeedometerLine[10], 0);

    TD_SpeedometerLine[11] = TextDrawCreate(382.664642, 387.037872, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[11], 18.000000, 22.000000);
    TextDrawAlignment(TD_SpeedometerLine[11], 1);
    TextDrawColor(TD_SpeedometerLine[11], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[11], 255);
    TextDrawFont(TD_SpeedometerLine[11], 4);
    TextDrawSetProportional(TD_SpeedometerLine[11], 0);

    TD_SpeedometerLine[12] = TextDrawCreate(242.866790, 388.793365, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[12], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[12], 1);
    TextDrawColor(TD_SpeedometerLine[12], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[12], 255);
    TextDrawFont(TD_SpeedometerLine[12], 4);
    TextDrawSetProportional(TD_SpeedometerLine[12], 0);

    TD_SpeedometerLine[13] = TextDrawCreate(267.466430, 388.793365, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[13], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[13], 1);
    TextDrawColor(TD_SpeedometerLine[13], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[13], 255);
    TextDrawFont(TD_SpeedometerLine[13], 4);
    TextDrawSetProportional(TD_SpeedometerLine[13], 0);

    TD_SpeedometerLine[14] = TextDrawCreate(307.700134, 423.141052, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[14], 25.000000, 27.000000);
    TextDrawAlignment(TD_SpeedometerLine[14], 1);
    TextDrawColor(TD_SpeedometerLine[14], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[14], 255);
    TextDrawFont(TD_SpeedometerLine[14], 4);
    TextDrawSetProportional(TD_SpeedometerLine[14], 0);

    TD_SpeedometerLine[15] = TextDrawCreate(403.700225, 442.878601, "");
    TextDrawTextSize(TD_SpeedometerLine[15], 11.000000, -26.000000);
    TextDrawAlignment(TD_SpeedometerLine[15], 1);
    TextDrawColor(TD_SpeedometerLine[15], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[15], 0);
    TextDrawFont(TD_SpeedometerLine[15], 5);
    TextDrawSetProportional(TD_SpeedometerLine[15], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[15], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[15], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[16] = TextDrawCreate(227.597991, 442.878601, "");
    TextDrawTextSize(TD_SpeedometerLine[16], 11.000000, -26.000000);
    TextDrawAlignment(TD_SpeedometerLine[16], 1);
    TextDrawColor(TD_SpeedometerLine[16], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[16], 0);
    TextDrawFont(TD_SpeedometerLine[16], 5);
    TextDrawSetProportional(TD_SpeedometerLine[16], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[16], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[16], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[17] = TextDrawCreate(233.066650, 423.715026, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[17], 176.000305, 13.499998);
    TextDrawAlignment(TD_SpeedometerLine[17], 1);
    TextDrawColor(TD_SpeedometerLine[17], 505290495);

    TextDrawBackgroundColor(TD_SpeedometerLine[17], 255);
    TextDrawFont(TD_SpeedometerLine[17], 4);
    TextDrawSetProportional(TD_SpeedometerLine[17], 0);

    TD_SpeedometerLine[18] = TextDrawCreate(242.832870, 427.130004, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[18], 149.099868, 5.399980);
    TextDrawAlignment(TD_SpeedometerLine[18], 1);
    TextDrawColor(TD_SpeedometerLine[18], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[18], 255);
    TextDrawFont(TD_SpeedometerLine[18], 4);
    TextDrawSetProportional(TD_SpeedometerLine[18], 0);

    TD_SpeedometerLine[19] = TextDrawCreate(244.033325, 428.388946, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[19], 146.899932, 3.000000);
    TextDrawAlignment(TD_SpeedometerLine[19], 1);
    TextDrawColor(TD_SpeedometerLine[19], -1111638529);
    TextDrawBackgroundColor(TD_SpeedometerLine[19], 255);
    TextDrawFont(TD_SpeedometerLine[19], 4);
    TextDrawSetProportional(TD_SpeedometerLine[19], 0);

    TD_SpeedometerLine[20] = TextDrawCreate(243.666625, 427.540893, "//////////");
    TextDrawLetterSize(TD_SpeedometerLine[20], 0.968330, 0.416592);
    TextDrawAlignment(TD_SpeedometerLine[20], 1);
    TextDrawColor(TD_SpeedometerLine[20], 255);
    TextDrawSetShadow(TD_SpeedometerLine[20], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[20], 255);
    TextDrawFont(TD_SpeedometerLine[20], 1);
    TextDrawSetProportional(TD_SpeedometerLine[20], 1);

    TD_SpeedometerLine[21] = TextDrawCreate(235.166702, 424.985626, "o");
    TextDrawLetterSize(TD_SpeedometerLine[21], 0.107230, 0.599816);
    TextDrawTextSize(TD_SpeedometerLine[21], -4.000000, 0.000000);
    TextDrawAlignment(TD_SpeedometerLine[21], 1);
    TextDrawColor(TD_SpeedometerLine[21], -6029057);
    TextDrawSetShadow(TD_SpeedometerLine[21], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[21], 255);
    TextDrawFont(TD_SpeedometerLine[21], 2);
    TextDrawSetProportional(TD_SpeedometerLine[21], 1);

    TD_SpeedometerLine[22] = TextDrawCreate(235.500091, 430.492950, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[22], 2.299998, 3.699995);
    TextDrawAlignment(TD_SpeedometerLine[22], 1);
    TextDrawColor(TD_SpeedometerLine[22], -6029057);
    TextDrawBackgroundColor(TD_SpeedometerLine[22], 255);
    TextDrawFont(TD_SpeedometerLine[22], 4);
    TextDrawSetProportional(TD_SpeedometerLine[22], 0);

    TD_SpeedometerLine[23] = TextDrawCreate(233.400039, 426.030090, "C");
    TextDrawLetterSize(TD_SpeedometerLine[23], 0.066932, 0.915484);
    TextDrawTextSize(TD_SpeedometerLine[23], 0.092600, 1.330299);
    TextDrawAlignment(TD_SpeedometerLine[23], 1);
    TextDrawColor(TD_SpeedometerLine[23], -6029057);
    TextDrawSetShadow(TD_SpeedometerLine[23], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[23], 255);
    TextDrawFont(TD_SpeedometerLine[23], 1);
    TextDrawSetProportional(TD_SpeedometerLine[23], 1);

    TD_SpeedometerLine[24] = TextDrawCreate(311.633422, 429.730072, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[24], 17.000005, 17.000003);
    TextDrawAlignment(TD_SpeedometerLine[24], 1);
    TextDrawColor(TD_SpeedometerLine[24], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[24], 255);
    TextDrawFont(TD_SpeedometerLine[24], 4);
    TextDrawSetProportional(TD_SpeedometerLine[24], 0);

    TD_SpeedometerLine[25] = TextDrawCreate(346.467712, 388.793365, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[25], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[25], 1);
    TextDrawColor(TD_SpeedometerLine[25], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[25], 255);
    TextDrawFont(TD_SpeedometerLine[25], 4);
    TextDrawSetProportional(TD_SpeedometerLine[25], 0);

    TD_SpeedometerLine[26] = TextDrawCreate(303.200195, 391.500732, "");
    TextDrawTextSize(TD_SpeedometerLine[26], 32.399997, 35.000000);
    TextDrawAlignment(TD_SpeedometerLine[26], 1);
    TextDrawColor(TD_SpeedometerLine[26], 67);
    TextDrawBackgroundColor(TD_SpeedometerLine[26], 0);
    TextDrawFont(TD_SpeedometerLine[26], 5);
    TextDrawSetProportional(TD_SpeedometerLine[26], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[26], 2729);
    TextDrawSetPreviewRot(TD_SpeedometerLine[26], 151.000000, 0.000000, 0.000000, 0.698598);

    TD_SpeedometerLine[27] = TextDrawCreate(319.366760, 408.322387, "km/h");
    TextDrawLetterSize(TD_SpeedometerLine[27], 0.163662, 0.824293);
    TextDrawAlignment(TD_SpeedometerLine[27], 2);
    TextDrawColor(TD_SpeedometerLine[27], 977026047);
    TextDrawSetShadow(TD_SpeedometerLine[27], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[27], 255);
    TextDrawFont(TD_SpeedometerLine[27], 1);
    TextDrawSetProportional(TD_SpeedometerLine[27], 1);

    TD_SpeedometerLine[28] = TextDrawCreate(257.000000, 414.185455, "LIMIT");
    TextDrawLetterSize(TD_SpeedometerLine[28], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[28], 2);
    TextDrawColor(TD_SpeedometerLine[28], 255);
    TextDrawSetShadow(TD_SpeedometerLine[28], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[28], 255);
    TextDrawFont(TD_SpeedometerLine[28], 1);
    TextDrawSetProportional(TD_SpeedometerLine[28], 1);

    TD_SpeedometerLine[29] = TextDrawCreate(281.000244, 414.185455, "ENGINE");
    TextDrawLetterSize(TD_SpeedometerLine[29], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[29], 2);
    TextDrawColor(TD_SpeedometerLine[29], 255);
    TextDrawSetShadow(TD_SpeedometerLine[29], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[29], 255);
    TextDrawFont(TD_SpeedometerLine[29], 1);
    TextDrawSetProportional(TD_SpeedometerLine[29], 1);

    TD_SpeedometerLine[30] = TextDrawCreate(360.201049, 414.185455, "LIGHT");
    TextDrawLetterSize(TD_SpeedometerLine[30], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[30], 2);
    TextDrawColor(TD_SpeedometerLine[30], 255);
    TextDrawSetShadow(TD_SpeedometerLine[30], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[30], 255);
    TextDrawFont(TD_SpeedometerLine[30], 1);
    TextDrawSetProportional(TD_SpeedometerLine[30], 1);

    TD_SpeedometerLine[31] = TextDrawCreate(385.401306, 414.185455, "DOORS");
    TextDrawLetterSize(TD_SpeedometerLine[31], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[31], 2);
    TextDrawColor(TD_SpeedometerLine[31], 255);
    TextDrawSetShadow(TD_SpeedometerLine[31], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[31], 255);
    TextDrawFont(TD_SpeedometerLine[31], 1);
    TextDrawSetProportional(TD_SpeedometerLine[31], 1);

    TD_SpeedometerLine[32] = TextDrawCreate(371.066711, 388.793365, "LD_BEAT:chit");
    TextDrawTextSize(TD_SpeedometerLine[32], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[32], 1);
    TextDrawColor(TD_SpeedometerLine[32], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[32], 255);
    TextDrawFont(TD_SpeedometerLine[32], 4);
    TextDrawSetProportional(TD_SpeedometerLine[32], 0);
}

static LoadPlayerFlinSpeedometer(playerid) 
{
    if (s_PlayerTextdrawLoaded[playerid]) {
        return 0;
    }

    s_PlayerTextdrawLoaded[playerid] = true;

    PTD_SpeedometerInfo[playerid][0] = CreatePlayerTextDraw(playerid, 320.000152, 377.081787, "Infernus");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][0], 0.273665, 1.317924);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][0], 2);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, PTD_SpeedometerInfo[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][0], 521869567);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][0], 1);

    PTD_SpeedometerInfo[playerid][1] = CreatePlayerTextDraw(playerid, 319.733581, 392.429779, "0");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][1], 0.253331, 1.749330);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][1], 2);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][1], -5963521);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, PTD_SpeedometerInfo[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][1], -5963763);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][1], 1);

    PTD_SpeedometerInfo[playerid][2] = CreatePlayerTextDraw(playerid, 361.833404, 395.048309, "D");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][2], -0.307332, 1.725630);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][2], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][2], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][2], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][2], 1);

    PTD_SpeedometerInfo[playerid][3] = CreatePlayerTextDraw(playerid, 361.633422, 393.803833, "=");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][3], 0.236662, 1.787852);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][3], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][3], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][3], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][3], 1);

    PTD_SpeedometerInfo[playerid][4] = CreatePlayerTextDraw(playerid, 368.366668, 400.189392, "-");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][4], -0.615631, 1.341462);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][4], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][4], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][4], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][4], 1);

    PTD_SpeedometerInfo[playerid][5] = CreatePlayerTextDraw(playerid, 380.800659, 398.233154, "0");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][5], 0.384665, 1.337406);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][5], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][5], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][5], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][5], 1);

    PTD_SpeedometerInfo[playerid][6] = CreatePlayerTextDraw(playerid, 382.000732, 401.681274, "U");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][6], 0.281331, -0.371627);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][6], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][6], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][6], 1);

    PTD_SpeedometerInfo[playerid][7] = CreatePlayerTextDraw(playerid, 251.999954, 393.933532, "0");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][7], 0.461665, 1.966222);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][7], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][7], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][7], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][7], 1);

    PTD_SpeedometerInfo[playerid][8] = CreatePlayerTextDraw(playerid, 256.833343, 401.685363, "/");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][8], 0.163000, 0.438517);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][8], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][8], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][8], 1);

    PTD_SpeedometerInfo[playerid][9] = CreatePlayerTextDraw(playerid, 278.299926, 398.337280, "U");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][9], 0.266000, 1.479701);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][9], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][9], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][9], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][9], 1);

    PTD_SpeedometerInfo[playerid][10] = CreatePlayerTextDraw(playerid, 276.333374, 409.766845, "J");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][10], 0.230599, -1.481734);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][10], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][10], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][10], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][10], 1);

    PTD_SpeedometerInfo[playerid][11] = CreatePlayerTextDraw(playerid, 287.234039, 409.766845, "J");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][11], -0.237397, -1.481734);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][11], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][11], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][11], 2);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][11], 1);

    PTD_SpeedometerInfo[playerid][12] = CreatePlayerTextDraw(playerid, 317.166900, 433.522460, "(");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][12], 0.382299, 0.844964);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][12], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][12], -5963521);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][12], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][12], 1);

    PTD_SpeedometerInfo[playerid][13] = CreatePlayerTextDraw(playerid, 319.266479, 430.892639, "o");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][13], 0.212999, 1.061926);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][13], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][13], -2147483393);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][13], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][13], 0);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][13], 1);

    PTD_SpeedometerInfo[playerid][14] = CreatePlayerTextDraw(playerid, 318.566864, 432.207702, ")");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][14], 0.333299, 0.898890);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][14], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][14], -9174785);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][14], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][14], 1);

    PTD_SpeedometerInfo[playerid][15] = CreatePlayerTextDraw(playerid, 392.399902, 424.970275, "123.3");
    PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][15], 0.200332, 1.002665);
    PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][15], 1);
    PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][15], -5701377);
    PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][15], 255);
    PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][15], 1);

    return 1;
}

ShowTextDraw_FlinSpeedometr(playerid, bool:isCreate)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && vehicleid != 0)
    {
        if( !IsABicycleVehicle(vehicleid) )
        {
            if(isCreate) LoadPlayerFlinSpeedometer(playerid);

            for(new i = 32; i != -1; i--)
            {
                if(i < 16) PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                TextDrawShowForPlayer(playerid, TD_SpeedometerLine[i]);
            }
            PlayerTextDrawSetString(playerid, PTD_SpeedometerInfo[playerid][0], GetVehicleName(GetVehicleModel(vehicleid)));

            for(new i = SPEEDO_NONE+1; i < SPEEDO_ALL; i++) OnPlayerUpdateVehicleInfo(playerid, i);
        }
    }
    return 1;
}

HideTextDraw_FlinSpeedometr(playerid, bool:isDestroy)
{
    for(new i = 32; i != -1; i--)
    {
        if(i < 16 && PTD_SpeedometerInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
        {
            if(isDestroy) {
                PlayerTextDrawDestroy(playerid, PTD_SpeedometerInfo[playerid][i]);
                PTD_SpeedometerInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
            else PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
        }
        TextDrawHideForPlayer(playerid, TD_SpeedometerLine[i]);
    }
    if (isDestroy) s_PlayerTextdrawLoaded[playerid] = false;
}

OnPlayerUpdateVehicleInfo(playerid, type)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid < 0 || vehicleid >= MAX_VEHICLES) return 1;
        if( !IsABicycleVehicle(vehicleid) )
        {
            switch(type)
            {
                case SPEEDO_LIGHT:
                {
                    for(new i = 2; i <= 4; i++)
                    {
                        new engine,lights,alarm,doors,bonnet,boot,objective;
                        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
                        PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                        PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], lights ? 1018626047 : -1);
                        PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                    }
                }
                case SPEEDO_DOORS:
                {
                    for(new i = 5; i <= 6; i++)
                    {
                        PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                        PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], veh_info[vehicleid][v_locked] ? -1523963137 : -1);
                        PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                    }
                }
                case SPEEDO_LIMITE:
                {
                    for(new i = 7; i <= 8; i++)
                    {
                        PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                        PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], PlayerInfo[playerid][p_carlimit] != 0 ? -65281 : -1);
                        PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                    }
                }
                case SPEEDO_ENGINE:
                {
                    for(new i = 9; i <= 11; i++)
                    {
                        PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                        PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], veh_info[vehicleid][v_engine_status] ? 8388863 : -1);
                        PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                    }
                }
                case SPEEDO_TWINTURBO:
                {
                    for(new i = 12; i <= 14; i++)
                    {
                        new twinturbo_on = 0; //TODO
                        PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                        PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], twinturbo_on ? 8388863 : -1);
                        PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                    }
                }
            }
        }
    }
    return 1;
}
/*
public OnPlayerConnect(playerid)
{
    s_PlayerTextdrawLoaded[playerid] = false;

    #if defined SpeedoMeter_OnPlayerConnect
        return SpeedoMeter_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect SpeedoMeter_OnPlayerConnect
#if defined SpeedoMeter_OnPlayerConnect
    forward SpeedoMeter_OnPlayerConnect(playerid);
#endif
*/