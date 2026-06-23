#if defined _metro_stop_included
	#endinput
#endif
#define _metro_stop_included

#if defined _metro_stop_included
	#define MAX_METRO_STOP_NAME	32
	#define METRO_INTERIOR_ID	5
	#define METRO_ROUTE_PRICE 	10 // $250

	#define METRO_STATION_DISTANCE	5.0
#endif

enum METRO_STOP_E {
	msName[MAX_METRO_STOP_NAME],
	msArea,
	Text3D:msText,
	Float:msPos[4],
	Float:msStationPos[6],
	msStationType,
	msWaitTime,
	msPickupID,
	msMapIconID,
	msSpeed
};
new MetroStationInfo[][METRO_STOP_E] = {
	{ "Railway Los Santos", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1772.8097, -1941.4541, 13.6463, 179.3422}, {1775.464721, -1941.249755, 10.232057, 0.0, 0.0, 0.0}, 2 },
	{ "Los Santos train station", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1950.0671, -2099.9065, 13.5956, 85.0178}, {1950.166015, -2102.440185, 10.181360, -0.000022, 0.0, -89.999900}, 1 },
	{ "Central Los Santos", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1652.7644, -1604.2094, 13.7349, 177.022}, {1655.354736, -1604.000366, 10.202184, -0.0, 0.500113, 0.0}, 1 },
	{ "Boat", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {615.7380, -1503.5029, 14.9340, 85.7062}, {615.777954, -1506.166503, 11.609760, -0.0, 0.0, -89.999946}, 1 },
	{ "Hospital city of Los Santos", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1217.6338, -1339.8987, 13.8156, 266.4648}, {1217.436889, -1337.251098, 10.3, 0.0, 0.0, 89.699951}, 1 },
	{ "Road Los Santos", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {2295.7781, -1214.5850, 24.2254, 86.6937}, {2295.835937, -1217.218750, 20.811159, -0.0, 0.0, -89.999923}, 2 },
	{ "Vinewood", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {106.1870, -1561.3304, 7.9091, 164.4171}, {106.968284, -1561.413208, 4.598847, 0.0, 0.0, -24.700006}, 1 },
	{ "Railway San Fierro", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {-1995.5001, 70.2498, 28.8729, 271.775}, {-1995.710815, 72.405570, 25.083684, -0.0, 6.899992, 89.999977}, 2 },
	{ "Central San Fierro", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {-2263.8748, 427.8391, 35.2798, 47.1092}, {-2265.279052, 425.892944, 31.925594, -0.0, -0.000012, -129.099975}, 1 },
    { "Fort Carson", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {-77.1224, 1178.7816, 19.8272, 98.5384}, {-76.909889, 1176.147827, 16.552961, -0.0, 0.0, -89.999923}, 1 },
    { "Railway Las Venturas", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {2789.4402, 1324.9789, 11.0242, 8.0289}, {2786.861083, 1324.921142, 7.494196, 0.0, -0.0, 179.999847}, 1 },
    { "Hospital Las Venturas", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1658.5389, 1830.6097, 11.1561, 271.3095}, {1658.715454, 1832.817626, 7.566228, -0.0, -0.0, 90.0}, 0 },
	{ "Central Las Venturas", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {2030.6613, 1291.6230, 10.9261, 92.6553}, {2030.546752, 1289.099853, 7.676076, -0.0, 0.0, -89.999946}, 1 },
	{ "Los Santos", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1726.4681, -1322.6925, 13.6398, 266.6574}, {1726.259399, -1320.036987, 10.129796, -0.0, 0.0, 89.999992}, 1 },
	{ "Los Santos airport", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1580.6787, -2330.4792, 13.7456, 179.2156}, {1583.303588, -2330.270019, 10.235646, -0.0, 0.0, 0.0}, 2 },
	{ "Ganton", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {2421.2969, -1780.0392, 13.7107, 264.46}, {2421.085693, -1777.387451, 10.205320, -0.000001, -0.100100, 89.999961}, 1 },
	{ "Los Santos driving school", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {615.7986, -1429.1450, 14.0806, 87.5359}, {616.009277, -1431.865234, 10.645569, -0.000002, -1.600004, -90.000015}, 1 },
	{ "Santa Maria Beach", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {353.3419, -1753.6027, 5.0663, 271.5664}, {352.854309, -1751.126831, 1.486683, 0.398289, 1.599853, 95.836952}, 1 },
	{ "Skate Park", INVALID_DYNAMIC_AREA_ID, INVALID_DYNAMIC_3D_TEXT_ID, {1835.1935, -1396.3192, 13.5880, 84.655}, {1835.404663, -1398.946166, 10.077966, 0.000001, 0.000007, -90.00001}, 1 }

};
#define MAX_METRO_STOP 	sizeof (MetroStationInfo)

