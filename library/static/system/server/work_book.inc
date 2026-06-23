//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=| Mihan Role Play|=-=-=-=-=-=-=-=-=-=-=-=-=//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

/* 
    System Information 
    ----------------
    Developer: Abolfazl Hosseini (Github : @inj3ct0r & Tel: @inject3r)
    Name: Work Book System
    Version: 1.0.0
    File Type: pwn

    All rights to this file are reserved by Developer. Unauthorized use, reproduction, or modification of this file is strictly prohibited. 

    Copyright © 2024 Abolfazl Hosseini. All rights reserved. 
*/


new workBookFactionList[] = {3, 4, 5, 6, 7, 10, 14, 15, 16, 26, 28, 17, 18, 19, 20, 21, 22, 23, 24};

cmd:wbook(playerid, params[])
{
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /wbook [id bazikon]");
    if(IsPlayerConnected(params[0]) == 0) return SendError(playerid, "Bazikon Yaft Nashod.");
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, p_t_info[params[0]][p_pos][0], p_t_info[params[0]][p_pos][1], p_t_info[params[0]][p_pos][2]) || GetPlayerVirtualWorld(params[0]) != GetPlayerVirtualWorld(playerid)) return SendError(playerid, "Bazikon kheyli door az shoma ast.");

    if(params[0] == playerid)
    {
        ShowWBook(playerid, playerid);
        SendAction(playerid, "dare sabeghe kari khodesho negah mikone");
    }
    else
    {
        SendAccess(playerid, "Shoma sabeghe kari khod ra be %s[%d] neshan dadid.", get_name(params[0]), params[0]);
		
		new string[128];
		format(string, sizeof(string), ""c_white"Pishnehad shoma be player {%06x}%s "c_white":\n"c_orange_red"Work Book", 
			GetPlayerColor(params[0]) >>> 8,
			Name(params[0]));
		show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, "Pishnehad", string, "Close", "");

		format(string, sizeof(string), "Player {%06x}%s {508EAF}mikhahad ba shoma {E4851B}Sabeghe Kari{508EAF} khod ra be shoma neshan dahad", 
			GetPlayerColor(playerid) >>> 8,
			Name(playerid));
		SendClientMessage(params[0], 0x508EAFFF, string);
		SendClientMessage(params[0], 0x508EAFFF, "Baraye movafeghat "c_green"/yes "c_white"Va Baraye Rad "c_red"/no "c_white"vared konid");


		SetPVarInt(params[0], "WBOOK_Status", 1);
		SetPVarInt(params[0], "WBOOK_Target", playerid);
    }
    return 1;
}

stock ShowWBook(playerid,actplayerid)
{
	if(!IsPlayerConnected(playerid)) return SendError(playerid, "Bazikon Offline Shod.");

	global_string[0] = EOS;

	format(global_string, sizeof(global_string), "Faction Name\tTedad Savabegh\n");

	for (new i = 0; i < sizeof workBookFactionList; i++) {
        new line_string[85];
        format(line_string, sizeof(line_string), c_server"%d | "c_white"%s\t"c_white"%d\n", i+1, f_info[workBookFactionList[i]][f_name], getCountWbook(playerid, workBookFactionList[i]));
        strcat(global_string, line_string);
	}

	new header_title[150];
	format(header_title, sizeof header_title, "%s | Work Book", PlayerInfo[playerid][name]);

	SetPVarInt(actplayerid, "w_targetid", playerid);

    show_dialog(actplayerid, d_work_book, DIALOG_STYLE_TABLIST_HEADERS, header_title, global_string, "Entekhab", "Bastan");
    return 1;
}

stock getCountWbook(playerid, faction_id)
{
	new logsCount = 0;
    new query[256];

    mysql_format(sql_connection, query, sizeof(query), "SELECT `ID` FROM `log_faction` WHERE `Member` = '%d' AND `PlayerID` = '%d'", f_info[faction_id][f_id], PlayerInfo[playerid][id]);

    new Cache:result = mysql_query(sql_connection, query);

    logsCount = cache_num_rows();

    cache_delete(result);

    return logsCount;
}

