cmd:makeadmin(playerid,params[])
{
    if(check_admin_rank(playerid , 6)) return 1;

 	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /makeadmin [id Bazikon]");
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(PlayerInfo[targetid][admin] >= PlayerInfo[playerid][admin]) return SendError(playerid, "Shoma nemitavanid satahe modiriat in admin ra taghir dahid");

	SetPVarInt(playerid, !"target_id", targetid);

	new header_string[45], body[40];
	global_string[0] = EOS;
	global_string = !""c_grey"Hazf az morede modiriat\n"c_white"";

	for(new i = 1; i < PlayerInfo[playerid][admin]; i++)
	{
		format(body, sizeof body, "%s level\n", a_rank_name[i-1]);
		strcat(global_string, body);
	}

	format(header_string, sizeof(header_string), ""scm_dialog"%s", PlayerInfo[targetid][name]);
	return show_dialog(playerid, d_makeadmin, DIALOG_STYLE_LIST, header_string, global_string, !"Entekhab", !"Bastan");
}

callback: makeadmin_callback(playerid, targetid, admin_level)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(admin_level >= PlayerInfo[playerid][admin]) return SendError(playerid, "You cannot change the level of this administrator.");

	if(!rows)
	{
		if(admin_level == 0) return SendError(playerid, "The player is not an administrator.");
		else
		{
			if(PlayerInfo[playerid][admin] == admin_level) return SendError(playerid, "You cannot issue the same level as you.");

			new query_string[144];
			format(query_string, sizeof(query_string), "INSERT INTO `users_admins`(`u_a_name`,`u_a_level`,`u_a_date`) VALUES ('%s','%d', NOW())", PlayerInfo[targetid][name], admin_level);
			mysql_query(sql_connection, query_string);

			format(query_string, sizeof(query_string), ""scm_info"You have assigned "c_server"%s"c_white" to %s administrator level", PlayerInfo[targetid][name], a_rank_name[admin_level-1]);
			SendClientMessage(playerid, col_white, query_string);

			format(query_string, sizeof(query_string), ""scm_info"Admin "c_server"%s"c_white" appointed Vasna to %s admin level", PlayerInfo[playerid][name], a_rank_name[admin_level-1]);
			SendClientMessage(targetid, col_white, query_string);
			SendClientMessage(targetid, col_white, !""scm_info"Enter "c_gold"/alogin"c_white" for authorization in the admin panel");
			GameTextForPlayer(targetid, "~g~/ahelp", 3000, 3);
		}
	}
	else
	{
		if(admin_level == 0)
		{
			new query_string[148];
			format(query_string, sizeof(query_string), "DELETE FROM `users_admins` WHERE `u_a_name`='%s' LIMIT 1", PlayerInfo[targetid][name]);
			mysql_query(sql_connection, query_string);

			if(PlayerInfo[targetid][admin] != 0)
			{
				PlayerInfo[targetid][admin] = 0;
				Iter_Remove(admin_players, targetid);

				UpdatePlayerName(targetid);
			}

			format(query_string, sizeof(query_string), ""scm_info"You have retired "c_server"%s"c_white" as administrator", PlayerInfo[targetid][name]);
			SendClientMessage(playerid, col_white, query_string);
		}
		else
		{
			if(PlayerInfo[playerid][admin] == admin_level) return SendError(playerid, "You cannot issue the same level as you.");

			new query_string[128];
			format(query_string, sizeof(query_string), "UPDATE `users_admins` SET `u_a_level`='%d' WHERE `u_a_name`='%s' LIMIT 1", admin_level, PlayerInfo[targetid][name]);
			mysql_query(sql_connection, query_string);

			PlayerInfo[targetid][admin] = admin_level;

			UpdatePlayerName(targetid);

			format(query_string, sizeof(query_string), ""scm_info"You have assigned "c_server"%s"c_white" to %d administrator level", PlayerInfo[targetid][name], admin_level);
			SendClientMessage(playerid, col_white, query_string);

			format(query_string, sizeof(query_string), ""scm_info"Admin "c_server"%s"c_white" assigned you to %d level Admin", PlayerInfo[playerid][name], admin_level);
			SendClientMessage(targetid, col_white, query_string);
		}
	}
	return 1;
}

cmd:ahelp(playerid)
{
	if(check_admin_rank(playerid , 1)) return 1;

	if(PlayerInfo[playerid][admin] == 1) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !" Level 1", !"Entekhab", !"Bastan");
	else if(PlayerInfo[playerid][admin] == 2) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !"1 level\n2 level", !"Entekhab", !"Bastan");
	else if(PlayerInfo[playerid][admin] == 3) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !"1 level\n2 level\n3 level", !"Entekhab", !"Bastan");
	else if(PlayerInfo[playerid][admin] == 4) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !"1 level\n2 level\n3 level\n4 level", !"Entekhab", !"Bastan");
	else if(PlayerInfo[playerid][admin] == 5) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !"1 level\n2 level\n3 level\n4 level\n5 level", !"Entekhab", !"Bastan");
	else if(PlayerInfo[playerid][admin] == 6) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !"1 level\n2 level\n3 level\n4 level\n5 level\n6 level", !"Entekhab", !"Bastan");
	else if(PlayerInfo[playerid][admin] == 7) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !"1 level\n2 level\n3 level\n4 level\n5 level\n6 level \n7 level", !"Entekhab", !"Bastan");
	else if(PlayerInfo[playerid][admin] == 8) show_dialog(playerid, d_ahelp, DIALOG_STYLE_LIST, !c_server"Admin "c_white"Commands", !"1 level\n2 level\n3 level\n4 level\n5 level\n6 level\n7 level\n8 level", !"Entekhab", !"Bastan");
	
	return 1;
}

alias:admin("a");
cmd:admin(playerid, params[])
{
	if(check_admin_rank(playerid , 1)) return 1;
	extract params -> new string:a_text[128]; else return SendInfo(playerid, "Enter: /a [Matn]");

	foreach(new i: admin_players) SendMes(i, 0x9ACD32AA, "[A] %s %s[%d]: %s", a_rank_name[PlayerInfo[playerid][admin]-1], PlayerInfo[playerid][name], playerid, a_text);

	return 1;
}

cmd:stats(playerid, params[])
{
	if(check_admin_rank(playerid , 1)) return 1;
	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /stats [id Bazikon]");
	if(!IsPlayerConnected(targetid)) return SendError(playerid, "Bazikon Yaft Nashod.");

	return show_stats(targetid, playerid);
}

cmd:money(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /money [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");


	new sql_string[96];
	mysql_format(sql_connection, sql_string, 96, "SELECT * FROM `deposit_boxes` WHERE `db_owner` = '%d' LIMIT 3",
	PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, sql_string, "cmd_money_callback", "ii", playerid, params[0]);

	return 1;
}

cmd:fulldorm(playerid)
{
	if(check_admin_rank(playerid , 3)) return 1;

	show_dialog(playerid, d_fulldorm, DIALOG_STYLE_LIST, !""scm_dialog"Pour kardan komod",
    !"Grove Street\n\
	Ballas\n\
	Los Santos Vagos\n\
	Rifa\n\
	Varios Los Aztecas", !"Full", !"Bastan");

	return 1;
}


callback:cmd_money_callback(playerid, targetid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	new _db_name[32],
		line_string[78];


	format(global_string, 136, "\
	"c_grey"Cash -"c_white"$%d\n\
	"c_grey"Main focus -"c_white"$%d\n\n"c_server"Open accounts\n", PlayerInfo[targetid][money], PlayerInfo[targetid][bank]);
	for(new j = 0; j < rows; j ++)
	{
		new _db_id = cache_get_field_content_int(j, "db_id", sql_connection);
		new _db_money = cache_get_field_content_int(j, "db_money", sql_connection);

		cache_get_field_content(j, "db_name", _db_name, sql_connection, 32);

		format(line_string, sizeof(line_string), ""c_grey"%s(#%d) -"c_white"$%d\n", _db_name, _db_id, _db_money);
		strcat(global_string, line_string);
	}
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Player finances", global_string, "Bastan", "");
	return 1;
}

cmd:moneylog(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /moneylog [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");


	new sql_string[136];
	mysql_format(sql_connection, sql_string, 136, "SELECT * FROM `money_logs` WHERE `name` = '%s' ORDER BY `money_logs`.`log_id` DESC LIMIT 25",
	PlayerInfo[params[0]][name]);
	mysql_tquery(sql_connection, sql_string, "cmd_moneylog_callback", "ii", playerid, params[0]);

	return 1;
}


cmd:offmoneylog(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Enter: /offmoneylog [имя]");


	new sql_string[136];
	mysql_format(sql_connection, sql_string, 136, "SELECT * FROM `money_logs` WHERE `name` = '%s' ORDER BY `money_logs`.`log_id` DESC LIMIT 25",
	params[0]);
	mysql_tquery(sql_connection, sql_string, "cmd_moneylog_callback", "is", playerid, params[0]);

	return 1;
}

callback:cmd_moneylog_callback(playerid, pl_name[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"No transfer data found.");
	global_string[0] = EOS;
	for(new j = 0; j < rows; j ++)
	{
		new log_date[24], log_reason[48], log_from[20], log_money, line_string[108];

		log_money = cache_get_field_content_int(j, "money", sql_connection);

		cache_get_field_content(j, "from_name", log_from, sql_connection, 20);
		cache_get_field_content(j, "reason", log_reason, sql_connection, 48);
		cache_get_field_content(j, "date", log_date, sql_connection, 24);

		format(line_string, sizeof(line_string), ""c_white"%s\t%s\t$%d\t%s\n", log_date, log_from, log_money, log_reason);
		strcat(global_string, line_string);
	}
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"The history of the player's finances", global_string, "Bastan", "");
	return 1;
}

cmd:ans(playerid, params[])
{
	if(check_admin_rank(playerid , 1)) return 1;
	extract params -> new player:targetid, string:ans_text[128]; else return SendInfo(playerid, "Enter: /ans [id Bazikon] [Matn]");
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendError(playerid, "Bazikon Yaft Nashod.");

    new text_string[144];
    format(text_string, sizeof(text_string), "Admin %s:"c_white" %s", PlayerInfo[playerid][name], ans_text);
    SendClientMessage(targetid, 0xFF6347FF, text_string);

    foreach(new i: admin_players) SendMes(i, 0xFAAC58FF, "Admin %s[%i] for %s[%i]:"c_white" %s", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid, ans_text);

	return 1;
}

alias:cc("clearchat");
cmd:cc(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	for(new i = 0; i < 56; i ++)SendClientMessageToAll(col_white, " ");
	foreach(new i: logged_players) if(PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, "Chat has been cleared by the administration.");

	AdminMes(""c_server"* A.INFO: "c_grey"Admin %s cleared chat.", PlayerInfo[playerid][name]);

	return 1;
}

cmd:ufo(playerid, params[])
{
    if(check_admin_rank(playerid , 7)) return 1;

    new tid;
	if(sscanf(params, "r", tid)) return SendInfo(playerid, "Enter: /UFO [id Bazikon]");

	new veh_id_temporary = GetPVarInt(tid, !"admin_vehicle");
	if(veh_id_temporary)
	{
		DestroyVehicle(veh_id_temporary);
	}

	new color_1 = random(255);
	new color_2 = random(255);

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z;
	GetPlayerPos(tid, pl_pos_X, pl_pos_Y, pl_pos_Z);
	new adm_veh = CreateVehicle(501, pl_pos_X, pl_pos_Y, pl_pos_Z + 1.0, 0.0, color_1, color_2, -1);
	SetPVarInt(tid, !"admin_vehicle", adm_veh);
	veh_info[adm_veh -1][v_ufo_object] = CreateDynamicObject(18846, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    AttachDynamicObjectToVehicle(veh_info[adm_veh -1][v_ufo_object], adm_veh, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	veh_info[adm_veh -1][v_fuel] = 100.0;

	LinkVehicleToInterior(adm_veh, 1);
	SetVehicleVirtualWorld(adm_veh, GetPlayerVirtualWorld(tid));

	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(adm_veh, engine, lights, alarm, doors, bonnet, boot, objective);

	PutPlayerInVehicle(tid, adm_veh, 0);
	SetPlayerArmedWeapon(tid, 0);

	veh_info[adm_veh -1][v_engine_status] = VEHICLE_PARAMS_ON;
	SetVehicleParamsEx(adm_veh, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);

	AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] created a transport for %s[%d]. Model: UFO", PlayerInfo[playerid][name], playerid, PlayerInfo[tid][name], tid, adm_veh);

	if(playerid != tid) SendClientMessage(tid, col_green, !"Admin gave you a car");
	return true;
}

cmd:setint(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /setint [id]");
	set_interior(playerid, params[0]);
	SendAccess(playerid, "You are mixing in the specified interior.");
	return 1;
}

cmd:setvw(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /setvw [id]");
	set_world(playerid, params[0]);
	SendAccess(playerid, "You have moved to the indicated virtual world.");
	return 1;
}

cmd:redpanel(playerid)
{
	if(check_admin_rank(playerid , 7)) return 1;

	return show_dialog(playerid, d_redpanel, DIALOG_STYLE_LIST, !""scm_dialog"Server control panel",
	""c_white"Unlock all banned accounts\n\
	"c_white" Unblock all banned IP addresses\n\
	"c_white" Unboil all brewed accounts\n\
	"c_white"Emit everything from the tюрьmы\n\
	"c_white"Sell all houses on the server\n\
	"c_white"Sell all businesses on the server\n\
	"c_white"Conclusion x2\n\
	"c_white"Edit PayDay\n\
	"c_white"Distribution\n\
	"c_red"Do an early restart of the server", "Entekhab", "Cancel");
}

cmd:asellbiz(playerid, params[])
{
	if(check_admin_rank(playerid , 7)) return 1;

	new b, isMsg;
	if(sscanf(params, "dD(1)", b, isMsg)) return SendClientMessage(playerid, col_white, !"Enter: /asellbiz [id business]");

	if(!(0 < b < b_count))
	{
		return SendClientMessage(playerid, col_gray, !"Unknown business indicated");
	}

	if(b_info[b-1][b_owner_inc] == -1)
		return SendClientMessage(playerid, col_gray, !"Business is in voice");
	
	new b_owner = GetPlayerID(b_info[b-1][b_owner_name]);

	if(IsPlayerConnected(b_owner))
	{
		update_int_sql(b_owner, "u_business", -1);
		PlayerInfo[b_owner][business] = -1;
		SendClientMessage(b_owner, col_light_red, "Admin sold your business");
	}
	else
	{
		new query_string[87];
		format(query_string,sizeof(query_string),"UPDATE `users` SET `u_business` = '-1' WHERE `u_id` = '%d' LIMIT 1", b_info[b-1][b_owner_inc]);
		mysql_tquery(sql_connection, query_string, "", "");
	}

	b_info[b-1][b_owner_inc] = -1;
	strfmt(b_info[b-1][b_owner_name], "The State");

	if(isMsg == 1) SendClientMessage(playerid, col_white, "Business successfully sold");

	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	new query_string[200 + MAX_PLAYER_NAME + 1];
	format(query_string, 136,"UPDATE `businesses` SET `b_owner_inc` = '-1', `b_owner_name` = 'The State' WHERE `b_id` = '%d' LIMIT 1", b_info[b-1][b_id]);
	mysql_tquery(sql_connection, query_string);

	UpdateBusinessEnterLabel(b-1);

	return 1;
}


cmd:fullinfo(playerid, params[])
{
	if(check_admin_rank(playerid , 6)) return 1;
	extract params -> new string:u_name[20]; else return SendInfo(playerid, "Enter: /fullinfo [player nickname]");

	new query_string[100];
	format(query_string, sizeof query_string, "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", u_name);
	mysql_tquery(sql_connection, query_string, "GetOfflinePlayerInfo", "d", playerid);

	return 1;
}

callback: GetOfflinePlayerInfo(playerid)
{
	if(!cache_num_rows()) return SendError(playerid, "Bazikon Yaft Nashod.");

	new o_id;
	o_id = cache_get_field_content_int(0, "u_id", sql_connection);
	SetPVarInt(playerid, "offline_target_id", o_id);
	new otarget[20];
	cache_get_field_content(0, "u_name", otarget, sql_connection, sizeof(otarget));
	SetPVarString(playerid, "offline_target", otarget);

	show_dialog(playerid, d_afainfo, DIALOG_STYLE_LIST, !""scm_dialog"Detailed information", !"\
		"c_server"1 | "c_white"Basic info\n\
		"c_server"2 | "c_white"Reg. data\n\
		"c_server"3 | "c_white"Warning history\n\
		"c_server"4 | "c_white"Account lock history\n\
		"c_server"5 | "c_white"History of finance", !"Entekhab", !"Bastan");

	return 1;
}

callback: GetOfflineStats(playerid)
{
	new const mm_gender[][] = {
	"Mard",
	"Zan"};

	new oid, ohouse, obiz, omember, orank, olvl, oexp, oage, ophone, opbalance, owanted, osex, ojob, ogoogle[30], otarget[20], otimeplay, otimeplayafk, otimeplaytoday, otimeplaytodayafk;

	oid = cache_get_field_content_int(0, "u_id", sql_connection);
	cache_get_field_content(0, "u_name", otarget, sql_connection);
	cache_get_field_content(0, "u_googleauth", ogoogle, sql_connection);
	ohouse = cache_get_field_content_int(0, "u_house", sql_connection);
	obiz = cache_get_field_content_int(0, "u_business", sql_connection);
	omember = cache_get_field_content_int(0, "u_member", sql_connection);
	orank = cache_get_field_content_int(0, "u_rank", sql_connection);
	olvl = cache_get_field_content_int(0, "u_level", sql_connection);
	oexp = cache_get_field_content_int(0, "u_exp", sql_connection);
	oage = cache_get_field_content_int(0, "u_age", sql_connection);
	ophone = cache_get_field_content_int(0, "u_number", sql_connection);
	opbalance = cache_get_field_content_int(0, "u_phone_balance", sql_connection);
	owanted = cache_get_field_content_int(0, "u_wanted", sql_connection);
	osex = cache_get_field_content_int(0, "u_gender", sql_connection);
	ojob = cache_get_field_content_int(0, "u_job", sql_connection);

	otimeplay = cache_get_field_content_int(0, "u_timeplay", sql_connection);
	otimeplayafk = cache_get_field_content_int(0, "u_timeplay_afk", sql_connection);
	
	otimeplaytoday = cache_get_field_content_int(0, "u_timeplaytoday", sql_connection);
	otimeplaytodayafk = cache_get_field_content_int(0, "u_timeplaytoday_afk", sql_connection);

	new house_data[12];
	if(ohouse != -1)
		format(house_data, sizeof(house_data), "house #%d", ohouse);
	else
		format(house_data, sizeof(house_data), "missing");

	new business_date[32];
	if(obiz != -1)
		format(business_date, 32, "%s (%d)", b_info[obiz -1][b_name], obiz -1);
	else
		format(business_date, 32, "missing");

	new job_data[22];
	if(ojob != 0 && ojob < 50)
		format(job_data, sizeof(job_data), "%s", jobs_name[ojob -1]);
	else
		format(job_data, sizeof(job_data), "missing");

	new fraction_data[32];
	if(omember)
		format(fraction_data, sizeof(fraction_data), "%s", f_info[getFactionID(omember)][f_name]);
	else
		format(fraction_data, sizeof(fraction_data), "missing");

	new rank_data[32];
	if(orank)
		format(rank_data, sizeof(rank_data), "%s", f_rank[orank -1][orank -1]);
	else
		format(rank_data, sizeof(rank_data), "missing");

	new hours=0, minutes=0, seconds=0;
	ToHHMMSS(otimeplay, hours, minutes, seconds);
	new afk_hours=0, afk_minutes=0, afk_seconds=0;
	ToHHMMSS(otimeplayafk, afk_hours, afk_minutes, afk_seconds);

	new today_hours=0, today_minutes=0, today_seconds=0;
	ToHHMMSS(otimeplaytoday, today_hours, today_minutes, today_seconds);
	new today_afk_hours=0, today_afk_minutes=0, today_afk_seconds=0;
	ToHHMMSS(otimeplaytodayafk, afk_hours, afk_minutes, afk_seconds);

	format(global_string, 1028, "\
	"c_grey"Yamya:\t\t\t\t"c_white"%s %s\n\
	"c_grey"Account number:\t\t"c_white"%d\n\
	"c_grey"Google Authenticator:\t\t"c_white"%s\n\
	"c_grey"Level:\t\t\t"c_white"%d\n\
	"c_grey"XP:\t\t\t"c_white"%d from %d\n\
	"c_grey" Return:\t\t\t"c_white"%d\n\
	"c_grey"Active warnings:\t"c_white"%d\n\n\
	"c_grey"Phone number:\t\t"c_white"%d\n\
	"c_grey"On phone account:\t\t"c_white"%d\n\n\
	"c_grey"Search Level:\t\t"c_white"%d\n\n\
	"c_grey"Prin:\t\t\t\t"c_white"%s\n\
	"c_grey"Working:\t\t\t\t"c_white"%s\n\
	"c_grey" Organization:\t\t\t"c_white"%s\n\
	"c_grey"Ran:\t\t\t\t"c_white"%s\n\
	"c_grey"Residence:\t\t\t"c_white"%s\n\
	"c_grey"Business:\t\t\t"c_white"%s\n\n\
	"c_grey"Total time play today:\t\t\t"c_white"%02d:%02d:%02d\n\
	"c_grey"Total afk today:\t\t\t"c_white"%02d:%02d:%02d\n\
	"c_grey"Total time play:\t\t\t"c_white"%02d:%02d:%02d\n\
	"c_grey"Total AFK:\t\t\t"c_white"%02d:%02d:%02d",

	otarget, (IsPlayerConnected(GetPlayerID(otarget))) ? ""c_green"[Online]" : ""c_orange_red"[Offline]", oid,
	(!strcmp(ogoogle, "0", true, 33)) ? (""c_orange_red"Disabled") : (""c_green"Activated"),
	olvl,  oexp,(olvl+ 1)* 4, oage,
	get_player_warn_count_off(oid), ophone, opbalance, owanted,
	mm_gender[osex],
	job_data,
	fraction_data,
	rank_data,
	house_data,
	business_date,
	today_hours, today_minutes, today_seconds,
	today_afk_hours, today_afk_minutes, today_afk_seconds,
	hours, minutes, seconds,
	afk_hours, afk_minutes, afk_seconds);
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, !""scm_dialog"Player statistics", global_string, !"Bastan", !"");
}

stock get_player_warn_count_off(acc_id)
{
	new _warn_count = 0, query_string[78];
	format(query_string, sizeof(query_string), "SELECT * FROM `users_warns` WHERE `w_owner`='%d' AND `w_end` > NOW()", acc_id);
	new Cache:result = mysql_query(sql_connection, query_string);
	_warn_count = cache_num_rows();
	cache_delete(result);
	return _warn_count;
}

cmd:distributeghetto(playerid)
{
	if(check_admin_rank(playerid , 7)) return 1;

	new gangzone_id;

	for(new i = 0; i < sizeof gang_zones; i++)
	{
		for(new j = 0; j < sizeof gang_zones[]; j++)
		{
			gangzone_id = gang_zones[i][j] -1;
			gz_info[gangzone_id][gz_owner] = getFactionID(i + 18);
			HideZoneForAll(gz_info[gangzone_id][gz_created]);
			ShowZoneForAll(gz_info[gangzone_id][gz_created], GetGangZoneColor(gz_info[gangzone_id][gz_owner]));
			SaveGangZone(gangzone_id);
		}
	}

	AdminMes(""c_server"A.INFO:"c_grey" %s[%d] Tamami gang zone ha ra reset kard.", PlayerInfo[playerid][name], playerid);

	return SendAccess(playerid, "Tamami gang zone ha reset shod.");
}

cmd:distributemafia(playerid)
{
	if(check_admin_rank(playerid , 7)) return 1;

	new query_string[228], b;

	for(new i = 0; i < 3; i++)
	{
		for(new j = 0; j < b_count / 3; j++)
		{
			b = i * (b_count / 3) + j;

			b_info[b][b_mafia] = i + 23;

			UpdateBusinessEnterLabel(b);

			format(query_string, 118,"UPDATE `businesses` SET `b_mafia` = '%d' WHERE `b_id` = '%d' LIMIT 1", getFactionDBID(b_info[b][b_mafia]), b_info[b][b_id]);
			mysql_tquery(sql_connection, query_string);
		}
	}

	foreach(new i: admin_players) if(PlayerInfo[i][admin] >= 7) SendMes(i, col_gray, ""c_server"* A.INFO:"c_grey" %s[%d] distributed business between mafia", PlayerInfo[playerid][name], playerid);
	
	global_string[0] = EOS;

	return SendClientMessage(playerid, col_green, "All businesses are distributed");
}

cmd:banhistory(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Enter: /banhistory [name]");

	new scm_string[144];
	format(scm_string, sizeof scm_string, "SELECT * FROM `users_bans` WHERE `u_b_name` = '%s'", params[0]);
	mysql_tquery(sql_connection, scm_string, "banhistory_callback", "i", playerid);
	return 1;
}

callback: banhistory_callback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		global_string[0] = EOS;
		strcat(global_string, ""c_white"");
		for(new j = 0; j < rows; j ++)
		{
			new admin_name[MAX_PLAYER_NAME],
				warn_reason[32],
				warn_date[22], line_string[98];


			cache_get_field_content(j, "u_b_admin", admin_name, sql_connection, MAX_PLAYER_NAME);
			cache_get_field_content(j, "u_b_reason", warn_reason, sql_connection, 32);
			cache_get_field_content(j, "u_b_date", warn_date, sql_connection, 22);


			format(line_string, sizeof(line_string), "%s\t%s\t%s\n", warn_date, admin_name, warn_reason);
			strcat(global_string, line_string);
		}
		show_dialog(playerid, d_none, DIALOG_STYLE_LIST, !""scm_dialog"Block List", global_string, !"Bastan", !"");
	}
	if(!rows) return SendError(playerid, "Blocking info not found.");
	return 1;
}

