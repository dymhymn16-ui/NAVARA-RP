// Constants
static const TD_ID_START_PLAYER_NAMES = 37;

// -------------------------------------------------------------------------
// Enumerate

enum GangPlayerEnum {
    Kills,
    Float:Damage,
    Float:DamageTake,
    Deaths
};
new GangPlayer[MAX_PLAYERS][GangPlayerEnum];

new TopListNick[2] = {-1, ...};

// -------------------------------------------------------------------------
// Vars

new
    Text:TopWarTextdraw[107],
    Text:TD_Capture[15],
    PlayerText:PTD_Capture[MAX_PLAYERS][11],
    PlayerBar:PlayerTopWarProgressBar[MAX_PLAYERS];

static 
    bool:TopWarTextdrawLoaded,
    bool:PlayerSmallTopWarTextdrawLoad[MAX_PLAYERS],
    bool:PlayerTopWarProgressBarLoaded[MAX_PLAYERS],
    bool:ShowTextdraw[sizeof TopWarTextdraw],
    TopWarGangKills[3],
    TopWarGangColours[3],
    ResetTimeRecentGang;

new
    TopWarGangAttacker = -2, 
    TopWarGangAttackerRecent = -2,
    TopWarGangProtector = -2, 
    TopWarGangProtectorRecent = -2;

// -------------------------------------------------------------------------

// Lib of Textdraw Codes
#include "../library/static/system/server/top_war/top_war_textdraw_codes.inc"

// -------------------------------------------------------------------------

stock TopWar_CreateGlobalTextdraws() {
    if(TopWarTextdrawLoaded) {
        TextDrawSetString(TopWarTextdraw[36], "~>~ Gang");
        TextDrawSetString(TopWarTextdraw[32], "Gang ~<~");

        for(new TD; TD < sizeof TopWarTextdraw; TD++) {
            if(TD >= TD_ID_START_PLAYER_NAMES) {
                TextDrawSetString(TopWarTextdraw[TD], " ");
                ShowTextdraw[TD] = false;
            }
        }

        return false;
    }
    
    TopWarTextdrawLoaded = true;
    TopWar_LoadTextdraws();
    return true;
}

stock TopWar_CreateSmallGlobalTexts() {
    loadTDCapture();
    return true;
}

stock TopWar_CreatePlayerSmallTexts(playerid) {
    PlayerSmallTopWarTextdrawLoad[playerid] = true;
    loadPTDCapture(playerid);
    return true;
}

stock TopWar_CreatePlayerProgressBar(playerid, color, fill_color, Float:value, Float:max_value) {
    if(PlayerTopWarProgressBarLoaded[playerid]) {
        SetPlayerProgressBarValue(playerid, PlayerTopWarProgressBar[playerid], value);
        SetPlayerProgressBarMaxValue(playerid, PlayerTopWarProgressBar[playerid], max_value);
        SetPlayerProgressBarColourEx(playerid, PlayerTopWarProgressBar[playerid], color, fill_color);
        return false;
    }
    
    PlayerTopWarProgressBarLoaded[playerid] = true;
    PlayerTopWarProgressBar[playerid] = CreatePlayerProgressBar(
        playerid, 
        271.149627, 
        236.649993, 
        .width = 105.000000, 
        .height = 5.000000, 
        .colour = color, 
        .max = max_value, 
        .direction = BAR_DIRECTION_RIGHT);
    SetPlayerProgressBarValue(playerid, PlayerTopWarProgressBar[playerid], value);
    SetPlayerProgressBarColourEx(playerid, PlayerTopWarProgressBar[playerid], color, fill_color);
    return true;
}

stock TopWar_HideGlobalTextdraws(playerid) {

    if(!PlayerBoxOpen[playerid]) return false;
    
    PlayerBoxOpen[playerid] = false;

    foreach(new showplayerid : logged_players) {
        if (showplayerid != playerid)
            ShowPlayerNameTagForPlayer(playerid, showplayerid, 1);
    }

    for (new TD; TD < sizeof TopWarTextdraw; TD++) {
        TextDrawHideForPlayer(playerid, TopWarTextdraw[TD]);
    }

    //Bar
    HidePlayerProgressBar(playerid, PlayerTopWarProgressBar[playerid]);

    CancelSelectTextDraw(playerid);

    return true;
}

stock TopWar_ShowGlobalTextdraws(playerid) {
    if(TopWarTextdrawLoaded)
    {
        if(!PlayerBoxOpen[playerid])
        {
            foreach(new showplayerid : logged_players) {
                if (showplayerid != playerid)
                    ShowPlayerNameTagForPlayer(playerid, showplayerid, 0); // Hide Name Tags For Player -> playerid
            }

            for (new TD; TD < sizeof TopWarTextdraw; TD++) {
                
                if(TD >= TD_ID_START_PLAYER_NAMES) {
                    if(ShowTextdraw[TD])
                        TextDrawShowForPlayer(playerid, TopWarTextdraw[TD]);
                    else
                        TextDrawHideForPlayer(playerid, TopWarTextdraw[TD]);
                }
                else
                    TextDrawShowForPlayer(playerid, TopWarTextdraw[TD]);
            }
        } 
        else 
        {
            for (new TD = TD_ID_START_PLAYER_NAMES; TD < sizeof TopWarTextdraw; TD++) {
                if(ShowTextdraw[TD])
                    TextDrawShowForPlayer(playerid, TopWarTextdraw[TD]);
                else
                    TextDrawHideForPlayer(playerid, TopWarTextdraw[TD]);
            }
        }

        PlayerBoxOpen[playerid] = true;
        SelectTextDraw(playerid, 0x0DF690AA);

        // Bar
        new Float:max_value;
        if(TopWarGangKills[1] == 0 && TopWarGangKills[2] == 0) 
        {
            max_value = 2.0;
            TopWar_CreatePlayerProgressBar(playerid, TopWarGangColours[1], TopWarGangColours[2], 1.0, max_value);
        }
        else
        {
            max_value = float(TopWarGangKills[1]) + float(TopWarGangKills[2]);
            TopWar_CreatePlayerProgressBar(playerid, TopWarGangColours[1], TopWarGangColours[2], float(TopWarGangKills[2]), max_value);
        }
        ShowPlayerProgressBar(playerid, PlayerTopWarProgressBar[playerid]);
    }
    return true;
}

