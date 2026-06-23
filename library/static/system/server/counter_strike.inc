#define COLOR_CS_ERROR 				0xFA5032FF

#define LOBBY_PLAYER_INTERIOR 		1
#define LOBBY_PLAYER_WORLDID 		85

#define CS_PLAYER_INTERIOR 			3
#define CS_PLAYER_WORLDID 			86

#define COUNTER_STRIKE_TIME_LOBBY	1 * 60 + 15

#define COUNTER_STRIKE_TIME_PLAY	10 * 60

#define CSTEAM_NONE					0
#define CSTEAM_T					1
#define CSTEAM_CT					2

// -----------------------------------------------

static CS_START_NONE = 0;
static CS_START_LOBBY = 1;
static CS_START_PLAYING = 2;

static JOINED_LOBBY = 1;
static PLAYING = 2;

// -----------------------------------------------

static
	InCounterStrike[MAX_PLAYERS]
;

// -----------------------------------------------

stock bool: IsPlayerInCounterStrike(playerid) return (InCounterStrike[playerid] == PLAYING ? true : false);
stock bool: IsPlayerInCounterStrikeLobby(playerid) return (InCounterStrike[playerid] == JOINED_LOBBY ? true : false);

forward ReturnPlayerInCounterStrike(playerid);
public ReturnPlayerInCounterStrike(playerid) return InCounterStrike[playerid];

// -----------------------------------------------

static
	CounterStrikeStatus,
	CounterStrikeTimeStart,
	CounterStrikeTimePlaying,
	CounterStrikeTeamKills[3],

	WhoStartedEvent[MAX_PLAYER_NAME],

	Team,
	Text:CounterStrikeTD[8],
	Text:CounterStrikeStartCountdownTD[1],
	PlayerText:PlayerCounterStrikeTD[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...},
	PlayerTeam[MAX_PLAYERS],
	CounterStrikeTDColorChange,
	PlayerKills[MAX_PLAYERS],
	PlayerDeaths[MAX_PLAYERS],
	HideDeathTDTime[MAX_PLAYERS],

	WeaponShopBriefcases[2] = {-1, ...},

	PlayerWeapon_AK47[MAX_PLAYERS],
	PlayerWeapon_PISTOL[MAX_PLAYERS],

	PlayersJoinedInCS_Count,
	PlayersJoinedInCounterStrike[MAX_PLAYERS][MAX_PLAYER_NAME],
	PlayersJoinedInCS_Team[MAX_PLAYERS],
	PlayerBackToEvent[MAX_PLAYERS],

	PlayerFreezeLoadMode[MAX_PLAYERS],
	StopMusicSoundPlayer[MAX_PLAYERS]
;

static
	Float:LobbyCoords[23][4] = {
		{1413.5814,-45.2633,1000.9229,85.4706}, // 1
		{1413.8350,-36.4039,1000.9250,89.2306}, // 2
		{1414.7025,-23.9475,1000.9254,89.0622}, // 3 
		{1413.2531,-12.0141,1000.9247,82.3372}, // 4
		{1413.8951,0.7943,1000.9250,101.4507}, // 5
		{1402.8209,2.8753,1000.9096,177.3506}, // 6
		{1386.4076,2.7047,1000.9173,176.4106}, // 7
		{1374.7223,2.7926,1000.9153,178.6039}, // 8
		{1364.5891,2.5823,1000.9219,178.9173}, // 9
		{1363.0305,-10.5737,1000.9219,269.1581}, // 10
		{1362.6133,-21.6494,1000.9219,267.9048}, // 11
		{1362.3015,-32.3619,1000.9219,268.8448}, // 12
		{1363.4812,-44.5827,1000.9188,272.2190}, // 13
		{1374.6301,-45.6859,1000.9180,1.2790}, // 14
		{1386.5151,-45.5356,1000.9242,1.9057}, // 15
		{1396.7114,-45.3084,1000.9213,358.1456}, // 16
		{1407.5386,-45.5380,1000.9181,358.7723}, // 17
		{1402.8590,-36.5805,1000.9108,359.0131}, // 18
		{1388.7334,-36.9821,1000.9128,3.0140}, // 19
		{1378.1526,-25.3441,1000.9258,268.7723}, // 20
		{1380.1213,-13.1145,1000.9249,269.0856}, // 21
		{1390.5604,-6.1541,1000.9119,175.7114}, // 22
		{1404.8378,-8.3865,1000.9127,177.9048} // 23
	}, 

	LobbyCoordsOrder;

// -----------------------------------------------

static 
	Float:CS_T_Coords[][4] = 
	{
		{589.2326,3668.9377,99.5809,265.6385}, //pos team Terrorists 1
		{587.7192,3671.2109,99.5813,264.1443}, //pos team Terrorists 1
		{591.2610,3671.3416,99.5813,268.6035}, //pos team Terrorists 1
		{589.5463,3674.0129,99.5813,266.5785}, //pos team Terrorists 1
		{592.4147,3673.9978,99.5813,269.7119}, //pos team Terrorists 1
		{589.2497,3676.7007,99.5813,269.7119}, //pos team Terrorists 1
		{592.2634,3676.6846,99.5813,269.7119}, //pos team Terrorists 1
		{588.1041,3679.4209,99.5813,267.5185}, //pos team Terrorists 1
		{591.5587,3679.2710,99.5813,267.5185}, //pos team Terrorists 1
		{587.8035,3682.8616,99.5813,266.2652}, //pos team Terrorists 1
		{591.3842,3682.6731,99.5813,267.2052}, //pos team Terrorists 1
		{587.7468,3685.8838,99.5813,267.5185}, //pos team Terrorists 1
		{591.5208,3685.8333,99.5813,269.2536}, //pos team Terrorists 1
		{588.1591,3689.1433,99.5813,266.8919}, //pos team Terrorists 1
		{590.3246,3688.4487,99.5813,266.8919}, //pos team Terrorists 1
		{593.5898,3667.2007,99.5813,247.6579} //pos team Terrorists 1
	},

	Float:CS_CT_Coords[][4] = 
	{
		{683.9051,3660.8259,97.8204,358.1709}, //pos team Counter Terrorists 1
		{683.9113,3663.6426,97.8204,357.5443}, //pos team Counter Terrorists 1
		{685.4918,3661.9385,97.8204,357.5443}, //pos team Counter Terrorists 1
		{687.2343,3659.8215,97.8204,357.5443}, //pos team Counter Terrorists 1
		{687.6646,3663.2754,97.8204,357.5443}, //pos team Counter Terrorists 1
		{688.3470,3667.5837,97.2588,357.5443}, //pos team Counter Terrorists 1
		{685.9749,3668.9587,96.7584,357.5443}, //pos team Counter Terrorists 1
		{683.3701,3667.0823,97.4413,357.5443}, //pos team Counter Terrorists 1
		{687.9443,3673.1357,95.8264,350.9642}, //pos team Counter Terrorists 1
		{684.1944,3673.1687,95.8264,13.5244}, //pos team Counter Terrorists 1
		{690.4285,3665.0107,97.8204,352.8443}, //pos team Counter Terrorists 1
		{691.5143,3677.3040,95.8264,88.7252}, //pos team Counter Terrorists 1
		{688.6176,3679.6206,95.8264,88.7252}, //pos team Counter Terrorists 1
		{686.4390,3678.1809,95.8264,88.7252}, //pos team Counter Terrorists 1
		{685.4995,3675.9692,95.8264,88.7252}, //pos team Counter Terrorists 1
		{679.2043,3676.3289,95.8264,91.2319}, //pos team Counter Terrorists 1
		{679.2972,3679.1753,95.8264,91.5452} //pos team Counter Terrorists 1
	},

	CSCoordsOrder[2];