cmd:mute(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "uds[42]", params[0], params[1], params[2]))
		return SendInfo(playerid, "Enter: /mute [id] [Daghighe] [Dalil]");
	if(!IsPlayerConnected(params[0]))
		return SendError(playerid, "Bazikon Yaft Nashod.");
	if(PlayerInfo[params[0]][mute] > 1)
		return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The player is already banned from chat.");
		
	if(params[0] != playerid && PlayerInfo[params[0]][admin] >= 5) return SendError(playerid, "You can't give him a punishment.");
		
	new scm_string[144];
	format(scm_string,sizeof(scm_string ), "Admin %s issued a chat ban for player %s for %d minutes. Reason: %s", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1], params[2]);
	foreach(new i: logged_players) if(PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, scm_string);

	format(scm_string,sizeof(scm_string),"UPDATE `users_admins` SET `u_a_mute` = `u_a_mute`+1 WHERE `u_a_name` = '%s' LIMIT 1", PlayerInfo[playerid][name]);
	mysql_tquery(sql_connection, scm_string, "", "");

	PlayerInfo[params[0]][mute] = params [1]*60;
	CallRemoteFunction("SV_RemoveVoice", "d", params[0]);
	return 1;
}

cmd:unmute(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0]))
		return SendInfo(playerid, "Enter: /unmute [id]");
	if(!IsPlayerConnected(params[0]))
		return SendError(playerid, "Bazikon Yaft Nashod.");
	if(PlayerInfo[params[0]][mute] == 0)
	    return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Player has no muta!");
	PlayerInfo[params[0]][mute] = 0;
	CallRemoteFunction("SV_AddVoice", "d", params[0]);
	
	SendAdmin("Admin %s Player %s ro az halat sokoot dar avord", PlayerInfo[playerid][name], PlayerInfo[params[0]][name]);
	return 1;
}

cmd:offmute(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	new
		mname[MAX_PLAYER_NAME],
		mtime,
		reason[32];
	if(sscanf(params, "s[24]ds[32]", mname, mtime, reason)) return SendInfo(playerid, "Enter: /offmute [id player] [Daghighe] [Dalil]");
	if(!(0 < mtime <= 180)) return SendError(playerid, "Mute time should not be less than 1 and more than 180 minutes.");

	new player = GetPlayerID(mname);
	
	if(IsPlayerConnected(player)) return SendError(playerid, "At the moment the player is online, use: /mute.");

	new sql_string[50 + MAX_PLAYER_NAME];
	format(sql_string, sizeof sql_string, "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", mname);
	mysql_tquery(sql_connection, sql_string, "offmute_check_callback", "isds", playerid, mname, mtime, reason);
	return 1;
}

cmd:mutelist(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	new rows_amount;
	foreach(new i: logged_players)
	{
		if(PlayerInfo[i][mute])
		{
			new scm_string[92];
			format(scm_string, sizeof(scm_string ), "%s[%i] | %d секунд(ы).", PlayerInfo[i][name], i, PlayerInfo[i][mute]);
			SendClientMessage(playerid, col_white, scm_string);
			rows_amount ++;
		}
	}
	new scm_string[48];
	format(scm_string, sizeof(scm_string ), "Igrocov Found: %d.", rows_amount);
	SendClientMessage(playerid, col_white, scm_string);
	return 1;
}

cmd:skick(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /skick [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	
	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] quietly kicked the player %s[%d].", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	kick_player(params[0]);
 	return 1;
}


cmd:offleaders(playerid)
{
    if(check_admin_rank(playerid , 4)) return 1;

    SetPVarInt(playerid, !"ofm_list_page", 1);
    mysql_tquery(sql_connection, "SELECT `u_name`,`u_last_date`,`u_leader` FROM `users` WHERE `u_leader` != '-1'", "callback_offleaders", "i", playerid);
    return 1;
}

callback: callback_offleaders(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
    if(!rows)
    {
        SendError(playerid, "Players with these parameters not found.");
        return DeletePVar(playerid, !"ofm_list_page");
    }

    new rows_list = GetPVarInt(playerid, !"ofm_list_page") -1;
    SetPVarInt(playerid, !"ofm_list_rows", rows);

    dlobal_string[0] = EOS;
    strcat(dlobal_string, ""c_grey"Previous page\n"c_grey"Next page\n"c_white"");
    for(new i = rows_list * 10; i < rows_list * 10 + 10; i ++)
    {
        if(i >= rows) break;

        new pl_ofm_name[24], pl_ofm_online[24], pl_leader;
        cache_get_field_content(i, "u_name", pl_ofm_name, sql_connection, 24);
        cache_get_field_content(i, "u_last_date", pl_ofm_online, sql_connection, 24);
        pl_leader = cache_get_field_content_int(i, "u_leader", sql_connection);

        new pvar_string[8];
        format(pvar_string, sizeof(pvar_string), "ofm_%d", i -rows_list * 10);
        SetPVarString(playerid, pvar_string, pl_ofm_name);

        new line_string[100];
        format(line_string, sizeof(line_string), ""c_white"%s -"c_silver"%s"c_white" -%s\n", pl_ofm_name, f_info[getFactionID(pl_leader)][f_name], pl_ofm_online);
        strcat(dlobal_string, line_string);
    }
    return show_dialog(playerid, d_offleaders, DIALOG_STYLE_LIST, !""scm_dialog"List of leaders", dlobal_string, !"Entekhab", !"Barghast");
}

callback: callback_offleaders_info(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new last_date[16], fraction_date[24], pl_leader;
		pl_leader = cache_get_field_content_int(0, "u_leader", sql_connection);
		cache_get_field_content(0, "u_last_date", last_date, sql_connection, 24);
		cache_get_field_content(0, "u_fraction_date", fraction_date, sql_connection, 24);

		new pvar_string[38], pl_name[MAX_PLAYER_NAME];
		format(pvar_string, sizeof(pvar_string), "ofm_%d", GetPVarInt(playerid, !"ofm_listitem"));
		GetPVarString(playerid, pvar_string, pl_name, MAX_PLAYER_NAME);

		new dialog_string[256];
		format(dialog_string, sizeof(dialog_string), ""c_white"Name: "c_server"%s\n"c_white"Organization: %s\n"c_white"At the post: "c_silver"%s\n"c_white"Last login: "c_silver"%s", pl_name, f_info[getFactionID(pl_leader)][f_name], fraction_date, last_date);
		show_dialog(playerid, d_offleaders_menu_info, DIALOG_STYLE_MSGBOX, !""scm_dialog"Player Information", dialog_string, !"Barghast", !"");
	}
	if(!rows)
	{
		DeletePVar(playerid, !"ofm_listitem");
		if(!GetPVarInt(playerid, !"ofm_type"))
		{
			mysql_tquery(sql_connection, "SELECT `u_name`,`u_last_date`,`u_leader` FROM `users` WHERE `u_leader` != '-1'", "callback_offamily", "i", playerid);
			return 1;
		}
	}
	return 1;
}

cmd:offadmins(playerid)
{
    if(check_admin_rank(playerid , 6)) return 1;

    SetPVarInt(playerid, !"ofm_list_page", 1);
    mysql_tquery(sql_connection, "SELECT `u_a_name`,`u_a_date`,`u_a_level` FROM `users_admins`", "callback_offadmins", "i", playerid);
    return 1;
}

callback: callback_offadmins(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows)
	{
		SendError(playerid, "Players with these parameters not found.");
		return DeletePVar(playerid, !"ofm_list_page");
	}

	new rows_list = GetPVarInt(playerid, !"ofm_list_page") -1;
	SetPVarInt(playerid, !"ofm_list_rows", rows);

	dlobal_string[0] = EOS;
	strcat(dlobal_string, ""c_grey"Previous page\n"c_grey"Next page\n"c_white"");
	for(new i = rows_list * 10; i < rows_list * 10 + 10; i ++)
	{
		if(i >= rows) break;

		new pl_ofm_name[24], pl_ofm_online[24], a_level;

		cache_get_field_content(i, "u_a_name", pl_ofm_name, sql_connection, 24);
		cache_get_field_content(i, "u_a_date", pl_ofm_online, sql_connection, 24);
		a_level = cache_get_field_content_int(i, "u_a_level", sql_connection);

		new pvar_string[8];
		format(pvar_string, sizeof(pvar_string), "ofm_%d", i -rows_list * 10);
		SetPVarString(playerid, pvar_string, pl_ofm_name);

		new line_string[80];
		format(line_string, sizeof(line_string), ""c_white"%s -"c_silver"%s level"c_white" -%s\n", pl_ofm_name, a_rank_name[a_level-1], pl_ofm_online);
		strcat(dlobal_string, line_string);
	}
	return show_dialog(playerid, d_offadmins, DIALOG_STYLE_LIST, !""scm_dialog"Administration List", dlobal_string, !"Entekhab", !"Barghast");
}

callback: callback_offadmins_info(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new pl_ofm_online[24], pl_ofm_issued[24], a_level, a_online, a_jails, a_csjails, a_warns, a_bans, a_kicks, a_mute;
		cache_get_field_content(0, "u_a_date", pl_ofm_online, sql_connection, 24);
		cache_get_field_content(0, "u_a_issued", pl_ofm_issued, sql_connection, 24);
		a_level = cache_get_field_content_int(0, "u_a_level", sql_connection);
		a_online = cache_get_field_content_int(0, "u_a_online", sql_connection);
		a_jails = cache_get_field_content_int(0, "u_a_jails", sql_connection);
		a_csjails = cache_get_field_content_int(0, "u_a_csjails", sql_connection);
		a_warns = cache_get_field_content_int(0, "u_a_warns", sql_connection);
		a_bans = cache_get_field_content_int(0, "u_a_bans", sql_connection);
		a_kicks = cache_get_field_content_int(0, "u_a_kicks", sql_connection);
		a_mute = cache_get_field_content_int(0, "u_a_mute", sql_connection);

		new pvar_string[38], pl_name[MAX_PLAYER_NAME];
		format(pvar_string, sizeof(pvar_string), "ofm_%d", GetPVarInt(playerid, !"ofm_listitem"));
		GetPVarString(playerid, pvar_string, pl_name, MAX_PLAYER_NAME);

		new dialog_string[600];

		format(dialog_string, sizeof(dialog_string), ""c_server"General Information:\n\n\
		"c_white"Yamya: "c_server"%s\n\
		"c_white"Level: %d\n"c_white"At checkout: "c_silver"%s\n\
		"c_white" Last login: "c_silver"%s\n\
		"c_white"Played at checkout: "c_gold"%s\n\n\
		"c_server" Penalties issued:\n\n \
		"c_white" Imprisoned: "c_silver"%d\n\
		"c_white" Cs Jail: "c_silver"%d\n\
		"c_white"Warning issued: "c_silver"%d\n\
		"c_white"Locked Accounts: "c_silver"%d\n\
		"c_white" Disabled Players: "c_silver "%d\n\
		"c_white"Chats blocked: "c_silver"%d\
		", pl_name, a_level, pl_ofm_issued, pl_ofm_online, convert_time(a_online), a_jails, a_csjails, a_warns, a_bans, a_kicks, a_mute);

		show_dialog(playerid, d_offadmins_menu_info, DIALOG_STYLE_MSGBOX, !""scm_dialog"Statistics Admin", dialog_string, !"Barghast", !"");
	}
	if(!rows)
	{
		DeletePVar(playerid, "ofm_listitem");
		if(!GetPVarInt(playerid, "ofm_type"))
		{
			mysql_tquery(sql_connection, "SELECT `u_a_name`,`u_a_date`,`u_a_level` FROM `users_admins`", "callback_offadmins", "i", playerid);
			return 1;
		}
	}
	return 1;
}

cmd:offstats(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Enter: /offstats [имя]");
	new query_string[80 + MAX_PLAYER_NAME];
	format(query_string, sizeof query_string, "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", params[0]);
	mysql_tquery(sql_connection, query_string, "offstats_callback", "i", playerid);
 	return 1;
}


callback: offstats_callback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows)
	{
		SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"This account was not found in the database.");
		return 1;
	}
	else
	{
		new gs_id,
			gs_name[MAX_PLAYER_NAME],
			gs_level,
			gs_exp,
			gs_number,
			gs_phone_money,
			gs_suspect,
			gs_gender,
			gs_job,
			gs_member,
			gs_rank,
			gs_house,
			gs_business;


		cache_get_field_content(0, "u_name", gs_name, sql_connection, MAX_PLAYER_NAME);

		gs_id = cache_get_field_content_int(0, "u_id", sql_connection);
		gs_level = cache_get_field_content_int(0, "u_level", sql_connection);
		gs_exp = cache_get_field_content_int(0, "u_exp", sql_connection);
		gs_number = cache_get_field_content_int(0, "u_number", sql_connection);
		gs_phone_money = cache_get_field_content_int(0, "u_phone_balance", sql_connection);
		gs_suspect = cache_get_field_content_int(0, "u_wanted", sql_connection);
		gs_gender = cache_get_field_content_int(0, "u_gender", sql_connection);
		gs_job = cache_get_field_content_int(0, "u_job", sql_connection);
		gs_member = cache_get_field_content_int(0, "u_member", sql_connection);
		gs_rank = cache_get_field_content_int(0, "u_rank", sql_connection);
		gs_house = cache_get_field_content_int(0, "u_house", sql_connection);
		gs_business = cache_get_field_content_int(0, "u_business", sql_connection);

		static const mm_gender[][] = {
		"Mard",
		"Zan"};

		new house_data[12];
		if(gs_house != -1)format(house_data, sizeof(house_data), "house # %d", gs_house);
		else format(house_data, sizeof(house_data), "missing");
		new business_date[32];
		if(gs_business != -1)format(business_date, 32, "%s", b_info[gs_business -1][b_name]);
		else format(business_date, 32, "missing");

		new job_data[22];
		if(gs_job != 0 && gs_job < 50)format(job_data, sizeof(job_data), "%s", jobs_name[gs_job -1]);
		else format(job_data, sizeof(job_data), "missing");
		new fraction_data[32];
		if(gs_member) format(fraction_data, sizeof(fraction_data), "%s", f_info[getFactionID(gs_member)][f_name]);
		else format(fraction_data, sizeof(fraction_data), "missing");
		new rank_data[32];
		if(gs_rank)format(rank_data, sizeof(rank_data), "%s", f_rank[gs_member -1][gs_rank -1]);
		else format(rank_data, sizeof(rank_data), "missing");




		format(global_string, 1028, "\
		"c_grey"Yamya:\t\t\t\t"c_white"%s\n\
		"c_grey"Account number:\t\t"c_white"%d\n\
		"c_grey"Level:\t\t\t"c_white"%d\n\
		"c_grey"XP:\t\t\t"c_white"%d from %d\n\
		"c_grey"Phone number:\t\t"c_white"%d\n\
		"c_grey"On phone account:\t\t"c_white"%d\n\n\
		"c_grey"Search Level:\t\t"c_white"%d\n\n\
		"c_grey"Prin:\t\t\t\t"c_white"%s\n\
		"c_grey"Working:\t\t\t"c_white"%s\n\
		"c_grey" Organization:\t\t\t"c_white"%s\n\
		"c_grey"Ran:\t\t\t\t"c_white"%s\n\
		"c_grey"Residence:\t\t\t"c_white"%s\n\
		"c_grey"Business:\t\t\t"c_white"%s\n\n",

		gs_name,
		gs_id,
		gs_level,
		gs_exp,(gs_level + 1)* 4,
		gs_number,
		gs_phone_money,

		gs_suspect,

		mm_gender[gs_gender],
		job_data,
		fraction_data,
		rank_data,
		house_data,
		business_date);
		show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Player statistics", global_string, "Bastan", "");
	}
	return 1;
}

cmd:get(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /get [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	new query_string[80 + MAX_PLAYER_NAME];
	format(query_string, sizeof query_string, "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", PlayerInfo[params[0]][name]);
	mysql_tquery(sql_connection, query_string, "get_callback", "i", playerid);
 	return 1;
}

cmd:getip(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /getip [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	AdminMes(""c_server"* A.INFO: "c_grey"Nickname: %s | IP: %s", PlayerInfo[params[0]][name], p_t_info[params[0]][p_ip]);

 	return 1;
}

cmd:offget(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Enter: /offget [имя]");
	new query_string[80 + MAX_PLAYER_NAME];
	format(query_string, sizeof query_string, "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", params[0]);
	mysql_tquery(sql_connection, query_string, "get_callback", "i", playerid);
 	return 1;
}

cmd:teleport(playerid)
{
	if(check_admin_rank(playerid , 1)) return 1;
	return show_dialog(playerid, d_tp, DIALOG_STYLE_LIST, !""scm_dialog"Teleportation", !""c_server"1 | "c_white"Basic organization\n"c_server"2 | "c_white"Work\n"c_server"3 | "c_white"Newbies\n"c_server"4 | "c_white"Licensing Centers\n"c_server"5 | "c_white"Important Places\n"c_server"6 | "c_white"Transport", !"Select", !"Close");
}

callback: get_callback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	
	if(!rows) return SendError(playerid, "This account was not found in the database.");

	if(rows)
	{
		new gs_name[MAX_PLAYER_NAME], gs_increment, gs_regdate[26], gs_money, gs_bank, gs_level, gs_regip[16], gs_lastip[16], gs_lastdate[16], gs_donate, country[32], lastcountry[32], city[32], lastcity[32], provider[32], lastprovider[32], regmail[50];
		cache_get_field_content(0, "u_name", gs_name, sql_connection, MAX_PLAYER_NAME);
		cache_get_field_content(0, "u_ip_registration", gs_regip, sql_connection, MAX_PLAYER_NAME);
		cache_get_field_content(0, "u_last_ip", gs_lastip, sql_connection, MAX_PLAYER_NAME);
		cache_get_field_content(0, "u_date_registration", gs_regdate, sql_connection, MAX_PLAYER_NAME);
		cache_get_field_content(0, "u_last_date", gs_lastdate, sql_connection, MAX_PLAYER_NAME);

		gs_increment = cache_get_field_content_int(0, "u_id", sql_connection);
		gs_money = cache_get_field_content_int(0, "u_money", sql_connection);
		gs_level = cache_get_field_content_int(0, "u_level", sql_connection);
		gs_donate = cache_get_field_content_int(0, "u_donate", sql_connection);
		cache_get_field_content(0, "u_email", regmail, sql_connection);

		if(get_player_admin_level(gs_name) > 6) return SendError(playerid, "You can't view the chapter data. administration.");

		GetIPCountry(gs_regip, country, sizeof(country));
		GetIPCountry(gs_lastip, lastcountry, sizeof(lastcountry));
		GetIPCity(gs_regip, city, sizeof(city));
		GetIPCity(gs_lastip, lastcity, sizeof(lastcity));
		GetIPISP(gs_regip, provider, sizeof(provider));
		GetIPISP(gs_lastip, lastprovider, sizeof(lastprovider));

		global_string[0] = EOS;
		new pvar_string[16];

		if(gs_money > 1800000000 || gs_money < -1800000000) gs_money = 1800000000;
		if(gs_bank > 1800000000 || gs_bank < -1800000000) gs_money = 1800000000;

		strcat(global_string, ""c_server"Player information:");

        strcat(global_string, "\n\n"c_white"Account number: "c_silver"");
        valstr(pvar_string, gs_increment);
        strcat(global_string, pvar_string);
        strcat(global_string, "\n"c_white"Normal: "c_green"");
        valstr(pvar_string, gs_money);
        strcat(global_string, pvar_string);
        strcat(global_string, "$");
        strcat(global_string, "\n"c_white"Primary string: "c_green"");
        valstr(pvar_string, gs_bank);
        strcat(global_string, pvar_string);
        strcat(global_string, "$");
        strcat(global_string, "\n"c_white"Level: ");
        valstr(pvar_string, gs_level);
        strcat(global_string, pvar_string);
        strcat(global_string, "\n"c_white" Return: ");
        valstr(pvar_string, gs_donate);
        strcat(global_string, pvar_string);
        strcat(global_string, "\n"c_white"Print: ");
        strcat(global_string, isnull(regmail) ? "not specified" : regmail);

		strcat(global_string, "\n\n"c_server"Open accounts:");

		new bank_count = 0, query_string[156];
		format(query_string, sizeof(query_string), "SELECT * FROM `deposit_boxes` WHERE `db_owner`='%d' LIMIT 10", gs_increment);
		mysql_query(sql_connection, query_string);

		new Cache:result = mysql_query(sql_connection, query_string);
		bank_count = cache_num_rows();
		
		if(bank_count)
		{
			for(new j = 0; j < bank_count; j++)
			{
				new _db_id, _db_money;
				_db_id = cache_get_field_content_int(j, "db_id", sql_connection);
				_db_money = cache_get_field_content_int(j, "db_money", sql_connection);

				if(_db_money > 1800000000 || _db_money < -1800000000) _db_money = 1800000000;

				new _db_name[32];
				cache_get_field_content(j, "db_name", _db_name, sql_connection, 32);

				strcat(global_string, "\n"c_white"");
				strcat(global_string, _db_name);

				strcat(global_string, "[#");
				valstr(pvar_string, _db_id);
				strcat(global_string, pvar_string);
				strcat(global_string, "] -");
				strcat(global_string, ""c_green"");
				valstr(pvar_string, _db_money);
				strcat(global_string, pvar_string);
				strcat(global_string, "$");
			}
		}
		else strcat(global_string, "\n"scm_error"The player has no open bank accounts.");
		cache_delete(result);

        strcat(global_string, "\n\n"c_white"IP address(registration.): "c_server"");
        strcat(global_string, gs_regip);
        strcat(global_string, "\n"c_white"IP address(next): "c_server"");

		strcat(global_string, gs_lastip);

        strcat(global_string, "\n\n"c_white"Registration data: "c_server"");
        strcat(global_string, gs_regdate);
        strcat(global_string, "\n"c_white"Last Date: "c_server"");
        strcat(global_string, gs_lastdate);

		strcat(global_string, "\n\n"c_server"Technical information of the player:");

        strcat(global_string, "\n\n"c_white"Country when registering: "c_server" ");
        strcat(global_string, country);
        strcat(global_string, "\n"c_white"Country on last login: "c_server"");
        strcat(global_string, lastcountry);
        strcat(global_string, "\n"c_white"City on registration: "c_server"");
        strcat(global_string, city);
        strcat(global_string, "\n"c_white"City on last login: "c_server"");
        strcat(global_string, lastcity);
        strcat(global_string, "\n"c_white"Registration provider: "c_server"");
        strcat(global_string, provider);
        strcat(global_string, "\n"c_white"Provider last login: "c_server"");
        strcat(global_string, lastprovider);

		new header_string[45];
		format(header_string, sizeof(header_string), ""scm_dialog"%s", gs_name);
		show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, header_string, global_string, "Bastan", "");

		if(PlayerInfo[playerid][admin] < 7)
		{
			AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] view player information %s", PlayerInfo[playerid][name], playerid, gs_name);
		}
	}
	return 1;
}

cmd:ban(playerid, params[])
{
    if (check_admin_rank(playerid, 3)) return 1;

    if (sscanf(params, "uds[42]", params[0], params[1], params[2]))
        return SendInfo(playerid, "Enter: /ban [id/name] [number of days] [reason]");

    if (!IsPlayerConnected(params[0]))
        return SendError(playerid, "Bazikon Yaft Nashod.");

    if (params[1] < 1 || params[1] > 30)
        return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Only allowed to ban from 1 to 30 days.");

    if (PlayerInfo[params[0]][admin] >= 5)
        return SendError(playerid, "You can't give him a punishment.");

    new timestamp_x = timestamp_x + (params[1] * 86400);
    new year, month, day, hour, minute, second;
    TimestampToDate(timestamp_x, year, month, day, hour, minute, second, 3, 30);

    new text_date[70];
    format(text_date, sizeof(text_date), "%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

    new scm_string[248];
    format(scm_string, sizeof(scm_string), "Admin %s banned player %s for %d days. Reason: %s",
        PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1], params[2]);
    foreach (new i: logged_players)
        if (PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, scm_string);

    AdminMes(""c_server"* A.INFO: %s[%d] for %d days. Reason: %s | IP: %s", PlayerInfo[params[0]][name], params[0], params[1], params[2], p_t_info[params[0]][p_ip]);

    RunQuery("INSERT INTO `users_bans` (`u_b_admin`,`u_b_name`,`u_b_reason`,`u_b_ndate`,`u_b_days`,`u_b_expire`) VALUES ('%s', '%s', '%e', NOW(), '%d', '%d')", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[2], params[1], timestamp_x);

    RunQuery("UPDATE `users_admins` SET `u_a_bans`=`u_a_bans`+1 WHERE `u_a_name`='%s' LIMIT 1", PlayerInfo[playerid][name]);

    format(global_string, sizeof global_string,"\
        "c_orange_red"Account Shoma be dalil adam raayat ghavanin ban mibashad.\n\n\
        "c_grey"* Lotfan az safhe screenshot bgirid (F8).\n\
        "c_grey"Agar ba mojazat taeein shode movafeg nistid mitavanid ba admin marboot ertebat begirid.\n\n\
        "c_server"* "c_grey"Esm Account: "c_white"%s\n\
        "c_server"* "c_grey"Esm Admin: "c_white"%s\n\
        "c_server"* "c_grey"Zamani ke ban shodid: "c_white"Halan\n\
        "c_server"* "c_grey"Zaman Unban: "c_white"%s (%d days)\n\
        "c_server"* "c_grey"Dalil: "c_white"%s\n",
        PlayerInfo[params[0]][name], PlayerInfo[playerid][name], text_date, params[1], params[2]);

    show_dialog(params[0], d_none, DIALOG_STYLE_MSGBOX, ""c_server"Blocking information", global_string, "Bastan", "");

    kick_player(params[0]);
    return 1;
}

cmd:pban(playerid, params[])
{
    if (check_admin_rank(playerid, 7)) return 1;

    if (sscanf(params, "us[42]", params[0], params[1]))
        return SendInfo(playerid, "Enter: /pban [id/name] [reason]");

    if (!IsPlayerConnected(params[0]))
        return SendError(playerid, "Bazikon Yaft Nashod.");

    if (PlayerInfo[params[0]][admin] >= 5)
        return SendError(playerid, "You can't give him a punishment.");

    new scm_string[248];
    format(scm_string, sizeof(scm_string), "Admin %s permanently banned player %s. Reason: %s",
        PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1]);
    foreach (new i: logged_players)
        if (PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, scm_string);

    AdminMes(""c_server"* A.INFO: %s[%d] permanent banned. Reason: %s | IP: %s", PlayerInfo[params[0]][name], params[0], params[1], p_t_info[params[0]][p_ip]);

    RunQuery("INSERT INTO `users_bans` (`u_b_admin`,`u_b_name`,`u_b_reason`,`u_b_ndate`,`u_permanet_ban`) VALUES ('%s','%s','%e',NOW(),1)", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1]);

    RunQuery("UPDATE `users_admins` SET `u_a_bans`=`u_a_bans`+1 WHERE `u_a_name`='%s' LIMIT 1", PlayerInfo[playerid][name]);

    format(global_string, sizeof global_string,"\
        "c_orange_red"Account Shoma permanently ban shod.\n\n\
        "c_grey"* Lotfan az safhe screenshot bgirid (F8).\n\n\
        "c_server"* "c_grey"Esm Account: "c_white"%s\n\
        "c_server"* "c_grey"Esm Admin: "c_white"%s\n\
        "c_server"* "c_grey"Zamani ke ban shodid: "c_white"Halan\n\
        "c_server"* "c_grey"Zaman Unban: "c_white"Hichvaght\n\
        "c_server"* "c_grey"Dalil: "c_white"%s\n",
        PlayerInfo[params[0]][name], PlayerInfo[playerid][name], params[1]);

    show_dialog(params[0], d_none, DIALOG_STYLE_MSGBOX, ""c_server"Blocking information", global_string, "Bastan", "");

    kick_player(params[0]);
    return 1;
}