stock TopWar_UpdatePlayer(playerid, TD, UpdateName = 0, UpdateKills = 0, UpdateDamage = 0, UpdateDeaths = 0) {
    
    new
        string[18];

    new
        UpdateKD;

    ShowTextdraw[ TD ] = true;
    ShowTextdraw[ TD + 1 ] = true;
    ShowTextdraw[ TD + 2 ] = true;
    ShowTextdraw[ TD + 3 ] = true;
    ShowTextdraw[ TD + 4 ] = true;

    if(UpdateName) {
        format(string, sizeof string, "%s", Name(playerid));

        TextDrawSetString(TopWarTextdraw[TD], string);
    }

    if(UpdateKills) {
        format(string, sizeof string, "%d", GangPlayer[playerid][Kills]);

        TextDrawSetString(TopWarTextdraw[ TD + 1 ], string);
        UpdateKD = 1;
    }

    if(UpdateDamage) {
        format(string, sizeof string, "%d", floatround(GangPlayer[playerid][Damage], floatround_ceil));
        
        TextDrawSetString(TopWarTextdraw[ TD + 2 ], string);
    }

    if(UpdateDeaths) {
        format(string, sizeof string, "%d", GangPlayer[playerid][Deaths]);
        
        TextDrawSetString(TopWarTextdraw[ TD + 3 ], string);
        UpdateKD = 1;
    }

    if(UpdateKD) {

        new
            Float:Ratio;

        if(GangPlayer[playerid][Deaths] == 0 && GangPlayer[playerid][Kills] > 0) 
        {
            Ratio = floatdiv(GangPlayer[playerid][Kills], 3); // Kills/3=? 
        }

        if(GangPlayer[playerid][Deaths] > 0 && GangPlayer[playerid][Kills] > 0) 
        {
            Ratio = floatdiv(GangPlayer[playerid][Kills], GangPlayer[playerid][Deaths]);
        }

        format(string, sizeof string, "%0.2f", Ratio);

        TextDrawSetString(TopWarTextdraw[ TD + 4 ], string);
    }

    return true;
}

stock TopWar_UpdateTopWarInfo(GangName_1[], ColorGang_1, GangName_2[], ColorGang_2)
{
    new string[64];

    format(string, sizeof string, "~>~ %s", GangName_1);
    TextDrawSetString(TopWarTextdraw[32], string);
    TextDrawColor(TopWarTextdraw[32], ColorGang_1);
    TextDrawBoxColor(TopWarTextdraw[12], ColorGang_1);

    format(string, sizeof string, "%s ~<~", GangName_2);
    TextDrawSetString(TopWarTextdraw[36], string);
    TextDrawColor(TopWarTextdraw[36], ColorGang_2);
    TextDrawBoxColor(TopWarTextdraw[13], ColorGang_2);

    TopWarGangColours[1] = ColorGang_1;
    TopWarGangColours[2] = ColorGang_2;

    foreach(new i : logged_players) {
        
        //Reshow
        if(PlayerBoxOpen[i]) {
            TextDrawShowForPlayer(i, TopWarTextdraw[36]);
            TextDrawShowForPlayer(i, TopWarTextdraw[12]);

            TextDrawShowForPlayer(i, TopWarTextdraw[32]);
            TextDrawShowForPlayer(i, TopWarTextdraw[13]);
        }

        //Reset Data
        for(new GangPlayerEnum:j; j < GangPlayerEnum; j++) GangPlayer[i][j] = 0;
    }
}

stock TopWar_UpdateSmallTopWarInfo()
{
    // Show Textdraws
    foreach(new i : logged_players)
    {
        if(PlayerInfo[i][member] == TopWarGangAttacker || PlayerInfo[i][member] == TopWarGangProtector) {
            TopWar_ShowSmallTopWarInfo(i);
            CaptureInfoUpdate(i, true);
        }
    }
}

stock TopWar_ShowSmallTopWarInfo(playerid) {
    TopWar_CreatePlayerSmallTexts(playerid);
    for(new TD; TD < sizeof TD_Capture; TD++) {
        TextDrawShowForPlayer(playerid, TD_Capture[TD]);
    }
    for(new TD; TD < sizeof PTD_Capture[]; TD++) {
        PlayerTextDrawShow(playerid, PTD_Capture[playerid][TD]);
    }
}

stock TopWar_HideTopWar(target) {
	if(PlayerInfo[target][member] == TopWarGangAttacker || PlayerInfo[target][member] == TopWarGangProtector) {
		TopWar_HideSmallTopWarInfo(target);

		//Reset Vars
		for(new GangPlayerEnum:i; i < GangPlayerEnum; i++) GangPlayer[target][i] = 0;
	}
}

stock TopWar_HideSmallTopWarInfo(playerid) {
    for(new TD; TD < sizeof TD_Capture; TD++) {
        TextDrawHideForPlayer(playerid, TD_Capture[TD]);
    }
    for(new TD; TD < sizeof PTD_Capture[]; TD++) {
        PlayerTextDrawHide(playerid, PTD_Capture[playerid][TD]);
    }
}

