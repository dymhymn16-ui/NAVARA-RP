#if !defined TABLE_MAP_ICONS
	#define TABLE_MAP_ICONS "mapicons"
#endif

#if !defined MAX_MAP_ICONS
	#define MAX_MAP_ICONS 400
#endif

enum map_icons_enum {
	bool:exist,
	sql_id,
	mapicon_id,
	Float:position[3],
	interior,
	virtual_world,
	Float:stream_distance,
	streamer_id
}
static MapIcons[MAX_MAP_ICONS][map_icons_enum];

static GetFreeMapIconID() {
	for (new i = 0; i < sizeof MapIcons; i++) {
		if (!MapIcons[i][exist]) {
			return i;
		}
	}
	return -1;
}

MapIcons_Init() {
	mysql_tquery(sql_connection, "SELECT * FROM `"TABLE_MAP_ICONS"`", "mapicons_loading");
}

forward mapicons_loading();
public mapicons_loading() {
	new rows = cache_num_rows();
	if (rows > 0) {
      	for (new i = 0; i < rows; i++)
        {
			MapIcons[i][exist] = true;
			MapIcons[i][sql_id] = cache_get_field_content_int(i, "id", sql_connection);
			MapIcons[i][mapicon_id] = cache_get_field_content_int(i, "mapicon_id", sql_connection);
			MapIcons[i][position][0] = cache_get_field_content_float(i, "x", sql_connection);
			MapIcons[i][position][1] = cache_get_field_content_float(i, "y", sql_connection);
			MapIcons[i][position][2] = cache_get_field_content_float(i, "z", sql_connection);
			MapIcons[i][interior] = cache_get_field_content_int(i, "interior", sql_connection);
			MapIcons[i][virtual_world] = cache_get_field_content_int(i, "virtual_world", sql_connection);
			MapIcons[i][stream_distance] = cache_get_field_content_float(i, "stream_distance", sql_connection);

			MapIcons[i][streamer_id] = CreateDynamicMapIcon(
				MapIcons[i][position][0],
				MapIcons[i][position][1],
				MapIcons[i][position][2], 
				MapIcons[i][mapicon_id], 
				0, 
				MapIcons[i][virtual_world], 
				MapIcons[i][interior], 
				-1, 
				MapIcons[i][stream_distance], 
				MAPICON_LOCAL);
		}
	}
	printf("[SERVER] Loaded map icons: %d", rows);
}

