new Text:NDP_GlobalTextdraw[1];
new PlayerText:NDP_PlayerTextdraw[MAX_PLAYERS][5];

// FPS
new pDrunkLevelLast[MAX_PLAYERS];
new pFPS[MAX_PLAYERS];

// ------------------------------------------------------------------

stock CreateDateServer()
{
	NDP_GlobalTextdraw[0] = TextDrawCreate(4.000000, 433.920044, "");
	TextDrawLetterSize(NDP_GlobalTextdraw[0], 0.369500, 1.000799);
	TextDrawTextSize(NDP_GlobalTextdraw[0], 1280.000000, 1280.000000);
	TextDrawAlignment(NDP_GlobalTextdraw[0], 1);
	TextDrawColor(NDP_GlobalTextdraw[0], 0x3EF27DFF);
	TextDrawBoxColor(NDP_GlobalTextdraw[0], 0x80808080);
	TextDrawSetShadow(NDP_GlobalTextdraw[0], 0);
	TextDrawSetOutline(NDP_GlobalTextdraw[0], 1);
	TextDrawBackgroundColor(NDP_GlobalTextdraw[0], 0x00000033);
	TextDrawFont(NDP_GlobalTextdraw[0], 1);
	TextDrawSetProportional(NDP_GlobalTextdraw[0], 1);
	TextDrawSetSelectable(NDP_GlobalTextdraw[0], 0);
	TextDrawSetPreviewRot(NDP_GlobalTextdraw[0], 0.000000, 0.000000, 0.000000, 1.000000);

	return 1;
}

stock Load_NPD(playerid)
{
	NDP_PlayerTextdraw[playerid][0] = CreatePlayerTextDraw(playerid, 89.999, 325.498, "_");
	PlayerTextDrawLetterSize(playerid, NDP_PlayerTextdraw[playerid][0], 0.306, 1.252);
	PlayerTextDrawTextSize(playerid, NDP_PlayerTextdraw[playerid][0], 1280.000, 1280.000);
	PlayerTextDrawAlignment(playerid, NDP_PlayerTextdraw[playerid][0], 2);
	PlayerTextDrawColor(playerid, NDP_PlayerTextdraw[playerid][0], 1056079359);
	PlayerTextDrawSetShadow(playerid, NDP_PlayerTextdraw[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, NDP_PlayerTextdraw[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, NDP_PlayerTextdraw[playerid][0], 51);
	PlayerTextDrawFont(playerid, NDP_PlayerTextdraw[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, NDP_PlayerTextdraw[playerid][0], 1);

	NDP_PlayerTextdraw[playerid][1] = CreatePlayerTextDraw(playerid, 3.666, 409.970, "_");
	PlayerTextDrawLetterSize(playerid, NDP_PlayerTextdraw[playerid][1], 0.318, 1.276);
	PlayerTextDrawTextSize(playerid, NDP_PlayerTextdraw[playerid][1], 1280.000, 1280.000);
	PlayerTextDrawAlignment(playerid, NDP_PlayerTextdraw[playerid][1], 1);
	PlayerTextDrawColor(playerid, NDP_PlayerTextdraw[playerid][1], 1056079359);
	PlayerTextDrawSetShadow(playerid, NDP_PlayerTextdraw[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, NDP_PlayerTextdraw[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, NDP_PlayerTextdraw[playerid][1], 51);
	PlayerTextDrawFont(playerid, NDP_PlayerTextdraw[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, NDP_PlayerTextdraw[playerid][1], 1);

    NDP_PlayerTextdraw[playerid][2] = CreatePlayerTextDraw(playerid, 496.666, 102.003, "particle:lamp_shad_64");
    PlayerTextDrawLetterSize(playerid, NDP_PlayerTextdraw[playerid][2], 0.479, 1.120);
    PlayerTextDrawTextSize(playerid, NDP_PlayerTextdraw[playerid][2], 118.000, 12.000);
    PlayerTextDrawAlignment(playerid, NDP_PlayerTextdraw[playerid][2], 1);
    PlayerTextDrawColor(playerid, NDP_PlayerTextdraw[playerid][2], 69);
    PlayerTextDrawSetShadow(playerid, NDP_PlayerTextdraw[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, NDP_PlayerTextdraw[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, NDP_PlayerTextdraw[playerid][2], 0);
    PlayerTextDrawFont(playerid, NDP_PlayerTextdraw[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, NDP_PlayerTextdraw[playerid][2], 0);
    PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][2]);

    NDP_PlayerTextdraw[playerid][3] = CreatePlayerTextDraw(playerid, 495.666, 117.251, "particle:lamp_shad_64");
    PlayerTextDrawLetterSize(playerid, NDP_PlayerTextdraw[playerid][3], 0.479, 1.120);
    PlayerTextDrawTextSize(playerid, NDP_PlayerTextdraw[playerid][3], 117.000, -16.000);
    PlayerTextDrawAlignment(playerid, NDP_PlayerTextdraw[playerid][3], 1);
    PlayerTextDrawColor(playerid, NDP_PlayerTextdraw[playerid][3], 69);
    PlayerTextDrawSetShadow(playerid, NDP_PlayerTextdraw[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, NDP_PlayerTextdraw[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, NDP_PlayerTextdraw[playerid][3], 0);
    PlayerTextDrawFont(playerid, NDP_PlayerTextdraw[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, NDP_PlayerTextdraw[playerid][3], 0);
    PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][3]);

    NDP_PlayerTextdraw[playerid][4] = CreatePlayerTextDraw(playerid, 554.033, 103.162, "FPS:_~g~0_~w~PING:_~g~0_~w~LOSS:_~w~%0.0");
    PlayerTextDrawLetterSize(playerid, NDP_PlayerTextdraw[playerid][4], 0.177, 0.856);
    PlayerTextDrawTextSize(playerid, NDP_PlayerTextdraw[playerid][4], 0.000, 904.000);
    PlayerTextDrawAlignment(playerid, NDP_PlayerTextdraw[playerid][4], 2);
    PlayerTextDrawColor(playerid, NDP_PlayerTextdraw[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, NDP_PlayerTextdraw[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, NDP_PlayerTextdraw[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, NDP_PlayerTextdraw[playerid][4], 255);
    PlayerTextDrawFont(playerid, NDP_PlayerTextdraw[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, NDP_PlayerTextdraw[playerid][4], 1);
    PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][4]);

	PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][0]);
	PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][1]);
	PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][2]);
	PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][3]);
	PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][4]);
	
	TextDrawShowForPlayer(playerid, NDP_GlobalTextdraw[0]);

	UpdateNameNDP(playerid);
}