cmd:offban(playerid, params[])
{
    if (check_admin_rank(playerid, 3)) return 1;

    new offb_reason[42], offb_name[24], offb_day;

    if (sscanf(params, "s[24]ds[42]", offb_name, offb_day, offb_reason))
        return SendInfo(playerid, "Enter: /offban [name] [number of days] [reason]");

    if (offb_day < 1 || offb_day > 300)
        return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"hadaghal bin 1 rooz ta 300 rooz bashe.");

    new scm_string[128];
    format(scm_string, sizeof(scm_string), "SELECT * FROM `users` WHERE `u_name`='%s' LIMIT 1", offb_name);
    mysql_tquery(sql_connection, scm_string, "offban_check_callback", "isds", playerid, offb_name, offb_day, offb_reason);

    return 1;
}

cmd:sban(playerid, params[])
{
    if (check_admin_rank(playerid, 4)) return 1;

    if (sscanf(params, "uds[32]", params[0], params[1], params[2]))
        return SendInfo(playerid, "Enter: /sban [id] [number of days] [reason]");

    if (!IsPlayerConnected(params[0]))
        return SendError(playerid, "Bazikon Yaft Nashod.");

    if (params[1] < 1 || params[1] > 300)
        return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"hadaghal bin 1 rooz ta 300 rooz bashe.");

    AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] silently banned player %s[%d] for %d days. Reason: %s", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0], params[1], params[2]);

    RunQuery("INSERT INTO `users_bans` (`u_b_admin`,`u_b_name`,`u_b_reason`,`u_b_ndate`,`u_b_days`,`u_b_expire`) VALUES ('%s','%s','%e',NOW(),'%d','%d')", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[2], params[1], timestamp + (params[1] * 86400));

    RunQuery("UPDATE `users_admins` SET `u_a_bans`=`u_a_bans`+1 WHERE `u_a_name`='%s' LIMIT 1", PlayerInfo[playerid][name]);

    new timestamp_x = timestamp_x + (params[1] * 86400);
    new year, month, day, hour, minute, second;
    TimestampToDate(timestamp_x, year, month, day, hour, minute, second, 3, 30);

    new text_date[70];
    format(text_date, sizeof(text_date), "%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);

    format(global_string, sizeof global_string,"\
        "c_orange_red"Account Shoma be dalil adam raayat ghavanin ban mibashad.\n\n\
        "c_grey"* Lotfan az safhe screenshot bgirid (F8).\n\n\
        "c_server"* "c_grey"Esm Account: "c_white"%s\n\
        "c_server"* "c_grey"Esm Admin: "c_white"%s\n\
        "c_server"* "c_grey"Zamani ke ban shodid: "c_white"Halan\n\
        "c_server"* "c_grey"Zaman Unban: "c_white"%s (%d days)\n\
        "c_server"* "c_grey"Dalil: "c_white"%s\n",
        PlayerInfo[params[0]][name], PlayerInfo[playerid][name], text_date, params[1], params[2]);

    show_dialog(params[0], d_none, DIALOG_STYLE_MSGBOX, ""c_server"Blocking information", global_string, "Bastan", "");

    kick_player(params[0]);
    return 1;
}

cmd:weather(playerid, params[])
{
	if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /weather [id]");
	if(params[0] < 0|| params[0] > 45) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Weather ID cannot be less than 0 and greater than 45.");
	global_weather = params[0];
	SetWeather(params[0]);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] changed the weather for %d.", PlayerInfo[playerid][name], playerid, params[0]);

	return 1;
}

cmd:deletegun(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /deletegun [radius]");
	if(params[0] < 0 || params[0] > 70) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Radius less than 0 and greater than 70.");

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] took a weapon within a radius of %d meters around him.", PlayerInfo[playerid][name], playerid, params[0]);

	foreach(new i:streamed_players[playerid])
	{
		if(IsPlayerInRangeOfPoint(i, Float:params[0], p_t_info[i][p_pos][0], p_t_info[i][p_pos][1], p_t_info[i][p_pos][2]) && GetPlayerVirtualWorld(i) ==  GetPlayerVirtualWorld(playerid))
		{
			reset_player_weapon(i);
		}
	}
	return 1;
}

cmd:unban(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Enter:/unban [Player Name]");
	new query_string[144];
	mysql_format(sql_connection, query_string, sizeof(query_string ), "SELECT `u_b_name` FROM `users_bans` WHERE `u_b_name` = '%s' LIMIT 1", params[0]);
	mysql_tquery(sql_connection, query_string, "unban_callback", "is", playerid, params[0]);
	return 1;
}

cmd:plveh(playerid, params[])
{
    if(check_admin_rank(playerid , 4)) return 1;

    new tid, vehicle_id, color_1, color_2;
	if(sscanf(params, "udI(-1)I(-1)", tid, vehicle_id, color_1, color_2)) return SendInfo(playerid, "Enter: /plveh [id Bazikon] [vehicle id] [color 1] [color 2]");

	if(color_1 == -1) color_1 = random(255);
	if(color_2 == -1) color_2 = random(255);

	if(!(400 < vehicle_id < 611) || !(0 <= color_1 <= 255) || !(0 <= color_2 <= 255)) return SendInfo(playerid, "Enter: /plveh [id Bazikon] [id transport] [color 1] [color 2]");

	// if(GetPVarInt(tid, !"admin_vehicle")) return SendClientMessage(playerid, col_white, !"A temporary car has already been created for this player. Delete to start with /delveh");

	new veh_id_temporary = GetPVarInt(tid, !"admin_vehicle");
	if(veh_id_temporary)
	{
		DestroyVehicle(veh_id_temporary);
	}

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z;
	GetPlayerPos(tid, pl_pos_X, pl_pos_Y, pl_pos_Z);
	new adm_veh = CreateVehicle(vehicle_id, pl_pos_X, pl_pos_Y, pl_pos_Z, 0.0, color_1, color_2, -1);
	SetPVarInt(tid, !"admin_vehicle", adm_veh);

	veh_info[adm_veh -1][v_fuel] = 100.0;

	LinkVehicleToInterior(adm_veh, GetPlayerInterior(tid));
	SetVehicleVirtualWorld(adm_veh, GetPlayerVirtualWorld(tid));

	PutPlayerInVehicle(tid, adm_veh, 0);
	SetPlayerArmedWeapon(tid, 0);

	AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] created a transport for %s[%d]. ID: %d | Model: %d", PlayerInfo[playerid][name], playerid, PlayerInfo[tid][name], tid, adm_veh, vehicle_id);

	if(playerid != tid) SendClientMessage(tid, col_green, !"Admin gave you a car");
	return true;
}

cmd:delveh(playerid, params[])
{
    if(check_admin_rank(playerid , 4)) return 1;

	extract params -> new player:tid; else return SendInfo(playerid, "Enter: /delveh [id player]");
	if(!GetPVarInt(tid, !"admin_vehicle")) return SendError(playerid, "No vehicle has been created for this player");

	new veh_id = GetPVarInt(tid, !"admin_vehicle");
	DestroyVehicle(veh_id);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] removed transport %s[%d]. ID: %d", PlayerInfo[playerid][name], playerid, PlayerInfo[tid][name], tid, veh_id);

	if(playerid != tid) SendClientMessage(tid, col_gray, "Admin deleted your car");

	return DeletePVar(playerid, !"admin_vehicle");
}

cmd:givedonate(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "ud", params[0], params[1])) return SendInfo(playerid, "Enter: /givedonate [id] [amount of donation]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(params[1] < 1 || params[1] > 100000) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Amount of donation must be from 1 to 100000.");
	give_donate(params[0], params[1]);
	new text_string[120];
	format(text_string, sizeof(text_string), ""c_server"* S.INFO: "c_grey"Admin %s[%d] gave you a donation in the amount %d \"M-COINS\"", PlayerInfo[playerid][name], playerid, params[1]);
	SendClientMessage(params[0], -1, text_string);
	format(text_string, sizeof(text_string), ""c_server"* S.INFO: "c_grey"You donated %d \"M-COINS\" to the player %s[%d]", params[1], PlayerInfo[params[0]][name], params[0]);
	SendClientMessage(params[0], -1, text_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] issued %d \"M-COINS\" to the player %s[%d]", PlayerInfo[playerid][name], playerid, params[1], PlayerInfo[params[0]][name], params[0]);

	insert_donate_log(params[0], playerid, params[1]);
	return 1;
}

cmd:givemoney(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "ud", params[0], params[1])) return SendInfo(playerid, "Enter: /givemoney [id] [amount]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	give_money(params[0], params[1]);
	new text_string[120];
	format(text_string, sizeof(text_string), ""c_server"* S.INFO: "c_grey"Admin %s[%d] gave you $%d money", PlayerInfo[playerid][name], playerid, params[1]);
	SendClientMessage(params[0], -1, text_string);
	format(text_string, sizeof(text_string), ""c_server"* S.INFO: "c_grey"You gave $%d money to the player %s[%d]", params[1], PlayerInfo[params[0]][name], params[0]);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] issued $%d money to the player %s[%d]", PlayerInfo[playerid][name], playerid, params[1], PlayerInfo[params[0]][name], params[0]);
	
	new moneylog_string[62];
	format(moneylog_string, sizeof(moneylog_string), "admin %s[%d] gave $%d to %s[%d]", PlayerInfo[playerid][name], playerid, params[1], PlayerInfo[params[0]][name], params[0]);
	insert_money_log(playerid, params[0], params[1], moneylog_string);
	return 1;
}

cmd:saveall(playerid)
{
	if(check_admin_rank(playerid , 8)) return 1;
	new _sql_string[156];

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '1' LIMIT 1", dorm_count[DORM_SAWMILL]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '2' LIMIT 1", dorm_count[DORM_MINE]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '3' LIMIT 1", dorm_count[DORM_FACTORY_GUNS]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '4' LIMIT 1", mine_count[MINE_MELTED]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '5' LIMIT 1", mine_count[MINE_UNMELTED]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '6' LIMIT 1", dorm_count[DORM_FACTORY_MINE]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '7' LIMIT 1", dorm_count[DORM_FACTORY_WOOD]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '8' LIMIT 1", election_status);
	mysql_query(sql_connection, _sql_string);

	for(new h = 0; h < house_count; h ++)
	{
		format(_sql_string, 112, "UPDATE `houses` SET `h_seed` = '%d',`h_seed_result` = '%d' WHERE `h_id` = '%d' LIMIT 1", h_info[h][h_seed], h_info[h][h_seed_result], h_info[h][h_id]);
		mysql_query(sql_connection, _sql_string);
	}

	for(new t = 0; t < b_count; t ++)
	{
		format(_sql_string, 156, "UPDATE `businesses` SET `b_product` = '%d',`b_cost` = '%d',`b_money` = '%d' WHERE `b_id` = '%d' LIMIT 1",
		b_info[t][b_product], b_info[t][b_cost], b_info[t][b_money], b_info[t][b_id]);
		mysql_query(sql_connection, _sql_string);
	}

	AdminMes(""c_server"* A.INFO: "c_grey"Admin %s saved all server information.", PlayerInfo[playerid][name]);

	return 1;
}

cmd:rr(playerid)
{
	if(check_admin_rank(playerid , 8)) return 1;

	SendClientMessageToAll(col_yellow, "Server Restart shod bad channd sanie dobare vared shavid.");
	for(new i = 0; i < MAX_PLAYERS; i ++)
	{
		kick_player(i);
	}

	new _sql_string[156];

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '1' LIMIT 1", dorm_count[DORM_SAWMILL]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '2' LIMIT 1", dorm_count[DORM_MINE]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '3' LIMIT 1", dorm_count[DORM_FACTORY_GUNS]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '4' LIMIT 1", mine_count[MINE_MELTED]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '5' LIMIT 1", mine_count[MINE_UNMELTED]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '6' LIMIT 1", dorm_count[DORM_FACTORY_MINE]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '7' LIMIT 1", dorm_count[DORM_FACTORY_WOOD]);
	mysql_query(sql_connection, _sql_string);

	format(_sql_string, 112, "UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '8' LIMIT 1", election_status);
	mysql_query(sql_connection, _sql_string);

	for(new h = 0; h < house_count; h ++)
	{
		format(_sql_string, 112, "UPDATE `houses` SET `h_seed` = '%d',`h_seed_result` = '%d' WHERE `h_id` = '%d' LIMIT 1", h_info[h][h_seed], h_info[h][h_seed_result], h_info[h][h_id]);
		mysql_query(sql_connection, _sql_string);
	}

	for(new t = 0; t < b_count; t ++)
	{
		b_info[t][b_cash_today] = 0;
		format(_sql_string, 156, "UPDATE `businesses` SET `b_product` = '%d',`b_cost` = '%d',`b_money` = '%d' WHERE `b_id` = '%d' LIMIT 1",
		b_info[t][b_product], b_info[t][b_cost], b_info[t][b_money], b_info[t][b_id]);
		mysql_query(sql_connection, _sql_string);
	}

	for(new j = 0; j < fraction_count; j ++)
	{
		format(_sql_string, 146, "UPDATE `fractions` SET `f_money` = '%d',`f_materials`='%d',`f_guns` = '%d' WHERE `f_id` = '%d' LIMIT 1",
		f_info[j][f_money], f_info[j][f_materials], f_info[j][f_guns], f_info[j][f_id]);
		mysql_tquery(sql_connection, _sql_string, "", "");
	}
	SendRconCommand("gmx");
	return 1;
}

cmd:spawn(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /spawn [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	set_health(params[0], 100);
	SpawnPlayer(params[0]);
	new scm_string[128];
	format(scm_string, sizeof(scm_string),""c_server"* S.INFO: "c_grey"Admin %s[%i] brought you back to the surface.", PlayerInfo[playerid][name], playerid);
	SendClientMessage(params[0], col_gray, scm_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] conservation %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	return 1;
}

cmd:spcartime(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "d", params[0])) return SendError(playerid, "Enter: /spcartime [seconds]");
	
	if(params[0] < 0 || params[0] > 60) return SendError(playerid, "От 1 to 60 секунд.");
	
	new scm_string[128];
	format(scm_string, sizeof(scm_string), "* S.INFO: Warning, Baad Az %d Sanie Mashin Haye Bi Sar Nashin Pak Mishavand.", params[0]);
 	foreach(new i: logged_players) SendClientMessage(i, 0xEBC826FF, scm_string);
 	
	params[0] = params[0]* 1000;
	
	SetTimer("spawn_cars", params[0], false);
	
	return 1;
}

cmd:spcar(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /spcar [radius]");
	if(params[0] < 1 || params[0] > 5000) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Forbidden below 1 or more 5000.");

	for(new i = 0; i < MAX_VEHICLES; i++)
	{
		if(veh_info[i][v_deleted] == 1) continue;
		if(!IsValidVehicle(i)) continue;
		if(GetVehicleModel(i) ==  450) continue;

		new Float:v_pos_x,
			Float:v_pos_y,
			Float:v_pos_z;
		GetVehiclePos(i, v_pos_x, v_pos_y, v_pos_z);

		if(!IsPlayerInRangeOfPoint(playerid, params[0], v_pos_x, v_pos_y, v_pos_z)) continue;
		SetVehicleToRespawn(i);
	}

	AdminMes(""c_server"* A.INFO: "c_grey"Admin %s updated transport in radius %d m.", PlayerInfo[playerid][name], params[0]);

	return 1;
}

cmd:spcarid(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /spcarid [auto ID]");
	if(params[0] < 1 || params[0] > MAX_VEHICLES) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Invalid transport id.");
	if(!IsValidVehicle(params[0])) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Invalid transport id.");
	if(is_vehicle_occupied(params[0]) != -1) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Cannot recall a busy car.");
	SetVehicleToRespawn(params[0]);

	AdminMes(""c_server"* A.INFO: "c_grey"Admin %s updated transport | ID: %d", PlayerInfo[playerid][name], params[0]);

	return 1;
}

cmd:okay(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /okay [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(GetString(change_name[params[0]], "none")) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"I did not leave an application for a name change.");

	new query_string[80 + MAX_PLAYER_NAME];
	format(query_string, sizeof query_string, "SELECT `u_id` FROM `users` WHERE `u_name` = '%s' LIMIT 1", change_name[params[0]]);
	mysql_tquery(sql_connection, query_string, "changename_callback", "ii", playerid, params[0]);

	return 1;
}

cmd:gotopos(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	
	new Float:g_x,
		Float:g_y,
		Float:g_z,
		int_id;

	if(sscanf(params, "p<,>fffd", g_x, g_y, g_z, int_id)) return SendInfo(playerid, "Enter: /gotopos [x] [y] [z] [interior]");
	set_pos(playerid, g_x, g_y, g_z, 0.0, int_id, 0);
	SendAccess(playerid, "You have teleported to the indicated coordinates.");
	return 1;
}
alias:gotopos("tpcoord");

cmd:createarea(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	GetPlayerFacingAngle(playerid, p_t_info[playerid][p_pos][3]);
	for(new i = 0; i < 4; i ++)
	{
		new pvar_string[28];
		format(pvar_string, sizeof(pvar_string ), "area_pos_%d", i);
		SetPVarFloat(playerid, pvar_string, p_t_info[playerid][p_pos][i]);
	}
	SendClientMessage(playerid, col_lblue, "Proceed to the next stage of creation ((/endarea))");
	return 1;
}

cmd:endarea(playerid, params[])
{
	if(check_admin_rank(playerid , 6)) return 1;
	if(area_amount >= sizeof(area_info)) return SendClientMessage(playerid, col_white, "Error creating teleport. Exit limits area_info.");
	if(sscanf(params, "dddds[32]", params[0], params[1], params[2], params[3], params[4])) return SendClientMessage(playerid, col_gray,"Enter: /endarea [virtual_world] [interior] [to_vw] [to_int] [Name]");
	GetPlayerFacingAngle(playerid, p_t_info[playerid][p_pos][3]);
	area_amount ++;
	area_info[area_amount -1][a_id] = area_amount + 1;
	for(new i = 0; i < 4; i ++)
	{
		new pvar_string[28];
		format(pvar_string, sizeof(pvar_string ), "area_pos_%d", i);
		area_info[area_amount -1][a_pos][i] = GetPVarFloat(playerid, pvar_string);
		DeletePVar(playerid, pvar_string);
		area_info[area_amount -1][a_to_pos][i] = p_t_info[playerid][p_pos][i];
	}

	area_info[area_amount -1][a_pick] = 1318;
	area_info[area_amount -1][a_virt_world][0] = params[0];
	area_info[area_amount -1][a_virt_world][1] = params[2];

	area_info[area_amount -1][a_interior][0] = params[1];
	area_info[area_amount -1][a_interior][1] = params[3];

	area_info[area_amount -1][a_area][0] = CreateDynamicPickup(1318, 23, area_info[area_amount -1][a_pos][0 ], area_info[area_amount -1][a_pos][1 ], area_info[area_amount -1][a_pos][2 ], area_info[area_amount -1][a_virt_world][0]);
	area_info[area_amount -1][a_area][1] = CreateDynamicPickup(1318, 23, area_info[area_amount -1][a_to_pos][0 ], area_info[area_amount -1][a_to_pos][1 ], area_info[area_amount -1][a_to_pos][2 ], area_info[area_amount -1][a_virt_world][1]);

	pick_info[area_info[area_amount -1][a_area][0]][pick_type] = pick_type_teleportation;
	pick_info[area_info[area_amount -1][a_area][1]][pick_type] = pick_type_teleportation;


	new insert_string[512];
	format(insert_string, sizeof insert_string, "INSERT INTO `teleport_areas`(`area_x`, `area_y`, `area_z`, `area_c`, `area_to_x`, `area_to_y`, `area_to_z`, `area_to_c`, `area_virtual_world`, `area_to_virtual_world`, `area_interior`, `area_to_interior`, `area_name`)VALUES('%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%s')",
	area_info[area_amount -1][a_pos][0 ], area_info[area_amount -1][a_pos][1 ], area_info[area_amount -1][a_pos][2 ], area_info[area_amount -1][a_pos][3 ],
	area_info[area_amount -1][a_to_pos][0 ], area_info[area_amount -1][a_to_pos][1 ], area_info[area_amount -1][a_to_pos][2 ], area_info[area_amount -1][a_to_pos][3 ],
	params[0 ], params[2 ], params[1 ], params[3], params[4]);
	mysql_tquery(sql_connection, insert_string, "", "");

	SendClientMessage(playerid, col_lblue, "Dynamic login successfully created.");
	return 1;
}

cmd:createcellar(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /createcellar [Gheymat]");
	if(params[1] < 1) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The price of a basement cannot be less 1$.");
	GetPlayerPos(playerid, cellar_info[cellar_count][cl_pos][0], cellar_info[cellar_count][cl_pos][1], cellar_info[cellar_count][cl_pos][2]);
	GetPlayerFacingAngle(playerid, cellar_info[cellar_count][cl_pos][3]);

	cellar_info[cellar_count][cl_id] = cellar_count + 1;
	strcat(cellar_info[cellar_count][cl_owner_name], "State Property");
	cellar_info[cellar_count][cl_owner] = -1;
	cellar_info[cellar_count][cl_price] = params[0];

	cellar_info[cellar_count][cl_pickup] = CreateDynamicPickup(1318, 23, cellar_info[cellar_count][cl_pos][0], cellar_info[cellar_count][cl_pos][1], cellar_info[cellar_count][cl_pos][2], 0, -1);

	pick_info [cellar_info[cellar_count][cl_pickup]][pick_type] = pick_type_clentrance;

	new query_string[246];
	format(query_string, 68, "Shoma Ba Movafghiat ye zamin sakhtid | zir zamin %d.", cellar_info[cellar_count][cl_id]);
	SendClientMessage(playerid, col_white, query_string);

	mysql_format(sql_connection, query_string, sizeof(query_string ),"INSERT INTO `cellars` (`cl_pos_x`,`cl_pos_y`,`cl_pos_z`,`cl_pos_c`,`cl_price`) VALUES ('%f','%f','%f','%f','%d')",
	cellar_info[cellar_count][cl_pos][0], cellar_info[cellar_count][cl_pos][1], cellar_info[cellar_count][cl_pos][2], cellar_info[cellar_count][cl_pos][3],
	params[0]);
	mysql_tquery(sql_connection, query_string, "", "");

	cellar_count ++;
	return 1;
}

cmd:intlist(playerid)
{
	if(check_admin_rank(playerid , 8)) return 1;
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Business Enterers", ""c_white"\
	1. 24/7\n\
	2. Ammunition\n\
	3. Car market\n\
	4. Cluckin Bell\n\
	5. Well Stacked Pizza\n\
	6. Burger Shot\n\
	7. Clothes Shop\n\
	8. Cape\n\
	9. Alьhhambra\n\
	10. Enterer Bara\n\
	11. Stroke\n\
	12. Jazzy\n\
	13. Pharmacy\n\
	14. Electronics shop", "Bastan", "");
	return 1;
}

cmd:bizprice(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;

	new bizId = -1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	for (new i = 0; i < b_count; i++) {
		if(GetDistanceBetweenPoints(x, y, z, b_info[i][b_position][0], b_info[i][b_position][1], b_info[i][b_position][2]) <= 3.0) {
			bizId = i;
			break;
		}
	}

    if(bizId == -1)
        return SendClientMessage(playerid, col_white, ""scm_error"Bayad Be Kenar Business Beravid.");

	new price;

	if(sscanf(params, "d", price)) 
		return SendInfo(playerid, "Enter: /bizprice [price]");

    // if(!(0 <= bizId < b_count)) return SendClientMessage(playerid, col_white, ""scm_error"Invalid Business ID.");

    if(!(1 <= price < 800_000_000))
        return SendClientMessage(playerid, col_white, ""scm_error"Invalid Price. (1 to 800,000,000)");

	b_info[bizId][b_price] = price;

	new query_string[200];

	UpdateBusinessEnterLabel(bizId);

	format(query_string, 144, "Price \"Business #%d\" changed to {18E70E}$%d", bizId, b_info[bizId][b_price]);

	SendClientMessage(playerid, col_white, query_string);

	format(query_string, 100, "UPDATE `businesses` SET `b_price` = %d WHERE `b_id` = '%d'", 
		b_info[bizId][b_price], b_info[bizId][b_id]);
	mysql_tquery(sql_connection, query_string);
	return 1;
}

