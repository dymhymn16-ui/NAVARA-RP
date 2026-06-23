new Float:csjailpos[15][3] = {
    {-960.2534,1952.4518,9.0000},
    {-960.2540,1940.9476,9.0000},
    {-960.2432,1924.7424,9.0000},
    {-960.2492,1903.5723,9.0000},
    {-960.2523,1882.6263,9.0000},
    {-960.2436,1860.2688,9.0000},
    {-960.2490,1848.6647,9.0000},
    {-945.9603,1867.6355,5.0000},
    {-946.1104,1865.8285,5.0000},
    {-943.8152,1889.3751,5.0000},
    {-943.6862,1891.3250,5.0000},
    {-946.1864,1908.6964,5.0000},
    {-945.0101,1910.8713,5.0000},
    {-943.8923,1932.5713,5.0000},
    {-942.8617,1934.3732,5.0000}
};

cmd:csjail(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "uds[42]", params[0], params[1], params[2])) return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /csjail [id/name] [tedad] [dalil]");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, col_gray,""scm_error"Bazikon yaft nashod.");
	if(params[1] < 1 || params[1] > 1000) return SendClientMessage(playerid, col_gray,""scm_error"Tedad khadamate nemitavanad az 1 kamtar va az 1000 bishtar bashad.");
	if(PlayerInfo[params[0]][csjail] > 0) return SendClientMessage(playerid, col_gray,""scm_error"In bazikon darhal hazer dar csjail ast.");
	
	
    SendAdmin("Admin %s player %s baraye %d khedmat ejtemaii admin jail kard. (Dalil: %s)", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1], params[2]);
    SendSelfAdmin(params[0], "Admin %s shoma ro baraye %d khedmat ejtemaii be admin jail andakht. (Dalil: %s)", PlayerInfo[playerid][name], params[1], params[2]);
    new scm_string[250];

	format(scm_string,sizeof(scm_string),"UPDATE `users_admins` SET `u_a_csjails` = `u_a_csjails`+1 WHERE `u_a_name` = '%s' LIMIT 1", PlayerInfo[playerid][name]);
	mysql_tquery(sql_connection, scm_string, "", "");

	PlayerInfo[params[0]][csjail] = params[1];
    format(PlayerInfo[params[0]][jail_reason], 100, "%s", params[2]);
	update_int_sql(params[0], "u_csjail", PlayerInfo[params[0]][csjail]);
	
    new random_csjail = random(sizeof csjailpos);
 	set_pos(params[0], -959.4586,1954.3555,9.0000,180.0,1, 15);
 	SetPlayerInterior(params[0],17);
 	SetPlayerCheckpoint(params[0],csjailpos[random_csjail][0],csjailpos[random_csjail][1],csjailpos[random_csjail][2],0.5);
 	

    SendInfo(params[0], "Shoma Bayad {0099FF}%d{FFFFFF} Kar Digar Baraye {66CC00}Azadi{FFFFFF} Anjam Dahid", params[1]);

 	SetPlayerSkin(params[0], 42);
	
    mysql_format(sql_connection, scm_string,sizeof(scm_string),"UPDATE `users` SET `u_jail_reason`='%e' WHERE `u_id`='%d'", params[2], PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, scm_string, "", "");

	return 1;
}

forward csjail_callback(playerid);
public csjail_callback(playerid)
{
    PlayerInfo[playerid][csjail]--;
    update_int_sql(playerid, "u_csjail", PlayerInfo[playerid][csjail]);
    if(PlayerInfo[playerid][csjail] == 0) {
        SendAccess(playerid, "Shoma khadamat-e ejtemaei khod ra etmam kardid va ham aknoon azad hastid.");
        return SpawnPlayer(playerid);
    }
    new rand = random(sizeof(csjailpos));
    SetPlayerCheckpoint(playerid,csjailpos[rand][0],csjailpos[rand][1],csjailpos[rand][2],0.5);


    SendInfo(playerid, "Shoma Bayad {0099FF}%d{FFFFFF} Kar Digar Baraye {66CC00}Azadi{FFFFFF} Anjam Dahid", PlayerInfo[playerid][csjail]);

    return 1;
}