new MetroDialogItemID[MAX_PLAYERS][MAX_METRO_STOP], MetroInteriorObjectID[4];

#define METRO_STATIONS_TIMER    (3) // every 3s
static metroStationsTimer, METRO_TABLES_UPDATE;

ms_OnGameModeInit() {
	for (new ms_id = 0, ms_string[MAX_METRO_STOP_NAME + 144], ms_wait_time = (30 + 10); ms_id < MAX_METRO_STOP; ms_id++) {
		format(ms_string, sizeof(ms_string), 
			"{FFFFFF}Istgah: {3EF27D}%s\n \n{FFFFFF}Zaman entezar takriban: 30 saniye.\n{3EF27D}Safar rayegan baraye fukara.\n \n{FFFFFF}Entekhab istgah ba {3EF27D}\"ALT\"",
			MetroStationInfo[ms_id][msName]
		);
		MetroStationInfo[ms_id][msPickupID] = CreateDynamicPickup(1239, 23, MetroStationInfo[ms_id][msPos][0], MetroStationInfo[ms_id][msPos][1], MetroStationInfo[ms_id][msPos][2], 0);
		MetroStationInfo[ms_id][msMapIconID] = CreateDynamicMapIcon(MetroStationInfo[ms_id][msPos][0], MetroStationInfo[ms_id][msPos][1], MetroStationInfo[ms_id][msPos][2], 26, col_white);

		MetroStationInfo[ms_id][msText] = CreateDynamic3DTextLabel(
			ms_string, 0xFFFFFFFF, MetroStationInfo[ms_id][msPos][0], MetroStationInfo[ms_id][msPos][1], MetroStationInfo[ms_id][msPos][2], 
			7.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0
		);	
		MetroStationInfo[ms_id][msArea] = CreateDynamicSphere(
			MetroStationInfo[ms_id][msPos][0], MetroStationInfo[ms_id][msPos][1], MetroStationInfo[ms_id][msPos][2], METRO_STATION_DISTANCE, 0, 0, -1
		);
		ms_CreateStationObject(
			MetroStationInfo[ms_id][msStationPos][0], MetroStationInfo[ms_id][msStationPos][1], MetroStationInfo[ms_id][msStationPos][2],
			MetroStationInfo[ms_id][msStationPos][3], MetroStationInfo[ms_id][msStationPos][4], MetroStationInfo[ms_id][msStationPos][5], 
			MetroStationInfo[ms_id][msStationType]
		);
		MetroStationInfo[ms_id][msWaitTime] = (ms_wait_time -= 2);
		if (MetroStationInfo[ms_id][msWaitTime] <= 0) MetroStationInfo[ms_id][msWaitTime] = 30;
	}
}

