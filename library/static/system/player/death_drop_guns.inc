static const
    WEAPON_Slot[] = {
    0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    10, 10, 10, 10, 10, 10,
    8, 8, 8,
    0, 0, 0,
    2, 2, 2,
    3, 3, 3,
    4, 4,
    5, 5,
    4,
    6, 6,
    7, 7, 7, 7,
    8,
    12,
    9, 9, 9,
    11, 11, 11
};

#define MAX_OBJ_DEATH_DROP_GUNS 2000

#define PICKUP_TYPE_ID_DEATH_DROP_GUNS 1

#define TIME_TO_DESTROY_DROPPED_GUNS 4 * 60


static enum dGunEnum
{
	Float:ObjPos[3],
	ObjID,
	ObjData[2],
	Text3D:label,
	Expire,
	bool:Dropped
};
static dGunData[MAX_OBJ_DEATH_DROP_GUNS][dGunEnum];

static s_TimerSeconds;


static GunObjects[47] = {
	0,331,333,334,335,336,337,338,339,341,321,322,323,324,325,326,342,343,344,
	0,0,0,346,347,348,349,350,351,352,353,355,356,372,357,358,359,360,361,362,
	363,364,365,366,367,368,368,371
};

// --------------------

public OnGameModeExit()
{
	#if defined DropGun_OnGameModeExit
		return DropGun_OnGameModeExit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif

#define OnGameModeExit DropGun_OnGameModeExit
#if defined DropGun_OnGameModeExit
	forward DropGun_OnGameModeExit();
#endif


alias:dropgun("dgun");
cmd:dropgun(playerid, params[])
{
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /dropgun [ammo]");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendError(playerid, "Shoma dar in halat nmitavanid in kar ra anjam dahid.");
	if(!player_have_weapon(playerid)) return SendError(playerid, "Selah bayad dar dastanetan bashad.");
	
	new gun_name[24], gun_id = GetPlayerWeapon(playerid);
	GetWeaponName(gun_id, gun_name, sizeof(gun_name));

	new weapon, ammo;
    GetPlayerWeaponData(playerid, WEAPON_Slot[gun_id], weapon, ammo);
    if(ammo < params[0]) return SendError(playerid, "Shoma be andaze vared shode ammo nadarid.");

	new Float:pPosX, Float:pPosY, Float:pPosZ;
	GetPlayerPos(playerid, pPosX, pPosY, pPosZ);

	RemovePlayerWeapon(playerid, gun_id);

	take_weapon(playerid, gun_id, params[0]);

	CreateDroppedGun(playerid, gun_id, params[0], pPosX, pPosY, pPosZ, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	return 1;
}

alias:pickupgun("pgun");
CMD:pickupgun(playerid) {
    new f = MAX_OBJ_DEATH_DROP_GUNS+1;
    new Float:x1,Float:y1,Float:z1;
	GetPlayerPos(playerid,x1,y1,z1);
	for(new a = 0; a < MAX_OBJ_DEATH_DROP_GUNS; a++)
	{
	    if(GetDistance(x1, y1, dGunData[a][ObjPos][0], dGunData[a][ObjPos][1]) <= 1.0)
	    {
	        f = a;
	        break;
	    }
	}
	if(f > MAX_OBJ_DEATH_DROP_GUNS) return 1;
	
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendError(playerid, "Shoma dar in halat nmitavanid in kar ra anjam dahid.");
	if(PlayerInfo[playerid][gun_lic] == 0 && dGunData[f][Dropped]) return SendError(playerid, "Shoma mojavez aslahe nadarid.");

	if(dGunData[f][Dropped])
	{
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 800);
		SetTimerEx("PickWeaponT", 800, 0, "dd", playerid, f);
	}

	if(dGunData[f][Dropped])
	{
		DestroyDynamicObject(dGunData[f][ObjID]);
	}else
	{
		DestroyDynamicPickup(dGunData[f][ObjID]);
	}
	
	DestroyDynamic3DTextLabel(dGunData[f][label]);


	give_weapon(playerid, dGunData[f][ObjData][0], dGunData[f][ObjData][1]);

	dGunData[f][ObjPos][0] = 0.0;
	dGunData[f][ObjPos][1] = 0.0;
	dGunData[f][ObjPos][2] = 0.0;
	dGunData[f][ObjID] = -1;
	dGunData[f][Expire] = 0;

	dGunData[f][Dropped] = false;

	dGunData[f][ObjData][0] = 0;
	dGunData[f][ObjData][1] = 0;

	return 1;
}

forward PickWeaponT(playerid, f);
public PickWeaponT(playerid, f)
{
	if(dGunData[f][Dropped])
	{
		DestroyDynamicObject(dGunData[f][ObjID]);
	}else
	{
		DestroyDynamicPickup(dGunData[f][ObjID]);
	}

	DestroyDynamic3DTextLabel(dGunData[f][label]);

	give_weapon(playerid, dGunData[f][ObjData][0], dGunData[f][ObjData][1]);
	dGunData[f][ObjPos][0] = 0.0;
	dGunData[f][ObjPos][1] = 0.0;
	dGunData[f][ObjPos][2] = 0.0;
	dGunData[f][ObjID] = -1;
	dGunData[f][Expire] = 0;

	dGunData[f][Dropped] = false;

	dGunData[f][ObjData][0] = 0;
	dGunData[f][ObjData][1] = 0;
}

DropGuns_PlayerDeath(playerid)
{
	#pragma unused playerid
	return 1;
}

stock CreateDroppedGun(playerid, GunID, GunAmmo, Float:gPosX, Float:gPosY, Float:gPosZ, world, interiorId, dropped=true)
{
	new f = -1;
    for(new a = 0; a < MAX_OBJ_DEATH_DROP_GUNS; a++)
    {
        if(dGunData[a][ObjPos][0] == 0.0)
        {
            f = a;
            break;
        }
    }
    if(f == -1) return;
   
    dGunData[f][Expire] = timestamp + (TIME_TO_DESTROY_DROPPED_GUNS);

    dGunData[f][ObjData][0] = GunID;
	dGunData[f][ObjData][1] = GunAmmo;
	dGunData[f][ObjPos][0] = gPosX;
	dGunData[f][ObjPos][1] = gPosY;
	dGunData[f][ObjPos][2] = gPosZ;

	dGunData[f][Dropped] = dropped;

	if(dropped)
	{
		dGunData[f][ObjID] = CreateDynamicObject(GunObjects[GunID], dGunData[f][ObjPos][0], dGunData[f][ObjPos][1], dGunData[f][ObjPos][2]-1.0, 93.7, 120.0, float(random(360)), .worldid = world, .interiorid = interiorId);
	}else{
		dGunData[f][ObjID] = CreateDynamicPickup(GunObjects[GunID], PICKUP_TYPE_ID_DEATH_DROP_GUNS, dGunData[f][ObjPos][0], dGunData[f][ObjPos][1], dGunData[f][ObjPos][2]);
	}

	new gun_name[50];
	GetWeaponName(GunID, gun_name, sizeof(gun_name));

	new string_drop[300];
	format(string_drop, sizeof string_drop, "{3EF27D}Drop\n{FFFFFF} %s\nAmmo : %d\nThrown by : {FFFFFF}%s\n{FFFFFF}Press {3EF27D}'ALT'", gun_name, GunAmmo, PlayerInfo[playerid][name]);
	dGunData[f][label] = CreateDynamic3DTextLabel(string_drop, 0x828282FF, dGunData[f][ObjPos][0], dGunData[f][ObjPos][1], dGunData[f][ObjPos][2], .drawdistance=8.5, .testlos=1, .worldid = world, .interiorid = interiorId);
	return;
}

DropGun_OneSecTimer()
{
	if(s_TimerSeconds == 10) {
		s_TimerSeconds = 0;
		for(new f = 0; f < MAX_OBJ_DEATH_DROP_GUNS; f++)
	    {
	        if(dGunData[f][ObjData][0] != 0)
	        {
	        	if(timestamp > dGunData[f][Expire])
	        	{
					if(dGunData[f][Dropped])
					{
						DestroyDynamicObject(dGunData[f][ObjID]);
					}else
					{
						DestroyDynamicPickup(dGunData[f][ObjID]);
					}

					DestroyDynamic3DTextLabel(dGunData[f][label]);

					dGunData[f][ObjPos][0] = 0.0;
					dGunData[f][ObjPos][1] = 0.0;
					dGunData[f][ObjPos][2] = 0.0;
					dGunData[f][ObjID] = -1;
					dGunData[f][Expire] = 0;

					dGunData[f][ObjData][0] = 0;
					dGunData[f][ObjData][1] = 0;
	        	}
	        }
	    }
	}
	else
	{
		s_TimerSeconds++;
	}
}

DropGuns_PlayerKeyStateChange(playerid, newkeys)
{
	if(newkeys == KEY_WALK)
	{
		callcmd::pickupgun(playerid);
	}
}