#define LOG_SMS true
#include "../library/static/system/server/sms/Short_Message_Sender.inc"

// ----------------------------------------------

#define DIALOG_VERIFYING                    9250
#define DIALOG_VERIFYING_CODE               9251

#define MAX_REGISTER_WITH_ONE_NUMBER        1

// ----------------------------------------------

new REGISTER_WITH_PHONE_NUMBER;

new pPhoneNumber[MAX_PLAYERS][13];
new pTempPhoneNumber[MAX_PLAYERS][13];
new pCodeNumber[MAX_PLAYERS];
new CodeVerifyingPhoneTime[MAX_PLAYERS];

// ----------------------------------------------

stock DialogPhoneNumber(playerid)
    return show_dialog(playerid, DIALOG_VERIFYING, DIALOG_STYLE_INPUT, ""scm_dialog"Sabt Shomare Tamas", c_white"Shomare telephone khodeton ra jahat sakht account vared konid:", "Next", "");

stock Dialog_SMS(playerid, response, inputtext[]) { //DIALOG_VERIFYING
    if (!response)
        return DialogPhoneNumber(playerid);

    if (!IsValidPhoneNumber(inputtext))
    {
        SendInfo(playerid, "Shomare vared shode eshtebah mibashad!");
        return show_dialog(playerid, DIALOG_VERIFYING, DIALOG_STYLE_INPUT, ""scm_dialog"Sabt Shomare Tamas", c_white"Shomare telephone khodeton ra jahat sakht account vared konid:\n\n"c_orange_red"* Shomare vared shode eshtebah mibashad!\n* Shomare telephone bayad ba adad"c_yellow" 0 "c_orange_red"shoro shode bashad.\n* Baraye Mesal : "c_yellow"09120123012", "Next", "");
    }

    new string[240];
    new Cache: mresult;
    new ph_row;

    format(string, 144, "SELECT `u_name` FROM `users` WHERE `phone_number`='%s'", inputtext);
    mresult = mysql_query(sql_connection, string);
    ph_row = cache_num_rows();
    cache_delete(mresult);
    if (ph_row >= MAX_REGISTER_WITH_ONE_NUMBER) { 
        show_dialog(playerid, DIALOG_VERIFYING, DIALOG_STYLE_INPUT, ""scm_dialog"Sabt Shomare Tamas", c_white"Shomare telephone khodeton ra jahat sakht account vared konid:\n\n"c_orange_red"* Shomare telefon vared shode az ghabl sabt shode!\n* Lotfan yek shomare telefon digari vared konid.", "Next", "");
        return 1;
    }

    pCodeNumber[playerid] = (random(99998-10002)+10002);

    new value = SendVerificationSMS(playerid, inputtext, pCodeNumber[playerid]);

    if (value == INVALID_PHONE_NUMBER)
    {
        SendInfo(playerid, "Shomare vared shode eshtebah mibashad!");
        return show_dialog(playerid, DIALOG_VERIFYING, DIALOG_STYLE_INPUT, ""scm_dialog"Vared Kardan Code", c_white"Shomare telephone khodeton ra jahat sakht account vared konid:\n\n"c_orange_red"* Shomare vared shode eshtebah mibashad!\n* Shomare telephone bayad ba adad"c_yellow" 0 "c_orange_red"shoro shode bashad.\n* Baraye Mesal : "c_yellow"09120123012", "Next", "");
    }

    if (value == 1) {

        CodeVerifyingPhoneTime[playerid] = (1 * 60) + 15; // 1:15 min

        format(pTempPhoneNumber[playerid], 12, "%s", inputtext);

        SendInfo(playerid, "Be shomare "c_server"%s"c_white" yek code ersal shod.", inputtext);

        format(string, sizeof string, "{FFFFFF}Payamak Code Be {6BFE76}%s {FFFFFF}Ersal Shod.\n{FFFFFF}Lotfan {E0360C}Code {FFFFFF}Ra Vared Konid:", inputtext);
        show_dialog(playerid, DIALOG_VERIFYING_CODE, DIALOG_STYLE_INPUT, ""scm_dialog"Vared Kardan Code", string, "Sabt", "Back");
        return 1;
    }
    return 1;
}

