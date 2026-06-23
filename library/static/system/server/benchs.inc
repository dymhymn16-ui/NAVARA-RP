#if !defined TABLE_BENCHS
	#define TABLE_BENCHS "benchs"
#endif

#if !defined MAX_BENCHS
	#define MAX_BENCHS 1000
#endif

#define BENCH_USE_DYNAMIC_3DTEXT_LABEL true

enum benchs_enum {
	bool:exist,
	sql_id,
	Float:position[4],
	interior_id,
	virtualworld_id,
	textlabel_id
};
new Float:BenchAnimSitPositions[MAX_BENCHS][benchs_enum];

new bool:PlayerSitOnBench[MAX_PLAYERS];
new PlayerSitOnBenchId[MAX_PLAYERS];

static GetFreeBenchID() {
	for (new i = 0; i < sizeof BenchAnimSitPositions; i++) {
		if (!BenchAnimSitPositions[i][exist]) {
			return i;
		}
	}
	return -1;
}

Benchs_Init() {
	mysql_tquery(sql_connection, "SELECT * FROM `"TABLE_BENCHS"`", "benchs_loading");
}

forward benchs_loading();
public benchs_loading() {
	new rows = cache_num_rows();
	if (rows > 0) {
      	for (new i = 0; i < rows; i++)
        {
			BenchAnimSitPositions[i][exist] = true;
			BenchAnimSitPositions[i][sql_id] = cache_get_field_content_int(i, "id", sql_connection);
			BenchAnimSitPositions[i][position][0] = cache_get_field_content_float(i, "x", sql_connection);
			BenchAnimSitPositions[i][position][1] = cache_get_field_content_float(i, "y", sql_connection);
			BenchAnimSitPositions[i][position][2] = cache_get_field_content_float(i, "z", sql_connection);
			BenchAnimSitPositions[i][position][3] = cache_get_field_content_float(i, "angle", sql_connection);
			BenchAnimSitPositions[i][interior_id] = cache_get_field_content_int(i, "interior", sql_connection);
			BenchAnimSitPositions[i][virtualworld_id] = cache_get_field_content_int(i, "virtualworld", sql_connection);

			#if BENCH_USE_DYNAMIC_3DTEXT_LABEL
				BenchAnimSitPositions[i][textlabel_id] = CreateDynamic3DTextLabel(
					""c_light_green"'ALT' "c_white"(Baraye neshastan)", 
					col_white, 
					BenchAnimSitPositions[i][position][0], 
					BenchAnimSitPositions[i][position][1], 
					BenchAnimSitPositions[i][position][2], 
					3.0, 
					INVALID_PLAYER_ID, 
					INVALID_VEHICLE_ID, 
					1, 
					BenchAnimSitPositions[i][virtualworld_id], 
					BenchAnimSitPositions[i][interior_id]);
			#else
				BenchAnimSitPositions[i][textlabel_id] = Create3DTextLabel(
					""c_light_green"'ALT' "c_white"(Baraye neshastan)", 
					col_white, 
					BenchAnimSitPositions[i][position][0], 
					BenchAnimSitPositions[i][position][1], 
					BenchAnimSitPositions[i][position][2], 
					3.0,
					BenchAnimSitPositions[i][virtualworld_id],
					1);
			#endif
		}
	}
	printf("[SERVER] Loaded benchs: %d", rows);
}

