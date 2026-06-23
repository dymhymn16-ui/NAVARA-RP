
stock after_global(playerid)
{
    new string_wc[30+MAX_PLAYER_NAME];
    format(string_wc, sizeof(string_wc), "~b~Welcome ~n~~w~ %s", PlayerInfo[playerid][name]);
	GameTextForPlayer(playerid, string_wc, 5000, 1);

    // Voice Setting
    VoiceMuted[playerid] = false;
    PlayerHaveStreamKey[playerid] = SV_GSTREAM:-1;

    SendInfo(playerid, "Ba movafghiat vared shodid. lahazat khoshi ro dar "c_server"Mihan Role Play"c_white" tajrobe konid.");
	
    if(SvGetVersion(playerid) == SV_NULL)
    {
        if(!IsPlayerUsingSampMobile(playerid)) SendError(playerid, "VoiceChat: "c_white"Plugin voice chat peyda nashod.");
    }
    else if(SvHasMicro(playerid) == SV_FALSE)
    {
        if(!IsPlayerUsingSampMobile(playerid)) SendError(playerid, "VoiceChat: "c_white"Shoma microphone nadarid.");
    }
    else if((lstream[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "Local")))
    {
        if(!IsPlayerUsingSampMobile(playerid)) SendInfo(playerid, "VoiceChat: "c_white"Ba Dokme [B] Mitoni Voice Bedi ba PC.");
        SvAddKey(playerid, 0x42);
    }

    if(PlyayerIsGang && !PlayerInfo[playerid][settings][AUTO_LOGIN])
    {
        SendInfo(playerid, "AutoLogin "c_red"khamosh"c_white" mibashad. roshan kardan: /autologin");
    }else
    {
        SendInfo(playerid, "AutoLogin "c_green"roshan"c_white" mibashad. khamosh kardan: /autologin");
    }

    if(!checkPIN(PlayerInfo[playerid][pin]))
    {
        SendInfo(playerid, "Lotfan pin account khod ra ba dastor /unlockpin baz konid");
    }
    else
    {
        SendInfo(playerid, "Baraye afzayesh amniyat account, pin tanzim konid : /setpin");
    }
    
    if(PlayerInfo[playerid][level] > 3)
    {
        SendInfo(playerid, "Pacifist mode shoma khamosh mibashad. rahnama: /pacifistinfo");
    }else
    {
        PacifistModeToggle(playerid, 1);
        SendInfo(playerid, "Pacifist mode shoma roshan mibashad. rahnama: /pacifistinfo");
    }

    SendInfo(playerid, "Tanzimat character, dastorat server, ertebat ba admin va forushgah server: "c_gold_main"/menu");
}

stock after_login(playerid)
{
    after_global(playerid);
}

stock after_reg(playerid)
{
    after_global(playerid);
    PlayerInfo[playerid][level] = 1;
	update_int_sql(playerid, "u_level", PlayerInfo[playerid][level]);
	SetPlayerScore(playerid, PlayerInfo[playerid][level]);

    AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] dakhel server sabtenam kard!", PlayerInfo[playerid][name], playerid);
}