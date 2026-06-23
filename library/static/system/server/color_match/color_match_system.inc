#if !defined RGB_RGBAToARGB
    #define RGB_RGBAToARGB(%0)              ((((%0) << 24) & 0xFF000000) | (((%0) >>> 8) & 0xFFFFFF))
#endif

#define CM_EVENT_TIME       (120)
#define CM_MIN_PLAYERS      (3)
#define CM_MAX_PLAYERS      (20)
#define CM_SETUP_TIME       (20)

static Float:SavePos2[MAX_PLAYERS][3];
static SaveIntWorld[MAX_PLAYERS][2];

static enum    _:E_OBJECTID
{
    OBJ_ORANGE,
    OBJ_RED,
    OBJ_GREEN,
    OBJ_YELLOW,
    OBJ_PURPLE,
    OBJ_PINK,
    OBJ_MAROON,
    OBJ_BLUE,
    OBJ_WHITE
}
static enum    _:E_GAMESTAGE
{
    STAGE_NONE,
    STAGE_SETUP,
    STAGE_PLAYING
}
static
    ColorMatchObjects[9] = {INVALID_OBJECT_ID, ...},
    ColorMatchNames[9][7] = {"Orange", "Red", "Green", "Yellow", "Purple", "Pink", "Maroon", "Blue", "White"},
    ColorMatchColors[9] = {0xFF7F00FF, 0xEE0000FF, 0x00EE00FF, 0xFFFF00FF, 0x9B30FFFF, 0xFF1493FF, 0x8B1A1AFF, 0x1E90FFFF, 0xFFFFFFFF},
    ColorMatchCurrent = -1,
    ColorMatchPlayers,
    ColorMatchTimer = -1,
    ColorMatchFallTimer = -1,
    ColorMatchEventTimer = -1,
    ColorMatchStage = STAGE_NONE,
    bool: InCMEvent[MAX_PLAYERS];

new Text:TD_ColorMatch[9];
static PlayerText:TD_P_ColorMatch[MAX_PLAYERS] = {PlayerText: INVALID_TEXT_DRAW, ...};

forward CM_SetupTimer(time);
public CM_SetupTimer(time)
{
    new string[144], soundid = 0;
    time--;
    
    if(time < 1) {
        if(ColorMatchPlayers < CM_MIN_PLAYERS) {
            SendClientMessageToAll(0xEA266AFF, "[ColorMatch] {FFFFFF}Zaman Event Be Payan Resid.");
            ColorMatch_CleanUp(1);
            return 1;
        }else{
            ColorMatchStage = STAGE_PLAYING;
            ColorMatchTimer = SetTimer("CM_PickColor", 2000, false);
            ColorMatchFallTimer = SetTimer("CM_FallTimer", 500, true);
            ColorMatchEventTimer = SetTimerEx("CM_EndEvent", 1000, false, "i", CM_EVENT_TIME);
            //TextDrawSetString(TD_ColorMatch, "_");
            
            format(string, sizeof(string), "~n~~n~~n~~y~~h~~h~Event ~g~~h~Started!");
            soundid = 1057;
        }
    }else{
        
        if(time <= 5) format(string, sizeof(string), "~n~~n~~n~~y~~h~~h~Event: ~y~~h~%d", time), soundid = 1056;
        if(time == 10) 
            SendClientMessageToAll(0xD76B00FF, ">> Event ColorMatch: {D7BC00}Start up 10 Seconds. {FCB185}(Join with /cm)");
    }
    
    for(new i, mp = GetPlayerPoolSize(); i <= mp; i++)
    {
        if(!IsPlayerConnected(i) || !InCMEvent[i]) continue;
        if(soundid != 0) PlayerPlaySound(i, soundid, 0.0, 0.0, 0.0), GameTextForPlayer(i, string, 1000, 4);
        
        if(time < 1)
        {
            for(new TD; TD < sizeof TD_ColorMatch; TD++) TextDrawShowForPlayer(i, TD_ColorMatch[TD]);

            //for(new TD; TD < sizeof TD_BestCM; TD++) TextDrawHideForPlayer(i, TD_BestCM[TD]);

            new Float: x, Float: y, Float: z;
            GetDynamicObjectPos(ColorMatchObjects[ random(9) ], x, y, z);
            SetPlayerPos(i, x + frandom(1.0, -1.0), y + frandom(1.0, -1.0), z + 1.0);
        }
    }
    
    if(time > 0) ColorMatchTimer = SetTimerEx("CM_SetupTimer", 1000, false, "i", time);
    return 1;
}

