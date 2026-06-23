PacifistMode(playerid, issuerid)
{
    // if(!TEST_SYSTEM) return 1;
    if(PlayerInfo[playerid][settings][PACIFIST_MODE])
    {
        if((cop_player(issuerid) || fbi_player(issuerid) || army_player(issuerid) || gov_player(issuerid)) && is_fraction_duty{issuerid}) {
            return 1;
        }
        if(gang_player(playerid) || mafia_player(playerid))
        {
            SendAccess(playerid, "Pacifist Mode: Disabled (Gang | Mafia)");
            PacifistModeToggle(playerid, 0);
            return 1;
        }
        if(GetPlayerVirtualWorld(playerid) == 0 && (GetGangZoneID(playerid) != INVALID_CRIMINAL_ZONE_ID)) {
            return 1;
        }
        if(PlayerInfo[playerid][wanted] != 0)
        {
            SendAccess(playerid, "Pacifist Mode: Disabled (Wanted)");
            PacifistModeToggle(playerid, 0);
            return 1;
        }
        if( duel_opponent[playerid] != INVALID_PLAYER_ID ||
            TeamPaint[playerid] ||
            is_player_race_regged[playerid] || 
            IsPlayerInAnyDMZone(playerid) || 
            ReturnPlayerInCounterStrike(playerid) != 0) 
        {
            return 1;
        }

        //#if !defined _INC_WEAPON_CONFIG
        new Float: health, Float: armour;

        GetPlayerHealth(playerid, health);
        GetPlayerArmour(playerid, armour);
        
        set_health(playerid, health);
        set_armour(playerid, armour);
        //#endif

        GameTextForPlayer(issuerid, "~r~Pacifist Mode", 1000, 3);
        return 0;
    }
    return 1;
}

PacifistModeToggle(playerid, toggle)
{
    PlayerInfo[playerid][settings][PACIFIST_MODE] = toggle;
    UpdatePlayerSettings(playerid);
}
CMD:pacifist(playerid)
{
    if(p_t_info[playerid][pacifist_time] > timestamp) return SendError(playerid, "Wait 15 Seconds.");
    if(PlyayerIsGang && !PlayerInfo[playerid][settings][PACIFIST_MODE])
    {
        if(gang_player(playerid) || mafia_player(playerid))
            return SendError(playerid, "You are gang or mafia.");
        if((cop_player(playerid) || fbi_player(playerid) || army_player(playerid) || gov_player(playerid)) && is_fraction_duty{playerid})
            return SendError(playerid, "You are on duty.");
        if(PlayerInfo[playerid][wanted] != 0)
            return SendError(playerid, "You Have Wanted Level.");
    }
    p_t_info[playerid][pacifist_time] = timestamp+15;
    PacifistModeToggle(playerid, !PlayerInfo[playerid][settings][PACIFIST_MODE]);
    SendAccess(playerid, "Pacifist Mode: %s", PlayerInfo[playerid][settings][PACIFIST_MODE] == 0 ? "Disabled" : "Enabled");
    return 1;
}

CMD:pacifistinfo(playerid)
{
    show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""scm_dialog"Pacifist Mode", "\
        "c_white"Ba aktivate kardan ("c_green"/pacifist"c_white") in mode - shoma "c_yellow"be haami"c_white"\n\
        az zarbat aslahhaye digaran, be joz mo'amele government.\n\
        Dar ham zamane, shoma dastresi be estefade az aslahhaye khod ra az dast midahid.\n\
        \n\
        In mode be tore khodkar baraye bazikonan dar sathe avval va dovom bedun faction fa'al mishavad.\n\
        Baraye bazikonan dar sathe balatar, ye rahnamayi zamane vared shodan be bazi faraham mishavad.\n\
        Dar in mode, 15 saniye vaght baraye aktivate va deactivate kardan vojood darad.\n\
        \n\
        In mode chand mahdudiyat darad: in nemitavanad tavasote a'za ye saazmanhaye qezbi\n\
        ya karmandan government dar zamane kar kardan estefade shavad.\n\
        In mode khodkar ghafl mishavad agar: shoma yek maratabe zindan shavid, vared Ghetto ya Family Zones shavid.\n\
        Dar mode pacifist, mask (/mask) na dostupish nist.\n\
        In mode kar nemikonad agar shoma dar sparring ya events shirakat konid.", "Fahmidam", "");
    return 1;
}
