stock is_player_family_bl(playerid, familyid)
{
    new _bl_count = 0, query_string[125];
    format(query_string, sizeof(query_string), "SELECT `bl_player`,`bl_family` FROM `family_blacklist` WHERE `bl_player`='%d' AND `bl_family`='%d' LIMIT 1", PlayerInfo[playerid][id], familyid);
    new Cache:result = mysql_query(sql_connection, query_string);
    _bl_count = cache_num_rows();
    cache_delete(result);
    return _bl_count;
}

stock find_last_family()
{
    new _fam_count = 0, _fam_id = 0;
    new Cache:result = mysql_query(sql_connection, "SELECT `fam_id` FROM `family` ORDER BY `family`.`fam_id` DESC LIMIT 1");
    _fam_count = cache_num_rows();
    if(_fam_count) _fam_id = cache_get_field_content_int(0, "fam_id", sql_connection);
    cache_delete(result);
    return _fam_id;
}

stock find_family_name(family_name[])
{
    new _fam_count = 0, query_string[120];
    format(query_string, sizeof(query_string), "SELECT `fam_name` FROM `family` WHERE `fam_name`='%s' AND LIMIT 1", family_name);
    new Cache:result = mysql_query(sql_connection, query_string);
    _fam_count = cache_num_rows();
    cache_delete(result);
    return _fam_count;
}

stock getPlayerFamilyID(playerid)
{
	if(PlayerInfo[playerid][family] != -1) return family_info[PlayerInfo[playerid][family]][fam_id];
	else return 0;
}

stock familyHouseStatus(family_id)
{
	if(family_info[family_id][fam_house] != -1) return 1;
	else return 0;
}

stock getFamilyID(familyid)
{
	for (new i = 0; i < family_count; i++)
	{
		if(family_info[i][fam_id] == familyid)
		{
			return i;
		}
		
	}
	
	return -1;
}

stock playerFamilyStatus(playerid)
{
	if(PlayerInfo[playerid][family] != -1) return 1;
	else return 0;
}

stock family_message(family_stk, color, text[])
{
    foreach(new i: logged_players)
    {
        if(PlayerInfo[i][family] != family_stk) continue;
        SendClientMessage(i, color, text);
    }
    return 1;
}

stock UpdateFamilyLabel(family_id)
{
	foreach(new vehicleid: family_vehicles[family_id])
	{
		new text_string[95];
		format(text_string, sizeof(text_string), "{%s}%s", family_info[family_id][fam_chat_color], family_info[family_id][fam_name]);
		UpdateDynamic3DTextLabelText(veh_info[vehicleid -1][v_label_family], -1, text_string);
	}

	return 1;
}

