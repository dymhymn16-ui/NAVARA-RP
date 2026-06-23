
callback: fractions_loading()
{
	new fields;
	cache_get_data(fraction_count, fields);
	new str_to_hex[28];
	if(fraction_count)
	{
		for(new i = 0; i < fraction_count; i++)
		{
			f_info[i][f_id] = cache_get_field_content_int(i, "f_id", sql_connection);
			cache_get_field_content(i, "f_name", f_info[i][f_name], sql_connection, 48);

			f_info[i][f_money] = cache_get_field_content_int(i, "f_money", sql_connection);
			f_info[i][f_materials] = cache_get_field_content_int(i, "f_materials", sql_connection);
			f_info[i][f_drugs] = cache_get_field_content_int(i, "f_drugs", sql_connection);
			f_info[i][f_guns] = cache_get_field_content_int(i, "f_guns", sql_connection);
			f_info[i][f_dorm_status] = cache_get_field_content_int(i, "f_dorm_status", sql_connection);

			cache_get_field_content(i, "f_leader_name", f_info[i][f_leader_name], sql_connection, MAX_PLAYER_NAME);
			cache_get_field_content(i, "f_chat_color", f_info[i][f_chat_color], sql_connection, 28);
			cache_get_field_content(i, "f_radar_color", str_to_hex, sql_connection, 28);
			f_info[i][f_radar_color] = StrToHex(str_to_hex);

			global_string[0] = EOS;
			cache_get_field_content(i, "f_spawn", global_string), sscanf(global_string, "p<|>ffffdd",
			f_info[i][f_spawn][0], f_info[i][f_spawn][1], f_info[i][f_spawn][2], f_info[i][f_spawn][3],
			f_info[i][f_spawn_int], f_info[i][f_spawn_virt]);


			global_string[0] = EOS;
			if(i > 17 && i < 26)
			{
				cache_get_field_content(i, "f_dip", global_string), sscanf(global_string, "p<|>dddddddd",
				f_diplomacy[i -18][0], f_diplomacy[i -18][1], f_diplomacy[i -18][2],
				f_diplomacy[i -18][3], f_diplomacy[i -18][4], f_diplomacy[i -18][5],
				f_diplomacy[i -18][6], f_diplomacy[i -18][7]);
			}
			global_string[0] = EOS;
			cache_get_field_content(i, "f_ranks", global_string), sscanf(global_string, "p<|>s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]",
			f_rank[i][0], f_rank[i][1], f_rank[i][2], f_rank[i][3],
			f_rank[i][4], f_rank[i][5], f_rank[i][6], f_rank[i][7],
			f_rank[i][8], f_rank[i][9], f_rank[i][10], f_rank[i][11],
			f_rank[i][12], f_rank[i][13], f_rank[i][14], f_rank[i][15]);

			global_string[0] = EOS;
			cache_get_field_content(i, "f_salary", global_string), sscanf(global_string, "p<|>dddddddddddddddd",
			f_info[i][f_rank_salary][0], f_info[i][f_rank_salary][1], f_info[i][f_rank_salary][2],
			f_info[i][f_rank_salary][3], f_info[i][f_rank_salary][4], f_info[i][f_rank_salary][5],
			f_info[i][f_rank_salary][6], f_info[i][f_rank_salary][7], f_info[i][f_rank_salary][8],
			f_info[i][f_rank_salary][9], f_info[i][f_rank_salary][10], f_info[i][f_rank_salary][11],
			f_info[i][f_rank_salary][12], f_info[i][f_rank_salary][13], f_info[i][f_rank_salary][14],
			f_info[i][f_rank_salary][15]);

			global_string[0] = EOS;
			cache_get_field_content(i, "f_skins_m", global_string), sscanf(global_string, "p<|>dddddddddddddddd",
			f_skin[i][0][0], f_skin[i][0][1], f_skin[i][0][2], f_skin[i][0][3],
			f_skin[i][0][4], f_skin[i][0][5], f_skin[i][0][6], f_skin[i][0][7],
			f_skin[i][0][8], f_skin[i][0][9], f_skin[i][0][10], f_skin[i][0][11],
			f_skin[i][0][12], f_skin[i][0][13], f_skin[i][0][14], f_skin[i][0][15]);

			global_string[0] = EOS;
			cache_get_field_content(i, "f_skins_f", global_string), sscanf(global_string, "p<|>dddddddddddddddd",
			f_skin[i][1][0], f_skin[i][1][1], f_skin[i][1][2], f_skin[i][1][3],
			f_skin[i][1][4], f_skin[i][1][5], f_skin[i][1][6], f_skin[i][1][7],
			f_skin[i][1][8], f_skin[i][1][9], f_skin[i][1][10], f_skin[i][1][11],
			f_skin[i][1][12], f_skin[i][1][13], f_skin[i][1][14], f_skin[i][1][15]);

			f_info[i][tp_label] = Text3D:INVALID_3DTEXT_ID;

			global_string[0] = EOS;
			cache_get_field_content(i, "f_rank_settings", global_string), sscanf(global_string, "p<|>ddddd",
			f_info[i][f_rank_settings][0], f_info[i][f_rank_settings][1], f_info[i][f_rank_settings][2], f_info[i][f_rank_settings][3],
			f_info[i][f_rank_settings][4]);

		}
		printf("[SERVER] %d fractions loaded.", fraction_count);
	}
	else print("[SERVER] Fractions were not found in the database.");

	for(new i; i < sizeof(dorm_pos); i ++)
	{
		if(dorm_pos[i][0] + dorm_pos[i][1] + dorm_pos[i][2] != 0.0)
		{
			gdorm_text[i] = CreateDynamic3DTextLabel("Loading...", col_blue, dorm_pos[i][0], dorm_pos[i][1], dorm_pos[i][2] + 1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, f_info[i + 17][f_spawn_virt], f_info[i + 17][f_spawn_int]);
			UpdateGangDormLabel(i + 17);
		}
	}
	return 1;
}