ms_Timer() {
	format(STRING_GLOBAL, 10, "%d MP/H", RandomEx(117, 120));
	SetDynamicObjectMaterialText(MetroInteriorObjectID[2], 0, STRING_GLOBAL, 140, "Arial", 25, 1, 0xFFFF0000, 0x00000000, 1);
	SetDynamicObjectMaterialText(MetroInteriorObjectID[3], 0, STRING_GLOBAL, 140, "Arial", 25, 1, 0xFFFF0000, 0x00000000, 1);

	
	if ((++METRO_TABLES_UPDATE) >= 30) {
		format(STRING_GLOBAL, 10, "%02d:%02d", timestamp_hour, timestamp_minute);
		SetDynamicObjectMaterialText(MetroInteriorObjectID[0], 0, STRING_GLOBAL, 140, "Arial", 20, 1, 0xFFFF0000, 0x00000000, 1);
		SetDynamicObjectMaterialText(MetroInteriorObjectID[1], 0, STRING_GLOBAL, 140, "Arial", 20, 1, 0xFFFF0000, 0x00000000, 1);
		STRING_GLOBAL[0] = EOS;
		METRO_TABLES_UPDATE = 0;
	}
	if (++metroStationsTimer < METRO_STATIONS_TIMER) 
		return;
	for (new ms_id = 0; ms_id < MAX_METRO_STOP; ms_id++) {
		new virtualworld = random(1000);

		MetroStationInfo[ms_id][msWaitTime] -= METRO_STATIONS_TIMER;
		if (MetroStationInfo[ms_id][msWaitTime] <= 0) {
			foreach(new playerid: Player) {
				if (IsPlayerNPC(playerid) || !p_t_info[playerid][p_logged]) 
					continue;
				if ((GetPVarInt(playerid, "metro_next_id") - 1) == ms_id) 
					ms_SpawnPlayer(playerid, virtualworld);
			}
			MetroStationInfo[ms_id][msSpeed] = (120);
			MetroStationInfo[ms_id][msWaitTime] = (30);
		}
	}
	metroStationsTimer = 0;
}

ms_TimerPlayer(playerid) {
	if (!p_t_info[playerid][p_logged]) 
		return;
	if (GetPVarInt(playerid, "player_in_metro") && GetPlayerInterior(playerid) == METRO_INTERIOR_ID && GetPVarInt(playerid, "metro_route_time")) {
		SetPVarInt(playerid, "metro_route_time", GetPVarInt(playerid, "metro_route_time") - 1);

		if (GetPVarInt(playerid, "metro_route_time")) {
			format(STRING_GLOBAL, 28, "_~n~ ~n~~r~~h~~h~~h~%s", ConvertSecondsStr(GetPVarInt(playerid, "metro_route_time")));
			GameTextForPlayer(playerid, STRING_GLOBAL, 1000, 6), STRING_GLOBAL[0] = EOS;
		}
		else if (GetPVarInt(playerid, "metro_route_time") <= 0) ms_ExitPlayer(playerid);
	}
	else if (!GetPVarInt(playerid, "player_in_metro") && GetPVarInt(playerid, "metro_current_id")) {
		new ms_id = GetPVarInt(playerid, "metro_current_id") - 1;
		if (MetroStationInfo[ms_id][msWaitTime] - metroStationsTimer) {
			format(STRING_GLOBAL, 28, "_~n~ ~n~~r~~h~~h~~h~%s", ConvertSecondsStr(MetroStationInfo[ms_id][msWaitTime] - metroStationsTimer));
			GameTextForPlayer(playerid, STRING_GLOBAL, 1000, 6), STRING_GLOBAL[0] = EOS;
		}
	}
}

stock ms_SpawnPlayer(playerid, virtualworld) {
	if (GetPVarInt(playerid, "player_in_metro")) 
		return;

	if (PlayerInfo[playerid][money] < GetPVarInt(playerid, "metro_route_price")) {
		DeletePVar(playerid, "metro_next_id");
		DeletePVar(playerid, "player_in_metro");
		DeletePVar(playerid, "metro_current_id");
		DeletePVar(playerid, "metro_route_price");

		SendError(playerid, "Shoma pool kafi baraye safar nadarid.");
		return;
	}
	if (GetPVarInt(playerid, "metro_route_price")) {
		give_money(playerid, -GetPVarInt(playerid, "metro_route_price"));
	}
	SetPVarInt(playerid, "player_in_metro", 1);

	SetCameraBehindPlayer(playerid);
    set_pos(playerid,
    	1354.1033 + (RandomFloat(0.001, 0.5) - RandomFloat(0.001, 0.5)),
    	1571.1875 + (RandomFloat(0.001, 0.5) - RandomFloat(0.001, 0.5)), 
    	2872.3979, 0.0, METRO_INTERIOR_ID, virtualworld
    );
    freezePlayer(playerid, 2);
    SetPlayerFacingAngle(playerid, 90.0);
}

