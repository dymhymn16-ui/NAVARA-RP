
#define MODE_SKATE (0)        // 0 - medium speed | 1 - fast speed
#define TYPE_SKATE (0)        // 0 - the skate is placed on the right arm | 1 - the skate is placed in the back
#define INDEX_SKATE (0)       //is the slot that used SetPlayerAttachedObject
enum skate{
	bool:sActive,
	sSkate,
};
new InfoSkate[MAX_PLAYERS][skate];

// ------------------------------------------------------------------

static NonRpPremiumVehicles[] = {406, 425, 432, 435, 449, 450, 476, 520, 537, 538, 553, 558, 569, 570, 577, 584, 590, 591, 592, 594, 606, 607, 608, 610, 611};

static s_PlayerWaitTime[MAX_PLAYERS];

new griderObjectFire[MAX_PLAYERS][3];
new bool:PlayerFlamingHandEffect[MAX_PLAYERS];



#define RAINBOW_COLOR_COUNT 7 // Number of rainbow colors
#define RAINBOW_INTERVAL 500 // Interval for changing colors in milliseconds

// Array of rainbow colors using Color IDs
new rainbowColors[RAINBOW_COLOR_COUNT] = {
    1,  // Red
    35, // Orange
    89, // Yellow
    37, // Green
    54, // Blue
    70, // Indigo
    95  // Violet
};

// Array to store the original colors of vehicles (2 colors for each vehicle)
new originalColors[MAX_VEHICLES][2];


new bool:isPlayerSurfing[MAX_PLAYERS];  // Stores the surfing status for each player
new Float:playerOffset[MAX_PLAYERS][3]; // Stores the player's offset relative to the vehicle
new attachedVehicle[MAX_PLAYERS];       // Stores the vehicle the player is surfing on

#define RAINBOW_INTERVAL 500 // Interval for changing lights in milliseconds
new bool:isPlayerLightOn[MAX_PLAYERS]; // Store the status of PLight for each player

// ------------------------------------------------------------------

CheckPlayerPremiumTime(playerid) {
	if(PlayerInfo[playerid][premium] > 0) {
		if(timestamp > PlayerInfo[playerid][premium_time]) {
			new query_string[100];
			format(query_string, sizeof(query_string), "UPDATE `users` SET `u_premium`= 0, `u_premium_time`= 0 WHERE `u_id` = '%d' LIMIT 1", PlayerInfo[playerid][id]);
			mysql_query(sql_connection, query_string);

			SendClientMessage(playerid, col_white, ""c_green"* "c_white"Time "c_server"Premium "c_white"shoma tamam shod.");

			PlayerInfo[playerid][premium] = 0;
			PlayerInfo[playerid][premium_time] = 0;
			UpdatePlayerName(playerid);
		}
	}
}

// ------------------------------------------------------------------

SetPlayerPremiumTag(playerid) {
	if(PlayerInfo[playerid][premium_text] == Text3D:INVALID_3DTEXT_ID) {
		PlayerInfo[playerid][premium_text] = CreateDynamic3DTextLabel("{FFEC00}Premium", 0xFFFFFFFF, 0.0, 0.0, 0.5, 20.0, playerid, INVALID_VEHICLE_ID, 1);
	}
}

// ------------------------------------------------------------------

DeletePlayerPremiumTag(playerid) {
	if(PlayerInfo[playerid][premium_text] != Text3D:INVALID_3DTEXT_ID) {
		DestroyDynamic3DTextLabel(PlayerInfo[playerid][premium_text]);
		PlayerInfo[playerid][premium_text] = Text3D:INVALID_3DTEXT_ID;
	}
}

// ------------------------------------------------------------------

//p. give premium for player
cmd:setpremium(playerid, params[]) {
	if(check_admin_rank(playerid , 8)) return 1;

	extract params -> new player:targetid, premiumDays; else return SendInfo(playerid, "Enter: /setpremium [Player id] [Days]");
	
	if(!IsPlayerConnected(targetid)) return SendError(playerid, "Player not found.");
    if(!p_t_info[targetid][p_logged]) return SendError(playerid, "Player is not logged in.");
    if(PlayerInfo[targetid][premium]) return SendError(playerid, "Player is already premium.");
    if(!(1 <= premiumDays <= 365)) return SendError(playerid, "Days should be between 1 to 365.");

	PlayerInfo[targetid][premium_time] = timestamp + (60 * 60 * 24 * premiumDays);
    PlayerInfo[targetid][premium] = 1;
    Iter_Add(premium_players, targetid);
    SetPlayerPremiumTag(targetid);
    UpdatePlayerName(targetid);

    new query_string[128];

	format(query_string, sizeof(query_string), ""c_server"* S.INFO:"c_grey" admin %s[%d] shoma ra premium kard. (%d Rooz)", PlayerInfo[playerid][name], playerid, premiumDays);
	SendClientMessage(targetid, col_gray, query_string);
	GameTextForPlayer(targetid, "/phelp", 3000, 3);

	format(query_string, sizeof(query_string), ""c_server"* S.INFO:"c_grey" shoma bazikon %s[%d] ra premium kardid. (%d Rooz)", PlayerInfo[targetid][name], targetid, premiumDays);
	SendClientMessage(playerid, col_gray, query_string);
	
	format(query_string, sizeof(query_string), 
		"UPDATE `users` SET `u_premium`=%d,`u_premium_time`='%d' WHERE `u_id`='%d' LIMIT 1", 
		PlayerInfo[targetid][premium], 
		PlayerInfo[targetid][premium_time], 
		PlayerInfo[targetid][id]);
	mysql_query(sql_connection, query_string);
	return 1;
}

