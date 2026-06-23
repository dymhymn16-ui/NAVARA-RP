// -*- coding: utf-8 -*-

// Gun License Exam By Adib (telegram: @adib_yg)
// 2023 / 03 / 29
// COPYRIGHT: © 2023 Adib Salehi, TELEGRAM @adib_yg. All rights reserved.

// -----------------------------------------------

#define MONEY_COST_TO_EXAM_GUN 		30000

#define EXAM_TIME_GUN_LICENSE 		45 // 45 Seconds

#define LICENSE_GUN_SHOP_INTERIOR 	11

#define LICENSE_GUN_SHOP_WORLD 		11

#define MAX_BOTTLES_GUN_LICENSE		12

// -----------------------------------------------

static 
	PickupEnter,
	PickupExit,

	Checkpointid,

	Text3D: PlayerActorLabel[MAX_PLAYERS] = {Text3D: INVALID_3DTEXT_ID, ...},
	ActorLabelReset[MAX_PLAYERS],

	PlayerText:PTD_ExamPlayer[MAX_PLAYERS][2] = {PlayerText:INVALID_TEXT_DRAW, ...},
	Text:TD_Globals[4],

	PlayerInExam[MAX_PLAYERS],
	PlayerExamTime[MAX_PLAYERS],
	PlayerExamStatus[MAX_PLAYERS],
	PlayerExamEndedTime[MAX_PLAYERS],
	PlayerTimeToUnfreeze[MAX_PLAYERS],
	PlayerCountBottles[MAX_PLAYERS],
	PlayerBottleObjects[MAX_PLAYERS][MAX_BOTTLES_GUN_LICENSE],
	PlayerActorCharacter[MAX_PLAYERS];

static enum _player_pos_backs_enum
{
    Float: HealthBack,
    Float: ArmourBack
}

static PlayerBackPositionData[MAX_PLAYERS][_player_pos_backs_enum];


#include "../library/static/system/server/license_gun_map.inc"

// -----------------------------------------------

IsPlayerInGunLicenseExam(playerid)
{
	return PlayerInExam[playerid];
}

// -----------------------------------------------

CreateGunLicenseShopTextdraws()
{
	TD_Globals[0] = TextDrawCreate(165.000000, 146.250000, "");
	TextDrawTextSize(TD_Globals[0], 39.000000, 35.000000);
	TextDrawAlignment(TD_Globals[0], 1);
	TextDrawColor(TD_Globals[0], -1);
	TextDrawSetShadow(TD_Globals[0], 0);
	TextDrawBackgroundColor(TD_Globals[0], 0);
	TextDrawFont(TD_Globals[0], 5);
	TextDrawSetProportional(TD_Globals[0], 0);
	TextDrawSetPreviewModel(TD_Globals[0], 1950);
	TextDrawSetPreviewRot(TD_Globals[0], 0.000000, 0.000000, -56.000000, 1.000000);

	TD_Globals[1] = TextDrawCreate(176.000000, 141.000000, "");
	TextDrawTextSize(TD_Globals[1], 39.000000, 35.000000);
	TextDrawAlignment(TD_Globals[1], 1);
	TextDrawColor(TD_Globals[1], -1);
	TextDrawSetShadow(TD_Globals[1], 0);
	TextDrawBackgroundColor(TD_Globals[1], 0);
	TextDrawFont(TD_Globals[1], 5);
	TextDrawSetProportional(TD_Globals[1], 0);
	TextDrawSetPreviewModel(TD_Globals[1], 1520);
	TextDrawSetPreviewRot(TD_Globals[1], 0.000000, 0.000000, 0.000000, 1.000000);

	TD_Globals[2] = TextDrawCreate(188.300277, 146.250000, "");
	TextDrawTextSize(TD_Globals[2], 39.000000, 35.000000);
	TextDrawAlignment(TD_Globals[2], 1);
	TextDrawColor(TD_Globals[2], -1);
	TextDrawSetShadow(TD_Globals[2], 0);
	TextDrawBackgroundColor(TD_Globals[2], 0);
	TextDrawFont(TD_Globals[2], 5);
	TextDrawSetProportional(TD_Globals[2], 0);
	TextDrawSetPreviewModel(TD_Globals[2], 1664);
	TextDrawSetPreviewRot(TD_Globals[2], 0.000000, 0.000000, 0.000000, 1.000000);

	TD_Globals[3] = TextDrawCreate(108.999877, 139.250000, "");
	TextDrawTextSize(TD_Globals[3], 69.000000, 64.000000);
	TextDrawAlignment(TD_Globals[3], 1);
	TextDrawColor(TD_Globals[3], -1);
	TextDrawSetShadow(TD_Globals[3], 0);
	TextDrawBackgroundColor(TD_Globals[3], 0);
	TextDrawFont(TD_Globals[3], 5);
	TextDrawSetProportional(TD_Globals[3], 0);
	TextDrawSetPreviewModel(TD_Globals[3], 346);
	TextDrawSetPreviewRot(TD_Globals[3], 0.000000, 0.000000, 180.000000, 1.000000);
}

