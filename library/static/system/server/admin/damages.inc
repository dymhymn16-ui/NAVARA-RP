static playerLastHitID[MAX_PLAYERS];
static playerLastHitTick[MAX_PLAYERS];
static playerDeathTimer[MAX_PLAYERS];
new playerRetardKill[MAX_PLAYERS char];
static playerFakeKill[MAX_PLAYERS char];

static Float:WeaponDamage[] = {
	1.0, // 0 - Fist
	1.0, // 1 - Brass knuckles
	1.0, // 2 - Golf club
	1.0, // 3 - Nitestick
	1.0, // 4 - Knife
	1.0, // 5 - Bat
	1.0, // 6 - Shovel
	1.0, // 7 - Pool cue
	1.0, // 8 - Katana
	1.0, // 9 - Chainsaw
	1.0, // 10 - Dildo
	1.0, // 11 - Dildo 2
	1.0, // 12 - Vibrator
	1.0, // 13 - Vibrator 2
	1.0, // 14 - Flowers
	1.0, // 15 - Cane
	82.5, // 16 - Grenade
	0.0, // 17 - Teargas
	1.0, // 18 - Molotov
	9.9, // 19 - Vehicle M4 (custom)
	46.2, // 20 - Vehicle minigun (custom)
	82.5, // 21 - Vehicle rocket (custom)
	8.25, // 22 - Colt 45
	13.2, // 23 - Silenced
	46.2, // 24 - Deagle
	3.3, // 25 - Shotgun
	3.3, // 26 - Sawed-off
	4.95, // 27 - Spas
	6.6, // 28 - UZI
	8.25, // 29 - MP5
	9.9, // 30 - AK47
	9.9, // 31 - M4
	6.6, // 32 - Tec9
	24.75, // 33 - Cuntgun
	41.25, // 34 - Sniper
	82.5, // 35 - Rocket launcher
	82.5, // 36 - Heatseeker
	1.0, // 37 - Flamethrower
	46.2, // 38 - Minigun
	82.5, // 39 - Satchel
	0.0, // 40 - Detonator
	0.33, // 41 - Spraycan
	0.33, // 42 - Fire extinguisher
	0.0, // 43 - Camera
	0.0, // 44 - Night vision
	0.0, // 45 - Infrared
	0.0, // 46 - Parachute
	0.0, // 47 - Fake pistol
	2.64, // 48 - Pistol whip (custom)
	9.9, // 49 - Vehicle
	330.0, // 50 - Helicopter blades
	82.5, // 51 - Explosion
	1.0, // 52 - Car park (custom)
	1.0, // 53 - Drowning
	165.0  // 54 - Splat
};

new Float:MaxDistShot[17] = {45.0, 45.0, 45.0, 50.0, 45.0, 50.0, 45.0, 55.0, 100.0, 120.0, 45.0, 110.0, 320.0, 0.0, 0.0, 0.0, 75.0};

stock IsPlayerPausedAC(playerid) return pl_afk_time[playerid] >= 2;

stock DamageSystem(playerid, weap, hitid, hittype, Float:topldist) 
{
	if(hitid != INVALID_PLAYER_ID) {
		if(!PacifistMode(playerid, hitid)) return 0;
	}

    if(CounterStrikePlayerTakeDMG(playerid, hitid) == 0) return 0;

	if((!IsPlayerNPC(hitid) && !playerRetardKill{hitid} && !playerFakeKill{hitid} && hittype == BULLET_HIT_TYPE_PLAYER)
	 	|| hittype == BULLET_HIT_TYPE_VEHICLE)
	{
		new Float:ndmg, Float:dmg = WeaponDamage[weap];

		if(25 <= weap <= 27)
		{
			ndmg = (topldist / 7.5);
			if(ndmg >= 1.0 && (5.0 <= topldist <= MaxDistShot[weap - 22])) dmg = (dmg / ndmg);
		}

		playerLastHitID[hitid] = playerid;
		playerLastHitTick[hitid] = GetTickCount();

		if(hittype == BULLET_HIT_TYPE_PLAYER)
		{
			new Float:heal = p_t_info[hitid][p_health], Float:arm = p_t_info[hitid][p_armour];

            MRP_OnPlayerTakeDamage(playerid, hitid, dmg, weap);

			if(!arm)
			{
				if((heal - dmg) > 0.0)
                {
                    set_health(hitid, (heal - dmg));
                }
				else
				{
					DeathSystem(hitid, playerid, weap);
                    HideDamage(playerid);
				}
			}
			else if(dmg > arm)
			{
				set_armour(hitid, 0.0);
				if((heal - (dmg - arm)) > 0.0)
                {
					set_health(hitid, (heal - (dmg - arm)));
                }
				else
                {
					DeathSystem(hitid, playerid, weap);
                    HideDamage(playerid);
                }
			}
			else set_armour(hitid, (arm - dmg));
			
            ShowDamage(playerid, hitid);
		}
		else if(hittype == BULLET_HIT_TYPE_VEHICLE)
		{
			new Float:heal = veh_info[hitid -1][v_health];
			if((heal - dmg) > 300.0) SetVehicleHealth(hitid, (heal - dmg));
			else
				SetVehicleHealth(hitid, 299.0);
		}
	}
	return 1;
}