stock save_faction(factionid)
{
	RunQuery("UPDATE `fractions` SET `f_drugs` = '%d', `f_materials` = '%d', `f_guns` = '%d', `f_money` = '%d' WHERE `f_id` = '%d' LIMIT 1", f_info[factionid][f_drugs], f_info[factionid][f_materials], f_info[factionid][f_guns], f_info[factionid][f_money], f_info[factionid][f_id]);
	return 1;
}

cmd:fmute(playerid, params[])
{
 	if(!gang_player(playerid)) return 1;
	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1]) return 1;
	if(sscanf(params, "uds[42]", params[0], params[1], params[2])) return SendInfo(playerid, "Enter: /fmute [id] [Daghighe] [Dalil]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
    if(PlayerInfo[params[0]][member] != PlayerInfo[playerid][member]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Player is not in your organization.");
    if(PlayerInfo[params[0]][rank] >= PlayerInfo[playerid][rank]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey" stva.");
    if(params [1] < 1 || params [1] > 120) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The plug cannot be less than 1 minute or more Only 120 minutes.");


	new scm_string[144];
	format(scm_string,sizeof(scm_string), "%s %s put a gag on player %s at %i min. Reason: %s", f_rank[PlayerInfo[playerid][member]][PlayerInfo[playerid][rank] -1], PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1], params[2]);
	foreach(new i: logged_players) if(PlayerInfo[i][member] == PlayerInfo[playerid][member]) SendClientMessage(i, 0x326EA1FF, scm_string);

	PlayerInfo[params[0]][f_mute] = params [1]*60;
	return 1;
}