static createPlayerTextdraws(playerid)
{
	if(PTD_ExamPlayer[playerid][0] == PlayerText:INVALID_TEXT_DRAW)
	{
		PTD_ExamPlayer[playerid][0] = CreatePlayerTextDraw(playerid, 77.800292, 152.000000, "TIME : ~y~~h~0:45~n~~w~0 / ~y~12");
		PlayerTextDrawLetterSize(playerid, PTD_ExamPlayer[playerid][0], 0.400000, 1.600000);
		PlayerTextDrawTextSize(playerid, PTD_ExamPlayer[playerid][0], 0.000000, 106.000000);
		PlayerTextDrawAlignment(playerid, PTD_ExamPlayer[playerid][0], 2);
		PlayerTextDrawColor(playerid, PTD_ExamPlayer[playerid][0], -1);
		PlayerTextDrawUseBox(playerid, PTD_ExamPlayer[playerid][0], 1);
		PlayerTextDrawBoxColor(playerid, PTD_ExamPlayer[playerid][0], 50);
		PlayerTextDrawSetShadow(playerid, PTD_ExamPlayer[playerid][0], 0);
		PlayerTextDrawSetOutline(playerid, PTD_ExamPlayer[playerid][0], 1);
		PlayerTextDrawBackgroundColor(playerid, PTD_ExamPlayer[playerid][0], 255);
		PlayerTextDrawFont(playerid, PTD_ExamPlayer[playerid][0], 2);
		PlayerTextDrawSetProportional(playerid, PTD_ExamPlayer[playerid][0], 1);

		PTD_ExamPlayer[playerid][1] = CreatePlayerTextDraw(playerid, 24.850006, 186.475051, "~r~~h~Jeffery Cartel~n~~n~Behet ~y~~h~Colt 45 ~w~Midam~n~Botri Haro Bezan");
		PlayerTextDrawLetterSize(playerid, PTD_ExamPlayer[playerid][1], 0.400000, 1.600000);
		PlayerTextDrawTextSize(playerid, PTD_ExamPlayer[playerid][1], 207.849975, 0.000000);
		PlayerTextDrawAlignment(playerid, PTD_ExamPlayer[playerid][1], 1);
		PlayerTextDrawColor(playerid, PTD_ExamPlayer[playerid][1], -1);
		PlayerTextDrawUseBox(playerid, PTD_ExamPlayer[playerid][1], 1);
		PlayerTextDrawBoxColor(playerid, PTD_ExamPlayer[playerid][1], 134);
		PlayerTextDrawSetShadow(playerid, PTD_ExamPlayer[playerid][1], 0);
		PlayerTextDrawSetOutline(playerid, PTD_ExamPlayer[playerid][1], 1);
		PlayerTextDrawBackgroundColor(playerid, PTD_ExamPlayer[playerid][1], 255);
		PlayerTextDrawFont(playerid, PTD_ExamPlayer[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, PTD_ExamPlayer[playerid][1], 1);

		return 1;
	}

	return 0;
}

static destroyPlayerTextdraws(playerid)
{
	if(PTD_ExamPlayer[playerid][0] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PTD_ExamPlayer[playerid][0]);
		PlayerTextDrawDestroy(playerid, PTD_ExamPlayer[playerid][1]);

		PTD_ExamPlayer[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
		PTD_ExamPlayer[playerid][1] = PlayerText:INVALID_TEXT_DRAW;
	}
}

// -----------------------------------------------

LicenseGunShop_Init()
{
	CreateDynamic3DTextLabel("Jeffery Cartel", -1, -1722.5638, 71.0300, 3.7005+1.1, 13.5, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR); // Label On Actor Heads

	PickupEnter = CreateDynamicPickup(1318, 1, 1113.4490,-1837.2885,16.6002, .worldid = 0);
	PickupExit = CreateDynamicPickup(1318, 1, -1708.1086,84.5361,3.6604, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR);
	CreateDynamic3DTextLabel("** Gerftane Mojavez Aslahe **", col_blue, 1113.4490,-1837.2885,16.6002+0.7, 13.0);
	CreateDynamicMapIcon(1113.4490,-1837.2885,16.6002, 18, 1);
	Checkpointid = CreateDynamicCP(-1720.3203,73.3854,3.6604, 1.3, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR, .streamdistance = 30.0);
	//CreateDynamicPickup(1581, 1, -1720.3203,73.3854,3.6604, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR); // Key Card Pickup

	LoadLicenseGunShopMap();
	CreateGunLicenseShopTextdraws();
}

public OnPlayerDisconnect(playerid, reason)
{
	destroyPlayerTextdraws(playerid);

	if(PlayerInExam[playerid])
	{
		PlayerExamTime[playerid] = 0;
		PlayerExamStatus[playerid] = 0;
		PlayerExamEndedTime[playerid] = 0;
		PlayerInExam[playerid] = 0;

		if(PlayerActorLabel[playerid] != Text3D:INVALID_TEXT_DRAW)
		{
			ActorLabelReset[playerid] = 0;
			DestroyDynamic3DTextLabel(PlayerActorLabel[playerid]);
			PlayerActorLabel[playerid] = Text3D:INVALID_TEXT_DRAW;
		}

		for(new i; i < MAX_BOTTLES_GUN_LICENSE; i++)
		{
			if(PlayerBottleObjects[playerid][i])
			{
				DestroyDynamicObject(PlayerBottleObjects[playerid][i]);
				PlayerBottleObjects[playerid][i] = 0;
			}
		}

		DestroyDynamicActor(PlayerActorCharacter[playerid]);
	}
	
	#if defined GunExam_OnPlayerDisconnect
		return GunExam_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect GunExam_OnPlayerDisconnect
#if defined GunExam_OnPlayerDisconnect
	forward GunExam_OnPlayerDisconnect(playerid, reason);
#endif

LicenseGunShop_OnDynamicPickup(playerid, pickupid)
{
	if(pickupid == PickupEnter)
	{
		texture_load_mode(playerid);
		SetPlayerInterior(playerid, LICENSE_GUN_SHOP_INTERIOR);
		SetPlayerVirtualWorld(playerid, LICENSE_GUN_SHOP_WORLD);
		SetPlayerPos(playerid, -1709.1659,83.3498,3.6604);
		SetPlayerFacingAngle(playerid, 138.3030);
		return 1;
	}
	if(pickupid == PickupExit)
	{
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerPos(playerid, 1111.4902,-1837.3254,16.6016);
		SetPlayerFacingAngle(playerid, 90.7733);
		return 1;
	}

	return 0;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(checkpointid == Checkpointid)
	{
		if(PlyayerIsGang && !PlayerInfo[playerid][gun_lic])
		{
			show_dialog(playerid, d_license_gun_exam, DIALOG_STYLE_MSGBOX, "{FBB346}Gerftane Mojavez Aslahe", 
				"{FFFFFF}Mojavez Aslahe {D7D700}Mikhay?",
				"Are", "Na");
		}
		else
		{
			SendError(playerid, "To mojavez aslahe dari");
			PlayerPlaySound(playerid, 1137, 0.0, 0.0, 0.0);
		}
		return 1;
	}
	
	#if defined GunExam_OnPlayerEnterDynamicCP
		return GunExam_OnPlayerEnterDynamicCP(playerid, checkpointid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterDynamicCP
	#undef OnPlayerEnterDynamicCP
#else
	#define _ALS_OnPlayerEnterDynamicCP
#endif

#define OnPlayerEnterDynamicCP GunExam_OnPlayerEnterDynamicCP
#if defined GunExam_OnPlayerEnterDynamicCP
	forward GunExam_OnPlayerEnterDynamicCP(playerid, checkpointid);
#endif

LicenseGunShop_DialogResponse(playerid, dialogid, response)
{
	if(dialogid == d_license_gun_exam)
	{
		if(!response)
		{
			return 1;
		}

		if(PlayerInfo[playerid][level] < 3)
		{
		    SendClientMessage(playerid, col_white, ""scm_error"You Are Not Level 3.");
		    return 1;
		}

		if(PlayerInfo[playerid][money] < MONEY_COST_TO_EXAM_GUN)
		{
			SendError(playerid, "Shoma pool kafi nadarid.");
			return 1;
		}

		for(new i; i < 15; i++) SendClientMessage(playerid, -1, " ");

		GetPlayerHealth(playerid, PlayerBackPositionData[playerid][HealthBack]);
	    GetPlayerArmour(playerid, PlayerBackPositionData[playerid][ArmourBack]);

	    ResetPlayerWeapons(playerid);

		PlayerExamTime[playerid] = 0;
		PlayerInExam[playerid] = 1;

		PlayerActorCharacter[playerid] = CreateDynamicActor(293, 2455.4548,-1975.4532,13.5469,90.8701, .worldid = playerid + 1, .playerid = playerid);

		PlayerCountBottles[playerid] = 0;
		PlayerBottleObjects[playerid][0] = CreateDynamicObject(1950, 2449.0522, -1973.1407, 13.4953, 0.0000, 0.0000, -66.1999, .worldid = playerid + 1, .playerid = playerid); //kb_beer
		PlayerBottleObjects[playerid][1] = CreateDynamicObject(1950, 2452.5131, -1969.2742, 13.5753, 0.0000, 0.0000, -45.5999, .worldid = playerid + 1, .playerid = playerid); //kb_beer
		PlayerBottleObjects[playerid][2] = CreateDynamicObject(1950, 2450.0183, -1972.7137, 12.7253, 0.0000, 0.0000, -66.1999, .worldid = playerid + 1, .playerid = playerid); //kb_beer
		PlayerBottleObjects[playerid][3] = CreateDynamicObject(1950, 2453.7656, -1968.0490, 12.7353, 0.0000, 0.0000, -45.5999, .worldid = playerid + 1, .playerid = playerid); //kb_beer
		PlayerBottleObjects[playerid][4] = CreateDynamicObject(1520, 2440.8493, -1974.5649, 14.0591, 0.0000, 0.0000, 77.2000, .worldid = playerid + 1, .playerid = playerid); //DYN_WINE_BOUNCE
		PlayerBottleObjects[playerid][5] = CreateDynamicObject(1520, 2439.9724, -1972.7784, 14.2291, 0.0000, 0.0000, 77.2000, .worldid = playerid + 1, .playerid = playerid); //DYN_WINE_BOUNCE
		PlayerBottleObjects[playerid][6] = CreateDynamicObject(1520, 2440.5048, -1976.8907, 13.4891, 0.0000, 0.0000, 14.8000, .worldid = playerid + 1, .playerid = playerid); //DYN_WINE_BOUNCE
		PlayerBottleObjects[playerid][7] = CreateDynamicObject(1520, 2440.2229, -1975.8179, 12.5791, 0.0000, 0.0000, 14.8000, .worldid = playerid + 1, .playerid = playerid); //DYN_WINE_BOUNCE
		PlayerBottleObjects[playerid][8] = CreateDynamicObject(1664, 2440.3815, -1978.0177, 13.6004, 0.0000, 0.0000, -34.9000, .worldid = playerid + 1, .playerid = playerid); //propwinebotl2
		PlayerBottleObjects[playerid][9] = CreateDynamicObject(1664, 2441.3518, -1978.6947, 12.6904, 0.0000, 0.0000, -34.9000, .worldid = playerid + 1, .playerid = playerid); //propwinebotl2
		PlayerBottleObjects[playerid][10] = CreateDynamicObject(1664, 2440.8039, -1978.8850, 14.1804, 0.0000, 0.0000, -34.9000, .worldid = playerid + 1, .playerid = playerid); //propwinebotl2
		PlayerBottleObjects[playerid][11] = CreateDynamicObject(1664, 2440.0295, -1979.9993, 14.3404, 0.0000, 0.0000, -34.9000, .worldid = playerid + 1, .playerid = playerid); //propwinebotl2

		if(!createPlayerTextdraws(playerid))
		{
			PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][1], "~r~~h~Jeffery Cartel~n~~n~Behet ~y~~h~Colt 45 ~w~Midam~n~Botri Haro Bezan");
			PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][0], "TIME : ~y~~h~0:45~n~~w~0 / ~y~12");
		}

		SetPlayerCameraPos(playerid, 2443.1589, -1963.6952, 22.3717);
		SetPlayerCameraLookAt(playerid, 2443.5117, -1964.6311, 21.6017);
		ApplyDynamicActorAnimation(PlayerActorCharacter[playerid], "PED", "IDLE_CHAT", 4.1, 0, 1, 1, 1, 1);

		PlayerExamStatus[playerid] = 0;

		TogglePlayerControllable(playerid, false);

		give_money(playerid, -MONEY_COST_TO_EXAM_GUN);

		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, playerid + 1);
		SetPlayerPos(playerid, 2455.7534,-1978.1604,13.5469);
		SetPlayerFacingAngle(playerid, 89.6167);

		set_health(playerid, 100.0);
		set_armour(playerid, 0.0);

		PlayerTimeToUnfreeze[playerid] = 20;

		PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);

		PlayerTextDrawShow(playerid, PTD_ExamPlayer[playerid][1]);
		return 1;
	}
	return 0;
}

