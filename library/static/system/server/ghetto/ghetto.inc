cmd:freezepanel(playerid)
{
	if(check_admin_rank(playerid , 4)) return 1;
	global_string[0] = EOS;

	for(new j = 0; j < 5; j ++)
	{
		new line_string[98];
		if(capture_gang_freezed[j] == 0)format(line_string, sizeof(line_string), ""c_white"%s\t"c_green"defrosted\n", f_info[j + 17][f_name]);
		else format(line_string, sizeof(line_string), ""c_white"%s\t"c_orange_red"Frozen\n", f_info[j + 17][f_name]);
		strcat(global_string, line_string);
	}
	show_dialog(playerid, d_capture_freeze, DIALOG_STYLE_TABLIST, ""c_server"Freeze Status", global_string, "Change", "Bastan");
	return 1;
}

cmd:capture(playerid)
{
	if(!gang_player(playerid)) 
		return SendError(playerid, "Shoma nmitavanid az in dastor estefade konid.");
    if(PlayerInfo[playerid][rank] < 9)
		return SendError(playerid, "Shoma nmitavanid az in dastor estefade konid.");

    new faction_playerid = PlayerInfo[playerid][member];

    if(timestamp_hour < 14 || timestamp_hour > 23)
        return SendError(playerid, "Taskhir ghalamro faghat az 14:00 ta 23:00 mojaz ast.");
	if(timestamp_minute < 0 || timestamp_minute > 10)
        return SendError(playerid, "Taskhir ghalamro faghat az **:00 ta **:10 mojaz ast.");

    if(capture_gang_freezed[faction_playerid -18] > 0)
		return SendError(playerid, "Ghalamro shoma freeze shode ast, nmitavand in kar ra anjam dahad.");
    if(gz_captured != -1)
		return SendError(playerid, "Darhal hazer yek tasarof dar hal anjam ast.");

	if(capture_gang_cd[faction_playerid -18] > 0)
		return SendError(playerid, "Capture ta %s dastres mishavad.", convert_time(capture_gang_cd[faction_playerid -18]));

    for(new i = 0; i < gz_count; i ++)
	{
		if(IsPlayerInGangZone(playerid, i))
		{
			if(gz_info[i][gz_owner] == faction_playerid)
				return SendError(playerid, "Shoma nemitavanid be ghalamro khod hamle konid.");

			if(f_diplomacy[faction_playerid -18][gz_info[i][gz_owner] -18] == dip_status_alliance)
				return SendError(playerid, "Shoma nemitavanid be ham-piman khod hamle konid.");

            if(capture_gang_freezed[gz_info[i][gz_owner] -18] > 0)
            	return SendError(playerid, "Shoma nemitavanid be in band hamle konid, anha freeze hastan.");

			if(capture_gang_cd[gz_info[i][gz_owner] -18] > 0)
				return SendError(playerid, "In band pas az capture ghabli esterat nakardeh ast.");

			if(playerInSpawnZone(playerid))
				return SendError(playerid, "Nemitavan be base gang hamle kard.");

			new owner_counts = 0;
			foreach(new j: logged_players) if(gz_info[i][gz_owner] == PlayerInfo[j][member]) owner_counts ++;

			if(owner_counts < 3)
				return SendError(playerid, "Shoma nemitavanid be in gang hamle konid, anha kheyli kamand.");

			gz_captured = i;
			gz_info[i][gz_time] = 1200;
			gz_info[i][gz_attacker] = faction_playerid;

			for(new x = 0; x < 2; x++) gz_info[i][gz_kills][x] = 0;

			foreach (new pl_id : logged_players) 
			{
				if ((PlayerInfo[pl_id][member] == faction_playerid) || 
					(PlayerInfo[pl_id][admin]) || 
					(PlayerInfo[pl_id][member] == gz_info[i][gz_owner]))
				{
					SendMes(pl_id, 0x33CC66FF, "[F] %s[%d] az \"%s\" shoru' be tasarof manteghe \"%s\" kard.", PlayerInfo[playerid][name], playerid, GetFractionName(PlayerInfo[playerid][member]), GetFractionName(gz_info[i][gz_owner]));
				}
			}

			foreach (new pl_id : logged_players) 
			{
				if ((PlayerInfo[pl_id][member] == faction_playerid) || 
					(PlayerInfo[pl_id][member] == gz_info[i][gz_owner]))
				{
					SendMes(pl_id, 0x33CC66FF, "[F] Shoma mitavanid amade shavid, shoma 1 daghighe zaman darid.");
				}
			}

			//------------
			//TopWar
			TopWar_SetGangs(gz_info[i][gz_owner], gz_info[i][gz_attacker]);
			TopWar_SetRecentGangs(gz_info[i][gz_owner], gz_info[i][gz_attacker]);
			TopWar_Setup();
			//------------

			owner_points = 0;
			attacker_points	= 0;
			PauseWarStatus = 0;

			capture_gang_cd[faction_playerid -18] = 3000;
			capture_gang_cd[gz_info[i][gz_owner] -18] = 3000;

			foreach(new pl_id: logged_players)
			{
				if(!gang_player(pl_id)) continue;

				SetPVarInt(pl_id, "gz_td_status", 1);
			}

			RunQuery("UPDATE `users` SET `u_capture_start` = `u_capture_start`+1 WHERE `u_id` = '%d' LIMIT 1", PlayerInfo[playerid][id]);

   			GangZoneFlashForAll(gz_info[i][gz_created], f_info[faction_playerid][f_radar_color]);

			gz_capture_type = 0;

			currentGz_tid = i;

			gz_info[i][gz_timer] = SetTimerEx("gangzone_timer", 1000, 1, "iiii", i, faction_playerid, gz_info[i][gz_owner], gz_capture_type);
			break;
		}
	}
	return 1;
}