cmd:funmute(playerid, params[])
{
 	if(!gang_player(playerid)) return 1;
	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1]) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /funmute [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
    if(PlayerInfo[params[0]][member] != PlayerInfo[playerid][member]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Player is not in your organization.");
    if(PlayerInfo[params[0]][rank] >= PlayerInfo[playerid][rank]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey" stva.");
    if(PlayerInfo[params[0]][f_mute] == 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"У Player has no tags.");


	PlayerInfo[params[0]][f_mute] = 0;
	update_int_sql(params[0], "u_fmute", PlayerInfo[params[0]][f_mute]);

	new scm_string[128];
	format(scm_string, sizeof(scm_string ), "%s %s removed plug for player %s", f_rank[PlayerInfo[playerid][member]][PlayerInfo[playerid][rank] -1], PlayerInfo[playerid][name], PlayerInfo[params[0]][name]);
	foreach(new i: logged_players) if(PlayerInfo[i][member] == PlayerInfo[playerid][member]) SendClientMessage(i, 0x326EA1FF, scm_string);
	return 1;
}

cmd:invite(playerid, params[])
{
	if(!playerFactionStatus(playerid)) return 1;
	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1]) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /invite [id]");
	if(!IsPlayerConnected(params[0])  || params[0] == playerid) return SendError(playerid, "Bazikon Yaft Nashod.");
    if(playerFactionStatus(params[0]) || GetPVarInt(playerid, "frac_invite")) return SendError(playerid, "In bazikon ozv sazman digari ast.");
    if(p_t_info[params[0]][p_dialog] != -1) return SendError(playerid, "In bazikon yek dialog baz dard.");
    if(!IsPlayerInRangeOfPoint(playerid, 5, p_t_info[params[0]][p_pos][0], p_t_info[params[0]][p_pos][1], p_t_info[params[0]][p_pos][2] ) || GetPlayerVirtualWorld(params[0]) != GetPlayerVirtualWorld(playerid)) return SendError(playerid, "Bazikon Kheyli door ast.");
    if(get_player_warn_count(params[0]) != 0) return SendError(playerid, "In bazikon warn dard va nmitavand ozv sazman shavad.");
    if(is_player_fraction_bl(params[0], getPlayerFactionID(playerid)) != 0) return SendError(playerid, "In bazikon dar blacklist ast.");
	
	if(PlayerInfo[params[0]][faction_punish] > 0) return SendError(playerid, "In bazikon faction punish ast.");

	SendMes(playerid, col_gray, "You invited %s to the organization", PlayerInfo[params[0]][name]);

	new scm_string[180];
	format(scm_string, sizeof scm_string, ""c_server"%s "c_white"shoma ra be sazman invite dad "c_grey"\"%s\"", PlayerInfo[playerid][name], f_info[PlayerInfo[playerid][member]][f_name]);
	show_dialog(params[0], d_invite_box, DIALOG_STYLE_MSGBOX, ""c_server"Joining an organization", scm_string, "Enter", "Reject");
	
	SetPVarInt(params[0], "frac_invite", PlayerInfo[playerid][member]);
	SetPVarInt(params[0], "frac_invite_pl_id", playerid + 1);
	return 1;
}

cmd:uninvite(playerid, params[])
{
	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1])
		return 1;
	new punishmentHour;
	
	if(sscanf(params, "uds[48]", params[0], punishmentHour, params[1]))
		return SendInfo(playerid, "Enter: /uninvite [id/name] [punishment hours] [reason]");
	
	if(!IsPlayerConnected(params[0])  || params[0] == playerid)
		return SendError(playerid, "Bazikon Yaft Nashod.");
	
	if(PlayerInfo[params[0]][member] != PlayerInfo[playerid][member])
		return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Not a member of your organization.");
	
	if(PlayerInfo[params[0]][rank] >= PlayerInfo[playerid][rank])
		return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You can't fire your management.");
	
	if(is_text_invalid(params[1]))
		return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Cause contains invalid characters.");
	
	if(!(0 <= punishmentHour <= 24))
		return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Enter punishment hours between 0 to 24.");

	new scm_string[266];

	if(punishmentHour == 1) {
		format(scm_string, 144, "%s fired you from the organization, faction punish: %d hour. Reason: %s", PlayerInfo[playerid][name], punishmentHour, params[1]);
		SendClientMessage(params[0], 0x4682B4AA, scm_string);
		format(scm_string, 144, "You fired %s from the organization, faction punish: %d hour. Reason: %s", PlayerInfo[params[0]][name], punishmentHour, params[1]);
		SendClientMessage(playerid, 0x4682B4AA, scm_string);
	}
	else if(punishmentHour > 1) {
		format(scm_string, 144, "%s fired you from the organization, faction punish: %d hours. Reason: %s", PlayerInfo[playerid][name], punishmentHour, params[1]);
		SendClientMessage(params[0], 0x4682B4AA, scm_string);
		format(scm_string, 144, "You fired %s from the organization, faction punish: %d hours. Reason: %s", PlayerInfo[params[0]][name], punishmentHour, params[1]);
		SendClientMessage(playerid, 0x4682B4AA, scm_string);
	}
	else
	{
		format(scm_string, 128, "%s fired you from the organization. Reason: %s", PlayerInfo[playerid][name], params[1]);
		SendClientMessage(params[0], 0x4682B4AA, scm_string);
		format(scm_string, 128, "You fired %s from the organization. Reason: %s", PlayerInfo[params[0]][name], params[1]);
		SendClientMessage(playerid, 0x4682B4AA, scm_string);
	}

	if(gang_player(playerid))
	{
		format(scm_string, 128, "%s(%d) %s expelled %s(%d) %s from the area. Reason: %s",
		f_rank[PlayerInfo[playerid][member]][PlayerInfo[playerid][rank] -1],
		PlayerInfo[playerid][rank],
		PlayerInfo[playerid][name],

		f_rank[PlayerInfo[params[0]][member]][PlayerInfo[params[0]][rank] -1],
		PlayerInfo[params[0]][rank],
		PlayerInfo[params[0]][name], params[1]);
		foreach(new i: logged_players) if((PlayerInfo[i][member] == PlayerInfo[playerid][member] || is_control_chat {i} == PlayerInfo[playerid][member]) && PlayerInfo[i][settings][0] != 0) SendClientMessage(i, 0x4682B4AA, scm_string);
	}

	addWorkBook(params[0], PlayerInfo[playerid][name], params[1]);

	// ----------------------
	// Top War
	TopWar_HideTopWar(params[0]);
	// ----------------------

	reset_player_weapon(params[0]);

	PlayerInfo[params[0]][faction_punish] = punishmentHour;
	update_int_sql(params[0], "u_faction_punish", PlayerInfo[params[0]][faction_punish]);

	return 1;
}