LicenseGunShop_PlayerTimer(playerid)
{
	if(ActorLabelReset[playerid] >= 2) ActorLabelReset[playerid]--;
	if(ActorLabelReset[playerid] == 1) {
		ActorLabelReset[playerid] = 0;
		UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Jeffery Cartel");
	}

	if(pl_afk_time[playerid] > 3) return 1; // Is AFK

	if(PlayerTimeToUnfreeze[playerid] >= 2) {
		PlayerTimeToUnfreeze[playerid]--;

		if(PlayerTimeToUnfreeze[playerid] == 15)
		{
			SetPlayerCameraPos(playerid, 2446.5986, -1981.6652, 17.0589);
			SetPlayerCameraLookAt(playerid, 2445.7793, -1981.0930, 16.6489);
		} 
		else if(PlayerTimeToUnfreeze[playerid] == 10)
		{
			SetPlayerCameraPos(playerid, 2451.0894, -1977.0829, 15.7736);
			SetPlayerCameraLookAt(playerid, 2451.0049, -1976.0876, 15.3637);
		} 
		else if(PlayerTimeToUnfreeze[playerid] == 5)
		{
			PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][1], "~r~~h~Jeffery Cartel~n~~n~Agar Tirat Tamom Beshe~n~Rad Mishi");
		}
	}
	if(PlayerTimeToUnfreeze[playerid] == 1)
	{
		PlayerTimeToUnfreeze[playerid] = 0;

		TogglePlayerControllable(playerid, true);

		if(PlayerExamStatus[playerid] == 0)
		{
			PlayerActorLabel[playerid] = CreateDynamic3DTextLabel("Jeffery Cartel", 0xC0583FFF, 2455.4548,-1975.4532,13.5469 + 1.1, 14.0, .worldid = playerid + 1); //, .playerid = playerid

			for(new td; td < sizeof TD_Globals; td++)
			{
				TextDrawShowForPlayer(playerid, TD_Globals[td]);
			}

			SetCameraBehindPlayer(playerid);

			PlayerTextDrawShow(playerid, PTD_ExamPlayer[playerid][0]);
			PlayerTextDrawHide(playerid, PTD_ExamPlayer[playerid][1]);

			SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1);

            ResetPlayerWeapons(playerid);
			GivePlayerWeapon(playerid, WEAPON_COLT45, 28);

			PlayerExamTime[playerid] = EXAM_TIME_GUN_LICENSE;
		}
	}

	if(PlayerExamEndedTime[playerid] >= 2) PlayerExamEndedTime[playerid]--;
	if(PlayerExamEndedTime[playerid] == 1)
	{
		PlayerExamEndedTime[playerid] = 0;

		if(PlayerExamStatus[playerid]) {
			PlayerInfo[playerid][gun_lic] = 1;
			update_int_sql(playerid, "u_gun_lic", PlayerInfo[playerid][gun_lic]);
			SendAccess(playerid, "Shoma mojavez aslahe gerftid.");
		} else {
			SendError(playerid, "Shoma dar azmon rad shodi.");
		}

		PlayerPlaySound(playerid, 1137, 0.0, 0.0, 0.0);

		for(new td; td < 2; td++)
		{
			PlayerTextDrawHide(playerid, PTD_ExamPlayer[playerid][td]);
		}

		for(new td; td < sizeof TD_Globals; td++)
		{
			TextDrawHideForPlayer(playerid, TD_Globals[td]);
		}

		reset_player_weapon(playerid);

		//texture_load_mode(playerid);
		SetPlayerInterior(playerid, LICENSE_GUN_SHOP_INTERIOR);
		SetPlayerVirtualWorld(playerid, LICENSE_GUN_SHOP_WORLD);
		SetPlayerPos(playerid, -1710.7875,73.5838,3.6604);
		SetPlayerFacingAngle(playerid, 45.5057);

		SetCameraBehindPlayer(playerid);

		TogglePlayerControllable(playerid, true);

		if(PlayerExamStatus[playerid]) {
			new rand_anim = random(3);
	        switch(rand_anim)  
	        {        
	            case 0: ApplyAnimation(playerid,"RIOT","RIOT_CHANT",4.1, 0, 0, 0, 0, 0, 1);
	            case 1: ApplyAnimation(playerid,"STRIP","PUN_HOLLER",4.1, 0, 0, 0, 0, 0, 1);
	            case 2: ApplyAnimation(playerid,"OTB","wtchrace_win",4.1, 0, 0, 0, 0, 0, 1);
	        }
		}

		if(PlayerActorLabel[playerid] != Text3D:INVALID_TEXT_DRAW)
		{
			ActorLabelReset[playerid] = 0;
			DestroyDynamic3DTextLabel(PlayerActorLabel[playerid]);
			PlayerActorLabel[playerid] = Text3D:INVALID_TEXT_DRAW;
		}

		for(new i; i < MAX_BOTTLES_GUN_LICENSE; i++)
		{
			if(PlayerBottleObjects[playerid][i])
			{
				DestroyDynamicObject(PlayerBottleObjects[playerid][i]);
				PlayerBottleObjects[playerid][i] = 0;
			}
		}

		DestroyDynamicActor(PlayerActorCharacter[playerid]);

		set_health(playerid, PlayerBackPositionData[playerid][HealthBack]);
	    set_armour(playerid, PlayerBackPositionData[playerid][ArmourBack]);
	    
        for(new i; i < MAX_WEAPONS; i++) GivePlayerWeapon(playerid, PlayerInfo[playerid][Weapon][i], PlayerInfo[playerid][Ammo][i]);
        SetPlayerArmedWeapon(playerid, 0);

	    // Skills
	    SetPlayerSkills(playerid);
	}

	if(PlayerInExam[playerid])
	{
		if(PlayerExamTime[playerid] >= 2) {
			PlayerExamTime[playerid]--;

			new 
				string[46],
				time = PlayerExamTime[playerid],
				color_stat[8] = "~y~~h~";

			if(time <= 10)
			{
				if((time % 2)) 
					color_stat = "~y~~h~";
				else
					color_stat = "~r~~h~";
			}

			format(string, sizeof string, "TIME : %s%d:%02d~n~~w~%d / ~y~12", 
				color_stat, time / 60, time % 60, PlayerCountBottles[playerid]);

			PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][0], string);

			if(PlayerExamTime[playerid] <= (EXAM_TIME_GUN_LICENSE-3)) // Needed
			{
				PlayerExamTime[playerid] = 0;

				TogglePlayerControllable(playerid, false);

				ActorLabelReset[playerid] = 0;
				UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Jeffery Cartel");

				for(new td; td < sizeof TD_Globals; td++)
				{
					TextDrawHideForPlayer(playerid, TD_Globals[td]);
				}
				PlayerTextDrawHide(playerid, PTD_ExamPlayer[playerid][0]);

				PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][1], "~r~~h~Jeffery Cartel~n~~n~~r~Bad~n~To Rad Shodi~n~~w~Tirat Tamom Shod");
				PlayerTextDrawShow(playerid, PTD_ExamPlayer[playerid][1]);

				PlayerExamStatus[playerid] = 0;
				PlayerExamEndedTime[playerid] = 8;
				PlayerInExam[playerid] = 0;

				PlayerPlaySound(playerid, 5203, 0.0, 0.0, 0.0);

				SetPlayerCameraPos(playerid, 2451.7659, -1975.0665, 14.4056);
				SetPlayerCameraLookAt(playerid, 2452.7639, -1975.0509, 14.2156);

				ApplyDynamicActorAnimation(PlayerActorCharacter[playerid], "COP_AMBIENT", "COPLOOK_SHAKE", 4.1, 0, 1, 1, 1, 1);
			}
		}
		if(PlayerExamTime[playerid] == 1)
		{
			PlayerExamTime[playerid] = 0;

			TogglePlayerControllable(playerid, false);

			ActorLabelReset[playerid] = 0;
			UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Jeffery Cartel");

			for(new td; td < sizeof TD_Globals; td++)
			{
				TextDrawHideForPlayer(playerid, TD_Globals[td]);
			}
			PlayerTextDrawHide(playerid, PTD_ExamPlayer[playerid][0]);

			PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][1], "~r~~h~Jeffery Cartel~n~~n~~r~Bad~n~To Rad Shodi~n~~w~Vaghtet Tamom Shod");
			PlayerTextDrawShow(playerid, PTD_ExamPlayer[playerid][1]);

			PlayerExamStatus[playerid] = 0;
			PlayerExamEndedTime[playerid] = 8;
			PlayerInExam[playerid] = 0;

			PlayerPlaySound(playerid, 5203, 0.0, 0.0, 0.0);

			SetPlayerCameraPos(playerid, 2451.7659, -1975.0665, 14.4056);
			SetPlayerCameraLookAt(playerid, 2452.7639, -1975.0509, 14.2156);

			//ApplyDynamicActorAnimation(PlayerActorCharacter[playerid], "COP_AMBIENT", "COPLOOK_SHAKE", 4.1, 0, 1, 1, 1, 1);
			ApplyDynamicActorAnimation(PlayerActorCharacter[playerid], "MISC", "PLYR_SHKHEAD", 4.1, 0, 1, 1, 1, 1);
		}
	}

	return 1;
}