cmd:createbusiness(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "ddds[32]", params[0], params[1], params[2], params[3])) return SendInfo(playerid, "Enter: /createbusiness [id][Gheymat][int][Name]" ),
			SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Mag -0 type, refill -1 type, weapon shop -2 type, typ -3 t SP, clothing store -4 type."),
	SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Auto market -5 typ, diner -6 typ, club -7 typ, bar -8 typ, apte ka -9 type, electronics shop -10 type | intlist");

	GetPlayerPos(playerid, b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2]);
	GetPlayerFacingAngle(playerid, b_info[b_count][b_position][3]);

	b_info[b_count][b_id] = b_count + 1;
	strcat(b_info[b_count][b_owner_name], "state property");
	b_info[b_count][b_owner_inc] = -1;
	b_info[b_count][b_price] = params[1];
	b_info[b_count][b_type] = params[0];
	b_info[b_count][b_maxproduct] = 15000;
	format(b_info[b_count][b_name], 32, "%s", params[3]);

	new bis_int = params[2] -1;


	if(b_info[b_count][b_type] == bizz_type_shop || b_info[b_count][b_type] == bizz_type_pharm || b_info[b_count][b_type] == bizz_type_electronic || b_info[b_count][b_type] == bizz_type_clothes || b_info[b_count][b_type] == bizz_type_carshop || b_info[b_count][b_type] == bizz_type_cafe || b_info[b_count][b_type] == bizz_type_club || b_info[b_count][b_type] == bizz_type_bar)
	{
		b_info[b_count][b_pickup] = CreateDynamicPickup(1318, 23, b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2], 0, 0);
		pick_info[b_info[b_count][b_pickup]][pick_type] = pick_type_bentrance;


		new pickup_biz = CreateDynamicPickup(1318, 23, b_interior[bis_int][i_position][0], b_interior[bis_int][i_position][1], b_interior[bis_int][i_position][2], b_info[b_count][b_id] + 1000, b_interior[bis_int][i_interior]);
		pick_info[pickup_biz][pick_type] = pick_type_bexit;
	}
	else if(b_info[b_count][b_type] == bizz_type_ammo)
	{
		b_info[b_count][b_pickup] = CreateDynamicPickup(1318, 23, b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2], 0, 0);
		pick_info[b_info[b_count][b_pickup]][pick_type] = pick_type_bentrance;


		new pickup_biz = CreateDynamicPickup(1318, 23, b_interior[bis_int][i_position][0], b_interior[bis_int][i_position][1], b_interior[bis_int][i_position][2], b_info[b_count][b_id] + 1000, b_interior[bis_int][i_interior]);
		pick_info[pickup_biz][pick_type] = pick_type_bexit;

		new actorid = CreateActor(179, 296.4053, -40.2153, 1001.5156, 1.6147);
		SetActorVirtualWorld(actorid, b_info[b_count][b_id] + 1000);
	}

	b_info[b_count][b_label] = CreateDynamic3DTextLabel("Loading...", -1,  b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2] + 0.7, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
	UpdateBusinessEnterLabel(b_count);

	if(bis_int >= 0)
	{
 		CreateDynamicMapIcon(b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2], b_interior[bis_int][i_map_icon], 0, 0, 0, -1, 300.0);
	}
	else
	{
		switch(b_info[b_count][b_type])
		{
			case bizz_type_tune:CreateDynamicMapIcon(b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2], 27, 0, 0, 0, -1, 300.0);
			case bizz_type_gas:CreateDynamicMapIcon(b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2], 47, 0, 0, 0, -1, 300.0);
		}
	}

	new query_string[236];
	mysql_format(sql_connection, query_string, sizeof(query_string ),"INSERT INTO `businesses` (`b_pos_x`,`b_pos_y`,`b_pos_z`,`b_pos_c`,`b_price`,`b_type`,`b_int`,`b_name`) VALUES ('%f','%f','%f','%f','%d','%d','%d','%e')",
	b_info[b_count][b_position][0], b_info[b_count][b_position][1], b_info[b_count][b_position][2], b_info[b_count][b_position][3],
	params[1], b_info[b_count][b_type], bis_int + 1, b_info[b_count][b_name]);
	mysql_tquery(sql_connection, query_string, "", "");

	b_count ++;
	return 1;
}

cmd:flymode(playerid)
{
	if(check_admin_rank(playerid , 1)) return 1;
	if(GetPVarType(playerid, "FlyMode")) CancelFlyMode(playerid);
	else FlyMode(playerid);
	return 1;
}

cmd:spawncars(playerid)
{
	if(check_admin_rank(playerid , 7)) return 1;
	
	respawn_all_unoccupied_cars();

	AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] Spawn all server car's.", PlayerInfo[playerid][name], playerid);

	return 1;
}

cmd:spawnall(playerid,params[])
{
	if(check_admin_rank(playerid , 7)) return 1;
	new range;
	if(sscanf(params, "d", range)) return SendInfo(playerid, "Enter: /spawnall [range]");
	if(!(1 <= range <= 10000)) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Enter range between 1 to 10000");

	new text_string[80];
    format(text_string, sizeof(text_string), ""c_server"* SPAWN: "c_grey"Admin %s shoma ra spawn kard.", Name(playerid));

	foreach(new i: logged_players) {
		if(i == playerid) continue;
		if(GetDistanceBetweenPlayers(i, playerid) > float(range)) continue;
		SpawnPlayer(i);
		SendClientMessage(i,0x00CDD3FF, text_string);
	}

	SendClientMessage(playerid, col_white, ""scm_sucess"Players spawned.");
	return 1;
}

cmd:alogin(playerid)
{
	if(PlayerInfo[playerid][admin])
	{
		AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] az panel admin kharej shod", PlayerInfo[playerid][name], playerid);

		Iter_Remove(admin_players, playerid);

		PlayerInfo[playerid][admin] = 0;

		HideConnectPanelAC(playerid);
		HideWarningPanelAC(playerid);

		UpdatePlayerName(playerid);
		return 1;
	}
	new tquery_string[85];
	mysql_format(sql_connection, tquery_string, sizeof(tquery_string), "SELECT * FROM `users_admins` WHERE `u_a_name`='%s' LIMIT 1", PlayerInfo[playerid][name]);
	mysql_tquery(sql_connection, tquery_string, "alogin_step_one", "i", playerid);
	return 1;
}

callback: alogin_step_one(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	
    if(!rows) return 1;

    new admin_pass[32];
    cache_get_field_content(0, "u_a_password", admin_pass, sql_connection, 32);

    if(GetString(admin_pass, "n"))
    	show_dialog(playerid, d_alogin_reg, DIALOG_STYLE_INPUT, !""scm_dialog"Registration", !""c_white"Enter the password that will be used for authorization\n"c_grey"Note:\n\t"c_grey"- The password must consist of Latin letters and numbers\n\t"c_grey"-Password size from 6 to 15 characters.", !"Next", !"Cancel");
    else
    	show_dialog(playerid, d_alogin, DIALOG_STYLE_INPUT, !""scm_dialog"Authorization", !""c_white"Enter your password from the admin panel:", !"Next", !"Cancel");
    	
	return 1;
}

callback: alogin_step_two(playerid)
{
	new rows = cache_num_rows();

	if(!rows)
	{
		AdminMes(""c_server"* A.INFO:"c_grey" Admin %s[%d] failed authorization [%s]", PlayerInfo[playerid][name], playerid, p_t_info[playerid][p_ip]);

		PlayerInfo[playerid][admin] = 0;
		UpdatePlayerName(playerid);
		return 1;
	}


    PlayerInfo[playerid][admin] = cache_get_field_content_int(0, "u_a_level", sql_connection);
    PlayerInfo[playerid][admin_played] = cache_get_field_content_int(0, "u_a_online", sql_connection);

    UpdatePlayerName(playerid);

	ShowWarningPanelAC(playerid);
	ShowConnectPanelAC(playerid);

	Iter_Add(admin_players, playerid);

	AdminMes(""c_server"* A.INFO:"c_grey" Admin %s[%d] ba movafaghiat be panel "c_gold_main"%s"c_grey" level vared shod", PlayerInfo[playerid][name], playerid, a_rank_name[PlayerInfo[playerid][admin]-1]);
	
	return 1;
}

cmd:iwep(playerid,params[])
{
    if(check_admin_rank(playerid , 2)) return 1;
    if(sscanf(params,"u",params[0])) return	SendInfo(playerid, "Enter: /iwep [id/name]");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Offline player!");
    global_string[0] = EOS;
    new Gun[13], pAmmo[13];
    for(new i = 0; i < 12; i++)
    {
        GetPlayerWeaponData(params[0], i, Gun[i], pAmmo[i]);
        format(global_string, 2000, "%s"c_white"Slot: %i\t Weaponid: %i\t Ammo: %i\n", global_string, i, Gun[i], pAmmo[i]);
        if(i == 12) format(global_string, 2000, "%s\n",global_string);
    }
	strcat(global_string, "\n"c_server"Server Information:\n\n"c_grey"");
    for(new slot = 0; slot <= 12; slot++)
    {
    	format(global_string, 2000, "%s"c_server"Slot %i\t Weaponid: %i\t Ammo: %i\n",global_string, slot, PlayerInfo[params[0]][Weapon][slot], PlayerInfo[params[0]][Ammo][slot]);
	}
    show_dialog(playerid,d_none,DIALOG_STYLE_MSGBOX, PlayerInfo[params[0]][name], global_string, "Bastan", "");
    return 1;
}

cmd:afklist(playerid)
{
    if(check_admin_rank(playerid , 2)) return 1;

	global_string[0] = EOS;

	new _count = 0;
    foreach(new i : logged_players)
    {
		if(pl_afk_time[i] < 3) continue;
		new line_string[MAX_PLAYER_NAME + 62 + 16 + 10];
		format(line_string, sizeof(line_string), ""c_server"%s[%d] "c_white"| %d level | IP:%s | "c_server"AFK: %d\n", PlayerInfo[i][name], i, PlayerInfo[i][level], p_t_info[i][p_ip], pl_afk_time[i]);
		strcat(global_string, line_string);
		_count ++;
	}
	if(_count == 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"No AFK players.");
    else show_dialog(playerid, d_none,DIALOG_STYLE_MSGBOX, ""c_server"AFK players", global_string, "Bastan", "");
	return 1;
}

cmd:clearsd(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendClientMessage(playerid, col_gray,""scm_info"Enter: /clearsd [id/name]");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Bazikon Yaft Nashod!");

	p_t_info[params[0]][p_gun_shots] = 0;
	p_t_info[params[0]][p_gun_accuracy] = 0;
	SendClientMessage(playerid, col_gray, ""c_grey"* Player shot statistics updated.");
	return 1;
}

cmd:sd(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendClientMessage(playerid, col_gray,""scm_info"Enter: /sd [id/name]");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Bazikon Yaft Nashod!");

	if(p_t_info[params[0]][p_gun_shots] > 0)
	{
		new _dialog_string[74 + MAX_PLAYER_NAME + 12];
		format(_dialog_string, sizeof(_dialog_string), ""c_server"%s\n\n"c_white"Shots: %d\nHits: %d\nAccuracy: %d percent.",
		PlayerInfo[params[0]][name], p_t_info[params[0]][p_gun_shots], p_t_info[params[0]][p_gun_accuracy],
		p_t_info[params[0]][p_gun_accuracy]* 100 / p_t_info[params[0]][p_gun_shots]);
		show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Shot statistics", _dialog_string, "Bastan", "");
	}
	else return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The player didn't fire a single shot.");
	return 1;
}

cmd:setstat(playerid, params[])
{
	if(check_admin_rank(playerid , 7)) return 1;
	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /setstat [id Bazikon]");

	SetPVarInt(playerid, !"target_id", targetid);

	new header_string[45];
	format(header_string, sizeof(header_string), ""scm_dialog"%s", PlayerInfo[targetid][name]);
	show_dialog(playerid, d_setstat, DIALOG_STYLE_LIST, header_string, !"\
    "c_server"1 | "c_white"Nick\n\
    "c_server"2 | "c_white"Level\n\
    "c_server"3 | "c_white"EXP\n\
    "c_server"4 | "c_white"Licenses\n\
    "c_server"5 | "c_white"Weapon Skills\n\
    "c_server"6 | "c_white"Game currency\n\
    "c_server"7 | "c_white"Donate", !"Entekhab", !"Bastan");
	return 1;
}

cmd:kick(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "us[24]", params[0], params [1])) return SendInfo(playerid, "Enter: /kick [id] [причина]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	new scm_string[144];
	format(scm_string, sizeof(scm_string ), "Admin %s kicked player %s. Reason: %s", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1]);
	foreach(new i: logged_players) if(PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, scm_string);

	format(scm_string,sizeof(scm_string),"UPDATE `users_admins` SET `u_a_kicks` = `u_a_kicks`+1 WHERE `u_a_name` = '%s' LIMIT 1", PlayerInfo[playerid][name]);
	mysql_tquery(sql_connection, scm_string, "", "");

	kick_player(params[0]);
 	return 1;
}

cmd:setbproduct(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
 	if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /setbproduct [id] [number]");
    if(params[0] > b_count || params[0] < 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Non-precise business number.");
    if(params[1] > 50000 || params[0] < 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Some number of products.");


	b_info[params[0] -1][b_product] = params[1];

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] installed %s business %d products.", PlayerInfo[playerid][name], playerid, b_info[params[0] -1][b_name], params[1]);
	return 1;
}

cmd:setbmoney(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
 	if(sscanf(params, "dd", params[0], params[1])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Emter: /setbmoney [id] [quantity]");
	if(params[0] > b_count || params[0] < 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Uncorrect business number.");
	if(params[1] > 50000 || params[0] < 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Inaccurate amount of money.");


	b_info[params[0] -1][b_money] = params[1];

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] established business %s $%d.", PlayerInfo[playerid][name], playerid, b_info[params[0] -1][b_name], params[1]);
	return 1;
}

cmd:warn(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "us[32]", params[0], params[1])) return SendInfo(playerid, "Enter: /warn [id/name] [reason]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	
	if(PlayerInfo[params[0]][admin] >= 5) return SendError(playerid, "You can't give him a punishment.");

	if(get_player_warn_count(params[0]) == 2)
	{
		new scm_string[238];
		format(scm_string, 144, "Admin %s has blocked %s [3 warnings]. Deadline: 3 days. Reason: %s", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1]);
		foreach(new i: logged_players) if(PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, scm_string);

		mysql_format(sql_connection, scm_string, sizeof(scm_string ), "INSERT INTO `users_bans` (`u_b_admin`,`u_b_name`,`u_b_reason`,`u_b_date`,`u_b_ndate`,`u_b_days`) VALUES('%s', '%s', '%s', NOW() + INTERVAL 3 DAY, NOW(), '3')", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1]);
		mysql_query(sql_connection, scm_string);


		format(scm_string,sizeof(scm_string),"UPDATE `users_admins` SET `u_a_warns` = `u_a_warns`+1 WHERE `u_a_name` = '%s' LIMIT 1", PlayerInfo[playerid][name]);
		mysql_tquery(sql_connection, scm_string, "", "");



		format(scm_string, sizeof scm_string, "UPDATE `users_warns` SET `w_end`=NOW() WHERE `w_owner`='%d'", PlayerInfo[params[0]][id]);
		mysql_tquery(sql_connection, scm_string);

		format(scm_string, sizeof scm_string, "SELECT * FROM `users_bans` WHERE `u_b_name` = '%s' AND `u_b_date` > NOW()LIMIT 1", PlayerInfo[params[0]][name]);
		mysql_tquery(sql_connection, scm_string, "check_player_banned", "i", params[0]);

	}
	else
	{
		new scm_string[238];
		format(scm_string, 144, "Admin %s issued a warning to player %s. Reason: %s", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], params[1]);
		foreach(new i: logged_players) if(PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, scm_string);

		format(scm_string,sizeof(scm_string),"UPDATE `users_admins` SET `u_a_warns` = `u_a_warns`+1 WHERE `u_a_name` = '%s' LIMIT 1", PlayerInfo[playerid][name]);
		mysql_tquery(sql_connection, scm_string, "", "");

		format(scm_string, sizeof(scm_string ), "INSERT INTO `users_warns` (`w_admin_name`,`w_owner`,`w_reason`,`w_date`,`w_end`) VALUES('%s', '%d', '%s', NOW(), NOW() + INTERVAL 5 DAY)", PlayerInfo[playerid][name], PlayerInfo[params[0]][id], params[1]);
		mysql_tquery(sql_connection, scm_string);

		// ----------------------
		// Top War
		new topWarTarget = params[0];
		if(PlayerInfo[topWarTarget][member] == TopWarGangAttacker || PlayerInfo[topWarTarget][member] == TopWarGangProtector) {
			TopWar_HideSmallTopWarInfo(topWarTarget);

			//Reset Vars
			for(new GangPlayerEnum:i; i < GangPlayerEnum; i++) GangPlayer[topWarTarget][i] = 0;
		}
		// ----------------------

		new reason_warn[70];
		format(reason_warn, sizeof reason_warn, "Admin Warn(%s)", params[1]);

		addWorkBook(params[0], PlayerInfo[playerid][name], reason_warn);

		kick_player(params[0]);
	}
 	return 1;
}

cmd:unwarn(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /unwarn [id/name]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	if(get_player_warn_count(params[0]) == 0) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Player has no warnings.");

	new scm_string[238];

	AdminMes(""c_server"* A.INFO: "c_grey"%s cleared warnings from %s.", PlayerInfo[playerid][name], PlayerInfo[params[0]][name]);

	format(scm_string, 128, "UPDATE `users_warns` SET `w_end`=NOW() WHERE `w_owner`='%d'", PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, scm_string);
	return 1;
}

cmd:warnlist(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /warnhistory [id/name]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	new scm_string[144];
	format(scm_string, sizeof scm_string, "SELECT * FROM `users_warns` WHERE `w_owner` = '%d' AND `w_end` > NOW()LIMIT 3", PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, scm_string, "warnlist_callback", "i", playerid);
	return 1;
}

cmd:warnhistory(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /warnlist [id/name]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	new scm_string[144];
	format(scm_string, sizeof scm_string, "SELECT * FROM `users_warns` WHERE `w_owner` = '%d'", PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, scm_string, "warnlist_callback", "i", playerid);
	return 1;
}

callback: warnlist_callback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		global_string[0] = EOS;
		strcat(global_string, ""c_white"");
		for(new j = 0; j < rows; j ++)
		{
			new admin_name[MAX_PLAYER_NAME],
				warn_reason[32],
				warn_date[22], line_string[98];

			cache_get_field_content(j, "w_admin_name", admin_name, sql_connection, MAX_PLAYER_NAME);
			cache_get_field_content(j, "w_reason", warn_reason, sql_connection, 32);
			cache_get_field_content(j, "w_date", warn_date, sql_connection, 22);


			format(line_string, sizeof(line_string), "%s\t%s\t%s\n", warn_date, admin_name, warn_reason);
			strcat(global_string, line_string);
		}
		show_dialog(playerid, d_none, DIALOG_STYLE_TABLIST, ""c_server"List of Warnings", global_string, "Bastan", "");
	}
	if(!rows) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"No Warnings.");
	return 1;
}

cmd:arep(playerid, params[])
{
    if(check_admin_rank(playerid , 1)) return 1;

	new dialog_string[17 + (MAX_PLAYER_NAME -4) * 2 + 9 + 16],
	string[19 + MAX_PLAYER_NAME -3];
	global_string[0] = EOS;

	for(new i = 0; i < max_report; i++)
	{
		if(report_player[i] == -1) continue;
		if(isnull(global_string)) global_string = ""c_white"#\t"c_white"Sender\t"c_white"Status\n";
		if(report_slot[i] != -1) string = ""c_yellow"Checks: ", strcat(string, PlayerInfo[report_slot[i]][name]);

		format(dialog_string, sizeof dialog_string, ""c_white"%d.\t%s\t%s\n", i, PlayerInfo[report_player[i]][name], (report_slot[i] == -1) ?
		""c_green"Montazer pardazesh" : string);
		strcat(global_string, dialog_string);
		string[0] = EOS;
	}

	if(!isnull(global_string)) show_dialog(playerid, d_reports, DIALOG_STYLE_TABLIST_HEADERS, !""scm_dialog"List of reports", global_string, !"Process", !"Bastan");
    else SendError(playerid, "The report is currently empty.");

	return 1;
}

cmd:anamestore(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;


	if(sscanf(params, "s[30]", params[0])) return SendInfo(playerid, "Enter: /anamestore [name]");
	new query_string[80 + MAX_PLAYER_NAME];
	mysql_format(sql_connection, query_string, sizeof query_string, "SELECT `u_id` FROM `users` WHERE `u_name` = '%e' LIMIT 1", params[0]);
	mysql_tquery(sql_connection, query_string, "anamestore_callback", "i", playerid);

	return 1;
}

callback:anamestore_callback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The player with the given nickname was not found in the database.");

	new db_increment = cache_get_field_content_int(0, "u_id", sql_connection);

	new query_string[80 + MAX_PLAYER_NAME];
	format(query_string, sizeof query_string, "SELECT * FROM `nickname_history` WHERE `nh_owner` = '%d'", db_increment);
	mysql_tquery(sql_connection, query_string, "_anamestore_callback", "i", playerid);
	return 1;
}

callback:_anamestore_callback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"ИThis player's nickname bar is empty.");

    global_string[0] = EOS;
    strcat(global_string, "{cccc99}Old Nickname -New Nickname -Nickname Change Date\n\n"c_white"");

	for(new j = 0; j < rows; j ++)
    {
		new _nh_oldname[MAX_PLAYER_NAME],
			_nh_newname[MAX_PLAYER_NAME],
			_nh_date[20],
			_nh_admin[MAX_PLAYER_NAME],
			line_string[82];

		cache_get_field_content(j, "nh_oldname", _nh_oldname, sql_connection, MAX_PLAYER_NAME);
		cache_get_field_content(j, "nh_newname", _nh_newname, sql_connection, MAX_PLAYER_NAME);
		cache_get_field_content(j, "nh_admin", _nh_admin, sql_connection, MAX_PLAYER_NAME);
		cache_get_field_content(j, "nh_date", _nh_date, sql_connection, 20);

		format(line_string, sizeof(line_string), "%s -%s -%s | Изменён %s\n", _nh_oldname, _nh_newname, _nh_date, _nh_admin);
		strcat(global_string, line_string);

	}
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, "{E3D18D}History of nicknames", global_string, "Bastan", "");
	return 1;
}

cmd:goto(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /goto [id Bazikon]");
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(!IsPlayerSpawned(targetid)) return SendError(playerid, "Bazikon Spawn Nashode Ast.");

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z;
	GetPlayerPos(targetid, pl_pos_X, pl_pos_Y, pl_pos_Z);

	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || GetPlayerInterior(targetid) != 0) {
		set_pos(playerid, pl_pos_X + 2.0, pl_pos_Y, pl_pos_Z, 0.0, GetPlayerInterior(targetid), GetPlayerVirtualWorld(targetid));
	} else {
		new carid = GetPlayerVehicleID(playerid);
		SetVehiclePos(carid, pl_pos_X + 2.0, pl_pos_Y, pl_pos_Z);
		SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(targetid));
		LinkVehicleToInterior(carid, GetPlayerInterior(targetid));
	}

	if(p_t_info[targetid][house] != -1) p_t_info[playerid][house] = p_t_info[targetid][house];
	if(p_t_info[targetid][business] != -1) p_t_info[playerid][business] = p_t_info[targetid][business];

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] teleporting to the player %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid);

	return 1;
}

cmd:gotoveh(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /gotoveh [id]");
	if(params[0] < 1 || params[0] > MAX_VEHICLES) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Vehicle not found.");
	new Float: veh_pos[3];
	GetVehiclePos(params[0], veh_pos[0], veh_pos[1],veh_pos[2]);
	veh_pos[0] += 2.0;
	set_pos(playerid, veh_pos[0], veh_pos[1], veh_pos[2], 90, 0, 0);
	new scm_string[86];
	format(scm_string, sizeof(scm_string ),""c_server"* A.INFO: "c_grey"You teleported to the car | ID: %d", params[0]);
	SendClientMessage(playerid, col_gray, scm_string);
	return 1;
}

cmd:gethereveh(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /gethereveh [id]");
	if(!IsValidVehicle(params[0])) return 0;
	new Float: veh_pos[3];
	GetPlayerPos(playerid, veh_pos[0], veh_pos[1],veh_pos[2]);

	SetVehicleVirtualWorld(params[0], GetPlayerVirtualWorld(playerid));
	SetVehiclePos(params[0], veh_pos[0] -4, veh_pos[1], veh_pos[2] + 1);

	new scm_string[82];
	format(scm_string, sizeof(scm_string),""c_server"* A.INFO: "c_grey"You have teleported the car to you | ID: %d", params[0]);
	SendClientMessage(playerid, col_gray, scm_string);

	return 1;
}

cmd:gotobiz(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /gotobiz [id]");
	if(params[0] < 1 || params[0] > b_count) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Business not found.");
	set_pos(playerid, b_info[params[0] -1][b_position][0], b_info[params[0] -1][b_position][1], b_info[params[0] -1][b_position][2], 90, 0, 0);
	new scm_string[82];
	format(scm_string, sizeof(scm_string ),""c_server"* A.INFO: "c_grey"You teleported to business | ID: %d", params[0]);
	SendClientMessage(playerid, col_gray, scm_string);
	return 1;
}

cmd:gethere(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /gethere [id Bazikon]");
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(!IsPlayerSpawned(targetid)) return SendError(playerid, "Bazikon Spawn Nashode Ast.");
    if(pl_afk_time[targetid] > 0) return SendError(playerid, "At this moment AFK players.");

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z;
	GetPlayerPos(playerid, pl_pos_X, pl_pos_Y, pl_pos_Z);

	if(GetPlayerState(targetid) != PLAYER_STATE_DRIVER)
		set_pos(targetid, pl_pos_X, pl_pos_Y, pl_pos_Z, 90, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	else
	{
		new vehicle = GetPlayerVehicleID(targetid);
		SetVehiclePos(vehicle, pl_pos_X, pl_pos_Y, pl_pos_Z);
		SetVehicleVirtualWorld(vehicle, GetPlayerVirtualWorld(playerid));
		LinkVehicleToInterior(vehicle, GetPlayerInterior(playerid));
	}

	
	if(p_t_info[playerid][house] != -1) p_t_info[targetid][house] = p_t_info[playerid][house];
	if(p_t_info[playerid][business] != -1) p_t_info[targetid][business] = p_t_info[playerid][business];

	new text_string[128];
	format(text_string, sizeof(text_string), ""scm_info"Admin "c_server"%s"c_white" teleported you to yourself.", PlayerInfo[playerid][name]);
	SendClientMessage(targetid, col_white, text_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] teleported to %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid);

	return true;
}

cmd:agun(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "udd", params[0], params[1], params[2])) return SendInfo(playerid, "Enter: /agun [id] [weapon] [ammo]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	
	give_weapon(params[0], params[1], params[2]);

	new scm_string[128];
	format(scm_string, sizeof(scm_string ),""c_server"* S.INFO: "c_grey"Admin %s[%i] gave you #%i weapons.", PlayerInfo[playerid][name], playerid, params[1]);
	SendClientMessage(params[0], col_white, scm_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] issued weapon %d to player %s[%d].", PlayerInfo[playerid][name], playerid, params[1], PlayerInfo[params[0]][name], params[0]);
	
	return 1;
}

cmd:gun(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /gun [weapon] [ammo]");
	give_weapon(playerid, params[0], params[1]);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] gave himself a weapon #%d.", PlayerInfo[playerid][name], playerid, params[0]);
	
	return 1;
}

