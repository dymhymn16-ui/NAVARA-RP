#if !defined BOOMBOX_RANGE_OF_AUDIO
    #define BOOMBOX_RANGE_OF_AUDIO 48.0
#endif

static Text3D:gBoomboxLabel[MAX_PLAYERS],
    bool:gBoomboxDroped[MAX_PLAYERS],
    gBoomboxObject[MAX_PLAYERS],
    Float:gBoomboxPos[MAX_PLAYERS][3],
    gBoomboxArea[MAX_PLAYERS],
    gBoomboxURL[MAX_PLAYERS][144],
    playerOpenedboomboxSel[MAX_PLAYERS];

static Text:TD_BoomBox[7];

Boombox_Init() {
    TD_BoomBox[0] = TextDrawCreate(188.000061, 183.437500, "box");
    TextDrawLetterSize(TD_BoomBox[0], 0.000000, 4.650002);
    TextDrawTextSize(TD_BoomBox[0], 446.000061, 0.000000);
    TextDrawAlignment(TD_BoomBox[0], 1);
    TextDrawColor(TD_BoomBox[0], -1);
    TextDrawUseBox(TD_BoomBox[0], 1);
    TextDrawBoxColor(TD_BoomBox[0], 104);
    TextDrawSetShadow(TD_BoomBox[0], 0);
    TextDrawBackgroundColor(TD_BoomBox[0], 255);
    TextDrawFont(TD_BoomBox[0], 1);
    TextDrawSetProportional(TD_BoomBox[0], 1);

    TD_BoomBox[1] = TextDrawCreate(277.100128, 168.912414, "BoomBox");
    TextDrawLetterSize(TD_BoomBox[1], 0.400999, 1.516875);
    TextDrawAlignment(TD_BoomBox[1], 1);
    TextDrawColor(TD_BoomBox[1], -5963521);
    TextDrawSetShadow(TD_BoomBox[1], 0);
    TextDrawSetOutline(TD_BoomBox[1], 1);
    TextDrawBackgroundColor(TD_BoomBox[1], 255);
    TextDrawFont(TD_BoomBox[1], 2);
    TextDrawSetProportional(TD_BoomBox[1], 1);

    TD_BoomBox[2] = TextDrawCreate(192.500030, 169.437500, "");
    TextDrawTextSize(TD_BoomBox[2], 72.000000, 66.000000);
    TextDrawAlignment(TD_BoomBox[2], 1);
    TextDrawColor(TD_BoomBox[2], -1);
    TextDrawSetShadow(TD_BoomBox[2], 0);
    TextDrawFont(TD_BoomBox[2], 5);
    TextDrawSetProportional(TD_BoomBox[2], 0);
    TextDrawSetPreviewModel(TD_BoomBox[2], 2226);
    TextDrawSetPreviewRot(TD_BoomBox[2], 0.000000, 0.000000, 212.000000, 1.000000);
    TextDrawSetSelectable(TD_BoomBox[2], true);
    TextDrawBackgroundColor(TD_BoomBox[2], 0x00000000);

    TD_BoomBox[3] = TextDrawCreate(280.499328, 167.887512, "");
    TextDrawTextSize(TD_BoomBox[3], 72.000000, 66.000000);
    TextDrawAlignment(TD_BoomBox[3], 1);
    TextDrawColor(TD_BoomBox[3], -1);
    TextDrawSetShadow(TD_BoomBox[3], 0);
    TextDrawFont(TD_BoomBox[3], 5);
    TextDrawSetProportional(TD_BoomBox[3], 0);
    TextDrawSetPreviewModel(TD_BoomBox[3], 2102);
    TextDrawSetPreviewRot(TD_BoomBox[3], 0.000000, 0.000000, 212.000000, 1.000000);
    TextDrawSetSelectable(TD_BoomBox[3], true);
    TextDrawBackgroundColor(TD_BoomBox[3], 0x00000000);

    TD_BoomBox[4] = TextDrawCreate(369.500000, 168.837677, "");
    TextDrawTextSize(TD_BoomBox[4], 72.000000, 66.000000);
    TextDrawAlignment(TD_BoomBox[4], 1);
    TextDrawColor(TD_BoomBox[4], -1);
    TextDrawSetShadow(TD_BoomBox[4], 0);
    TextDrawFont(TD_BoomBox[4], 5);
    TextDrawSetProportional(TD_BoomBox[4], 0);
    TextDrawSetPreviewModel(TD_BoomBox[4], 2103);
    TextDrawSetPreviewRot(TD_BoomBox[4], 0.000000, 0.000000, 212.000000, 1.000000);
    TextDrawSetSelectable(TD_BoomBox[4], true);
    TextDrawBackgroundColor(TD_BoomBox[4], 0x00000000);

    TD_BoomBox[5] = TextDrawCreate(188.300048, 225.274963, "box");
    TextDrawLetterSize(TD_BoomBox[5], 0.000000, -0.082000);
    TextDrawTextSize(TD_BoomBox[5], 445.090270, 0.000000);
    TextDrawAlignment(TD_BoomBox[5], 1);
    TextDrawColor(TD_BoomBox[5], -5963521);
    TextDrawUseBox(TD_BoomBox[5], 1);
    TextDrawBoxColor(TD_BoomBox[5], -5963521);
    TextDrawSetShadow(TD_BoomBox[5], 0);
    TextDrawBackgroundColor(TD_BoomBox[5], 255);
    TextDrawFont(TD_BoomBox[5], 1);
    TextDrawSetProportional(TD_BoomBox[5], 1);

    TD_BoomBox[6] = TextDrawCreate(188.300048, 184.172454, "box");
    TextDrawLetterSize(TD_BoomBox[6], 0.000000, -0.082000);
    TextDrawTextSize(TD_BoomBox[6], 445.090270, 0.000000);
    TextDrawAlignment(TD_BoomBox[6], 1);
    TextDrawColor(TD_BoomBox[6], -5963521);
    TextDrawUseBox(TD_BoomBox[6], 1);
    TextDrawBoxColor(TD_BoomBox[6], -5963521);
    TextDrawSetShadow(TD_BoomBox[6], 0);
    TextDrawBackgroundColor(TD_BoomBox[6], 255);
    TextDrawFont(TD_BoomBox[6], 1);
    TextDrawSetProportional(TD_BoomBox[6], 1);
}