// -----------------------------------------------

static
	MenuWeaponShopPrices[5] = {
		600, //M4
		300, //Deagle
		700, //UZI
		250, //Grenade
		100 //Armour
	};

// -----------------------------------------------

static enum _player_pos_backs_enum
{
	Float:PosBack[4],
	InteriorBack,
	WorldBack,
	BizEnterBack,
	HouseEnterBack,
    Float: HealthBack,
    Float: ArmourBack
}

static
	PlayerBackPositionData[MAX_PLAYERS][_player_pos_backs_enum];

// -----------------------------------------------

CounterStrikeInit()
{
	LoadCounterStrikeTextdraws();

	// CS Lobby Map Interior
	new g_Object[6];
	g_Object[0] = CreateDynamicObject(14795, 1388.8828, -20.8827, 1159.2181, 0.0000, 0.0000, 0.0000, .interiorid = LOBBY_PLAYER_INTERIOR, .worldid = LOBBY_PLAYER_WORLDID, .priority = 1); //no comment
	SetDynamicObjectMaterial(g_Object[0], 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	SetDynamicObjectMaterial(g_Object[0], 1, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	SetDynamicObjectMaterial(g_Object[0], 5, 10101, "2notherbuildsfe", "sl_vicbrikwall01", 0x00000000);
	SetDynamicObjectMaterial(g_Object[0], 10, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	SetDynamicObjectMaterial(g_Object[0], 14, 9514, "711_sfw", "beachwall_law", 0x00000000);
	g_Object[1] = CreateDynamicObject(18753, 1374.1435, -50.0013, 1165.0882, 0.0000, 0.0000, 0.0000, .interiorid = LOBBY_PLAYER_INTERIOR, .worldid = LOBBY_PLAYER_WORLDID); //no comment
	SetDynamicObjectMaterial(g_Object[1], 0, 14668, "711c", "gun_ceiling1128", 0x00000000);
	g_Object[2] = CreateDynamicObject(19447, 1419.2384, -49.3358, 1155.6457, 90.0000, 0.0000, 90.0000, .interiorid = LOBBY_PLAYER_INTERIOR, .worldid = LOBBY_PLAYER_WORLDID); //no comment
	SetDynamicObjectMaterial(g_Object[2], 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	g_Object[3] = CreateDynamicObject(19447, 1417.9041, 7.5895, 1162.6203, 0.0000, 0.0000, -90.0000, .interiorid = LOBBY_PLAYER_INTERIOR, .worldid = LOBBY_PLAYER_WORLDID); //no comment
	SetDynamicObjectMaterial(g_Object[3], 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	g_Object[4] = CreateDynamicObject(19447, 1396.8140, 9.2501, 1154.9635, 90.0000, 0.0000, 0.0000, .interiorid = LOBBY_PLAYER_INTERIOR, .worldid = LOBBY_PLAYER_WORLDID); //no comment
	SetDynamicObjectMaterial(g_Object[4], 0, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
	g_Object[5] = CreateDynamicObject(18753, 1373.8526, -49.3502, 1153.4855, 0.0000, 0.0000, 0.0000, .interiorid = LOBBY_PLAYER_INTERIOR, .worldid = LOBBY_PLAYER_WORLDID); //no comment
	SetDynamicObjectMaterial(g_Object[5], 0, 10101, "2notherbuildsfe", "sl_vicbrikwall01", 0x00000000);

	//Author
	g_Object[1] = CreateDynamicObject(19175, 1419.5800, 5.7280, 1163.4639, 0.0000, 0.0000, -90.1999); //SAMPPicture4
	SetDynamicObjectMaterialText(g_Object[1], 0, "Counter Strike", OBJECT_MATERIAL_SIZE_256x128, "Arial", 24, 1, 0xFFFFFFFF, 0x00000000, 0);
	SetDynamicObjectMaterialText(g_Object[1], 1, ".",  OBJECT_MATERIAL_SIZE_256x128, "Arial", 24, 1, 0xFFFFFFFF, 0x00000000, 0);
	g_Object[3] = CreateDynamicObject(19175, 1419.5787, 5.4280, 1163.2038, 0.0000, 0.0000, -90.1999); //SAMPPicture4
	SetDynamicObjectMaterialText(g_Object[3], 0, "Mihan Role Play", OBJECT_MATERIAL_SIZE_256x128, "Arial", 15, 1, 0xFF327BCD, 0x00000000, 0);
	SetDynamicObjectMaterialText(g_Object[3], 1, ".",  OBJECT_MATERIAL_SIZE_256x128, "Arial", 24, 1, 0xFFFFFFFF, 0x00000000, 0);
	g_Object[4] = CreateDynamicObject(19175, 1419.5783, 5.2880, 1163.0231, 0.0000, 0.0000, -90.1999); //SAMPPicture4
	SetDynamicObjectMaterialText(g_Object[4], 0, "- On Top -", OBJECT_MATERIAL_SIZE_256x128, "Arial", 14, 1, 0xFFFFE4E1, 0x00000000, 0);
	SetDynamicObjectMaterialText(g_Object[4], 1, ".",  OBJECT_MATERIAL_SIZE_256x128, "Arial", 24, 1, 0xFFFFFFFF, 0x00000000, 0);
}

// -----------------------------------------------

CounterStrikePlayerConnect(playerid)
{
	for(new _player_pos_backs_enum:i; i < _player_pos_backs_enum; i++) PlayerBackPositionData[playerid][i] = 0;

	if(CounterStrikeStatus == CS_START_PLAYING && PlayersJoinedInCS_Count > 0) {
		for(new i; i < PlayersJoinedInCS_Count; i++) {
			if(!strcmp(PlayersJoinedInCounterStrike[i], Name(playerid), true))
			{
				//Agar bazikon toye counter bod va az bazi dis shod va dobare omad server dobare biad event
				InCounterStrike[playerid] = PLAYING;
				PlayerTeam[playerid] = PlayersJoinedInCS_Team[i];
				PlayerBackToEvent[playerid] = 1;
				break;
			}
		}
	}
}

// -----------------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	DestroyCounterStrikePlayerTDs(playerid);
	// LeavePlayerFromCounterStrike(playerid);

	#if defined CounterStrike_OnPlayerDisconne
		return CounterStrike_OnPlayerDisconne(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect CounterStrike_OnPlayerDisconne
#if defined CounterStrike_OnPlayerDisconne
	forward CounterStrike_OnPlayerDisconne(playerid, reason);
#endif

// -----------------------------------------------

LeavePlayerFromCounterStrike(playerid)
{
	InCounterStrike[playerid] = 0;
	PlayerTeam[playerid] = 0;
	PlayerBackToEvent[playerid] = 0;
}

// -----------------------------------------------

CounterStrikePlayerSpawn(playerid)
{
	if(IsPlayerInCounterStrike(playerid))
	{
		SendPlayerToCounterStrike(playerid);
		if(PlayerBackToEvent[playerid]) 
		{
			for(new td; td < sizeof(CounterStrikeTD); td++) {
				TextDrawShowForPlayer(playerid, CounterStrikeTD[td]);
			}
			PlayerBackToEvent[playerid] = 0;
			set_health(playerid, 100.0);
		}
		return 1;
	}

	return 0;
}

// -----------------------------------------------

static CS_SendDeathMessage(playerid, killerid, weapon)
{
    foreach(new i : Player)
    {
        if(IsPlayerInCounterStrike(i))
        {
            SendDeathMessageToPlayer(i, killerid, playerid, weapon);
        }
    }
}

// -----------------------------------------------

CounterStrikePlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerInCounterStrikeLobby(playerid)) {
		InCounterStrike[playerid] = 0;
		return 1;
	}

	if(killerid != INVALID_PLAYER_ID)
	{
		if(IsPlayerInCounterStrike(killerid))
		{
			new 
				string[64];

			CS_SendDeathMessage(playerid, killerid, reason);

			if(PlayerTeam[killerid] == PlayerTeam[playerid])
			{
				format(string, sizeof string, "~w~Teammate ~r~~h~%s ~w~Killed You", Name(killerid));
				PlayerTextDrawSetString(playerid, PlayerCounterStrikeTD[playerid], string);
				PlayerTextDrawShow(playerid, PlayerCounterStrikeTD[playerid]);
				HideDeathTDTime[playerid] = 5;

				format(string, sizeof string, "~w~You Killed Teammate~r~~h~%s", Name(playerid));
				PlayerTextDrawSetString(killerid, PlayerCounterStrikeTD[killerid], string);
				PlayerTextDrawShow(killerid, PlayerCounterStrikeTD[killerid]);
				HideDeathTDTime[killerid] = 5;
			}
			else
			{

				CS_SendDeathMessage(playerid, killerid, reason);

				PlayerPlaySound(killerid, 6401, 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 5202, 0.0, 0.0, 0.0);

				PlayerDeaths[playerid]++;
				PlayerKills[killerid]++;

				format(string, sizeof string, "~r~~h~%s ~w~Killed You~n~~r~%d Deaths", Name(killerid), PlayerDeaths[playerid]);
				PlayerTextDrawSetString(playerid, PlayerCounterStrikeTD[playerid], string);
				PlayerTextDrawShow(playerid, PlayerCounterStrikeTD[playerid]);
				HideDeathTDTime[playerid] = 5;

				format(string, sizeof string, "~w~You Killed ~r~~h~%s~n~~r~%d Kills", Name(playerid), PlayerKills[killerid]);
				PlayerTextDrawSetString(killerid, PlayerCounterStrikeTD[killerid], string);
				PlayerTextDrawShow(killerid, PlayerCounterStrikeTD[killerid]);
				HideDeathTDTime[killerid] = 5;

				CounterStrikeTeamKills[PlayerTeam[killerid]]++;

				if(PlayerTeam[killerid] == CSTEAM_CT)
				{
					format(string, 32, "C. Terrorist~n~%d Kills", CounterStrikeTeamKills[PlayerTeam[killerid]]);
					TextDrawSetString(CounterStrikeTD[2], string);
				}
				else if(PlayerTeam[killerid] == CSTEAM_T)
				{
					format(string, 32, "Terrorist~n~%d Kills", CounterStrikeTeamKills[PlayerTeam[killerid]]);
					TextDrawSetString(CounterStrikeTD[4], string);
				}
			}
		}
	}

	return 1;
}

// -----------------------------------------------

static ShowWeaponShopMenuForPlayer(playerid)
{
	new 
		info[280];

	format(info, sizeof info, "M4\t{%s}$%d\nDeagle\t{%s}$%d\nUZI\t{%s}$%d\nGrenade\t{%s}$%d\n",  //Armour\t{%s}$%d\n
		(PlayerInfo[playerid][money] > MenuWeaponShopPrices[0] ? "00BB00" : "FFFFFF"), MenuWeaponShopPrices[0],
		(PlayerInfo[playerid][money] > MenuWeaponShopPrices[1] ? "00BB00" : "FFFFFF"), MenuWeaponShopPrices[1],
		(PlayerInfo[playerid][money] > MenuWeaponShopPrices[2] ? "00BB00" : "FFFFFF"), MenuWeaponShopPrices[2],
		(PlayerInfo[playerid][money] > MenuWeaponShopPrices[3] ? "00BB00" : "FFFFFF"), MenuWeaponShopPrices[3],
		(PlayerInfo[playerid][money] > MenuWeaponShopPrices[4] ? "00BB00" : "FFFFFF"), MenuWeaponShopPrices[4]);

	show_dialog(playerid, DIALOG_CS_GUNSHOP, DIALOG_STYLE_TABLIST, "Weapon Shop", info, "Buy", "Cancel");
}

// -----------------------------------------------

CounterStrikePickDynamicPickup(playerid, pickupid)
{
	if(pickupid == WeaponShopBriefcases[0])
	{
		if(PlayerTeam[playerid] == CSTEAM_T) ShowWeaponShopMenuForPlayer(playerid);
		return 1;
	}
	if(pickupid == WeaponShopBriefcases[1])
	{
		if(PlayerTeam[playerid] == CSTEAM_CT) ShowWeaponShopMenuForPlayer(playerid);
		return 1;
	}
	return 0;
}

// -----------------------------------------------

CounterStrikeDialogResponse(playerid, dialogid, response, listitem)
{
	if(dialogid == DIALOG_CS_GUNSHOP) 
	{
		if(!response) {
			return 1;
		}

		if(PlayerInfo[playerid][money] < MenuWeaponShopPrices[listitem]) 
		{
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0); //SOUND_ROULETTE_NO_CASH
		}
		else
		{
			switch(listitem)
			{
				case 0: {
					if(PlayerWeapon_AK47[playerid] == WEAPON_M4) {
						PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0); //SOUND_SHOP_BUY_DENIED
						ShowWeaponShopMenuForPlayer(playerid);
						return 1;
					}
					GivePlayerWeapon(playerid, WEAPON_M4, 250);
					PlayerWeapon_AK47[playerid] = WEAPON_M4;
				}
				case 1: {
					if(PlayerWeapon_PISTOL[playerid] == WEAPON_DEAGLE) {
						PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0); //SOUND_SHOP_BUY_DENIED
						ShowWeaponShopMenuForPlayer(playerid);
						return 1;
					}
					GivePlayerWeapon(playerid, WEAPON_DEAGLE, 250);
					PlayerWeapon_PISTOL[playerid] = WEAPON_DEAGLE;
				}
				case 2: {
					if(PlayerWeapon_AK47[playerid] == WEAPON_UZI) {
						PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0); //SOUND_SHOP_BUY_DENIED
						ShowWeaponShopMenuForPlayer(playerid);
						return 1;
					}
					GivePlayerWeapon(playerid, WEAPON_UZI, 250);
					PlayerWeapon_AK47[playerid] = WEAPON_UZI;
				}
				case 3: {
					new weapons, ammo;
					GetPlayerWeaponData(playerid, 8, weapons, ammo);
					if(weapons == WEAPON_GRENADE) {
						PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0); //SOUND_SHOP_BUY_DENIED
						ShowWeaponShopMenuForPlayer(playerid);
						return 1;
					}
					GivePlayerWeapon(playerid, WEAPON_GRENADE, 1);
				}
				case 4: {
					set_armour(playerid, 100.0);
				}
			}

			PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0); //SOUND_ROULETTE_NO_CASH
			give_money(playerid, -MenuWeaponShopPrices[listitem]);

		}

		ShowWeaponShopMenuForPlayer(playerid);
		return 1;
	}
	return 0;
}

