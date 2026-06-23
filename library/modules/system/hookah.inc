#define MAX_HOOKAH_OBJECT   13

new Hookah[MAX_PLAYERS][MAX_HOOKAH_OBJECT];
new Text3D:HookahText[MAX_PLAYERS] = {Text3D:INVALID_3DTEXT_ID, ...};
new Float:HookahPos[MAX_PLAYERS][3];
new bool:HookahAreaStatus[MAX_PLAYERS];
new HookahSmokeTimer[MAX_PLAYERS];
new HookahArea[MAX_PLAYERS] = {-1, ...};

forward SetupHookah(playerid, Float: x, Float: y, Float: z, Float: angle, object_world, object_int);
public SetupHookah(playerid, Float: x, Float: y, Float: z, Float: angle, object_world, object_int)
{
    print("Debug Hookah 1");

    HookahPos[playerid][0] = x;
    HookahPos[playerid][1] = y;
    HookahPos[playerid][2] = z;

    new string[64];
    format(string, sizeof(string), "Ghelyan\nPlaced by: {%06x}%s", GetPlayerColor(playerid) >>> 8, Name(playerid));
    HookahArea[playerid] = CreateDynamicSphere(x, y, z, 5.0, object_world, object_int);
    // UpdateAreaInfo(HookahArea[playerid], TYPE_HOOKAH_AREA, AREA_SUBTYPE_INVALID_ID, playerid);

    print("Debug Hookah 2");

    new Float: ox, Float: oy, Float: oz, Float: orx, Float: ory, Float: orz;
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.375366, 0.117797, 2.376281, 0.000000, 179.999984, -179.999893, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][0] = CreateDynamicObject(2726, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][0], 0, 2592, "ab_veg", "ab_slotBase", 0xFFFFFFFF);

    HookahText[playerid] = CreateDynamic3DTextLabel(string, -1, ox, oy, oz+0.5, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, object_world, object_int);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.364379, 0.116699, 2.097411, 0.000000, 179.999984, 179.999893, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][1] = CreateDynamicObject(14705, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][1], 0, 6869, "vegastemp1", "vgnbarbwall6_256", 0xFFFFFFFF);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.374877, 0.108520, 2.694518, 0.000000, 0.000022, 0.000000, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][2] = CreateDynamicObject(19993, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][2], 0, 1381, "cranes_dyn2", "ws_sheetsteel", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.359008, 0.136230, 2.766356, 0.000009, 0.000027, 28.699977, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][3] = CreateDynamicObject(19187, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][3], 0, 18996, "mattextures", "lava1", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][3], 1, 18996, "mattextures", "lava1", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.356079, 0.081176, 2.766356, 0.000009, 0.000027, 28.699977, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][4] = CreateDynamicObject(19187, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][4], 0, 18996, "mattextures", "lava1", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][4], 1, 18996, "mattextures", "lava1", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.405883, 0.101196, 2.766356, 0.000024, 0.000011, 96.999893, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][5] = CreateDynamicObject(19187, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][5], 0, 18996, "mattextures", "lava1", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][5], 1, 18996, "mattextures", "lava1", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.375854, 0.105957, 2.653441, 0.000000, 0.000022, 0.000000, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][6] = CreateDynamicObject(11744, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][6], 0, 14629, "ab_chande", "ab_goldpipe", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.376586, 0.213989, 2.359130, 78.500022, 0.000115, -0.000113, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][7] = CreateDynamicObject(18634, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][7], 0, -1, "none", "none", 0xFF000000);
    SetDynamicObjectMaterial(Hookah[playerid][7], 1, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][7], 2, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.376586, 0.448608, 2.574218, -88.300033, -179.999206, 0.000809, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][8] = CreateDynamicObject(18634, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][8], 0, 10101, "2notherbuildsfe", "ferry_build14", 0xFF000000);
    SetDynamicObjectMaterial(Hookah[playerid][8], 1, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][8], 2, 10101, "2notherbuildsfe", "ferry_build14", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.380004, 0.072753, 1.939940, -16.899976, 0.000023, 0.000006, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][9] = CreateDynamicObject(19822, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][9], 0, 14581, "ab_mafiasuitea", "goldPillar", 0xFFFFFFFF);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.378784, 0.637329, 2.269957, 25.100112, 179.999938, -179.999847, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][10] = CreateDynamicObject(18632, ox, oy, oz, orx, ory, orz, object_world, object_int);
    SetDynamicObjectMaterial(Hookah[playerid][10], 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
    SetDynamicObjectMaterial(Hookah[playerid][10], 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][10], 2, 14581, "ab_mafiasuitea", "goldPillar", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][10], 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(Hookah[playerid][10], 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.376586, 0.672851, 0.861267, -1.999984, 0.000022, 0.000000, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][11] = CreateDynamicObject(18673, ox, oy, oz, orx, ory, orz, object_world, object_int);
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.371948, 0.102294, 1.171854, 0.000000, 0.000022, 0.000000, ox, oy, oz, orx, ory, orz);
    Hookah[playerid][12] = CreateDynamicObject(18673, ox, oy, oz, orx, ory, orz, object_world, object_int);

    print("Debug Hookah 3");

    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

    do_action(playerid, "Yek ghelyan gozasht");

    print("Debug Hookah 4");
    
    SendInfo(playerid, "Press 'ALT' to smoke hookah.");
    return 1;
}