CMD:addmapicon(playerid, params[]) {
	if (ReturnPlayerAdminLevel(playerid) < 8)
		return 1;

	new mapIconId, interiorId, virtualWorld, range;
	if (sscanf(params, "ddI(-65535)I(-65535)", mapIconId, range, interiorId, virtualWorld)) {
		SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Enter: /addmapicon [id] [range]");
		return 1;
	}
	if (!(0 <= mapIconId <= 63)) {
		SendClientMessage(playerid, col_gray, ""scm_error"id Bayad Beyne 0 Ta 63 Bashad.");
		return 1;
	}
	if (!(1 <= range <= 500)) {
		SendClientMessage(playerid, col_gray, ""scm_error"range Bayad Beyne 1 Ta 500 Bashad. (300 = default)");
		return 1;
	}

	new freeId = GetFreeMapIconID();
	if (freeId == -1) {
		SendClientMessage(playerid, col_gray, ""scm_error"Cannot create more mapicons. \
			"#MAX_MAP_ICONS"/"#MAX_MAP_ICONS"");
		return 1;
	}

	new query[200];

	if (interiorId == -65535) {
		interiorId = GetPlayerInterior(playerid);
	}

	if (virtualWorld == -65535) {
		virtualWorld = GetPlayerVirtualWorld(playerid);
	}

	MapIcons[freeId][exist] = true;
	GetPlayerPos(playerid, MapIcons[freeId][position][0], MapIcons[freeId][position][1], MapIcons[freeId][position][2]);
	MapIcons[freeId][interior] = interiorId;
	MapIcons[freeId][virtual_world] = virtualWorld;
	MapIcons[freeId][mapicon_id] = mapIconId;
	MapIcons[freeId][stream_distance] = float(range);
	
	MapIcons[freeId][streamer_id] = CreateDynamicMapIcon(
		MapIcons[freeId][position][0],
		MapIcons[freeId][position][1],
		MapIcons[freeId][position][2], 
		MapIcons[freeId][mapicon_id], 
		0, 
		MapIcons[freeId][virtual_world], 
		MapIcons[freeId][interior], 
		-1, 
		MapIcons[freeId][stream_distance], 
		MAPICON_LOCAL);

	SendClientMessage(playerid, col_white, ""scm_sucess"Map Icon Sakhte Shod.");

	format(query, sizeof query, 
		"INSERT INTO `"TABLE_MAP_ICONS"` (`mapicon_id`, `x`, `y`, `z`, `interior`, `virtual_world`, `stream_distance`) \
		VALUES (%d, %f, %f, %f, %d, %d, %f)",
		MapIcons[freeId][mapicon_id],
		MapIcons[freeId][position][0], MapIcons[freeId][position][1], MapIcons[freeId][position][2],
		MapIcons[freeId][interior],
		MapIcons[freeId][virtual_world],
		MapIcons[freeId][stream_distance]);

	mysql_tquery(sql_connection, query, "on_mapicon_insert", "d", freeId);
	return 1;
}

forward on_mapicon_insert(freeId);
public on_mapicon_insert(freeId) {
	MapIcons[freeId][sql_id] = cache_insert_id();
}

static Float:GetDistance2D(Float:x1, Float:y1, Float:x2, Float:y2, bool:sqrt = true)
{
    x1 -= x2;
    x1 *= x1;
    y1 -= y2;
    y1 *= y1;
    x1 += y1;
    return sqrt ? floatsqroot(x1) : x1;
}

CMD:delmapicon(playerid, params[]) {
	if (ReturnPlayerAdminLevel(playerid) < 8)
		return 1;

	new mapIconId = -1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	for (new i = 0; i < sizeof MapIcons; i++) {
		if (!MapIcons[i][exist]) continue;
		if (GetDistance2D(x, y, MapIcons[i][position][0], MapIcons[i][position][1]) <= 10.0) {
			mapIconId = i;
			break;
		}
	}

	if (mapIconId == -1) {
		SendClientMessage(playerid, col_gray, ""scm_error"Bayad Be Kenar Map Icon Beravid.");
		return 1;
	}

	new query[64];

	MapIcons[mapIconId][exist] = false;
	DestroyDynamicMapIcon(MapIcons[mapIconId][streamer_id]);

	SendClientMessage(playerid, col_white, ""scm_sucess"Map Icon Delete Shod.");

	format(query, sizeof query, 
		"DELETE FROM `"TABLE_MAP_ICONS"` WHERE `id` = %d",
		MapIcons[mapIconId][sql_id]);

	mysql_tquery(sql_connection, query);
	return 1;
}

CMD:rangemapicon(playerid, params[]) {
	if (ReturnPlayerAdminLevel(playerid) < 8)
		return 1;

	new mapIconId = -1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	for (new i = 0; i < sizeof MapIcons; i++) {
		if (!MapIcons[i][exist]) continue;
		if (GetDistance2D(x, y, MapIcons[i][position][0], MapIcons[i][position][1]) <= 10.0) {
			mapIconId = i;
			break;
		}
	}

	if (mapIconId == -1) {
		SendClientMessage(playerid, col_gray, ""scm_error"Bayad Be Kenar Map Icon Beravid.");
		return 1;
	}

	new range;
	if (sscanf(params, "d", range)) {
		SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Enter: /rangemapicon [range]");
		return 1;
	}
	if (!(1 <= range <= 500)) {
		SendClientMessage(playerid, col_gray, ""scm_error"range Bayad Beyne 1 Ta 500 Bashad. (300 = default)");
		return 1;
	}

	new query[100];

	MapIcons[mapIconId][stream_distance] = float(range);
	Streamer_SetFloatData(
		STREAMER_TYPE_MAP_ICON, 
		MapIcons[mapIconId][streamer_id], 
		E_STREAMER_STREAM_DISTANCE, 
		MapIcons[mapIconId][stream_distance]);

	format(query, 64, 
		""scm_sucess"Range Map Icon Update Shod Be %d.",
		range);
	SendClientMessage(playerid, col_white, query);

	format(query, sizeof query, 
		"UPDATE `"TABLE_MAP_ICONS"` SET `stream_distance` = %f WHERE `id` = %d",
		MapIcons[mapIconId][stream_distance],
		MapIcons[mapIconId][sql_id]);

	mysql_tquery(sql_connection, query);
	return 1;
}