stock Destroy_NPD(playerid)
{
	PlayerTextDrawDestroy(playerid, NDP_PlayerTextdraw[playerid][0]);
	PlayerTextDrawDestroy(playerid, NDP_PlayerTextdraw[playerid][1]);
	PlayerTextDrawDestroy(playerid, NDP_PlayerTextdraw[playerid][2]);
	PlayerTextDrawDestroy(playerid, NDP_PlayerTextdraw[playerid][3]);
	PlayerTextDrawDestroy(playerid, NDP_PlayerTextdraw[playerid][4]);
	
	TextDrawHideForPlayer(playerid, NDP_GlobalTextdraw[0]);
}

stock NDP_OneSecondTimer()
{
	new ndp_string[150];

	new year, month, day;

	getdate(year, month, day);

	format(ndp_string, sizeof ndp_string, "%02d/%02d/%d_%02d:%02d:%02d", day, month, year, timestamp_hour, timestamp_minute, timestamp_second);
	TextDrawSetString(NDP_GlobalTextdraw[0], ndp_string);

	foreach (new i: Player) {
		format(ndp_string, 16, "PING: %d", GetPlayerPing(i));
		PlayerTextDrawSetString(i, NDP_PlayerTextdraw[i][1], ndp_string);

		new playerFPSString[30];

		if(GetPlayerFPS(i) < 40) format(playerFPSString, sizeof(playerFPSString), "~r~%d", GetPlayerFPS(i));
		if(GetPlayerFPS(i) > 60) format(playerFPSString, sizeof(playerFPSString), "~y~%d", GetPlayerFPS(i));
		if(GetPlayerFPS(i) > 80) format(playerFPSString, sizeof(playerFPSString), "~g~%d", GetPlayerFPS(i));
		if(GetPlayerFPS(i) <= 0) format(playerFPSString, sizeof(playerFPSString), "~r~0");

		format(ndp_string, sizeof ndp_string, "FPS:_%s_~w~PING:_~g~%d_~w~LOSS:_~w~%%%.1f", playerFPSString, GetPlayerPing(i), NetStats_PacketLossPercent(i));
		PlayerTextDrawSetString(i, NDP_PlayerTextdraw[i][4], ndp_string);
	}
}


stock ShowPlayerNameTDForPlayer(playerid) 
{
	return PlayerTextDrawShow(playerid, NDP_PlayerTextdraw[playerid][0]);
}

stock HidePlayerNameTDForPlayer(playerid)
{
	return PlayerTextDrawHide(playerid, NDP_PlayerTextdraw[playerid][0]);
}

stock UpdateNameNDP(playerid)
{
	new main_string[198];

	format(main_string, 28, "%s(%d)", PlayerInfo[playerid][name], playerid);
	
	PlayerTextDrawSetString(playerid, NDP_PlayerTextdraw[playerid][0], main_string);
}

public OnPlayerConnect(playerid) {
    pDrunkLevelLast[playerid] = 0;
    pFPS[playerid] = 0;

    #if defined NDP_OnPlayerConnect
        return NDP_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect NDP_OnPlayerConnect
#if defined NDP_OnPlayerConnect
    forward NDP_OnPlayerConnect(playerid);
#endif
 

public OnPlayerUpdate(playerid) {
    new drunknew = GetPlayerDrunkLevel(playerid);

    if (drunknew < 100) {
        SetPlayerDrunkLevel(playerid, 2000);
    } else {
        if (pDrunkLevelLast[playerid] != drunknew) {
            new wfps = pDrunkLevelLast[playerid] - drunknew;
            
            if ((wfps > 0) && (wfps < 800)) {
                pFPS[playerid] = wfps;
            }

            pDrunkLevelLast[playerid] = drunknew;
        }
    }

    #if defined NDP_OnPlayerUpdate
        return NDP_OnPlayerUpdate(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate NDP_OnPlayerUpdate
#if defined NDP_OnPlayerUpdate
    forward NDP_OnPlayerUpdate(playerid);
#endif

stock GetPlayerFPS(playerid) {
    return pFPS[playerid];
}