cmd:resetweapon(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /resetweapon [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	new scm_string[96 + MAX_PLAYER_NAME];
	format(scm_string, sizeof(scm_string ),""c_server"* A.INFO: "c_grey"%s took %s weapon", PlayerInfo[playerid][name], PlayerInfo[params[0]][name]);
	foreach(new i: admin_players)
	{
		if(PlayerInfo[playerid][admin] < 3) continue;
		SendClientMessage(i, col_gray, scm_string);
	}

 	reset_player_weapon(params[0]);

	return 1;
}

alias:giveskin("changeskin");
cmd:giveskin(playerid, params[])
{
	if(check_admin_rank(playerid , 6)) return 1;
	new targetid, skinid;
	if(sscanf(params, "ud", targetid, skinid)) return SendInfo(playerid, "Enter: /giveskin [id] [skin id]");
	if(!IsPlayerConnected(targetid)) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(skinid > 311 || skinid < 1) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid skin number.");

	new bool:found_any_empty_slot = false;

	for(new j = 0; j < 5; j ++)
	{
		if(PlayerInfo[targetid][temp_skin][j] == 0)
		{
			PlayerInfo[targetid][temp_skin][j] = skinid;
			found_any_empty_slot = true;
			break;
		}
	}

	if(!found_any_empty_slot) {
		return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Skin Haye In Bazikon Max Ast. (5/5)");
	}

	set_skin(targetid, skinid);

	new scm_string[128];
	format(scm_string, sizeof(scm_string ),""c_server"* S.INFO: "c_grey"Admin %s gave you a new skin.", PlayerInfo[playerid][name]);
	SendClientMessage(targetid, col_gray, scm_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s gave player %s a permanent skin %d", PlayerInfo[playerid][name], PlayerInfo[targetid][name], skinid);

	format(scm_string, sizeof(scm_string), "UPDATE `users` SET `u_tempskin`='%d|%d|%d|%d|%d' WHERE `u_id` = '%d'",
	PlayerInfo[targetid][temp_skin][0], PlayerInfo[targetid][temp_skin][1], PlayerInfo[targetid][temp_skin][2],
	PlayerInfo[targetid][temp_skin][3], PlayerInfo[targetid][temp_skin][4], PlayerInfo[targetid][id]);
	mysql_tquery(sql_connection, scm_string);
	return 1;
}

cmd:skin(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "ud", params[0], params[1])) return SendInfo(playerid, "Enter: /skin [id] [скин]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	if(params[1] > 311 || params[1] < 1) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid skin number.");

	new scm_string[128];
	format(scm_string, sizeof(scm_string ),""c_server"* S.INFO: "c_grey"Admin %s[%i] give you a temporary skin #%i.", PlayerInfo[playerid][name], playerid, params[1]);
	SendClientMessage(params[0], col_gray, scm_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] issued a temporary skin to the player %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	SetPlayerSkin(params[0], params[1]);
	return 1;
}

cmd:msg(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "s[108]", params[0])) return SendInfo(playerid, "Enter: /msg [Matn]");
	new scm_string[144];
	format(scm_string, sizeof(scm_string ), "Admin %s: %s ", PlayerInfo[playerid][name], params[0]);
	foreach(new i: logged_players) SendClientMessage(i, 0xEBC826FF, scm_string);
	return 1;
}

cmd:connections(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params,"u", params[0])) return SendClientMessage(playerid,col_gray,""scm_info"Enter: /connections [id/name]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	new sql_string[121];
	format(sql_string, sizeof sql_string, "SELECT * FROM `users_history` WHERE `uh_user` = '%d' ORDER BY `users_history`.`uh_id` DESC LIMIT 10", PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, sql_string, "adminload_user_history", "i", playerid);
	return 1;
}

callback: adminload_user_history(playerid)
{
	new rows,
		fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		global_string[0] = EOS;

		for(new i = 0; i < 10; i ++)
		{
			new uh_ip[16],
				uh_date[22];

			new line_string[62];

			cache_get_field_content(i, "uh_ip", uh_ip, sql_connection, 16);
			cache_get_field_content(i, "uh_date", uh_date, sql_connection, 22);

			format(line_string, sizeof(line_string), ""c_white"%d."c_grey"\t%s\t%s\n",
															i + 1,
															uh_date,
															uh_ip);
			strcat(global_string, line_string);
		}
		show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, !""scm_dialog"Connection history", global_string, !"Barghast", !"");
	}
	if(!rows)
	{
		SendError(playerid, "Connection history missing, please try again later.");
		return 1;
	}
	return 1;
}

cmd:offleader(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params,"s[24]s[70]", params[0], params[1])) return SendClientMessage(playerid,col_gray,""scm_info"Enter: /offleader [name] [reason]");

	new scm_string[128];
	format(scm_string, sizeof(scm_string ), "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", params[0]);
	mysql_function_query(sql_connection, scm_string, true, "offleader_check_callback", "iss", playerid, params[0]);
	return 1;
}

callback: offleader_check_callback(playerid, pl_name[], _reason[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows)
	{
		new scm_string[128];
		format(scm_string, sizeof(scm_string), ""c_orange_red"* "c_orange_red"Account %s not found in database.", pl_name);
		SendClientMessage(playerid, col_gray, scm_string);
		return 1;
	}
	else
	{
		addOffWorkBook(pl_name, PlayerInfo[playerid][name], _reason);

		AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] removed the authority of the leader from %s.", PlayerInfo[playerid][name], playerid, pl_name);
		
		return 1;
	}
}

cmd:delacc(playerid, params[])
{
	if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params,"s[24]", params[0])) return SendClientMessage(playerid,col_gray,""scm_info"Enter: /delacc [name]");

	new scm_string[128];
	format(scm_string, sizeof(scm_string ), "SELECT * FROM `users` WHERE `u_name` = '%s' LIMIT 1", params[0]);
	mysql_function_query(sql_connection, scm_string, true, "dellaccount_check_callback", "is", playerid, params[0]);
	return 1;
}
alias:delacc("delaccount");

callback: dellaccount_check_callback(playerid, pl_name[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows)
	{
		new scm_string[128];
		format(scm_string, sizeof(scm_string), ""c_orange_red"* "c_orange_red"Account %s not found in database.", pl_name);
		SendClientMessage(playerid, col_gray, scm_string);
		return 1;
	}
	else
	{
		static query6[] = "DELETE IGNORE FROM "TABLE_PHOTOGRHAPHER_COOLDOWN" WHERE `user_name` = '%e' LIMIT 1";
		new fmt_query6[sizeof(query6) + MAX_PLAYER_NAME + 1 -2];
		mysql_format(sql_connection, fmt_query6, sizeof(fmt_query6), query6, pl_name);
		mysql_tquery(sql_connection, fmt_query6);

		new scm_string[108];
		format(scm_string, sizeof(scm_string ), "DELETE FROM `users` WHERE `u_name` = '%s' LIMIT 1", pl_name);
		mysql_tquery(sql_connection, scm_string);

		AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] deleted account %s.", PlayerInfo[playerid][name], playerid, pl_name);

		return 1;
	}
}

cmd:freeze(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /freeze [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	toggle_controlable(params[0], false);
	new scm_string[128];

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] frozen player %s[%d].", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	format(scm_string, sizeof(scm_string ),""c_server"* S.INFO: "c_grey"Admin %s зamorozil vass.", PlayerInfo[playerid][name]);
	SendClientMessage(params[0], col_gray, scm_string);
	return 1;
}

cmd:unfreeze(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /unfreeze [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	toggle_controlable(params[0], true);
	new scm_string[128];

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] player thawed %s[%d].", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	format(scm_string, sizeof(scm_string ),""c_server"* S.INFO: "c_grey"Admin %s thawed you out.", PlayerInfo[playerid][name]);
	SendClientMessage(params[0], col_gray, scm_string);
	return 1;
}

cmd:slap(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /slap [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	new Float:pl_pos[3];
	p_t_info[playerid][p_tp_immune_time] = 3;

	GetPlayerPos(params[0], pl_pos[0], pl_pos[1], pl_pos[2]);
	SetPlayerPos(params[0], pl_pos[0], pl_pos[1], pl_pos[2] + 6);
	PlayerPlaySound(params[0], 1130, pl_pos[0], pl_pos[1], pl_pos[2] + 6);
	new scm_string[98];
	format(scm_string, sizeof(scm_string ),""c_server"* S.INFO: "c_grey"Admin %s[%d] threw you up.", PlayerInfo[playerid][name], playerid);
	SendClientMessage(params[0], col_gray, scm_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] tossed a player %s[%d].", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	return 1;
}

cmd:setarmour(playerid, params[])
{
    if(check_admin_rank(playerid , 3)) return 1;

	if(sscanf(params,"dd", params[0], params[1]))
		return SendInfo(playerid, "Enter: /setarmour [id] [amount of armor]");

	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	if(IsPlayerInAnyDMZone(params[0])) return SendError(playerid, "In Bazikon Dar DM Zone Ast.");
	if(IsPlayerInCounterStrike(params[0]) || IsPlayerInCounterStrikeLobby(params[0])) return SendError(playerid, "In Bazikon Dar Counter Strike Ast.");

	if(PlayerInfo[playerid][admin] > 7)
	{
		if(params[1] > 1000 || params[1] < 0) return SendError(playerid, "You can enter armor from 0 to 1000.");
	}
	else
	{
		if(params[1] > 100 || params[1] < 0) return SendError(playerid, "You can enter armor from 0 to 100.");
	}

	set_armour(params[0], params[1]);

	new str[128];
	format(str, sizeof(str), ""scm_sucess"Shoma Ba Movafghiat armor bazikon ra tanzim kardid be (%d) baraye in bazikon %s[%d]", params[1], PlayerInfo[params[0]][name], params[0]);
	SendClientMessage(playerid, col_white, str);

	return 1;
}

cmd:sethp(playerid, params[])
{
    if(check_admin_rank(playerid , 3)) return 1;

	if(sscanf(params,"dd", params[0], params[1]))
		return SendInfo(playerid, "Enter: /sethp [id] [amount of health]");

	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	if(IsPlayerInAnyDMZone(params[0])) return SendError(playerid, "In Bazikon Dar DM Zone Ast.");
	if(IsPlayerInCounterStrike(params[0]) || IsPlayerInCounterStrikeLobby(params[0])) return SendError(playerid, "In Bazikon Dar Counter Strike Ast.");

	if(PlayerInfo[playerid][admin] > 7)
	{
		if(params[1] > 1000 || params[1] < 0) return SendError(playerid, "You can enter hp from 0 to 1000");
	}
	else
	{
		if(params[1] > 160 || params[1] < 0) return SendError(playerid, "You can enter hp from 0 to 160");
	}
	
	set_health(params[0], params[1]);

	if(GetPVarInt(params[0], "p_dead")) {
		DeletePVar(params[0], "p_dead");
	}

	new str[128];
	format(str, sizeof(str), ""scm_sucess"Shoma Ba Movafghiat set the player's HP (%d) %s[%d]", params[1], PlayerInfo[params[0]][name], params[0]);
	SendClientMessage(playerid, col_white, str);
	return 1;
}

cmd:gmcheck(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /gmcheck [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	new Float:pl_health;
	GetPlayerHealth(params[0], pl_health);
	set_health(params[0], pl_health -5);

	SetTimerEx("check_player_nop", 1400, false, "iif", playerid, params[0], pl_health);

	return 1;
}

callback:check_player_nop(playerid, targetid, Float:pl_health)
{
	new Float:new_health;
	GetPlayerHealth(targetid, new_health);
	new gm_result[16];


	if(new_health == pl_health)format(gm_result, 16, "NOP detected");
	else format(gm_result, 16, "NOP not found");

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] checked %s[%d] for GM | Result: %s", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid, gm_result);

	return 1;
}

cmd:satiety(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /satiety [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
	PlayerInfo[params[0]][hunger] = 100;
	SetPlayerProgressBarValue(params[0], satiety_progress_bar[params[0]], PlayerInfo[params[0]][hunger]);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] full satiety %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	return 1;
}

alias:gmuse("godmode", "god");
cmd:gmuse(playerid)
{
	if(check_admin_rank(playerid , 1)) return 1;

	if(p_t_info[playerid][player_gm] == 0)
	{
		p_t_info[playerid][player_gm] = 1;

		AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] enabled god mode.", PlayerInfo[playerid][name], playerid);

		return 1;
	}

	p_t_info[playerid][player_gm] = 0;

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] disabled god mode.", PlayerInfo[playerid][name], playerid);

	set_health(playerid, 100.0);
	set_armour(playerid, 0.0);
	
	return 1;
}

cmd:godp(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /godp [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	if(p_t_info[params[0]][player_gm] == 0)
	{
		p_t_info[params[0]][player_gm] = 1;

		new scm_string[150];

		AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] enabled god mode player %s[%d].", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

		format(scm_string, sizeof(scm_string),""scm_info"Admin "c_server"%s"c_white" enabled god mode for you.", PlayerInfo[playerid][name]);
		SendClientMessage(params[0], col_gray, scm_string);

		return 1;
	}

	p_t_info[params[0]][player_gm] = 0;

	set_health(params[0], 100.0);
	set_armour(params[0], 0.0);

	new scm_string[150];

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] disabled god mode player %s[%d].", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0]);

	format(scm_string, sizeof(scm_string),""scm_info"Admin "c_server"%s"c_white" disabled god mode for you.", PlayerInfo[playerid][name]);
	SendClientMessage(params[0], col_gray, scm_string);

	return 1;
}

cmd:hpcar(playerid)
{
	if(check_admin_rank(playerid , 3)) return 1;

	new veh_id = GetPlayerVehicleID(playerid);
	if(veh_id == 0) return SendClientMessage(playerid, col_white, ""scm_info"You must be in transport.");
	RepairVehicle(veh_id);
	return SendAccess(playerid, "Shoma Ba Movafghiat repaired transport");
}

cmd:afillid(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;

	extract params -> new veh_id; else return SendInfo(playerid, "Enter: /afillid [id player]");

	if(!IsValidVehicle(veh_id)) return SendError(playerid, "Invalid transport ID.");

	veh_info[veh_id -1][v_fuel] = 100.0;
	return	SendAccess(playerid, "Shoma ba movafghiat be in vasile naghlie benzin zadid.");
}

cmd:afill(playerid)
{
	if(check_admin_rank(playerid , 4)) return 1;

	if(!IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Shoma bayad savar yek vasile naghliye bashid.");

	new veh_id = GetPlayerVehicleID(playerid);

	veh_info[veh_id -1][v_fuel] = 100.0;
	return SendAccess(playerid, "Shoma ba movafghiat be in vasile naghlie benzin zadid.");
}

cmd:hpcarid(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /hpcarid [id machines]");
	if(params[0] < 1 || params[0] > MAX_VEHICLES) return SendError(playerid, "Invalid transport ID.");
	RepairVehicle(params[0]);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] car repaired | ID:%d", PlayerInfo[playerid][name], playerid, params[0]);

	return 1;
}

cmd:spoff(playerid)
{
	if(GetPVarInt(playerid, "spectate_status") != 0)
	{
		for(new j = 0; j < 7; j ++)
		{
			TextDrawHideForPlayer(playerid, sp_td[j]);
			if(j < 3)
			{
				PlayerTextDrawDestroy(playerid, sp_ptd[playerid][j]);
				sp_ptd[playerid][j] = PlayerText:-1;
			}
		}
		CancelSelectTextDraw(playerid);
		TogglePlayerSpectating(playerid, false);
	}
	else return 1;
	return 1;
}

