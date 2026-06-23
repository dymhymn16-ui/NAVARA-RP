callback: houses_loading() //loadhouse load_house
{
	new fields;
	cache_get_data(house_count, fields);
	if(house_count)
	{
		for(new i = 0; i < house_count; i++)
		{
			h_info[i][h_id] = cache_get_field_content_int(i, "h_id", sql_connection);
			h_info[i][h_owner] = cache_get_field_content_int(i, "h_owner", sql_connection);
			cache_get_field_content(i, "h_ownername", h_info[i][h_owner_name], sql_connection, MAX_PLAYER_NAME);
			
			h_info[i][h_int] = cache_get_field_content_int(i, "h_int", sql_connection);
			if(!(1 <= h_info[i][h_int] <= HINTS_COUNT)) h_info[i][h_int] = 1;
			
			h_info[i][h_vw] = cache_get_field_content_int(i, "h_vw", sql_connection);

			h_info[i][h_pos][0] = cache_get_field_content_float(i,"h_pos_x", sql_connection);
			h_info[i][h_pos][1] = cache_get_field_content_float(i,"h_pos_y", sql_connection);
			h_info[i][h_pos][2] = cache_get_field_content_float(i,"h_pos_z", sql_connection);
			h_info[i][h_pos][3] = cache_get_field_content_float(i,"h_pos_c", sql_connection);

			h_info[i][h_v_pos][0] = cache_get_field_content_float(i,"h_v_pos_x", sql_connection);
			h_info[i][h_v_pos][1] = cache_get_field_content_float(i,"h_v_pos_y", sql_connection);
			h_info[i][h_v_pos][2] = cache_get_field_content_float(i,"h_v_pos_z", sql_connection);
			h_info[i][h_v_pos][3] = cache_get_field_content_float(i,"h_v_pos_c", sql_connection);

			h_info[i][h_radio_status] = cache_get_field_content_int(i, "h_radio_status", sql_connection);
			cache_get_field_content(i, "h_radio_url", h_info[i][h_radio_url], sql_connection, MAX_PLAYER_NAME);

			h_info[i][h_garage] = cache_get_field_content_int(i, "h_garage", sql_connection);
			h_info[i][h_price] = cache_get_field_content_int(i, "h_price", sql_connection);
			h_info[i][h_rent_price] = cache_get_field_content_int(i, "h_rent", sql_connection);
			h_info[i][h_closed] = cache_get_field_content_int(i, "h_closed", sql_connection);

			h_info[i][h_renters] = cache_get_field_content_int(i, "h_renters", sql_connection);

			h_info[i][h_safe_code] = cache_get_field_content_int(i, "h_safe_code", sql_connection);
			h_info[i][h_prods] = cache_get_field_content_int(i, "h_prods", sql_connection);

			h_info[i][h_days] = cache_get_field_content_int(i, "h_days", sql_connection);
			h_info[i][h_family] = cache_get_field_content_int(i, "h_family", sql_connection);

			new sscanf_delimit[48];
			cache_get_field_content(i, "h_improve", sscanf_delimit, sql_connection, 48);
			sscanf(sscanf_delimit, "p<|>dddddddd", h_info[i][h_improve][0], h_info[i][h_improve][1], h_info[i][h_improve][2],
			h_info[i][h_improve][3], h_info[i][h_improve][4], h_info[i][h_improve][5], h_info[i][h_improve][6], h_info[i][h_improve][7]);

			cache_get_field_content(i, "h_safe_data", sscanf_delimit, sql_connection, 36);
			sscanf(sscanf_delimit, "p<|>dddddddd", h_info[i][h_safe_data][0], h_info[i][h_safe_data][1],
			h_info[i][h_safe_guns][0],	h_info[i][h_safe_guns][1], h_info[i][h_safe_guns][2],
			h_info[i][h_safe_guns][3],	h_info[i][h_safe_guns][4], h_info[i][h_safe_guns][5]);

			h_info[i][h_seed] = cache_get_field_content_int(i, "h_seed", sql_connection);
			h_info[i][h_seed_result] = cache_get_field_content_int(i, "h_seed_result", sql_connection);


			if(h_info[i][h_garage] > 0)
			{
				h_info[i][h_garage_label] = CreateDynamic3DTextLabel("** Garage **\n"c_grey"Dokme "c_white"Y"c_grey", baraye vorod",col_lblue,
										h_info[i][h_v_pos][0], h_info[i][h_v_pos][1], h_info[i][h_v_pos][2],
										4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, -1);
			}

			new hint = h_info[i][h_int] -1;

			h_info[i][h_exit_label] = CreateDynamic3DTextLabel("Exit\nKey: "c_light_green"'ALT'",col_white,
													house_int[hint][hint_position][0], house_int[hint][hint_position][1], house_int[hint][hint_position][2] + 0.5,
													4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, h_info[i][h_id],  house_int[hint][hint_int]);

			if(h_info[i][h_owner] == -1)
			{
				if(!h_info[i][h_vw]) h_info[i][h_icon_id] = CreateDynamicMapIcon(h_info[i][h_pos][0], h_info[i][h_pos][1], h_info[i][h_pos][2], 31, 0, 0, 0, -1, 60.1000);
			}
			else
			{
				if(h_info[i][h_rent_price] == 0)
				{
					if(!h_info[i][h_vw]) h_info[i][h_icon_id] = CreateDynamicMapIcon(h_info[i][h_pos][0], h_info[i][h_pos][1], h_info[i][h_pos][2], 32, 0, 0, 0, -1, 60.1000);
				}
				else
				{
					if(!h_info[i][h_vw]) h_info[i][h_icon_id] = CreateDynamicMapIcon(h_info[i][h_pos][0], h_info[i][h_pos][1], h_info[i][h_pos][2], 31, 0, 0, 0, -1, 60.1000);
				}
			}

			h_info[i][h_enter_label] = CreateDynamic3DTextLabel("Loading...",COLOR_WHITE,
				h_info[i][h_pos][0], h_info[i][h_pos][1], h_info[i][h_pos][2] + 0.5,
				4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

			UpdateHouseEnterLabel(i);


			for(new k; k < 6; k++)
			{
				if(!h_info[i][h_improve][k]) continue;
				switch(k)
				{
					case 1:	CreateDynamic3DTextLabel("Exit\n"c_grey"Dokme "c_white"[Y]"c_grey" Ra Feshar Dahid", col_server, house_safe_pos[hint][0], house_safe_pos[hint][1], house_safe_pos[hint][2], 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, h_info[i][h_id], 2);
					case 2: CreateDynamic3DTextLabel("Cooler\n"c_grey"Dokme "c_white"[Y]"c_grey" Ra Feshar Dahid", col_server, house_freeze_pos[hint][0], house_freeze_pos[hint][1], house_freeze_pos[hint][2], 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, h_info[i][h_id], 2);
				}
			}
		}
    }
	printf("[SERVER] %d houses loaded.", house_count);
	return 1;
}

stock playerHouseStatus(playerid)
{
	if(PlayerInfo[playerid][house] != -1) return 1;
	else return 0;
}

stock playerRentHouseStatus(playerid)
{
	if(PlayerInfo[playerid][rent_house] != -1) return 1;
	else return 0;
}

stock getHouseID(houseid)
{
	for (new i = 0; i < house_count; i++)
	{
		if(h_info[i][h_id] == houseid)
		{
			return i;
		}
		
	}
	
	return -1;
}

stock getPlayerHouseID(playerid)
{
	if(playerHouseStatus(playerid)) return h_info[PlayerInfo[playerid][house]][h_id];
	else return -1;
}

stock getPlayerRentHouseID(playerid)
{
	if(playerRentHouseStatus(playerid)) return h_info[PlayerInfo[playerid][rent_house]][h_id];
	else return -1;
}

stock getFamilyHouseID(familyid)
{
	if(familyHouseStatus(familyid)) return h_info[family_info[familyid][fam_house]][h_id];
	else return -1;
}


stock find_last_house()
{
    new _house_count = 0, _house_id = 0;
    new Cache:result = mysql_query(sql_connection, "SELECT `h_id` FROM `houses` ORDER BY `houses`.`h_id` DESC LIMIT 1");
    _house_count = cache_num_rows();
    if(_house_count) _house_id = cache_get_field_content_int(0, "h_id", sql_connection);
    cache_delete(result);
    return _house_id;
}

stock save_house(houseid)
{
	new sql_string[220];
	format(sql_string, sizeof sql_string, "UPDATE `houses` SET `h_owner` = '%d',`h_ownername` = '%s',`h_closed` = '%d',`h_rent` = '%d',`h_days`=%d WHERE `h_id` = '%d' LIMIT 1",
	h_info[houseid][h_owner], h_info[houseid][h_owner_name], h_info[houseid][h_closed], h_info[houseid][h_rent_price], h_info[houseid][h_days], h_info[houseid][h_id]);
	mysql_tquery(sql_connection, sql_string, "", "");
	return 1;
}

cmd:houseprice(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;

	new houseId = -1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	for (new i = 0; i < house_count; i++) {
		if(GetDistanceBetweenPoints(x, y, z, h_info[i][h_pos][0], h_info[i][h_pos][1], h_info[i][h_pos][2]) <= 3.0) {
			houseId = i;
			break;
		}
	}

    if(houseId == -1)
        return SendClientMessage(playerid, col_white, ""scm_error"Bayad Be Kenar Khane Beravid.");

	new price;

	if(sscanf(params, "d", price)) 
		return SendClientMessage(playerid, col_gray,""scm_info"Enter: /houseprice [price]");

    // if(!(0 <= houseId < house_count)) return SendClientMessage(playerid, col_white, ""scm_error"Invalid House ID.");

    if(!(1 <= price < 800_000_000))
        return SendClientMessage(playerid, col_white, ""scm_error"Invalid Price. (1 to 800,000,000)");

	h_info[houseId][h_price] = price;
	UpdateHouseEnterLabel(houseId);

	new string[128];

	if(h_info[houseId][h_price] <= 15000)
		format(string, sizeof(string), "Price \"House #%d\" changed to {E8A60D}%d coin", houseId, h_info[houseId][h_price]);
	else
		format(string, sizeof(string), "Price \"House #%d\" changed to {18E70E}$%d", houseId, h_info[houseId][h_price]);

	SendClientMessage(playerid, col_white, string);

	format(string, sizeof(string), "UPDATE `houses` SET `h_price` = %d WHERE `h_id` = '%d'", 
		h_info[houseId][h_price], h_info[houseId][h_id]);
	mysql_tquery(sql_connection, string);
	return 1;
}

cmd:createhouse(playerid, params[])
{
	if(PlayerInfo[playerid][admin] < 8) return 1;
	if(sscanf(params, "ddd", params[0], params[1], params[2])) return SendInfo(playerid, "Enter: /createhouse [int] [Gheymat] [garage]");
	if(params[1] < 1) return SendError(playerid, "The price of a house cannot be less than 1.");
	if(!(1 <= params[0] <= HINTS_COUNT)) return SendError(playerid, "Enter int 1 to "#HINTS_COUNT"");
	if(!(1 <= params[2] <= HGARAGES_COUNT)) return SendError(playerid, "Enter garage 1 to "#HGARAGES_COUNT"");


	GetPlayerPos(playerid, h_info[house_count][h_pos][0], h_info[house_count][h_pos][1], h_info[house_count][h_pos][2]);
	GetPlayerFacingAngle(playerid, h_info[house_count][h_pos][3]);

	strcat(h_info[house_count][h_owner_name], "State Property");
	h_info[house_count][h_owner] = -1;
	h_info[house_count][h_family] = -1;
	h_info[house_count][h_days] = 5;
	h_info[house_count][h_price] = params[1];
	h_info[house_count][h_garage] = params[2];
	h_info[house_count][h_int] = params[0];
	h_info[house_count][h_vw] = p_t_info[playerid][p_data][1];

	h_info[house_count][h_radio_status] = 0;
	h_info[house_count][h_garage] = 0;
	h_info[house_count][h_rent_price] = 0;
	h_info[house_count][h_renters] = 0;
	h_info[house_count][h_safe_code] = 0000;
	h_info[house_count][h_prods] = 0;
	h_info[house_count][h_seed] = 0;
	h_info[house_count][h_seed_result] = 0;


	if(!h_info[house_count][h_vw]) h_info[house_count][h_icon_id] = CreateDynamicMapIcon(h_info[house_count][h_pos][0], h_info[house_count][h_pos][1], h_info[house_count][h_pos][2], 31, 0, 0, 0, -1, 60.1000);
	
	new query_string[300];
	mysql_format(sql_connection, query_string, sizeof(query_string ),"INSERT INTO `houses` (`h_pos_x`,`h_pos_y`,`h_pos_z`,`h_pos_c`,`h_price`,`h_vw`,`h_int`,`h_garage`) VALUES ('%f','%f','%f','%f','%d','%d','%d','%d')",
	h_info[house_count][h_pos][0], h_info[house_count][h_pos][1], h_info[house_count][h_pos][2], h_info[house_count][h_pos][3],
	params[1], h_info[house_count][h_vw], params[0], params[2]);
	mysql_tquery(sql_connection, query_string, "", "");

	h_info[house_count][h_id] = find_last_house();

	h_info[house_count][h_enter_label] = CreateDynamic3DTextLabel("Loading...",COLOR_WHITE,
		h_info[house_count][h_pos][0], h_info[house_count][h_pos][1], h_info[house_count][h_pos][2] + 0.5,
		4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

	new hint = h_info[house_count][h_int] -1;

	h_info[house_count][h_exit_label] = CreateDynamic3DTextLabel("Exit\nKey: "c_light_green"'ALT'",col_white,
								house_int[hint][hint_position][0], house_int[hint][hint_position][1], house_int[hint][hint_position][2] + 0.5,
								4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, h_info[house_count][h_id],  house_int[hint][hint_int]);

	sscanf("0|0|0|0|0|0|0|0", "p<|>dddddddd", h_info[house_count][h_improve][0], h_info[house_count][h_improve][1], h_info[house_count][h_improve][2],
		h_info[house_count][h_improve][3], h_info[house_count][h_improve][4], h_info[house_count][h_improve][5], h_info[house_count][h_improve][6], h_info[house_count][h_improve][7]);

	sscanf("0|0|0|0|0|0|0|0", "p<|>dddddddd", h_info[house_count][h_safe_data][0], h_info[house_count][h_safe_data][1],
		h_info[house_count][h_safe_guns][0],	h_info[house_count][h_safe_guns][1], h_info[house_count][h_safe_guns][2],
		h_info[house_count][h_safe_guns][3],	h_info[house_count][h_safe_guns][4], h_info[house_count][h_safe_guns][5]);

	SendAccess(playerid, "Shoma Ba Movafghiat amlak ijad kardid | house id %d.", h_info[house_count][h_id]);

	UpdateHouseEnterLabel(house_count);
	
	Streamer_Update(playerid);

	house_count ++;
	
	return 1;
}

cmd:gotohint(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, col_gray,""scm_info"Enter: /gotohint [int]");
	new hint = params[0] -1;
	set_pos(playerid, house_int[hint][hint_position][0], house_int[hint][hint_position][1], house_int[hint][hint_position][2], house_int[hint][hint_position][3], house_int[hint][hint_int], 3223);
	return 1;
}

cmd:hgarage(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /hgarage [house id] [garage type]");

	if(getHouseID(params[0]) == -1) return SendError(playerid, "ID khane nadorost ast.");
	if(GetPlayerState(playerid) != 2) return SendError(playerid, "Niaz be vasile naghlie darid.");

	new veh_id = GetPlayerVehicleID(playerid),
		house_id = getHouseID(params[0]);

	GetVehiclePos(veh_id, h_info[house_id][h_v_pos][0], h_info[house_id][h_v_pos][1], h_info[house_id][h_v_pos][2]);
	GetVehicleZAngle(veh_id, h_info[house_id][h_v_pos][3]);

	h_info[house_id][h_garage] = params[1];

	new scm_string[168];
	format(scm_string, 70, "You have set new garage coordinates for %d home.", params[0]);
	SendClientMessage(playerid, col_white, scm_string);

	format(scm_string, 168, "UPDATE `houses` SET `h_v_pos_x` = '%.2f', `h_v_pos_y` = '%.2f', `h_v_pos_z` = '%.2f',`h_v_pos_c` = '%.2f',`h_garage` = '%d' WHERE `h_id` = '%d'",
	h_info[house_id][h_v_pos][0], h_info[house_id][h_v_pos][1], h_info[house_id][h_v_pos][2],
	h_info[house_id][h_v_pos][3], params[1], params[0]);
	mysql_tquery(sql_connection, scm_string);

	if(h_info[house_id][h_garage] > 0)
	{
		DestroyDynamic3DTextLabel(h_info[house_id][h_garage_label]);

		h_info[house_id][h_garage_label] = CreateDynamic3DTextLabel("** Garage **\n"c_grey"Dokme "c_white"Y"c_grey", baraye vorod",col_lblue,
								h_info[house_id][h_v_pos][0], h_info[house_id][h_v_pos][1], h_info[house_id][h_v_pos][2],
								4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, -1);
	}

	return 1;
}

cmd:changehouseid(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /changehouseid [house id] [new house id]");

	if(getHouseID(params[0]) == -1 || getHouseID(params[1]) == -1) return SendError(playerid, "ID khane nadorost ast.");

	new house_id_1 = getHouseID(params[0]),
		house_id_2 = getHouseID(params[1]);


	SendAccess(playerid, "House ID #%d successfully changed to #%d", params[0], params[1]);

    new query[300];

    mysql_tquery(sql_connection, "START TRANSACTION;");

    format(query, sizeof(query), "UPDATE houses SET h_id = -h_id WHERE h_id = %d;", params[0]);
    mysql_tquery(sql_connection, query);

    format(query, sizeof(query), "UPDATE houses SET h_id = %d WHERE h_id = %d;", params[0], params[1]);
    mysql_tquery(sql_connection, query);

    format(query, sizeof(query), "UPDATE houses SET h_id = %d WHERE h_id = -%d;", params[1], params[0]);
    mysql_tquery(sql_connection, query);

    mysql_tquery(sql_connection, "COMMIT;");

	h_info[house_id_1][h_id] = params[1];
	h_info[house_id_2][h_id] = params[0];


	if(h_info[house_id_1][h_owner] != -1)
	{
		new h_owner_id = GetPlayerID(h_info[house_id_1][h_owner_name]);

		if(IsPlayerConnected(h_owner_id) && p_t_info[h_owner_id][p_logged])
		{
			PlayerInfo[h_owner_id][house] = house_id_2;
			update_int_sql(playerid, "u_house", h_info[house_id_2][h_id]);
		}else{
			format(query,sizeof(query),"UPDATE `users` SET `u_house` = '%d', WHERE `u_id` = '%d' LIMIT 1", params[0], h_info[house_id_1][h_owner]);
			mysql_tquery(sql_connection, query, "", "");
		}
	}

	if(h_info[house_id_2][h_owner] != -1)
	{
		new h_owner_id = GetPlayerID(h_info[house_id_2][h_owner_name]);

		if(IsPlayerConnected(h_owner_id) && p_t_info[h_owner_id][p_logged])
		{
			PlayerInfo[h_owner_id][house] = house_id_1;
			update_int_sql(playerid, "u_house", h_info[house_id_1][h_id]);
		}else{
			format(query,sizeof(query),"UPDATE `users` SET `u_house` = '%d', WHERE `u_id` = '%d' LIMIT 1", params[1], h_info[house_id_2][h_owner]);
			mysql_tquery(sql_connection, query, "", "");
		}
	}

	UpdateHouseEnterLabel(house_id_1);
	UpdateHouseEnterLabel(house_id_2);

	return 1;
}

cmd:hclass(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SendInfo(playerid, "Enter: /hclass [house id] [class type]");
	if(!(1 <= params[1] <= HINTS_COUNT)) return SendError(playerid, "Enter int 1 to "#HINTS_COUNT"");

	if(getHouseID(params[0]) == -1) return SendError(playerid, "ID khane nadorost ast.");

	new house_id = getHouseID(params[0]);

	h_info[house_id][h_int] = params[1];

	new scm_string[200];
	SendAccess(playerid, "You have set new class coordinates for %d home.", params[0]);

	format(scm_string, sizeof scm_string, "UPDATE `houses` SET `h_int` = '%d' WHERE `h_id` = '%d'", params[1], params[0]);
	mysql_tquery(sql_connection, scm_string);

	return 1;
}

cmd:sellhouse(playerid, params[])
{
	if(!playerHouseStatus(playerid)) return SendClientMessage(playerid, col_gray,""scm_error"Shoma hich khene nadarid.");
	new dialog_string[108];

	new house_id = PlayerInfo[playerid][house],
		house_price;

	if(h_info[house_id][h_price] <= 15000)
		house_price = h_info[house_id][h_price] * 7000;
	else
		house_price = h_info[house_id][h_price]/ 2;


	format(dialog_string, sizeof(dialog_string),""c_white"Shoma vaghan mikhahid khane khod ra bafrosid?\nGheymat foorosh: "c_server"$%s", convert_money(house_price));
	show_dialog(playerid, d_sellhouse, DIALOG_STYLE_MSGBOX, ""c_server"Forosh khane be dolat", dialog_string, "Foorosh", "Bastan");
	return 1;
}

cmd:findhouse(playerid, params[])
{
	if(is_gps_used {playerid})
	{
		DisablePlayerRaceCheckpoint(playerid);
		is_gps_used {playerid} = 0;
		is_searching_player_used[playerid] = INVALID_PLAYER_ID;
	}

    if(PlayerInfo[playerid][money] < 5000) return SendClientMessage(playerid, col_white, ""scm_error"Shoma $5000 Nadarid.");

	new houseId;

	if(sscanf(params, "d", houseId)) 
		return SendClientMessage(playerid, col_gray,""scm_info"Enter: /findhouse [house id]");

    if(getHouseID(houseId) == -1) return SendClientMessage(playerid, col_white, ""scm_error"Invalid House ID.");

	houseId = getHouseID(houseId);

	give_money(playerid, -5000);

	SetPlayerRaceCheckpoint(playerid, 1, h_info[houseId][h_pos][0], h_info[houseId][h_pos][1], h_info[houseId][h_pos][2], 0.0, 0.0, 0.0, 5.0);

	SendMes(playerid, col_white, "\"Khane #%d\" Roye GPS Set Shod: %.0f Meter Distance.", houseId, GetPlayerDistanceFromPoint(playerid, h_info[houseId][h_pos][0], h_info[houseId][h_pos][1], h_info[houseId][h_pos][2]));

	is_gps_used{playerid} = 1;

	return 1;
}

cmd:home(playerid)
{
	if(!playerHouseStatus(playerid)) return SendClientMessage(playerid, col_gray,""scm_error"Shoma Khone nadarid.");
	new h = PlayerInfo[playerid][house];
	if(!IsPlayerInRangeOfPoint(playerid, 30, house_int[h_info[h][h_int] -1][hint_position][0], house_int[h_info[h][h_int] -1][hint_position][1], house_int[h_info[h][h_int] -1][hint_position][2]) && GetPlayerVirtualWorld(playerid)!= h_info[h][h_id]) return SendClientMessage(playerid, col_gray, ""scm_error"Shoma bayad dar khane khod bashid.");
	show_hmenu(playerid);
	return 1;
}

cmd:hradio(playerid)
{
	if(!playerHouseStatus(playerid)) return SendClientMessage(playerid, col_gray,""scm_error"Shoma Khone nadarid.");
	new h = PlayerInfo[playerid][house];
	if(!IsPlayerInRangeOfPoint(playerid, 30, house_int[h_info[h][h_int] -1][hint_position][0], house_int[h_info[h][h_int] -1][hint_position][1], house_int[h_info[h][h_int] -1][hint_position][2]) && GetPlayerVirtualWorld(playerid)!= h_info[h][h_id]) return SendClientMessage(playerid, col_gray, ""scm_error"Shoma bayad dar khane khod bashid.");

	if(h_info[h][h_radio_status] == 0)show_dialog(playerid, d_h_radio, DIALOG_STYLE_LIST, ""c_server"Audio system", ""c_server"1."c_green" Turn on audio", "Entekhab", "Bastan");
	else show_dialog(playerid, d_h_radio, DIALOG_STYLE_LIST, ""c_server"Audio system", ""c_server"1."c_orange_red" Mute audio", "Entekhab", "Bastan");

	return 1;
}

cmd:hlock(playerid)
{
	if(!playerHouseStatus(playerid) && !playerRentHouseStatus(playerid)) return SendClientMessage(playerid, col_gray,""scm_error"Shoma Khone nadarid.");
	new h = PlayerInfo[playerid][house];
	if(h == -1) h = PlayerInfo[playerid][rent_house];


	if(!IsPlayerInRangeOfPoint(playerid, 4.00, h_info[h][h_pos][0], h_info[h][h_pos][1], h_info[h][h_pos][2]) &&
	(! IsPlayerInRangeOfPoint(playerid, 30, house_int[h_info[h][h_int] -1][hint_position][0], house_int[h_info[h][h_int] -1][hint_position][1], house_int[h_info[h][h_int] -1][hint_position][2]) && GetPlayerVirtualWorld(playerid)!= h_info[h][h_id])) return SendClientMessage(playerid, col_gray, ""scm_error"Shoma bayad dar khane khod bashid.");

	if(h_info[h][h_closed] == 0)
	{
		h_info[h][h_closed] = 1;
		GameTextForPlayer(playerid,"~r~closed", 2000, 3);
	}
	else
	{
		h_info[h][h_closed] = 0;
		GameTextForPlayer(playerid, "~g~opened", 2000, 3);
	}
	new query_string[78];
	format(query_string, sizeof(query_string), "UPDATE `houses` SET `h_closed` = '%d' WHERE `h_id` = '%d'", h_info[h][h_closed], getPlayerHouseID(playerid));
	mysql_tquery(sql_connection, query_string);

	return 1;
}

stock show_hmenu(playerid)
{
	new house_id = PlayerInfo[playerid][house];

	if(h_info[house_id][h_closed] == 1)
	{
		if(h_info[house_id][h_garage] == 0)
		{
			show_dialog(playerid, d_hmenu, DIALOG_STYLE_LIST, ""c_server"Modiriyat Khane",
			""c_server"1."c_green" Dar-e Khane ro Baz Kon\n"c_server"2."c_white" Etelaat Darbareye Khane\n"c_server"3."c_white" Behbood Khane\n"c_server"4."c_white" Komod Khane\n"c_server"5."c_white" Modiriyat Ejare\n"c_server"6."c_white" Raftan be Zir Zamin\n"c_grey"7. Raftan be Garage\n"c_server"8."c_white" Set Kardan Khane Family\n"c_server"9."c_white" Neshan dadan romz-e gavsandoogh", "Entekhab", "Bastan");
		}
		else
		{
			show_dialog(playerid, d_hmenu, DIALOG_STYLE_LIST, ""c_server"Modiriyat Khane",
			""c_server"1."c_green" Dar-e Khane ro Baz Kon\n"c_server"2."c_white" Etelaat Darbareye Khane\n"c_server"3."c_white" Behbood Khane\n"c_server"4."c_white" Komod Khane\n"c_server"5."c_white" Modiriyat Ejare\n"c_server"6."c_white" Raftan be Zir Zamin\n"c_server"7."c_white" Raftan be Garage\n"c_server"8."c_white" Set Kardan Khane Family\n"c_server"9."c_white" Neshan dadan romz-e gavsandoogh", "Entekhab", "Bastan");
		}
	}
	else
	{
		if(h_info[house_id][h_garage] == 0)
		{
			show_dialog(playerid, d_hmenu, DIALOG_STYLE_LIST, ""c_server"Modiriyat Khane",
			""c_server"1."c_orange_red" Dar-haye Khane ro Beband\n"c_server"2."c_white" Etelaat Darbareye Khane\n"c_server"3."c_white" Behbood Khane\n"c_server"4."c_white" Komod Khane\n"c_server"5."c_white" Modiriyat Ejare\n"c_server"6."c_white" Raftan be Zir Zamin\n"c_grey"7. Raftan be Garage\n"c_server"8."c_white" Set Kardan Khane Family\n"c_server"9."c_white" Neshan dadan romz-e gavsandoogh", "Entekhab", "Bastan");
		}
		else
		{
			show_dialog(playerid, d_hmenu, DIALOG_STYLE_LIST, ""c_server"Modiriyat Khane",
			""c_server"1."c_orange_red" Dar-haye Khane ro Beband\n"c_server"2."c_white" Etelaat Darbareye Khane\n"c_server"3."c_white" Behbood Khane\n"c_server"4."c_white" Komod Khane\n"c_server"5."c_white" Modiriyat Ejare\n"c_server"6."c_white" Raftan be Zir Zamin\n"c_server"7."c_white" Raftan be Garage\n"c_server"8."c_white" Set Kardan Khane Family\n"c_server"9."c_white" Neshan dadan romz-e gavsandoogh", "Entekhab", "Bastan");
		}
	}
	return 1;
}

cmd:asellhouse(playerid, params[])
{
	if(check_admin_rank(playerid , 7)) return 1;

	new house_id, isMsg;
	if(sscanf(params, "dD(1)", house_id, isMsg)) return SendClientMessage(playerid, col_white, !": /asellhouse [id house]");

	if(getHouseID(house_id) == -1) return SendClientMessage(playerid, col_gray, !"Unknown house indicated");

	new s_house_id = getHouseID(house_id);

	if(h_info[s_house_id][h_owner] == -1) return SendClientMessage(playerid, col_gray, !"The house is in gosse");

	new h_owner_id = GetPlayerID(h_info[s_house_id][h_owner_name]);

	if(IsPlayerConnected(h_owner_id) && p_t_info[h_owner_id][p_logged])
	{
		PlayerInfo[h_owner_id][house] = -1;
		update_int_sql(h_owner_id, "u_house", getPlayerHouseID(h_owner_id));

		PlayerInfo[h_owner_id][spawnchange] = 0;
		update_int_sql(h_owner_id, "u_spawnchange", PlayerInfo[h_owner_id][spawnchange]);

		SendClientMessage(h_owner_id, col_light_red, !"Admin sold your house");
	}
	else
	{
		new query_string[91];
		format(query_string,sizeof(query_string),"UPDATE `users` SET `u_house` = '-1', `u_spawnchange` = '-1' WHERE `u_id` = '%d' LIMIT 1", h_info[s_house_id][h_owner]);
		mysql_tquery(sql_connection, query_string, "", "");
	}

	strfmt(h_info[s_house_id][h_owner_name], "state property");
	h_info[s_house_id][h_family] = -1;
	h_info[s_house_id][h_owner] = -1;
	h_info[s_house_id][h_closed] = 0;
	if(!h_info[s_house_id][h_vw])DestroyDynamicMapIcon(h_info[s_house_id][h_icon_id]);
	if(!h_info[s_house_id][h_vw])h_info[s_house_id][h_icon_id] = CreateDynamicMapIcon(h_info[s_house_id][h_pos][0], h_info[s_house_id][h_pos][1], h_info[s_house_id][h_pos][2], 31, 0, 0, 0, -1, 60.1000);

	save_house(s_house_id);

	UpdateHouseEnterLabel(s_house_id);

	new data[48], query[128];
	for(new i;i<8;i++)
	{
		h_info[s_house_id][h_improve][i] = 0;
		if(!i)format(data, sizeof(data),"%d", h_info[s_house_id][h_improve][i]);
		else format(data, sizeof(data),"%s|%d", data, h_info[s_house_id][h_improve][i]);
	}
	format(query,sizeof(query),"UPDATE `houses` SET `h_improve` = '%s' WHERE `h_id` = '%d'", data, h_info[s_house_id][h_id]);
	mysql_tquery(sql_connection, query);

    h_info[s_house_id][h_safe_code] = 0;
 	format(query, sizeof query, "UPDATE `houses` SET `h_safe_code` = '0000',`h_family`='-1' WHERE `h_id` = '%d' LIMIT 1", h_info[s_house_id][h_id]);
	mysql_tquery(sql_connection, query);

	if(isMsg == 1) SendClientMessage(playerid, col_white, "Real estate successfully sold by the states.");
	return 1;
}

cmd:gotohouse(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, col_gray,""scm_info"Enter: /gotohouse [id]");
	if(getHouseID(params[0]) == -1) return SendError(playerid, "Home not found.");

	new house_id = getHouseID(params[0]);

	set_pos(playerid, h_info[house_id][h_pos][0], h_info[house_id][h_pos][1], h_info[house_id][h_pos][2], 90, 0, 0);
	new scm_string[82];
	
	format(scm_string, sizeof(scm_string ),""c_server"* A.INFO: "c_grey"You teleported to the house | ID: %d", params[0]);
	SendClientMessage(playerid, col_gray, scm_string);
	return 1;
}

cmd:exit(playerid)
{
	// --------------
	if(CommandExitForCounterStrike(playerid)) return 1;
	if(CommandExitForFallout(playerid)) return 1;
	if(CommandExitForColormatch(playerid)) return 1;
	// --------------

	new h = p_t_info[playerid][house];
	if(h == -1) return SendError(playerid, "Shoma dar hich khane'e nistid.");

	set_pos(playerid, h_info[h][h_pos][0], h_info[h][h_pos][1], h_info[h][h_pos][2], h_info[h][h_pos][3], 0, h_info[h][h_vw]);
	SetPVarInt(playerid, "tp_area_used", 1);
	p_t_info[playerid][house] = -1;
	if(h_info[h][h_radio_status] == 1) StopAudioStreamForPlayer(playerid);
	return 1;
}

cmd:cellar(playerid, params[])
{
	new house_id = p_t_info[playerid][house];
	if(house_id < 0) return SendClientMessage(playerid, col_gray,""scm_error"Shoma bayad dakhel khane bashid.");
	if(h_info[house_id][h_improve][5] == 0)
	{
		return SendClientMessage(playerid, col_gray, ""scm_error"In khane be zirzamin mojahhaz nist.");
	}
	set_pos(playerid, 1400.0562, -9.9276, 1000.9152, 176.1147, 4, h_info[house_id][h_id]);
	SetPVarInt(playerid, "tp_area_used", 1);
	return 1;
}

cmd:garage(playerid, params[])
{
	new house_id = p_t_info[playerid][house];
	if(house_id < 0) return SendClientMessage(playerid, col_gray,""scm_error"Shoma bayad dakhel khane bashid.");
	new houseGarage = h_info[house_id][h_garage];
	if(houseGarage == 0)
	{
		return SendClientMessage(playerid, col_gray, ""scm_error"In khane be garage mojahhaz nist.");
	}
	houseGarage--;
	set_pos(playerid, house_garage_player_enter[houseGarage][0], house_garage_player_enter[houseGarage][1], house_garage_player_enter[houseGarage][2], house_garage_player_enter[houseGarage][3], 1, h_info[house_id][h_id]);
	SetPVarInt(playerid, "tp_area_used", 1);
	return 1;
}


stock SellHouse(s_house_id) {
	if(h_info[s_house_id][h_owner] == -1)
		return 1;

	new h_owner_id = GetPlayerID(h_info[s_house_id][h_owner_name]);

	if(IsPlayerConnected(h_owner_id))
	{
		PlayerInfo[h_owner_id][house] = -1;
		// update_int_sql(h_owner_id, "u_house", PlayerInfo[h_owner_id][house]);

		PlayerInfo[h_owner_id][spawnchange] = 0;
		// update_int_sql(h_owner_id, "u_spawnchange", PlayerInfo[h_owner_id][spawnchange]);

		SendClientMessage(h_owner_id, col_light_red, "Khane Shoma Be Dalil Tamdid Nakardan Forokhte Shod.");
	}
	new query_string[100];
	format(query_string,sizeof(query_string),"UPDATE `users` SET `u_house` = '-1', `u_spawnchange` = '-1' WHERE `u_id` = '%d' LIMIT 1", h_info[s_house_id][h_owner]);
	mysql_tquery(sql_connection, query_string, "", "");


	strfmt(h_info[s_house_id][h_owner_name], "state property");
	h_info[s_house_id][h_family] = -1;
	h_info[s_house_id][h_owner] = -1;
	h_info[s_house_id][h_closed] = 0;
	if(!h_info[s_house_id][h_vw]) DestroyDynamicMapIcon(h_info[s_house_id][h_icon_id]);
	if(!h_info[s_house_id][h_vw])h_info[s_house_id][h_icon_id] = CreateDynamicMapIcon(h_info[s_house_id][h_pos][0], h_info[s_house_id][h_pos][1], h_info[s_house_id][h_pos][2], 31, 0, 0, 0, -1, 60.1000);

	save_house(s_house_id);

	UpdateHouseEnterLabel(s_house_id);

	new data[48], query[200];
	
	for(new i;i<8;i++)
	{
		h_info[s_house_id][h_improve][i] = 0;
		if(!i)format(data, sizeof(data),"%d", h_info[s_house_id][h_improve][i]);
		else format(data, sizeof(data),"%s|%d", data, h_info[s_house_id][h_improve][i]);
	}

    h_info[s_house_id][h_safe_code] = 0;
 	format(query, sizeof query, "UPDATE `houses` SET `h_safe_code`='0000',`h_family`='-1',`h_improve`='%s' WHERE `h_id` = '%d' LIMIT 1", data, h_info[s_house_id][h_id]);
	mysql_tquery(sql_connection, query);
	
	new File:lFile, year, month, day;
    getdate(year, month, day);
    format(query_string, sizeof(query_string), "[%i-%02d-%02d | %02d:%02d]: Khane '%s' (ID %d) Forokhte Shod. (Tamdid Nakarde) (%d/30)\r\n",year, month, day, timestamp_hour, timestamp_minute, h_info[s_house_id][h_owner_name], s_house_id, h_info[s_house_id][h_days]);
    lFile = fopen("sell_house.txt", io_append);
    fwrite(lFile, query_string);
    fclose(lFile);

	return 1;
}