// ------------------------------------------------------------------

//p take premium player
cmd:takepremium(playerid, params[]) {
	if(check_admin_rank(playerid , 8)) return 1;

	extract params -> new player:targetid, string:takeReason[32]; else return SendInfo(playerid, "Enter: /takepremium [Player id] [Reason]");
	
	if(!IsPlayerConnected(targetid)) return SendError(playerid, "Player not found.");
    if(!p_t_info[targetid][p_logged]) return SendError(playerid, "Player is not logged in.");
    if(PlyayerIsGang && !PlayerInfo[targetid][premium]) return SendError(playerid, "Player is not premium.");

	PlayerInfo[targetid][premium_time] = 0;
    PlayerInfo[targetid][premium] = 0;
    Iter_Remove(premium_players, targetid);
    DeletePlayerPremiumTag(targetid);
    UpdatePlayerName(targetid);

    new query_string[128];

	format(query_string, sizeof(query_string), ""c_server"* S.INFO:"c_grey" admin %s[%d] premium shoma ra take kard. (Dalil: %s)", PlayerInfo[playerid][name], playerid, takeReason);
	SendClientMessage(targetid, col_gray, query_string);

	format(query_string, sizeof(query_string), ""c_server"* S.INFO:"c_grey" shoma premium bazikon %s[%d] ra take kardid. (Dalil: %s)", PlayerInfo[targetid][name], targetid, takeReason);
	SendClientMessage(playerid, col_gray, query_string);
	
	format(query_string, sizeof(query_string), 
		"UPDATE `users` SET `u_premium`=%d,`u_premium_time`='%d' WHERE `u_id`='%d' LIMIT 1", 
		PlayerInfo[targetid][premium], 
		PlayerInfo[targetid][premium_time], 
		PlayerInfo[targetid][id]);
	mysql_query(sql_connection, query_string);
	return 1;
}

//p. premuim command's
cmd:phelp(playerid,params[]) 
{

	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	show_dialog(playerid, d_mm_cmd_list, DIALOG_STYLE_MSGBOX, "{FFDC33}Premium "c_white"Commands",
	""c_grey"/pgoto [id player] "c_white" - teleport be yek player.\n\
	"c_grey"/pjp "c_white" - jetpack.\n\
	"c_grey"/pveh [id vehicle] [color 1] [color 2] "c_white" - spawn kardan mashin.\n\
	"c_grey"/pdv "c_white"- pak kardan mashin spawn shodeh.\n\
	"c_grey"/pskin [id skin] "c_white" - avaz kardan skin khod.\n\
	"c_grey"/pfixcar "c_white" - tamir mashin khod.\n\
	"c_grey"/pflipcar "c_white" - flip kardan mashin.\n\
	"c_grey"/pweather [id] "c_white" - avaz kardan hava bray khod.\n\
	"c_grey"/php [id player] "c_white" - por kardan khon khod.\n\
	"c_grey"/parmour [id player] "c_white" - por kardan jeligeh zed gololeh khod.\n\
	"c_grey"/psurf "c_white" - sabet mandan roy mashin darhal harkat.\n\
	"c_grey"/psettime "c_white" - tanzim kardan time baraye khod.\n\
	"c_grey"/pautonos "c_white" - nitro khodkar.\n\
	"c_grey"/flaminghand "c_white" - roshan kardan gabliyat dast atashin.\n\
	"c_grey"/ghostrider "c_white" - roshan kardan gabliyat roh savar.\n\
	"c_grey"/vjump "c_white" - paresh mashin ba bogh.\n\
	"c_grey"/rainbow "c_white" - taghir rangh rangin kaman vasile naghliye.\n\
	"c_grey"/plight "c_white" - raghs nour vasile naghliye.\n\
	"c_grey"/pskate "c_white" - skate savari.\n\
	"c_grey"/snow "c_white" - mode barf omadan.", "bastan", "");

	return 1;
}