stock TopWar_SetGangs(Gang_1, Gang_2)
{
    TopWarGangAttacker = Gang_2;
    TopWarGangProtector = Gang_1;

    if(Gang_1 == -1 && Gang_2 == -1) {
        ResetTimeRecentGang = 20 * 60;
    }
}
stock TopWar_SetRecentGangs(Gang_1, Gang_2)
{
    TopWarGangAttackerRecent = Gang_2;
    TopWarGangProtectorRecent = Gang_1;
}

stock TopWar_ResetAccountsInTopWar()
{
    mysql_tquery(sql_connection, "UPDATE `users` SET `TopWarGangKills`= 0,`TopWarGangDamage`= 0.0,`TopWarGangDamageTake`= 0.0,`TopWarGangDeaths`= 0");
}

ShowBestGangPlayer()
{
    new best_id[4];

    foreach(new playerid : logged_players)
    {
        if(PlayerInfo[playerid][member] != TopWarGangAttacker && PlayerInfo[playerid][member] != TopWarGangProtector) continue;
        if(GangPlayer[playerid][Deaths] > GangPlayer[best_id[0]][Deaths]) best_id[0] = playerid;
        if(GangPlayer[playerid][Kills] > GangPlayer[best_id[1]][Kills]) best_id[1] = playerid;
        if(GangPlayer[playerid][Damage] > GangPlayer[best_id[2]][Damage]) best_id[2] = playerid;
        if(GangPlayer[playerid][DamageTake] > GangPlayer[best_id[3]][DamageTake]) best_id[3] = playerid;
    }
            
    STRING_GLOBAL[0] = EOS;
    if(best_id[0] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas tedad koshtar moshakhas nashode ast.");
    else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas tedad death %s [%d] (%s). Tedad: %d.", get_name(best_id[0]), best_id[0], GetFractionName(PlayerInfo[best_id[0]][member]), GangPlayer[best_id[0]][Deaths]);
    foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == TopWarGangAttacker || PlayerInfo[pl_id][member] == TopWarGangProtector) SendMes(pl_id, 0x33CC66FF, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    if(best_id[1] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas tedad marg-ha moshakhas nashode ast.");
    else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas tedad kill %s [%d] (%s). Tedad: %d.", get_name(best_id[1]), best_id[1], GetFractionName(PlayerInfo[best_id[1]][member]), GangPlayer[best_id[1]][Kills]);
    foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == TopWarGangAttacker || PlayerInfo[pl_id][member] == TopWarGangProtector) SendMes(pl_id, 0x33CC66FF, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    if(best_id[2] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas asib vard shode moshakhas nashode ast.");
    else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas asib vard shode %s [%d] (%s). Meghdar: %0.2f.", get_name(best_id[2]), best_id[2], GetFractionName(PlayerInfo[best_id[2]][member]), GangPlayer[best_id[2]][Damage]);
    foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == TopWarGangAttacker || PlayerInfo[pl_id][member] == TopWarGangProtector) SendMes(pl_id, 0x33CC66FF, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    if(best_id[3] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas asib daryaft shode moshakhas nashode ast.");
    else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Behtarin bazikon dar tasarof bar asas asib daryaft shode %s [%d] (%s). Meghdar: %0.2f.", get_name(best_id[3]), best_id[3], GetFractionName(PlayerInfo[best_id[3]][member]), GangPlayer[best_id[3]][DamageTake]);
    foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == TopWarGangAttacker || PlayerInfo[pl_id][member] == TopWarGangProtector) SendMes(pl_id, 0x33CC66FF, STRING_GLOBAL);

    return 1;
}

stock TopWar_UpdateTime(time)
{
    // Update
    foreach(new i : logged_players) {
        if(PlayerInfo[i][member] == TopWarGangAttacker || PlayerInfo[i][member] == TopWarGangProtector) {
            CaptureInfoUpdate(i, false);
        }
    }

    // Update
    if(time%2) //Odd Timer
    {
        new
            TextdrawIDs_GangAttacker[7] = {37, 42, 47, 52, 57, 62, 67},
            TextdrawIDs_GangProtector[7] = {72, 77, 82, 87, 92, 97, 102};

        // Sorting Player Gang Kills (1)
        new Slot1 = -1, Slot2 = -1, Slot3 = -1, Slot4 = -1, Slot5 = -1, Slot6 = -1, Slot7 = -1, HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (PlayerInfo[x][member] == TopWarGangProtector && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot1 = x;
            TopListNick[0] = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1) if (PlayerInfo[x][member] == TopWarGangProtector && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot2 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2) if (PlayerInfo[x][member] == TopWarGangProtector && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot3 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3) if (PlayerInfo[x][member] == TopWarGangProtector && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot4 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3 && x != Slot4) if (PlayerInfo[x][member] == TopWarGangProtector && GangPlayer[x][Kills] >= HighestValue)
        {
            HighestValue = GangPlayer[x][Kills];
            Slot5 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3 && x != Slot4 && x != Slot5) if (PlayerInfo[x][member] == TopWarGangProtector && GangPlayer[x][Kills] >= HighestValue)
        {
            HighestValue = GangPlayer[x][Kills];
            Slot6 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3 && x != Slot4 && x != Slot5 && x != Slot6) if (PlayerInfo[x][member] == TopWarGangProtector && GangPlayer[x][Kills] >= HighestValue)
        {
            HighestValue = GangPlayer[x][Kills];
            Slot7 = x;
        }
        HighestValue = -9999;

        if(Slot1 != -1) {
            TopWar_UpdatePlayer(Slot1, TextdrawIDs_GangProtector[0], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangProtector[0];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot2 != -1) {
            TopWar_UpdatePlayer(Slot2, TextdrawIDs_GangProtector[1], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangProtector[1];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot3 != -1) {
            TopWar_UpdatePlayer(Slot3, TextdrawIDs_GangProtector[2], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangProtector[2];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot4 != -1) {
            TopWar_UpdatePlayer(Slot4, TextdrawIDs_GangProtector[3], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangProtector[3];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot5 != -1) {
            TopWar_UpdatePlayer(Slot5, TextdrawIDs_GangProtector[4], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangProtector[4];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot6 != -1) {
            TopWar_UpdatePlayer(Slot6, TextdrawIDs_GangProtector[5], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangProtector[5];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot7 != -1) {
            TopWar_UpdatePlayer(Slot7, TextdrawIDs_GangProtector[6], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangProtector[6];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        // End Of Sorting (1)

        // ---------------------------------------------------------

        // Sorting Player Gang Kills (2)
        Slot1 = -1;
        Slot2 = -1;
        Slot3 = -1;
        Slot4 = -1;
        Slot5 = -1;
        Slot6 = -1;
        Slot7 = -1;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (PlayerInfo[x][member] == TopWarGangAttacker && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot1 = x;
            TopListNick[1] = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1) if (PlayerInfo[x][member] == TopWarGangAttacker && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot2 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2) if (PlayerInfo[x][member] == TopWarGangAttacker && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot3 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3) if (PlayerInfo[x][member] == TopWarGangAttacker && GangPlayer[x][Kills] >= HighestValue) {
            HighestValue = GangPlayer[x][Kills];
            Slot4 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3 && x != Slot4) if (PlayerInfo[x][member] == TopWarGangAttacker && GangPlayer[x][Kills] >= HighestValue)
        {
            HighestValue = GangPlayer[x][Kills];
            Slot5 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3 && x != Slot4 && x != Slot5) if (PlayerInfo[x][member] == TopWarGangAttacker && GangPlayer[x][Kills] >= HighestValue)
        {
            HighestValue = GangPlayer[x][Kills];
            Slot6 = x;
        }
        HighestValue = -9999;
        foreach(new x : logged_players) if(GangPlayer[x][Kills] > 0 || GangPlayer[x][Damage] > 0.0 || GangPlayer[x][Deaths] > 0) if (x != Slot1 && x != Slot2 && x != Slot3 && x != Slot4 && x != Slot5 && x != Slot6) if (PlayerInfo[x][member] == TopWarGangAttacker && GangPlayer[x][Kills] >= HighestValue)
        {
            HighestValue = GangPlayer[x][Kills];
            Slot7 = x;
        }
        HighestValue = -9999;

        if(Slot1 != -1) {
            TopWar_UpdatePlayer(Slot1, TextdrawIDs_GangAttacker[0], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangAttacker[0];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot2 != -1) {
            TopWar_UpdatePlayer(Slot2, TextdrawIDs_GangAttacker[1], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangAttacker[1];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot3 != -1) {
            TopWar_UpdatePlayer(Slot3, TextdrawIDs_GangAttacker[2], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangAttacker[2];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot4 != -1) {
            TopWar_UpdatePlayer(Slot4, TextdrawIDs_GangAttacker[3], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangAttacker[3];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot5 != -1) {
            TopWar_UpdatePlayer(Slot5, TextdrawIDs_GangAttacker[4], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangAttacker[4];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot6 != -1) {
            TopWar_UpdatePlayer(Slot6, TextdrawIDs_GangAttacker[5], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangAttacker[5];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        if(Slot7 != -1) {
            TopWar_UpdatePlayer(Slot7, TextdrawIDs_GangAttacker[6], 1, 1, 1, 1);
        } else {
            //Reset Text To None
            new iTD = TextdrawIDs_GangAttacker[6];
            if(ShowTextdraw[iTD]) {
                for(new TD = iTD; TD < (iTD+5); TD++) {
                    TextDrawSetString(TopWarTextdraw[TD], " ");
                    ShowTextdraw[TD] = false;
                }
            }
        }
        // End Of Sorting (2)
    }
}

stock TopWar_Setup() {
    TopWar_ResetAccountsInTopWar();

    TopWarGangKills[1] = 0;
    TopWarGangKills[2] = 0;

    TopWar_CreateGlobalTextdraws();
    TopWar_CreateSmallGlobalTexts();

    new GangName_1[32], GangName_1_Short[32], ColorGang_1, HudGang_1[18], GangName_2[32], GangName_2_Short[32], ColorGang_2, HudGang_2[18];

    #define FRACTION_GROVE 18
    #define FRACTION_BALLAS 19
    #define FRACTION_VAGOS 20
    #define FRACTION_RIFA 21
    #define FRACTION_AZTEC 22

    switch(TopWarGangAttacker)
    {
        case FRACTION_BALLAS: GangName_1 = "The Ballas Gang", GangName_1_Short = "Ballas", ColorGang_1 = 0xA200CAFF, HudGang_1 = "hud:radar_gangP";
        case FRACTION_VAGOS: GangName_1 = "The Vagos Gang", GangName_1_Short = "Vagos", ColorGang_1 = 0xC6C004FF, HudGang_1 = "hud:radar_gangY";
        case FRACTION_GROVE: GangName_1 = "The Grove Street", GangName_1_Short = "Grove", ColorGang_1 = 0x01AD01FF, HudGang_1 = "hud:radar_gangG";
        case FRACTION_AZTEC: GangName_1 = "The Aztecas", GangName_1_Short = "Aztecas", ColorGang_1 = 0x00C4C4FF, HudGang_1 = "hud:radar_gangB";
        case FRACTION_RIFA: GangName_1 = "The Rifa Gang", GangName_1_Short = "Rifa", ColorGang_1 = 0x0062C4FF, HudGang_1 = "hud:radar_gangN";
    }

    switch(TopWarGangProtector)
    {
        case FRACTION_BALLAS: GangName_2 = "The Ballas Gang", GangName_2_Short = "Ballas", ColorGang_2 = 0xA200CAFF, HudGang_2 = "hud:radar_gangP";
        case FRACTION_VAGOS: GangName_2 = "The Vagos Gang", GangName_2_Short = "Vagos", ColorGang_2 = 0xC6C004FF, HudGang_2 = "hud:radar_gangY";
        case FRACTION_GROVE: GangName_2 = "The Grove Street", GangName_2_Short = "Grove", ColorGang_2 = 0x01AD01FF, HudGang_2 = "hud:radar_gangG";
        case FRACTION_AZTEC: GangName_2 = "The Aztecas", GangName_2_Short = "Aztecas", ColorGang_2 = 0x00C4C4FF, HudGang_2 = "hud:radar_gangB";
        case FRACTION_RIFA: GangName_2 = "The Rifa Gang", GangName_2_Short = "Rifa", ColorGang_2 = 0x0062C4FF, HudGang_2 = "hud:radar_gangN";
    }

    TopWar_UpdateTopWarInfo(GangName_1, ColorGang_1, GangName_2, ColorGang_2);
    
    TopWar_UpdateSmallTopWarInfo();
}

// -------------------------------------------------------------------------
// Commands

cmd:topwar(playerid, params[]) {

    if(!gang_player(playerid))
        return SendError(playerid, "In dastor baraye shoma dar dastres nist.");
    
    new PlayerMemberFaction = PlayerInfo[playerid][member];

    if(PlayerMemberFaction == TopWarGangAttacker || PlayerMemberFaction == TopWarGangProtector || 
        PlayerMemberFaction == TopWarGangAttackerRecent || PlayerMemberFaction == TopWarGangProtectorRecent) 
    {
        TopWar_ShowGlobalTextdraws(playerid);
    } 
    else 
    {
        if(gz_captured != -1)
            SendError(playerid, "Hich gang wari bargozar nashode ast.");
        else
            SendError(playerid, "Top war tanha baraye azaye gang war dar dastres ast.");
    }
    
    return true;
}

// -------------------------------------------------------------------------
// Callbacks

forward TopWar_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid);
public TopWar_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid) {
    if(issuerid != INVALID_PLAYER_ID) {
        if((PlayerInfo[playerid][member] == TopWarGangAttacker || PlayerInfo[playerid][member] != TopWarGangProtector) || (PlayerInfo[playerid][member] != TopWarGangAttacker || PlayerInfo[playerid][member] == TopWarGangProtector)) {
            GangPlayer[issuerid][Damage] += amount;
            GangPlayer[playerid][DamageTake] += amount;
        }
    }
}

forward TopWar_PlayerLoadAccount(playerid);
public TopWar_PlayerLoadAccount(playerid) {
    GangPlayer[playerid][Kills] = cache_get_field_content_int(0, "TopWarGangKills", sql_connection);
    GangPlayer[playerid][Deaths] = cache_get_field_content_int(0, "TopWarGangDeaths", sql_connection);
    GangPlayer[playerid][Damage] = cache_get_field_content_float(0, "TopWarGangDamage", sql_connection);
    GangPlayer[playerid][DamageTake] = cache_get_field_content_float(0, "TopWarGangDamageTake", sql_connection);

    if(PlayerInfo[playerid][member] == TopWarGangAttacker || PlayerInfo[playerid][member] == TopWarGangProtector) {
        TopWar_ShowSmallTopWarInfo(playerid);
        CaptureInfoUpdate(playerid, true);
    }
}

public OnPlayerDisconnect(playerid, reason)
{
    if(GangPlayer[playerid][Kills] != 0 || GangPlayer[playerid][Deaths] != 0 || GangPlayer[playerid][Damage] != 0 || GangPlayer[playerid][DamageTake] != 0) 
    {
        new query[180];
        format(query, sizeof query, 
        "UPDATE `users` SET `TopWarGangKills`=%d,`TopWarGangDeaths`=%d,`TopWarGangDamage`=%f,`TopWarGangDamageTake`=%f WHERE `u_id`=%d", 
            GangPlayer[playerid][Kills], 
            GangPlayer[playerid][Deaths], 
            GangPlayer[playerid][Damage], 
            GangPlayer[playerid][DamageTake], 
            PlayerInfo[playerid][id]);

        mysql_tquery(sql_connection, query);
    }

    clearTopWarPlayer(playerid);
    
    #if defined TopWar_OnPlayerDisconnect
        return TopWar_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect TopWar_OnPlayerDisconnect
#if defined TopWar_OnPlayerDisconnect
    forward TopWar_OnPlayerDisconnect(playerid, reason);
#endif

forward TopWar_OnPlayerKeyState(playerid, newkeys, oldkeys);
public TopWar_OnPlayerKeyState(playerid, newkeys, oldkeys) {
    if(PRESSED(KEY_NO)) {
        if(PlayerBoxOpen[playerid]) {
            TopWar_HideGlobalTextdraws(playerid);
            return 1;
        }
    }

    return 0;
}

forward TopWar_OneSecondTimer();
public TopWar_OneSecondTimer() {
    if(ResetTimeRecentGang == 1) {
        ResetTimeRecentGang = 0;
        TopWar_SetRecentGangs(-1, -1);
    }
    if(ResetTimeRecentGang > 1) ResetTimeRecentGang--;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
    if(PlayerBoxOpen[forplayerid]) {
        if(forplayerid != playerid)
            ShowPlayerNameTagForPlayer(forplayerid, playerid, 0);
    }
    
    #if defined TopWar_OnPlayerStreamIn
        return TopWar_OnPlayerStreamIn(playerid, forplayerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerStreamIn
    #undef OnPlayerStreamIn
#else
    #define _ALS_OnPlayerStreamIn
#endif

#define OnPlayerStreamIn TopWar_OnPlayerStreamIn
#if defined TopWar_OnPlayerStreamIn
    forward TopWar_OnPlayerStreamIn(playerid, forplayerid);
#endif

stock clearTopWarPlayer(playerid)
{
    for(new GangPlayerEnum:i; i < GangPlayerEnum; i++) GangPlayer[playerid][i] = 0;

	if(PlayerBoxOpen[playerid]) {
		foreach(new showplayerid : logged_players) {
			if (showplayerid != playerid)
				ShowPlayerNameTagForPlayer(playerid, showplayerid, 1); // Show Name Tags For Player -> playerid
		}
		PlayerBoxOpen[playerid] = false;
	}

	if(PlayerSmallTopWarTextdrawLoad[playerid]) {
		for(new TD; TD < sizeof PTD_Capture[]; TD++) {
			PlayerTextDrawDestroy(playerid, PTD_Capture[playerid][TD]);
		}
		PlayerSmallTopWarTextdrawLoad[playerid] = false;
	}

	if(PlayerTopWarProgressBarLoaded[playerid]) {
		DestroyPlayerProgressBar(playerid, PlayerTopWarProgressBar[playerid]);
		PlayerTopWarProgressBarLoaded[playerid] = false;
	}
}

CaptureInfoUpdate(playerid, bool:status_start = true)
{
    new str[150],
        time = gz_info[gz_captured][gz_time],
        pMember = -1;

    if(PlayerInfo[playerid][member] == TopWarGangAttacker)
        pMember = 0;
    if(PlayerInfo[playerid][member] == TopWarGangProtector)
        pMember = 1;


    fmt(str, "%02d:%02d", time/60, time%60);
    PlayerTextDrawSetString(playerid, PTD_Capture[playerid][2], str);

    fmt(str, "KILLS:_~s~%d", GangPlayer[playerid][Kills] <= 0 ? 0 : GangPlayer[playerid][Kills]);
    PlayerTextDrawSetString(playerid, PTD_Capture[playerid][5], str);
    
    fmt(str, "DEATHS:_~s~%d", GangPlayer[playerid][Deaths] <= 0 ? 0 : GangPlayer[playerid][Deaths]);
    PlayerTextDrawSetString(playerid, PTD_Capture[playerid][6], str);
    
    fmt(str, "GIVE:_~s~%.1f", GangPlayer[playerid][Damage]);
    PlayerTextDrawSetString(playerid, PTD_Capture[playerid][7], str);

    fmt(str, "TAKE:_~s~%.1f", GangPlayer[playerid][DamageTake]);
    PlayerTextDrawSetString(playerid, PTD_Capture[playerid][8], str);


    if(pMember == 1)
    {
        if(TopListNick[0] != -1)
            fmt(str, "~w~~h~%s", Name(TopListNick[0]));
        else
            fmt(str, "-");
        PlayerTextDrawSetString(playerid, PTD_Capture[playerid][10], str);
        
        if(TopListNick[1] != -1)
            fmt(str, "~w~~h~%s", Name(TopListNick[1]));
        else
            fmt(str, "-");
        PlayerTextDrawSetString(playerid, PTD_Capture[playerid][9], str);
    }
    else
    {
        if(TopListNick[1] != -1)
            fmt(str, "~w~~h~%s", Name(TopListNick[1]));
        else
            fmt(str, "-");
        PlayerTextDrawSetString(playerid, PTD_Capture[playerid][10], str);
        
        if(TopListNick[0] != -1)
            fmt(str, "~w~~h~%s", Name(TopListNick[0]));
        else
            fmt(str, "-");
        PlayerTextDrawSetString(playerid, PTD_Capture[playerid][9], str);
    }
    
    // Update
    if(PlayerBoxOpen[playerid]) TopWar_ShowGlobalTextdraws(playerid);

    if(pMember != -1)
    {
        if(status_start)
        {
            PlayerTextDrawHide(playerid, PTD_Capture[playerid][0]);
            PlayerTextDrawHide(playerid, PTD_Capture[playerid][1]);
        }

        if(pMember == 1)
        {
            if(status_start)
            {
                PlayerTextDrawColor(playerid, PTD_Capture[playerid][0], f_info[TopWarGangProtector][f_radar_color]);
                PlayerTextDrawColor(playerid, PTD_Capture[playerid][1], f_info[TopWarGangAttacker][f_radar_color]);
            }

            fmt(str, "%d", owner_points > 0 ? owner_points : 0);
            PlayerTextDrawSetString(playerid, PTD_Capture[playerid][3], str);
            fmt(str, "%d", attacker_points > 0 ? attacker_points : 0);
            PlayerTextDrawSetString(playerid, PTD_Capture[playerid][4], str);
        }else
        {
            if(status_start)
            {
                PlayerTextDrawColor(playerid, PTD_Capture[playerid][0], f_info[TopWarGangAttacker][f_radar_color]);
                PlayerTextDrawColor(playerid, PTD_Capture[playerid][1], f_info[TopWarGangProtector][f_radar_color]);
            }

            fmt(str, "%d", attacker_points > 0 ? attacker_points : 0);
            PlayerTextDrawSetString(playerid, PTD_Capture[playerid][3], str);
            fmt(str, "%d", owner_points > 0 ? owner_points : 0);
            PlayerTextDrawSetString(playerid, PTD_Capture[playerid][4], str);
        }

        new string[64];

        format(string, sizeof string, "%d", attacker_points > 0 ? attacker_points : 0);
        TextDrawSetString(TopWarTextdraw[31], string);

        format(string, sizeof string, "%d", owner_points > 0 ? owner_points : 0);
        TextDrawSetString(TopWarTextdraw[35], string);

        if(status_start)
        {
            PlayerTextDrawShow(playerid, PTD_Capture[playerid][0]);
            PlayerTextDrawShow(playerid, PTD_Capture[playerid][1]);
        }
    }

    return 1;
}

callback: gangzone_timer(gz_tid, gz_attacker_team, gz_owner_team, capture_type)
{
    if(PauseWarStatus == 1) return 1;

	foreach(new pl_id: logged_players)
	{
		if(!gang_player(pl_id) && GetPVarInt(pl_id, "gz_td_status") ==  1)
		{
			DeletePVar(pl_id, "gz_td_status");
			for(new j = 0; j < 5; j ++) SendDeathMessageToPlayer(pl_id, 1001, 1001, 200);
		}
		else if(gang_player(pl_id) && GetPVarInt(pl_id, "gz_td_status") ==  0)
		{
			ZoneFlashForPlayer(pl_id, gz_info[gz_tid][gz_created], f_info[gz_attacker_team][f_radar_color]);
			SetPVarInt(pl_id, "gz_td_status", 1);
		}
	}
	if(gz_info[gz_tid][gz_time] >= 1)
	{
		gz_info[gz_tid][gz_time] --;

		//----------------
		TopWar_UpdateTime(gz_info[gz_tid][gz_time]);
		//----------------


		if(capture_type == 1)
		{
			owner_points = 0,
			attacker_points	= 0;

			foreach(new i: logged_players)
			{
				if(PlayerInfo[i][member] != gz_info[gz_tid][gz_owner] && PlayerInfo[i][member] != gz_info[gz_tid][gz_attacker]) continue;
				if(!IsPlayerInGangZone(i, gz_captured)) continue;
				if(PlayerInfo[i][member] == gz_info[gz_tid][gz_owner]) owner_points ++;
				else if(PlayerInfo[i][member] == gz_info[gz_tid][gz_attacker]) attacker_points ++;
			}

			return 1;
		}
	}
	else if(gz_info[gz_tid][gz_time] < 1)
	{
		if(capture_type == 0)
		{
			if(owner_points >= attacker_points)
			{
				new _string[92];
				format(_string, sizeof(_string), "[F] \"%s\" az manteghe khod defa' kard.",
				f_info[gz_info[gz_tid][gz_owner]][f_name]);
				foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_attacker] || PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_owner]) SendMes(pl_id, 0x33CC66FF, _string);
			}
			else if(owner_points < attacker_points)
			{
				new _string[92];
				format(_string, sizeof(_string), "[F] \"%s\" tasarof manteghe \"%s\" ra barande shod.",
				f_info[gz_info[gz_tid][gz_attacker]][f_name],
				f_info[gz_info[gz_tid][gz_owner]][f_name]);
				foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_attacker] || PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_owner]) SendMes(pl_id, 0x33CC66FF, _string);
				gz_info[gz_tid][gz_owner] = gz_info[gz_tid][gz_attacker];
			}

            ShowBestGangPlayer();

			foreach(new i: logged_players)
			{
				if(GetPVarInt(i, "gz_td_status") ==  1)
				{
					DeletePVar(i, "gz_td_status");
					for(new j = 0; j < 5; j ++) SendDeathMessageToPlayer(i, 1001, 1001, 200);
				}
			}

			KillTimer(gz_info[gz_tid][gz_timer]);

			gz_captured = -1,
				owner_points = -1,
					attacker_points	= -1;

			gz_info[gz_tid][gz_time] = 0;
			gz_info[gz_tid][gz_attacker] = 0;


			GangZoneStopFlashForAll(gz_info[gz_tid][gz_created]);
			HideZoneForAll(gz_info[gz_tid][gz_created]);
			ShowZoneForAll(gz_info[gz_tid][gz_created], GetGangZoneColor(gz_info[gz_tid][gz_owner]));
			SaveGangZone(gz_tid);

            destroyTeleport(TopWarGangProtector);
            destroyTeleport(TopWarGangAttacker);
		
			// ----------------------
		    // Top War
		    foreach(new i : logged_players) {
		        if(PlayerInfo[i][member] == TopWarGangAttacker || PlayerInfo[i][member] == TopWarGangProtector) {
		            TopWar_HideSmallTopWarInfo(i);
		        }
		    }
		    TopWar_SetGangs(-1, -1);
		    // ----------------------
		}
		else
		{
			owner_points = 0,
			attacker_points	= 0;

			foreach(new i: logged_players)
			{
				if(PlayerInfo[i][member] != gz_info[gz_tid][gz_owner] && PlayerInfo[i][member] != gz_info[gz_tid][gz_attacker]) continue;
				if(PlayerInfo[i][member] == gz_info[gz_tid][gz_owner]) owner_points ++;
				else if(PlayerInfo[i][member] == gz_info[gz_tid][gz_attacker]) attacker_points ++;

				new query_string[98];
				format(query_string,sizeof(query_string),"UPDATE `users` SET `u_captures` = `u_captures`+1 WHERE `u_id` = '%d' LIMIT 1", PlayerInfo[i][id]);
				mysql_tquery(sql_connection, query_string, "", "");


				if(GetPVarInt(i, "gz_td_status") ==  1)
				{
					DeletePVar(i, "gz_td_status");
					for(new j = 0; j < 5; j ++) SendDeathMessageToPlayer(i, 1001, 1001, 200);
				}

			}

			if(owner_points >= attacker_points)
			{
				new _string[120];
				format(_string, sizeof(_string), "[F] \"%s\" az manteghe khod defa' kard.",
				f_info[gz_info[gz_tid][gz_owner]][f_name]);
				foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_attacker] || PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_owner]) SendMes(pl_id, 0x33CC66FF, _string);
			}
			else if(owner_points < attacker_points)
			{
				new _string[120];
				format(_string, sizeof(_string), "[F] \"%s\" tasarof manteghe \"%s\" ra barande shod.",
				f_info[gz_info[gz_tid][gz_attacker]][f_name],
				f_info[gz_info[gz_tid][gz_owner]][f_name]);
				foreach(new pl_id: logged_players) if(PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_attacker] || PlayerInfo[pl_id][member] == gz_info[gz_tid][gz_owner]) SendMes(pl_id, 0x33CC66FF, _string);
				gz_info[gz_tid][gz_owner] = gz_info[gz_tid][gz_attacker];
			}

            ShowBestGangPlayer();

			KillTimer(gz_info[gz_tid][gz_timer]);

			gz_captured = -1,
			owner_points = -1,
			attacker_points	= -1;

			gz_info[gz_tid][gz_time] = 0;
			gz_info[gz_tid][gz_attacker] = 0;


			GangZoneStopFlashForAll(gz_info[gz_tid][gz_created]);
			HideZoneForAll(gz_info[gz_tid][gz_created]);
			ShowZoneForAll(gz_info[gz_tid][gz_created], GetGangZoneColor(gz_info[gz_tid][gz_owner]));
			SaveGangZone(gz_tid);

            destroyTeleport(TopWarGangProtector);
            destroyTeleport(TopWarGangAttacker);

			// ----------------------
		    // Top War

		    foreach(new i : logged_players) {
		        if(PlayerInfo[i][member] == TopWarGangAttacker || PlayerInfo[i][member] == TopWarGangProtector) {
		            TopWar_HideSmallTopWarInfo(i);
		        }
		    }

		    TopWar_SetGangs(-1, -1);
		}

	}
	return 1;
}

cmd:stopwar(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;

    if(gz_captured == -1) return SendError(playerid, "Hich wari darhal ejra nist.");

	owner_points = 0,
	attacker_points	= 0;

	new gz_tid = currentGz_tid;

	foreach(new i: logged_players)
	{
		if(PlayerInfo[i][member] != gz_info[gz_tid][gz_owner] && PlayerInfo[i][member] != gz_info[gz_tid][gz_attacker]) continue;
		if(PlayerInfo[i][member] == gz_info[gz_tid][gz_owner]) owner_points ++;
		else if(PlayerInfo[i][member] == gz_info[gz_tid][gz_attacker]) attacker_points ++;

		if(GetPVarInt(i, "gz_td_status") ==  1)
		{
			DeletePVar(i, "gz_td_status");
			for(new j = 0; j < 5; j ++) SendDeathMessageToPlayer(i, 1001, 1001, 200);
		}

	}

	KillTimer(gz_info[gz_tid][gz_timer]);

	gz_captured = -1,
	owner_points = -1,
	attacker_points	= -1;

	gz_info[gz_tid][gz_time] = 0;
	gz_info[gz_tid][gz_attacker] = 0;

	GangZoneStopFlashForAll(gz_info[gz_tid][gz_created]);
	HideZoneForAll(gz_info[gz_tid][gz_created]);
	ShowZoneForAll(gz_info[gz_tid][gz_created], GetGangZoneColor(gz_info[gz_tid][gz_owner]));
	SaveGangZone(gz_tid);

	new string[100];
	format(string, sizeof(string), "Admin %s war gang zone ra motevaghef kard.", PlayerInfo[playerid][name]);

    destroyTeleport(TopWarGangProtector);
    destroyTeleport(TopWarGangAttacker);

	// ----------------------
    // Top War
    foreach(new i : logged_players) {
    	SendClientMessage(i, col_orange_red, string);
        if(PlayerInfo[i][member] == TopWarGangAttacker || PlayerInfo[i][member] == TopWarGangProtector) {
            TopWar_HideSmallTopWarInfo(i);
        }
    }
    TopWar_SetGangs(-1, -1);
    // ----------------------
	return 1;
}

cmd:pausewar(playerid)
{
	if(check_admin_rank(playerid , 3)) return 1;

    if(gz_captured == -1) return SendError(playerid, "Hich wari darhal ejra nist.");

    if(PauseWarStatus)
    {
        PauseWarStatus = 0;

        new string[100];
        format(string, sizeof(string), "Admin %s war gang zone ra az pause dar ovord.", PlayerInfo[playerid][name]);

        // ----------------------
        // Top War
        foreach(new i : logged_players) {
            SendClientMessage(i, col_orange_red, string);
            if(PlayerInfo[i][member] == TopWarGangAttacker || PlayerInfo[i][member] == TopWarGangProtector) {
                TopWar_HideSmallTopWarInfo(i);
            }
        }
    }
    else
    {
        PauseWarStatus = 1;

        new string[100];
        format(string, sizeof(string), "Admin %s war gang zone ra pause kard.", PlayerInfo[playerid][name]);

        // ----------------------
        // Top War
        foreach(new i : logged_players) {
            SendClientMessage(i, col_orange_red, string);
            if(PlayerInfo[i][member] == TopWarGangAttacker || PlayerInfo[i][member] == TopWarGangProtector) {
                TopWar_HideSmallTopWarInfo(i);
            }
        }
    }

    return 1;
}