cmd:fwarn(playerid, params[])
{
 	if(!playerFactionStatus(playerid)) return 1;
	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1]) return 1;
	if(sscanf(params, "us[48]", params[0], params[1])) return SendInfo(playerid, "Enter: /fwarn [id/name] [reason]");
	if(!IsPlayerConnected(params[0])  || params[0] == playerid) return SendError(playerid, "Bazikon Yaft Nashod.");
    if(PlayerInfo[params[0]][member] != PlayerInfo[playerid][member]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Player is not in your organization.");
    if(PlayerInfo[params[0]][rank] >= PlayerInfo[playerid][rank]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey" dstva.");
    if(is_text_invalid(params[1])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The reason contains some characters.");

	PlayerInfo[params[0]][f_warning] ++;
	if(PlayerInfo[params[0]][f_warning] >= 3)
	{
		new scm_string[266];
		format(scm_string, 128, "%s fired you from the organization. Reason: "c_white"%s | 3 reprimand", PlayerInfo[playerid][name], params[1]);
		SendClientMessage(params[0], col_wavy, scm_string);

		addWorkBook(params[0], PlayerInfo[playerid][name], "3/3 Warn");

		// ----------------------
		// Top War
		TopWar_HideTopWar(params[0]);
		// ----------------------
	}
	update_int_sql(params[0], "u_f_warning", PlayerInfo[params[0]][f_warning]);
	new scm_string[128];
	format(scm_string, sizeof scm_string, "You issued a %s pronunciation(%d/3). Reason: "c_white"%s", PlayerInfo[params[0]][name], PlayerInfo[params[0]][f_warning], params[1]);
	SendClientMessage(playerid, col_wavy, scm_string);

	format(scm_string, sizeof scm_string, "%s gave you a reprimand(%d/3). Reason: "c_white"%s", PlayerInfo[playerid][name], PlayerInfo[params[0]][f_warning], params[1]);
	SendClientMessage(params[0], col_wavy, scm_string);

    return 1;
}


cmd:unfwarn(playerid, params[])
{
 	if(!playerFactionStatus(playerid)) return 1;
 	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1]) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /unfwarn [id/name]");
	if(!IsPlayerConnected(params[0])  || params[0] == playerid) return SendError(playerid, "Bazikon Yaft Nashod.");
    if(PlayerInfo[params[0]][member] != PlayerInfo[playerid][member]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Player is not in your organization.");
    if(PlayerInfo[params[0]][rank] >= PlayerInfo[playerid][rank]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey" odstvo.");
	if(PlayerInfo[params[0]][f_warning] == 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The player has no reprimands.");


	PlayerInfo[params[0]][f_warning] --;
	update_int_sql(params[0], "u_f_warning", PlayerInfo[params[0]][f_warning]);
	new scm_string[128];
	format(scm_string, sizeof scm_string, "You %s reprimanded(%d/3).", PlayerInfo[params[0]][name], PlayerInfo[params[0]][f_warning]);
	SendClientMessage(playerid, col_wavy, scm_string);

	format(scm_string, sizeof scm_string, "%s You %s reprimanded(%d/3).", PlayerInfo[playerid][name], PlayerInfo[params[0]][f_warning]);
	SendClientMessage(params[0], col_wavy, scm_string);

    return 1;
}

cmd:setskin(playerid, params[])
{
	if(!playerFactionStatus(playerid)) return 1;
	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1]) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /setskin [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(PlayerInfo[params[0]][member] != PlayerInfo[playerid][member]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"I am not a member of your organization.");
    if(!IsPlayerInRangeOfPoint(playerid, 5, p_t_info[params[0]][p_pos][0], p_t_info[params[0]][p_pos][1], p_t_info[params[0]][p_pos][2]) || GetPlayerVirtualWorld(params[0]) != GetPlayerVirtualWorld(playerid)) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Bazikon Kheyli door ast.");

	new dialog_string[max_rank * 6],
		frac_id = PlayerInfo[playerid][member];
	for(new j = 0; j < max_rank; j ++)
	{
		if(f_skin[frac_id -1][PlayerInfo[params[0]][gender]][j] == 1) break;
		new line_string[7];
		format(line_string, 7, "%d\n", f_skin[frac_id -1][PlayerInfo[params[0]][gender]][j]);
		strcat(dialog_string, line_string);
	}
	SetPVarInt(playerid, "frac_invite_sk_id", params[0] + 1);

	show_dialog(playerid, d_set_fskin, DIALOG_STYLE_LIST, ""c_server"Choice of clothes", dialog_string, "Change", "Cancel");
	return 1;
}