// -----------------------------------------------

static EndCounterStrike()
{
	CounterStrikeStatus = CS_START_NONE;
	CounterStrikeTimePlaying = 0;
	CounterStrikeTimeStart = 0;

	if(PlayersJoinedInCS_Count > 0)
	{
		for(new i; i < PlayersJoinedInCS_Count; i++) 
		{
			PlayersJoinedInCounterStrike[i][0] = EOS;
		}
		PlayersJoinedInCS_Count = 0;
	}

	if(WeaponShopBriefcases[0] != -1) {
		DestroyDynamicPickup(WeaponShopBriefcases[0]);
		WeaponShopBriefcases[0] = -1;
	}
	if(WeaponShopBriefcases[1] != -1) {
		DestroyDynamicPickup(WeaponShopBriefcases[1]);
		WeaponShopBriefcases[1] = -1;
	}

	new
		winner,
		prize;

	if(CounterStrikeTeamKills[CSTEAM_T] > CounterStrikeTeamKills[CSTEAM_CT]) {
		winner = CSTEAM_T;
		prize = CounterStrikeTeamKills[CSTEAM_T] * 40;
	} 
	else {
		winner = CSTEAM_CT;
		prize = CounterStrikeTeamKills[CSTEAM_CT] * 40;
	}

	if(CounterStrikeTeamKills[CSTEAM_T] == CounterStrikeTeamKills[CSTEAM_CT]) {
		winner = CSTEAM_NONE;
	}

	new 
		string[128];

	SendClientMessageToAll(0xFFFF00FF, "------------------| {FF7900}Counter Strike {FFFF00}|------------------");

	if(winner == CSTEAM_T) {
		SendClientMessageToAll(0xFFFF00FF, "Team {FF0000}Terrorists {FFFF00}Barande Event Shod!");
		format(string, sizeof string, "KILLS : %d | PRIZE : +%d$", CounterStrikeTeamKills[CSTEAM_T], prize);
	}
	else if(winner == CSTEAM_CT) {
		SendClientMessageToAll(0xFFFF00FF, "Team {0000FF}Counter Terrorists {FFFF00}Barande Event Shod!");
		format(string, sizeof string, "KILLS : %d | PRIZE : +%d$", CounterStrikeTeamKills[CSTEAM_CT], prize);
	} 
	else if(winner == CSTEAM_NONE) {
		SendClientMessageToAll(0xFFFF00FF, "Hich Teami {FFFF00}Barande Event Nashod!");
		format(string, sizeof string, "{FF0000}TERRORISTS {FFFF00}KILLS : %d | {0000FF}COUNTER TERRORISTS {FFFF00}KILLS : %d", CounterStrikeTeamKills[CSTEAM_T], CounterStrikeTeamKills[CSTEAM_CT]);
	}

	SendClientMessageToAll(0xFFFF00FF, string);

	foreach(new i : Player)
	{
		if(!IsPlayerInCounterStrike(i)) continue;

		if(PlayerTeam[i] == winner) {
			PlayerPlaySound(i, 1097, 0.0, 0.0, 0.0);
			give_money(i, prize);
		} 
		else {
			PlayerPlaySound(i, 1187, 0.0, 0.0, 0.0);
		}

		StopMusicSoundPlayer[i] = 10;

		EndCounterStrikeForPlayer(i);
	}
}