stock IsPlayerDropedBoomBox(playerid)
{
    if(gBoomboxDroped[playerid] == true) 
        return true;
    return false;
}

stock IsPlayerInAnyBoomboxArea(playerid)
{
    foreach(new i: logged_players)
    {
        if(IsPlayerDropedBoomBox(i))
        {
            if(IsPlayerInRangeOfPoint(playerid, BOOMBOX_RANGE_OF_AUDIO, gBoomboxPos[i][0], gBoomboxPos[i][1], gBoomboxPos[i][2])) 
                return true;
        }
    }
    return false;
}

CMD:pickupboombox(playerid, params[]) {
    if(IsPlayerDropedBoomBox(playerid)) {

        if(!IsPlayerInRangeOfPoint(playerid, 2.0, gBoomboxPos[playerid][0], gBoomboxPos[playerid][1], gBoomboxPos[playerid][2])) 
            return SendClientMessage(playerid, COLOR_GREY, "Baraye Bardashtan Boombox Az Roye Zamin Bayad Be Kenar An Beravid.");
        
        new string[100], Float:_rot[3];

        SendClientMessage(playerid, -1, "Shoma Boombox Khodetan Ra Bardashtid.");
        format(string,sizeof(string), "%s(%d) Boombox Khodesh Ra Az Roye Zamin Bardasht.", Name(playerid), playerid);
        SetPlayerChatBubble(playerid, string, 0xDE9814FF, 25.5, 2000);
        
        GetDynamicObjectRot(gBoomboxObject[playerid], _rot[0], _rot[1], _rot[2]);
        SetPlayerFacingAngle(playerid, _rot[2]);
        ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 500);

        gBoomboxDroped[playerid] = false;
        foreach(new i: logged_players)
        {
            if(IsPlayerInDynamicArea(i, gBoomboxArea[playerid]))
            {
                StopAudioStreamForPlayer(i);
            }
        }
        DestroyDynamicObject(gBoomboxObject[playerid]);
        DestroyDynamicArea(gBoomboxArea[playerid]);
        Delete3DTextLabel(gBoomboxLabel[playerid]);

        PlayerInfo[playerid][boombox]++;
        update_int_sql(playerid, "u_boombox", PlayerInfo[playerid][boombox]);
        return 1;
    }
    return 1;
}