//p. spawned a car
cmd:pveh(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(!checkPlayerAllowed(playerid)) return 1;

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	extract params -> new vehicle_id, color_1, color_2; else return SendInfo(playerid, "Enter: /pveh [vehicle id] [color 1] [color 2]");
	if(!(400 < vehicle_id < 611) || !(0 <= color_1 <= 255) || !(0 <= color_2 <= 255)) return SendInfo(playerid, "Enter: /pveh [vehicle id] [color 1] [color 2]");

	for(new i = 0; i < sizeof NonRpPremiumVehicles; i++) {
		if(vehicle_id == NonRpPremiumVehicles[i]) {
			SendClientMessage(playerid, col_white, !"In Mashin Ra Nemitavanid Spawn Konid.");
			return 1;
		}
	}

	if(GetPVarInt(playerid, !"premium_vehicle")) return SendClientMessage(playerid, col_white, !"Shoma Yek Mashin Spawn Darid. Baraye Hazf /pdv Bezanid.");

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z, Float:pl_pos_C;
	GetPlayerPos(playerid, pl_pos_X, pl_pos_Y, pl_pos_Z);
	GetPlayerFacingAngle(playerid, pl_pos_C);

	new prem_veh = CreateVehicle(vehicle_id, pl_pos_X, pl_pos_Y, pl_pos_Z, pl_pos_C, color_1, color_2, -1);
	SetPVarInt(playerid, !"premium_vehicle", prem_veh);

	veh_info[prem_veh -1][v_fuel] = 100.0;

	LinkVehicleToInterior(prem_veh, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(prem_veh, GetPlayerVirtualWorld(playerid));

	PutPlayerInVehicle(playerid, prem_veh, 0);
	SetPlayerArmedWeapon(playerid, 0);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] Created Vehicle ID: %d | Model: %s", PlayerInfo[playerid][name], playerid, prem_veh, vehicle_name[vehicle_id-400]);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return true;
}

//p. remove the spawned car
cmd:pdv(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	new veh_id = GetPVarInt(playerid, !"premium_vehicle");
	if(!veh_id) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Hich Mashini Spawn Nakardid");

	DestroyVehicle(veh_id);

	SendClientMessage(playerid, col_gray, "Car deleted");

	return DeletePVar(playerid, !"premium_vehicle");
}

//p. spawn jetpack
cmd:pjp(playerid) 
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(p_t_info[playerid][gomp]) return SendError(playerid, "Shoma Dar Event Hastid!");
	if(IsPlayerInFalloutGame(playerid)) return SendError(playerid, "Shoma Dar Event Hastid!");
	if(ReturnPlayerInCounterStrike(playerid) != 0) return SendError(playerid, "Shoma Dar Event Hastid!");

	if(isPlayerInJail(playerid)) return SendError(playerid, "Shoma Dar Zendan Hastid!");

	if(PlayerInfo[playerid][wanted] > 0) {
		SendClientMessage(playerid, col_gray, "Shoma Wanted Darid.");
		return 1;
	}

	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
	{
	    SendClientMessage(playerid, COLOR_GREY, "Shoma Jetpack Darid. Baraye Az Bin Bordan {FFFFFF}/jpoff {999999}Bezanid.");
		return 1;
	}

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	GameTextForPlayer(playerid, "~y~~h~JETPACK", 3, 2500);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] spawned jetpack", PlayerInfo[playerid][name], playerid);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

cmd:jpoff(playerid) 
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium] && !PlayerInfo[playerid][helper]) {
		SendError(playerid, "Shoma Premium Ya Helper Nistid.");
		return 1;
	}

	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK)
	{
	    SendClientMessage(playerid, COLOR_GREY, "Shoma Jetpack Nadarid. Baraye Gerftan {FFFFFF}/pjp {999999}Bezanid.");
		return 1;
	}

	//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE); //Noise Bug

	ApplyAnimation(playerid, "DEALER", "SHOP_PAY", 4.1, 0, 0, 0, 0, 30, 1);
	return 1;
}

// ------------------------------------------------------------------