forward CM_FallTimer();
public CM_FallTimer()
{
    if(ColorMatchStage != STAGE_PLAYING) return 1;
    new Float: z;
    for(new i, mp = GetPlayerPoolSize(); i <= mp; i++)
    {
        if(!IsPlayerConnected(i) || !InCMEvent[i]) continue;
        GetPlayerPos(i, z, z, z);
        if(z < 95.0) ColorMatch_Eliminate(i);
    }
    
    return 1;
}

forward CM_PickColor();
public CM_PickColor()
{
    if(ColorMatchStage != STAGE_PLAYING) return 1;
    new NameId = random(sizeof(ColorMatchNames));
    ColorMatchCurrent = NameId;

    for(new i, mp = GetPlayerPoolSize(); i <= mp; i++)
    {
        if(!IsPlayerConnected(i) || !InCMEvent[i]) continue;
        PlayerTextDrawColor(i, TD_P_ColorMatch[i], ColorMatchColors[NameId]);
        PlayerTextDrawSetString(i, TD_P_ColorMatch[i], ColorMatchNames[ random(sizeof(ColorMatchNames)) ]);
        PlayerTextDrawShow(i, TD_P_ColorMatch[i]);
    }

    ColorMatchTimer = SetTimer("CM_MoveObjects", 2700, false);
    return 1;
}

forward CM_MoveObjects();
public CM_MoveObjects()
{
    if(ColorMatchStage != STAGE_PLAYING) return 1;
    for(new i, mp = GetPlayerPoolSize(); i <= mp; i++)
    {
        if(!IsPlayerConnected(i) || !InCMEvent[i]) continue;
        PlayerTextDrawColor(i, TD_P_ColorMatch[i], 0xFFFFFFFF);
        PlayerTextDrawSetString(i, TD_P_ColorMatch[i], "_");
        PlayerTextDrawHide(i, TD_P_ColorMatch[i]);
    }
    
    new Float: x, Float: y, Float: z;
    for(new i; i < sizeof(ColorMatchObjects); i++)
    {
        if(i == ColorMatchCurrent) continue;
        GetDynamicObjectPos(ColorMatchObjects[i], x, y, z);
        SetDynamicObjectPos(ColorMatchObjects[i], x, y, z - 1000.0);
    }

    ColorMatchTimer = SetTimer("CM_FixObjects", 3000, false);
    return 1;
}

forward CM_FixObjects();
public CM_FixObjects()
{
    if(ColorMatchStage != STAGE_PLAYING) return 1;
    new Float: x, Float: y, Float: z;
    for(new i; i < sizeof(ColorMatchObjects); i++)
    {
        if(i == ColorMatchCurrent) continue;
        GetDynamicObjectPos(ColorMatchObjects[i], x, y, z);
        SetDynamicObjectPos(ColorMatchObjects[i], x, y, z + 1000.0);
    }
    
    ColorMatchTimer = SetTimer("CM_PickColor", 1000, false);
    return 1;
}

forward CM_EndEvent(time);
public CM_EndEvent(time)
{
    if(ColorMatchStage != STAGE_PLAYING) return 1;
    new string[55];
    if(time > 1) {
        time--;
        
        new count;
        foreach(new i : Player) {
            if (InCMEvent[i]) count++;
        }

        format(string, sizeof(string), "Time Left: %02d:%02d~n~Alive Players: %d", time / 60, time % 60, count);
        TextDrawSetString(TD_ColorMatch[3], string);
        ColorMatchEventTimer = SetTimerEx("CM_EndEvent", 1000, false, "i", time);
    }else if(time == 1) {

        SendClientMessageToAll(0xEA266AFF, "[ColorMatch] {FFFFFF}Zaman Event Be Payan Resid.");
        ColorMatch_CleanUp(1);
    }
    return 1;
}