CMD:boombox(playerid)
{
    if(playerOpenedboomboxSel[playerid])
        return 1;

    if(IsPlayerDropedBoomBox(playerid))
        return 1;

    if (AntiDMZone(playerid) == 1) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Dar Green Zone Nemitavanid Boombox Bezarid.");

    if(PlayerInfo[playerid][boombox] < 1) {
        SendClientMessage(playerid, COLOR_RED, "Shoma Boombox Nadarid. {FFFFFF}Az 24/7 Bekharid.");
        return 1;
    }

    playerOpenedboomboxSel[playerid] = 1;
    for(new td; td < sizeof TD_BoomBox; td++) 
        TextDrawShowForPlayer(playerid, TD_BoomBox[td]);
        
    SelectTextDraw(playerid, 0xFFFFFFFF);

    return 1;
}

CMD:boomboxlink(playerid, params[])
{
    if(!IsPlayerDropedBoomBox(playerid)) 
        return SendClientMessage(playerid, COLOR_GREY, "Shoma Bayad Yek Boombox Roye Zamin Dashte Bashid.");
    if(!IsPlayerInRangeOfPoint(playerid, 2.0, gBoomboxPos[playerid][0], gBoomboxPos[playerid][1], gBoomboxPos[playerid][2])) 
        return SendClientMessage(playerid, COLOR_GREY, "Baraye Taghir URL Bayad Be Kenar Boombox Khodetan Beravid.");
    new b_link[144];
    if(sscanf(params, "s[144]", b_link)) return SendClientMessage(playerid, COLOR_GREY, "Raveshe Estefade: {FA5858}/boomboxlink (link)");
    
    for(new t; t < strlen(b_link); t++)
    {
        if(b_link[t] == '#') b_link[t] = '%';
    }
    format(gBoomboxURL[playerid], 144, "%s", b_link);

    foreach(new i: logged_players)
    {
        if(IsPlayerInDynamicArea(i, gBoomboxArea[playerid]))
        {
            StopAudioStreamForPlayer(i);
            PlayAudioStreamForPlayer(i, b_link, gBoomboxPos[playerid][0], gBoomboxPos[playerid][1], gBoomboxPos[playerid][2], BOOMBOX_RANGE_OF_AUDIO, 1);
        }
    }
    return 1;
}