CMD:addsit(playerid, params[]) {
	if (ReturnPlayerAdminLevel(playerid) < 8)
		return 1;

	new freeId = GetFreeBenchID();
	if (freeId == -1) {
		SendClientMessage(playerid, col_gray, ""scm_error"Cannot create more. \
			"#MAX_BENCHS"/"#MAX_BENCHS"");
		return 1;
	}

	new query[200];

	BenchAnimSitPositions[freeId][exist] = true;
	GetPlayerPos(playerid, BenchAnimSitPositions[freeId][position][0], BenchAnimSitPositions[freeId][position][1], BenchAnimSitPositions[freeId][position][2]);
	GetPlayerFacingAngle(playerid, BenchAnimSitPositions[freeId][position][3]);
	BenchAnimSitPositions[freeId][interior_id] = GetPlayerInterior(playerid);
	BenchAnimSitPositions[freeId][virtualworld_id] = GetPlayerVirtualWorld(playerid);
	
	#if BENCH_USE_DYNAMIC_3DTEXT_LABEL
		BenchAnimSitPositions[freeId][textlabel_id] = CreateDynamic3DTextLabel(
			""c_light_green"'ALT' "c_white"(Baraye neshastan)", 
			col_white, 
			BenchAnimSitPositions[freeId][position][0], 
			BenchAnimSitPositions[freeId][position][1], 
			BenchAnimSitPositions[freeId][position][2], 
			7.0, 
			INVALID_PLAYER_ID, 
			INVALID_VEHICLE_ID, 
			1, 
			BenchAnimSitPositions[freeId][virtualworld_id], 
			BenchAnimSitPositions[freeId][interior_id]);
	#else
		BenchAnimSitPositions[freeId][textlabel_id] = Create3DTextLabel(
			""c_light_green"'ALT' "c_white"(Baraye neshastan)", 
			col_white, 
			BenchAnimSitPositions[freeId][position][0], 
			BenchAnimSitPositions[freeId][position][1], 
			BenchAnimSitPositions[freeId][position][2], 
			7.0,
			BenchAnimSitPositions[freeId][virtualworld_id],
			1);
	#endif

	SendClientMessage(playerid, col_white, ""scm_sucess"created.");

	format(query, sizeof query, 
		"INSERT INTO `"TABLE_BENCHS"` (`x`, `y`, `z`, `angle`, `interior`, `virtualworld`) \
		VALUES (%f, %f, %f, %f, %d, %d)",
		BenchAnimSitPositions[freeId][position][0], BenchAnimSitPositions[freeId][position][1], BenchAnimSitPositions[freeId][position][2],
		BenchAnimSitPositions[freeId][position][3],
		BenchAnimSitPositions[freeId][interior_id],
		BenchAnimSitPositions[freeId][virtualworld_id]);

	mysql_tquery(sql_connection, query, "on_bench_insert", "d", freeId);
	return 1;
}

forward on_bench_insert(freeId);
public on_bench_insert(freeId) {
	BenchAnimSitPositions[freeId][sql_id] = cache_insert_id();
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

CMD:delsit(playerid, params[]) {
	if (ReturnPlayerAdminLevel(playerid) < 8)
		return 1;

	new benchId = -1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	for (new i = 0; i < sizeof BenchAnimSitPositions; i++) {
		if (!BenchAnimSitPositions[i][exist]) continue;
		if (GetDistance2D(x, y, BenchAnimSitPositions[i][position][0], BenchAnimSitPositions[i][position][1]) <= 0.9 &&
			BenchAnimSitPositions[i][virtualworld_id] == GetPlayerVirtualWorld(playerid)) {
			benchId = i;
			break;
		}
	}

	if (benchId == -1) {
		SendClientMessage(playerid, col_gray, ""scm_error"Bayad Be Kenar Label Beravid.");
		return 1;
	}

	new query[64];

	BenchAnimSitPositions[benchId][exist] = false;

	#if BENCH_USE_DYNAMIC_3DTEXT_LABEL
		DestroyDynamic3DTextLabel(BenchAnimSitPositions[benchId][textlabel_id]);
	#else
		Delete3DTextLabel(BenchAnimSitPositions[benchId][textlabel_id]);
	#endif

	SendClientMessage(playerid, col_white, ""scm_sucess"deleted.");

	format(query, sizeof query, 
		"DELETE FROM `"TABLE_BENCHS"` WHERE `id` = %d",
		BenchAnimSitPositions[benchId][sql_id]);

	mysql_tquery(sql_connection, query);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (!IsPlayerInAnyVehicle(playerid)) {
		if (PRESSED(KEY_WALK)) {

			for (new i; i < sizeof BenchAnimSitPositions; i++) {
				if (!BenchAnimSitPositions[i][exist]) continue;
	        	if (IsPlayerInRangeOfPoint(playerid, 0.9, BenchAnimSitPositions[i][position][0], BenchAnimSitPositions[i][position][1], BenchAnimSitPositions[i][position][2]) &&
					BenchAnimSitPositions[i][virtualworld_id] == GetPlayerVirtualWorld(playerid)) 
		        {
		            if (PlayerSitOnBench[playerid]) {
		                PlayerSitOnBench[playerid] = false;

		                ApplyAnimation(playerid, "DEALER", "SHOP_PAY", 4.1, 0, 0, 0, 0, 30, 1);

		                return 0;
		            }

		            PlayerSitOnBenchId[playerid] = i;
		            PlayerSitOnBench[playerid] = true;
					
					p_t_info[playerid][p_animation] = true;

		            SetPlayerPos(playerid, BenchAnimSitPositions[i][position][0], BenchAnimSitPositions[i][position][1], BenchAnimSitPositions[i][position][2]);
		            SetPlayerFacingAngle(playerid, BenchAnimSitPositions[i][position][3]);


		            ApplyAnimation(playerid, "PED", "SEAT_down",  4.0,  0,  0,  0,  1,  1 , 0);

		            return 0;
		        }
		    }

		}
	}

	#if defined Benchs_OnPlayerKeyStateChange
		return Benchs_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange Benchs_OnPlayerKeyStateChange
#if defined Benchs_OnPlayerKeyStateChange
	forward Benchs_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	PlayerSitOnBench[playerid] = false;

	#if defined Benchs_OnPlayerDisconnect
		return Benchs_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect Benchs_OnPlayerDisconnect
#if defined Benchs_OnPlayerDisconnect
	forward Benchs_OnPlayerDisconnect(playerid, reason);
#endif