stock addWorkBook(playerid, _registrar[], _reason[])
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(sql_connection, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `log_faction` (`PlayerID`, `Member`, `Rank`, `Registrar`, `LeftDate`, `CreateData`, `Reason`) SELECT `u_id`, `u_member`, `u_rank`, '%s', `u_fraction_date`, NOW(), '%s' FROM `users` WHERE `u_id` = '%d'",
    _registrar, _reason, PlayerInfo[playerid][id]);
    mysql_tquery(sql_connection, STRING_GLOBAL, "clear_member", "s", PlayerInfo[playerid][name]);
	return 1;
}

stock addOffWorkBook(playerName[], _registrar[], _reason[])
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(sql_connection, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `log_faction` (`PlayerID`, `Member`, `Rank`, `Registrar`, `LeftDate`, `CreateData`, `Reason`) SELECT `u_id`, `u_member`, `u_rank`, '%s', `u_fraction_date`, NOW(), '%s' FROM `users` WHERE `u_name` = '%s'",
    _registrar, _reason, playerName);
    mysql_tquery(sql_connection, STRING_GLOBAL, "clear_member", "s", playerName);

	return 1;
}

stock clearWorkBook(playerid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(sql_connection, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `log_faction` WHERE `PlayerID` = '%d'",
    PlayerInfo[playerid][id]);
    mysql_tquery(sql_connection, STRING_GLOBAL);
	
	return 1;
}

callback:clear_member(playerName[])
{
	new playerid = GetPlayerID(playerName);

	if(IsPlayerConnected(playerid))
	{
		PlayerInfo[playerid][leader] = -1;
		PlayerInfo[playerid][member] = -1;
		PlayerInfo[playerid][rank] = 0;
		PlayerInfo[playerid][org_skin] = 0;
		PlayerInfo[playerid][spawnchange] = 0;

		SetPlayerSkin(playerid, PlayerInfo[playerid][skin]);
		SetPlayerColor(playerid, 0xFFFFFFFF);

		if(is_fraction_duty {playerid}) is_fraction_duty {playerid} = 0;

		UpdatePlayerName(playerid);

		clearTopWarPlayer(playerid);
	}

	format(STRING_GLOBAL,sizeof(STRING_GLOBAL),"UPDATE `users` SET `u_member` = '-1', `u_rank` = '0', `u_leader` = '-1', `u_org_skin` = '0', `u_spawnchange` = '0' WHERE `u_name` = '%s' LIMIT 1", playerName);
	mysql_tquery(sql_connection, STRING_GLOBAL);

	return 1;
}

callback:show_wbook_dialog(playerid){
	new rows,
		fields,
		w_number = 0;
	cache_get_data(rows, fields);

	if(!rows) return SendInfo(playerid, "Hich sabeghe kari dar in faction peyda nashod.");
	
	new targetid = GetPVarInt(playerid, "w_targetid"),
		factionid = GetPVarInt(playerid, "w_faction");
	DeletePVar(playerid, "w_faction");

	global_string[0] = EOS;

	format(global_string, sizeof(global_string), c_grey"Sabt konande\t"c_grey"Rank\t"c_grey"Joined/Left\t"c_grey"Reason\n");


	for(new i = 0; i < rows; i ++)
	{
		new line_string[200];
		
		new w_registrar[100],
			w_rank,
			w_member,
			w_left[25],
			w_joined[25],
			w_reason[70];

		cache_get_field_content(i, "Registrar", w_registrar, sql_connection, 100);
		cache_get_field_content(i, "LeftDate", w_left, sql_connection, 25);
		cache_get_field_content(i, "CreateData", w_joined, sql_connection, 25);
		cache_get_field_content(i, "Reason", w_reason, sql_connection, 70);

		w_rank = cache_get_field_content_int(i, "Rank", sql_connection);
		w_member = cache_get_field_content_int(i, "Member", sql_connection);

		format(line_string, sizeof(line_string), c_white"%s\t%s\t%s %s\t%s", w_registrar, f_rank[w_member -1][w_rank -1], w_left, w_joined, w_reason);

		strcat(global_string, line_string);

		w_number++;
	}

	new w_title[90];
	format(w_title, sizeof w_title, c_server"%s | %s (%d)", PlayerInfo[targetid][name], f_info[factionid][f_name], w_number);

	show_dialog(playerid, d_car, DIALOG_STYLE_TABLIST_HEADERS, w_title, global_string, "Entekhab", "Bastan");

	return 1;
}