cmd:fmenu(playerid)
{
	if(!playerFamilyStatus(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Shoma dar family nistid.");

	dlobal_string[0] = EOS;

	strcat(dlobal_string, ""c_server"1 | "c_white"Moshakhasat Family\n");
	strcat(dlobal_string, ""c_server"2 | "c_white"Family members ["c_green"online"c_white"]\n");
	strcat(dlobal_string, ""c_server"3 | "c_white"Family members ["c_orange_red"offline"c_white"]\n");
	strcat(dlobal_string, ""c_server"4 | "c_white"Family "c_gold"[VIP]\n");
	strcat(dlobal_string, ""c_server"5 | "c_white"Tanzimat Family\n");
	strcat(dlobal_string, ""c_server"6 | "c_white"Black List\n");
	strcat(dlobal_string, ""c_server"7 | "c_white"Modiriat Vehicle\n");
	strcat(dlobal_string, ""c_server"8 | "c_white"Sabeghe Family\n");
	strcat(dlobal_string, ""c_server"9 | "c_white"Enteghal Family\n");
	strcat(dlobal_string, ""c_server"10 | "c_white"Kharid Slot Car Family\n");

	strcat(dlobal_string, ""c_grey"Khoroj az Family\n");

	return show_dialog(playerid, d_family, DIALOG_STYLE_LIST, !""scm_dialog"Modiriat Family", dlobal_string, !"Entekhab", !"Bastan");
}

cmd:fam(playerid, params[])
{
    if(!playerFamilyStatus(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Shoma dar family nistid.");
    if(PlayerInfo[playerid][mute]) return SendClientMessage(playerid, col_white, !""scm_error"Dastrasi be chat masdod shode ast. zaman baz kardan gofhl: "c_server"/time");
    if(PlayerInfo[playerid][fam_mute])
    {
        new text_string[80];
        format(text_string, sizeof(text_string), ""scm_error"Dastrasi shoma be radio family masdod shod ast | %s", convert_time(PlayerInfo[playerid][fam_mute]));
        SendClientMessage(playerid, col_white, text_string);
        return 0;
    }
    extract params -> new string:fam_text[128]; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /fam [matn]");
    if(CheckForAdvTexts(playerid, fam_text)) return 1;

    new text_string[144];
    format(text_string, sizeof(text_string), "{%s}[Family] %s %s[%d]: "c_silver"%s", family_info[PlayerInfo[playerid][family]][fam_chat_color], family_rank[PlayerInfo[playerid][family]][PlayerInfo[playerid][family_rang] -1], PlayerInfo[playerid][name], playerid, params[0]);
    family_message(PlayerInfo[playerid][family], col_white, text_string);
    return 1;
}

cmd:fammute(playerid, params[])
{
    if(!playerFamilyStatus(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Shoma dar family nistid.");
    if(PlayerInfo[playerid][family_rang] < family_info[PlayerInfo[playerid][family]][fam_settings][5])
    {
        new text_string[100];
        format(text_string, sizeof(text_string), ""scm_error"Team available from status %s (%d)", family_rank[PlayerInfo[playerid][family]][family_info[PlayerInfo[playerid][family]][fam_settings][5] -1], family_info[PlayerInfo[playerid][family]][fam_settings][5]);
        return SendClientMessage(playerid, col_white, text_string);
    }
    extract params -> new player:targetid, fam_mutes, string:fam_reason[64]; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /fammute [id Bazikon] [Daghighe] [Dalil]");
    if(!IsPlayerConnected(targetid) || targetid == playerid) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");
    if(PlayerInfo[targetid][family] != PlayerInfo[playerid][family]) return SendClientMessage(playerid, col_white, !""scm_error"I am not a member of your family.");
    if(PlayerInfo[targetid][family_rang] >= PlayerInfo[playerid][family_rang]) return SendClientMessage(playerid, col_white, !""scm_error" leadership.");
    if(fam_mutes < 1 || fam_mutes > 120) return SendClientMessage(playerid, col_white, !""scm_info"Radio lock cannot be less than 1 minute or more more than 120 minutes.");
    new family_id = PlayerInfo[playerid][family];

    new text_string[125];
    format(text_string, sizeof(text_string),"{%s}[Family]"c_silver" %s %s blocked rate %s for %d min. Reason: %s", family_info[family_id][fam_chat_color], family_rank[family_id][PlayerInfo[playerid][family_rang] -1], PlayerInfo[playerid][name], PlayerInfo[targetid][name], fam_mutes, fam_reason);
    family_message(family_id, col_white, text_string);

    format(text_string, sizeof(text_string), "%s blocked rate %s for %d min. Reason: %s", PlayerInfo[playerid][name], PlayerInfo[targetid][name], fam_mutes, fam_reason);
    write_family(playerid, family_id, TYPE_LOG_WARN, text_string);

    PlayerInfo[targetid][fam_mute] = fam_mutes * 60;
    return 1;
}

cmd:famunmute(playerid, params[])
{
    if(!playerFamilyStatus(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Shoma dar family nistid.");
    if(PlayerInfo[playerid][family_rang] < family_info[PlayerInfo[playerid][family]][fam_settings][5])
    {
        new text_string[100];
        format(text_string, sizeof(text_string), ""scm_error"Team available from status %s (%d)", family_rank[PlayerInfo[playerid][family]][family_info[PlayerInfo[playerid][family]][fam_settings][5] -1], family_info[PlayerInfo[playerid][family]][fam_settings][5]);
        return SendClientMessage(playerid, col_white, text_string);
    }
    extract params -> new player:targetid; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /famunmute [id Bazikon]");
    if(!IsPlayerConnected(targetid) || targetid == playerid) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");
    if(PlayerInfo[targetid][family] != PlayerInfo[playerid][family]) return SendClientMessage(playerid, col_white, !""scm_error"I am not a member of your family.");
    if(PlayerInfo[targetid][family_rang] >= PlayerInfo[playerid][family_rang]) return SendClientMessage(playerid, col_white, !""scm_info" leadership.");
    if(PlayerInfo[targetid][fam_mute] == 0) return SendClientMessage(playerid, col_white, !""scm_error"The player is not blocked from accessing the radio.");

    PlayerInfo[targetid][fam_mute] = 0;
    update_int_sql(targetid, "u_family_mute", PlayerInfo[targetid][fam_mute]);

    new family_id = PlayerInfo[playerid][family];

    new text_string[125];
    format(text_string, sizeof(text_string), "{%s}[Family]"c_silver" %s %s unlocked the radio %s", family_info[family_id][fam_chat_color], family_rank[family_id][PlayerInfo[playerid][family_rang] -1], PlayerInfo[playerid][name], PlayerInfo[targetid][name]);
    family_message(family_id, col_white, text_string);

    format(text_string, sizeof(text_string), "%s unlocked the radio %s", PlayerInfo[playerid][name], PlayerInfo[targetid][name]);
    write_family(playerid, family_id, TYPE_LOG_WARN, text_string);
    return 1;
}

cmd:faminvite(playerid, params[])
{
	if(!playerFamilyStatus(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Shoma dar family nistid.");
	if(PlayerInfo[playerid][family_rang] < family_info[PlayerInfo[playerid][family]][fam_settings][0])
	{
		new text_string[100];
		format(text_string, sizeof(text_string), ""scm_error"Team available from status %s (%d).", family_rank[PlayerInfo[playerid][family]][family_info[PlayerInfo[playerid][family]][fam_settings][0] -1], family_info[PlayerInfo[playerid][family]][fam_settings][0]);
		return SendClientMessage(playerid, col_white, text_string);
	}
	extract params -> new player:targetid; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /faminvite [id Bazikon]");
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");
	if(!IsPlayerInRangeOfPoint(playerid, 5, p_t_info[targetid][p_pos][0], p_t_info[targetid][p_pos][1], p_t_info[targetid][p_pos][2]) || GetPlayerVirtualWorld(targetid) != GetPlayerVirtualWorld(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Kheyli door ast.");
	if(p_t_info[targetid][p_dialog] != -1) return SendClientMessage(playerid, col_white, !""scm_error"The player already has a dialogue open.");
    if(PlayerInfo[targetid][family] > 0) return SendClientMessage(playerid, col_white, "Player is already in the family.");
	if(is_player_family_bl(targetid, PlayerInfo[playerid][family])!= 0) return SendClientMessage(playerid, col_white, !""scm_error"You cannot adopt a player from the black list of the family.");
	
	if(family_info[PlayerInfo[playerid][family]][fam_members] >= MAX_SLOT_FAMILY_MEMBERS && family_info[PlayerInfo[playerid][family]][fam_vip] == 0) return SendError(playerid, "Family shoma pour ast va ja baraye ozv jadid nadard. (15/15)");

	new text_string[144];
	format(text_string, sizeof(text_string), ""scm_info"You suggested "c_server"%s"c_white" to join the family %s", PlayerInfo[targetid][name], family_info[PlayerInfo[playerid][family]][fam_name]);
	SendClientMessage(playerid, col_white, text_string);

	format(text_string, sizeof(text_string), ""c_server"%s"c_white" invites you to join the %s family.\n\n"c_grey"You agree to join?", PlayerInfo[playerid][name], family_info[PlayerInfo[playerid][family]][fam_name]);
	show_dialog(targetid, d_family_invite, DIALOG_STYLE_MSGBOX, !""scm_dialog"Bringing into the familyю", text_string, !"Join", !"Cancel");

	SetPVarInt(targetid, !"family_id", PlayerInfo[playerid][family]);
	SetPVarInt(targetid, !"family_player", playerid);
	return 1;
}

cmd:famuninvite(playerid, params[])
{
	if(!playerFamilyStatus(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Shoma dar family nistid.");
	if(PlayerInfo[playerid][family_rang] < family_info[PlayerInfo[playerid][family]][fam_settings][1])
	{
		new text_string[100];
		format(text_string, sizeof(text_string), ""scm_error"Team available from status %s (%d)", family_rank[PlayerInfo[playerid][family]][family_info[PlayerInfo[playerid][family]][fam_settings][1] -1], family_info[PlayerInfo[playerid][family]][fam_settings][1]);
		return SendClientMessage(playerid, col_white, text_string);
	}
	extract params -> new player:targetid, string:reason[64]; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /famuninvite [id Bazikon] [reason]");
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");
	if(PlayerInfo[targetid][family] != PlayerInfo[playerid][family]) return SendClientMessage(playerid, col_white, !""scm_error"You are not a member of your family.");
	if(PlayerInfo[targetid][family_rang] >= family_info[PlayerInfo[playerid][family]][fam_settings][3]) return SendClientMessage(playerid, col_white, !""scm_error"You can't kick out the creator of the family.");

	new family_id = PlayerInfo[playerid][family], text_string[144];
	format(text_string, sizeof(text_string), ""scm_info"You have removed "c_server"%s"c_white" from the %s family. Reason: %s", PlayerInfo[targetid][name], family_info[PlayerInfo[playerid][family]][fam_name], reason);
	SendClientMessage(playerid, col_white, text_string);

	format(text_string, sizeof(text_string), "{%s}[Family] %s %s[%d] kicked %s[%d] out of the family. Reason: %s", family_info[family_id][fam_chat_color], family_rank[family_id][PlayerInfo[playerid][family_rang] -1], PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid, reason);
	family_message(family_id, col_white, text_string);

	Iter_Remove(family_players[family_id], targetid);
	PlayerInfo[targetid][family] = PlayerInfo[targetid][family_rang] = 0;

	if(PlayerInfo[targetid][family_text] != Text3D:INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(PlayerInfo[targetid][family_text]);
		PlayerInfo[targetid][family_text] = Text3D:INVALID_3DTEXT_ID;
	}

	new query_string[120];
	format(query_string, sizeof(query_string), "UPDATE `users` SET `u_family`='-1',`u_family_rank`='0' WHERE `u_id`='%d' LIMIT 1", PlayerInfo[targetid][id]);
	mysql_query(sql_connection, query_string);

	family_info[family_id][fam_members] --;

	format(query_string, sizeof(query_string), "UPDATE `family` SET `fam_members`='%d' WHERE `fam_id`='%d' LIMIT 1", family_info[family_id][fam_members], getPlayerFamilyID(playerid));
	mysql_query(sql_connection, query_string);

	format(query_string, sizeof(query_string), "%s kicked out of the family %s", PlayerInfo[playerid][name], PlayerInfo[targetid][name]);
	write_family(playerid, family_id, TYPE_LOG_UVAL, query_string);
	return 1;
}

cmd:famrank(playerid, params[])
{
    if(PlyayerIsGang && !PlayerInfo[playerid][family]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma dar family nistid.");
    if(PlayerInfo[playerid][family_rang] < family_info[PlayerInfo[playerid][family]][fam_settings][2])
    {
        new text_string[100];
        format(text_string, sizeof(text_string), ""scm_error"Team available from status %s (%d).", family_rank[PlayerInfo[playerid][family]][family_info[PlayerInfo[playerid][family]][fam_settings][2] -1], family_info[PlayerInfo[playerid][family]][fam_settings][2]);
        return SendClientMessage(playerid, col_white, text_string);
    }
    extract params -> new player:targetid; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /famrank [id Bazikon]");
    if(!IsPlayerConnected(targetid) || targetid == playerid) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");
    if(PlayerInfo[targetid][family] != PlayerInfo[playerid][family]) return SendClientMessage(playerid, col_white, !""scm_error"You are not a member of your family.");
    if(PlayerInfo[targetid][family_rang] >= family_info[PlayerInfo[playerid][family]][fam_settings][3]) return SendClientMessage(playerid, col_white, !""scm_error"You cannot change the role of the creator of the family.");

    dlobal_string[0] = EOS;
    for(new i = 0; i < family_info[PlayerInfo[playerid][family]][fam_settings][3]; i ++)
    {
        new text_string[80];
        format(text_string, sizeof(text_string), ""c_server"%d | "c_white"%s\n", i + 1, family_rank[PlayerInfo[playerid][family]][i]);
        strcat(dlobal_string, text_string);
    }
    show_dialog(playerid, d_family_rank, DIALOG_STYLE_LIST, !""scm_dialog"Family status", dlobal_string, !"Entekhab", !"Barghast");
    return SetPVarInt(playerid, !"pl_setrank_id", targetid);
}

callback: family_loading()
{
    new fields;
    cache_get_data(family_count, fields);

	if(family_count)
	{
		for(new f = 0; f < family_count; f++)
		{
			family_info[f][fam_id] = cache_get_field_content_int(f, "fam_id", sql_connection);
			family_info[f][fam_type] = cache_get_field_content_int(f, "fam_type", sql_connection);

			cache_get_field_content(f, "fam_name", family_info[f][fam_name], sql_connection, 68);
			cache_get_field_content(f, "fam_creator", family_info[f][fam_creator], sql_connection, MAX_PLAYER_NAME);

			family_info[f][fam_nationality] = cache_get_field_content_int(f, "fam_nationality", sql_connection);
			cache_get_field_content(f, "fam_chat_color", family_info[f][fam_chat_color], sql_connection, 8);

			new sscanf_string[380];
			cache_get_field_content(f, "fam_settings", sscanf_string, sql_connection, 80), sscanf(sscanf_string, "p<|>ddddddddd", family_info[f][fam_settings][0], family_info[f][fam_settings][1], family_info[f][fam_settings][2], family_info[f][fam_settings][3], family_info[f][fam_settings][4], family_info[f][fam_settings][5], family_info[f][fam_settings][6], family_info[f][fam_settings][7], family_info[f][fam_settings][8]);
			cache_get_field_content(f, "fam_ranks", sscanf_string, sql_connection, 700), sscanf(sscanf_string, "p<|>s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]s[30]", family_rank[f][0], family_rank[f][1], family_rank[f][2], family_rank[f][3], family_rank[f][4], family_rank[f][5], family_rank[f][6], family_rank[f][7], family_rank[f][8], family_rank[f][9], family_rank[f][10], family_rank[f][11], family_rank[f][12], family_rank[f][13], family_rank[f][14], family_rank[f][15], family_rank[f][16], family_rank[f][17], family_rank[f][18], family_rank[f][19]);

			family_info[f][fam_bank] = cache_get_field_content_int(f, "fam_bank", sql_connection);
			family_info[f][fam_house] = cache_get_field_content_int(f, "fam_house", sql_connection);

			family_info[f][fam_vip] = cache_get_field_content_int(f, "fam_vip", sql_connection);

			if(familyHouseStatus(f))
			{
				for(new h = 0; h < house_count; h ++)
				{
					if(h_info[h][h_id] == family_info[f][fam_house])
					{
						family_info[f][fam_house] = h;
						break;
					}
				}
			}

			family_info[f][fam_members] = cache_get_field_content_int(f, "fam_members", sql_connection);
			family_info[f][fam_rating] = cache_get_field_content_int(f, "fam_rating", sql_connection);
			family_info[f][fam_ticket] = cache_get_field_content_int(f, "fam_ticket", sql_connection);
			family_info[f][fam_max_car] = cache_get_field_content_int(f, "fam_max_car", sql_connection);
		}
	}
	for(new i = 0; i < family_count; i ++)
	{
		new query_string[144];
		format(query_string, sizeof(query_string), "SELECT `u_family` FROM `users` WHERE `u_family`='%d'", i + 1);
		new Cache:_result = mysql_query(sql_connection, query_string);
		new count_members = cache_num_rows();
		cache_delete(_result);

		family_info[i][fam_members] = count_members;

		format(query_string, sizeof(query_string), "UPDATE `family` SET `fam_members`='%d' WHERE `fam_id`='%d' LIMIT 1", family_info[i][fam_members], family_info[i][fam_id]);
		mysql_query(sql_connection, query_string);
	}

	load_family_houses();

	return printf("[SERVER] Total family loaded: %d", family_count);
}

callback: callback_familylist(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	
    if(!rows)
    {
        SendClientMessage(playerid, col_white, !""scm_error"Not 1 family found in the archive.");
        show_dialog(playerid, d_family_hall, DIALOG_STYLE_LIST, !""scm_dialog"Family Archive", !"Create Family\nRename Family\nFamily List", !"Entekhab", !"Bastan");
        return DeletePVar(playerid, !"ofm_list_page");
    }
    new rows_list = GetPVarInt(playerid, !"ofm_list_page") -1;
    SetPVarInt(playerid, !"ofm_list_rows", rows);

    new pl_f_name[68], pl_f_color[68];

    dlobal_string[0] = EOS;
    for(new i = rows_list * 10; i < rows_list * 10 + 10; i++)
    {
        if(i >= rows) break;
        
        cache_get_field_content(i, "fam_name", pl_f_name, sql_connection, 68);
        cache_get_field_content(i, "fam_chat_color", pl_f_color, sql_connection, 8);

        new line_string[80];
        format(line_string, sizeof(line_string), ""c_server"%d | "c_white"%s\n", i + 1, pl_f_name);
        strcat(dlobal_string, line_string);
    }
    return show_dialog(playerid, d_family_list, DIALOG_STYLE_MSGBOX, !""scm_dialog"Family Archive", dlobal_string, !"Barghast", !"Next");
}

stock load_family_houses()
{
	for(new i = 0; i < house_count; i++)
	{
		for(new ix = 0; ix < family_count; ix++)
		{
			if(family_info[ix][fam_id] == h_info[i][h_family]) 
			{
				h_info[i][h_family] = ix;
				UpdateHouseEnterLabel(i);
				break;
			}
		}
	}
}

stock show_create_family(playerid)
{
	if(PlayerInfo[playerid][level] < 7) return SendError(playerid, "Baraye sakht Family be Level 7 niyaz darid.");
	show_dialog(playerid, d_family_create, DIALOG_STYLE_INPUT, !""scm_dialog"Sakht Family", !""c_white"Gheymat Sakht Family: {FFDC33}500 M-Coin\n"c_white"Esm family ra vared konid:", !"Next", !"Bargasht");
	return 1;
}

stock show_settings_family(playerid, family_id, select_id)
{
    global_string[0] = EOS;
    for(new i = 0; i < family_info[family_id][fam_settings][8]; i++)
    {
        new line_string[60];
        format(line_string, sizeof(line_string), ""c_server"%d | "c_white"%s\n", i + 1, family_rank[family_id][i]);
        strcat(global_string, line_string);
    }

    if(select_id == 0) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"Admission to the family", global_string, !"Entekhab", !"Barghast");
    else if(select_id == 1) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"Exclusion from the family", global_string, !"Entekhab", !"Barghast");
    else if(select_id == 2) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"Status change", global_string, !"Entekhab", !"Barghast");
    else if(select_id == 3) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"History list", global_string, !"Entekhab", !"Barghast");
    else if(select_id == 4) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"Black list", global_string, !"Entekhab", !"Barghast");
    else if(select_id == 5) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"Access to /fam(unmute", global_string, !"Entekhab", !"Barghast");
    else if(select_id == 6) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"Access to /famlock", global_string, !"Entekhab", !"Barghast");
    else if(select_id == 7) show_dialog(playerid, d_family_settings_select, DIALOG_STYLE_LIST, !""scm_dialog"Access to the public", global_string, !"Entekhab", !"Barghast");
    return SetPVarInt(playerid, !"select_id", select_id);
}

stock family_logs(playerid)
{
    return show_dialog(playerid, d_family_logs, DIALOG_STYLE_LIST, !""scm_dialog"Family History", !""c_server"1."c_white" Rank history\n"c_server"2."c_white" Verdict history\n"c_server"3."c_white" Blacklist\n"c_server"4."c_white" History of acceptance\n"c_server"5."c_white" Layoff history\n"c_server"6."c_white" Warehouse history", !"Entekhab", !"Barghast");
}

stock family_settings(playerid)
{
	global_string[0] = EOS;

    new f = PlayerInfo[playerid][family], line_string[105];
    format(line_string, sizeof(line_string), ""c_server"1 | "c_white"Admission to the family - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][0]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"2 | "c_white"Exclusion from the family - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][1]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"3 | "c_white"Status change - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][2]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"4 | "c_white"History list - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][3]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"5 | "c_white"Black list - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][4]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"6 | "c_white"Access to /fam(un)mute - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][5]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"7 | "c_white"Access to /famlock - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][6]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"8 | "c_white"Access to the public - "c_server"%s\n", family_rank[f][(family_info[f][fam_settings][7]) -1]);
    strcat(global_string, line_string);
    format(line_string, sizeof(line_string), ""c_server"9 | "c_white"Number of statuses - "c_server"%d\n", family_info[f][fam_settings][8]);
    strcat(global_string, line_string);

    strcat(global_string, ""c_server"9 | "c_white"Title statuses\n");
    strcat(global_string, ""c_server"10 | "c_white"Set family nationality\n");
    strcat(global_string, ""c_server"11 | "c_white"Family chat settings");

    return show_dialog(playerid, d_family_settings, DIALOG_STYLE_LIST, !""scm_dialog"Family Settings", global_string, !"Entekhab", !"Barghast");
}

stock family_sql(familyid)
{
    new query_string[100];
    format(query_string, sizeof(query_string), "UPDATE `family` SET `fam_settings`='%d|%d|%d|%d|%d|%d|%d|%d|%d' WHERE `fam_id`='%d' LIMIT 1", family_info[familyid][fam_settings][0], family_info[familyid][fam_settings][1], family_info[familyid][fam_settings][2], family_info[familyid][fam_settings][3], family_info[familyid][fam_settings][4], family_info[familyid][fam_settings][5], family_info[familyid][fam_settings][6], family_info[familyid][fam_settings][7], family_info[familyid][fam_settings][8], family_info[familyid][fam_id]);
    mysql_query(sql_connection, query_string);
    return 1;
}

stock write_family(playerid, fam, type, text[])
{
    slobal_string[0] = EOS;
    format(slobal_string, sizeof(slobal_string), "INSERT INTO `logs_family` (`name`,`family`,`type`,`Text`,`text_date`) VALUES ('%s','%d','%d','%s', NOW())", PlayerInfo[playerid][name], fam, type, text);
    mysql_query(sql_connection, slobal_string);
    return 1;
}

callback: callback_offamily(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows)
	{
		SendClientMessage(playerid, col_white, !""scm_error"No players with these parameters found.");
		DeletePVar(playerid, !"ofm_list_page");
		return pc_cmd_fmenu(playerid);
	}

	new rows_list = GetPVarInt(playerid, !"ofm_list_page") -1;
	SetPVarInt(playerid, !"ofm_list_rows", rows);

	global_string[0] = EOS;
	strcat(global_string, ""c_grey"Previous page\n"c_grey"Next page\n"c_white"");
	for(new i = rows_list * 10; i < rows_list * 10 + 10; i ++)
	{
		if(i >= rows) break;

		new pl_ofm_name[24], pl_ofm_online[24], fam_c_rank;
		
		
		cache_get_field_content(i, "u_name", pl_ofm_name, sql_connection, 24);
		cache_get_field_content(i, "u_last_date", pl_ofm_online, sql_connection, 24);
		fam_c_rank = cache_get_field_content_int(i, "u_family_rank", sql_connection);

		new pvar_string[8];
		format(pvar_string, sizeof(pvar_string), "ofm_%d", i -rows_list * 10);
		SetPVarString(playerid, pvar_string, pl_ofm_name);

		new _pl_id;
		sscanf(pl_ofm_name, "u", _pl_id);

		new line_string[120];
		format(line_string, sizeof(line_string), "%s - %s (%d) - %s (%s)\n", pl_ofm_name, family_rank[PlayerInfo[playerid][family]][fam_c_rank -1], fam_c_rank, pl_ofm_online, (IsPlayerConnected(_pl_id)) ? (""c_green"online") : (""c_orange_red"offline"));
		strcat(global_string, line_string);
	}
	return show_dialog(playerid, d_offamily_list, DIALOG_STYLE_LIST, !""scm_dialog"Family members ["c_orange_red"offline"c_white"]", global_string, !"Entekhab", !"Barghast");
}

callback: callback_offamily_info(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(rows)
	{
	
		new last_date[16], fraction_date[24], fam_c_rank;
		fam_c_rank = cache_get_field_content_int(0, "u_family_rank", sql_connection);
		cache_get_field_content(0, "u_last_date", last_date, sql_connection, 24);
		cache_get_field_content(0, "u_family_date", fraction_date, sql_connection, 24);

		new pvar_string[38], pl_name[MAX_PLAYER_NAME];
		format(pvar_string, sizeof(pvar_string), "ofm_%d", GetPVarInt(playerid, !"ofm_listitem"));
		GetPVarString(playerid, pvar_string, pl_name, MAX_PLAYER_NAME);

		new dialog_string[256];
		format(dialog_string, sizeof(dialog_string), ""c_white"Name: "c_server"%s\n"c_white"Status: "c_server"%s (%d)\n"c_white"Date of membership: "c_grey"%s\n"c_white"Last login: "c_grey"%s", pl_name, family_rank[PlayerInfo[playerid][family]][fam_c_rank -1], fam_c_rank, fraction_date, last_date);
		show_dialog(playerid, d_offamily_pl_menu_info, DIALOG_STYLE_MSGBOX, !""scm_dialog"Player Information", dialog_string, !"Barghast", !"");
	}
	if(!rows)
	{
		DeletePVar(playerid, !"ofm_listitem");
		if(!GetPVarInt(playerid, !"ofm_type"))
		{
			new query_string[100];
			mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT `u_name`,`u_last_date`,`u_family_rank` FROM `users` WHERE `u_family`='%d'", PlayerInfo[playerid][family]);
			mysql_tquery(sql_connection, query_string, "callback_offamily", "i", playerid);
			return 1;
		}
	}
	return 1;
}

callback: logs_player_family(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	new t_name[32], t_date[48], t_id;
	if(!rows)
	{
		DeletePVar(playerid, !"ofm_list_page");
		return SendClientMessage(playerid, col_white, !""scm_error"No active logs found.");
	}

	SetPVarInt(playerid, !"ofm_list_rows", rows);
	new rows_list = GetPVarInt(playerid, !"ofm_list_page") -1;

	global_string[0] = EOS;
	strcat(global_string, ""c_grey"Previous page\n"c_grey"Next page\n"c_white"");
	for(new i = rows_list * 10; i < rows_list * 10 + 10; i ++)
	{
		if(i >= rows) break;

		t_id = cache_get_field_content_int(i, "id", sql_connection);
		cache_get_field_content(i, "name", t_name, sql_connection, 32);
		cache_get_field_content(i, "text_date", t_date, sql_connection, 48);

		new pvar_string[16];
		format(pvar_string, sizeof(pvar_string), "vrl_%d", i -rows_list * 10);
		SetPVarInt(playerid, pvar_string, t_id);

		new line_string[128];
		format(line_string, sizeof(line_string), ""c_server"%d | "c_white"%s "c_grey"(%s)\n", i + 1, t_name, t_date);
		strcat(global_string, line_string);
	}
	return show_dialog(playerid, d_offamily_lognext, DIALOG_STYLE_LIST, !""scm_dialog"Family history", global_string, !"Entekhab", !"Bastan");
}

callback: logs_player_family_info(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows)
	{
		DeletePVar(playerid, !"ofm_list_page");
		return pc_cmd_fmenu(playerid);
	}


	new t_name[32], t_date[48], t_text[128];
	cache_get_field_content(0, "name", t_name, sql_connection, 32);
	cache_get_field_content(0, "text_date", t_date, sql_connection, 48);
	cache_get_field_content(0, "Text", t_text, sql_connection, 128);

	new logs_dialog[512];
	format(logs_dialog, sizeof(logs_dialog), ""c_white"Character nickname: "c_gold"%s\n"c_white"Date: "c_silver"%s\n\n"c_white"Action: "c_silver"%s", t_name, t_date, t_text);
	return show_dialog(playerid, d_offamily_logback, DIALOG_STYLE_MSGBOX, !""scm_dialog"Family history", logs_dialog, !"Barghast", !"Bastan");
}

callback: get_family_logs(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	new t_name[32], t_date[48], t_id;
	if(!rows)
	{
		DeletePVar(playerid, !"ofm_list_page");
		return SendClientMessage(playerid, col_white, !""scm_error"No active logs found.");
	}

	SetPVarInt(playerid, !"ofm_list_rows", rows);
	new rows_list = GetPVarInt(playerid, !"ofm_list_page") -1;

	global_string[0] = EOS;
	strcat(global_string, ""c_grey"Previous page\n"c_grey"Next page\n"c_white"");
	for(new i = rows_list * 10; i < rows_list * 10 + 10; i ++)
	{
		if(i >= rows) break;

		t_id = cache_get_field_content_int(i, "id", sql_connection);
		cache_get_field_content(i, "name", t_name, sql_connection, 32);
		cache_get_field_content(i, "text_date", t_date, sql_connection, 48);

		new pvar_string[16];
		format(pvar_string, sizeof(pvar_string), "vrl_%d", i -rows_list * 10);
		SetPVarInt(playerid, pvar_string, t_id);

		new line_string[100];
		format(line_string, sizeof(line_string), ""c_server"%d | "c_white"%s -"c_grey"%s\n", i + 1, t_name, t_date);
		strcat(global_string, line_string);
	}
	return show_dialog(playerid, d_family_lognext, DIALOG_STYLE_LIST, !""scm_dialog"Family history", global_string, !"Entekhab", !"Bastan");
}

callback: get_family_logs_info(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(!rows)
	{
	    DeletePVar(playerid, !"ofm_list_page");
	    return pc_cmd_fmenu(playerid);
	}

	new t_name[32], t_date[48], t_text[128];
	
	cache_get_field_content(0, "name", t_name, sql_connection, 32);
	cache_get_field_content(0, "text_date", t_date, sql_connection, 48);
	cache_get_field_content(0, "Text", t_text, sql_connection, 128);

	new dialog_string[350];
	format(dialog_string, sizeof(dialog_string), ""c_white"Character nickname: "c_gold"%s\n"c_white"Date: "c_silver"%s\n\n"c_white"Action: "c_silver"%s", t_name, t_date, t_text);
	return show_dialog(playerid, d_family_logback, DIALOG_STYLE_MSGBOX, !""scm_dialog"Family history", dialog_string, !"Barghast", !"Bastan");
}

callback: check_bl_list_family(playerid, pl_name[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new target_inc;
		
		target_inc = cache_get_field_content_int(0, "bl_player", sql_connection);

		new query_string[144];
		format(query_string, sizeof(query_string), "DELETE FROM `family_blacklist` WHERE `bl_player`='%d' AND `bl_family`='%d' LIMIT 1", target_inc, PlayerInfo[playerid][family]);
		mysql_query(sql_connection, query_string);

		new targetid = INVALID_PLAYER_ID;
		foreach(new i: logged_players)
		{
			if(PlayerInfo[i][id] != target_inc) continue;
			targetid = i;
		}
		if(targetid != INVALID_PLAYER_ID)
		{
			format(query_string, sizeof(query_string), ""scm_info""c_server"%s"c_white" removed Vas from the black list of the family "c_gold"%s", PlayerInfo[playerid][name], family_info[PlayerInfo[playerid][family]][fam_name]);
			SendClientMessage(targetid, col_white, query_string);
		}
		format(query_string, sizeof(query_string), "%s removed %s from family black list %s", PlayerInfo[playerid][name], pl_name, family_info[PlayerInfo[playerid][family]][fam_name]);
		write_family(playerid, PlayerInfo[playerid][family], TYPE_LOG_BL, query_string);

		format(query_string, sizeof(query_string), ""scm_info"You have been removed from the blacklist "c_server"%s", pl_name);
		SendClientMessage(playerid, col_white, query_string);

		show_dialog(playerid, d_blacklist_family, DIALOG_STYLE_LIST, !""scm_dialog"What list", !""c_server"1."c_white" Add person to blacklist\n"c_server"2."c_white" Clear black ый scribble\n"c_server"3."c_white" Remove person from blacklist\n"c_server"4."c_white"ЧHardlist of players", !"Entekhab", !"Barghast");
	}
	else
	{
		new text_string[95];
		format(text_string, sizeof(text_string), ""scm_error""c_server"%s"c_white" not found in black list", pl_name);
		SendClientMessage(playerid, col_white, text_string);

		show_dialog(playerid, d_blacklist_family, DIALOG_STYLE_LIST, !""scm_dialog"What list", !""c_server"1."c_white" Add person to blacklist\n"c_server"2."c_white" Clear black ый scribble\n"c_server"3."c_white" Remove person from blacklist\n"c_server"4."c_white"ЧHardlist of players", !"Entekhab", !"Barghast");
	}
	return 1;
}

callback: callback_bl_family(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
    if(!rows) return SendClientMessage(playerid, col_white, !""scm_error"Players with these parameters not found.");

    new rows_list = GetPVarInt(playerid, !"ofm_list_page") -1;
    SetPVarInt(playerid, !"ofm_list_rows", rows);

    global_string[0] = EOS;
    strcat(global_string, ""c_grey"Previous page\n"c_grey"Next page\n"c_white"");
    for(new i = rows_list * 10; i < rows_list * 10 + 10; i ++)
    {
        if(i >= rows) break;

        new pl_ofm_name[24], pl_ofm_online[24];

        cache_get_field_content(i, "bl_name", pl_ofm_name, sql_connection, 24);
        cache_get_field_content(i, "bl_date", pl_ofm_online, sql_connection, 24);

        new pvar_string[8];
        format(pvar_string, sizeof(pvar_string), "ofm_%d", i -rows_list * 10);
        SetPVarString(playerid, pvar_string, pl_ofm_name);

        new _pl_id;
        sscanf(pl_ofm_name, "u", _pl_id);

        new line_string[95];
        format(line_string, sizeof(line_string), ""c_white"%s -"c_grey"Date of entry: %s (%s)\n", pl_ofm_name, pl_ofm_online, (IsPlayerConnected(_pl_id)) ? (""c_green"in the network"c_white"") : (""c_orange_red"offline"c_white""));
        strcat(global_string, line_string);
    }
    return show_dialog(playerid, d_offamily_bl_list, DIALOG_STYLE_LIST, !""scm_dialog"Чёрный список", global_string, !"Entekhab", !"Barghast");
}

callback: callback_bl_family_info(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new pl_date[24], pl_reason[24], pl_add_name[32];

		cache_get_field_content(0, "bl_date", pl_date, sql_connection, 24);
		cache_get_field_content(0, "bl_reason", pl_reason, sql_connection, 24);
		cache_get_field_content(0, "bl_add_name", pl_add_name, sql_connection, 32);

		new pvar_string[38], pl_name[MAX_PLAYER_NAME];
		format(pvar_string, sizeof(pvar_string), "ofm_%d", GetPVarInt(playerid, !"ofm_listitem"));
		GetPVarString(playerid, pvar_string, pl_name, MAX_PLAYER_NAME);

		new dialog_string[325];
		format(dialog_string, sizeof(dialog_string), ""c_white"Name: "c_gold"%s\n"c_white" Reason: "c_silver"%s\n"c_white" Entry Date: "c_silver"%s\n"c_white" Started: "c_silver"%s", pl_name, pl_reason, pl_date, pl_add_name);
		show_dialog(playerid, d_offamily_bl_pl_menu_info, DIALOG_STYLE_MSGBOX, !""scm_dialog"Player Information", dialog_string, !"Barghast", !"");
	}
	if(!rows)
	{
		DeletePVar(playerid, !"ofm_listitem");

		if(!GetPVarInt(playerid, !"ofm_type"))
		{
			new query_string[80];
			format(query_string, sizeof(query_string), "SELECT `bl_name`,`bl_date` FROM `family_blacklist` WHERE `bl_family`='%d'", PlayerInfo[playerid][family]);
			mysql_tquery(sql_connection, query_string, "callback_bl_family", "i", playerid);
			return 1;
		}
	}
	return 1;
}

stock offuninvite_check(playerid, pl_name[], type)
{
	if(type == 0)
	{
		new _pl_id, family_id = PlayerInfo[playerid][family];
		sscanf(pl_name, "u", _pl_id);

		if(IsPlayerConnected(_pl_id))
		{
			if(playerid == _pl_id)
			{
				SendClientMessage(playerid, col_white, !""scm_error"Shoma nmitoni in kar ra roye khodeton anjam badid.");

				DeletePVar(playerid, !"ofm_listitem");
				if(!GetPVarInt(playerid, !"ofm_type"))
				{
					new query_string[100];
					mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT `u_name`,`u_last_date`,`u_family_rank` FROM `users` WHERE `u_family`='%d'", PlayerInfo[playerid][family]);
					mysql_tquery(sql_connection, query_string, "callback_offamily", "i", playerid);
				}
				return 1;
			}
			Iter_Remove(family_players[family_id], _pl_id);

			PlayerInfo[_pl_id][family] = -1;
			PlayerInfo[_pl_id][family_rang] = 0;

			new text_string[105];
			format(text_string, sizeof(text_string), ""scm_info""c_server"%s"c_white" kicked you out of the family.", PlayerInfo[playerid][name]);
			SendClientMessage(_pl_id, col_white, text_string);
		}
		else
		{
			new query_string[105];
			format(query_string, sizeof(query_string), "INSERT INTO `debtor_message`(`dm_text`, `dm_dest`) VALUES ('You were kicked out of the family.','%d')", get_player_account_id(pl_name));
			mysql_query(sql_connection, query_string);
		}
		new query_string[125];
		format(query_string, sizeof(query_string), "UPDATE `users` SET `u_family`='-1',`u_family_rank`='0' WHERE `u_name`='%s' LIMIT 1", pl_name);
		mysql_query(sql_connection, query_string);

		format(query_string, sizeof(query_string), ""scm_info"You kicked "c_server"%s"c_white" out of the family.", pl_name);
		SendClientMessage(playerid, col_white, query_string);

		family_info[family_id][fam_members] --;

		format(query_string, sizeof(query_string), "UPDATE `family` SET `fam_members`='%d' WHERE `fam_id`='%d' LIMIT 1", family_info[family_id][fam_members], getPlayerFamilyID(playerid));
		mysql_query(sql_connection, query_string);

		format(query_string, sizeof(query_string), "%s kicked %s out of the family", PlayerInfo[playerid][name], pl_name);
		write_family(playerid, family_id, TYPE_LOG_UVAL, query_string);

		DeletePVar(playerid, !"ofm_listitem");
		if(!GetPVarInt(playerid, !"ofm_type"))
		{
			mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT `u_name`,`u_last_date`,`u_family_rank` FROM `users` WHERE `u_family`='%d'", PlayerInfo[playerid][family]);
			mysql_tquery(sql_connection, query_string, "callback_offamily", "i", playerid);
			return 1;
		}
	}
	return 1;
}

stock offmembers_rank(playerid, value_rank, pl_name[], type)
{
	if(type == 0)
	{
		new _pl_id;
		sscanf(pl_name, "u", _pl_id);

		if(IsPlayerConnected(_pl_id))
		{
			if(playerid == _pl_id)
			{
				SendClientMessage(playerid, col_white, !""scm_error"You cannot apply this action to yourself.");
				return show_dialog_offpanel(playerid, pl_name, 3);
			}
			PlayerInfo[_pl_id][family_rang] = value_rank;

			new text_string[110];
			format(text_string, sizeof(text_string), ""scm_info""c_server"%s"c_white" changed your status in the family on "c_gold"%d", PlayerInfo[playerid][name], value_rank);
			SendClientMessage(_pl_id, col_white, text_string);
		}
		else
		{
			new debtor_string[35];
			format(debtor_string, sizeof(debtor_string), "Your status in the family has been changed %d", value_rank);

			new query_string[150];
			format(query_string, sizeof(query_string), "INSERT INTO `debtor_message`(`dm_text`,`dm_dest`) VALUES ('%s','%d')", debtor_string, get_player_account_id(pl_name));
			mysql_query(sql_connection, query_string);
		}
		new query_string[120];
		format(query_string, sizeof(query_string), "UPDATE `users` SET `u_family_rank`='%d' WHERE `u_name`='%s' LIMIT 1", value_rank, pl_name);
		mysql_query(sql_connection, query_string);

		format(query_string, sizeof(query_string), ""scm_info"You have changed the status "c_server"%s"c_white" on "c_gold"%d", pl_name, value_rank);
		SendClientMessage(playerid, col_white, query_string);

		format(query_string, sizeof(query_string), "%s changed the status of %s to %d", PlayerInfo[playerid][name], pl_name, value_rank);
		write_family(playerid, PlayerInfo[playerid][family], TYPE_LOG_AGIVERANK, query_string);
	}
    return 1;
}

callback: load_family_vehicles()
{
	new rows, fields;
	cache_get_data(rows, fields);
	
	new family_id;
	new fam_hex_string[64];

    if(rows)
    {
        for(new i = 0; i < rows; i++)
        {
			new veh_id = GetVehicleID();
			veh_info[veh_id -1][v_id] = cache_get_field_content_int(i, "sv_id", sql_connection);
			veh_info[veh_id -1][v_model] = cache_get_field_content_int(i, "sv_model", sql_connection);
			// veh_info[veh_id -1][v_type] = cache_get_field_content_int(i, "sv_type", sql_connection);
			veh_info[veh_id -1][v_type] = vehicle_type_family;
			veh_info[veh_id -1][v_owner] = getFamilyID(cache_get_field_content_int(i, "sv_owner", sql_connection));
			veh_info[veh_id -1][v_rank] = cache_get_field_content_int(i, "sv_rank", sql_connection);

			cache_get_field_content(i, "sv_plate", veh_info[veh_id -1][v_plate], sql_connection, 12);

			veh_info[veh_id -1][v_fuel] = cache_get_field_content_float(i, "sv_fuel", sql_connection);

			veh_info[veh_id -1][v_color][0] = cache_get_field_content_int(i, "sv_color_1", sql_connection);
			veh_info[veh_id -1][v_color][1] = cache_get_field_content_int(i, "sv_color_2", sql_connection);
			veh_info[veh_id -1][v_paint] = cache_get_field_content_int(i, "sv_paint", sql_connection);

			veh_info[veh_id -1][v_sell_price] = cache_get_field_content_int(i, "sv_sell_price", sql_connection);

			veh_info[veh_id -1][v_pos][0] = cache_get_field_content_float(i, "sv_pos_x", sql_connection);
			veh_info[veh_id -1][v_pos][1] = cache_get_field_content_float(i, "sv_pos_y", sql_connection);
			veh_info[veh_id -1][v_pos][2] = cache_get_field_content_float(i, "sv_pos_z", sql_connection);
			veh_info[veh_id -1][v_pos][3] = cache_get_field_content_float(i, "sv_pos_a", sql_connection);

			veh_info[veh_id -1][v_millage] = cache_get_field_content_float(i, "sv_millage", sql_connection);

			veh_info[veh_id -1][v_engine_boost] = cache_get_field_content_float(i, "sv_engine_boost", sql_connection);
			veh_info[veh_id -1][v_brake_boost] = cache_get_field_content_float(i, "sv_brake_boost", sql_connection);
			veh_info[veh_id -1][v_stability_boost] = cache_get_field_content_float(i, "sv_stability_boost", sql_connection);

			new sscanf_delimit[126];
			cache_get_field_content(i, "sv_eng_details", sscanf_delimit, sql_connection, 16);
			sscanf(sscanf_delimit, "p<|>ddddd", veh_info[veh_id -1][v_pt_engine][0], veh_info[veh_id -1][v_pt_engine][1], veh_info[veh_id -1][v_pt_engine][2], veh_info[veh_id -1][v_pt_engine][3], veh_info[veh_id -1][v_pt_engine][4]);

			cache_get_field_content(i, "sv_brake_details", sscanf_delimit, sql_connection, 16);
			sscanf(sscanf_delimit, "p<|>ddddd", veh_info[veh_id -1][v_pt_brake][0], veh_info[veh_id -1][v_pt_brake][1], veh_info[veh_id -1][v_pt_brake][2], veh_info[veh_id -1][v_pt_brake][3], veh_info[veh_id -1][v_pt_brake][4]);

			cache_get_field_content(i, "sv_stab_details", sscanf_delimit, sql_connection, 16);
			sscanf(sscanf_delimit, "p<|>ddddd", veh_info[veh_id -1][v_pt_stability][0], veh_info[veh_id -1][v_pt_stability][1], veh_info[veh_id -1][v_pt_stability][2], veh_info[veh_id -1][v_pt_stability][3], veh_info[veh_id -1][v_pt_stability][4]);

			cache_get_field_content(i, "sv_components", sscanf_delimit, sql_connection, 126);
			sscanf(sscanf_delimit, "p<|>dddddddddd", veh_info[veh_id -1][v_component][0], veh_info[veh_id -1][v_component][1], veh_info[veh_id -1][v_component][2], veh_info[veh_id -1][v_component][3], veh_info[veh_id -1][v_component][4], veh_info[veh_id -1][v_component][5], veh_info[veh_id -1][v_component][6], veh_info[veh_id -1][v_component][7], veh_info[veh_id -1][v_component][8], veh_info[veh_id -1][v_component][9]);

			veh_info[veh_id -1][v_vw] = cache_get_field_content_int(i, "sv_vw", sql_connection);
			veh_info[veh_id -1][v_int] = cache_get_field_content_int(i, "sv_int", sql_connection);

            veh_info[veh_id -1][v_vehicle] = AddStaticVehicleEx(veh_info[veh_id -1][v_model], veh_info[veh_id -1][v_pos][0], veh_info[veh_id -1][v_pos][1], veh_info[veh_id -1][v_pos][2], veh_info[veh_id -1][v_pos][3], veh_info[veh_id -1][v_color][0], veh_info[veh_id -1][v_color][1], 600);
            SetVehicleNumberPlate(veh_info[veh_id -1][v_vehicle], veh_info[veh_id -1][v_plate]);

            family_id = veh_info[veh_id -1][v_owner];
			format(fam_hex_string, sizeof(fam_hex_string), "{%s}%s", family_info[family_id][fam_chat_color], family_info[family_id][fam_name]);
			veh_info[veh_id -1][v_label_family] = CreateDynamic3DTextLabel(fam_hex_string, col_white, 0.0, 0.0, 0.0, 13.0, INVALID_PLAYER_ID, veh_info[veh_id -1][v_vehicle], 0);

			if(veh_info[veh_id -1][v_int] != 0)
				LinkVehicleToInterior(veh_info[veh_id -1][v_vehicle], veh_info[veh_id -1][v_int]);

			if(veh_info[veh_id -1][v_vw] != 0)
				SetVehicleVirtualWorld(veh_info[veh_id -1][v_vehicle], veh_info[veh_id -1][v_vw]);

            if(veh_info[veh_id -1][v_paint] != 3)
            	ChangeVehiclePaintjob(veh_info[veh_id -1][v_vehicle], veh_info[veh_id -1][v_paint]);

            for(new j = 0; j < 10; j ++)
            	AddVehicleComponent(veh_info[veh_id -1][v_vehicle], veh_info[veh_id -1][v_component][j]);

			veh_info[veh_id -1][v_locked] = false;

            Iter_Add(family_vehicles[veh_info[veh_id -1][v_owner]], veh_id);
        }
    }
    return printf("[SERVER] Total load of family vehicles: %d", rows);
}


alias:deletefamily("delfam");
cmd:deletefamily(playerid, params[])
{
    if(check_admin_rank(playerid , 8)) return 1;

    new familyName[68];
	if(sscanf(params, "s[68]", familyName)) return SendClientMessage(playerid, col_gray,""scm_info"Enter: /deletefamily [family name]");

	new family_id = -1;

	for(new i = 0; i < family_count; i ++)
	{
		if(!strcmp(familyName, family_info[i][fam_name], true)) 
		{
			family_info[family_id][fam_id] = family_info[i][fam_id];

			family_id = i;

			strdel(family_info[i][fam_name], 0, 68);
			strdel(family_info[i][fam_chat_color], 0, 8);
			strdel(family_info[i][fam_creator], 0, MAX_PLAYER_NAME);
			strdel(family_info[i][fam_settings], 0, 8);

			family_info[i][fam_type] = 0;
			family_info[i][fam_house] = -1;
			family_info[i][fam_materials] = 0;
			family_info[i][fam_dorm_status] = 0;
			family_info[i][fam_guns] = 0;
			family_info[i][fam_members] = 0;
			family_info[i][fam_rating] = 0;
			family_info[i][fam_ticket] = 0;
			family_info[i][fam_max_car] = 0;

			break;
		}
	}

	if(family_id == -1) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Family not found");

	new query_string[125];

	foreach(new i: logged_players)
	{
		Iter_Remove(family_players[family_id], i);

		PlayerInfo[i][family] = -1;
		PlayerInfo[i][family_rang] = 0;

		if(PlayerInfo[i][spawnchange] == 6) PlayerInfo[i][spawnchange] = 0;

		if(PlayerInfo[i][family_text] != Text3D:INVALID_3DTEXT_ID)
		{
			DestroyDynamic3DTextLabel(PlayerInfo[i][family_text]);
			PlayerInfo[i][family_text] = Text3D:INVALID_3DTEXT_ID;
		}
	}

	format(query_string, sizeof(query_string), "UPDATE `users` SET `u_family`='-1',`u_family_rank`='0' WHERE `u_family`='%d'", family_info[family_id][fam_id]);
	mysql_query(sql_connection, query_string);

	format(query_string, sizeof(query_string), "DELETE FROM `family_blacklist` WHERE `bl_family`='%d' LIMIT 1", family_info[family_id][fam_id]);
	mysql_query(sql_connection, query_string);
	
	format(query_string, sizeof(query_string), "DELETE FROM `logs_family` WHERE `family`='%d' LIMIT 1", family_info[family_id][fam_id]);
	mysql_query(sql_connection, query_string);

	format(query_string, sizeof(query_string), "DELETE FROM `family_vehicles` WHERE `sv_owner`='%d' LIMIT 1", family_info[family_id][fam_id]);
	mysql_query(sql_connection, query_string);

	format(query_string, sizeof(query_string), "DELETE FROM `family` WHERE `fam_id`='%d' LIMIT 1", family_info[family_id][fam_id]);
	mysql_query(sql_connection, query_string);

	format(query_string, sizeof(query_string), ""scm_sucess"Family {%s}%s "c_white"Delete Shod.", family_info[family_id][fam_chat_color], family_info[family_id][fam_name]);
	SendClientMessage(playerid, col_white, query_string);

    if(Iter_Count(family_vehicles[family_id]) > 0)
    {
        family_cars[family_id] = 0;
        foreach(new i: family_vehicles[family_id])
        {
            DestroyVehicle(i);
            veh_info[i -1][v_vehicle] = INVALID_VEHICLE_ID;
        }
        Iter_Clear(family_vehicles[family_id]);
    }

	/* Family House Reset */
	if(familyHouseStatus(family_id)) 
	{
		new house_id = family_info[family_id][fam_house];

		h_info[house_id][h_family] = -1;
		
		family_info[family_id][fam_house] = -1;
		
		UpdateHouseEnterLabel(house_id);

		format(query_string, 72, "UPDATE `houses` SET `h_family`=%d WHERE `h_id`='%d'", h_info[house_id][h_family], h_info[house_id][h_id]);
		mysql_query(sql_connection, query_string);
	}

	family_info[family_id][fam_id] = 0;

	return 1;
}