CMD:boomboxmodel(playerid, params[])
{
    if(playerOpenedboomboxSel[playerid])
        return 1;
    if(!IsPlayerDropedBoomBox(playerid)) 
        return SendClientMessage(playerid, COLOR_GREY, "Shoma Bayad Yek Boombox Roye Zamin Dashte Bashid.");
    if(!IsPlayerInRangeOfPoint(playerid, 2.0, gBoomboxPos[playerid][0], gBoomboxPos[playerid][1], gBoomboxPos[playerid][2])) 
        return SendClientMessage(playerid, COLOR_GREY, "Baraye Taghir Model Bayad Be Kenar Boombox Khodetan Beravid.");

    playerOpenedboomboxSel[playerid] = 2;
    for(new td; td < sizeof TD_BoomBox; td++) 
        TextDrawShowForPlayer(playerid, TD_BoomBox[td]);
    SelectTextDraw(playerid, 0xFFFFFFFF);

    return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(playerOpenedboomboxSel[playerid]) {
        if(clickedid == Text:INVALID_TEXT_DRAW) {
            playerOpenedboomboxSel[playerid] = 0;
            for(new td; td < sizeof TD_BoomBox; td++) 
                TextDrawHideForPlayer(playerid, TD_BoomBox[td]);
            return 1;
        }

        new model_id;

        if(clickedid == TD_BoomBox[2]) {
            model_id = 2226;
        }

        if(clickedid == TD_BoomBox[3]) {
            model_id = 2102;
        }

        if(clickedid == TD_BoomBox[4]) {
            model_id = 2103;
        }

        if(playerOpenedboomboxSel[playerid] == 2) {

            Streamer_SetIntData(STREAMER_TYPE_OBJECT, gBoomboxObject[playerid], E_STREAMER_MODEL_ID, model_id);
            return 1;
        }

        foreach(new i: logged_players)
        {
            if(IsPlayerDropedBoomBox(i))
            {
                if(IsPlayerInRangeOfPoint(playerid, 50.0, gBoomboxPos[i][0], gBoomboxPos[i][1], gBoomboxPos[i][2]))
                {
                    SendClientMessage(playerid, COLOR_GREY, "Yek Boombox Dar Atrafe In Mantaghe Mibashed Bayad Be Jaye Digari Beravid.");
                    return 1;
                }
            }
        }

        playerOpenedboomboxSel[playerid] = 0;
        for(new td; td < sizeof TD_BoomBox; td++) 
            TextDrawHideForPlayer(playerid, TD_BoomBox[td]);
        CancelSelectTextDraw(playerid);

        gBoomboxURL[playerid][0] = EOS;

        new Float:dPlayerPos[4], string[170];
        GetPlayerPos(playerid, dPlayerPos[0], dPlayerPos[1], dPlayerPos[2]);
        GetPlayerFacingAngle(playerid, dPlayerPos[3]);
        format(string, sizeof(string), "Boombox Owner: {%06x}%s\n{FFFFFF}Use {FFFF79}/setboombox {FFFFFF}to set your Boombox\n{FFFF79}/pickupboombox {FFFFFF}to Pick up your boombox", GetPlayerColor(playerid) >>> 8, Name(playerid));

        if(!IsPlayerInAnyVehicle(playerid)) 
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 2000);

        gBoomboxObject[playerid] = CreateDynamicObject(model_id, dPlayerPos[0], dPlayerPos[1], dPlayerPos[2] - 1.0, 0.0, 0.0, dPlayerPos[3], .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid));
        gBoomboxArea[playerid] = CreateDynamicSphere(dPlayerPos[0], dPlayerPos[1], dPlayerPos[2], BOOMBOX_RANGE_OF_AUDIO, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
        gBoomboxPos[playerid][0] = dPlayerPos[0];
        gBoomboxPos[playerid][1] = dPlayerPos[1];
        gBoomboxPos[playerid][2] = dPlayerPos[2];
        gBoomboxLabel[playerid] = Create3DTextLabel(string, -1, dPlayerPos[0], dPlayerPos[1], dPlayerPos[2] - 0.7, 13.5, GetPlayerVirtualWorld(playerid));

        gBoomboxDroped[playerid] = true;

        format(string,sizeof(string), "%s(%d) Yek Boombox Roye Zamin Gozasht!", Name(playerid), playerid);
        SetPlayerChatBubble(playerid, string, 0xDE9814FF, 25.5, 2000);

        foreach(new i: logged_players)
        {
            if(IsPlayerInRangeOfPoint(i, BOOMBOX_RANGE_OF_AUDIO, dPlayerPos[0], dPlayerPos[1], dPlayerPos[2]))
            {
                Streamer_Update(i, STREAMER_TYPE_AREA);
            }
        }

        PlayerInfo[playerid][boombox]--;
        update_int_sql(playerid, "u_boombox", PlayerInfo[playerid][boombox]);
    }

    #if defined Boombox_OnPlayerClickTextDraw
        return Boombox_OnPlayerClickTextDraw(playerid, clickedid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerClickTextDraw
    #undef OnPlayerClickTextDraw
#else
    #define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw Boombox_OnPlayerClickTextDraw
#if defined Boombox_OnPlayerClickTextDraw
    forward Boombox_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

// --------------------------------------------------------------------------------- //

public OnPlayerDisconnect(playerid, reason)
{
    if(IsPlayerDropedBoomBox(playerid))
    {
        foreach(new i: logged_players)
        {
            if(IsPlayerInDynamicArea(i, gBoomboxArea[playerid]))
            {
                SendClientMessage(i, col_white, ""scm_info"Boombox owner disconnected.");
                StopAudioStreamForPlayer(i);
            }
        }
        gBoomboxDroped[playerid] = false;
        DestroyDynamicObject(gBoomboxObject[playerid]);
        DestroyDynamicArea(gBoomboxArea[playerid]);
        Delete3DTextLabel(gBoomboxLabel[playerid]);
    }

    #if defined Boombox_OnPlayerDisconnect
        return Boombox_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect Boombox_OnPlayerDisconnect
#if defined Boombox_OnPlayerDisconnect
    forward Boombox_OnPlayerDisconnect(playerid, reason);
#endif

// --------------------------------------------------------------------------------- //

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
    foreach(new i: logged_players)
    {
        if(IsPlayerDropedBoomBox(i))
        {
            if(areaid == gBoomboxArea[i])
            {
                StopAudioStreamForPlayer(playerid);

                if(playerid == i) {
                    SendClientMessage(playerid, col_white, ""scm_info"Shoma Az Boombox Khodetan Dor Shodid.");
                } else {
                    new string[80];
                    format(string, sizeof string, ""scm_info"Shoma Az Boombox %s Dor Shodid.", Name(i));
                    SendClientMessage(playerid, col_white, string);
                }
                
                return 0;
            }
        }
    }

    #if defined Boombox_OnPlayerLeaveDynamicAre
        return Boombox_OnPlayerLeaveDynamicAre(playerid, areaid);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerLeaveDynamicArea
    #undef OnPlayerLeaveDynamicArea
#else
    #define _ALS_OnPlayerLeaveDynamicArea
#endif

#define OnPlayerLeaveDynamicArea Boombox_OnPlayerLeaveDynamicAre
#if defined Boombox_OnPlayerLeaveDynamicAre
    forward Boombox_OnPlayerLeaveDynamicAre(playerid, areaid);
#endif

public OnPlayerEnterDynamicArea(playerid, areaid)
{
    foreach(new i: logged_players)
    {
        if(IsPlayerDropedBoomBox(i))
        {
            if(areaid == gBoomboxArea[i])
            {
                if(isnull(gBoomboxURL[i])) break;

                if(i != playerid)
                {
                    new string[100];
                    format(string, sizeof(string), ""scm_info"Shoma Darhale Gosh Dadan Be Boombox %s Mibashid!", Name(i));
                    SendClientMessage(playerid, col_white, string);
                } else
                {
                    SendClientMessage(playerid, col_white, ""scm_info"Shoma Darhale Gosh Dadan Be Boombox Khodetan Hastid!");
                }
                StopAudioStreamForPlayer(playerid);
                PlayAudioStreamForPlayer(playerid, gBoomboxURL[i], gBoomboxPos[i][0], gBoomboxPos[i][1], gBoomboxPos[i][2], BOOMBOX_RANGE_OF_AUDIO, 1);

                return 0;
            }
        }
    }

    #if defined Boombox_OnPlayerEnterDynamicAre
        return Boombox_OnPlayerEnterDynamicAre(playerid, areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif

#define OnPlayerEnterDynamicArea Boombox_OnPlayerEnterDynamicAre
#if defined Boombox_OnPlayerEnterDynamicAre
    forward Boombox_OnPlayerEnterDynamicAre(playerid, areaid);
#endif

CMD:boomboxhelp(playerid) {
    new string[128];
    strcat(string, "{FFFFFF}/boombox\n");
    strcat(string, "{FFFFFF}/pickupboombox\n");
    strcat(string, "{FFFFFF}/setboombox\n");
    strcat(string, "{FFFFFF}/boomboxlink\n");
    strcat(string, "{FFFFFF}/boomboxmodel\n");
    show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, "{B67E18}Boombox Help", string, "Close", "");
    return 1;
}

static ShowPlayerBoomboxList(playerid) {
    show_dialog(
        playerid,
        d_boombox_list,
        DIALOG_STYLE_LIST,
        ""scm_dialog"BoomBox List",
        "Remix\nRadio\nEnter URL",
        "Entekhab",
        "Cancel");
}

CMD:setboombox(playerid, params[]) {
    if (!IsPlayerDropedBoomBox(playerid))
        return 1;
    if(!IsPlayerInRangeOfPoint(playerid, 2.0, gBoomboxPos[playerid][0], gBoomboxPos[playerid][1], gBoomboxPos[playerid][2])) 
        return SendClientMessage(playerid, COLOR_GREY, "Be Kenar Boombox Beravid.");

    ShowPlayerBoomboxList(playerid);
    return 1;
}

Boombox_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if (dialogid == d_boombox_list) {
        if (!response) return 1;

        switch (listitem) {
            case 0: {
                show_dialog(
                    playerid,
                    d_boombox_list_remix,
                    DIALOG_STYLE_LIST,
                    "Remix",
                    "Music",
                    "Play",
                    "Back");
            }
            case 1: {
                show_dialog(
                    playerid,
                    d_boombox_list_radio,
                    DIALOG_STYLE_LIST,
                    "Radio",
                    
                    "Radio Faaz\n\
                    Radio Pulseedm",
                    
                    "Play",
                    "Back");
            }
            case 2: {
                show_dialog(
                    playerid,
                    d_boombox_list_input_url,
                    DIALOG_STYLE_INPUT,
                    "BoomBox input URL",
                    ""c_white"Please put a Music URL to play the Music",
                    "Play",
                    "Back");
            }
        }

        return 1;
    }
    if (dialogid == d_boombox_list_remix) {
        if (!response) {
            ShowPlayerBoomboxList(playerid);
            return 1;
        }

        switch (listitem) {
            case 0: {

            }
        }
        return 1;
    }
    if (dialogid == d_boombox_list_radio) {
        if (!response) {
            ShowPlayerBoomboxList(playerid);
            return 1;
        }

        switch (listitem) {
            case 0: {
                callcmd::boomboxlink(playerid, "http://www.radiofaaz.com:8000/radiofaaz");
            }
            case 1: {
                callcmd::boomboxlink(playerid, "http://pulseedm.cdnstream1.com:8124/1373_128");
            }
        }
        return 1;
    }
    if (dialogid == d_boombox_list_input_url) {
        if (!response) {
            ShowPlayerBoomboxList(playerid);
            return 1;
        }

        if (isnull(inputtext)) {
            show_dialog(
                playerid,
                d_boombox_list_input_url,
                DIALOG_STYLE_INPUT,
                "BoomBox input URL",
                ""c_white"Please put a Music URL to play the Music",
                "Play",
                "Back");
            return 1;
        }

        callcmd::boomboxlink(playerid, inputtext);
        return 1;
    }

    return 0;
}

#undef BOOMBOX_RANGE_OF_AUDIO