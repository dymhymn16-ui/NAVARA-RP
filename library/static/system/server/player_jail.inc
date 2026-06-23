stock isPlayerInJail(playerid)
{
    if(PlayerInfo[playerid][jailed] > 0 || PlayerInfo[playerid][csjail] > 0) return true;
    else return false;
}

stock unJailPlayer(playerid)
{
	PlayerInfo[playerid][jailed] = 0;
	PlayerInfo[playerid][jail] = 0;
	PlayerInfo[playerid][csjail] = 0;
	PlayerInfo[playerid][bail] =
	PlayerInfo[playerid][wanted] = 0;

	DestroyPlayerTimeJailTextdraw(playerid);

	update_int_sql(playerid, "u_jail", PlayerInfo[playerid][jail]);
	update_int_sql(playerid, "u_jailed", PlayerInfo[playerid][jailed]);
	update_int_sql(playerid, "u_csjail", PlayerInfo[playerid][csjail]);
	update_int_sql(playerid, "u_wanted", PlayerInfo[playerid][wanted]);
	update_int_sql(playerid, "u_bail", PlayerInfo[playerid][bail]);

	SpawnPlayer(playerid);

    return 1;
}

cmd:jail(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "uds[42]", params[0], params[1], params[2]))
		return SendInfo(playerid, "Enter: /jail [id/name] [Daghighe] [Dalil]");
	if(!IsPlayerConnected(params[0]))
		return SendError(playerid, "Bazikon Yaft Nashod.");
	if(params[1] < 1 || params[1] > 180)
		return SendError(playerid, "Had jail az 1 min ta 180 min ast.");
	if(isPlayerInJail(params[0]))
	    return SendError(playerid, "In bazikon dar darhal hazer dar jail!");
	    
	new scm_string[250];
	
	SendAdmin("Admin %s Player %s baraye %d daghighe admin jail kard. (Dalil: %s)", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1], params[2]);

	if(PlyayerIsGang && !PlayerInfo[params[0]][settings][2]) SendMes(params[0], col_light_red, "Admin %s Player %s baraye %d daghighe admin jail kard. (Dalil: %s)", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1], params[2]);

	format(scm_string,sizeof(scm_string),"UPDATE `users_admins` SET `u_a_jails` = `u_a_jails`+1 WHERE `u_a_name` = '%s' LIMIT 1", PlayerInfo[playerid][name]);
	mysql_tquery(sql_connection, scm_string);

	if(GetPVarInt(params[0], "PlayerCuffed")!= 0)
	{
		DeletePVar(params[0], "PlayerCuffed");
		SetPlayerSpecialAction(params[0], SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(params[0], 1);
	}

	PlayerInfo[params[0]][jailed] = params[1]* 60;
	PlayerInfo[params[0]][jail] = 10;
	format(PlayerInfo[params[0]][jail_reason], 100, "%s", params[2]);

	new random_jail_pos = random(sizeof admin_jail_spawn);
	set_pos(params[0], admin_jail_spawn[random_jail_pos][0],
		admin_jail_spawn[random_jail_pos][1],
		admin_jail_spawn[random_jail_pos][2],
		admin_jail_spawn[random_jail_pos][3],
		1, 15);

	
	ResetPlayerWeapons(params[0]);

	mysql_format(sql_connection, scm_string,sizeof(scm_string),"UPDATE `users` SET `u_jail_reason`='%e',`u_jail`=%d WHERE `u_id`='%d'", params[2], PlayerInfo[params[0]][jail], PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, scm_string, "", "");
	return 1;
}

cmd:unjail(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;

	if(sscanf(params, "us[32]", params[0], params[1]))
        return SendInfo(playerid, "Enter: /unjail [id/name] [dalil]");

	if(strval(params[1]) > 32) return SendError(playerid, "Dalil toolani ast.");
		
	if(!IsPlayerConnected(params[0]))
		return SendError(playerid, "Bazikon Yaft Nashod.");

	if(!isPlayerInJail(params[0]))
	    return SendError(playerid, "In bazikon dar jail nist.");
	    
	SendAdmin("Admin %s Player %s az jail azad kard. (Dalil: %s).", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1]);

    unJailPlayer(params[0]);

	return 1;
}

cmd:unjailall(playerid, params[])
{
	if(check_admin_rank(playerid , 7)) return 1;

	new found_any_jailed_player;

	SendAdmin("Admin %s Hame bazikonan online ra az zendaan azad kard.", PlayerInfo[playerid][name]);

	foreach(new i: logged_players) {
		
		if(!isPlayerInJail(i)) continue;
		
		unJailPlayer(i);

		found_any_jailed_player++;
	}

	if(found_any_jailed_player == 0)
	    return SendError(playerid, "Hich bazikoni dar jail nsit!");

	return 1;
}