cmd:spec(playerid, params[])
{
	if(check_admin_rank(playerid , 1)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /spec [id]");
	if(!IsPlayerConnected(params[0])) return  SendError(playerid, "Bazikon yaft nashod.");
	if(GetPVarInt(params[0], "spectate_status") != 0) return SendError(playerid, "Admin digari dar spectate in bazikon ast.");


	new Float: player_health;
	GetPlayerHealth(params[0], player_health);
	if(GetPVarInt(playerid, "spectate_status") ==  0)
	{
		GetPlayerPos(playerid, p_t_info[playerid][p_pos][0], p_t_info[playerid][p_pos][1], p_t_info[playerid][p_pos][2]);
		GetPlayerFacingAngle(playerid, p_t_info[playerid][p_pos][3]);

		new td_str[98];
		format(td_str, 48, "%s(%d)", PlayerInfo[params[0]][name], params[0]);
		sp_ptd[playerid][0] = CreatePlayerTextDraw(playerid, 86.666687, 166.148117, td_str);
		PlayerTextDrawLetterSize(playerid, sp_ptd[playerid][0], 0.242082, 1.076297);
		PlayerTextDrawAlignment(playerid, sp_ptd[playerid][0], 2);
		PlayerTextDrawColor(playerid, sp_ptd[playerid][0], -1);
		PlayerTextDrawSetShadow(playerid, sp_ptd[playerid][0], 0);
		PlayerTextDrawSetOutline(playerid, sp_ptd[playerid][0], 0);
		PlayerTextDrawBackgroundColor(playerid, sp_ptd[playerid][0], 255);
		PlayerTextDrawFont(playerid, sp_ptd[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, sp_ptd[playerid][0], 1);
		PlayerTextDrawSetShadow(playerid, sp_ptd[playerid][0], 0);

		sp_ptd[playerid][1] = CreatePlayerTextDraw(playerid, 32.083312, 189.999969, "LEVEL:~n~PING:~n~HEALTH:~n~ARMOUR:~n~SHOT_ACCURACY:~n~AMMO:~n~SPEED:~n~IP:~n~WARNS:~n~CASH:");
		PlayerTextDrawLetterSize(playerid, sp_ptd[playerid][1], 0.242082, 1.076297);
		PlayerTextDrawAlignment(playerid, sp_ptd[playerid][1], 1);
		PlayerTextDrawColor(playerid, sp_ptd[playerid][1], -2139062017);
		PlayerTextDrawSetShadow(playerid, sp_ptd[playerid][1], 0);
		PlayerTextDrawSetOutline(playerid, sp_ptd[playerid][1], 0);
		PlayerTextDrawBackgroundColor(playerid, sp_ptd[playerid][1], 255);
		PlayerTextDrawFont(playerid, sp_ptd[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, sp_ptd[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, sp_ptd[playerid][1], 0);

		format(td_str, sizeof(td_str), "%d~n~%d~n~%.2f~n~%.2f~n~%d~n~%d~n~%d~n~%s~n~%d~n~$%s",
		PlayerInfo[params[0]][level],
		GetPlayerPing(params[0]),
		player_health,
		p_t_info[params[0]][p_armour],
		p_t_info[params[0]][p_gun_accuracy],
		GetPlayerAmmo(params[0]),
		get_speed(params[0]),
		p_t_info[params[0]][p_ip],
		get_player_warn_count(params[0]),
		convert_money(PlayerInfo[params[0]][money]));
		sp_ptd[playerid][2] = CreatePlayerTextDraw(playerid, 138.333206, 189.999862, td_str);
		PlayerTextDrawLetterSize(playerid, sp_ptd[playerid][2], 0.242082, 1.076297);
		PlayerTextDrawAlignment(playerid, sp_ptd[playerid][2], 3);
		PlayerTextDrawColor(playerid, sp_ptd[playerid][2], -1);
		PlayerTextDrawSetShadow(playerid, sp_ptd[playerid][2], 0);
		PlayerTextDrawSetOutline(playerid, sp_ptd[playerid][2], 0);
		PlayerTextDrawBackgroundColor(playerid, sp_ptd[playerid][2], 255);
		PlayerTextDrawFont(playerid, sp_ptd[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, sp_ptd[playerid][2], 1);
		PlayerTextDrawSetShadow(playerid, sp_ptd[playerid][2], 0);
		for(new j = 0; j < 7; j ++)
		{
			TextDrawShowForPlayer(playerid, sp_td[j]);
			if(j < 3) PlayerTextDrawShow(playerid, sp_ptd[playerid][j]);
		}
	}
	else
	{
		new td_str[98];
		format(td_str, 48, "%s(%d)", PlayerInfo[params[0]][name], params[0]);
		PlayerTextDrawSetString(playerid, sp_ptd[playerid][0], td_str);

		format(td_str, sizeof(td_str), "%d~n~%d~n~%.2f~n~%.2f~n~%d~n~%d~n~%d~n~%s~n~%d~n~$%s",
		PlayerInfo[params[0]][level],
		GetPlayerPing(params[0]),
		player_health,
		p_t_info[params[0]][p_armour],
		p_t_info[params[0]][p_gun_accuracy],
		GetPlayerAmmo(params[0]),
		get_speed(params[0]),
		p_t_info[params[0]][p_ip],
		get_player_warn_count(params[0]),
		convert_money(PlayerInfo[params[0]][money]));

		PlayerTextDrawSetString(playerid, sp_ptd[playerid][2], td_str);
	}
	switch(GetPlayerState(params[0]))
	{
		case 1:
		{
			SetPlayerInterior(playerid, p_t_info[params[0]][p_data][0]);
			SetPlayerVirtualWorld(playerid, p_t_info[params[0]][p_data][1]);
			TogglePlayerSpectating(playerid, true);
	   		PlayerSpectatePlayer(playerid, params[0]);
		}
		case 2:
		{
			SetPlayerInterior(playerid, p_t_info[params[0]][p_data][0]);
			SetPlayerVirtualWorld(playerid, p_t_info[params[0]][p_data][1]);
			new veh_id = GetPlayerVehicleID(params[0]);
			TogglePlayerSpectating(playerid, true);
			PlayerSpectateVehicle(playerid, veh_id);
		}
		case 3:
		{
			SetPlayerInterior(playerid, p_t_info[params[0]][p_data][0]);
			SetPlayerVirtualWorld(playerid, p_t_info[params[0]][p_data][1]);
	        new veh_id = GetPlayerVehicleID(params[0]);
	        TogglePlayerSpectating(playerid, true);
			PlayerSpectateVehicle (playerid, veh_id);
		}
	}
	in_recon_chat{playerid} = is_control_chat{playerid};
	is_control_chat{playerid} = PlayerInfo[params[0]][member];
	SetPVarInt(playerid, "spectate_status", params[0] + 1);
	return 1;
}

cmd:inter(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params,"i",params[0])) return SendInfo(playerid, "Enter: /inter [1-140]");
	if(params[0] > 140 && params[0] < 0) return SendInfo(playerid, "Enter: /inter [1-140]");


	switch(params[0])
	{
		case 1: SetPlayerPos(playerid,-25.884499,-185.868988,1003.549988), SetPlayerInterior(playerid, 17);
		case 2: SetPlayerPos(playerid,6.091180,-29.271898,1003.549988), SetPlayerInterior(playerid, 10);
		case 3: SetPlayerPos(playerid,-30.946699,-89.609596,1003.549988), SetPlayerInterior(playerid, 18);
		case 4: SetPlayerPos(playerid,-25.132599,-139.066986,1003.549988), SetPlayerInterior(playerid, 16);
		case 5: SetPlayerPos(playerid,-27.312300,-29.277599,1003.549988), SetPlayerInterior(playerid, 4);
		case 6: SetPlayerPos(playerid,-26.691599,-55.714897,1003.549988), SetPlayerInterior(playerid, 6);
		case 7: SetPlayerPos(playerid,-1827.147338,7.207418,1061.143554), SetPlayerInterior(playerid, 14);
		case 8: SetPlayerPos(playerid,2.384830,33.103397,1199.849976), SetPlayerInterior(playerid, 1);
		case 9: SetPlayerPos(playerid,315.856170,1024.496459,1949.797363), SetPlayerInterior(playerid, 9);
		case 10: SetPlayerPos(playerid,286.148987,-40.644398,1001.569946), SetPlayerInterior(playerid, 1);
		case 11: SetPlayerPos(playerid,286.800995,-82.547600,1001.539978), SetPlayerInterior(playerid, 4);
		case 12: SetPlayerPos(playerid,296.919983,-108.071999,1001.569946), SetPlayerInterior(playerid, 6);
		case 13: SetPlayerPos(playerid,314.820984,-141.431992,999.661987), SetPlayerInterior(playerid, 7);
		case 14: SetPlayerPos(playerid,316.524994,-167.706985,999.661987), SetPlayerInterior(playerid, 6);
		case 15: SetPlayerPos(playerid,302.292877,-143.139099,1004.062500), SetPlayerInterior(playerid, 7);
		case 16: SetPlayerPos(playerid,235.508994,1189.169897,1080.339966), SetPlayerInterior(playerid, 3);
		case 17: SetPlayerPos(playerid,225.756989,1240.000000,1082.149902), SetPlayerInterior(playerid, 2);
		case 18: SetPlayerPos(playerid,223.043991,1289.259888,1082.199951), SetPlayerInterior(playerid, 1);
		case 19: SetPlayerPos(playerid,225.630997,1022.479980,1084.069946), SetPlayerInterior(playerid, 7);
		case 20: SetPlayerPos(playerid,295.138977,1474.469971,1080.519897), SetPlayerInterior(playerid, 15);
		case 21: SetPlayerPos(playerid,328.493988,1480.589966,1084.449951), SetPlayerInterior(playerid, 15);
		case 22: SetPlayerPos(playerid,385.803986,1471.769897,1080.209961), SetPlayerInterior(playerid, 15);
		case 23: SetPlayerPos(playerid,375.971985,1417.269897,1081.409912), SetPlayerInterior(playerid, 15);
		case 24: SetPlayerPos(playerid,490.810974,1401.489990,1080.339966), SetPlayerInterior(playerid, 2);
		case 25: SetPlayerPos(playerid,447.734985,1400.439941,1084.339966), SetPlayerInterior(playerid, 2);
		case 26: SetPlayerPos(playerid,227.722992,1114.389893,1081.189941), SetPlayerInterior(playerid, 5);
		case 27: SetPlayerPos(playerid,260.983978,1286.549927,1080.299927), SetPlayerInterior(playerid, 4);
		case 28: SetPlayerPos(playerid,221.666992,1143.389893,1082.679932), SetPlayerInterior(playerid, 4);
		case 29: SetPlayerPos(playerid,27.132700,1341.149902,1084.449951), SetPlayerInterior(playerid, 10);
		case 30: SetPlayerPos(playerid,-262.601990,1456.619995,1084.449951), SetPlayerInterior(playerid, 4);
		case 31: SetPlayerPos(playerid,22.778299,1404.959961,1084.449951), SetPlayerInterior(playerid, 5);
		case 32: SetPlayerPos(playerid,140.278000,1368.979980,1083.969971), SetPlayerInterior(playerid, 5);
		case 33: SetPlayerPos(playerid,234.045990,1064.879883,1084.309937), SetPlayerInterior(playerid, 6);
		case 34: SetPlayerPos(playerid,-68.294098,1353.469971,1080.279907), SetPlayerInterior(playerid, 6);
		case 35: SetPlayerPos(playerid,-285.548981,1470.979980,1084.449951), SetPlayerInterior(playerid, 15);
		case 36: SetPlayerPos(playerid,-42.581997,1408.109985,1084.449951), SetPlayerInterior(playerid, 8);
		case 37: SetPlayerPos(playerid,83.345093,1324.439941,1083.889893), SetPlayerInterior(playerid, 9);
		case 38: SetPlayerPos(playerid,260.941986,1238.509888,1084.259888), SetPlayerInterior(playerid, 9);
		case 39: SetPlayerPos(playerid,1038.509888,-0.663752,1001.089966), SetPlayerInterior(playerid, 3);
		case 40: SetPlayerPos(playerid,446.622986,509.318970,1001.419983), SetPlayerInterior(playerid, 12);
		case 41: SetPlayerPos(playerid,2216.339844,-1150.509888,1025.799927), SetPlayerInterior(playerid, 15);
		case 42: SetPlayerPos(playerid,833.818970,7.418000,1004.179993), SetPlayerInterior(playerid, 3);
		case 43: SetPlayerPos(playerid,-100.325996,-22.816500,1000.741943), SetPlayerInterior(playerid, 3);
		case 44: SetPlayerPos(playerid,964.376953,2157.329834,1011.019958), SetPlayerInterior(playerid, 1);
		case 45: SetPlayerPos(playerid,-2239.569824,130.020996,1035.419922), SetPlayerInterior(playerid, 6);
		case 46: SetPlayerPos(playerid,662.641601,-571.398803,16.343263), SetPlayerInterior(playerid, 0);
		case 47: SetPlayerPos(playerid,614.581420,-23.066856,1004.781250), SetPlayerInterior(playerid, 1);
		case 48: SetPlayerPos(playerid,612.508605,-129.236114,1001.992187), SetPlayerInterior(playerid, 3);
		case 49: SetPlayerPos(playerid,-1786.603759,1215.553466,28.531250), SetPlayerInterior(playerid, 0);
		case 50: SetPlayerPos(playerid,-2048.605957,162.093444,28.835937), SetPlayerInterior(playerid, 1);
		case 51: SetPlayerPos(playerid,2170.284,1618.629,999.9766), SetPlayerInterior(playerid, 1);
		case 52: SetPlayerPos(playerid,1889.975,1018.055,31.88281), SetPlayerInterior(playerid, 10);
		case 53: SetPlayerPos(playerid,-2158.719971,641.287964,1052.369995), SetPlayerInterior(playerid, 1);
		case 54: SetPlayerPos(playerid,1133.069946,-9.573059,1000.750000), SetPlayerInterior(playerid, 12);
		case 55: SetPlayerPos(playerid,207.737991,-109.019997,1005.269958), SetPlayerInterior(playerid, 15);
		case 56: SetPlayerPos(playerid,204.332993,-166.694992,1000.578979), SetPlayerInterior(playerid, 14);
		case 57: SetPlayerPos(playerid,207.054993,-138.804993,1003.519958), SetPlayerInterior(playerid, 3);
		case 58: SetPlayerPos(playerid,203.778000,-48.492397,1001.799988), SetPlayerInterior(playerid, 1);
		case 59: SetPlayerPos(playerid,226.293991,-7.431530,1002.259949), SetPlayerInterior(playerid, 5);
		case 60: SetPlayerPos(playerid,161.391006,-93.159156,1001.804687), SetPlayerInterior(playerid, 18);
		case 61: SetPlayerPos(playerid,493.390991,-22.722799,1000.686951), SetPlayerInterior(playerid, 17);
		case 62: SetPlayerPos(playerid,501.980988,-69.150200,998.834961), SetPlayerInterior(playerid, 11);
		case 63: SetPlayerPos(playerid,-227.028000,1401.229980,27.769798), SetPlayerInterior(playerid, 18);
		case 64: SetPlayerPos(playerid,460.099976,-88.428497,999.621948), SetPlayerInterior(playerid, 4);
		case 65: SetPlayerPos(playerid,454.973950,-110.104996,999.717957), SetPlayerInterior(playerid, 5);
		case 66: SetPlayerPos(playerid,452.489990,-18.179699,1001.179993), SetPlayerInterior(playerid, 1);
		case 67: SetPlayerPos(playerid,681.474976,-451.150970,-25.616798), SetPlayerInterior(playerid, 1);
		case 68: SetPlayerPos(playerid,366.923980,-72.929359,1001.507812), SetPlayerInterior(playerid, 10);
		case 69: SetPlayerPos(playerid,365.672974,-10.713200,1001.869995), SetPlayerInterior(playerid, 9);
		case 70: SetPlayerPos(playerid,372.351990,-131.650986,1001.449951), SetPlayerInterior(playerid, 5);
		case 71: SetPlayerPos(playerid,377.098999,-192.439987,1000.643982), SetPlayerInterior(playerid, 17);
		case 72: SetPlayerPos(playerid,244.411987,305.032990,999.231995), SetPlayerInterior(playerid, 1);
		case 73: SetPlayerPos(playerid,271.884979,306.631989,999.325989), SetPlayerInterior(playerid, 2);
		case 74: SetPlayerPos(playerid,291.282990,310.031982,999.154968), SetPlayerInterior(playerid, 3);
		case 75: SetPlayerPos(playerid,302.181000,300.722992,999.231995), SetPlayerInterior(playerid, 4);
		case 76: SetPlayerPos(playerid,322.197998,302.497986,999.231995), SetPlayerInterior(playerid, 5);
		case 77: SetPlayerPos(playerid,346.870025,309.259033,999.155700), SetPlayerInterior(playerid, 6);
		case 78: SetPlayerPos(playerid,-959.873962,1952.000000,9.044310), SetPlayerInterior(playerid, 17);
		case 79: SetPlayerPos(playerid,388.871979,173.804993,1008.389954), SetPlayerInterior(playerid, 3);
		case 80: SetPlayerPos(playerid,220.4109,1862.277,13.147), SetPlayerInterior(playerid, 0);
		case 81: SetPlayerPos(playerid,772.112000,-3.898650,1000.687988), SetPlayerInterior(playerid, 5);
		case 82: SetPlayerPos(playerid,774.213989,-48.924297,1000.687988), SetPlayerInterior(playerid, 6);
		case 83: SetPlayerPos(playerid,773.579956,-77.096695,1000.687988), SetPlayerInterior(playerid, 7);
		case 84: SetPlayerPos(playerid,1527.229980,-11.574499,1002.269958), SetPlayerInterior(playerid, 3);
		case 85: SetPlayerPos(playerid,1523.509888,-47.821198,1002.269958), SetPlayerInterior(playerid, 2);
		case 86: SetPlayerPos(playerid,2496.049805,-1693.929932,1014.750000), SetPlayerInterior(playerid, 3);
		case 87: SetPlayerPos(playerid,1263.079956,-785.308960,1091.959961), SetPlayerInterior(playerid, 5);
		case 88: SetPlayerPos(playerid,1291.725341,-788.319885,96.460937), SetPlayerInterior(playerid, 0);
		case 89: SetPlayerPos(playerid,516.650,-18.611898,1001.459961), SetPlayerInterior(playerid, 3);
		case 90: SetPlayerPos(playerid,2464.109863,-1698.659912,1013.509949), SetPlayerInterior(playerid, 2);
		case 91: SetPlayerPos(playerid,2526.459961,-1679.089966,1015.500000), SetPlayerInterior(playerid, 1);
		case 92: SetPlayerPos(playerid,2543.659912,-1303.629883,1025.069946), SetPlayerInterior(playerid, 2);
		case 93: SetPlayerPos(playerid,1212.019897,-28.663099,1001.089966), SetPlayerInterior(playerid, 3);
		case 94: SetPlayerPos(playerid,744.542969,1437.669922,1102.739990), SetPlayerInterior(playerid, 6);
		case 95: SetPlayerPos(playerid,1204.809937,-11.586800,1001.089966), SetPlayerInterior(playerid, 2);
		case 96: SetPlayerPos(playerid,1204.809937,13.586800,1001.089966), SetPlayerInterior(playerid, 2);
		case 97: SetPlayerPos(playerid,940.921997,-17.007000,1001.179993), SetPlayerInterior(playerid, 3);
		case 98: SetPlayerPos(playerid,964.106995,-53.205498,1001.179993), SetPlayerInterior(playerid, 3);
		case 99: SetPlayerPos(playerid,-2661.009766,1415.739990,923.305969), SetPlayerInterior(playerid, 3);
		case 100: SetPlayerPos(playerid,-2637.449951,1404.629883,906.457947), SetPlayerInterior(playerid, 3);
		case 101: SetPlayerPos(playerid,-735.5619504,484.351318,1371.952270), SetPlayerInterior(playerid, 1);
		case 102: SetPlayerPos(playerid,-794.8064,491.6866,1376.195), SetPlayerInterior(playerid, 1);
		case 103: SetPlayerPos(playerid,-835.2504,500.9161,1358.305), SetPlayerInterior(playerid, 1);
		case 104: SetPlayerPos(playerid,-813.431518,533.231079,1390.782958), SetPlayerInterior(playerid, 1);
		case 105: SetPlayerPos(playerid,2350.339844,-1181.649902,1028.000000), SetPlayerInterior(playerid, 5);
		case 106: SetPlayerPos(playerid,2807.619873,-1171.899902,1025.579956), SetPlayerInterior(playerid, 8);
		case 107: SetPlayerPos(playerid,318.564972,1118.209961,1083.979980), SetPlayerInterior(playerid, 5);
		case 108: SetPlayerPos(playerid,1412.639893,-1.787510,1000.931946), SetPlayerInterior(playerid, 1);
		case 109: SetPlayerPos(playerid,1302.519897,-1.787510,1000.931946), SetPlayerInterior(playerid, 18);
		case 110: SetPlayerPos(playerid,2522.0,-1673.383911,14.8), SetPlayerInterior(playerid, 0);
		case 111: SetPlayerPos(playerid,-219.322601,1410.444824,27.773437), SetPlayerInterior(playerid, 18);
		case 112: SetPlayerPos(playerid,2324.419922,-1147.539917,1050.719971), SetPlayerInterior(playerid, 12);
		case 113: SetPlayerPos(playerid,-972.4957,1060.983,1358.914), SetPlayerInterior(playerid, 10);
		case 114: SetPlayerPos(playerid,411.625977,-21.433298,1001.799988), SetPlayerInterior(playerid, 2);
		case 115: SetPlayerPos(playerid,418.652985,-82.639793,1001.959961), SetPlayerInterior(playerid, 3);
		case 116: SetPlayerPos(playerid,412.021973,-52.649899,1001.959961), SetPlayerInterior(playerid, 12);
		case 117: SetPlayerPos(playerid,-204.439987,-26.453999,1002.299988), SetPlayerInterior(playerid, 16);
		case 118: SetPlayerPos(playerid,-204.439987,-8.469600,1002.299988), SetPlayerInterior(playerid, 17);
		case 119: SetPlayerPos(playerid,-204.439987,-43.652496,1002.299988), SetPlayerInterior(playerid, 3);
		case 120: SetPlayerPos(playerid,246.783997,63.900200,1003.639954), SetPlayerInterior(playerid, 6);
		case 121: SetPlayerPos(playerid,246.375992,109.245995,1003.279968), SetPlayerInterior(playerid, 10);
		case 122: SetPlayerPos(playerid,288.745972,169.350998,1007.179993), SetPlayerInterior(playerid, 3);
		case 123: SetPlayerPos(playerid,1494.429932,1305.629883,1093.289917), SetPlayerInterior(playerid, 3);
		case 124: SetPlayerPos(playerid,-2029.719971,-115.067993,1035.169922), SetPlayerInterior(playerid, 3);
		case 125: SetPlayerPos(playerid,420.484985,2535.589844,10.020289), SetPlayerInterior(playerid, 10);
		case 126: SetPlayerPos(playerid,-2184.751464,2413.111816,5.156250), SetPlayerInterior(playerid, 0);
		case 127: SetPlayerPos(playerid,-1397.782470,-203.723114,1051.346801), SetPlayerInterior(playerid, 7);
		case 128: SetPlayerPos(playerid,-1398.103515,933.445434,1041.531250), SetPlayerInterior(playerid, 15);
		case 129: SetPlayerPos(playerid,-1428.809448,-663.595886,1060.219848), SetPlayerInterior(playerid, 4);
		case 130: SetPlayerPos(playerid,-1486.861816,1642.145996,1060.671875), SetPlayerInterior(playerid, 14);
		case 131: SetPlayerPos(playerid,-1401.830000,107.051300,1032.273000), SetPlayerInterior(playerid, 1);
		case 132: SetPlayerPos(playerid,1382.615600,2184.345703,11.023437), SetPlayerInterior(playerid, 0);
		case 133: SetPlayerPos(playerid,297.9414,-64.3876,1001.5156), SetPlayerInterior(playerid, 4);
		case 134: SetPlayerPos(playerid,302.1602,-164.7588,999.6105), SetPlayerInterior(playerid, 6);
		case 135: SetPlayerPos(playerid,614.31,-125.22,997.99), SetPlayerInterior(playerid, 3);
		case 136: SetPlayerPos(playerid,72.03800201,394.72299194,1041.23596191), SetPlayerInterior(playerid, 5);
		case 137: SetPlayerPos(playerid,258.6563,-42.7578,1001.0234), SetPlayerInterior(playerid, 14);
		case 138: SetPlayerPos(playerid,1887.25000000,508.48001099,1204.37194824), SetPlayerInterior(playerid, 5);
		case 139: SetPlayerPos(playerid,1583.48498535,534.78302002,1128.39794922), SetPlayerInterior(playerid, 5);
		case 140: SetPlayerPos(playerid,2527.09692383,464.17098999,2636.01293945), SetPlayerInterior(playerid, 8);
	}
	return 1;
}

cmd:asettime(playerid, params[])
{
	if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params, "ddd", params[0], params[1], params[2])) return SendInfo(playerid, "Enter: /asettime [hours] [minutes] [seconds]");
    if(params[0] > 23 || params[0] < 0) return SendInfo(playerid, "Enter: /asettime [hours] [minutes] [seconds]");
    if(params[1] > 59 || params[1] < 0) return SendInfo(playerid, "Enter: /asettime [hours] [minutes] [seconds]");
    if(params[2] > 59 || params[2] < 0) return SendInfo(playerid, "Enter: /asettime [hours] [minutes] [seconds]");
	timestamp_hour = params[0];
	SetWorldTime(params[0]);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] set a new time on the server %d:%d:%d.", PlayerInfo[playerid][name], playerid, params[0], params[1], params[2]);

	return 1;
}

cmd:ipaccounts(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	new ban_ip[16];
	if(sscanf(params, "s[16]", ban_ip)) return SendInfo(playerid, "Enter: /ipaccounts [ип]");


	new sql_string[178];
	mysql_format(sql_connection, sql_string, 178, "SELECT `u_name`,`u_last_date`,`u_online`,`u_level` FROM `users` WHERE `u_last_ip` = '%s' OR `u_ip_registration` = '%s' LIMIT 25",
	ban_ip, ban_ip);
	mysql_tquery(sql_connection, sql_string, "cmd_ipaccounts_callback", "i", playerid);

	return 1;
}

callback:cmd_ipaccounts_callback(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"No data found for the given ip address.");
	global_string[0] = EOS;
	for(new j = 0; j < rows; j ++)
	{
		new pl_name[24], pl_date[28], u_online, line_string[98], pl_level;
		u_online = cache_get_field_content_int(j, "u_online", sql_connection);
		pl_level = cache_get_field_content_int(j, "u_level", sql_connection);

		cache_get_field_content(j, "u_name", pl_name, sql_connection, 24);
		cache_get_field_content(j, "u_last_date", pl_date, sql_connection, 28);

		if(u_online)format(line_string, sizeof(line_string), ""c_white"%s (LVL:%d) -"c_green"ONLINE\t"c_white"%s\n", pl_name, pl_level, pl_date);
		else format(line_string, sizeof(line_string), ""c_white"%s (LVL:%d) -"c_orange_red"OFFLINE\t"c_white"%s\n", pl_name, pl_level, pl_date);
		strcat(global_string, line_string);
	}
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Account List", global_string, "Bastan", "");
	return 1;
}

cmd:banip(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	new ban_ip[16], ban_reason_ip[32];
	if(sscanf(params,"s[16]s[32]", ban_ip, ban_reason_ip)) return SendInfo(playerid, "Enter: /banip [ip] [reason]");
	if(strfind(ban_ip, "*.*", true)!= -1) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Wrong ip address.");

	SendRcon("banip %s", ban_ip);
	SendRconCommand("reloadbans");

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] blocked IP %s. Reason: %s", PlayerInfo[playerid][name], playerid, ban_ip, ban_reason_ip);

	return 1;
}

cmd:unbanip(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params,"s[16]",params[0])) return SendInfo(playerid, "Enter: /unbanip [IP]");
	if(strfind(params[0], "*.*", true)!= -1) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Wrong ip address.");

	SendRcon("unbanip %s", params[0]);
	SendRconCommand("reloadbans");

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] unlocked IP %s.", PlayerInfo[playerid][name], playerid, params[0]);

	return 1;
}

cmd:setfvehiclemodel(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(GetPlayerState(playerid)!= PLAYER_STATE_DRIVER) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You need to be in transport.");
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /setfvehiclemodel [mode]");
    if(params[0] < 400 || params[0] > 611) return SendInfo(playerid, "Enter: /setfvehiclemodel [modeель]");

    new veh_id = GetPlayerVehicleID(playerid);
    if(GetPVarInt(playerid, "admin_vehicle") == veh_id) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Data transport is not dynamic.");

	DestroyVehicle(veh_id);

	veh_info[veh_id -1][v_vehicle] = INVALID_VEHICLE_ID;
	veh_info[veh_id -1][v_model] = params[0];

    if(veh_info[veh_id -1][v_owner] == 1)veh_info[veh_id -1][v_vehicle] = CreateVehicle(veh_info[veh_id -1][v_model], veh_info[veh_id -1][v_pos][0], veh_info[veh_id -1][v_pos][1], veh_info[veh_id -1][v_pos][2], veh_info[veh_id -1][v_pos][3], veh_info[veh_id -1][v_color][0], veh_info[veh_id -1][v_color][1], -1, 1);
	else veh_info[veh_id -1][v_vehicle] = CreateVehicle(veh_info[veh_id -1][v_model], veh_info[veh_id -1][v_pos][0], veh_info[veh_id -1][v_pos][1], veh_info[veh_id -1][v_pos][2], veh_info[veh_id -1][v_pos][3], veh_info[veh_id -1][v_color][0], veh_info[veh_id -1][v_color][1], -1);
	SetVehicleNumberPlate(veh_info[veh_id -1][v_vehicle], veh_info[veh_id -1][v_plate]);
	veh_info[veh_id -1][v_fuel] = 60.0;

	new sql_string[76];
	mysql_format(sql_connection, sql_string, 76, "UPDATE `server_vehicles` SET `sv_model` = '%d' WHERE `sv_id` = '%d'",
	veh_info[veh_id -1][v_model],
	veh_info[veh_id -1][v_id]);
	mysql_tquery(sql_connection, sql_string, "", "");

    SendClientMessage(playerid, col_white, "The transport model of the organization has been successfully changed.");
	return 1;
}

cmd:setfvehiclecolor(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
    if(GetPlayerState(playerid)!= PLAYER_STATE_DRIVER) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You need to be in transit.");
    if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /setfvehiclecolor [color 1] [color 2]") ;
    new veh_id = GetPlayerVehicleID(playerid);
    if(GetPVarInt(playerid, "admin_vehicle") == veh_id) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Data transport is not dynamic.");

    if(params[1] < 0 || params[1] > 255) return SendInfo(playerid, "Enter: /setfvehiclecolor [color 1] [color 2]");
    if(params[0] < 0 || params[0] > 255) return SendInfo(playerid, "Enter: /setfvehiclecolor [color 1] [color 2]");

	veh_info[veh_id -1][v_color][0] = params[0];
	veh_info[veh_id -1][v_color][1] = params[1];

	n_ChangeVehicleColor(veh_id, params[0], params[1]);

	new sql_string[128];
	mysql_format(sql_connection, sql_string, 128, "UPDATE `server_vehicles` SET `sv_color_1` = '%d',`sv_color_2` = '%d' WHERE `sv_id` = '%d'",
	params[0], params[1],
	veh_info[veh_id -1][v_id]);
	mysql_query(sql_connection, sql_string);

    SendClientMessage(playerid, col_white, "The organization's transport color has been successfully changed.");
	return 1;
}


cmd:givelic(playerid,params[])
{
	if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /givelic [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");


    show_dialog(playerid, d_give_lic, DIALOG_STYLE_LIST,""c_server"Give license",
    ""c_white"Driver's license\nPilot license\nWater transport license\nLicense n a weapon", "Entekhab", "Cancel");
	SetPVarInt(playerid,"gl_id", params[0]);
	return 1;
}

cmd:giveskill(playerid,params[])
{
	if(check_admin_rank(playerid , 6)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /giveskill [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	for(new j = 0; j < 7; j ++)
	{
		PlayerInfo[params[0]][gun_skills][j] = 100;
	}
	new _query[128];

	format(_query, sizeof(_query), "UPDATE `users` SET `u_skills`='%d|%d|%d|%d|%d|%d|%d' WHERE `u_id` = '%d'",
	PlayerInfo[params[0]][gun_skills][0], PlayerInfo[params[0]][gun_skills][1], PlayerInfo[params[0]][gun_skills][2],
	PlayerInfo[params[0]][gun_skills][3], PlayerInfo[params[0]][gun_skills][4], PlayerInfo[params[0]][gun_skills][5],
	PlayerInfo[params[0]][gun_skills][6], PlayerInfo[params[0]][id]);
	mysql_tquery(sql_connection, _query);
	SetPlayerSkills(params[0]);

	AdminMes(""c_server"* A.INFO: "c_grey"%s issued %s weapon skills.", PlayerInfo[playerid][name], PlayerInfo[params[0]][name]);

	format(_query, sizeof(_query), ""c_server"* S.INFO:"c_grey" %s set you to perfect weapon skills.", PlayerInfo[playerid][name]);
	SendClientMessage(params[0], col_gray, _query);
	return 1;
}


cmd:makeleader(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /makeleader [id Bazikon]");
	if(!IsPlayerConnected(targetid)) return SendError(playerid, "Bazikon Yaft Nashod.");

	SetPVarInt(playerid, !"target_id", targetid);

	strfmt(global_string, "{BC2C2C}Removal from the post of leader\n");
	new line_string[65];

	for(new j = 0; j < fraction_count; j++)
	{
		format(line_string, sizeof(line_string), ""c_server"%d | {%s}%s\n", j + 1, f_info[j][f_chat_color], f_info[j][f_name]);
		strcat(global_string, line_string);
	}
	new header_string[45];
	format(header_string, sizeof(header_string), ""scm_dialog"%s", PlayerInfo[playerid][name]);
	return show_dialog(playerid, d_makeleader, DIALOG_STYLE_LIST, header_string, global_string, !"Entekhab", !"Bastan");
}

cmd:templeader(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /templeader [organization number]");
	if(params[0] < 0 || params[0] > fraction_count) return SendError(playerid, "Wrong organization number.");

	if(params[0] != 0)
	{
		params[0] -= 1;
		
		AdminMes(""c_server"* A.INFO:"c_grey" %s appointed himself interim leader of the organization \""c_white"%s"c_grey"\"", PlayerInfo[playerid][name], f_info[params[0]][f_name]);

		PlayerInfo[playerid][member] = PlayerInfo[playerid][leader] =  params[0] + 1;
		PlayerInfo[playerid][rank] = f_info[params[0]][f_rank_settings][0];
		PlayerInfo[playerid][org_skin] = f_skin[params[0]][PlayerInfo[playerid][gender]][0]	;
	}
	else if(params[0] == 0 && playerLeaderStatus(playerid))
	{
		AdminMes(""c_server"* A.INFO:"c_grey" %s removed himself from the post of interim leader of the organization \""c_white"%s"c_grey"\"", PlayerInfo[playerid][name], f_info[PlayerInfo[params[0]][member]][f_name]);

		// ----------------------
		// Top War
		new topWarTarget = playerid;
		if(PlayerInfo[topWarTarget][member] == TopWarGangAttacker || PlayerInfo[topWarTarget][member] == TopWarGangProtector) {
			TopWar_HideSmallTopWarInfo(topWarTarget);

			//Reset Vars
			for(new GangPlayerEnum:i; i < GangPlayerEnum; i++) GangPlayer[topWarTarget][i] = 0;
		}
		// ----------------------

		PlayerInfo[playerid][member] = -1;
		PlayerInfo[playerid][leader] = -1;
		PlayerInfo[playerid][rank] = 0;

		UpdatePlayerName(playerid);

		SetPlayerSkin(playerid, PlayerInfo[playerid][skin]);
		SetPlayerColor(playerid, 0xFFFFFF40);
	}
	return 1;
}

cmd:unmakeleader(playerid, params[])
{
	if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params, "us[70]", params[0], params[1])) return SendInfo(playerid, "Enter: /unmakeleader [id/name] [reason]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	if(!playerLeaderStatus(playerid))	return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The player does not have organization leader rights.");

	new scm_string[144];
	AdminMes(""c_server"* A.INFO:"c_grey" %s removed %s as organization leader \""c_white"%s"c_grey"\"", PlayerInfo[playerid][name], PlayerInfo[params[0]][name], f_info[PlayerInfo[params[0]][member]][f_name]);

	format(scm_string, sizeof scm_string, ""c_server"* S.INFO:"c_grey" %s removed Vass from the position of the leader of the organization \""c_white"%s"c_grey"\"", PlayerInfo[playerid][name], f_info[PlayerInfo[params[0]][member]][f_name]);
	SendClientMessage(params[0], col_gray, scm_string);

	UpdateGangDormLabel(PlayerInfo[playerid][member]);

	addWorkBook(params[0], PlayerInfo[playerid][name], params[1]);

	new query_string[268];

	if(PlayerInfo[params[0]][admin] != 0)
	{
		format(f_info[PlayerInfo[params[0]][member]][f_leader_name], MAX_PLAYER_NAME, "Free");
		format(query_string, 100, "UPDATE `fractions` SET `f_leader_name` = '%s' WHERE `f_id` = '%d' LIMIT 1",
		f_info[PlayerInfo[params[0]][member]][f_leader_name], PlayerInfo[params[0]][member]);
		mysql_tquery(sql_connection, query_string, "", "");
	}

	// ----------------------
	// Top War
	new topWarTarget = params[0];
	if(PlayerInfo[topWarTarget][member] == TopWarGangAttacker || PlayerInfo[topWarTarget][member] == TopWarGangProtector) {
		TopWar_HideSmallTopWarInfo(topWarTarget);

		//Reset Vars
		for(new GangPlayerEnum:i; i < GangPlayerEnum; i++) GangPlayer[topWarTarget][i] = 0;
	}

	return 1;
}

cmd:afind(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /afind [organization number]");
	if(params[0] < 0 || params[0] > fraction_count) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid organization number.");
	global_string[0] = EOS;

	new line_string[92],
		fr_count;

	foreach(new i: logged_players)
	{
		if(PlayerInfo[i][member] != params[0]) continue;
		fr_count ++;
	}
	format(line_string, sizeof(line_string), ""c_white"All online: {cccc99}%d\nID\tlevel\tphone\trange\treprimands\tИmy player\n\n"c_white"", fr_count);
	strcat(global_string, line_string);

	foreach(new i: logged_players)
	{
	    if(PlayerInfo[i][member] != params[0]) continue;

		format(line_string, sizeof(line_string), "%d\t%d\t\t%d\t\t%d\t0/3\t\t%s%s\n", i, PlayerInfo[i][level], PlayerInfo[i][number], PlayerInfo[i][rank], PlayerInfo[i][name],
		(pl_afk_time[i] >= 2)?("{FFB859}[AFK]"c_white""):(""));
		strcat(global_string, line_string);
	}
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Members of the online organization", global_string, "Bastan", "");
	return 1;
}

cmd:achat(playerid, params[])
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /achat [organization number]");
	if(params[0] < 0 || params[0] > fraction_count) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Incorrect organization number.");
	is_control_chat {playerid} = params[0];
	if(params[0] == 0)
	{
		SendClientMessage(playerid, col_gray, ""c_server"* A.INFO:"c_grey" Gosh dadn be chat sazman ro khamosh kard.");
	}
	else
	{
		new t_string[116];
		format(t_string, sizeof(t_string), ""c_server"* A.INFO:"c_grey" shoma start be gosh kardn chat sazman kardid \""c_white"%s"c_grey"\"", f_info[params[0]][f_name]);
		SendClientMessage(playerid, col_gray, t_string);
	}
	return 1;
}

