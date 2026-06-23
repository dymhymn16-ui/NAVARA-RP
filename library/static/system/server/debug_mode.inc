static bool:s_PlayerDebugMode[MAX_PLAYERS];
static s_PlayerDebugModeTimer[MAX_PLAYERS];
static PlayerText:s_PlayerTextdraws[MAX_PLAYERS][1];
static PlayerText:s_PlayerTextdrawsAndroid[MAX_PLAYERS][1];

// ------------------------------------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	if (s_PlayerDebugMode[playerid]) {
		s_PlayerDebugMode[playerid] = false;

		KillTimer(s_PlayerDebugModeTimer[playerid]);

		DestroyPlayerDebugModeTextdraw(playerid);
	}

	#if defined DebugMode_OnPlayerDisconnect
		return DebugMode_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect DebugMode_OnPlayerDisconnect
#if defined DebugMode_OnPlayerDisconnect
	forward DebugMode_OnPlayerDisconnect(playerid, reason);
#endif

// ------------------------------------------------------------------

static LoadPlayerDebugModeTextdraw(playerid) {
	if (!IsPlayerUsingSampMobile(playerid)) {
		s_PlayerTextdraws[playerid][0] = CreatePlayerTextDraw(playerid, 515.000000, 173.375000, " ");
		PlayerTextDrawLetterSize(playerid, s_PlayerTextdraws[playerid][0], 0.270999, 1.118749);
		PlayerTextDrawTextSize(playerid, s_PlayerTextdraws[playerid][0], 0.000000, 252.000000);
		PlayerTextDrawAlignment(playerid, s_PlayerTextdraws[playerid][0], 2);
		PlayerTextDrawColor(playerid, s_PlayerTextdraws[playerid][0], -1);
		PlayerTextDrawSetShadow(playerid, s_PlayerTextdraws[playerid][0], 0);
		PlayerTextDrawSetOutline(playerid, s_PlayerTextdraws[playerid][0], 1);
		PlayerTextDrawBackgroundColor(playerid, s_PlayerTextdraws[playerid][0], 255);
		PlayerTextDrawFont(playerid, s_PlayerTextdraws[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, s_PlayerTextdraws[playerid][0], 1);
	} else {
		s_PlayerTextdrawsAndroid[playerid][0] = CreatePlayerTextDraw(playerid, 449.599487, 172.774993, " ");
		PlayerTextDrawLetterSize(playerid, s_PlayerTextdrawsAndroid[playerid][0], 0.295999, 1.327498);
		PlayerTextDrawTextSize(playerid, s_PlayerTextdrawsAndroid[playerid][0], 0.000000, 262.849914);
		PlayerTextDrawAlignment(playerid, s_PlayerTextdrawsAndroid[playerid][0], 2);
		PlayerTextDrawColor(playerid, s_PlayerTextdrawsAndroid[playerid][0], -1);
		PlayerTextDrawSetShadow(playerid, s_PlayerTextdrawsAndroid[playerid][0], 0);
		PlayerTextDrawSetOutline(playerid, s_PlayerTextdrawsAndroid[playerid][0], 1);
		PlayerTextDrawBackgroundColor(playerid, s_PlayerTextdrawsAndroid[playerid][0], 255);
		PlayerTextDrawFont(playerid, s_PlayerTextdrawsAndroid[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, s_PlayerTextdrawsAndroid[playerid][0], 1);
	}
}

static DestroyPlayerDebugModeTextdraw(playerid) {
	if (!IsPlayerUsingSampMobile(playerid)) {
		for (new i = 0; i < sizeof(s_PlayerTextdraws[]); i++) {
			PlayerTextDrawDestroy(playerid, s_PlayerTextdraws[playerid][i]);
		}
	} else {
		for (new i = 0; i < sizeof(s_PlayerTextdrawsAndroid[]); i++) {
			PlayerTextDrawDestroy(playerid, s_PlayerTextdrawsAndroid[playerid][i]);
		}
	}
}

static ShowPlayerDebugModeTextdraw(playerid) {
	if (!IsPlayerUsingSampMobile(playerid)) {
		for (new i = 0; i < sizeof(s_PlayerTextdraws[]); i++) {
			PlayerTextDrawShow(playerid, s_PlayerTextdraws[playerid][i]);
		}
	} else {
		for (new i = 0; i < sizeof(s_PlayerTextdrawsAndroid[]); i++) {
			PlayerTextDrawShow(playerid, s_PlayerTextdrawsAndroid[playerid][i]);
		}
	}
}

// ------------------------------------------------------------------

forward DebugModeTimer(playerid);
public DebugModeTimer(playerid) 
{
	new string[350];
	new Float:x, Float:y, Float:z;
	new Float:angle;
	new Float:health;
	new Float:armour;

	new Float:v_pos_x, Float:v_pos_y, Float:v_pos_z, Float:v_pos_c,
		vehicleid = GetPlayerVehicleID(playerid);
    GetVehicleZAngle(vehicleid, v_pos_c);
	GetVehiclePos(vehicleid, v_pos_x, v_pos_y, v_pos_z);

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);
	GetPlayerHealth(playerid, health);
	GetPlayerArmour(playerid, armour);

	format(string, sizeof(string), "\
		[DEBUG MODE]\
		~n~~r~%.4f, %.4f, %.4f, %.4f\
		~n~~r~%.4f, %.4f, %.4f, %.4f\
		~n~~w~Interior: ~r~%d\
		~n~~w~World: ~r~%d\
		~n~~w~Skin: ~r~%d\
		~n~~w~Weapon: ~r~%d\
		~n~~w~Vehicle: ~r~%d\
		~n~~w~State: ~r~%d\
		~n~~w~Health: ~r~%.1f\
		~n~~w~Armour: ~r~%.1f\
		", 
		x, y, z, angle,
		v_pos_x, v_pos_y, v_pos_z, v_pos_c,
		GetPlayerInterior(playerid),
		GetPlayerVirtualWorld(playerid),
		GetPlayerSkin(playerid),
		GetPlayerWeapon(playerid),
		GetPlayerVehicleID(playerid),
		GetPlayerState(playerid),
		health,
		armour);

	if (!IsPlayerUsingSampMobile(playerid)) {
		PlayerTextDrawSetString(playerid, s_PlayerTextdraws[playerid][0], string);
	} else {
		PlayerTextDrawSetString(playerid, s_PlayerTextdrawsAndroid[playerid][0], string);
	}
}

// ------------------------------------------------------------------

CMD:debugmode(playerid, params[]) {

	if(check_admin_rank(playerid , 8)) return 1;

	if (s_PlayerDebugMode[playerid]) {
		s_PlayerDebugMode[playerid] = false;


		KillTimer(s_PlayerDebugModeTimer[playerid]);

		DestroyPlayerDebugModeTextdraw(playerid);
		return 1;
	}

	s_PlayerDebugMode[playerid] = true;

	LoadPlayerDebugModeTextdraw(playerid);

	ShowPlayerDebugModeTextdraw(playerid);

	s_PlayerDebugModeTimer[playerid] = SetTimerEx("DebugModeTimer", 1000, true, "d", playerid);
	return 1;
}