stock ms_StopInfo(playerid, next_ms_id) {
	if (!(0 <= next_ms_id < MAX_METRO_STOP)) 
		return;

	for (new ms_id = 0; ms_id < MAX_METRO_STOP; ms_id++) 
		if (IsPlayerInRangeOfPoint(playerid, METRO_STATION_DISTANCE, MetroStationInfo[ms_id][msPos][0], MetroStationInfo[ms_id][msPos][1], MetroStationInfo[ms_id][msPos][2])) {
		new 
			Float:ms_distance = GetDistanceBetweenPoints(
				MetroStationInfo[ms_id][msPos][0], MetroStationInfo[ms_id][msPos][1], MetroStationInfo[ms_id][msPos][2],
				MetroStationInfo[next_ms_id][msPos][0], MetroStationInfo[next_ms_id][msPos][1], MetroStationInfo[next_ms_id][msPos][2]
			)
		;
		SetPVarInt(playerid, "metro_route_time", (floatround(ms_distance, floatround_round) / (30)));
		if (PlayerInfo[playerid][level] <= 2) {
			DeletePVar(playerid, "metro_route_price");
			
			format(STRING_GLOBAL, 512, ""c_white"Shoma istgah badi ra entekhab kardid "c_pale_green"\"%s\""c_white".\n \n\
				"c_white"Zaman masir: %s\n\
				"c_white"Zaman vorood be istgah badi: %s\n\
				"c_white"Hazine: "c_gold"rayegan\n \n\
				"c_white"Dar istgah bemanid va montazer qatar bashid.",

				MetroStationInfo[next_ms_id][msName], ConvertSecondsStr(GetPVarInt(playerid, "metro_route_time")), 
				ConvertSecondsStr(MetroStationInfo[next_ms_id][msWaitTime])
			);
		}
		else {
			SetPVarInt(playerid, "metro_route_price", METRO_ROUTE_PRICE);

			format(STRING_GLOBAL, 512, ""c_white"Shoma istgah badi ra entekhab kardid "c_pale_green"\"%s\""c_white".\n \n\
				"c_white"Zaman masir: "c_pale_green"%s\n\
				"c_white"Zaman vorood be istgah badi: "c_pale_green"%s\n\
				"c_white"Hazine: "c_pale_green"$%d\n \n\
				"c_white"Dar istgah bemanid va montazer residan qatar bashid.",

				MetroStationInfo[next_ms_id][msName], ConvertSecondsStr(GetPVarInt(playerid, "metro_route_time")), 
				ConvertSecondsStr(MetroStationInfo[next_ms_id][msWaitTime]), GetPVarInt(playerid, "metro_route_price")
			);
		}
		show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""c_pale_green"Metro station", STRING_GLOBAL, "close", "");

		SendInfo(playerid, "Shoma istgah badi \"%s\" ra entekhab kardid, montazer residan qatar bashid.", MetroStationInfo[next_ms_id][msName]);
        STRING_GLOBAL[0] = EOS;

		SetPVarInt(playerid, "metro_current_id", next_ms_id + 1);
		SetPVarInt(playerid, "metro_next_id", next_ms_id + 1);
		break;
	}
}
stock ms_SelectStop(playerid) {
	if (GetPVarInt(playerid, "metro_current_id")) {
		if (GetPVarInt(playerid, "metro_info_flood") > timestamp) 
			return false;
		SetPVarInt(playerid, "metro_info_flood", timestamp + 5);

		format(STRING_GLOBAL, (MAX_METRO_STOP_NAME + 110), 
			"Shoma ghablan istgah "c_pale_green"%s"c_white" ra entekhab kardid. Zaman entezar baraye saf khod: "c_pale_green"%s"c_white".", 
			MetroStationInfo[GetPVarInt(playerid, "metro_next_id") - 1][msName], 
			ConvertSecondsStr(MetroStationInfo[GetPVarInt(playerid, "metro_next_id") - 1][msWaitTime])
		);
		SendClientMessage(playerid, COLOR_WHITE, STRING_GLOBAL);
		return STRING_GLOBAL[0] = '\0';
	}
	new metro_current_id = (-1), idx = 0;

	for (new ms_id = 0; ms_id < MAX_METRO_STOP; ms_id++) {
		if (IsPlayerInDynamicArea(playerid, MetroStationInfo[ms_id][msArea])) {
			metro_current_id = ms_id;
			break;
		}
	}
	STRING_GLOBAL[0] = '\0';

	for (new ms_id = 0, ms_string[MAX_METRO_STOP_NAME + 24]; ms_id < MAX_METRO_STOP; ms_id++) if (ms_id != metro_current_id) {
		format(ms_string, (MAX_METRO_STOP_NAME + 24), ""c_pale_green"%i. "c_white"%s\n", idx + 1, MetroStationInfo[ms_id][msName]);
		strcat(STRING_GLOBAL, ms_string), ms_string[0] = EOS;
		MetroDialogItemID[playerid][idx++] = ms_id; 
	}
	if (!strlen(STRING_GLOBAL)) {
		format(STRING_GLOBAL, 8, "Khaali.");
		MetroDialogItemID[playerid][idx] = (-1);
	}
	show_dialog(playerid, d_metro_stop, DIALOG_STYLE_LIST, ""c_pale_green"Select a station", STRING_GLOBAL, "Choose", "Cancel"), STRING_GLOBAL[0] = '\0';

	return true;
}
stock ms_ExitPlayer(playerid) { 
	if (!GetPVarInt(playerid, "player_in_metro")) 
		return false;

	new ms_id = (GetPVarInt(playerid, "metro_next_id") - 1);
	set_pos(playerid,
		MetroStationInfo[ms_id][msPos][0] + (RandomFloat(0.001, 0.5) - RandomFloat(0.001, 0.5)), 
		MetroStationInfo[ms_id][msPos][1] + (RandomFloat(0.001, 0.5) - RandomFloat(0.001, 0.5)), 
		MetroStationInfo[ms_id][msPos][2], 0.0, 0, 0
	);

	freezePlayer(playerid, 2);
	SetPlayerFacingAngle(playerid, MetroStationInfo[ms_id][msPos][3] + 180.0);
	SetCameraBehindPlayer(playerid);

	DeletePVar(playerid, "metro_next_id");
	DeletePVar(playerid, "player_in_metro");
	DeletePVar(playerid, "metro_current_id");
	DeletePVar(playerid, "metro_route_price");

	return true;
}
stock ms_OnPlayerDisconnect(playerid) {
	ms_OnPlayerDeath(playerid);
}
stock ms_OnPlayerDeath(playerid) {
	DeletePVar(playerid, "player_in_metro");
	DeletePVar(playerid, "metro_current_id");
	DeletePVar(playerid, "metro_next_id");
}
stock ms_OnPlayerLeaveDynArea(playerid, areaid) {
	if (!GetPVarInt(playerid, "player_in_metro") && areaid >= MetroStationInfo[0][msArea] && areaid <= MetroStationInfo[MAX_METRO_STOP - 1][msArea]) {
		if (GetPVarInt(playerid, "metro_current_id")) 
			SendError(playerid, "Shoma az istgah metro door shode'id, lotfan istgah khod ra dobare entekhab konid.");
		DeletePVar(playerid, "metro_current_id"), DeletePVar(playerid, "metro_next_id"), DeletePVar(playerid, "metro_route_time");
	
		return true;
	}
	return false;
}
stock ConvertSecondsStr(seconds) {
	new stringTo[15], result[4];
	result[0] = floatround(seconds / (3600 * 24));
	result[1] = floatround(seconds / 3600);
	result[2] = floatround((seconds / 60) - (result[1] * 60));
	result[3] = floatround(seconds - ((result[1] * 3600) + (result[2] * 60)));

	switch (result[0]) {
		case 0: {
			switch (result[1]) {
				case 0: format(stringTo, 16, "%02d:%02d", result[2], result[3]);
				default: format(stringTo, 16, "%d:%02d:%02d", result[1], result[2], result[3]);
			}
		}
	}
	return stringTo;
}
CMD:tpmetro(playerid) {
	if (PlayerInfo[playerid][admin] < 3) return true;
	STRING_GLOBAL[0] = '\0';
	new idx;
	for (new ms_id = 0, ms_string[MAX_METRO_STOP_NAME + 24]; ms_id < MAX_METRO_STOP; ms_id++) {
		format(ms_string, (MAX_METRO_STOP_NAME + 24), ""c_pale_green"%i. "c_white"%s\n", ms_id + 1, MetroStationInfo[ms_id][msName]);
		strcat(STRING_GLOBAL, ms_string), ms_string[0] = EOS;
		MetroDialogItemID[playerid][idx++] = ms_id; 
	}
	if (!strlen(STRING_GLOBAL)) {
		format(STRING_GLOBAL, 8, "Empty");
		MetroDialogItemID[playerid][idx] = (-1);
	}
	show_dialog(playerid, d_metro_list, DIALOG_STYLE_LIST, ""c_pale_green"Select a station", STRING_GLOBAL, "Choose", "Cancel"), STRING_GLOBAL[0] = '\0';
	return 1;
}
ms_CreateAttachedDynamicObject(objectid, modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD) {
	new Float:new_object_pos[3], Float:new_object_rot[3], object_id;
	AttachObjectToObjectEx(objectid, 
		x, y, z - 100.0, rx, ry, rz,
		new_object_pos[0], new_object_pos[1], new_object_pos[2], 
		new_object_rot[0], new_object_rot[1], new_object_rot[2]
	);
	object_id = CreateDynamicObject(modelid, 
		new_object_pos[0], new_object_pos[1], new_object_pos[2], 
		new_object_rot[0], new_object_rot[1], new_object_rot[2], 
		worldid, interiorid, playerid, streamdistance, drawdistance
	);
	return object_id;
}
stock ms_CreateStationObject(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, type) {
	new 
		object_id = 0, objectid[99], 
		Float:SUBWAY_DRAW_DISTANCE = 170.0
	;
	objectid[object_id] = CreateDynamicObject(18763, x, y, z, rx, ry, rz, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);

	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, -2.989994, 0.000762, 100.000938, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	SetDynamicObjectMaterial(objectid[object_id], 1, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	SetDynamicObjectMaterial(objectid[object_id], 2, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, -5.980359, 0.000761, 100.001007, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, 3.000482, 0.000762, 100.000839, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.338058, -0.175018, 105.225440, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.338050, 0.225372, 105.425453, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "ab_loadbayMark01", 0xFFF0F8FF);
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.328037, 0.205352, 105.425445, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "ab_loadbayMark01", 0xFFF0F8FF);
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.328037, 0.235382, 105.425445, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "ab_loadbayMark01", 0xFFF0F8FF);
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19696, -2.479693, -0.203948, 103.055519, 90.0, -89.853622, -90.146415, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 7978, "vgssairport", "airportwindow02_128", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.318031, 0.225372, 105.425453, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "ab_loadbayMark01", 0xFFF0F8FF);
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.318040, -0.175018, 105.225456, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.328046, -0.165009, 105.225448, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18880, -7.328045, -0.185029, 105.225440, 0.0, 179.999038, -179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 2, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, -5.971569, -0.019257, 100.010993, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	SetDynamicObjectMaterial(objectid[object_id], 1, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	SetDynamicObjectMaterial(objectid[object_id], 2, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, -2.982068, -0.019257, 100.010955, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	SetDynamicObjectMaterial(objectid[object_id], 1, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	SetDynamicObjectMaterial(objectid[object_id], 2, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, 0.018545, -0.019257, 100.010894, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	SetDynamicObjectMaterial(objectid[object_id], 1, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	SetDynamicObjectMaterial(objectid[object_id], 2, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, 2.990462, -0.019257, 100.010856, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	SetDynamicObjectMaterial(objectid[object_id], 1, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	SetDynamicObjectMaterial(objectid[object_id], 2, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, 3.010485, -0.029266, 100.000846, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, 0.011101, -0.029266, 100.000900, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, -2.978646, -0.029266, 100.000961, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, -5.989755, -0.029265, 100.000999, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -5.095847, 1.192168, 105.989448, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "SUBWA", 130, "Arial", 150, 1, 0xFFFFFFFF, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -6.436913, 1.192168, 105.989479, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "Y", 130, "Arial", 150, 1, 0xFFFFFFFF, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -6.456936, 1.182159, 105.979476, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "Y", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -6.416895, 1.182159, 105.979461, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "Y", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -6.416900, 1.182159, 106.009475, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "Y", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -6.446932, 1.182159, 106.009475, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "Y", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -5.115867, 1.182159, 105.989456, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "SUBWA", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -5.075828, 1.182159, 105.989448, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "SUBWA", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -5.075827, 1.182160, 105.969444, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "SUBWA", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -5.115867, 1.182159, 105.969444, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "SUBWA", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -5.115869, 1.182159, 106.019454, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "SUBWA", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -5.085842, 1.182159, 106.019439, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "SUBWA", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, 0.426122, 1.192167, 106.019355, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "MIHAN", 130, "Arial", 150, 1, 0xFF0DF690, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -1.004665, 1.192168, 106.019371, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "RP", 130, "Arial", 150, 1, 0xFF0DF690, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, 0.416107, 1.182160, 105.999343, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "MIHAN", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, 0.436126, 1.182158, 105.999359, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "MIHAN", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, 0.436128, 1.182159, 106.039360, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "MIHAN", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, 0.416109, 1.182158, 106.039352, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "MIHAN", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -1.014673, 1.182159, 106.049369, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "RP", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -1.014672, 1.182159, 105.999382, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "RP", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -0.994652, 1.182160, 105.999366, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "RP", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -2.585227, 1.172149, 106.269416, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "u", 130, "Webdings", 199, 0, 0xFFff0000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -2.605240, 1.162138, 106.289421, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "u", 130, "Webdings", 199, 0, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -2.565200, 1.162139, 106.289413, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "u", 130, "Webdings", 199, 0, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -2.575220, 1.162139, 106.239410, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "u", 130, "Webdings", 199, 0, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, 1.338465, 1.177641, 105.695434, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, 1.338470, 1.177641, 105.595436, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -0.992586, 1.177642, 105.695472, 0.0, 0.000962, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -0.992583, 1.177642, 105.595466, 0.0, 0.000962, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -3.242953, 1.177642, 105.695503, 0.0, 0.000967, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -3.242952, 1.177642, 105.595512, 0.0, 0.000967, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -5.554604, 1.177641, 105.695556, 0.0, 0.000977, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -5.554599, 1.177641, 105.595535, 0.0, 0.000977, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -6.295328, 1.177642, 105.695571, 0.0, 0.000984, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19834, -6.295323, 1.177642, 105.595558, 0.0, 0.000984, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, 2.003780, -0.820893, 100.489318, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, 1.013913, -0.820892, 100.489334, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, 0.024040, -0.820892, 100.489356, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -0.975716, -0.820892, 100.489379, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -1.215938, -0.810882, 100.479370, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -3.966427, -0.810882, 100.479415, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -4.965823, -0.810882, 100.479438, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -5.956057, -0.810882, 100.479461, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -6.826909, -0.800872, 100.469467, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -6.816891, -0.820892, 100.479484, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -5.956298, -0.820892, 100.489463, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -4.955689, -0.820892, 100.489440, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -3.974738, -0.820892, 100.489425, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -1.214231, -0.830902, 100.499374, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, -0.224366, -0.830902, 100.499359, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, 0.765990, -0.830902, 100.499343, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, 1.766844, -0.830902, 100.499328, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18762, 1.997064, -0.830902, 100.509315, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFFFFFFFF);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1444, -2.656689, -0.662567, 103.314544, 0.0, 0.000955, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 2430, "cj_burg_sign", "CJ_BS_MENU2", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 2.596987, -0.024384, 103.989135, 0.0, 0.000977, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 4.127871, 1.496612, 103.989112, 0.000976, -0.0, 89.999748, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 4.127872, -1.566252, 103.989105, 0.000976, -0.0, 89.999748, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 5.649474, -0.024384, 103.989089, 0.0, 0.000977, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 18763, 4.118690, 0.000761, 103.280830, 0.0, 0.000977, -0.000055, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 14577, "casinovault01", "vaultFloor", 0xFF808080);
	SetDynamicObjectMaterial(objectid[object_id], 1, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	SetDynamicObjectMaterial(objectid[object_id], 2, 12978, "ce_payspray", "sf_spray_floor2", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19483, -0.994652, 1.182159, 106.049369, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterialText(objectid[object_id], 0, "Y", 130, "Arial", 150, 1, 0xFF000000, 0x00000000, 1);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 4.127805, 1.496611, 100.509109, 0.000976, -0.0, 89.999748, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 5.668572, -0.033782, 100.509086, 0.000031, -0.000954, 179.999908, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
	switch (type) { 
		case 1: {
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 5.639430, -2.268769, 101.894035, 24.999990, 0.001073, -0.000487, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 5.639402, -5.186614, 100.555564, 24.999990, 0.001073, -0.000487, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19740, 4.377595, -6.981046, 102.401885, -0.000946, 205.0, -89.999961, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0xFFFFFFFF);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 3.118529, -5.186612, 100.555595, 24.999990, 0.001073, -0.000487, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 3.118551, -2.295989, 101.903762, 24.999990, 0.001073, -0.000487, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
		}
		case 2: {
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 5.639430, -0.765879, 102.077026, 49.500003, 0.001386, -0.000685, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 5.639402, -2.865950, 99.649063, 49.500003, 0.001386, -0.000685, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19740, 4.377595, -5.264471, 100.585006, -0.000845, 229.500015, -89.999565, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0xFFFFFFFF);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 3.118529, -2.865961, 99.649093, 49.500003, 0.001386, -0.000685, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
			object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 19354, 3.118551, -0.794682, 102.074592, 49.500003, 0.001386, -0.000685, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
			SetDynamicObjectMaterial(objectid[object_id], 0, 10763, "airport1_sfse", "ws_airportdoors1", 0x00000000);
		}
	}
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 11706, -7.004246, 1.036773, 102.384811, 0.000955, 0.000001, 89.999885, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, -6.661215, -0.832612, 102.511009, 0.000012, -0.000954, -179.999984, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, -6.070889, -0.832611, 102.511001, 0.000012, -0.000954, -179.999984, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, -5.480308, -0.832612, 102.511001, 0.000012, -0.000954, -179.999984, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, -4.880091, -0.832611, 102.510993, 0.000012, -0.000954, -179.999984, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, -4.290370, -0.832611, 102.510978, 0.000012, -0.000954, -179.999984, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, -0.848718, -0.832612, 102.510917, 0.0, -0.000962, 179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, -0.258384, -0.832611, 102.510910, 0.0, -0.000962, 179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, 0.332190, -0.832611, 102.510887, 0.0, -0.000962, 179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, 0.932407, -0.832612, 102.510887, 0.0, -0.000962, 179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
	object_id++; objectid[object_id] = ms_CreateAttachedDynamicObject(objectid[0], 1715, 1.522127, -0.832611, 102.510879, 0.0, -0.000962, 179.999923, 0, 0, -1, SUBWAY_DRAW_DISTANCE, SUBWAY_DRAW_DISTANCE); 
}