cmd:offjail(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	new
		jname[MAX_PLAYER_NAME],
		jtime,
		reason[32];
		
	if(sscanf(params, "s[24]ds[32]", jname, jtime, reason)) return SendInfo(playerid, "Enter: /offjail [Player name] [Daghighe] [Dalil]");
	if(!(0 < jtime <= 180)) return SendError(playerid, "Zaman hadaghal bayad 1 min ta 180 min bashe.");

	new player = GetPlayerID(jname);

	if(IsPlayerConnected(player)) return SendError(playerid, "Dar hal hazer bazikon online ast , bezan: /jail.");

	new sql_string[50 + MAX_PLAYER_NAME];
	format(sql_string, sizeof sql_string, "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", jname);
	mysql_tquery(sql_connection, sql_string, "offjail_check_callback", "isds", playerid, jname, jtime, reason);
	return 1;
}

//////////////////////////////////////
	    ////Time Jail Text Draw////
//////////////////////////////////////

CreatePlayerTimeJailTextdraw(playerid)
{
	if(ptd_jailtime[playerid][0] == PlayerText:INVALID_TEXT_DRAW) {
		ptd_jailtime[playerid][0] = CreatePlayerTextDraw(playerid, 27.000000, 266.000000, "Jail Time :");
		PlayerTextDrawLetterSize(playerid, ptd_jailtime[playerid][0], 0.350000, 1.900000);
		PlayerTextDrawTextSize(playerid, ptd_jailtime[playerid][0], 400.000000, 17.000000);
		PlayerTextDrawAlignment(playerid, ptd_jailtime[playerid][0], 1);
		PlayerTextDrawColor(playerid, ptd_jailtime[playerid][0], 0xFF0000FF);
		PlayerTextDrawBoxColor(playerid, ptd_jailtime[playerid][0], 0x00000032);
		PlayerTextDrawSetShadow(playerid, ptd_jailtime[playerid][0], 0);
		PlayerTextDrawSetOutline(playerid, ptd_jailtime[playerid][0], 0);
		PlayerTextDrawBackgroundColor(playerid, ptd_jailtime[playerid][0], 0x000000FF);
		PlayerTextDrawFont(playerid, ptd_jailtime[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, ptd_jailtime[playerid][0], 1);
		PlayerTextDrawSetSelectable(playerid, ptd_jailtime[playerid][0], 0);
		PlayerTextDrawSetPreviewRot(playerid, ptd_jailtime[playerid][0], 0.000000, 0.000000, 0.000000, 1.000000);

		ptd_jailtime[playerid][1] = CreatePlayerTextDraw(playerid, 91.000000, 266.000000, "0 Sanie");
		PlayerTextDrawLetterSize(playerid, ptd_jailtime[playerid][1], 0.350000, 1.900000);
		PlayerTextDrawTextSize(playerid, ptd_jailtime[playerid][1], 400.000000, 17.000000);
		PlayerTextDrawAlignment(playerid, ptd_jailtime[playerid][1], 1);
		PlayerTextDrawColor(playerid, ptd_jailtime[playerid][1], 0xFFFFFFFF);
		PlayerTextDrawBoxColor(playerid, ptd_jailtime[playerid][1], 0x00000032);
		PlayerTextDrawSetShadow(playerid, ptd_jailtime[playerid][1], 0);
		PlayerTextDrawSetOutline(playerid, ptd_jailtime[playerid][1], 0);
		PlayerTextDrawBackgroundColor(playerid, ptd_jailtime[playerid][1], 0x000000FF);
		PlayerTextDrawFont(playerid, ptd_jailtime[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, ptd_jailtime[playerid][1], 1);
		PlayerTextDrawSetSelectable(playerid, ptd_jailtime[playerid][1], 0);
		PlayerTextDrawSetPreviewRot(playerid, ptd_jailtime[playerid][1], 0.000000, 0.000000, 0.000000, 1.000000);
	}
}

UpdatePlayerTimeJailTextdraw(playerid)
{
	if(ptd_jailtime[playerid][0] == PlayerText:INVALID_TEXT_DRAW) {
		CreatePlayerTimeJailTextdraw(playerid);
	}

	new string[32];
		
	format(string, sizeof(string), "%d Sanie", PlayerInfo[playerid][jailed]);
	PlayerTextDrawSetString(playerid, ptd_jailtime[playerid][1], string);
	PlayerTextDrawShow(playerid, ptd_jailtime[playerid][0]);
	PlayerTextDrawShow(playerid, ptd_jailtime[playerid][1]);
}

DestroyPlayerTimeJailTextdraw(playerid)
{
	if(ptd_jailtime[playerid][0] != PlayerText:INVALID_TEXT_DRAW) {
		PlayerTextDrawDestroy(playerid, ptd_jailtime[playerid][0]);
		PlayerTextDrawDestroy(playerid, ptd_jailtime[playerid][1]);
		ptd_jailtime[playerid][0] = PlayerText:INVALID_TEXT_DRAW;
	}
}

callback: offjail_check_callback(playerid, jname[], jtime, reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new string[104 + MAX_PLAYER_NAME + 42];
		format(string, sizeof string, "UPDATE `users` SET `u_jail` = '10', `u_jailed` = '%d' WHERE `u_name` = '%s' LIMIT 1", jtime * 60, jname);
		mysql_query(sql_connection, string);

		SendAdmin("Admin %s Player %s offline baraye %d daghighe admin jail kard. (Dalil: %s)", PlayerInfo[playerid][name], jname, jtime, reason);
	}
	else
	{
		SendError(playerid, "Hesab %s dar database peyda nashod.", jname);
	}
	return 1;
}