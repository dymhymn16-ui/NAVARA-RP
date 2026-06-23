#define MAX_DAMAGES 20
enum damages_data
{
    gdBody,
    gdTime[24],
    gdGun,
    Float:gdDamage,
    gdNameDamages[MAX_PLAYER_NAME],
    gdNameID
}
new gDamagesData[MAX_PLAYERS][MAX_DAMAGES][damages_data];

#if !defined BODY_PART_TORSO
enum
{
	BODY_PART_TORSO = 3,
	BODY_PART_GROIN,
	BODY_PART_LEFT_ARM,
	BODY_PART_RIGHT_ARM,
	BODY_PART_LEFT_LEG,
	BODY_PART_RIGHT_LEG,
	BODY_PART_HEAD
};

stock TakePlayerDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    for(new i = MAX_DAMAGES-1; i != 0; i--)
    {
        if(gDamagesData[playerid][i-1][gdNameID] == INVALID_PLAYER_ID) continue;
        gDamagesData[playerid][i][gdBody] = gDamagesData[playerid][i-1][gdBody];
        format(gDamagesData[playerid][i][gdTime], 24, "%s", gDamagesData[playerid][i-1][gdTime]);
        gDamagesData[playerid][i][gdGun] = gDamagesData[playerid][i-1][gdGun];
        gDamagesData[playerid][i][gdDamage] = gDamagesData[playerid][i-1][gdDamage];
        format(gDamagesData[playerid][i][gdNameDamages], MAX_PLAYER_NAME, "%s", gDamagesData[playerid][i-1][gdNameDamages]);
        gDamagesData[playerid][i][gdNameID] = gDamagesData[playerid][i-1][gdNameID];
    }
    gDamagesData[playerid][0][gdBody] = bodypart;
    format(gDamagesData[playerid][0][gdTime], 24, "%s", GetFullDate());
    gDamagesData[playerid][0][gdGun] = weaponid;
    gDamagesData[playerid][0][gdDamage] = amount;
    strmid(gDamagesData[playerid][0][gdNameDamages], get_name(issuerid), 0, strlen(get_name(issuerid)), MAX_PLAYER_NAME);
    gDamagesData[playerid][0][gdNameID] = issuerid;
    return 1;
}

ClearPlayerDamage(playerid)
{
    for(new i = 0; i < MAX_DAMAGES; i++)
    {
        if(gDamagesData[playerid][i][gdBody] == -1) break;
        gDamagesData[playerid][i][gdBody] = -1;
        gDamagesData[playerid][i][gdGun] = 0;
        gDamagesData[playerid][i][gdDamage] = 0.0;
        gDamagesData[playerid][i][gdTime][0] = EOS;
        gDamagesData[playerid][i][gdNameDamages][0] = EOS;
        gDamagesData[playerid][i][gdNameID] = INVALID_PLAYER_ID;
    }
}

cmd:damages(playerid,params[])
{
    new id_damage;
    if(PlayerInfo[playerid][admin] > 0)
    {
        if(sscanf(params,"u",id_damage))
        {
            SendClientMessage(playerid,COLOR_GREY,"/damages [id of the player]");
            id_damage = playerid;
        }
        if(id_damage == INVALID_PLAYER_ID) return SendError(playerid, "Player is not online.");
    }
    else id_damage = playerid;
    new count_damages_show = 1;
    STRING_GLOBAL = "{4EBA6F}[#] Time\t{4EBA6F}Damage \t{4EBA6F}Weapon | Body Part\t{4EBA6F}Attacker\n";
    for(new i = 0; i < MAX_DAMAGES; i++)
    {
        if(gDamagesData[id_damage][i][gdBody] == -1) continue;
        new to_part_body[32], name_damage_weapon[32];
        if(gDamagesData[id_damage][i][gdGun] < 0 || gDamagesData[id_damage][i][gdGun] > 50) name_damage_weapon = "Unknown";
        else if(gDamagesData[id_damage][i][gdGun] < 47) strmid(name_damage_weapon, WEAPON_Name[gDamagesData[id_damage][i][gdGun]], 0, strlen(WEAPON_Name[gDamagesData[id_damage][i][gdGun]]), 32);
        else if(gDamagesData[id_damage][i][gdGun] >= 48) name_damage_weapon="Vehicle Injuries";

        switch(gDamagesData[id_damage][i][gdBody])
        {
            case BODY_PART_TORSO: to_part_body = "Torso";
            case BODY_PART_GROIN: to_part_body = "Groin";
            case BODY_PART_LEFT_ARM: to_part_body = "Left Arm";
            case BODY_PART_RIGHT_ARM: to_part_body = "Right Arm";
            case BODY_PART_LEFT_LEG: to_part_body = "Left Leg";
            case BODY_PART_RIGHT_LEG: to_part_body = "Right Leg";
            case BODY_PART_HEAD: to_part_body = "Head";
            default: to_part_body = "Unknown";
        }

        fmt(STRING_GLOBAL, "%s{AFAFAF}[%d] {FFFFFF}%s\t%.1f\t%s | %s\t%s(%d)\n",
            STRING_GLOBAL, count_damages_show,
            gDamagesData[id_damage][i][gdTime],
            gDamagesData[id_damage][i][gdDamage],
            name_damage_weapon, to_part_body,
            gDamagesData[id_damage][i][gdNameDamages],
            gDamagesData[id_damage][i][gdNameID]);
        count_damages_show++;
    }
    if(!count_damages_show) SendError(playerid, "Player has no records.");
    else show_dialog(playerid, d_none, DIALOG_STYLE_TABLIST_HEADERS, get_name(id_damage), STRING_GLOBAL, "Close", "");
    return 1;
}