stock Dialog_SMScode(playerid, response, inputtext[]) { //DIALOG_VERIFYING_CODE
    if (!response) {

        if (CodeVerifyingPhoneTime[playerid] > 0) {
            new string[320];
            new timesss, sece, mine;
            timesss = CodeVerifyingPhoneTime[playerid];
            timesss /= 60;
            sece = CodeVerifyingPhoneTime[playerid];
            mine = timesss;
            timesss *= 60;
            sece -= timesss;
            
            format(string, sizeof string, "{FFFFFF}Payamak Code Be {6BFE76}%s {FFFFFF}Ersal Shod.\n{FFFFFF}Lotfan {8FF381}Code {FFFFFF}Ra Vared Konid:\n\n{FFFFFF}[ERROR] Baraye Taghir Shomare Telephone Bayad {FF2D2D}%02d:%02d {FFFFFF}Sabr Konid!", pTempPhoneNumber[playerid], mine, sece);
            show_dialog(playerid, DIALOG_VERIFYING_CODE, DIALOG_STYLE_INPUT, ""scm_dialog"Vared Kardan Code", string, "Sabt", "Back");
            return 0;
        }

        return DialogPhoneNumber(playerid);
    }

    new string[320];
    if (pCodeNumber[playerid] != strval(inputtext))
    {
        format(string, sizeof string, "{FFFFFF}Payamak Code Be {6BFE76}%s {FFFFFF}Ersal Shod.\n{FFFFFF}Lotfan {E0360C}Code {FFFFFF}Ra Vared Konid:\n\n{FF2D2D}Code Vared Shode Eshtebah Ast.", pTempPhoneNumber[playerid]);
        show_dialog(playerid, DIALOG_VERIFYING_CODE, DIALOG_STYLE_INPUT, ""scm_dialog"Vared Kardan Code", string, "Sabt", "Back");
        return 1;
    }

    SendInfo(playerid, "Shomare telephone "c_server"%s"c_white" sabt shod!", pTempPhoneNumber[playerid]);

    format(pPhoneNumber[playerid], 12, "%s", pTempPhoneNumber[playerid]);

    if(GetPVarInt(playerid, "first_entrance") == 1)
    {
        //register
        DeletePVar(playerid, "step_reg");

        KillTimer(timerShowCityPart[playerid]);

        SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
        // --------
    }
    else
    {
        SavePlayerPhoneNumber(playerid);

        //login
        if (p_t_info[playerid][LastPositionUnix] > timestamp &&
            PlayerInfo[playerid][jailed] == 0)
        {
            if (!IsPlayerInRangeOfPoint(playerid, 10.0, p_t_info[playerid][LastPositionX], p_t_info[playerid][LastPositionY], p_t_info[playerid][LastPositionZ])) {
                show_dialog(playerid, d_goto_last_position, DIALOG_STYLE_MSGBOX, ""scm_dialog"Makan Ghabl", "{FFFFFF}Aya Mikhahid Be "c_server"Makan Ghabli {FFFFFF}Bargardid?", "Bale", "Kheyr");
            }
        }
        else {
            // TogglePlayerSpectating(playerid, true);
            TogglePlayerSpectating(playerid, false); //login camera related
            // SpawnPlayer(playerid);
        }
        // --------
    }

    return 1;
}

static SavePlayerPhoneNumber(playerid) {
    new query[100];
    format(query, sizeof query, "UPDATE `users` SET `phone_number`='%s' WHERE `u_id`=%d", pTempPhoneNumber[playerid], PlayerInfo[playerid][id]);
    mysql_tquery(sql_connection, query);
}

stock SMS_System_ResetPlayerData(playerid) {
    pPhoneNumber[playerid][0] = EOS;
    pTempPhoneNumber[playerid][0] = EOS;
    pCodeNumber[playerid] = 0;
    CodeVerifyingPhoneTime[playerid] = 0;
}

// ----------------------------------------------

