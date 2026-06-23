// -*- coding: utf-8 -*-

// System (Bike Helmet Attachment) & (Seatbelt)
// ------------------------------------------------------------------

#define BIKE_HELMET_ATTACHMENT_INDEX \
	6

#define COLORED_BIKE_HELMET \
	true

#if !COLORED_BIKE_HELMET
	#define SPAO_HELMET{%0,%1,%2,%3,%4,%5} \
		SetPlayerAttachedObject(playerid, BIKE_HELMET_ATTACHMENT_INDEX, 18645, 2, %0, %1, %2, %3, %4, %5);
#else
	#define SPAO_HELMET{%0,%1,%2,%3,%4,%5} \
		SetPlayerAttachedObject(playerid, BIKE_HELMET_ATTACHMENT_INDEX, 18645, 2, %0, %1, %2, %3, %4, %5, 1.0, 1.0, 1.0, HelmetMaterialColorList[rand_material_color]);
#endif

// ------------------------------------------------------------------

static 
	bool: PlayerBikeHelmet[MAX_PLAYERS];

static 
	bool: SeatbeltStatus[MAX_PLAYERS],
	Float: LastCarHealth[MAX_PLAYERS];

#if COLORED_BIKE_HELMET
static
	HelmetMaterialColorList[14] = {
		0xFF000000,
		0xFFFFFFFF,
		0xFFFF0000,
		0xFF00FF00,
		0xFF0000FF,
		0xFF0000FF,
		0xFF00FFFF,
		0xFFFF00FF,
		0xFF808080,
		0xFF800000,
		0xFF008000,
		0xFF800080,
		0xFF008080,
		0xFF000080
	};
#endif

