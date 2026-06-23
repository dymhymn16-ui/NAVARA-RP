cmd:setpin(playerid)
{
    show_dialog(playerid, d_setpin, DIALOG_STYLE_INPUT, ""scm_dialog"Tnazim Pin", c_white"Lotfan pin jadid account khod ra vared konid:\n"c_gold"* "c_white"Tavajoh: Baraye hazf pin addad 0 ra vared konid", "OK", "Cancel");

    return 1;
}

cmd:unlockpin(playerid)
{
    if(checkPIN(PlayerInfo[playerid][pin])) return SendInfo(playerid, "Hich pin baraye account shoma set nashodeh. Tanzim pin: "c_yellow"/setpin");
    if(PlyayerIsGang && !PlayerInfo[playerid][pin_status]) return SendInfo(playerid, "Pin account shoma az ghabl unlock shode.");
    show_dialog(playerid, d_pin, DIALOG_STYLE_PASSWORD, ""scm_dialog"Unlock Pin", c_white"Lotfan pin account khod ra vared konid:", "OK", "Cancel");

    return 1;
}

stock checkPIN(pinx)
{
    if(pinx < 1000 || pinx > 9999) return 1;
    else return 0;
}

stock updatePIN(playerid)
{
    update_int_sql(playerid, "u_pin", PlayerInfo[playerid][pin]);

    return 1;
}