cmd:capturetime(playerid)
{
	if(!gang_player(playerid)) return 1;

	new line_string[98];
	global_string = ""c_grey"* Territory capture time: from 12:00 to 23:00\n\n";
	for(new j = 0; j < 5; j ++)
	{
		format(line_string, sizeof(line_string), "{%s}Before capture %s:"c_white" %s\n",
		f_info[j + 17][f_chat_color], f_info[j + 17][f_name], convert_time(capture_gang_cd[j]));
		strcat(global_string, line_string);

	}
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_server"Information", global_string, "Bastan", "");
	return 1;
}

cmd:diplomacy(playerid)
{
	if(!gang_player(playerid) && ! mafia_player(playerid)) return 1;

	static const dip_status[][] = {
	"{FFF2C7}Neutrality",
	"{AA3333}War",
	"{33AA33}Union",
	""c_server"Call request",
	""c_server"Call request"
	};

	new pvar_string[8],
		step;

	global_string[0] = EOS;

	for(new i = 0; i < 8; i ++)
	{
		if(i + 18 == getPlayerFactionID(playerid)) continue;

		format(pvar_string, 8, "d_%d", step);
		SetPVarInt(playerid, pvar_string, i + 18);

		strcat(global_string, "{");
		strcat(global_string, f_info[i + 17][f_chat_color]);
		strcat(global_string, "}");
		strcat(global_string, f_info[i + 17][f_name]);
		strcat(global_string, "\t");
		strcat(global_string, dip_status[f_diplomacy[getPlayerFactionID(playerid) -18][i]]);
		strcat(global_string, "\n");
		step ++;
	}
	show_dialog(playerid, d_dip_list, DIALOG_STYLE_TABLIST, ""c_server"Diplomacy", global_string, "Entekhab", "Bastan");
	return 1;
}

cmd:dip(playerid)
{
	if(!gang_player(playerid) && ! mafia_player(playerid)) return 1;

	static const dip_status[][] = {
	"{FFF2C7}Neutrality",
	"{AA3333}War",
	"{33AA33}Union",
	""c_server"Call request",
	""c_server"Call request"
	};

	new pvar_string[8],
		step;

	global_string[0] = EOS;

	for(new i = 0; i < 8; i ++)
	{
		if(i + 18 == getPlayerFactionID(playerid)) continue;

		format(pvar_string, 8, "d_%d", step);
		SetPVarInt(playerid, pvar_string, i + 18);

		strcat(global_string, "{");
		strcat(global_string, f_info[i + 17][f_chat_color]);
		strcat(global_string, "}");
		strcat(global_string, f_info[i + 17][f_name]);
		strcat(global_string, "\t");
		strcat(global_string, dip_status[f_diplomacy[getPlayerFactionID(playerid) -18][i]]);
		strcat(global_string, "\n");
		step ++;
	}
	show_dialog(playerid, d_dip_list, DIALOG_STYLE_TABLIST, ""c_server"Diplomacy", global_string, "Entekhab", "Bastan");
	return 1;
}

