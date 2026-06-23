#if defined _INC_DAMAGE_INFO
	#endinput
#endif
#define _INC_DAMAGE_INFO

// ------------------------------------------------------------------

#if !defined DMG_INFO_ENABLED
	#define DMG_INFO_ENABLED true
#endif

#if DMG_INFO_ENABLED == true

// ------------------------------------------------------------------

#if !defined DMG_INFO_HIDE_INTERVAL
	#define DMG_INFO_HIDE_INTERVAL 2300
#endif

// ------------------------------------------------------------------

static 
	PlayerText: TextDrawDamageInfoPlayer[MAX_PLAYERS][2],
	bool: PlayerTextdrawsLoaded[MAX_PLAYERS],
	bool: PlayerDamageInfoToggle[MAX_PLAYERS] = {bool: true, ...},
	PlayerTimer[MAX_PLAYERS] = {-1, ...};

new PlayerBar: PlayerBarHealthDamage[MAX_PLAYERS] = {INVALID_PLAYER_BAR_ID, ...};

// ------------------------------------------------------------------

stock SetPlayerDamageInfoToggle(playerid, bool: toggle) {
	return PlayerDamageInfoToggle[playerid] = toggle;
}

// ------------------------------------------------------------------

LoadDamageInfoTextdraws(playerid) {
	PlayerTextdrawsLoaded[playerid] = true;

	TextDrawDamageInfoPlayer[playerid][0] = CreatePlayerTextDraw(playerid, 216.700088, 345.474609, " "); //-46.2
	PlayerTextDrawLetterSize(playerid, TextDrawDamageInfoPlayer[playerid][0], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, TextDrawDamageInfoPlayer[playerid][0], 2);
	PlayerTextDrawColor(playerid, TextDrawDamageInfoPlayer[playerid][0], -14671617);
	PlayerTextDrawSetShadow(playerid, TextDrawDamageInfoPlayer[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawDamageInfoPlayer[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, TextDrawDamageInfoPlayer[playerid][0], 128);
	PlayerTextDrawFont(playerid, TextDrawDamageInfoPlayer[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, TextDrawDamageInfoPlayer[playerid][0], 1);

	TextDrawDamageInfoPlayer[playerid][1] = CreatePlayerTextDraw(playerid, 415.599639, 345.474609, " "); //+52.8
	PlayerTextDrawLetterSize(playerid, TextDrawDamageInfoPlayer[playerid][1], 0.400000, 1.600000);
	PlayerTextDrawAlignment(playerid, TextDrawDamageInfoPlayer[playerid][1], 2);
	PlayerTextDrawColor(playerid, TextDrawDamageInfoPlayer[playerid][1], 754852351);
	PlayerTextDrawSetShadow(playerid, TextDrawDamageInfoPlayer[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawDamageInfoPlayer[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, TextDrawDamageInfoPlayer[playerid][1], 128);
	PlayerTextDrawFont(playerid, TextDrawDamageInfoPlayer[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, TextDrawDamageInfoPlayer[playerid][1], 1);
}

static DestroyDamageInfoTextdraws(playerid) {
	if(PlayerTextdrawsLoaded[playerid]) {
		PlayerTextdrawsLoaded[playerid] = false;

		if (PlayerBarHealthDamage[playerid] != INVALID_PLAYER_BAR_ID) {
			DestroyPlayerProgressBar(playerid, PlayerBarHealthDamage[playerid]);
			PlayerBarHealthDamage[playerid] = INVALID_PLAYER_BAR_ID;
		}

		for(new td; td < sizeof(TextDrawDamageInfoPlayer[]); td++) {
			PlayerTextDrawDestroy(playerid, TextDrawDamageInfoPlayer[playerid][td]);
		}
	}
}

// ------------------------------------------------------------------

forward DamageInfo_HideTextdraws(playerid);
public DamageInfo_HideTextdraws(playerid) 
{
	for(new td; td < sizeof(TextDrawDamageInfoPlayer[]); td++) {
		PlayerTextDrawHide(playerid, TextDrawDamageInfoPlayer[playerid][td]);
	}
	HidePlayerProgressBar(playerid, PlayerBarHealthDamage[playerid]);

	PlayerTimer[playerid] = -1;
}

// ------------------------------------------------------------------

/*public OnPlayerConnect(playerid)
{
	LoadDamageInfoTextdraws(playerid);

	#if defined DamageInfo_OnPlayerConnect
		return DamageInfo_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect DamageInfo_OnPlayerConnect
#if defined DamageInfo_OnPlayerConnect
	forward DamageInfo_OnPlayerConnect(playerid);
#endif*/

// ------------------------------------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	DestroyDamageInfoTextdraws(playerid);
	PlayerDamageInfoToggle[playerid] = true;

	#if defined DamageInfo_OnPlayerDisconnect
		return DamageInfo_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect DamageInfo_OnPlayerDisconnect
#if defined DamageInfo_OnPlayerDisconnect
	forward DamageInfo_OnPlayerDisconnect(playerid, reason);
#endif

// ------------------------------------------------------------------

#if defined _INC_WEAPON_CONFIG
public OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart) {
#else
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
#endif
	if(
		!PlayerInfo[playerid][settings][PACIFIST_MODE] &&
		!IsPlayerInFalloutGame(playerid) &&
		!IsPlayerInColorMatchEvent(playerid)
		)
	{
		new 
			string[21];

		/* Player */
		if(PlayerDamageInfoToggle[playerid]) {
			format(string, 11, "-%.1f", amount);
			PlayerTextDrawSetString(playerid, TextDrawDamageInfoPlayer[playerid][0], string);
			PlayerTextDrawShow(playerid, TextDrawDamageInfoPlayer[playerid][0]);

			if(PlayerTimer[playerid] != -1) {
				KillTimer(PlayerTimer[playerid]);
			}
			PlayerTimer[playerid] = SetTimerEx("DamageInfo_HideTextdraws", DMG_INFO_HIDE_INTERVAL, false, "d", playerid);
		}

		/* Issuer */
		if(issuerid != INVALID_PLAYER_ID) {
			if(PlayerDamageInfoToggle[issuerid]) {
				format(string, 11, "+%.1f", amount);
				PlayerTextDrawSetString(issuerid, TextDrawDamageInfoPlayer[issuerid][1], string);
				PlayerTextDrawShow(issuerid, TextDrawDamageInfoPlayer[issuerid][1]);

				if(PlayerTimer[issuerid] != -1) {
					KillTimer(PlayerTimer[issuerid]);
				}
				PlayerTimer[issuerid] = SetTimerEx("DamageInfo_HideTextdraws", DMG_INFO_HIDE_INTERVAL, false, "d", issuerid);
			}
		}
	}

	#if defined _INC_WEAPON_CONFIG

	#if defined DamageInfo_OnPlayerDamageDone
		return DamageInfo_OnPlayerDamageDone(playerid, amount, issuerid, weapon, bodypart);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDamageDone
	#undef OnPlayerDamageDone
#else
	#define _ALS_OnPlayerDamageDone
#endif

#define OnPlayerDamageDone DamageInfo_OnPlayerDamageDone
#if defined DamageInfo_OnPlayerDamageDone
	forward DamageInfo_OnPlayerDamageDone(playerid, Float:amount, issuerid, WEAPON:weapon, bodypart);
#endif

	#else

	#if defined DamageInfo_OnPlayerTakeDamage
		return DamageInfo_OnPlayerTakeDamage(playerid, issuerid, amount, weaponid, bodypart);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif

#define OnPlayerTakeDamage DamageInfo_OnPlayerTakeDamage
#if defined DamageInfo_OnPlayerTakeDamage
	forward DamageInfo_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif

#endif

#endif