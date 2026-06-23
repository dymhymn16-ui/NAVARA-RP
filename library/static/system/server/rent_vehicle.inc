new rents_count;
#define MAX_RENTS 100

enum _rentinfo
{
	id,
	Float:rent_spawn[3],
	Float:rent_pos[4],
    rent_pickup,
    Text3D:rent_label_alt,
    Text3D:rent_label
};

new rent_info[MAX_RENTS][_rentinfo];

callback: rents_loading()
{
    new fields;
	cache_get_data(rents_count, fields);
	if(rents_count)
	{
        new dest[200];

        for(new i = 0; i < rents_count; i++)
		{
            rent_info[i][id] = cache_get_field_content_int(i, "id", sql_connection);

            cache_get_field_content(i, "rent_spawn", dest, sql_connection, sizeof dest);
		    sscanf(dest, "p<,>a<f>[3]", rent_info[i][rent_spawn]);

            cache_get_field_content(i, "rent_pos", dest, sql_connection, sizeof dest);
		    sscanf(dest, "p<,>a<f>[4]", rent_info[i][rent_pos]);

            rent_info[i][rent_pickup] = CreateDynamicPickup(1239, 23, rent_info[i][rent_spawn][0], rent_info[i][rent_spawn][1], rent_info[i][rent_spawn][2], -1, -1);

            rent_info[i][rent_label_alt] = CreateDynamic3DTextLabel(""c_grey"Interaction: "c_server"'ALT'", col_white,
				rent_info[i][rent_spawn][0], rent_info[i][rent_spawn][1], rent_info[i][rent_spawn][2],
				8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

            rent_info[i][rent_label] = CreateDynamic3DTextLabel(c_server"** Rent Vehicle **", col_white,
                rent_info[i][rent_spawn][0], rent_info[i][rent_spawn][1], rent_info[i][rent_spawn][2] + 0.7,
                8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
        }
    }
	printf("[SERVER] %d rents loaded.", rents_count);
	return 1;
}

cmd:createrent(playerid){
    if(check_admin_rank(playerid , 8)) return 1;

    new gate_position[200];

    if(!GetPVarInt(playerid, "step_two_rent"))
	{
        format(gate_position, sizeof gate_position, "%.4f,%.4f,%.4f", rent_info[rents_count][rent_spawn][0], rent_info[rents_count][rent_spawn][1], rent_info[rents_count][rent_spawn][2]);
        sscanf(gate_position, "p<,>a<f>[3]", rent_info[rents_count][rent_spawn]);

        GetPlayerPos(playerid, rent_info[rents_count][rent_spawn][0], rent_info[rents_count][rent_spawn][1], rent_info[rents_count][rent_spawn][2]);
        
        format(gate_position, sizeof gate_position, "%.4f,%.4f,%.4f", rent_info[rents_count][rent_spawn][0], rent_info[rents_count][rent_spawn][1], rent_info[rents_count][rent_spawn][2]);
        sscanf(gate_position, "p<,>a<f>[3]", rent_info[rents_count][rent_spawn]);

        new query_string[200];
        mysql_format(sql_connection, query_string, sizeof(query_string), "INSERT INTO `rent_pos`(`rent_spawn`, `rent_pos`) VALUES ('%s','unset')", gate_position);
        mysql_query(sql_connection, query_string);

        SetPVarInt(playerid, "step_two_rent", true);
        SetPVarInt(playerid, "rent_id_craete", rents_count);

        SendClientMessage(playerid, col_gray, c_green"[RENT-SYSTEM]"c_white" Moghe'iat spawn rent set shode, alan moghe'iat dovom ro set kon ba "c_yellow"/createrent");
    
    }else{
        new rent_id = GetPVarInt(playerid, "rent_id_craete");

        GetPlayerFacingAngle(playerid, rent_info[rent_id][rent_pos][3]);
        GetPlayerPos(playerid, rent_info[rent_id][rent_pos][0], rent_info[rent_id][rent_pos][1], rent_info[rent_id][rent_pos][2]);

        format(gate_position, sizeof gate_position, "%.4f,%.4f,%.4f,%.4f", rent_info[rent_id][rent_pos][0], rent_info[rent_id][rent_pos][1], rent_info[rent_id][rent_pos][2], rent_info[rent_id][rent_pos][3]);
        sscanf(gate_position, "p<,>a<f>[4]", rent_info[rent_id][rent_pos]);

        rent_info[rent_id][id] = find_last_rent();

        rent_info[rent_id][rent_pickup] = CreateDynamicPickup(1239, 23, rent_info[rent_id][rent_spawn][0], rent_info[rent_id][rent_spawn][1], rent_info[rent_id][rent_spawn][2], -1, -1);

        rent_info[rent_id][rent_label_alt] = CreateDynamic3DTextLabel(""c_grey"Interaction: "c_server"'ALT'", col_white,
                    rent_info[rent_id][rent_spawn][0], rent_info[rent_id][rent_spawn][1], rent_info[rent_id][rent_spawn][2],
                    8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

        rent_info[rent_id][rent_label] = CreateDynamic3DTextLabel(c_server"** Rent Vehicle **", col_white,
                    rent_info[rent_id][rent_spawn][0], rent_info[rent_id][rent_spawn][1], rent_info[rent_id][rent_spawn][2] + 0.7,
                    8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

        new query_string[200];
        mysql_format(sql_connection, query_string, sizeof(query_string), "UPDATE `rent_pos` SET `rent_pos`='%s' WHERE `id` = '%d'", gate_position, rent_info[rent_id][id]);
        mysql_query(sql_connection, query_string);

        DeletePVar(playerid, "step_two_rent");
        DeletePVar(playerid, "rent_id_craete");

        SendClientMessage(playerid, col_gray, c_green"[RENT-SYSTEM]"c_white" Rent ba movafaghiyat ijad shod va dar database zakhire shod.");

        rents_count++;
    }
    

    return 1;
}

stock find_last_rent()
{
    new _rent_count = 0, _rent_id = 0;
    new Cache:result = mysql_query(sql_connection, "SELECT `id` FROM `rent_pos` ORDER BY `rent_pos`.`id` DESC LIMIT 1");
    _rent_count = cache_num_rows();
    if(_rent_count) _rent_id = cache_get_field_content_int(0, "id", sql_connection);
    cache_delete(result);
    return _rent_id;
}