cmd:pgoto(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(!checkPlayerAllowed(playerid)) return 1;

	if(PlayerInfo[playerid][wanted] > 0) return SendError(playerid, "Shoma wanted darid.");

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /pgoto [id Bazikon]");
	
	if(!IsPlayerConnected(targetid) || targetid == playerid) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");
	if(!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Spawn Nashode Ast.");

	if(PlayerInfo[targetid][admin] > 0) return SendError(playerid, "Shoma nmitavanid be admin ha darkhast goto bedid.");

	if(playerid != targetid) if(!checkTargetAllowed(targetid)) return 1;

    if(IsPlayerInRangeOfPoint(playerid, 5.0, p_t_info[targetid][p_pos][0], p_t_info[targetid][p_pos][1], p_t_info[targetid][p_pos][2])) return SendError(playerid, "Shoma Kenar In Bazikon Hastid.");

	SetPVarInt(targetid, !"premium_teleport", 1);
	SetPVarInt(targetid, !"premium_teleport_target", playerid);

	new string[200];
	SendInfo(playerid ,"Darkhast shoma be player %s[%d] ersal shod.", PlayerInfo[targetid][name], targetid);

	format(string, sizeof(string),  ""c_server"* Premium:"c_grey" %s[%d] be shoma darkhast teleport dad. ghabol kardan : "c_server"/tpaccept", PlayerInfo[playerid][name],playerid);
	SendClientMessage(targetid, col_gray, string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

cmd:tpaccept(playerid)
{
	new targetid;

	if(GetPVarInt(playerid, !"premium_teleport")) {
		targetid = GetPVarInt(playerid, !"premium_teleport_target");
		DeletePVar(playerid, "premium_teleport");

		if(!checkPlayerAllowed(playerid)) return 1;
		if(playerid != targetid) if(!checkTargetAllowed(targetid)) return 1;

		new string[64];
		format(string, sizeof(string), "be player %s teleport kard", Name(playerid));
		me_action(targetid, string);

		new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z;
		GetPlayerPos(playerid, pl_pos_X, pl_pos_Y, pl_pos_Z);

		if(GetPlayerState(targetid) == PLAYER_STATE_ONFOOT || GetPlayerInterior(playerid) != 0) {
			set_pos(targetid, pl_pos_X + 2.0, pl_pos_Y, pl_pos_Z, 0.0, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
		} else {
			new carid = GetPlayerVehicleID(targetid);
			SetVehiclePos(carid, pl_pos_X + 2.0, pl_pos_Y, pl_pos_Z);
			SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(carid, GetPlayerInterior(playerid));
		}

		if(p_t_info[playerid][house] != -1) p_t_info[targetid][house] = p_t_info[playerid][house];
		if(p_t_info[playerid][business] != -1) p_t_info[targetid][business] = p_t_info[playerid][business];

		new text_string[120];
		format(text_string, sizeof(text_string), ""c_server"* Premium: "c_grey"%s[%d] teleporting to the player %s[%d]", PlayerInfo[targetid][name], targetid, PlayerInfo[playerid][name], playerid);
		foreach(new i: premium_players) SendClientMessage(i, col_gray, text_string);
		return 1;
	}

	return 1;
}

//p. change skin
cmd:pskin(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(!checkPlayerAllowed(playerid)) return 1;

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	new skinId;
	if(sscanf(params, "d", skinId)) return SendInfo(playerid, "Enter: /pskin [skin id]");
	if(skinId > 311 || skinId < 1) return SendError(playerid, "Invalid skin number.");
	if(GetPlayerSkin(playerid) == skinId) return SendError(playerid, "Shoma Hamin Skin Ra Darid.");

	SetPlayerSkin(playerid, skinId);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] changed skin to %d", PlayerInfo[playerid][name], playerid, skinId);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 5;
	return 1;
}

// ------------------------------------------------------------------

cmd:pfixcar(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(!checkPlayerAllowed(playerid)) return 1;

	if(!IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Shoma bayad savar mashin bashid.");

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	new vehicleid = GetPlayerVehicleID(playerid);

	SetVehicleHealth(vehicleid, 1000.0);
	RepairVehicle(vehicleid);

	veh_info[vehicleid -1][v_health] = 1000.0;

	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] fixed car", PlayerInfo[playerid][name], playerid);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

//p. flipcared a car
cmd:pflipcar(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(!checkPlayerAllowed(playerid)) return 1;

	if(!IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Shoma bayad savar mashin bashid.");

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	new vehicleid = GetPlayerVehicleID(playerid);

    new Float:zRot;
    GetVehicleZAngle(vehicleid, zRot);
    SetVehicleZAngle(vehicleid, zRot);

	PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] flipped car", PlayerInfo[playerid][name], playerid);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

//p. set weather for player
cmd:pweather(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	new weatherid;
	if(sscanf(params, "d", weatherid)) return SendInfo(playerid, "Enter: /pweather [0 - 45]");
	if(!(0 <= weatherid <= 45)) return SendInfo(playerid, "Enter: /pweather [0 - 45]");

	SetPlayerWeather(playerid, weatherid);
	return 1;
}

//p. set time for player
cmd:psettime(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	new timeset;
	if(sscanf(params, "d", timeset)) return SendInfo(playerid, "Enter: /psettime [0 - 24]");
	if(!(0 <= timeset <= 24)) return SendInfo(playerid, "Enter: /psettime [0 - 24]");

	SetPlayerTime(playerid, timeset, 0);
	return 1;
}

//p. give hp for a player
cmd:php(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /php [id Bazikon]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");

	if(!checkPlayerAllowed(playerid)) return 1;

	if(playerid != targetid) if(!checkTargetAllowed(targetid)) return 1;

    set_health(targetid, 100.0);

    new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* S.INFO:"c_grey" Premium %s[%d] healed you", PlayerInfo[playerid][name], playerid);
	SendClientMessage(targetid, col_white, text_string);

	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] healed player %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

//p. give armour for a player
cmd:parmour(playerid, params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	extract params -> new player:targetid; else return SendInfo(playerid, "Enter: /parmour [id Bazikon]");
	if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");

	if(!checkPlayerAllowed(playerid)) return 1;

	if(playerid != targetid) if(!checkTargetAllowed(targetid)) return 1;

    set_armour(targetid, 100.0);

    new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* S.INFO:"c_grey" Premium %s[%d] give you armour", PlayerInfo[playerid][name], playerid);
	SendClientMessage(targetid, col_white, text_string);

	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] give armour to %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

//p. ghost rider
cmd:ghostrider(playerid, params[]) {
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(!checkPlayerAllowed(playerid)) return 1;

    if(!IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Shoma batad savar vasile naghliye bashid.");

    new vehicleid = GetPlayerVehicleID(playerid);

	if(griderObjectFire[playerid][0]) {
		DestroyDynamicObject(griderObjectFire[playerid][0]);
		DestroyDynamicObject(griderObjectFire[playerid][1]);
		DestroyDynamicObject(griderObjectFire[playerid][2]);
		griderObjectFire[playerid][0] = 0;
		griderObjectFire[playerid][1] = 0;
		griderObjectFire[playerid][2] = 0;
		return 1;
	}

	if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");
 
	griderObjectFire[playerid][0] = CreateDynamicObject(18689, 0.0, 0.0, 0.0, 0.0, 0.0, 256.0);

	griderObjectFire[playerid][1] = CreateDynamicObject(18689, 0.0, 0.0, 0.0, 0.0, 0.0, 256.0);

	griderObjectFire[playerid][2] = CreateDynamicObject(18693, 0.0, 0.0, 0.0, 0.0, 0.0, 256.0);

	AttachDynamicObjectToVehicle(griderObjectFire[playerid][0], vehicleid, 0.0, 0.6, -1.7, 0.0, 0.0, 0.0);

	AttachDynamicObjectToVehicle(griderObjectFire[playerid][1], vehicleid, 0.0, -1.4, -1.7, 0.0, 0.0, 0.0);

	AttachDynamicObjectToPlayer(griderObjectFire[playerid][2], playerid, 0.0, -0.01, -0.9, 0.0, 0.0, 0.0);

	ChangeVehicleColor(vehicleid, 0, 0);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] used ghost rider mode", PlayerInfo[playerid][name], playerid);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

//p. flaming hand effects
cmd:flaminghand(playerid,params[])
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(!PlayerFlamingHandEffect[playerid])
	{
		if(s_PlayerWaitTime[playerid] > timestamp) return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

		SetPlayerAttachedObject(playerid, 7, 18693, 6, 0.068999, -0.010000, 1.724999, 0.000000, -177.800018, 0.000000);
		SetPlayerAttachedObject(playerid, 8, 18693, 5, 0.107000, -0.537999, -1.597999, -18.800004, -4.000007, -27.599994);
		PlayerFlamingHandEffect[playerid] = true;

		new text_string[128];
		format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] used flaming hand", PlayerInfo[playerid][name], playerid);
		foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);
		return 1;
	}

	if(IsPlayerAttachedObjectSlotUsed(playerid, 7)) RemovePlayerAttachedObject(playerid, 7);
	if(IsPlayerAttachedObjectSlotUsed(playerid, 8)) RemovePlayerAttachedObject(playerid, 8);

	PlayerFlamingHandEffect[playerid] = false;

	s_PlayerWaitTime[playerid] = timestamp + 10;
	return 1;
}

//p. premium chat
cmd:pc(playerid, params[]) 
{
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

	if(isnull(params)) return SendInfo(playerid, "Enter: /pc [text]");

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_pale_green"[Premium] " c_grey"%s[%d]:"c_grey" %s", PlayerInfo[playerid][name], playerid, params);
	foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);
	return 1;
}


// Forward declarations
forward R_ChangeVehicleColor(vehicleid, colorIndex);
forward RestoreOriginalColor(vehicleid);
forward RainbowColorChange(playerid);

// Function to change the vehicle's color
public R_ChangeVehicleColor(vehicleid, colorIndex) {
    new color1 = rainbowColors[colorIndex];
    new color2 = rainbowColors[(colorIndex + 1) % RAINBOW_COLOR_COUNT]; // Next color for second slot

    // Change the vehicle's color using Color IDs
    ChangeVehicleColor(vehicleid, color1, color2);

	return 1;
}

// Function to restore the vehicle's original color
public RestoreOriginalColor(vehicleid) {
    // Restore the vehicle's original color using Color IDs
    ChangeVehicleColor(vehicleid, originalColors[vehicleid][0], originalColors[vehicleid][1]);

	return 1;
}

// Timer function to loop and change the vehicle's color
public RainbowColorChange(playerid) {
    if(!IsPlayerInAnyVehicle(playerid)) return 0; // If the player is not in a vehicle, stop the timer

    new vehicleid = GetPlayerVehicleID(playerid);
    new colorIndex = GetPVarInt(playerid, "colorIndex"); // Retrieve the current color index

    // Change the vehicle's color
    R_ChangeVehicleColor(vehicleid, colorIndex);

    // Update the color index and loop it
    colorIndex = (colorIndex + 1) % RAINBOW_COLOR_COUNT;
    SetPVarInt(playerid, "colorIndex", colorIndex); // Store the updated index for the next loop

    // Continue the timer
    SetTimerEx("RainbowColorChange", RAINBOW_INTERVAL, false, "i", playerid);

    return 1;
}

// Define the 'rainbow' command to change the vehicle's color
CMD:rainbow(playerid) {
    if(PlyayerIsGang && !PlayerInfo[playerid][premium]) 
        return SendError(playerid, "Shoma Premium Nistid.");

    if(s_PlayerWaitTime[playerid] > timestamp) {
        SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");
        return 1;
    }

    if(IsPlayerInAnyVehicle(playerid)) {
        new vehicleid = GetPlayerVehicleID(playerid);
        
        // Save the original color if it's not already saved
        if(originalColors[vehicleid][0] == 0 && originalColors[vehicleid][1] == 0) {
            GetVehicleColor(vehicleid, originalColors[vehicleid][0], originalColors[vehicleid][1]);
        }
        
        // Initialize the color index and start the timer for color change
        SetPVarInt(playerid, "colorIndex", 0);
        RainbowColorChange(playerid); // Start changing colors with a timer

        new text_string[128];
        format(text_string, sizeof(text_string), ""c_server"* Premium:"c_grey" %s[%d] used rainbow", PlayerInfo[playerid][name], playerid);
        foreach(new i: premium_players) SendClientMessage(i, col_white, text_string);
    } else {
        SendError(playerid, "Shoma savar vasile naghliye nistid.");
    }
    
	s_PlayerWaitTime[playerid] = timestamp + 10;

    return 1;
}

// Define a variable to store the time of the last jump
new lastJumpTime[MAX_PLAYERS];

// Define the 'vjump' command for vehicle jumping
CMD:vjump(playerid) {
	
	if(PlyayerIsGang && !PlayerInfo[playerid][premium]) return SendError(playerid, "Shoma Premium Nistid.");

    // Check if the player is inside a vehicle
    if(IsPlayerInAnyVehicle(playerid)) {
        new vehicleid = GetPlayerVehicleID(playerid);
        
        // Get the current position of the vehicle
        new Float:x, Float:y, Float:z;
        GetVehiclePos(vehicleid, x, y, z);
        
        // Check if the vehicle is currently moving
        new Float:velocity[3];
        GetVehicleVelocity(vehicleid, velocity[0], velocity[1], velocity[2]);
        
        // Get the current time
        new currentTime = GetTickCount();

        // Check the time limit (every 5000 milliseconds = 5 seconds)
        if(currentTime - lastJumpTime[playerid] < 5000) {
            SendError(playerid, "Shoma har 5 sanyie mitavanid az vjump estefade konid.");
            return 1;
        }
        
        // If the vehicle is moving
        if(velocity[0] != 0.0 || velocity[1] != 0.0) {
            // Make the vehicle jump (increase the Z position for a jump)
            new Float:ax,Float:xx,Float:yx;
			GetVehicleZAngle(vehicleid, ax);
			xx = 0.5 * floatsin(-(ax+2), degrees);
			yx = 0.5 * floatcos(-(ax+2), degrees);
			SetVehicleVelocity(vehicleid, xx, yx, 0.7);
            SendClientMessage(playerid, col_white, ""scm_info"Your vehicle jumped!");
            
            // Update the time of the last jump
            lastJumpTime[playerid] = currentTime;
        } else {
            SendError(playerid, "Your vehicle needs to be moving to jump!");
        }
    } else {
        SendError(playerid, "Shoma savar vasile naghliye nistid.");
    }
    return 1;
}

// Command /psurf to enable the vehicle surfing system
CMD:psurf(playerid) {
    // If surfing is disabled
    if(!isPlayerSurfing[playerid]) {
        isPlayerSurfing[playerid] = true; // Enable the system
        SendClientMessage(playerid, col_white, ""scm_info"Surf mode activated.");
    } else {
        // If enabled, disable it
        isPlayerSurfing[playerid] = false;
        attachedVehicle[playerid] = INVALID_VEHICLE_ID; // Detach the connected vehicle
		SendClientMessage(playerid, col_white, ""scm_info"Surf mode deactivated.");
    }
    return 1;
}


forward premium_OnPlayerDeath(playerid, killerid, reason);
public premium_OnPlayerDeath(playerid, killerid, reason) {
    // If the player was surfing, disable the surf mode
    if(isPlayerSurfing[playerid]) {
        isPlayerSurfing[playerid] = false;               // Disable surf mode
        attachedVehicle[playerid] = INVALID_VEHICLE_ID;  // Reset the attached vehicle
    }
    return 1;
}

// Forward declarations
forward ToggleVehicleLights(playerid);

// Function to toggle vehicle lights (rainbow effect)
public ToggleVehicleLights(playerid) {
    if(!IsPlayerInAnyVehicle(playerid)) return 0; // If the player is not in a vehicle, stop the timer

    new vehicleid = GetPlayerVehicleID(playerid);
    new lightState = GetPVarInt(playerid, "lightState"); // Retrieve the current light state

	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    // Toggle the vehicle's lights
    if(lightState == 0) {
        // Turn on the vehicle's lights
        SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
    } else {
        // Turn off the vehicle's lights
        SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
    }

    // Toggle light state and loop it
    lightState = !lightState; // Flip between 0 and 1
    SetPVarInt(playerid, "lightState", lightState); // Store the updated state for the next loop

    // Continue the timer if the effect is still active
    if(isPlayerLightOn[playerid]) {
        SetTimerEx("ToggleVehicleLights", RAINBOW_INTERVAL, false, "i", playerid);
    }

    return 1;
}

// Define the 'plight' command to enable or disable the vehicle's light dance
CMD:plight(playerid) {
    // Check if the player is premium
    if(PlyayerIsGang && !PlayerInfo[playerid][premium])
        return SendError(playerid, "Shoma Premium Nistid.");

    // Check the wait time for premium commands
    if(s_PlayerWaitTime[playerid] > timestamp)
		return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

    // Check if the player is in a vehicle
    if(IsPlayerInAnyVehicle(playerid)) {
        // Get the vehicle ID
        new vehicleid = GetPlayerVehicleID(playerid);

        // Check if light dance mode is currently off
        if(!isPlayerLightOn[playerid]) {
            isPlayerLightOn[playerid] = true; // Enable light dance mode
            SetPVarInt(playerid, "lightState", 0); // Initialize light state
            ToggleVehicleLights(playerid); // Start the light toggle with a timer

            SendClientMessage(playerid, col_green, ""scm_info"Vehicle light dance activated.");
        } else {
            // Disable light dance mode
            isPlayerLightOn[playerid] = false; // Disable light dance mode
            SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_OFF, -1, -1, -1, -1, -1); // Turn off lights

            SendClientMessage(playerid, col_red, ""scm_info"Vehicle light dance deactivated.");
        }
    } else {
        // If the player is not in a vehicle
        SendError(playerid, "Shoma savar vasile naghliye nistid.");
    }

    return 1;
}