ColorMatch_Eliminate(playerid)
{
    if(ColorMatchStage != STAGE_PLAYING) return 1;
    if(!InCMEvent[playerid]) return 1;
    for(new TD; TD < sizeof TD_ColorMatch; TD++) TextDrawHideForPlayer(playerid, TD_ColorMatch[TD]);
    PlayerTextDrawHide(playerid, TD_P_ColorMatch[playerid]);

    TogglePlayerControllable(playerid, 1);
    SetCameraBehindPlayer(playerid);
    SetPlayerVirtualWorld(playerid, SaveIntWorld[playerid][1]);
    SetPlayerInterior(playerid, SaveIntWorld[playerid][0]);
    SetPlayerPos(playerid, SavePos2[playerid][0], SavePos2[playerid][1], SavePos2[playerid][2]);
    
    give_player_save_weapon(playerid);

    ColorMatchPlayers--;
    
    new string[100];
    format(string, sizeof(string), "[ColorMatch] {FFFFFF}%s(%d) got eliminated, Players Left: {F1C40F}%d", Name(name), playerid, ColorMatchPlayers);
    // format(string, sizeof(string), "~p~%s(%d) ~w~Got Eliminated~n~Players Left: ~p~%d", Name(playerid), playerid, ColorMatchPlayers);
    for(new i, mp = GetPlayerPoolSize(); i <= mp; i++)
    {
        if(!IsPlayerConnected(i) || !InCMEvent[i]) continue;
        SendClientMessage(i, 0xEA266AFF, string);
    }
    
    InCMEvent[playerid] = false;
    
    if(ColorMatchStage == STAGE_PLAYING)
    {
        if(ColorMatchPlayers < 2)
        {
            new winner = INVALID_PLAYER_ID;
            for(new i, mp = GetPlayerPoolSize(); i <= mp; i++)
            {
                if(!IsPlayerConnected(i) || !InCMEvent[i]) continue;
                winner = i;
                break;
            }
            
            if(IsPlayerConnected(winner))
            {
                new rand_pool = RandomEx(800,1500);
                format(string, sizeof(string), "[ColorMatch] {FFFFFF}Bazikon %s(%d) Barande Event ColorMatch Shod! [$%d Dollar Va +1 EXP]", Name(winner), winner, rand_pool);
                SendClientMessageToAll(0xEA266AFF, string);
                give_money(winner, rand_pool);

                PlayerInfo[winner][exp] += 1;
				PlayerLevelUpdateCheck(winner);
                
                /*EvCM[winner]++;
                mysql_format(SQLHandle, string, sizeof(string), "UPDATE `"TABLE_ACCOUNTS"` SET `EvCM` = %d WHERE `id` = %d", EvCM[winner], Player_SQL_ID[winner]);
                mysql_tquery(SQLHandle, string);
                UpdateEventsTopPlayers(4);*/
            }
            
            SendClientMessageToAll(0xEA266AFF, "[ColorMatch] {FFFFFF}Zaman Event Be Payan Resid.");
            ColorMatch_CleanUp(1);
        }
    }
    
    return 1;
}