// ------------------------------------------------------------------

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#if !defined PRESSED
		#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	#endif

	if(PRESSED(KEY_SUBMISSION)) {
		if(IsPlayerInAnyVehicle(playerid)) {
			if(IsVehicleIsABike(GetPlayerVehicleID(playerid))) {
				PlayerAttachOrDetachBikeHelmet(playerid);
			} else {
				callcmd::seatbelt(playerid);
			}
		}
	}

	#if defined SEATBELT_OnPlayerKeyStateChan
		return SEATBELT_OnPlayerKeyStateChan(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange SEATBELT_OnPlayerKeyStateChan
#if defined SEATBELT_OnPlayerKeyStateChan
	forward SEATBELT_OnPlayerKeyStateChan(playerid, newkeys, oldkeys);
#endif

// ------------------------------------------------------------------

public OnPlayerDeath(playerid, killerid, reason)
{
	if(PlayerBikeHelmet[playerid]) {
		DetachBikeHelmetFromPlayer(playerid);
	}

	#if defined Prefix_OnPlayerDeath
		return Prefix_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif

#define OnPlayerDeath Prefix_OnPlayerDeath
#if defined Prefix_OnPlayerDeath
	forward Prefix_OnPlayerDeath(playerid, killerid, reason);
#endif

// ------------------------------------------------------------------

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {
		if(PlayerBikeHelmet[playerid]) {
			DetachBikeHelmetFromPlayer(playerid);
			me_action(playerid,"Kolah imeni ra bardasht");
		}
	}

	#if defined SEATBELT_OnPlayerStateChange
		return SEATBELT_OnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange SEATBELT_OnPlayerStateChange
#if defined SEATBELT_OnPlayerStateChange
	forward SEATBELT_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

// ------------------------------------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	if(PlayerBikeHelmet[playerid]) {
		DetachBikeHelmetFromPlayer(playerid);
	}

	SeatbeltStatus[playerid] = false;

	#if defined SEATBELT_OnPlayerDisconnect
		return SEATBELT_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect SEATBELT_OnPlayerDisconnect
#if defined SEATBELT_OnPlayerDisconnect
	forward SEATBELT_OnPlayerDisconnect(playerid, reason);
#endif

// ------------------------------------------------------------------

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	SeatbeltStatus[playerid] = false;
	
	#if defined SEATBELT_OnPlayerEnterVehicle
		return SEATBELT_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif

#define OnPlayerEnterVehicle SEATBELT_OnPlayerEnterVehicle
#if defined SEATBELT_OnPlayerEnterVehicle
	forward SEATBELT_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
#endif

// ------------------------------------------------------------------

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(SeatbeltStatus[playerid])
	{
		me_action(playerid, "Kamarbandesh ro baz kard");
	    SeatbeltStatus[playerid] = false;
	}

	#if defined SEATBELT_OnPlayerExitVehicle
		return SEATBELT_OnPlayerExitVehicle(playerid, vehicleid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif

#define OnPlayerExitVehicle SEATBELT_OnPlayerExitVehicle
#if defined SEATBELT_OnPlayerExitVehicle
	forward SEATBELT_OnPlayerExitVehicle(playerid, vehicleid);
#endif

// ------------------------------------------------------------------

public OnPlayerUpdate(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_EXIT_VEHICLE && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER))
	{
		if (!IsPlayerUsingSampMobile(playerid))
		{
			new vehicleid = GetPlayerVehicleID(playerid),
				is_a_bike = IsVehicleIsABike(vehicleid);

			if( (is_a_bike && !PlayerBikeHelmet[playerid]) || 
				(!is_a_bike && !SeatbeltStatus[playerid]) ) 
			{
				new Float:TempLastCarHealth;
				GetVehicleHealth(vehicleid, TempLastCarHealth);
				new Float:Difference = floatsub(LastCarHealth[playerid], TempLastCarHealth);
				if((floatcmp(LastCarHealth[playerid], TempLastCarHealth) == 1) && (floatcmp(Difference,100.0) == 1))
				{
				    Difference = floatdiv(Difference, 10.0);
				    new Float:OldHealth;
				    GetPlayerHealth(playerid, OldHealth);

				    GameTextForPlayer(playerid, "~r~kamarband nabasti", 2000, 3);
				    set_health(playerid, floatsub(OldHealth, Difference));

				    RemovePlayerFromVehicle(playerid);

				    SetTimerEx("ApplySweetInjuredAnim", 300, false, "i", playerid);
				}
				LastCarHealth[playerid] = TempLastCarHealth;
			}
		}
	}
	else
	{
		LastCarHealth[playerid] = 0.0;
	}
	
	#if defined SEATBELT_OnPlayerUpdate
		return SEATBELT_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate SEATBELT_OnPlayerUpdate
#if defined SEATBELT_OnPlayerUpdate
	forward SEATBELT_OnPlayerUpdate(playerid);
#endif

// ------------------------------------------------------------------

static AttachBikeHelmetToPlayer(playerid) {
	#if COLORED_BIKE_HELMET
	new rand_material_color = random(sizeof HelmetMaterialColorList);
	#endif
	switch(GetPlayerSkin(playerid))
	{
		case 0, 65, 74, 149, 208, 273: SPAO_HELMET{0.070000, 0.000000, 0.000000, 88.000000, 75.000000, 0.000000}
		case 1..6, 8, 14, 16, 22, 27, 29, 33, 41..49, 82..84, 86, 87, 119, 289: SPAO_HELMET{0.070000, 0.000000, 0.000000, 88.000000, 77.000000, 0.000000}
		case 7, 10: SPAO_HELMET{0.090000, 0.019999, 0.000000, 88.000000, 90.000000, 0.000000}
		case 9: SPAO_HELMET{0.059999, 0.019999, 0.000000, 88.000000, 90.000000, 0.000000}
		case 11..13: SPAO_HELMET{0.070000, 0.019999, 0.000000, 88.000000, 90.000000, 0.000000}
		case 15: SPAO_HELMET{0.059999, 0.000000, 0.000000, 88.000000, 82.000000, 0.000000}
		case 17..21: SPAO_HELMET{0.059999, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 23..26, 28, 30..32, 34..39, 57, 58, 98, 99, 104..118, 120..131: SPAO_HELMET{0.079999, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 40: SPAO_HELMET{0.050000, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 50, 100..103, 148, 150..189, 222: SPAO_HELMET{0.070000, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 51..54: SPAO_HELMET{0.100000, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 55, 56, 63, 64, 66..73, 75, 76, 78..81, 133..143, 147, 190..207, 209..219, 221, 247..272, 274..288, 290..293: SPAO_HELMET{0.070000, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 59..62: SPAO_HELMET{0.079999, 0.029999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 77: SPAO_HELMET{0.059999, 0.019999, 0.000000, 87.000000, 82.000000, 0.000000}
		case 85, 88, 89: SPAO_HELMET{0.070000, 0.039999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 90..97: SPAO_HELMET{0.050000, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 132: SPAO_HELMET{0.000000, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 144..146: SPAO_HELMET{0.090000, 0.000000, 0.000000, 88.000000, 82.000000, 0.000000}
		case 220: SPAO_HELMET{0.029999, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 223, 246: SPAO_HELMET{0.070000, 0.050000, 0.000000, 88.000000, 82.000000, 0.000000}
		case 224..245: SPAO_HELMET{0.070000, 0.029999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 294: SPAO_HELMET{0.070000, 0.019999, 0.000000, 91.000000, 84.000000, 0.000000}
		case 295: SPAO_HELMET{0.050000, 0.019998, 0.000000, 86.000000, 82.000000, 0.000000}
		case 296..298: SPAO_HELMET{0.064999, 0.009999, 0.000000, 88.000000, 82.000000, 0.000000}
		case 299: SPAO_HELMET{0.064998, 0.019999, 0.000000, 88.000000, 82.000000, 0.000000}
		default: SPAO_HELMET{0.070000, 0.000000, 0.000000, 88.000000, 75.000000, 0.000000}
	}
	PlayerBikeHelmet[playerid] = true;
}

static DetachBikeHelmetFromPlayer(playerid) {
	RemovePlayerAttachedObject(playerid, BIKE_HELMET_ATTACHMENT_INDEX);
	PlayerBikeHelmet[playerid] = false;
}

// ------------------------------------------------------------------

forward ApplySweetInjuredAnim(playerid);
public ApplySweetInjuredAnim(playerid) {
	ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.1, true, false, false, false, 2500, true);
}

// ------------------------------------------------------------------

static PlayerAttachOrDetachBikeHelmet(playerid) {

	if(!PlayerBikeHelmet[playerid]) {
		AttachBikeHelmetToPlayer(playerid);
		me_action(playerid,"Kolah imeni gozasht");
		PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
		return 1;
	}

	LastCarHealth[playerid] = 0.0;
	DetachBikeHelmetFromPlayer(playerid);
	me_action(playerid,"Kolah imeni ra bardasht");
	PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
	return 1;
}

// ------------------------------------------------------------------

alias:seatbelt("st", "kamarband");
CMD:seatbelt(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid))
	{
        SendClientMessage(playerid, col_white, ""scm_error"Shoma dar mashin nistid!");
        return 1;
    }
    if(IsVehicleIsABike(GetPlayerVehicleID(playerid)))
	{
        SendClientMessage(playerid, col_white, ""scm_error"Shoma dar mashin nistid!");
        return 1;
    }
	
    if(SeatbeltStatus[playerid] == false)
	{
        SeatbeltStatus[playerid] = true;
        me_action(playerid, "Kamarbandesh ro bast");
		PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
		return 1;
    }

    LastCarHealth[playerid] = 0.0;
	SeatbeltStatus[playerid] = false;
	me_action(playerid, "Kamarbandesh ro baz kard");
	PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
	return 1;
}

// ------------------------------------------------------------------

static stock IsVehicleIsABike(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 509, 481, 510, 462, 448, 581, 522, 461, 521, 523, 463, 586, 468, 471: return 1;
	}
	return 0;
}

// ------------------------------------------------------------------

#undef BIKE_HELMET_ATTACHMENT_INDEX
#undef COLORED_BIKE_HELMET