cmd:setrank(playerid)
{
	if(check_admin_rank(playerid , 8)) return 1;

	if(!playerLeaderStatus(playerid)) return 1;
	if(!gang_player(playerid) && ! mafia_player(playerid)) return 1;
	global_string[0] = EOS;
	for(new i = 0; i < f_info[PlayerInfo[playerid][member]][f_rank_settings][0]; i ++)
	{
		new line_string[72];
		format(line_string, 72, ""c_grey"%i. "c_white"%s\n", i + 1, f_rank[PlayerInfo[playerid][member]][i]);
		strcat(global_string, line_string);
	}
	show_dialog(playerid, d_lmenu_rankname_list, DIALOG_STYLE_LIST, ""c_server"Change of name rank", global_string, "Next", "Bastan");
	return 1;
}

stock getPlayerFactionID(playerid)
{
	if(playerFactionStatus(playerid)) return f_info[PlayerInfo[playerid][member]][f_id];
	else return 0;
}

stock getLeaderFactionID(playerid)
{
	if(playerLeaderStatus(playerid)) return f_info[PlayerInfo[playerid][leader]][f_id];
	else return 0;
}

stock playerFactionStatus(playerid)
{
	if(PlayerInfo[playerid][member] != -1) return 1;
	else return 0;
}

stock playerLeaderStatus(playerid)
{
	if(PlayerInfo[playerid][leader] != -1) return 1;
	else return 0;
}

stock getJobFactionID(playerid)
{
	if(playerJobStatus(playerid)) return f_info[PlayerInfo[playerid][job]][f_id];
	else return 0;
}

stock getTimeJobFactionID(playerid)
{
	if(playerTimeJobStatus(playerid)) return f_info[PlayerInfo[playerid][timejob]][f_id];
	else return 0;
}

stock playerTimeJobStatus(playerid)
{
	if(PlayerInfo[playerid][timejob] != -1) return 1;
	else return 0;
}

stock playerJobStatus(playerid)
{
	if(PlayerInfo[playerid][job] != -1) return 1;
	else return 0;
}

stock getFactionID(factionId)
{
	for (new i = 0; i < fraction_count; i++)
	{
		if(f_info[i][f_id] == factionId)
		{
			return i;
		}
		
	}
	
	return -1;
}

stock getFactionDBID(factionID)
{
	return f_info[factionID][f_id];
}