stock ColorMatchCreateObjects() {
    ColorMatchObjects[OBJ_ORANGE] = CreateDynamicObject(19353, 2005.390, 3866.277, 101.323, 0.000, 90.000, 90.000); //  orange
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_ORANGE], 0, 18996, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_ORANGE]));
    
    ColorMatchObjects[OBJ_RED] = CreateDynamicObject(19353, 2008.590, 3866.277, 101.323, 0.000, 90.000, 90.000); // red
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_RED], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_RED]));
    
    ColorMatchObjects[OBJ_GREEN] = CreateDynamicObject(19353, 2002.190, 3866.277, 101.323, 0.000, 90.000, 90.000); // green
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_GREEN], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_GREEN]));
    
    ColorMatchObjects[OBJ_YELLOW] = CreateDynamicObject(19353, 2008.590, 3862.777, 101.323, 0.000, 90.000, 90.000); // yellow
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_YELLOW], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_YELLOW]));
    
    ColorMatchObjects[OBJ_PURPLE] = CreateDynamicObject(19353, 2008.590, 3869.777, 101.323, 0.000, 90.000, 90.000); // purple
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_PURPLE], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_PURPLE]));

    ColorMatchObjects[OBJ_PINK] = CreateDynamicObject(19353, 2005.390, 3862.777, 101.323, 0.000, 90.000, 90.000); // pink
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_PINK], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_PINK]));
    
    ColorMatchObjects[OBJ_MAROON] = CreateDynamicObject(19353, 2005.390, 3869.777, 101.323, 0.000, 90.000, 90.000); // maroon
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_MAROON], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_MAROON]));
    
    ColorMatchObjects[OBJ_BLUE] = CreateDynamicObject(19353, 2002.190, 3869.777, 101.323, 0.000, 90.000, 90.000); // blue
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_BLUE], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_BLUE]));

    ColorMatchObjects[OBJ_WHITE] = CreateDynamicObject(19353, 2002.190, 3862.777, 101.323, 0.000, 90.000, 90.000); // white
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_WHITE], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_WHITE]));
}

ColorMatch_Arena()
{
    for(new i; i < sizeof(ColorMatchObjects); i++) {
        //if(ColorMatchObjects[i] != INVALID_OBJECT_ID) 
        DestroyDynamicObject(ColorMatchObjects[i]);
    }
    
    ColorMatchObjects[OBJ_ORANGE] = CreateDynamicObject(19353, 2005.390, 3866.277, 101.323, 0.000, 90.000, 90.000); //  orange
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_ORANGE], 0, 18996, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_ORANGE]));

    ColorMatchObjects[OBJ_RED] = CreateDynamicObject(19353, 2008.590, 3866.277, 101.323, 0.000, 90.000, 90.000); // red
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_RED], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_RED]));

    ColorMatchObjects[OBJ_GREEN] = CreateDynamicObject(19353, 2002.190, 3866.277, 101.323, 0.000, 90.000, 90.000); // green
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_GREEN], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_GREEN]));

    ColorMatchObjects[OBJ_YELLOW] = CreateDynamicObject(19353, 2008.590, 3862.777, 101.323, 0.000, 90.000, 90.000); // yellow
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_YELLOW], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_YELLOW]));

    ColorMatchObjects[OBJ_PURPLE] = CreateDynamicObject(19353, 2008.590, 3869.777, 101.323, 0.000, 90.000, 90.000); // purple
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_PURPLE], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_PURPLE]));

    ColorMatchObjects[OBJ_PINK] = CreateDynamicObject(19353, 2005.390, 3862.777, 101.323, 0.000, 90.000, 90.000); // pink
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_PINK], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_PINK]));

    ColorMatchObjects[OBJ_MAROON] = CreateDynamicObject(19353, 2005.390, 3869.777, 101.323, 0.000, 90.000, 90.000); // maroon
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_MAROON], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_MAROON]));

    ColorMatchObjects[OBJ_BLUE] = CreateDynamicObject(19353, 2002.190, 3869.777, 101.323, 0.000, 90.000, 90.000); // blue
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_BLUE], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_BLUE]));

    ColorMatchObjects[OBJ_WHITE] = CreateDynamicObject(19353, 2002.190, 3862.777, 101.323, 0.000, 90.000, 90.000); // white
    SetDynamicObjectMaterial(ColorMatchObjects[OBJ_WHITE], 0, 18646, "matcolours", "white", RGB_RGBAToARGB(ColorMatchColors[OBJ_WHITE]));
    return 1;
}