// -----------------------------------------------

static EndCounterStrikeForPlayer(playerid)
{
	InCounterStrike[playerid] = 0;
	PlayerTeam[playerid] = 0;

    for(new td; td < sizeof(CounterStrikeTD); td++) {
		TextDrawHideForPlayer(playerid, CounterStrikeTD[td]);
	}
	PlayerTextDrawHide(playerid, PlayerCounterStrikeTD[playerid]);
	HideDeathTDTime[playerid] = 0;

	TextDrawHideForPlayer(playerid, CounterStrikeStartCountdownTD[0]);

	ResetPlayerWeapons(playerid);

	if (is_fraction_duty {playerid} == 1) 
	{
		SetPlayerColor(playerid, f_info[PlayerInfo[playerid][member]][f_radar_color]);
	}
	else 
	{
		SetPlayerColor(playerid, 0xFFFFFF80);
	}

	// Pak Kardan List Kills/Deaths (Clear Death List)
	for(new i = 1; i < 7; i++)
    {
        SendDeathMessageToPlayer(playerid, INVALID_PLAYER_ID, 100, WEAPON_BAT);
    }

	if(PlayerBackPositionData[playerid][HealthBack] == 0.0) {
		SpawnPlayer(playerid);

		return 1;
	}
	else
	{
		texture_load_mode(playerid, 2000);
		p_t_info[playerid][business] = PlayerBackPositionData[playerid][BizEnterBack];
		p_t_info[playerid][house] = PlayerBackPositionData[playerid][HouseEnterBack];
		SetPlayerInterior(playerid, PlayerBackPositionData[playerid][InteriorBack]);
		SetPlayerVirtualWorld(playerid, PlayerBackPositionData[playerid][WorldBack]);
		SetPlayerPos(playerid, PlayerBackPositionData[playerid][PosBack][0], PlayerBackPositionData[playerid][PosBack][1], PlayerBackPositionData[playerid][PosBack][2]);
		SetPlayerFacingAngle(playerid, PlayerBackPositionData[playerid][PosBack][3]);
		set_health(playerid, PlayerBackPositionData[playerid][HealthBack]);
	    set_armour(playerid, PlayerBackPositionData[playerid][ArmourBack]);
	    give_player_save_weapon(playerid);
	}

    SetCameraBehindPlayer(playerid);

    /* Previous Skin */
    SetPlayerSkin(playerid, PlayerInfo[playerid][skin]);

	return 1;
}