ClearHookah(playerid, type = 0)
{
    if(type == 1 || type == 2)
    {
        for(new i = 0; i < MAX_HOOKAH_OBJECT; i++)
        {
            if(Hookah[playerid][i] != INVALID_OBJECT_ID)
            {
                DestroyDynamicObject(Hookah[playerid][i]);
                Hookah[playerid][i] = INVALID_OBJECT_ID;
            }
        }
        if(HookahText[playerid] != Text3D:INVALID_3DTEXT_ID)
        {
            DestroyDynamic3DTextLabel(HookahText[playerid]);
            HookahText[playerid] = Text3D:INVALID_3DTEXT_ID;
        }
        if(HookahArea[playerid] != -1)
        {
            DestroyDynamicArea(HookahArea[playerid]);
            HookahArea[playerid] = -1;
        }
        for(new i = 0; i < 3; i++) HookahPos[playerid][i] = 0.0;
        HookahAreaStatus[playerid] = false;
        HookahSmokeTimer[playerid] = 0;
        if(type == 2)
        {
            do_action(playerid, "Ghelyan mikeshad");
        }
        return 1;
    }
    for(new i = 0; i < MAX_HOOKAH_OBJECT; i++) Hookah[playerid][i] = INVALID_OBJECT_ID;
    HookahText[playerid] = Text3D:INVALID_3DTEXT_ID;
    HookahArea[playerid] = -1;
    for(new i = 0; i < 3; i++) HookahPos[playerid][i] = 0.0;
    HookahAreaStatus[playerid] = false;
    HookahSmokeTimer[playerid] = 0;
    return 1;
}