CMD:getnumber(playerid, params[]) {

	if (ReturnPlayerAdminLevel(playerid) < 8)
		return 1;

    new targetid;
    if(sscanf(params, "r", targetid))
        return SendInfo(playerid, "Enter: /getnumber <playerid/name>");
    if(!IsPlayerConnected(targetid))
        return SendError(playerid, "In Bazikon Dar Server Nemibashad.");
    if(p_t_info[targetid][p_logged] == false)
        return SendError(playerid, "In Bazikon Login Nashode Ast.");
    if(!IsValidPhoneNumber(pPhoneNumber[targetid]))
        return SendError(playerid, "In Bazikon Shomare Tamas Sabt Nakarde Ast.");

    new string[200]; 
    new phone[19];

    format(phone, sizeof(phone), "%s", pPhoneNumber[targetid]); //SensorPhoneNumber(playerid, pPhoneNumber[targetid])
    
    strins(phone, " ", 4);
    strins(phone, " ", 8);

    format(string, sizeof(string), "{DF0255}%s\t{FFFFFF}%s", Name(targetid), phone);

    show_dialog(playerid, DIALOG_VERIFYING_CODE+1, DIALOG_STYLE_TABLIST, "{FFCED7}Player Phone Number", string, "OK", "");
    return 1;
}

CMD:offgetnumber(playerid, params[]) {

	if (ReturnPlayerAdminLevel(playerid) < 8)
		return 1;

    new tName[20];
    if(sscanf(params, "s[20]", tName))
        return SendInfo(playerid, "Enter: /offgetnumber <Player Name>");

    new targetid = GetPlayerID(tName);
    if (IsPlayerConnected(targetid)) {
        new string[5];
        format(string, 5, "%d", targetid);
        callcmd::getnumber(playerid, string);
        return 1;
    }

    new string[200], phone[19], RealTargetName[20];

    format(string, 100, "SELECT `u_name`,`phone_number` FROM `users` WHERE `u_name`='%s'", tName);
    new Cache: result = mysql_query(sql_connection, string);
    if (cache_num_rows()) { 
        // cache_get_value_index(0, 0, RealTargetName);
        // cache_get_value_index(0, 1, phone);

        cache_get_field_content(0, "u_name", RealTargetName, sql_connection, sizeof RealTargetName);
        cache_get_field_content(0, "phone_number", phone, sql_connection, sizeof phone);
    } else {
        return SendError(playerid, "In Name Dar Server Sabt Nashode Ast.");
    }
    cache_delete(result);

    if(!IsValidPhoneNumber(phone))
        return SendError(playerid, "In Bazikon Shomare Tamas Sabt Nakarde Ast.");

    strins(phone, " ", 4);
    strins(phone, " ", 8);

    format(string, sizeof(string), "{DF0255}%s\t{FFFFFF}%s", RealTargetName, phone);

    show_dialog(playerid, DIALOG_VERIFYING_CODE+1, DIALOG_STYLE_TABLIST, "{FFCED7}Player Phone Number", string, "OK", "");
    return 1;
}

// --------------------------------------------------------------------------------------------- //

CMD:registersms(playerid, params[]) {
    if (ReturnPlayerAdminLevel(playerid) < 8)
        return 1;

    new toggle;
    if(sscanf(params, "d", toggle)) {
        return SendInfo(playerid, "Enter: /registersms <0 - 1>");
    }
    if(!(0 <= toggle <= 1)) {
        return SendInfo(playerid, "Enter: /registersms <0 - 1>");
    }

    new string[64];
    
    REGISTER_WITH_PHONE_NUMBER = toggle;

    if (toggle) {
        SendInfo(playerid, "Sabte Nam Ba Taied Shomare "c_green"Roshan "c_white"Shod");
    } else {
        SendInfo(playerid, "Sabte Nam Ba Taied Shomare "c_red"Khamosh "c_white"Shod");
    }

    format(string, sizeof string, "UPDATE `server_info` SET `register_with_phone_number` = %d", REGISTER_WITH_PHONE_NUMBER);
    mysql_tquery(sql_connection, string);
    return 1;
}

// --------------------------------------------------------------------------------------------- //