// -----------------------------------------------

CounterStrikeTimer() //one second timer
{
	if(CounterStrikeStatus == CS_START_PLAYING)
	{
		if(CounterStrikeTimePlaying == 1)
		{
			EndCounterStrike();
		}
		else
		{
			new
				string[32],
				time = CounterStrikeTimePlaying;

			CounterStrikeTimePlaying--;

			format(string, sizeof string, "Time : ~w~%d:%02d", time / 60, time % 60);
			TextDrawSetString(CounterStrikeTD[6], string);

			// -----------------------------------------------------------

			CounterStrikeTDColorChange = !CounterStrikeTDColorChange;
			if(CounterStrikeTDColorChange) 
				TextDrawBackgroundColor(CounterStrikeTD[7], 0x3E3EFFFF);
			else 
				TextDrawBackgroundColor(CounterStrikeTD[7], -16776961);

			new 
				teams_count[3];

			foreach(new i : Player)
			{
				if(IsPlayerInCounterStrike(i)) 
				{
					TextDrawShowForPlayer(i, CounterStrikeTD[7]); //Reshow the textdraw
					teams_count[PlayerTeam[i]]++;
				}
			}

			if(teams_count[CSTEAM_T] == 0 || teams_count[CSTEAM_CT] == 0) EndCounterStrike();
		}
	}
	else if(CounterStrikeStatus == CS_START_LOBBY)
	{
		if(CounterStrikeTimeStart == 1)
		{
			CounterStrikeTimeStart = 0;
			CounterStrikeTimePlaying = COUNTER_STRIKE_TIME_PLAY;
			CounterStrikeStatus = CS_START_PLAYING;

			foreach(new i : Player)
			{
				if(IsPlayerInCounterStrike(i)) 
				{
					PlayerPlaySound(i, 3201, 0.0, 0.0, 0.0);
					TextDrawHideForPlayer(i, CounterStrikeStartCountdownTD[0]);

					//pTemp[i][FreezedByAdmin] = 0;
					TogglePlayerControllable(i, 1);
				}
			}
		}
		else
		{
			CounterStrikeTimeStart--;

			if(CounterStrikeTimeStart == 5)
			{
				new 
					any_player;

				/*new
					playerids_team_t[MAX_PLAYERS],
					playerids_team_t_count,

					playerids_team_ct[MAX_PLAYERS],
					playerids_team_ct_count;*/

				foreach(new i : Player)
				{
					if(IsPlayerInCounterStrikeLobby(i)) 
					{
						TogglePlayerControllable(i, 0);
						//pTemp[i][FreezedByAdmin] = 1;

						InCounterStrike[i] = PLAYING;

						Team = !Team;
						PlayerTeam[i] = Team + 1;

						/*if(PlayerTeam[i] == CSTEAM_T) {
							playerids_team_t[playerids_team_t_count] = i;
							playerids_team_t_count++;
						} else {
							playerids_team_ct[playerids_team_ct_count] = i;
							playerids_team_ct_count++;
						}*/

						PlayersJoinedInCounterStrike[i][0] = EOS;
						strcat(PlayersJoinedInCounterStrike[i], Name(i), MAX_PLAYER_NAME);

						PlayersJoinedInCS_Team[PlayersJoinedInCS_Count] = PlayerTeam[i];
						PlayersJoinedInCS_Count++;

						for(new td; td < sizeof(CounterStrikeTD); td++) {
							TextDrawShowForPlayer(i, CounterStrikeTD[td]);
						}

						SendPlayerToCounterStrike(i);

						any_player++;
					}
				}

				if(any_player != 0) 
				{
					// WeaponShopBriefcases[0] = CreateDynamicPickupEx(1210, 2, 585.8329,3675.8000,99.5813, .players = playerids_team_t);
					// WeaponShopBriefcases[1] = CreateDynamicPickupEx(1210, 2, 691.2806,3660.6628,97.8204, .players = playerids_team_ct);
					WeaponShopBriefcases[0] = CreateDynamicPickup(1210, 2, 585.8329,3675.8000,99.5813);
					WeaponShopBriefcases[1] = CreateDynamicPickup(1210, 2, 691.2806,3660.6628,97.8204);
				}
				else {
					EndCounterStrike();
				}
			}

			new
				string[64],
				time = CounterStrikeTimeStart;

			format(string, sizeof string, "Counter Strike~n~~r~~h~~h~~h~~h~Start: %02d:%02d", time / 60, time % 60);
			TextDrawSetString(CounterStrikeStartCountdownTD[0], string);
		}
	}

}

