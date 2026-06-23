new gang_graffiti[5];

#define MAX_GRAFFITI  150

new totalgraffiti;
enum E_GRAFFITI
{
    gID,
    gMember,
    gTime,
	Float:gX,
	Float:gY,
	Float:gZ,
	Float:grX,
	Float:grY,
	Float:grZ
};

new GRAFFITIInfo[MAX_GRAFFITI][E_GRAFFITI];
new GRAFFITI[MAX_GRAFFITI] = {INVALID_OBJECT_ID, ...};
new GraffitiObject[5] = {18659, 18664, 18663, 18661, 18665};


CMD:ggraffiti(playerid, params[])
{
    if(!gang_player(playerid)) return SendError(playerid, "Shoma nemitavanid az in dastor estefade konid.");

    SendInfo(playerid, "Taht control faction shoma %d graffiti ast.", gang_graffiti[getPlayerFactionID(playerid)-18]);
    return 1;
}

callback: load_graffiti()
{
    new fields;
	cache_get_data(totalgraffiti, fields);
	
	if(totalgraffiti)
	{
        for(new idx = 0; idx < totalgraffiti; idx ++)
        {
			GRAFFITIInfo[idx][gID] = cache_get_field_content_int(idx, "id", sql_connection);
			GRAFFITIInfo[idx][gMember] = cache_get_field_content_int(idx, "member", sql_connection);

            if(GRAFFITIInfo[idx][gMember] < 0) {
                GRAFFITIInfo[idx][gMember] = -1;
            }
            
            new invalidFactionID = -1;

            if(GRAFFITIInfo[idx][gMember] != -1)
            {
                for(new i = 0; i < fraction_count; i ++)
                {
                    if(f_info[i][f_id] == GRAFFITIInfo[idx][gMember]) 
                    {
                        GRAFFITIInfo[idx][gMember] = i;
                        invalidFactionID = 1;
                        break;
                    }
                    
                }
            }

            if(invalidFactionID == -1) GRAFFITIInfo[idx][gMember] = -1;

			GRAFFITIInfo[idx][gX] = cache_get_field_content_int(idx, "x", sql_connection);
			GRAFFITIInfo[idx][gY] = cache_get_field_content_int(idx, "y", sql_connection);
			GRAFFITIInfo[idx][gZ] = cache_get_field_content_int(idx, "z", sql_connection);
			GRAFFITIInfo[idx][grX] = cache_get_field_content_int(idx, "rx", sql_connection);
			GRAFFITIInfo[idx][grY] = cache_get_field_content_int(idx, "ry", sql_connection);
			GRAFFITIInfo[idx][grZ] = cache_get_field_content_int(idx, "rz", sql_connection);

            if(GRAFFITIInfo[idx][gMember] != -1) GRAFFITI[idx] = CreateDynamicObject(18661, GRAFFITIInfo[idx][gX], GRAFFITIInfo[idx][gY], GRAFFITIInfo[idx][gZ], GRAFFITIInfo[idx][grX], GRAFFITIInfo[idx][grY], GRAFFITIInfo[idx][grZ]);
            else GRAFFITI[idx] = CreateDynamicObject(18660, GRAFFITIInfo[idx][gX], GRAFFITIInfo[idx][gY], GRAFFITIInfo[idx][gZ], GRAFFITIInfo[idx][grX], GRAFFITIInfo[idx][grY], GRAFFITIInfo[idx][grZ]);
        }
    }

    for(new idx = 0; idx < sizeof(GRAFFITIInfo); idx++)
    {
        if(GRAFFITIInfo[idx][gMember] == -1) continue;
        gang_graffiti[f_info[GRAFFITIInfo[idx][gMember]][f_id]-18]++;
    }

    printf("[SERVER] %d Graffiti loaded.", totalgraffiti);

    return 1;
}