new PlayerSnow[MAX_PLAYERS];
static PlayerSnowObject[MAX_PLAYERS];

public OnPlayerDisconnect(playerid, reason)
{
	if (PlayerSnow[playerid]) {
		DestroyDynamicObject(PlayerSnowObject[playerid]);
		PlayerSnowObject[playerid] = 0;
		PlayerSnow[playerid] = 0;
	}

	#if defined SnowSystem_OnPlayerDisconnect
		return SnowSystem_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect SnowSystem_OnPlayerDisconnect
#if defined SnowSystem_OnPlayerDisconnect
	forward SnowSystem_OnPlayerDisconnect(playerid, reason);
#endif

// ------------------------------------------------------------------

public OnPlayerSpawn(playerid)
{
	if (PlayerSnow[playerid] && PlayerSnowObject[playerid] == 0) {
		PlayerSnowObject[playerid] = CreateDynamicObject(18864, 9999.0, 9999.0, -200.0, 0.0, 0.0, 45.0, .playerid = playerid);
		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	}

	#if defined SnowSystem_OnPlayerSpawn
		return SnowSystem_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn SnowSystem_OnPlayerSpawn
#if defined SnowSystem_OnPlayerSpawn
	forward SnowSystem_OnPlayerSpawn(playerid);
#endif

// ------------------------------------------------------------------

SnowSystemOneSecPlayerTimer(playerid) {
	if (PlayerSnow[playerid] && PlayerSnowObject[playerid] != 0) {
		if (GetPlayerInterior(playerid) == 0) {
			new Float:playerX, Float:playerY, Float:playerZ;
	        GetPlayerPos(playerid, playerX, playerY, playerZ);
	        SetDynamicObjectPos(PlayerSnowObject[playerid], playerX, playerY, playerZ - 5.0);
	    }
	}
}

// ------------------------------------------------------------------

cmd:allsnow(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;
	if(sscanf(params, "d", params[0])) return SendError(playerid, "Enter /allsnow [0 | 1]");
	if(params[0] < 0 || params[0] > 1) return SendError(playerid, "Enter /allsnow [0 | 1]");
	
	switch(params[0])
	{
	    case 1:
	    {
			foreach(new i: logged_players) {
				PlayerSnow[i] = 1;
    			PlayerSnowObject[i] = CreateDynamicObject(18864, 99999.0, 99999.0, 99999.0, 0.0, 0.0, 45.0, .playerid = playerid);
    			Streamer_Update(i, STREAMER_TYPE_OBJECT);
			}
			
			AdminMes(""c_server"* A.INFO: "c_grey"%s enabled snow mode.", PlayerInfo[playerid][name]);
		}
		case 0:
		{
			foreach(new i: logged_players) {
				DestroyDynamicObject(PlayerSnowObject[i]);
				PlayerSnowObject[i] = 0;
				PlayerSnow[i] = 0;
			}

			AdminMes(""c_server"* A.INFO: "c_grey"%s disabled snow mode.", PlayerInfo[playerid][name]);
		}
	}

	RunQuery("UPDATE `users` SET `u_snow_mode` = '%d' WHERE 1", params[0]);
    
    return 1;
}

// ------------------------------------------------------------------

cmd:snow(playerid, params[]) {
	// Check if the player is premium
    if(PlyayerIsGang && !PlayerInfo[playerid][premium])
        return SendError(playerid, "Shoma Premium Nistid.");

    // Check the wait time for premium commands
    if(s_PlayerWaitTime[playerid] > timestamp)
		return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	if(PlayerSnow[playerid] == 1) 
    {
        DestroyDynamicObject(PlayerSnowObject[playerid]);
        PlayerSnowObject[playerid] = 0;
        PlayerSnow[playerid] = 0;
        update_int_sql(playerid, "u_snow_mode", PlayerSnow[playerid]);
        return 1;
    }
    PlayerSnow[playerid] = 1;
    PlayerSnowObject[playerid] = CreateDynamicObject(18864, 99999.0, 99999.0, 99999.0, 0.0, 0.0, 45.0, .playerid = playerid);
    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
    update_int_sql(playerid, "u_snow_mode", PlayerSnow[playerid]);

	// Set the wait time for premium commands
    s_PlayerWaitTime[playerid] = timestamp + 10;

    return 1;
}

//skate

cmd:pskate(playerid){
	// Check if the player is premium
    if(PlyayerIsGang && !PlayerInfo[playerid][premium])
        return SendError(playerid, "Shoma Premium Nistid.");

    // Check the wait time for premium commands
    if(s_PlayerWaitTime[playerid] > timestamp)
		return SendError(playerid, "Shoma har "c_orange_red"10 "c_white"sanie yekbar mitavanid az cmd haye premium estefade konid.");

	if(!IsPlayerInAnyVehicle(playerid))
		return SendError(playerid, "Shoma nmitavanid dar in halat skate bardarid.");

	if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0)
		return SendError(playerid, "Shoma nmitavanid dar in makan skate dashte bashid.");
		
	ApplyAnimation(playerid, "CARRY","null",0,0,0,0,0,0,0);
	ApplyAnimation(playerid, "SKATE","null",0,0,0,0,0,0,0);
	ApplyAnimation(playerid, "CARRY","crry_prtial",4.0,0,0,0,0,0);
	SetPlayerArmedWeapon(playerid,0);

	if(!InfoSkate[playerid][sActive]){
		InfoSkate[playerid][sActive] = true;
		DestroyDynamicObject(InfoSkate[playerid][sSkate]);
		RemovePlayerAttachedObject(playerid,INDEX_SKATE);
		#if TYPE_SKATE == 0
		// the skate is placed on the right arm
		SetPlayerAttachedObject(playerid,INDEX_SKATE,19878,6,-0.055999,0.013000,0.000000,-84.099983,0.000000,-106.099998,1.000000,1.000000,1.000000);
		#else
		// the skate is placed in the back
		SetPlayerAttachedObject(playerid,INDEX_SKATE,19878,1,0.055999,-0.173999,-0.007000,-95.999893,-1.600010,24.099992,1.000000,1.000000,1.000000);
		#endif
		PlayerPlaySound(playerid,21000,0,0,0);
		SendClientMessage(playerid,-1,"{FFFFFF}Skate: {00B100}Voce Pegou o seu Skate{FFFFFF}!.");
	}else{
		InfoSkate[playerid][sActive] = false;
		DestroyDynamicObject(InfoSkate[playerid][sSkate]);
		RemovePlayerAttachedObject(playerid,INDEX_SKATE);
		PlayerPlaySound(playerid,21000,0,0,0);
		SendClientMessage(playerid,-1,"{FFFFFF}Skate: {B00000}Voce Guardou o seu Skate{FFFFFF}!.");
	}

	// Set the wait time for premium commands
    s_PlayerWaitTime[playerid] = timestamp + 10;

	return true;
}