CMD:hookah(playerid, params[])
{
    if(ReturnPlayerHookah(playerid) == 0)
        return SendError(playerid, "Shoma Ghelyon Nadarid.");

    if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
        return SendError(playerid, "Az Inja Kharej Shavid.");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendError(playerid, "Az Mashin Kharej Shavid.");
    if(AntiDMZone(playerid))
        return SendError(playerid, "Shoma Dar \"Green Zone\" Hastid.");
    
    // show_dialog(playerid, D_HOOKAH, DIALOG_STYLE_LIST, ""scm_dialog"Ghelyan", ""c_green"[1]"c_white" Gozashtan\n"c_green"[2]"c_white" Bardashtan", "Select", "Cancel");

    if(HookahArea[playerid] == -1) 
    {
        new Float:PlPos[4];
        GetPlayerPos(playerid, PlPos[0], PlPos[1], PlPos[2]);
        GetPlayerFacingAngle(playerid, PlPos[3]);
        SetupHookah(playerid, PlPos[0]+floatcos(PlPos[3]+90, degrees), PlPos[1]+floatsin(PlPos[3]+90, degrees), PlPos[2]-2.8, PlPos[3]+90, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        return 1;
    }

    if(IsPlayerInRangeOfPoint(playerid, 5.0, HookahPos[playerid][0], HookahPos[playerid][1], HookahPos[playerid][2])) 
    {
        ClearHookah(playerid, 2);
    }
    return 1;
}

CMD:dhookah(playerid, params[])
{
    if(PlayerInfo[playerid][admin] < 3) return 1;
    foreach(new i: Player)
    {
        if(HookahArea[i] == -1) continue;
        if(IsPlayerInRangeOfPoint(playerid, 5.0, HookahPos[i][0], HookahPos[i][1], HookahPos[i][2]))
        {
            ClearHookah(i, 1);
            break;
        }
    }
    return 1;
}

GetObjectOffset(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:off_x, Float:off_y, Float:off_z, Float:rot_x, Float:rot_y, Float:rot_z, &Float:ox, &Float:oy, &Float:oz, &Float:orx, &Float:ory, &Float: orz)
{
    new
        Float:sin[3],
        Float:cos[3],
        Float:pos[3],
        Float:rot[3];

    pos[0] = x, pos[1] = y, pos[2] = z;
    rot[0] = rx, rot[1] = ry, rot[2] = rz;

    EDIT_FloatEulerFix(rot[0], rot[1], rot[2]);

    cos[0] = floatcos(rot[0], degrees); cos[1] = floatcos(rot[1], degrees); cos[2] = floatcos(rot[2], degrees); sin[0] = floatsin(rot[0], degrees); sin[1] = floatsin(rot[1], degrees); sin[2] = floatsin(rot[2], degrees);
    pos[0] = pos[0] + off_x * cos[1] * cos[2] - off_x * sin[0] * sin[1] * sin[2] - off_y * cos[0] * sin[2] + off_z * sin[1] * cos[2] + off_z * sin[0] * cos[1] * sin[2];
    pos[1] = pos[1] + off_x * cos[1] * sin[2] + off_x * sin[0] * sin[1] * cos[2] + off_y * cos[0] * cos[2] + off_z * sin[1] * sin[2] - off_z * sin[0] * cos[1] * cos[2];
    pos[2] = pos[2] - off_x * cos[0] * sin[1] + off_y * sin[0] + off_z * cos[0] * cos[1];
    rot[0] = asin(cos[0] * cos[1]); rot[1] = atan2(sin[0], cos[0] * sin[1]) + rot_z; rot[2] = atan2(cos[1] * cos[2] * sin[0] - sin[1] * sin[2], cos[2] * sin[1] - cos[1] * sin[0] * -sin[2]);
    cos[0] = floatcos(rot[0], degrees); cos[1] = floatcos(rot[1], degrees); cos[2] = floatcos(rot[2], degrees); sin[0] = floatsin(rot[0], degrees); sin[1] = floatsin(rot[1], degrees); sin[2] = floatsin(rot[2], degrees);
    rot[0] = asin(cos[0] * sin[1]); rot[1] = atan2(cos[0] * cos[1], sin[0]); rot[2] = atan2(cos[2] * sin[0] * sin[1] - cos[1] * sin[2], cos[1] * cos[2] + sin[0] * sin[1] * sin[2]);
    cos[0] = floatcos(rot[0], degrees); cos[1] = floatcos(rot[1], degrees); cos[2] = floatcos(rot[2], degrees); sin[0] = floatsin(rot[0], degrees); sin[1] = floatsin(rot[1], degrees); sin[2] = floatsin(rot[2], degrees);
    rot[0] = atan2(sin[0], cos[0] * cos[1]) + rot_x; rot[1] = asin(cos[0] * sin[1]); rot[2] = atan2(cos[2] * sin[0] * sin[1] + cos[1] * sin[2], cos[1] * cos[2] - sin[0] * sin[1] * sin[2]);
    cos[0] = floatcos(rot[0], degrees); cos[1] = floatcos(rot[1], degrees); cos[2] = floatcos(rot[2], degrees); sin[0] = floatsin(rot[0], degrees); sin[1] = floatsin(rot[1], degrees); sin[2] = floatsin(rot[2], degrees);
    rot[0] = asin(cos[1] * sin[0]); rot[1] = atan2(sin[1], cos[0] * cos[1]) + rot_y; rot[2] = atan2(cos[0] * sin[2] - cos[2] * sin[0] * sin[1], cos[0] * cos[2] + sin[0] * sin[1] * sin[2]);

    ox = pos[0];
    oy = pos[1];
    oz = pos[2];
    orx = rot[0];
    ory = rot[1];
    orz = rot[2];
}

EDIT_FloatEulerFix(&Float:rot_x, &Float:rot_y, &Float:rot_z)
{
    EDIT_FloatGetRemainder(rot_x, rot_y, rot_z);
    if((!floatcmp(rot_x, 0.0) || !floatcmp(rot_x, 360.0))
    && (!floatcmp(rot_y, 0.0) || !floatcmp(rot_y, 360.0)))
    {
        rot_y = 0.0000002;
    }
    return 1;
}

EDIT_FloatGetRemainder(&Float:rot_x, &Float:rot_y, &Float:rot_z)
{
    EDIT_FloatRemainder(rot_x, 360.0);
    EDIT_FloatRemainder(rot_y, 360.0);
    EDIT_FloatRemainder(rot_z, 360.0);
    return 1;
}

EDIT_FloatRemainder(&Float:remainder, Float:value)
{
    if(remainder >= value)
    {
        while(remainder >= value)
        {
            remainder = remainder - value;
        }
    }
    else if(remainder < 0.0)
    {
        while(remainder < 0.0)
        {
            remainder = remainder + value;
        }
    }
    return 1;
}

HookahPlayerTimerOneSecond(playerid) {
    if(HookahSmokeTimer[playerid] > 0)
    {
        HookahSmokeTimer[playerid]--;
        if(HookahSmokeTimer[playerid] == 0)
        {
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
        }
    }
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
    foreach(new i: logged_players) {
        if (areaid == HookahArea[i]) {
            HookahAreaStatus[playerid] = true;
            return 1;
        }
    }
    
    #if defined Hookah_OnPlayerEnterDynArea
        return Hookah_OnPlayerEnterDynArea(playerid, areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif

#define OnPlayerEnterDynamicArea Hookah_OnPlayerEnterDynArea
#if defined Hookah_OnPlayerEnterDynArea
    forward Hookah_OnPlayerEnterDynArea(playerid, areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
    foreach(new i: logged_players) {
        if (areaid == HookahArea[i]) {
            HookahAreaStatus[playerid] = false;
            return 1;
        }
    }

    #if defined Hookah_OnPlayerLeaveDynArea
        return Hookah_OnPlayerLeaveDynArea(playerid, areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerLeaveDynamicArea
    #undef OnPlayerLeaveDynamicArea
#else
    #define _ALS_OnPlayerLeaveDynamicArea
#endif

#define OnPlayerLeaveDynamicArea Hookah_OnPlayerLeaveDynArea
#if defined Hookah_OnPlayerLeaveDynArea
    forward Hookah_OnPlayerLeaveDynArea(playerid, areaid);
#endif