// -----------------------------------------------

CounterStrikePlayerTimer(playerid) //one second timer
{
	if(PlayerFreezeLoadMode[playerid] >= 2) PlayerFreezeLoadMode[playerid]--;
	if(PlayerFreezeLoadMode[playerid] == 1)
	{
		PlayerFreezeLoadMode[playerid] = 0;
		TogglePlayerControllable(playerid, 1);
	}

	if(StopMusicSoundPlayer[playerid] >= 2) StopMusicSoundPlayer[playerid]--;
	if(StopMusicSoundPlayer[playerid] == 1)
	{
		StopMusicSoundPlayer[playerid] = 0;
		PlayerPlaySound(playerid, 1098, 0.0, 0.0, 0.0);
	}

	if(IsPlayerInCounterStrike(playerid))
	{
		if(HideDeathTDTime[playerid] >= 2) HideDeathTDTime[playerid]--;
		if(HideDeathTDTime[playerid] == 1) {
			HideDeathTDTime[playerid] = 0;
			PlayerTextDrawHide(playerid, PlayerCounterStrikeTD[playerid]);
		}
	}
}

// -----------------------------------------------

stock CounterStrikePlayerTakeDMG(playerid, issuerid)
{
	#pragma unused issuerid

	if(PlayerFreezeLoadMode[playerid] > 0) // Prevent Spawn Kill
		return 0;

	return 1;
}

// -----------------------------------------------

CMD:cs(playerid, params[])
{
	if(IsPlayerInCounterStrikeLobby(playerid))
		return SendClientMessage(playerid, COLOR_CS_ERROR, "Shoma Ghablan Be Lobby Vared Shode'id.");
	
	if(IsPlayerInCounterStrike(playerid))
		return 1;

	if(CounterStrikeStatus == CS_START_NONE)
		return SendClientMessage(playerid, COLOR_CS_ERROR, "Event Counter Strike Start Nashode Ast.");

	if(CounterStrikeStatus == CS_START_PLAYING)
		return SendClientMessage(playerid, COLOR_CS_ERROR, "Event Counter Strike Shoro Shod Digar Nemitavanid Vared Shavid.");

	PlayerBackPositionData[playerid][BizEnterBack] = p_t_info[playerid][business];
	PlayerBackPositionData[playerid][HouseEnterBack] = p_t_info[playerid][house];
	PlayerBackPositionData[playerid][InteriorBack] = GetPlayerInterior(playerid);
	PlayerBackPositionData[playerid][WorldBack] = GetPlayerVirtualWorld(playerid);
	GetPlayerPos(playerid, PlayerBackPositionData[playerid][PosBack][0], PlayerBackPositionData[playerid][PosBack][1], PlayerBackPositionData[playerid][PosBack][2]);
	GetPlayerFacingAngle(playerid, PlayerBackPositionData[playerid][PosBack][3]);
    GetPlayerHealth(playerid, PlayerBackPositionData[playerid][HealthBack]);
    GetPlayerArmour(playerid, PlayerBackPositionData[playerid][ArmourBack]);
	ResetPlayerWeapons(playerid);

	PlayerDeaths[playerid] = 0;
	PlayerKills[playerid] = 0;
	PlayerWeapon_AK47[playerid] = WEAPON_AK47;
	PlayerWeapon_PISTOL[playerid] = WEAPON_COLT45;

	LoadCounterStrikePlayerTDs(playerid);

	InCounterStrike[playerid] = JOINED_LOBBY;

	SendPlayerToLobby(playerid);
	return 1;
}

// -----------------------------------------------

//CMD:exit(playerid, params[]) {
CommandExitForCounterStrike(playerid) {
	if(IsPlayerInCS(playerid))
	{
		EndCounterStrikeForPlayer(playerid);
		return 1;
	}

	return 0;
}

// -----------------------------------------------

CMD:startcs(playerid, params[])
{
	if(ReturnPlayerAdminLevel(playerid) < 7)
		return 1;

	new string[300];

	if(CounterStrikeStatus != CS_START_NONE) {
		format(string, sizeof string, "Event Counter Strike Ghablan Tavasote %s Start Shode Ast.", WhoStartedEvent);
		return SendClientMessage(playerid, COLOR_CS_ERROR, string);
	}

	WhoStartedEvent[0] = EOS;
	strcat(WhoStartedEvent, Name(playerid), MAX_PLAYER_NAME);

    format(string,sizeof(string), ""c_server"[Event]"c_white" Admin %s Yek Event 'Counter Strike' Bargozar Kard. Had Aksar Player Baraye in event: 100 Nafar", PlayerInfo[playerid][name]);
    SendClientMessageToAll(col_gray,string);

    SendClientMessageToAll(col_gray, ""c_server"[Event]"c_white" Baraye vared shodan be event dastor /cs ra vared konid.");

	foreach(new i : Player) {
		GameTextForPlayer(i, "~y~~h~Counter Strike~n~~r~~h~~h~~h~~h~/CS", 6000, 3);
		PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
	}

	CounterStrikeStatus = CS_START_LOBBY;
	CounterStrikeTimeStart = COUNTER_STRIKE_TIME_LOBBY;
	CounterStrikeTimePlaying = COUNTER_STRIKE_TIME_PLAY;
	LobbyCoordsOrder = 0;
	CSCoordsOrder[0] = 0;
	CSCoordsOrder[1] = 0;
	CounterStrikeTeamKills[CSTEAM_T] = 0;
	CounterStrikeTeamKills[CSTEAM_CT] = 0;

	TextDrawSetString(CounterStrikeTD[4], "Terrorist~n~0 Kills");
	TextDrawSetString(CounterStrikeTD[2], "C. Terrorist~n~0 Kills");
	TextDrawSetString(CounterStrikeTD[6], "Time : ~w~10:00");
	return 1;
}