cmd:paydaytest(playerid)
{
	if(check_admin_rank(playerid , 8)) return 1;
	pay_day_time();
	return 1;
}


cmd:auninvite(playerid, params[])
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(sscanf(params, "us[48]", params[0], params[1])) return SendInfo(playerid, "Enter: /auninvite [id/name] [reason]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");
    if(!playerFactionStatus(params[0])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Player is not in the organization.");
    if(playerLeaderStatus(params[0])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"The player is the leader.");

	new scm_string[266];
	format(scm_string, 144, ""c_server"* S.INFO: "c_grey"Admin %s[%i] fired you from the organization. Reason:"c_white" %s", PlayerInfo[playerid][name], playerid, params[1]);
	SendClientMessage(params[0], col_gray, scm_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] fired %s[%d] from the organization. Reason: %s", PlayerInfo[playerid][name], playerid, PlayerInfo[params[0]][name], params[0], params[1]);

	addWorkBook(params[0], PlayerInfo[playerid][name], params[1]);

	// ----------------------
	// Top War
	new topWarTarget = params[0];
	if(PlayerInfo[topWarTarget][member] == TopWarGangAttacker || PlayerInfo[topWarTarget][member] == TopWarGangProtector) {
		TopWar_HideSmallTopWarInfo(topWarTarget);

		//Reset Vars
		for(new GangPlayerEnum:i; i < GangPlayerEnum; i++) GangPlayer[topWarTarget][i] = 0;
	}
	// ----------------------
	reset_player_weapon(params[0]);
	return 1;
}

cmd:promocodelist(playerid)
{
	if(check_admin_rank(playerid , 1)) return 1;

	mysql_tquery(sql_connection, "SELECT * FROM `server_promocodes` ORDER BY promo_id", "promo_code_list", "i", playerid);
	return 1;
}
alias:promocodelist("pcl");

cmd:gzowner(playerid)
{
	if(check_admin_rank(playerid , 4)) return 1;
	
	show_dialog(playerid, d_gzowner, DIALOG_STYLE_LIST, !""scm_dialog"Issuance of the Territory",
    !"Grove Street\n\
	Ballas\n\
	Los Santos Vagos\n\
	Rifa\n\
	Varios Los Aztecas", !"Set", !"Bastan");
	
	return 1;
}

cmd:gzid(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
    for(new i = 0; i < gz_count; i ++)
	{
		if(IsPlayerInGangZone(playerid, i))
		{
			new t_string[98];
			format(t_string, sizeof(t_string), "Gangzone cellid: %d", gz_info[i][gz_id]);
			SendClientMessage(playerid, -1, t_string);
			break;
		}
	}
	return 1;
}

cmd:orglist(playerid)
{
	if(check_admin_rank(playerid , 3)) return 1;
	global_string[0] = EOS;
	for(new j = 0; j < fraction_count; j ++)
	{
		new line_string[64];
		format(line_string, 64, ""c_white"ID:%d -{%s}%s\n", j + 1, f_info[j][f_chat_color], f_info[j][f_name]);
		strcat(global_string, line_string);
	}
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"List of organizations", global_string, "Bastan", "");

	return 1;
}

cmd:vlock(playerid)
{
	if(check_admin_rank(playerid , 4)) return 1;
	if(IsValidVehicle(GetPlayerVehicleID(playerid)))
	{
		new veh_id = GetPlayerVehicleID(playerid);
		if(veh_info[veh_id -1][v_type] == vehicle_type_family) return 1;

		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		if(veh_info[veh_id -1][v_locked])
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;

			veh_info[veh_id -1][v_locked] = false;
			GetVehicleParamsEx(veh_id, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(veh_id, engine, lights, alarm, false, bonnet, boot, objective);
		}
		else
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;

			veh_info[veh_id -1][v_locked] = true;
			GetVehicleParamsEx(veh_id, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(veh_id, engine, lights, alarm, true, bonnet, boot, objective);
		}
	}
	else
	{
		foreach(new veh_id:streamed_vehicles[playerid])
		{
			if(IsVehicleInRangeOfPoint(veh_id, 5.0, p_t_info[playerid][p_pos][0], p_t_info[playerid][p_pos][1], p_t_info[playerid][p_pos][2])){}
			else continue;
			if(veh_info[veh_id -1][v_type] == vehicle_type_family) continue;
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			if(veh_info[veh_id -1][v_locked])
			{
				new engine, lights, alarm, doors, bonnet, boot, objective;

				veh_info[veh_id -1][v_locked] = false;
				GetVehicleParamsEx(veh_id, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(veh_id, engine, lights, alarm, false, bonnet, boot, objective);
				GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~ CAR UNLOCK", 3000, 3);
				break;
			}
			else
			{
				new engine, lights, alarm, doors, bonnet, boot, objective;

				veh_info[veh_id -1][v_locked] = true;
				GetVehicleParamsEx(veh_id, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(veh_id, engine, lights, alarm, true, bonnet, boot, objective);
				GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~ CAR LOCK", 3000, 3);
				break;
			}
		}
	}
	return 1;
}

cmd:fspawnchange(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /fspawnchange [organization]");
	if(params[0] < 0 || params[0] > fraction_count) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid Organization ID.");
	params[0] --;
	GetPlayerPos(playerid, f_info[params[0]][f_spawn][0], f_info[params[0]][f_spawn][1], f_info[params[0]][f_spawn][2]);
	GetPlayerFacingAngle(playerid, f_info[params[0]][f_spawn][3]);

	f_info[params[0]][f_spawn_int] = GetPlayerInterior(playerid);
	f_info[params[0]][f_spawn_virt] =  GetPlayerVirtualWorld(playerid);

	new sql_string[82 + 9 * 4];
	format(sql_string, sizeof(sql_string), "Shoma Ba Movafghiat changed the location of the organization \"%s\".",
	f_info[params[0]][f_name]);
	SendClientMessage(playerid, col_succes, sql_string);

	mysql_format(sql_connection, sql_string, sizeof(sql_string), "UPDATE `fractions` SET `f_spawn` = '%f|%f|%f|%f|%d|%d' WHERE `f_id` = '%d' LIMIT 1",
	f_info[params[0]][f_spawn][0], f_info[params[0]][f_spawn][1], f_info[params[0]][f_spawn][2],
	f_info[params[0]][f_spawn][3],
	f_info[params[0]][f_spawn_int],
	f_info[params[0]][f_spawn_virt],
	f_info[params[0]][f_id]);
	mysql_tquery(sql_connection, sql_string, "", "");
	return 1;
}

cmd:ears(playerid)
{
	if(check_admin_rank(playerid , 2)) return 1;
	if(big_ears {playerid} == 0)
	{
		big_ears {playerid} = 1;
		SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You turned on Tracking Mode SMS.");
	}
	else
	{
		big_ears {playerid} = 0;
		SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You turned off tracking mode SMS.");
	}
	return 1;
}

cmd:getskill(playerid, params[])
{
	if(check_admin_rank(playerid , 1)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /getskill [id/name]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	global_string[0] = EOS;

	format(global_string, 1000, ""c_white"SDPistol:\t[%s]%d\nDeagle:\t[%s]%d\nShotGun:\t[%s]%d\nMP5\t\t[%s]%d\nAK47:\t\t[%s]%d\nM4A1:\t\t[%s]%d\nRifle:\t\t[%s]%d",
	ToDevelopSkills(PlayerInfo[params[0]][gun_skills][0],100 -PlayerInfo[params[0]][gun_skills][0]),PlayerInfo[params[0]][gun_skills][0],
	ToDevelopSkills(PlayerInfo[params[0]][gun_skills][1],100 -PlayerInfo[params[0]][gun_skills][1]),PlayerInfo[params[0]][gun_skills][1],
	ToDevelopSkills(PlayerInfo[params[0]][gun_skills][2],100 -PlayerInfo[params[0]][gun_skills][2]),PlayerInfo[params[0]][gun_skills][2],
	ToDevelopSkills(PlayerInfo[params[0]][gun_skills][3],100 -PlayerInfo[params[0]][gun_skills][3]),PlayerInfo[params[0]][gun_skills][3],
	ToDevelopSkills(PlayerInfo[params[0]][gun_skills][4],100 -PlayerInfo[params[0]][gun_skills][4]),PlayerInfo[params[0]][gun_skills][4],
	ToDevelopSkills(PlayerInfo[params[0]][gun_skills][5],100 -PlayerInfo[params[0]][gun_skills][5]),PlayerInfo[params[0]][gun_skills][5],
	ToDevelopSkills(PlayerInfo[params[0]][gun_skills][6],100 -PlayerInfo[params[0]][gun_skills][6]),PlayerInfo[params[0]][gun_skills][6]);
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX,""c_server"Weapon Skills", global_string, "Bastan", "");

	return 1;
}

cmd:createservervehicle(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(GetPlayerState(playerid)!= PLAYER_STATE_DRIVER) 
	    return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You must be in transport.");
    
	if(sscanf(params, "dds[12]d", params[0], params[1], params[2], params[3], params[4])) 
	    return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey" Enter: /createservervehicle [model] [owner] [type] [color 1] [color 2]");
    
	if(params[0] < 400 || params[0] > 611) 
	    return SendInfo(playerid, "Enter: /createservervehicle [model] [owner] [type] [color 1] [color 2]");
	
	new veh_id = GetPlayerVehicleID(playerid);

	for(new i = 1; i < MAX_VEHICLES; i ++)
	{
		if(veh_info[i -1][v_deleted] == 1) continue;
		if(IsValidVehicle(i)) continue;

		veh_info[i -1][v_owner] = params[1];
		veh_info[i -1][v_model] = params[0];
		format(veh_info[i -1][v_plate], 12, "%s", f_info[getFactionID(params[1])][f_name]);

		GetVehiclePos(veh_id, veh_info[i -1][v_pos][0], veh_info[i -1][v_pos][1], veh_info[i -1][v_pos][2]);
		GetVehicleZAngle(veh_id, veh_info[i -1][v_pos][3]);

		veh_info[i -1][v_rank] = 0;
		veh_info[i -1][v_type] = params[2];
		
        new respawn = (veh_info[i -1][v_owner] == 1) ? 1 : -1;
        veh_info[i -1][v_vehicle] = CreateVehicle(
            veh_info[i -1][v_model],
            veh_info[i -1][v_pos][0],
            veh_info[i -1][v_pos][1],
            veh_info[i -1][v_pos][2],
            veh_info[i -1][v_pos][3],
            veh_info[i -1][v_color][0],
            veh_info[i -1][v_color][1],
            -1,
            respawn
        );

		SetVehicleNumberPlate(veh_info[i -1][v_vehicle], veh_info[i -1][v_plate]);
		veh_info[i -1][v_fuel] = 60.0;

		new sql_string[288];
		mysql_format(sql_connection, sql_string, 288, 
		    "INSERT INTO `server_vehicles` (`sv_model`,`sv_owner`,`sv_plate`,`sv_color_1`,`sv_color_2`,`sv_pos_x`,`sv_pos_y`,`sv_pos_z`,`sv_pos_a`,`sv_type`) \
		    VALUES ('%d','%d','%e','%s','%s','%f','%f','%f','%f','%d')",
		    params[0], params[1], f_info[getFactionID(params[1])][f_name], params[3], params[4],
		    veh_info[i -1][v_pos][0], veh_info[i -1][v_pos][1], veh_info[i -1][v_pos][2], veh_info[i -1][v_pos][3], params[2]);
		
		mysql_tquery(sql_connection, sql_string, "create_vehicle_callback", "d", i);
		break;
	}
	SendClientMessage(playerid, col_white, "Transport created successfully.");
	return 1;
}

cmd:deleteservervehicle(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(GetPlayerState(playerid)!= PLAYER_STATE_DRIVER) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You must be in transport.");
	new veh_id = GetPlayerVehicleID(playerid);
	new sql_string[78];
	for(new i = 1; i < MAX_VEHICLES; i ++)
	{
		if(veh_info[i -1][v_deleted] == 1) continue;
		if(!IsValidVehicle(i)) continue;
		if(veh_id != veh_info[i -1][v_vehicle]) continue;
		DestroyVehicle(veh_info[i -1][v_vehicle]);
		veh_info[i -1][v_deleted] = 1;

		format(sql_string, sizeof sql_string, "UPDATE `server_vehicles` SET `DELETED`=1 WHERE `sv_id`='%d' LIMIT 1", 
			veh_info[i -1][v_id]);
		mysql_tquery(sql_connection, sql_string);

		SendClientMessage(playerid, col_white, "Transport deleted successfully.");
		return 1;
	}
	SendClientMessage(playerid, col_white, "Transport not found.");
	return 1;
}

cmd:deletehouse(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;

	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /deletehouse [house id]");

	if(getHouseID(params[0]) == -1) return SendError(playerid, "ID khane nadorost ast.");

	new s_house_id = getHouseID(params[0]),
		query[300],
		h_owner_id = GetPlayerID(h_info[s_house_id][h_owner_name]);

	if(IsPlayerConnected(h_owner_id))
	{
		PlayerInfo[h_owner_id][house] = -1;
		update_int_sql(h_owner_id, "u_house", getPlayerHouseID(h_owner_id));

		PlayerInfo[h_owner_id][spawnchange] = 0;
		update_int_sql(h_owner_id, "u_spawnchange", PlayerInfo[h_owner_id][spawnchange]);

		SendClientMessage(h_owner_id, col_light_red, !"Admin deleted your house");
	}
	else
	{
		format(query,sizeof(query),"UPDATE `users` SET `u_house` = '-1', `u_spawnchange` = '-1' WHERE `u_id` = '%d' LIMIT 1", h_info[s_house_id][h_owner]);
		mysql_tquery(sql_connection, query, "", "");
	}

	strfmt(h_info[s_house_id][h_owner_name], "state property");
	
	new house_family = h_info[s_house_id][h_family];

	if(house_family != -1)
	{
		family_info[house_family][fam_house] = -1;
		format(query, sizeof(query), "UPDATE `family` SET `fam_house`='-1' WHERE `fam_id`='%d' LIMIT 1", getPlayerFamilyID(playerid));
		mysql_query(sql_connection, query);	
	}

	h_info[s_house_id][h_pos][0] = -1;
	h_info[s_house_id][h_pos][1] = -1;
	h_info[s_house_id][h_pos][2] = -1;
	h_info[s_house_id][h_pos][3] = -1;

	h_info[s_house_id][h_v_pos][0] = -1;
	h_info[s_house_id][h_v_pos][1] = -1;
	h_info[s_house_id][h_v_pos][2] = -1;
	h_info[s_house_id][h_v_pos][3] = -1;

	h_info[s_house_id][h_family] = -1;
	h_info[s_house_id][h_owner] = -1;
	h_info[s_house_id][h_closed] = 0;
	DestroyDynamicMapIcon(h_info[s_house_id][h_icon_id]);
	DestroyDynamic3DTextLabel(h_info[s_house_id][h_enter_label]);
	DestroyDynamic3DTextLabel(h_info[s_house_id][h_exit_label]);
	DestroyDynamic3DTextLabel(h_info[s_house_id][h_garage_label]);


 	format(query, sizeof query, "DELETE FROM `houses` WHERE `h_id` = '%d' LIMIT 1", h_info[s_house_id][h_id]);
	mysql_tquery(sql_connection, query);

	h_info[s_house_id][h_id] = -1;

	SendClientMessage(playerid, col_white, "House successfully deleted.");
	
	return 1;
}

cmd:election(playerid)
{
	if(check_admin_rank(playerid , 6)) return 1;
	show_dialog(playerid, d_election, DIALOG_STYLE_LIST, ""c_server"Election Management | Status", "Elections are closed\nCandidate registration\nVoting\nCandida deletion item\ndelete candidate", "Accept", "Bastan");
	return 1;
}

cmd:startrace(playerid)
{
	if(check_admin_rank(playerid , 6)) return 1;

	TimerRace = 180;
	StartRace = 1;
	RaceCountWinner =
	PlayerRaceCount = 0;
	RaceVehicle = Race_Car[random(18)];
	if(++RaceMap > 9) RaceMap = 1;
	foreach(new i: logged_players)
	{
		if(is_player_race_regged[i])
		{
			DestroyVehicle(player_race_vehicle[i]);
			player_race_vehicle[i] =
			is_player_race_regged[i] =
			player_race_cp[i] = 0;
			DisableRemoteVehicleCollisions(i, 0);
			set_pos(i, 1298.1658, -1360.8027, 35.8113, 21.7293, 0, 5);
		}
	}

	SendClientMessageToAll(col_gray, ""c_server"[Derby]"c_white"Mosabeghe "c_yellow"\"Derby\""c_white" ta 3 daghighe digar bargozar mishe. Baraye raftan be race "c_server"/go"c_white" ra type konid.");

	return 1;
}

cmd:updorms(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;

	dorm_count[DORM_SAWMILL] = dorm_count[DORM_MINE] = dorm_count[DORM_FACTORY_GUNS] = dorm_count[DORM_FACTORY_MINE] = dorm_count[DORM_FACTORY_WOOD] = 1000000;
	return 1;
}

cmd:setwarehouse(playerid, params[])
{
	if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /setwarehouse [organization] [number of]");
	if(params[0] < 0 || params[0] > fraction_count) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid Organization ID.");
	if(params[1] < 0 || params[1] > 300000) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid Organization ID.");

	f_info[params[0]][f_materials] = params[1];
	f_info[params[0]][f_guns] = params[1];


	new query_string[136];
	format(query_string, 136, "UPDATE `fractions` SET `f_materials` = '%d',`f_guns` = '%d' WHERE `f_id` = '%d' LIMIT 1",
	f_info[params[0]][f_materials], f_info[params[0]][f_guns], f_info[params[0]][f_id]);
	mysql_tquery(sql_connection, query_string, "", "");

	AdminMes(""c_server"* A.INFO:"c_grey" %s[%i] replenished the warehouse with weapons %s", PlayerInfo[playerid][name], playerid, f_info[params[0]][f_name]);

	if(params[0] >= 18 && params[0]<= 25) UpdateGangDormLabel(params[0]);
	return 1;
}

cmd:setmoneyhouse(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /setmoneyhouse [organization] [number of]");
	if(params[0] < 0 || params[0] > fraction_count) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid Organization ID.");
	if(params[1] < 0 || params[1] > 5000000) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Invalid Organization ID.");

	f_info[params[0]][f_money] = params[1];


	new query_string[136];
	format(query_string, 136, "UPDATE `fractions` SET `f_money` = '%d' WHERE `f_id` = '%d' LIMIT 1",
	f_info[params[0]][f_money], f_info[params[0]][f_id]);
	mysql_tquery(sql_connection, query_string, "", "");

	AdminMes(""c_server"* A.INFO:"c_grey" %s[%i] replenished the organization %s", PlayerInfo[playerid][name], playerid, f_info[params[0]][f_name]);

	if(params[0] >= 18 && params[0]<= 22) UpdateGangDormLabel(params[0]);
	return 1;
}

cmd:abonus(playerid, params[])
{
	if(check_admin_rank(playerid , 7)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /abonus [meghdar]");
	server_bonus = params[0];
	
	if(server_bonus > 1)
	{
		SendRcon("hostname (MRP) Mihan - RolePlay [Android/PC] | Bonus x%d", server_bonus);
		SendInfo(playerid, "Bonus server gharar gerft roy: "c_yellow"x%d", params[0]);
	}
	else 
	{
		SendRconCommand("hostname (MRP) Mihan - RolePlay [Android/PC]");
		SendInfo(playerid, "Bonus server gheyre fa'al shod.");
	}

	RunQuery("UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '9' LIMIT 1", server_bonus);

	return 1;
}

cmd:servername(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "s[128]", params[0])) return SendInfo(playerid, "Enter: /servername [name]");

	SendRcon("hostname %s", params[0]);

	SendInfo(playerid, "Esm server taghir kard be: "c_yellow"%s", params[0]);

	return 1;
}

cmd:sopen(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "d", params[0])) return SendError(playerid, "Enter /sopen [0 - close | 1 - open]");
	if(params[0] < 0 || params[0] > 1) return SendError(playerid, "Enter /sopen [0 - close | 1 - open]");
	
	switch(params[0])
	{
	    case 1:
	    {
			SendRconCommand("password 0");
			SendInfo(playerid, "Server Baz Shod.");
		}
		case 0:
		{
			SendRconCommand("password q123q321");
			SendInfo(playerid, "Server Baste Shod.");
		}
	}

	RunQuery("UPDATE `server_variables` SET `var_count` = '%d' WHERE `var_id` = '10' LIMIT 1", params[0]);

	return 1;
}

cmd:ccport(playerid)
{
	if(check_admin_rank(playerid , 6)) return 1;

	new Float:_distance = 3000.0,
				container_cell;

	for(new i = 0; i < MAX_CONTAINERS; i ++)
	{
		new Float:__distance = GetPlayerDistanceFromPoint(playerid, porter_pos_take[i][0], porter_pos_take[i][1], porter_pos_take[i][2]);
		if(_distance > __distance)_distance = __distance, container_cell = i;
	}
	if(_distance < 7)
	{
		for(new j = 0; j < 2; j ++)
		{
			if(container_info[container_cell][con_status][j] != 0)
			{
				if(container_info[container_cell][con_status][1] == 1)
				{
					DestroyDynamicObject(container_info[container_cell][con_object][1]);
					container_info[container_cell][con_object][1] = 0;
					container_info[container_cell][con_status][1] = 0;
					closed_containers --;
				}
				if(container_info[container_cell][con_object][0] != 0)DestroyDynamicObject(container_info[container_cell][con_object][0]);
				container_info[container_cell][con_status][0] = 0;
				closed_containers --;

				SendClientMessage(playerid, -1, "Port slot cleared.");
				break;
			}
		}
	}
	return 1;
}

cmd:mp(playerid)
{
	if(check_admin_rank(playerid , 3)) return 1;
	show_dialog(playerid, d_mp, DIALOG_STYLE_LIST, !""scm_dialog"Event menu", !"Dispense Weapon (In 100m radius)\nLife Sharing (In 100m radius)\nDefuse everything (within 100m radius)\nDistribute Armor (In 100m radius)", !"Entekhab", !"Cancel");
	return 1;
}

cmd:startmp(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
    new
           Float:mp_pos_x,
           Float:mp_pos_y,
           Float:mp_pos_z;

	new quantity_player, name_mp[32];
	if(sscanf(params, "ds[32]", quantity_player, name_mp)) return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /startmp [Number of players] [Event name]");

    if(GetSVarInt("AidPlayers"))
       return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Gathering of players at the event.");
    if(quantity_player > 100)
       return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Max number of players per event: 100.");
    if(!(1 <= strlen(params) <= 32))
       return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Event name too long.");
    SetSVarInt("AidPlayers",quantity_player);
    GetPlayerPos(playerid, mp_pos_x, mp_pos_y, mp_pos_z);
    SetSVarFloat("mp_pos_x",mp_pos_x);
    SetSVarFloat("mp_pos_y",mp_pos_y);
    SetSVarFloat("mp_pos_z",mp_pos_z);
	SetSVarInt("mp_int",GetPlayerInterior(playerid));
	SetSVarInt("mp_virt",GetPlayerVirtualWorld(playerid));

    new string[200];
    format(string,sizeof(string), ""c_server"[Event]"c_white" Admin %s Yek Event '%s' Bargozar Kard. Had Aksar Player Baraye in event: %d Nafar", PlayerInfo[playerid][name], name_mp,quantity_player);
    SendClientMessageToAll(col_gray,string);

    return SendClientMessageToAll(col_gray, ""c_server"[Event]"c_white" Baraye vared shodan be event dastor /gomp ra vared konid.");
}