cmd:wlock(playerid)
{
	if(!gang_player(playerid) && ! mafia_player(playerid)) return 1;
	if(PlayerInfo[playerid][rank] < f_info[PlayerInfo[playerid][member]][f_rank_settings][1]) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You miss this opportunity.");

	new sql_string[92];
	if(f_info[PlayerInfo[playerid][member]][f_dorm_status])
	{
		f_info[PlayerInfo[playerid][member]][f_dorm_status] = 0;
		format(sql_string, sizeof(sql_string), "UPDATE `fractions` SET `f_dorm_status` = '%d' WHERE `f_id` = '%d' LIMIT 1",
		f_info[PlayerInfo[playerid][member]][f_dorm_status],
		getPlayerFactionID(playerid));
		mysql_tquery(sql_connection, sql_string);
		GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~ DORM UNLOCKED", 3000, 3);
		SendClientMessage(playerid, col_white, ""c_green"* "c_white"Warehouse successfully "c_green"opened"c_white".");

		format(sql_string, sizeof sql_string, "* %s %s[%d] "c_green"opened "c_grey"warehouse.", f_rank[PlayerInfo[playerid][member]][PlayerInfo[playerid][rank] -1], PlayerInfo[playerid][name], playerid);
		foreach(new i: logged_players) if(PlayerInfo[i][member] == PlayerInfo[playerid][member]) SendClientMessage(i, col_gray, sql_string);
	}
	else
	{
		f_info[PlayerInfo[playerid][member]][f_dorm_status] = 1;
		format(sql_string, sizeof(sql_string), "UPDATE `fractions` SET `f_dorm_status` = '%d' WHERE `f_id` = '%d' LIMIT 1",
		f_info[PlayerInfo[playerid][member]][f_dorm_status],
		getPlayerFactionID(playerid));
		mysql_tquery(sql_connection, sql_string);
		GameTextForPlayer(playerid,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~ DORM LOCKED", 3000, 3);
		SendClientMessage(playerid, col_white, ""c_green"* "c_white"Warehouse successfully "c_green"closed"c_white".");

		format(sql_string, sizeof sql_string, "* %s %s[%d] "c_orange_red"closed "c_grey"warehouse.", f_rank[PlayerInfo[playerid][member]][PlayerInfo[playerid][rank] -1], PlayerInfo[playerid][name], playerid);
		foreach(new i: logged_players) if(PlayerInfo[i][member] == PlayerInfo[playerid][member]) SendClientMessage(i, col_gray, sql_string);

	}

	return 1;
}

cmd:gangtop(playerid)
{
	if(!gang_player(playerid)) return 1;
	show_dialog(playerid, d_gangtop, DIALOG_STYLE_LIST, ""c_server"List of highlights", ""c_grey"-"c_white"Best Shooters\n"c_grey"-"c_white"Top zavoroodikov", "Entekhab", "Barghast");
	return 1;
}

cmd:ganginfo(playerid)
{
	if(!gang_player(playerid)) return 1;
	global_string[0] = EOS;

	for(new i = 0; i < 5; i ++)
	{
		strcat(global_string, "{");
		strcat(global_string, f_info[i + 17][f_chat_color]);
		strcat(global_string, "}");
		strcat(global_string, f_info[i + 17][f_name]);
		strcat(global_string, "\n");
	}
	show_dialog(playerid, d_ganginfo, DIALOG_STYLE_LIST, ""scm_dialog"Band information", global_string, "Entekhab", "Barghast");
	return 1;
}

cmd:paygang(playerid, params[])
{
	if(!gang_player(playerid)|| !playerLeaderStatus(playerid)) return 1;
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /paygang [meghdar]");
	if(params[0] < 1 || params[0] > 1000000) return SendClientMessage(playerid, col_gray, ""scm_error"The amount cannot be less than $1 or more than $1,000,000");

	new num = 0;
	foreach(new i : logged_players)
	{
		if(PlayerInfo[i][member] != PlayerInfo[playerid][member] || playerid == i) continue;
		num++;
	}
	new str[180];
	format(str, sizeof(str), ""c_white"You really want to give out $%d to players who are in your gang?\n\n\
	"c_grey"* The amount may change if the online organization changes.", params[0]* num);
	show_dialog(playerid, d_paygang, DIALOG_STYLE_MSGBOX, ""c_server"Payroll", str, "Bale", "Khyer");
	SetPVarInt(playerid, "gangpay_sum", params[0]);
	return 1;
}

stock playerInSpawnZone(playerid)
{
	for(new i = 0; i < gz_count; i ++)
	{
		if(IsPlayerInGangZone(playerid, i))
		{
			if(gz_info[i][gz_id] == 94 || gz_info[i][gz_id] == 101 || gz_info[i][gz_id] == 45 || gz_info[i][gz_id] == 61 || gz_info[i][gz_id] == 57)
				return true;
		}
	}

	return false;
}

stock factionPlayerOwnerSpawn(playerid, spawnID)
{
	if(spawn_zone[spawnID][spawn_owner] == getPlayerFactionID(playerid))
		return true;

	return false;
}

cmd:ecar(playerid)
{
	if(is_player_in_journey[playerid] == 0) return SendError(playerid, "Shoma dar journey nistid.");
	
	new Float:bd_x, Float:bd_y, Float:bd_z, Float:vehicle_angle;
	GetJourneyDoorPos(is_player_in_journey[playerid], bd_x, bd_y, bd_z);
	GetVehicleZAngle(is_player_in_journey[playerid], vehicle_angle);
	set_pos(playerid, bd_x, bd_y, bd_z, vehicle_angle + 180, 0, 0);

	is_player_in_journey[playerid] = 0;
	return 1;
}

// TP System

cmd:settp(playerid)
{
	if(!gang_player(playerid)) 
		return SendError(playerid, "Shoma nmitavanid az in dastor estefade konid.");
    
	if(PlayerInfo[playerid][rank] < 9)
		return SendError(playerid, "Shoma nmitavanid az in dastor estefade konid.");
	
	if(gz_captured == -1)
		return SendError(playerid, "Hich wari darhal ejra nist.");
	
	new player_faction = PlayerInfo[playerid][member];

	if(player_faction != gz_info[gz_captured][gz_owner] && player_faction != gz_info[gz_captured][gz_attacker])
		return SendError(playerid, "Hich wari az band shoma darhal ejra nist.");

	if(f_info[player_faction][tp_label] == INVALID_3DTEXT_ID)
		destroyTeleport(player_faction);

	foreach(new i: logged_players) if((PlayerInfo[i][member] == player_faction || is_control_chat {i} == player_faction) && PlayerInfo[i][settings][0] != 0) SendMes(i, 0xFF6600FF, "%s %s[%d] set the teleport mark to capture the territory (/tp)", f_rank[player_faction][PlayerInfo[playerid][rank] -1], PlayerInfo[playerid][name], playerid);


	GetPlayerPos(playerid, f_info[player_faction][tp_pos][0], f_info[player_faction][tp_pos][1], f_info[player_faction][tp_pos][2]);
	GetPlayerFacingAngle(playerid, f_info[player_faction][tp_pos][3]);

	f_info[player_faction][tp_mapicon] = CreateDynamicMapIcon(f_info[player_faction][tp_pos][0], f_info[player_faction][tp_pos][1], f_info[player_faction][tp_pos][2], 42, 0, 0, 0, -1, 300.0);

	new string_tp[250];

	format(string_tp, sizeof string_tp, "{%s}%s\n\n"c_white"Create by: {%s}%s\nBaraye teleport kardan (/tp)", f_info[player_faction][f_chat_color], f_info[player_faction][f_name], f_info[player_faction][f_chat_color], PlayerInfo[playerid][name]);
	f_info[player_faction][tp_label] = CreateDynamic3DTextLabel(string_tp, col_gray, f_info[player_faction][tp_pos][0], f_info[player_faction][tp_pos][1], f_info[player_faction][tp_pos][2] + 0.3, 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);


	return 1;
}

cmd:tp(playerid)
{
	if(!gang_player(playerid)) 
		return SendError(playerid, "Shoma nmitavanid az in dastor estefade konid.");
	
	new player_faction = PlayerInfo[playerid][member];

	if(f_info[player_faction][tp_label] == INVALID_3DTEXT_ID)
		return SendError(playerid, "Leader / Sub Leader hich makan teleport set nakarde.");

	if(PlayerInfo[playerid][war_tp])
		return SendError(playerid, "Shoma mitavanid %d saniye digar teleport konid.", PlayerInfo[playerid][war_tp]);

    if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) 
    {
    	set_pos(playerid, f_info[player_faction][tp_pos][0], f_info[player_faction][tp_pos][1], f_info[player_faction][tp_pos][2], f_info[player_faction][tp_pos][3], 0, 0);
    }
    else 
    {
    	new carid = GetPlayerVehicleID(playerid);
    	SetVehiclePos(carid, f_info[player_faction][tp_pos][0], f_info[player_faction][tp_pos][1], f_info[player_faction][tp_pos][2]);
    	SetVehicleVirtualWorld(carid, 0);
		LinkVehicleToInterior(carid, 0);
    }

	SendInfo(playerid, "Shoma ba movafaghiat teleport kardid.");

	PlayerInfo[playerid][war_tp] = 160;

	return 1;
}

stock destroyTeleport(faction_id)
{
	DestroyDynamic3DTextLabel(f_info[faction_id][tp_label]);

	f_info[faction_id][tp_label] = Text3D:INVALID_3DTEXT_ID;

	DestroyDynamicMapIcon(f_info[faction_id][tp_mapicon]);

	return 1;
}