// -----------------------------------------------

static SendPlayerToLobby(playerid)
{
	texture_load_mode(playerid, 2000);

	SetPlayerInterior(playerid, LOBBY_PLAYER_INTERIOR);
	SetPlayerVirtualWorld(playerid, LOBBY_PLAYER_WORLDID);
	SetPlayerPos(playerid, LobbyCoords[LobbyCoordsOrder][0], LobbyCoords[LobbyCoordsOrder][1], 1154.9856); //LobbyCoords[LobbyCoordsOrder][2]
	SetPlayerFacingAngle(playerid, LobbyCoords[LobbyCoordsOrder][3]);

	SetCameraBehindPlayer(playerid);
	
	TextDrawShowForPlayer(playerid, CounterStrikeStartCountdownTD[0]);

	LobbyCoordsOrder++;
	if(LobbyCoordsOrder == sizeof(LobbyCoords)) LobbyCoordsOrder = 0;
}

// -----------------------------------------------

static SendPlayerToCounterStrike(playerid)
{
	// if (PlayerInfo[playerid][settings][PACIFIST_MODE]) {
	// 	PacifistModeToggle(playerid, 0);
	// }

	new
		p_team = PlayerTeam[playerid] - 1;

	new
		order = CSCoordsOrder[p_team],
		size_of_array;

	SetPlayerInterior(playerid, CS_PLAYER_INTERIOR);
	SetPlayerVirtualWorld(playerid, CS_PLAYER_WORLDID);

	PlayerFreezeLoadMode[playerid] = 3;
	TogglePlayerControllable(playerid, 0);

	if(PlayerTeam[playerid] == CSTEAM_T)
	{
		SetPlayerSkin(playerid, 122);
		SetPlayerColor(playerid, 0xFF0000FF);
		SetPlayerPos(playerid, CS_T_Coords[order][0], CS_T_Coords[order][1], CS_T_Coords[order][2]);
		SetPlayerFacingAngle(playerid, CS_T_Coords[order][3]);
		size_of_array = sizeof(CS_T_Coords);
	}
	else
	{
		SetPlayerSkin(playerid, 124);
		SetPlayerColor(playerid, 0x3333FFFF);
		SetPlayerPos(playerid, CS_CT_Coords[order][0], CS_CT_Coords[order][1], CS_CT_Coords[order][2]);
		SetPlayerFacingAngle(playerid, CS_CT_Coords[order][3]);
		size_of_array = sizeof(CS_CT_Coords);
	}
	
	SetCameraBehindPlayer(playerid);

	GiveCounterStrikeWeapons(playerid);

	CSCoordsOrder[p_team]++;
	if(CSCoordsOrder[p_team] == size_of_array) CSCoordsOrder[p_team] = 0;
}

// -----------------------------------------------

static GiveCounterStrikeWeapons(playerid)
{
	GivePlayerWeapon(playerid, PlayerWeapon_AK47[playerid], 250);
	GivePlayerWeapon(playerid, PlayerWeapon_PISTOL[playerid], 250);
}

// -----------------------------------------------

static LoadCounterStrikePlayerTDs(playerid)
{
	if(PlayerCounterStrikeTD[playerid] == PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerCounterStrikeTD[playerid] = CreatePlayerTextDraw(playerid, 316.600524, 322.324218, "~r~~h~Test_Main ~w~Killed You~n~~r~5 Kills");
		PlayerTextDrawLetterSize(playerid, PlayerCounterStrikeTD[playerid], 0.283000, 1.083749);
		PlayerTextDrawTextSize(playerid, PlayerCounterStrikeTD[playerid], 0.000000, 678.000000);
		PlayerTextDrawAlignment(playerid, PlayerCounterStrikeTD[playerid], 2);
		PlayerTextDrawColor(playerid, PlayerCounterStrikeTD[playerid], -1);
		PlayerTextDrawSetShadow(playerid, PlayerCounterStrikeTD[playerid], 0);
		PlayerTextDrawSetOutline(playerid, PlayerCounterStrikeTD[playerid], 1);
		PlayerTextDrawBackgroundColor(playerid, PlayerCounterStrikeTD[playerid], 255);
		PlayerTextDrawFont(playerid, PlayerCounterStrikeTD[playerid], 1);
		PlayerTextDrawSetProportional(playerid, PlayerCounterStrikeTD[playerid], 1);
	}
}