cmd:stopmp(playerid)
{
	if(check_admin_rank(playerid , 3)) return 1;
    if(!GetSVarInt("AidPlayers")) return SendError(playerid, "Gathering of players is not started");
    
    DeleteSVar("AidPlayers");
    DeleteSVar("mp_pos_x"); DeleteSVar("mp_pos_y"); DeleteSVar("mp_pos_z");
	DeleteSVar("mp_int");  DeleteSVar("mp_virt");
	
    return SendClientMessageToAll(col_white, ""c_server"[Event]"c_white" Event Tavasot Admin Ghofl Shod");
}

cmd:dmgstat(playerid, params[])
{
	if(check_admin_rank(playerid , 1)) return 1;
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Enter: /dmgstat [id]");
	if(!IsPlayerConnected(params[0])) return SendError(playerid, "Bazikon Yaft Nashod.");

	global_string[0] = EOS;
	format(global_string, 140, ""c_white"God mode: %s\ntick differ: %d\nkilled: %d",
		!p_t_info[params[0]][player_gm] ? (""c_orange_red"Disabled") : (""c_green"Enabled"),
		GetTickCount() -p_t_info[params[0]][p_update], 
		p_t_info[params[0]][player_killed]);
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Damage statistics", global_string, "Bastan", "");

	return 1;
}


cmd:newveh(playerid, params[])
{
    if(check_admin_rank(playerid , 5)) return 1;
	if(GetPlayerState(playerid) ==  PLAYER_STATE_DRIVER) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You are already driving.");
	if(sscanf(params, "ddd", params[0 ], params[1 ], params[2])) return SendInfo(playerid, "Enter: /newveh [[Auto ID] [Color 1] [Color 2]");
	if(params[0] < 400 || params[0] > 611) return SendInfo(playerid, "Enter: /newveh [Auto ID] [Color 1] [Color 2]");
	if(params[1] < 0 || params[1] > 255) return SendInfo(playerid, "Enter: /newveh [Auto ID] [Color 1] [Color 2]");
	if(params[2] < 0 || params[2] > 255) return SendInfo(playerid, "Enter: /newveh [Auto ID] [Color 1] [Color 2]");
	new Float:player_pos[3];
	GetPlayerPos(playerid, player_pos[0], player_pos[1], player_pos[2]);
	new adm_veh = CreateVehicle(params[0], player_pos[0], player_pos[1], player_pos[2], 0.0, params[1], params[2], -1);

	veh_info[adm_veh -1][v_pos][0] = player_pos[0];
	veh_info[adm_veh -1][v_pos][1] = player_pos[1];
	veh_info[adm_veh -1][v_pos][2] = player_pos[2];


	SetPVarInt(playerid, "admin_vehicle", adm_veh);
	veh_info[adm_veh -1][v_fuel] = 60.0;
	PutPlayerInVehicle(playerid, adm_veh, 0);
	SetPlayerArmedWeapon(playerid,0);

	AdminMes(""c_server"* A.INFO: "c_grey"%s created the car. ID: %d | Model: %d", PlayerInfo[playerid][name], adm_veh, params[0]);

	return 1;
}

cmd:destroyveh(playerid, params[])
{
    if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /destroyveh [auto ID]");

	AdminMes(""c_server"* A.INFO: "c_grey"%s deleted car. ID: %d | Hard destroy", PlayerInfo[playerid][name], params[0]);

	DestroyVehicle(params[0]);
	return 1;
}

cmd:boton(playerid,params[])
{

    if(check_admin_rank(playerid , 6)) return 1;
    new ips[20];
	if(sscanf(params,"s[20]",ips)) return SendClientMessage(playerid, -1, "Enter: /boton [ip]");
	if(strlen(ips) < 1 || strlen(ips) > 20) return SendClientMessage(playerid, -1, "You entered the wrong number of characters");

	new bot_iter = -1;
	for(new j = 0; j < 5; j ++ )
	{
		if(strlen(ip_white_list[j]) > 3) continue;
		bot_iter = j;
	}
	if(bot_iter == -1) return SendClientMessage(playerid, -1, "There are no empty spaces on the white list of IP addresses.");

	format(ip_white_list[bot_iter], 16, "%s", ips);
	SendClientMessage(playerid, -1, ip_white_list[bot_iter]);
	SendClientMessage(playerid, -1, "IP added to whitelist.");
	return 1;
}

cmd:botoff(playerid,params[])
{

    if(check_admin_rank(playerid , 6)) return 1;
    new ips[20];
	if(sscanf(params,"s[20]",ips)) return SendClientMessage(playerid, -1, "Enter: /botoff [ip]");
	if(strlen(ips) < 1 || strlen(ips) > 20) return SendClientMessage(playerid, -1, "");

	new bot_iter = -1;
	for(new j = 0; j < 5; j ++ )
	{
		if(!GetString(ips, ip_white_list[j])) continue;
		bot_iter = j;
	}
	if(bot_iter == -1) return SendClientMessage(playerid, -1, "This IP is not found in the whitelist.");

	format(ip_white_list[bot_iter], 16, "1");
	SendClientMessage(playerid, -1, "IP removed from white sheet.");
	return 1;
}

cmd:botlist(playerid)
{
    if(check_admin_rank(playerid , 6)) return 1;
	new bot_iter = -1;
	for(new j = 0; j < 5; j ++ )
	{
		if(strlen(ip_white_list[j]) < 3) continue;
		SendClientMessage(playerid, -1, ip_white_list[j]);
		bot_iter = j;
	}
	if(bot_iter == -1) return SendClientMessage(playerid, -1, "No 1 IP found in whitelist.");

	return 1;
}

stock is_ip_white_list(server_ip[])
{
	new bot_iter = -1;
	for(new j = 0; j < 5; j ++ )
	{
		if(!GetString(server_ip, ip_white_list[j])) continue;
		bot_iter = j;
	}
	if(bot_iter != -1) return 1;
	return 0;
}

stock GetIPIndex(ipAddress[])
{
    for (new i = 0; i < MAX_IPS; i++)
    {
        if (strcmp(ipAddresses[i], ipAddress, false) == 0)
            return i;
    }
    return -1;
}

cmd:offwarn(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	new target_name[24], warn_reason[32];
	if(sscanf(params, "s[24]s[32]", target_name, warn_reason)) return SendClientMessage(playerid, col_gray,"Enter: /offwarn [name] [reason]");

	new scm_string[128];
	format(scm_string, sizeof(scm_string ), "SELECT `u_id` FROM `users` WHERE `u_name` = '%s' LIMIT 1", target_name);
	mysql_function_query(sql_connection, scm_string, true, "offwarn_check_callback", "iss", playerid, target_name, warn_reason);
	return 1;
}

callback: offwarn_check_callback(playerid, pl_name[], reason_[])
{
	new rows, fields;
	cache_get_data(rows, fields);
	if(!rows)
	{
		new scm_string[128];
		format(scm_string, sizeof(scm_string), "Account %s not found in database.", pl_name);
		SendClientMessage(playerid, col_gray, scm_string);
		return 1;
	}
	else
	{
		new account_id = cache_get_field_content_int(0, "u_id", sql_connection);
		new scm_string[128];
		format(scm_string, sizeof(scm_string ), "SELECT * FROM `users_warns` WHERE `w_owner` = '%d' LIMIT 1", account_id);
		mysql_function_query(sql_connection, scm_string, true, "offwarn_second_callback", "isis", playerid, pl_name, account_id, reason_);
		return 1;
	}
}

callback: offwarn_second_callback(playerid, pl_name[], account_id, reason_[])
{
	new _warn_count = 0,
	query_string[78];
	format(query_string, sizeof(query_string),"SELECT * FROM users_warns WHERE w_owner = '%d'", account_id);
	new Cache:result = mysql_query(sql_connection, query_string);
	_warn_count = cache_num_rows();
	if(_warn_count != 2)
	{
		new scm_string[238];
		foreach(new i: admin_players) if(PlayerInfo[i][settings][2]) SendMes(i, col_light_red, "Admin %s issued a warning to the offline player %s. Reason: %s", PlayerInfo[playerid][name], pl_name, reason_);

		format(scm_string, sizeof(scm_string ), "INSERT INTO `users_warns` (`w_admin_name`,`w_owner`,`w_reason`,`w_date`,`w_end`) VALUES('%s', '%d', '%s', NOW(), NOW() + INTERVAL 5 DAY)", PlayerInfo[playerid][name], account_id, reason_);
		mysql_tquery(sql_connection, scm_string);

		addOffWorkBook(pl_name, PlayerInfo[playerid][name], reason_);

		return 1;
	}
	if(_warn_count == 2)
	{
		new scm_string[238];
		format(scm_string, 144, "Admin %s blocked offline player %s [3 warnings]. Reason: %s", PlayerInfo[playerid][name], pl_name, reason_);
		foreach(new i: logged_players) if(PlayerInfo[i][settings][2]) SendClientMessage(i, col_light_red, scm_string);

		format(scm_string, sizeof(scm_string ), "INSERT INTO `users_bans` (`u_b_admin`,`u_b_name`,`u_b_reason`,`u_b_date`,`u_b_ndate`,`u_b_days`) VALUES('%s', '%s', '%s', NOW() + INTERVAL 3 DAY, NOW(), '3')", PlayerInfo[playerid][name], pl_name, reason_);
		mysql_query(sql_connection, scm_string);


		format(scm_string, sizeof scm_string, "UPDATE `users_warns` SET `w_end`=NOW() WHERE `w_owner`='%d'", account_id);
		mysql_tquery(sql_connection, scm_string);

		return 1;
	}
	cache_delete(result);
	return _warn_count;
}

cmd:offunwarn(playerid, params[])
{
	if(check_admin_rank(playerid , 5)) return 1;
	if(sscanf(params, "s[24]", params[0])) return SendClientMessage(playerid, col_gray,"Enter: /unwarnoff [name]");

	new scm_string[128];
	format(scm_string, sizeof(scm_string ), "SELECT `u_id` FROM `users` WHERE `u_name` = '%s' LIMIT 1", params[0]);
	mysql_function_query(sql_connection, scm_string, true, "unwarnoff_check_callback", "is", playerid, params[0]);
	return 1;
}

callback: unwarnoff_check_callback(playerid, pl_name[])
{
	new account_id = cache_get_field_content_int(0, "u_id", sql_connection);
	new scm_string[128];
	format(scm_string, sizeof(scm_string ), "SELECT * FROM `users_warns` WHERE `w_owner` = '%d' LIMIT 1", account_id);
	mysql_function_query(sql_connection, scm_string, true, "unwarnoff_second_callback", "isi", playerid, pl_name, account_id);
	return 1;
}

callback: unwarnoff_second_callback(playerid, pl_name[], account_id)
{
	new scm_string[128];
	format(scm_string, sizeof(scm_string ), "DELETE FROM `users_warns` WHERE `w_owner`='%d'", account_id);
	mysql_query(sql_connection, scm_string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s removed all warn from %s.", PlayerInfo[playerid][name], pl_name);

	return 1;
}

cmd:giveveh(playerid, params[]) {
    if(check_admin_rank(playerid , 8)) return 1;
    new targetid,give_car_model;
    if(sscanf(params,"ud",targetid,give_car_model)) return	SendInfo(playerid, "Enter: /giveveh [id/name] [model]");
	if(!(400 < give_car_model < 611)) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"model between 400 to 611.");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Offline player!");

	new string[128];

	if(get_player_veh_count(targetid) >= PlayerInfo[targetid][max_veh]) {
		format(string, 64, ""scm_error"Player vehicles is max. %d/%d", get_player_veh_count(targetid), PlayerInfo[targetid][max_veh]);
		return SendClientMessage(playerid, col_white, string);
	}

	new ts_id, ts_spawn_slot = random(5);

	new	veh_id = CreateVehicle(give_car_model, t_shop_respawn[ts_id][ts_spawn_slot][0],
										t_shop_respawn[ts_id][ts_spawn_slot][1],
										t_shop_respawn[ts_id][ts_spawn_slot][2],
										t_shop_respawn[ts_id][ts_spawn_slot][3],
										1, 1, -1);


	veh_info[veh_id -1][v_model] = GetVehicleModel(veh_id);

	new query_string[226];
	mysql_format(sql_connection, query_string, sizeof query_string, "INSERT INTO `users_vehicles`(`v_model`,`v_owner`,`v_color_1`,`v_color_2`,`v_pos_x`,`v_pos_y`,`v_pos_z`,`v_pos_a`,`v_buydate`) VALUES ('%d','%i','1','1','%f','%f','%f','%f',NOW())",
	give_car_model,
	PlayerInfo[targetid][id],
	t_shop_respawn[ts_id][ts_spawn_slot][0],
	t_shop_respawn[ts_id][ts_spawn_slot][1],
	t_shop_respawn[ts_id][ts_spawn_slot][2],
	t_shop_respawn[ts_id][ts_spawn_slot][3]);


	mysql_tquery(sql_connection, query_string, "create_vehicle_callback", "dd", veh_id, targetid);

	veh_info[veh_id -1][v_type] = vehicle_type_player;
	veh_info[veh_id -1][v_vehicle] = veh_id;
	format(veh_info[veh_id -1][v_plate], 12, "Transit");
	veh_info[veh_id -1][v_pos][0] = t_shop_respawn[ts_id][ts_spawn_slot][0];
	veh_info[veh_id -1][v_pos][1] = t_shop_respawn[ts_id][ts_spawn_slot][1];
	veh_info[veh_id -1][v_pos][2] = t_shop_respawn[ts_id][ts_spawn_slot][2];
	veh_info[veh_id -1][v_pos][3] = t_shop_respawn[ts_id][ts_spawn_slot][3];
	veh_info[veh_id -1][v_fuel] = 100.0;
	veh_info[veh_id -1][v_millage] = 0.0;
	veh_info[veh_id -1][v_fine] = 3;
	veh_info[veh_id -1][v_special_car] = 0;


	new engine, lights, alarm, doors, bonnet, boot, objective;
	veh_info[veh_id -1][v_locked] = true;
	GetVehicleParamsEx(veh_id, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(veh_id, engine, lights, alarm, true, bonnet, boot, objective);


	veh_info[veh_id -1][v_owner] = PlayerInfo[targetid][id];

	veh_info[veh_id -1][v_label_plate] = CreateDynamic3DTextLabel(veh_info[veh_id -1][v_plate], col_gray, 0.0, 0.0, 0.0, 13.0, INVALID_PLAYER_ID, veh_info[veh_id -1][v_vehicle], 0);

	SetVehicleNumberPlate(veh_info[veh_id -1][v_vehicle], veh_info[veh_id -1][v_plate]);
	Iter_Add(player_vehicles[targetid], veh_info[veh_id -1][v_vehicle]);

	format(string, sizeof(string), ""c_server"* S.INFO:"c_grey" %s be shoma mashin %s dad.", PlayerInfo[playerid][name], vehicle_name[give_car_model-400]);
	SendClientMessage(targetid, col_gray, string);

	AdminMes(""c_server"* A.INFO: "c_grey"%s gived %s %s car.", PlayerInfo[playerid][name], PlayerInfo[targetid][name], vehicle_name[give_car_model-400]);

	return 1;
}

alias:jetpack("ju");
cmd:jetpack(playerid, params[]) 
{
	if(check_admin_rank(playerid , 1)) return 1;

	new targetid;
	if(sscanf(params, "u", targetid)) return SendInfo(playerid, "Enter: /jt [id]");
	if(!IsPlayerConnected(targetid)) return SendError(playerid, "Bazikon Yaft Nashod.");

	if(IsPlayerInFalloutGame(targetid)) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"In Bazikon Dar Event Fallout Hast!");
	if(ReturnPlayerInCounterStrike(targetid) != 0) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"In Bazikon Dar Event Counter Strike Hast!");


	if(GetPlayerSpecialAction(targetid) == SPECIAL_ACTION_USEJETPACK)
	{
	    SendClientMessage(playerid, COLOR_GREY, "In Bazikon Jetpack Darad. Baraye Az Bin Bordan Bayad {FFFFFF}/jtoff {999999}Bezand.");
		return 1;
	}

	GameTextForPlayer(targetid, "~y~~h~JETPACK", 3, 2500);
	SetPlayerSpecialAction(targetid, SPECIAL_ACTION_USEJETPACK);

	AdminMes(""c_server"* A.INFO: "c_grey"%s[%d] gived jetpack to %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid);

	return 1;
}

cmd:jtoff(playerid) 
{
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK)
	{
	    SendClientMessage(playerid, COLOR_GREY, "Shoma Jetpack Nadarid.");
		return 1;
	}

	ApplyAnimation(playerid, "DEALER", "SHOP_PAY", 4.1, 0, 0, 0, 0, 30, 1);
	return 1;
}

cmd:givetunnedcar(playerid, params[]) {
	if(check_admin_rank(playerid , 8)) return 1;
	extract params -> new player:targetid; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /givetunnedcar [Player id]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_gray, ""scm_error"Player not found.");
    if(!p_t_info[targetid][p_logged]) return SendClientMessage(playerid, col_gray, ""scm_error"Player is not logged in.");

    SetPVarInt(playerid, "givetunnedcarTarget", targetid);

    show_dialog(playerid, d_give_tunned_car, DIALOG_STYLE_LIST, ""scm_dialog"Tunned Cars",

    	""c_server"1 | "c_white"ELEGY\n\
    	"c_server"2 | "c_white"Infernus\n\
    	"c_server"3 | "c_white"Bullet v1\n\
    	"c_server"4 | "c_white"Turismo\n\
    	"c_server"5 | "c_white"Perebbiel\n\
		"c_server"6 | "c_white"Bullet v2\n\
    	"c_server"7 | "c_white"Infernus V2\n\
    	"c_server"8 | "c_white"ZR 350\n\
    	"c_server"9 | "c_white"Sand King (No Gaurd)\n\
    	"c_server"10 | "c_white"Sabre\n\
    	"c_server"11 | "c_white"Jester\n\
    	"c_server"12 | "c_white"BLOODRING BANGER\n\
    	"c_server"13 | "c_white"Ghost Busters\n\
    	"c_server"14 | "c_white"Monster VIP\n\
    	"c_server"15 | "c_white"Sand King VIP\n\
    	"c_server"16 | "c_white"Sultan VIP (Police Edition)\n\
    	"c_server"17 | "c_white"Bullet VIP (Police Edition)\n\
    	"c_server"18 | "c_white"Cheetah VIP\n\
    	"c_server"19 | "c_white"Sand King VIP v2\n\
    	"c_server"20 | "c_white"Infernus VIP - v3\n\
    	"c_server"21 | "c_white"FBI Truck VIP\n\
    	"c_server"22 | "c_white"Patriot VIP\n\
    	"c_server"23 | "c_white"Feltzer VIP (Halloween)\n\
    	"c_server"24 | "c_white"Taxi Halloween\n\
    	"c_server"25 | "c_white"Roadtrain VIP v2\n\
    	"c_server"26 | "c_white"Dune VIP\n\
    	"c_server"27 | "c_white"Patroit VIP v2\n\
    	"c_server"28 | "c_white"Infernus VIP - v4\n\
    	"c_server"29 | "c_white"Infernus VIP - v5\n\
    	"c_server"30 | "c_white"Stallion VIP\n\
    	"c_server"31 | "c_white"Romero VIP\n\
    	"c_server"32 | "c_white"FBI Rancher VIP\n\
    	"c_server"33 | "c_white"BF Injection HalloWeen\n\
    	"c_server"34 | "c_white"Buffalo VIP\n\
    	"c_server"35 | "c_white"Clover VIP\n\
    	"c_server"36 | "c_white"Journey VIP",

    	"Give",
    	"Cancel");
	return 1;
}

cmd:changeaccpassword(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;

	new
		mname[MAX_PLAYER_NAME],
		newPassword[32];

	if(sscanf(params, "s[24]s[32]", mname, newPassword)) return SendInfo(playerid, "Enter: /ChangeAccPassword [ID Player] [New Password]");

	new player = GetPlayerID(mname);
	if(IsPlayerConnected(player)) return SendError(playerid, "In Bazikon Online Ast.");

	if(strlen(newPassword)< 6 || strlen(newPassword)> 24)
	{
		SendError(playerid, "At least 6 to 15 characters.");
		return 1;
	}

	if(is_text_invalid(newPassword))
	{
		SendError(playerid, "Invalid characters in the password.");
		return 1;
	}

	new sql_string[100];
	format(sql_string, sizeof sql_string, "SELECT `u_id`,`u_name` FROM `users` WHERE `u_name`='%s' LIMIT 1", mname);
	mysql_tquery(sql_connection, sql_string, "changeaccpassword_callback", "ds", playerid, newPassword);
	return 1;
}

forward changeaccpassword_callback(playerid, newPassword[]);
public changeaccpassword_callback(playerid, newPassword[])
{
	if(!cache_num_rows()) return SendError(playerid, "In Name Dar Database Vojod Nadarad.");

	new otarget[20];

    new _account_id = cache_get_field_content_int(0, "u_id", sql_connection);
	cache_get_field_content(0, "u_name", otarget, sql_connection, sizeof(otarget));

	new sql_string[108];
	mysql_format(sql_connection, sql_string, 108, "UPDATE `users` SET `u_password` = MD5('%e') WHERE `u_id`='%d' LIMIT 1",
	newPassword, _account_id);
	mysql_tquery(sql_connection, sql_string, "", "");

	format(sql_string, 90, "Ramz Jadid Bazikon %s: "c_green"%s", otarget, newPassword);
	SendClientMessage(playerid, col_white, sql_string);
	return 1;
}

cmd:fnear(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;

	new rangeFreeze;
	if(sscanf(params, "d", rangeFreeze)) return SendInfo(playerid, "Enter: /fnear [range 5 - 1000]");
	if(!(5 <= rangeFreeze <= 1000)) return SendInfo(playerid, "Enter: /fnear [range 5 - 1000]");

	new string[128];
	new count;
	new Float:x, Float:y, Float:z;
	new Float:temp_x, Float:temp_y, Float:temp_z;

	GetPlayerPos(playerid, x, y, z);

	format(string, sizeof(string), ""scm_info"Admin %s shoma ra freeze kard.", Name(playerid));

	foreach(new i: logged_players)
	{
		if(i == playerid) continue;
		
		GetPlayerPos(i, temp_x, temp_y, temp_z);
		if(GetDistance(x, y, temp_x, temp_y) > float(rangeFreeze)) continue;

		toggle_controlable(i, false);
		SendClientMessage(i, col_white, string);

		count++;
	}

	format(string, sizeof(string), ""scm_info"Tedad %d player freeze shod.", count);
	SendClientMessage(playerid, col_white, string);
	return 1;
}

cmd:unfnear(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;

	new rangeFreeze;
	if(sscanf(params, "d", rangeFreeze)) return SendInfo(playerid, "Enter: /unfnear [range 5 - 1000]");
	if(!(5 <= rangeFreeze <= 1000)) return SendInfo(playerid, "Enter: /unfnear [range 5 - 1000]");

	new string[128];
	new count;
	new Float:x, Float:y, Float:z;
	new Float:temp_x, Float:temp_y, Float:temp_z;

	GetPlayerPos(playerid, x, y, z);

	format(string, sizeof(string), ""scm_info"Admin %s shoma ra unfreeze kard.", Name(playerid));

	foreach(new i: logged_players)
	{
		if(i == playerid) continue;
		
		GetPlayerPos(i, temp_x, temp_y, temp_z);
		if(GetDistance(x, y, temp_x, temp_y) > float(rangeFreeze)) continue;

		toggle_controlable(i, true);
		SendClientMessage(i, col_white, string);

		count++;
	}

	format(string, sizeof(string), ""scm_info"Tedad %d player unfreeze shod.", count);
	SendClientMessage(playerid, col_white, string);
	return 1;
}

cmd:ghorekeshi(playerid, params[])
{
	if(check_admin_rank(playerid , 5)) return 1;

	if(GhorekeshiTime > 0) return 1;

	new prizeName[64];
	if(sscanf(params, "s[64]", prizeName)) return SendInfo(playerid, "Enter: /ghorekeshi [Name Jayeze]");

	strcat(GhorekeshiPrizeName, prizeName);
	GhorekeshiTime = 6;

	SendClientMessageToAll(col_gray, "{FF0000}[GHOREKESHI]: {FFFF00}Ghorekeshi dar hal anjam ast :D");

	return 1;
}

cmd:back(playerid,params[])
{
    if(g_DelayForSetPos[playerid] != 0)
        return 1;

    if(g_BeforeDelayPositons[playerid][0] == 0.0)
        return 1;

    SetPlayerPos(playerid, g_BeforeDelayPositons[playerid][0], g_BeforeDelayPositons[playerid][1], g_BeforeDelayPositons[playerid][2]);
    SetPlayerFacingAngle(playerid, g_BeforeDelayPositons[playerid][3]);

    SetPlayerVirtualWorld(playerid, g_BeforeDelayIntAndWorld[playerid][0]);
    SetPlayerInterior(playerid, g_BeforeDelayIntAndWorld[playerid][1]);

    p_t_info[playerid][house] = g_BeforeDelayInUniques[playerid][0];
	p_t_info[playerid][business] = g_BeforeDelayInUniques[playerid][1];

    g_BeforeDelayPositons[playerid][0] = 0.0;

    return 1;
}

cmd:staffroom(playerid,params[])
{
	if(check_admin_rank(playerid , 1)) return 1;
   
    if(g_DelayForSetPos[playerid] != 0) return 1;

    GetPlayerPos(playerid, g_BeforeDelayPositons[playerid][0], g_BeforeDelayPositons[playerid][1], g_BeforeDelayPositons[playerid][2]);
    GetPlayerFacingAngle(playerid, g_BeforeDelayPositons[playerid][3]);
    g_BeforeDelayIntAndWorld[playerid][0] = GetPlayerVirtualWorld(playerid);
    g_BeforeDelayIntAndWorld[playerid][1] = GetPlayerInterior(playerid);
    g_BeforeDelayInUniques[playerid][0] = p_t_info[playerid][house];
    g_BeforeDelayInUniques[playerid][1] = p_t_info[playerid][business];

   	p_t_info[playerid][house] = -1;
	p_t_info[playerid][business] = -1;

    g_DelayForSetPos[playerid] = 2;
    g_DelayPositons[playerid][0] = 1298.8677;
    g_DelayPositons[playerid][1] = -794.6638;
    g_DelayPositons[playerid][2] = 1084.0078;
    g_DelayPositons[playerid][3] = 359.1086;
    g_DelayIntAndWorld[playerid][0] = 5;
    g_DelayIntAndWorld[playerid][1] = 0;

    return 1;
}