ColorMatch_CleanUp(players = 0)
{
    KillTimer(ColorMatchTimer);
    KillTimer(ColorMatchFallTimer);
    KillTimer(ColorMatchEventTimer);
    ColorMatchStage = STAGE_NONE;
    ColorMatchPlayers = 0;
    ColorMatchTimer = -1;
    ColorMatchFallTimer = -1;
    ColorMatchEventTimer = -1;
    
    if(players)
    {
        for(new i, mp = GetPlayerPoolSize(); i <= mp; i++)
        {
            if(!IsPlayerConnected(i) || !InCMEvent[i]) continue;
            //for(new TD; TD < sizeof TD_BestCM; TD++) TextDrawHideForPlayer(i, TD_BestCM[TD]);
            InCMEvent[i] = false;
            PlayerTextDrawHide(i, TD_P_ColorMatch[i]);
            for(new TD; TD < sizeof TD_ColorMatch; TD++) TextDrawHideForPlayer(i, TD_ColorMatch[TD]);
            TogglePlayerControllable(i, 1);
            SetCameraBehindPlayer(i);
            SetPlayerVirtualWorld(i, SaveIntWorld[i][1]);
            SetPlayerInterior(i, SaveIntWorld[i][0]);
            SetPlayerPos(i, SavePos2[i][0], SavePos2[i][1], SavePos2[i][2]);
            give_player_save_weapon(i);
        }
    }

    return 1;
}

alias:cm("jcolor");
CMD:cm(playerid, params[])
{
    if(isPlayerInJail(playerid)) return SendError(playerid, "Shoma dar jail hastid.");

    if(GetPVarInt(playerid, "PlayerCuffed")> 0) return SendError(playerid, "Shoma cuff hastid.");

    if(IsPlayerInFalloutGame(playerid)) return SendError(playerid, "Shoma Dar Event Fallout Hastid!");

    if(InCMEvent[playerid]) return SendError(playerid, "Shoma dar ColorMatch Hastid.");

    if(ColorMatchStage == STAGE_PLAYING) return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}Event ColorMatch Shoro Shode Ast.");
    if(ColorMatchStage == STAGE_NONE) {
        if(PlayerInfo[playerid][admin] < 5)
        {
            // if(PlayerInfo[playerid][money] < 10000) return SendClientMessage(playerid, col_gray,""scm_error"Shoma $10,000 Pool Nadarid.");
            // give_money(playerid,-10000);
            return 1;
        }
        // init game
        ColorMatchStage = STAGE_SETUP;
        ColorMatchPlayers = 1;
        ColorMatchTimer = SetTimerEx("CM_SetupTimer", 1000, false, "i", CM_SETUP_TIME);
        ColorMatchFallTimer = ColorMatchEventTimer = -1;

        ColorMatch_Arena();
        
        new string[144];
        format(string, sizeof(string), "[COLORMATCH] Bazikon %s(%d) Event ColorMatch Ra Start Kard. Use (/cm) Baraye Vorod.", Name(playerid), playerid);
        SendClientMessageToAll(0xD96C00FF, string);
        SendClientMessageToAll(0xD76B00FF, ">> Event ColorMatch: {D7BC00}Start up 20 Seconds. {FCB185}(Join with /cm)");
    }else{
        if(ColorMatchPlayers >= CM_MAX_PLAYERS) return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}Emkane Vorod Bish Az 20 Nafar Be Event Nist.");
        ColorMatchPlayers++;
    }
    CreatePlayerColorMatchTD(playerid);
    GetPlayerPos(playerid, SavePos2[playerid][0], SavePos2[playerid][1], SavePos2[playerid][2]);
    SetPlayerPos(playerid, SavePos2[playerid][0], SavePos2[playerid][1], SavePos2[playerid][2]+1.0);
    me_action(playerid, "Ba /cm Raft Mosabeghe!");
    ResetPlayerWeapons(playerid);
    SaveIntWorld[playerid][0] = GetPlayerInterior(playerid);
    SaveIntWorld[playerid][1] = GetPlayerVirtualWorld(playerid);
    new Float:x, Float:y, Float:z;
    GetDynamicObjectPos(ColorMatchObjects[ random(9) ], x, y, z);
    texture_load_mode(playerid);
    SetPlayerPos(playerid, x + frandom(1.0, -1.0), y + frandom(1.0, -1.0), z + 1.0);
    SetPlayerVirtualWorld(playerid, 1);
    InCMEvent[playerid] = true;
    return 1;
}

CommandExitForColormatch(playerid)
{
    if(!InCMEvent[playerid]) return 0;
    callcmd::exitcm(playerid);
    return 1;
}