callback: DeathSystemTimer(playerid, killerid, reason)
{
    DeathSystem(playerid, killerid, reason);
}

static DeathSystem(playerid, killerid, reason)
{
    #if defined OnPlayerDeathSystemEnterAC
		if(!OnPlayerDeathSystemEnterAC(playerid, killerid, reason)) return;
	#endif

    if(playerRetardKill{playerid} || playerFakeKill{playerid}) return;
    playerRetardKill{playerid} = 1;

    #if defined Damages_OnPlayerDeath
		Damages_OnPlayerDeath(playerid, killerid, reason);
	#else
	    #pragma unused killerid
	    #pragma unused reason
	#endif

	set_health(playerid, 1.0);
	ResetPlayerWeapons(playerid);
	ClearAnimations(playerid);
	TogglePlayerControllable(playerid, 0);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	if(playerDeathTimer[playerid]) KillTimer(playerDeathTimer[playerid]);
    playerDeathTimer[playerid] = SetTimerEx("Damages_DeathRespawn", 3000, 0, "i", playerid);

    OnPlayerSyncDeath(playerid, killerid, reason);

	new anim = GetPlayerAnimationIndex(playerid);
	if(1195 <= anim <= 1198) // jump
	{
	    ApplyAnimation(playerid, "PED", "KO_skid_back", 4.1, 0, 0, 0, 1, 0, 1);
		return;
	}
	if((1538 <= anim <= 1544) || anim == 1250) // water
	{
		ApplyAnimation(playerid, "PED", "Drown", 4.1, 0, 0, 0, 1, 0, 1);
		return;
	}
	ApplyAnimation(playerid, "PED", "KO_shot_front", 4.1, 0, 0, 0, 1, 0, 1);
}

public OnPlayerConnect(playerid)
{
	playerFakeKill{playerid} = 0;
	playerRetardKill{playerid} = 0;

    #if defined Damages_OnPlayerConnect
		return Damages_OnPlayerConnect(playerid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#if defined Damages_OnPlayerConnect
	forward Damages_OnPlayerConnect(playerid);
#endif
#define	OnPlayerConnect Damages_OnPlayerConnect

public OnPlayerSpawn(playerid)
{
	if(!IsPlayerNPC(playerid))
	{
	    playerFakeKill{playerid} = 0;
	    playerRetardKill{playerid} = 0;
	}
	#if defined Damages_OnPlayerSpawn
		return Damages_OnPlayerSpawn(playerid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif
#if defined Damages_OnPlayerSpawn
	forward Damages_OnPlayerSpawn(playerid);
#endif
#define	OnPlayerSpawn Damages_OnPlayerSpawn

public OnPlayerDeath(playerid, killerid, reason)
{
	if(playerRetardKill{playerid}) return 0;

	if(!IsPlayerNPC(playerid))
	{
		if(killerid != INVALID_PLAYER_ID)
		{
			if(!IsPlayerConnected(killerid) || !IsPlayerStreamedIn(playerid, killerid))
			{
		        return 0;
		    }
			if(killerid == playerid || playerFakeKill{playerid})
			{
		        return 0;
		    }
   		}
        
		if(killerid == INVALID_PLAYER_ID && reason == 255 && (GetTickCount() - playerLastHitTick[playerid]) < 1000) killerid = playerLastHitID[playerid];

		playerFakeKill{playerid} = 1;
	}
	#if defined Damages_OnPlayerDeath
		return Damages_OnPlayerDeath(playerid, killerid, reason);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif
#if defined Damages_OnPlayerDeath
	forward Damages_OnPlayerDeath(playerid, killerid, reason);
#endif
#define	OnPlayerDeath Damages_OnPlayerDeath


callback: Damages_DeathRespawn(playerid)
{
    playerRetardKill{playerid} =
    playerDeathTimer[playerid] = 0;
    SetPlayerHealth(playerid, 100.0);
	SetPlayerArmour(playerid, 0.0);
    SetPlayerVirtualWorld(playerid, 10444);
    TogglePlayerControllable(playerid, 1);
	SpawnPlayer(playerid);
}