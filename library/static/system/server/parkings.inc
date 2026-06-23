#define MAX_PARKING 50
#define MAX_PARKING_NAME 60

enum e_parking
{
    p_mysql_id,
    p_name[MAX_PARKING_NAME],
    Float:p_enter[4],
    Text3D:p_label,
    p_pickup,
    p_faction
}
new ParkData[MAX_PARKING][e_parking],
    parking_count;

cmd:createparking(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;

    new parking_name[MAX_PARKING_NAME];

    if(sscanf(params, "s[60]", parking_name)) return SendInfo(playerid, "Enter: /createparking [parking name]");

    if(parking_count >= MAX_PARKING) return SendError(playerid, "Hadaksar tedad parkhaye mojaz rad shode ast (50/50).");

    new Float:Pos[3];
    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

    new Float:pA;
    GetPlayerFacingAngle(playerid, pA);

    format(ParkData[parking_count][p_name], 60, "%s", parking_name);

    ParkData[parking_count][p_enter][0] = Pos[0];
    ParkData[parking_count][p_enter][1] = Pos[1];
    ParkData[parking_count][p_enter][2] = Pos[2];
    ParkData[parking_count][p_enter][3] = pA;

    STRING_GLOBAL[0] = EOS;
    fmt(STRING_GLOBAL, c_server"%s [ID:%d]\nPress "c_white"'ALT'"c_server" to enter", ParkData[parking_count][p_name], parking_count+1);

    ParkData[parking_count][p_label] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, ParkData[parking_count][p_enter][0], ParkData[parking_count][p_enter][1], ParkData[parking_count][p_enter][2]+0.4, 11.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, -1);

    ParkData[parking_count][p_pickup] = CreateDynamicPickup(19134, 23, ParkData[parking_count][p_enter][0], ParkData[parking_count][p_enter][1], ParkData[parking_count][p_enter][2]+0.4, 0, 0);

    STRING_GLOBAL[0] = EOS;
    mysql_format(sql_connection, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `parkings` (`p_name`, `p_enterX`, `p_enterY`, `p_enterZ`, `p_enterA`) VALUES ('%s', '%f', '%f', '%f', '%f')",
    ParkData[parking_count][p_name], Pos[0], Pos[1], Pos[2], pA);
    mysql_tquery(sql_connection, STRING_GLOBAL, "create_park", "i", parking_count);

	SetPVarInt(playerid, !"parking_id", parking_count);

	strfmt(global_string, "{BC2C2C}None Faction\n");
	new line_string[65];

	for(new j = 0; j < fraction_count; j++)
	{
		format(line_string, sizeof(line_string), ""c_server"%d | {%s}%s\n", j + 1, f_info[j][f_chat_color], f_info[j][f_name]);
		strcat(global_string, line_string);
	}
    
	show_dialog(playerid, d_parking_faction, DIALOG_STYLE_LIST, "Select Parking Faction", global_string, !"Entekhab", !"Bastan");

    parking_count++;

    return 1;
}

stock check_parking(playerid)
{
    new playerstate = GetPlayerState(playerid);

    for(new h = 0; h < parking_count; h ++)
	{
        if(playerstate == PLAYER_STATE_ONFOOT || playerstate == PLAYER_STATE_DRIVER)
        {
            if(playerstate == PLAYER_STATE_DRIVER)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 6.0, ParkData[h][p_enter][0], ParkData[h][p_enter][1], ParkData[h][p_enter][2])) continue;
            }else
            {
                if(!IsPlayerInRangeOfPoint(playerid, 3.0, ParkData[h][p_enter][0], ParkData[h][p_enter][1], ParkData[h][p_enter][2])) continue; 
            }
          
            return h;
        }
    }

    return -1;
}


forward create_park(i);
public create_park(i)
{
    new _park_count = 0, _park_id = 0;
    new Cache:result = mysql_query(sql_connection, "SELECT `p_mysql_id` FROM `parkings` ORDER BY `parkings`.`p_mysql_id` DESC LIMIT 1");
    _park_count = cache_num_rows();
    if(_park_count) _park_id = cache_get_field_content_int(0, "p_mysql_id", sql_connection);
    cache_delete(result);

    ParkData[i][p_mysql_id] = _park_id;
    return 1;
}

forward load_park();
public load_park()
{
	new fields;
	cache_get_data(parking_count, fields);
	
	if(parking_count)
	{
        for(new idx = 0; idx < parking_count; idx ++)
        {
            ParkData[idx][p_mysql_id] = cache_get_field_content_int(idx, "p_mysql_id", sql_connection);
            ParkData[idx][p_enter][0] = cache_get_field_content_int(idx, "p_enterX", sql_connection);
            ParkData[idx][p_enter][1] = cache_get_field_content_int(idx, "p_enterY", sql_connection);
            ParkData[idx][p_enter][2] = cache_get_field_content_int(idx, "p_enterZ", sql_connection);
            ParkData[idx][p_enter][3] = cache_get_field_content_int(idx, "p_enterA", sql_connection);
            ParkData[idx][p_faction] = cache_get_field_content_int(idx, "p_faction", sql_connection);

            cache_get_field_content(idx, "p_name", ParkData[idx][p_name], sql_connection, MAX_PARKING_NAME);

            STRING_GLOBAL[0] = EOS;
            fmt(STRING_GLOBAL, c_server"%s [ID:%d]\nPress "c_white"'ALT'"c_server" to enter", ParkData[idx][p_name], idx+1);
            
            ParkData[idx][p_label] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, ParkData[idx][p_enter][0], ParkData[idx][p_enter][1], ParkData[idx][p_enter][2]+0.4, 11.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, -1);
            ParkData[parking_count][p_pickup] = CreateDynamicPickup(19134, 23, ParkData[idx][p_enter][0], ParkData[idx][p_enter][1], ParkData[idx][p_enter][2]+0.4, 0, 0);
        }

    }
    printf("[SERVER] %d parkings loaded.", parking_count);
    return true;
}