CMD:exitcm(playerid)
{
    if(!InCMEvent[playerid]) return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}Shoma Dar Event Nistid.");
    //for(new TD; TD < sizeof TD_BestCM; TD++) TextDrawHideForPlayer(playerid, TD_BestCM[TD]);
    for(new TD; TD < sizeof TD_ColorMatch; TD++) TextDrawHideForPlayer(playerid, TD_ColorMatch[TD]);
    PlayerTextDrawHide(playerid, TD_P_ColorMatch[playerid]);
    set_health(playerid, 100.0);
    TogglePlayerControllable(playerid, 1);
    SetCameraBehindPlayer(playerid);
    SetPlayerVirtualWorld(playerid, SaveIntWorld[playerid][1]);
    SetPlayerInterior(playerid, SaveIntWorld[playerid][0]);
    SetPlayerPos(playerid, SavePos2[playerid][0], SavePos2[playerid][1], SavePos2[playerid][2]);

    give_player_save_weapon(playerid);
    
    ColorMatchPlayers--;
    InCMEvent[playerid] = false;
    if(ColorMatchStage == STAGE_PLAYING)
    {
        if(ColorMatchPlayers < 2)
        {
            new winner = INVALID_PLAYER_ID;
            foreach(new i : Player)
            {
                if(!InCMEvent[i]) continue;
                winner = i;
                break;
            }
            if(IsPlayerConnected(winner))
            {
                new string[200], rand_pool = RandomEx(800,1500);
                format(string, sizeof(string), "[ColorMatch] {FFFFFF}Bazikon %s(%d) Barande Event ColorMatch Shod! [$%d Dollar Va +1 EXP]", Name(winner), winner, rand_pool);
                SendClientMessageToAll(0xEA266AFF, string);
                give_money(winner, rand_pool);
                
                PlayerInfo[winner][exp] += 1;
				PlayerLevelUpdateCheck(winner);
            }
            SendClientMessageToAll(0xEA266AFF, "[ColorMatch] {FFFFFF}Zaman Event Be Payan Resid.");
            ColorMatch_CleanUp(1);
        }
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    ColorMatch_Eliminate(playerid);
    DestroyPlayerColorMatchTD(playerid);

    #if defined ColorMatch_OnPlayerDisconnect
        return ColorMatch_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect ColorMatch_OnPlayerDisconnect
#if defined ColorMatch_OnPlayerDisconnect
    forward ColorMatch_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    ColorMatch_Eliminate(playerid);

    #if defined ColorMatch_OnPlayerStateChange
        return ColorMatch_OnPlayerStateChange(playerid, newstate, oldstate);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange ColorMatch_OnPlayerStateChange
#if defined ColorMatch_OnPlayerStateChange
    forward ColorMatch_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

CreatePlayerColorMatchTD(playerid) {
    if (TD_P_ColorMatch[playerid] == PlayerText: INVALID_TEXT_DRAW) {
        TD_P_ColorMatch[playerid] = CreatePlayerTextDraw(playerid,317.000000, 150.000000, "_");
        PlayerTextDrawAlignment(playerid,TD_P_ColorMatch[playerid], 2);
        PlayerTextDrawBackgroundColor(playerid,TD_P_ColorMatch[playerid], 255);
        PlayerTextDrawFont(playerid,TD_P_ColorMatch[playerid], 2);
        PlayerTextDrawLetterSize(playerid,TD_P_ColorMatch[playerid], 0.700000, 3.000000);
        PlayerTextDrawColor(playerid,TD_P_ColorMatch[playerid], -1);
        PlayerTextDrawSetOutline(playerid,TD_P_ColorMatch[playerid], 1);
        PlayerTextDrawSetProportional(playerid,TD_P_ColorMatch[playerid], 1);
        PlayerTextDrawSetSelectable(playerid,TD_P_ColorMatch[playerid], 0);
    }
}

DestroyPlayerColorMatchTD(playerid) {
    if (TD_P_ColorMatch[playerid] != PlayerText: INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_P_ColorMatch[playerid]);
        TD_P_ColorMatch[playerid] = PlayerText: INVALID_TEXT_DRAW;
    }
}

stock IsPlayerInColorMatchEvent(playerid) return InCMEvent[playerid];