static DestroyCounterStrikePlayerTDs(playerid)
{
	if(PlayerCounterStrikeTD[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PlayerCounterStrikeTD[playerid]);
		PlayerCounterStrikeTD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
}

// -----------------------------------------------

static LoadCounterStrikeTextdraws()
{
	CounterStrikeTD[0] = TextDrawCreate(22.399, 207.050, "box");
	TextDrawLetterSize(CounterStrikeTD[0], 0.000, 7.475);
	TextDrawTextSize(CounterStrikeTD[0], 147.399, 0.000);
	TextDrawAlignment(CounterStrikeTD[0], 1);
	TextDrawColor(CounterStrikeTD[0], -1);
	TextDrawUseBox(CounterStrikeTD[0], 1);
	TextDrawBoxColor(CounterStrikeTD[0], 150);
	TextDrawSetShadow(CounterStrikeTD[0], 0);
	TextDrawSetOutline(CounterStrikeTD[0], 0);
	TextDrawBackgroundColor(CounterStrikeTD[0], 255);
	TextDrawFont(CounterStrikeTD[0], 1);
	TextDrawSetProportional(CounterStrikeTD[0], 1);

	CounterStrikeTD[1] = TextDrawCreate(32.000, 244.250, "LD_TATT:8gun");
	TextDrawTextSize(CounterStrikeTD[1], 22.000, 19.000);
	TextDrawAlignment(CounterStrikeTD[1], 1);
	TextDrawColor(CounterStrikeTD[1], 757989375);
	TextDrawSetShadow(CounterStrikeTD[1], 0);
	TextDrawSetOutline(CounterStrikeTD[1], 0);
	TextDrawBackgroundColor(CounterStrikeTD[1], 255);
	TextDrawFont(CounterStrikeTD[1], 4);
	TextDrawSetProportional(CounterStrikeTD[1], 0);

	CounterStrikeTD[2] = TextDrawCreate(57.000, 242.500, "C. Terrorist~n~0 Kills");
	TextDrawLetterSize(CounterStrikeTD[2], 0.250, 1.127);
	TextDrawTextSize(CounterStrikeTD[2], 145.000, 0.000);
	TextDrawAlignment(CounterStrikeTD[2], 1);
	TextDrawColor(CounterStrikeTD[2], 757989375);
	TextDrawSetShadow(CounterStrikeTD[2], 2);
	TextDrawSetOutline(CounterStrikeTD[2], 0);
	TextDrawBackgroundColor(CounterStrikeTD[2], 255);
	TextDrawFont(CounterStrikeTD[2], 2);
	TextDrawSetProportional(CounterStrikeTD[2], 1);

	CounterStrikeTD[3] = TextDrawCreate(32.000, 216.349, "LD_TATT:8gun");
	TextDrawTextSize(CounterStrikeTD[3], 22.000, 19.000);
	TextDrawAlignment(CounterStrikeTD[3], 1);
	TextDrawColor(CounterStrikeTD[3], -16776961);
	TextDrawSetShadow(CounterStrikeTD[3], 0);
	TextDrawSetOutline(CounterStrikeTD[3], 0);
	TextDrawBackgroundColor(CounterStrikeTD[3], 255);
	TextDrawFont(CounterStrikeTD[3], 4);
	TextDrawSetProportional(CounterStrikeTD[3], 0);

	CounterStrikeTD[4] = TextDrawCreate(57.000, 214.500, "Terrorist~n~0 Kills");
	TextDrawLetterSize(CounterStrikeTD[4], 0.250, 1.127);
	TextDrawTextSize(CounterStrikeTD[4], 145.000, 0.000);
	TextDrawAlignment(CounterStrikeTD[4], 1);
	TextDrawColor(CounterStrikeTD[4], -16776961);
	TextDrawSetShadow(CounterStrikeTD[4], 2);
	TextDrawSetOutline(CounterStrikeTD[4], 0);
	TextDrawBackgroundColor(CounterStrikeTD[4], 255);
	TextDrawFont(CounterStrikeTD[4], 2);
	TextDrawSetProportional(CounterStrikeTD[4], 1);

	CounterStrikeTD[5] = TextDrawCreate(22.399, 187.148, "box");
	TextDrawLetterSize(CounterStrikeTD[5], 0.000, 1.786);
	TextDrawTextSize(CounterStrikeTD[5], 147.399, 0.000);
	TextDrawAlignment(CounterStrikeTD[5], 1);
	TextDrawColor(CounterStrikeTD[5], -1);
	TextDrawUseBox(CounterStrikeTD[5], 1);
	TextDrawBoxColor(CounterStrikeTD[5], 150);
	TextDrawSetShadow(CounterStrikeTD[5], 0);
	TextDrawSetOutline(CounterStrikeTD[5], 0);
	TextDrawBackgroundColor(CounterStrikeTD[5], 255);
	TextDrawFont(CounterStrikeTD[5], 1);
	TextDrawSetProportional(CounterStrikeTD[5], 1);

	CounterStrikeTD[6] = TextDrawCreate(45.199, 189.325, "Time : ~w~10:00");
	TextDrawLetterSize(CounterStrikeTD[6], 0.328, 1.211);
	TextDrawTextSize(CounterStrikeTD[6], 171.000, 0.000);
	TextDrawAlignment(CounterStrikeTD[6], 1);
	TextDrawColor(CounterStrikeTD[6], -5963521);
	TextDrawSetShadow(CounterStrikeTD[6], 0);
	TextDrawSetOutline(CounterStrikeTD[6], 0);
	TextDrawBackgroundColor(CounterStrikeTD[6], 255);
	TextDrawFont(CounterStrikeTD[6], 1);
	TextDrawSetProportional(CounterStrikeTD[6], 1);

	CounterStrikeTD[7] = TextDrawCreate(21.799, 159.850, "Counter Strike");
	TextDrawLetterSize(CounterStrikeTD[7], 0.719, 2.457);
	TextDrawTextSize(CounterStrikeTD[7], 217.000, 0.000);
	TextDrawAlignment(CounterStrikeTD[7], 1);
	TextDrawColor(CounterStrikeTD[7], 255);
	TextDrawSetShadow(CounterStrikeTD[7], 1);
	TextDrawSetOutline(CounterStrikeTD[7], 0);
	TextDrawBackgroundColor(CounterStrikeTD[7], -16776961);
	TextDrawFont(CounterStrikeTD[7], 0);
	TextDrawSetProportional(CounterStrikeTD[7], 1);

	// --------------------------------------------------------------------------

	CounterStrikeStartCountdownTD[0] = TextDrawCreate(319.800, 404.374, "Counter Strike~n~~r~~h~~h~~h~~h~Start: 1:00");
	TextDrawLetterSize(CounterStrikeStartCountdownTD[0], 0.409, 1.713);
	TextDrawTextSize(CounterStrikeStartCountdownTD[0], 0.000, 430.000);
	TextDrawAlignment(CounterStrikeStartCountdownTD[0], 2);
	TextDrawColor(CounterStrikeStartCountdownTD[0], -16776961);
	TextDrawSetShadow(CounterStrikeStartCountdownTD[0], 1);
	TextDrawSetOutline(CounterStrikeStartCountdownTD[0], -1);
	TextDrawBackgroundColor(CounterStrikeStartCountdownTD[0], 255);
	TextDrawFont(CounterStrikeStartCountdownTD[0], 2);
	TextDrawSetProportional(CounterStrikeStartCountdownTD[0], 1);
}

stock IsPlayerInCS(playerid){
	if(IsPlayerInCounterStrike(playerid) || IsPlayerInCounterStrikeLobby(playerid)) return 1;
	return 0;
}