LicenseGunShop_PlayerDeath(playerid)
{
	if(PlayerInExam[playerid])
	{
		give_money(playerid, MONEY_COST_TO_EXAM_GUN);

		PlayerExamTime[playerid] = 0;
		PlayerExamStatus[playerid] = 0;
		PlayerExamEndedTime[playerid] = 0;
		PlayerInExam[playerid] = 0;

		PlayerPlaySound(playerid, 5203, 0.0, 0.0, 0.0);

		if(PlayerActorLabel[playerid] != Text3D:INVALID_TEXT_DRAW)
		{
			ActorLabelReset[playerid] = 0;
			DestroyDynamic3DTextLabel(PlayerActorLabel[playerid]);
			PlayerActorLabel[playerid] = Text3D:INVALID_TEXT_DRAW;
		}

		for(new i; i < MAX_BOTTLES_GUN_LICENSE; i++)
		{
			if(PlayerBottleObjects[playerid][i])
			{
				DestroyDynamicObject(PlayerBottleObjects[playerid][i]);
				PlayerBottleObjects[playerid][i] = 0;
			}
		}

		DestroyDynamicActor(PlayerActorCharacter[playerid]);
		return 1;
	}

	return 0;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z)
{
	if(PlayerInExam[playerid])
	{
		for(new i; i < MAX_BOTTLES_GUN_LICENSE; i++)
		{
			if(PlayerBottleObjects[playerid][i] == objectid)
			{
				if(weaponid == 0)
				{
					PlayerExamTime[playerid] = 0;

					TogglePlayerControllable(playerid, false);

					ActorLabelReset[playerid] = 0;
					UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Jeffery Cartel");

					for(new td; td < sizeof TD_Globals; td++)
					{
						TextDrawHideForPlayer(playerid, TD_Globals[td]);
					}
					PlayerTextDrawHide(playerid, PTD_ExamPlayer[playerid][0]);

					PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][1], "~r~~h~Jeffery Cartel~n~~n~~r~Bad~n~To Rad Shodi~n~~w~Bayad Ba ~y~~h~Colt 45 ~w~Mizadi");
					PlayerTextDrawShow(playerid, PTD_ExamPlayer[playerid][1]);

					PlayerExamStatus[playerid] = 0;
					PlayerExamEndedTime[playerid] = 7;
					PlayerInExam[playerid] = 0;

					PlayerPlaySound(playerid, 5203, 0.0, 0.0, 0.0);

					SetPlayerCameraPos(playerid, 2451.7659, -1975.0665, 14.4056);
					SetPlayerCameraLookAt(playerid, 2452.7639, -1975.0509, 14.2156);

					//ApplyDynamicActorAnimation(PlayerActorCharacter[playerid], "COP_AMBIENT", "COPLOOK_SHAKE", 4.1, 0, 1, 1, 1, 1);
					ApplyDynamicActorAnimation(PlayerActorCharacter[playerid], "MISC", "PLYR_SHKHEAD", 4.1, 0, 1, 1, 1, 1);

					return 1;
				}

				DestroyDynamicObject(PlayerBottleObjects[playerid][i]);
				PlayerBottleObjects[playerid][i] = 0;
				PlayerCountBottles[playerid]++;

				new 
					string[46],
					time = PlayerExamTime[playerid],
					color_stat[8] = "~y~~h~";

				if(time <= 10)
				{
					if((time % 2)) 
						color_stat = "~y~~h~";
					else
						color_stat = "~r~~h~";
				}

				format(string, sizeof string, "TIME : %s%d:%02d~n~~w~%d / ~y~12", 
					color_stat, time / 60, time % 60, PlayerCountBottles[playerid]);

				PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][0], string);

				switch(PlayerCountBottles[playerid])
				{
					case 2: {
						ActorLabelReset[playerid] = 4;
						UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Afarin !");
					}
					case 5: {
						ActorLabelReset[playerid] = 4;
						UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Khob !");
					}
					case 7: {
						ActorLabelReset[playerid] = 4;
						UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Nice !");
					}
					case 10: {
						ActorLabelReset[playerid] = 4;
						UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Afarin Pesar !");
					}
					case MAX_BOTTLES_GUN_LICENSE:
					{
						PlayerExamStatus[playerid] = 1;

						PlayerExamTime[playerid] = 0;
						PlayerExamEndedTime[playerid] = 8;
						PlayerInExam[playerid] = 0;

						ActorLabelReset[playerid] = 0;
						UpdateDynamic3DTextLabelText(PlayerActorLabel[playerid], 0xC0583FFF, "Jeffery Cartel");

						for(new td; td < sizeof TD_Globals; td++)
						{
							TextDrawHideForPlayer(playerid, TD_Globals[td]);
						}
						PlayerTextDrawHide(playerid, PTD_ExamPlayer[playerid][0]);

						TogglePlayerControllable(playerid, false);

						SetPlayerCameraPos(playerid, 2451.7659, -1975.0665, 14.4056);
						SetPlayerCameraLookAt(playerid, 2452.7639, -1975.0509, 14.2156);

						PlayerTextDrawSetString(playerid, PTD_ExamPlayer[playerid][1], "~r~~h~Jeffery Cartel~n~~n~~g~~h~Besiar Khob!~n~~g~To Ghabol Shodi");
						PlayerTextDrawShow(playerid, PTD_ExamPlayer[playerid][1]);

						PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0);

						ApplyDynamicActorAnimation(PlayerActorCharacter[playerid], "FREEWEIGHTS", "GYM_FREE_CELEBRATE", 4.1, 0, 1, 1, 1, 1);
					}
				}
				break;
			}
		}
	}

	#if defined GunExam_OnPlayerShootDynamicOb
		return GunExam_OnPlayerShootDynamicOb(playerid, weaponid, objectid, Float:x, Float:y, Float:z);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerShootDynamicObjec
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObjec
#endif

#define OnPlayerShootDynamicObject GunExam_OnPlayerShootDynamicOb
#if defined GunExam_OnPlayerShootDynamicOb
	forward GunExam_OnPlayerShootDynamicOb(playerid, weaponid, objectid, Float:x, Float:y, Float:z);
#endif