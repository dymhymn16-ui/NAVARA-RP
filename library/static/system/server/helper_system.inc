
//h. set helper
cmd:sethelper(playerid, params[]) {
	if(check_admin_rank(playerid , 7)) return 1;

	extract params -> new player:targetid; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /sethelper [Player id]");
	
	if (!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_gray, ""scm_error"Player not found.");
    if (!p_t_info[targetid][p_logged]) return SendClientMessage(playerid, col_gray, ""scm_error"Player is not logged in.");
    if (PlayerInfo[targetid][helper]) return SendClientMessage(playerid, col_gray, ""scm_error"Player is already helper.");

    PlayerInfo[targetid][helperDuty] = true;
    PlayerInfo[targetid][helper] = 1;
    Iter_Add(helper_players, targetid);
    UpdatePlayerName(targetid);

    new query_string[128];

	format(query_string, sizeof(query_string), ""c_yellow"* S.INFO: Admin %s[%d] Shoma Ra Helper Kard!", PlayerInfo[playerid][name], playerid);
	SendClientMessage(targetid, col_gray, query_string);
	GameTextForPlayer(targetid, "/hhelp", 3000, 3);

	format(query_string, sizeof(query_string), ""c_yellow"* S.INFO: Shoma %s[%d] Ra Helper Kardid.", PlayerInfo[targetid][name], targetid);
	SendClientMessage(playerid, col_gray, query_string);
	
	format(query_string, sizeof(query_string), 
		"UPDATE `users` SET `u_helper`=%d WHERE `u_id`='%d' LIMIT 1", 
		PlayerInfo[targetid][helper], 
		PlayerInfo[targetid][id]);
	mysql_query(sql_connection, query_string);
	return 1;
}

// ------------------------------------------------------------------

cmd:takehelper(playerid, params[]) {
	if(check_admin_rank(playerid , 5)) return 1;

	extract params -> new player:targetid, string:takeReason[32]; else return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /takehelper [Player id] [Reason]");
	
	if (!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_gray, ""scm_error"Player not found.");
    if (!p_t_info[targetid][p_logged]) return SendClientMessage(playerid, col_gray, ""scm_error"Player is not logged in.");
    if (!PlayerInfo[targetid][helper]) return SendClientMessage(playerid, col_gray, ""scm_error"Player is not helper.");

    PlayerInfo[targetid][helperDuty] = false;
    PlayerInfo[targetid][helper] = 0;
    Iter_Remove(helper_players, targetid);
    UpdatePlayerName(targetid);

    new query_string[128];

	format(query_string, sizeof(query_string), ""c_yellow"* S.INFO: Admin %s[%d] Helper Shoma Ra Take Kard. (%s)", PlayerInfo[playerid][name], playerid, takeReason);
	SendClientMessage(targetid, col_gray, query_string);

	format(query_string, sizeof(query_string), ""c_yellow"* S.INFO: Shoma Helper %s[%d] Ra Take Kardid. (%s)", PlayerInfo[targetid][name], targetid, takeReason);
	SendClientMessage(playerid, col_gray, query_string);
	
	format(query_string, sizeof(query_string), 
		"UPDATE `users` SET `u_helper`=%d WHERE `u_id`='%d' LIMIT 1", 
		PlayerInfo[targetid][helper], 
		PlayerInfo[targetid][id]);
	mysql_query(sql_connection, query_string);
	return 1;
}

// ------------------------------------------------------------------

alias:hhelp("helperhelp", "helpercmds");
cmd:hhelp(playerid) {
	if (!PlayerInfo[playerid][helper]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Dastrasi Be In Dastor Ra Nadarid.");

	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, "{CA00CA}Helper Commands", "\
		"c_server"/hduty"c_white" - On/Off Duty\n\
		"c_server"/hgoto"c_white" - Goto Be Player\n\
		"c_server"/hjp"c_white" - Jetpack\n\
		"c_server"/hcar"c_white" - Mashin\n\
		"c_server"/hnrg"c_white" - Motor\n\
		"c_server"/hdv"c_white" - Hazf Mashin\n\
		"c_server"/hhp"c_white" - Por Kardan Khon\n\
		"c_server"/hc"c_white" - Chat Helper\n\
		"c_server"/asks"c_white" - Javab Be Soval Ha", 

		"Bastan", "");
	return 1;
}

// ------------------------------------------------------------------

cmd:hduty(playerid, params[])
{
	if (!PlayerInfo[playerid][helper]) return 1;

	if (PlayerInfo[playerid][helperDuty]) {
		PlayerInfo[playerid][helperDuty] = false;
		
		GameTextForPlayer(playerid, "~w~Helper Duty: ~r~Off", 3000, 3);
		return 1;
	}

	PlayerInfo[playerid][helperDuty] = true;
	GameTextForPlayer(playerid, "~w~Helper Duty: ~r~On", 3000, 3);
	return 1;
}

// ------------------------------------------------------------------

cmd:hgoto(playerid, params[])
{
	if (!PlayerInfo[playerid][helper]) return 1;

	if (!PlayerInfo[playerid][helperDuty]) {
		SendClientMessage(playerid, col_white, ""scm_error"Shoma Duty Nistid. (/hDuty)");
		return 1;
	}
	
	extract params -> new player:targetid; else return SendClientMessage(playerid, col_gray, !""scm_info"Enter: "c_white"/hgoto [id Bazikon]");
	if (!IsPlayerConnected(targetid) || targetid == playerid) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");
	if (!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Spawn Nashode Ast.");
	if (PlayerInfo[targetid][admin] > PlayerInfo[playerid][admin]) return SendClientMessage(playerid, col_white, !""scm_error"Be Admin Nemitavanid Goto Konid.");

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z;
	GetPlayerPos(targetid, pl_pos_X, pl_pos_Y, pl_pos_Z);

	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		set_pos(playerid, pl_pos_X + 2.0, pl_pos_Y, pl_pos_Z, 0.0, GetPlayerInterior(targetid), GetPlayerVirtualWorld(targetid));
	} else {
		new carid = GetPlayerVehicleID(playerid);
		SetVehiclePos(carid, pl_pos_X + 2.0, pl_pos_Y, pl_pos_Z);
		SetVehicleVirtualWorld(carid, GetPlayerVirtualWorld(targetid));
		LinkVehicleToInterior(carid, GetPlayerInterior(targetid));
	}

	if(p_t_info[playerid][house] != -1) p_t_info[targetid][house] = p_t_info[playerid][house];
	if(p_t_info[playerid][business] != -1) p_t_info[targetid][business] = p_t_info[playerid][business];

	new text_string[120];
	format(text_string, sizeof(text_string), ""c_server"* Helper: "c_grey"%s[%d] teleporting to the player %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid);
	foreach(new i: helper_players) SendClientMessage(i, col_gray, text_string);
	return 1;
}

// ------------------------------------------------------------------

cmd:hcar(playerid, params[])
{
	if (!PlayerInfo[playerid][helper]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Dastrasi Be In Dastor Ra Nadarid.");

	if (!PlayerInfo[playerid][helperDuty]) {
		SendClientMessage(playerid, col_white, ""scm_error"Shoma Duty Nistid. (/hDuty)");
		return 1;
	}

	if (GetPlayerInterior(playerid) != 0) return SendClientMessage(playerid, col_white, ""scm_error"Inja Nemitavanid Car Spawn Konid.");

	if (GetPVarInt(playerid, !"helper_vehicle")) return SendClientMessage(playerid, col_white, !"Shoma Yek Mashin Spawn Darid. Baraye Hazf /hdv Bezanid.");

	// new vehicle_id = 405, color_1 = random(255), color_2 = random(255);
	new vehicle_id = 405, color_1 = 136, color_2 = 136;

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z, Float:pl_pos_C;
	GetPlayerPos(playerid, pl_pos_X, pl_pos_Y, pl_pos_Z);

	GetPlayerFacingAngle(playerid, pl_pos_C);

	new helper_veh = CreateVehicle(vehicle_id, pl_pos_X, pl_pos_Y, pl_pos_Z, pl_pos_C, color_1, color_2, -1);
	SetPVarInt(playerid, !"helper_vehicle", helper_veh);

	veh_info[helper_veh -1][v_fuel] = 100.0;

	LinkVehicleToInterior(helper_veh, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(helper_veh, GetPlayerVirtualWorld(playerid));

	PutPlayerInVehicle(playerid, helper_veh, 0);
	SetPlayerArmedWeapon(playerid, 0);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Helper:"c_grey" %s[%d] Created Vehicle. Model: %s (%d)", PlayerInfo[playerid][name], playerid, vehicle_name[vehicle_id-400], vehicle_id);
	foreach(new i: helper_players) SendClientMessage(i, col_white, text_string);

	return true;
}

// ------------------------------------------------------------------

cmd:hnrg(playerid, params[])
{
	if (!PlayerInfo[playerid][helper]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Dastrasi Be In Dastor Ra Nadarid.");

	if (!PlayerInfo[playerid][helperDuty]) {
		SendClientMessage(playerid, col_white, ""scm_error"Shoma Duty Nistid. (/hDuty)");
		return 1;
	}

	if (GetPlayerInterior(playerid) != 0) return SendClientMessage(playerid, col_white, ""scm_error"Inja Nemitavanid Car Spawn Konid.");

	if (GetPVarInt(playerid, !"helper_vehicle")) return SendClientMessage(playerid, col_white, !"Shoma Yek Mashin Spawn Darid. Baraye Hazf /hdv Bezanid.");

	// new vehicle_id = 522, color_1 = random(255), color_2 = random(255);
	new vehicle_id = 522, color_1 = 136, color_2 = 136;

	new Float:pl_pos_X, Float:pl_pos_Y, Float:pl_pos_Z, Float:pl_pos_C;
	GetPlayerPos(playerid, pl_pos_X, pl_pos_Y, pl_pos_Z);

	GetPlayerFacingAngle(playerid, pl_pos_C);

	new helper_veh = CreateVehicle(vehicle_id, pl_pos_X, pl_pos_Y, pl_pos_Z, pl_pos_C, color_1, color_2, -1);
	SetPVarInt(playerid, !"helper_vehicle", helper_veh);

	veh_info[helper_veh -1][v_fuel] = 100.0;

	LinkVehicleToInterior(helper_veh, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(helper_veh, GetPlayerVirtualWorld(playerid));

	PutPlayerInVehicle(playerid, helper_veh, 0);
	SetPlayerArmedWeapon(playerid, 0);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Helper:"c_grey" %s[%d] Created Vehicle. Model: %s (%d)", PlayerInfo[playerid][name], playerid, vehicle_name[vehicle_id-400], vehicle_id);
	foreach(new i: helper_players) SendClientMessage(i, col_white, text_string);

	return true;
}

// ------------------------------------------------------------------

cmd:hdv(playerid, params[])
{
	if (!PlayerInfo[playerid][helper]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Dastrasi Be In Dastor Ra Nadarid.");

	new veh_id = GetPVarInt(playerid, !"helper_vehicle");
	if (!veh_id) return SendClientMessage(playerid, col_white, !""scm_error"No vehicle has been created");

	DestroyVehicle(veh_id);

	SendClientMessage(playerid, col_gray, "Car deleted");

	return DeletePVar(playerid, !"helper_vehicle");
}

// ------------------------------------------------------------------

cmd:hjp(playerid) 
{
	if (!PlayerInfo[playerid][helper]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Dastrasi Be In Dastor Ra Nadarid.");

	if (p_t_info[playerid][gomp]) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Shoma Dar Event Hastid!");
	if (IsPlayerInFalloutGame(playerid)) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Shoma Dar Event Hastid!");
	if (ReturnPlayerInCounterStrike(playerid) != 0) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Shoma Dar Event Hastid!");

	if (!PlayerInfo[playerid][helperDuty]) {
		SendClientMessage(playerid, col_white, ""scm_error"Shoma Duty Nistid. (/hDuty)");
		return 1;
	}

	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
	{
	    SendClientMessage(playerid, COLOR_GREY, "Shoma Jetpack Darid. Baraye Az Bin Bordan {FFFFFF}/jpoff {999999}Bezanid.");
		return 1;
	}

	GameTextForPlayer(playerid, "~y~~h~JETPACK", 3, 2500);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Helper:"c_grey" %s[%d] spawned jetpack", PlayerInfo[playerid][name], playerid);
	foreach(new i: helper_players) SendClientMessage(i, col_white, text_string);
	return 1;
}

// ------------------------------------------------------------------

cmd:hc(playerid, params[]) 
{
	if (!PlayerInfo[playerid][helper]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Dastrasi Be In Dastor Ra Nadarid.");

	if (isnull(params)) return SendClientMessage(playerid, col_gray,""scm_info"Enter: /hc [text]");

	new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* Helper %s[%d]:"c_grey" %s", PlayerInfo[playerid][name], playerid, params);
	foreach(new i: helper_players) SendClientMessage(i, col_white, text_string);
	return 1;
}

// ------------------------------------------------------------------

cmd:hhp(playerid, params[])
{
	if (!PlayerInfo[playerid][helper]) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Dastrasi Be In Dastor Ra Nadarid.");

	if (ReturnPlayerInCounterStrike(playerid) != 0) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Shoma Dar Event Hastid!");

	if (!PlayerInfo[playerid][helperDuty]) {
		SendClientMessage(playerid, col_white, ""scm_error"Shoma Duty Nistid. (/hDuty)");
		return 1;
	}

	extract params -> new player:targetid; else return SendClientMessage(playerid, col_gray, !""scm_info"Enter: "c_white"/hhp [id Bazikon]");
	if (!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Yaft Nashod.");

	if (IsPlayerInAnyDMZone(targetid)) return SendClientMessage(playerid, col_white, !""scm_error"In Bazikon Dar DM Zone Ast.");
	
	if (playerid != targetid) 
	{
		if (!IsPlayerSpawned(targetid)) return SendClientMessage(playerid, col_white, !""scm_error"Bazikon Spawn Nashode Ast.");
    	// if (!IsPlayerInRangeOfPoint(playerid, 7.0, p_t_info[targetid][p_pos][0], p_t_info[targetid][p_pos][1], p_t_info[targetid][p_pos][2])) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Shoma Kenar In Bazikon Nistid.");
	    
		if (IsPlayerInFalloutGame(targetid)) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"In Bazikon Dar Event Fallout Hast!");
		if (ReturnPlayerInCounterStrike(targetid) != 0) return SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"In Bazikon Dar Event Counter Strike Hast!");
	} 
	else 
	{
		if (!IsPlayerSpawned(playerid)) return SendClientMessage(playerid, col_white, !""scm_error"Shoma Spawn Nistid.");
	}

    set_health(targetid, 100.0);

    new text_string[128];
	format(text_string, sizeof(text_string), ""c_server"* S.INFO:"c_grey" Helper %s[%d] healed you", PlayerInfo[playerid][name], playerid);
	SendClientMessage(targetid, col_white, text_string);

	format(text_string, sizeof(text_string), ""c_server"* Helper:"c_grey" %s[%d] healed player %s[%d]", PlayerInfo[playerid][name], playerid, PlayerInfo[targetid][name], targetid);
	foreach(new i: helper_players) SendClientMessage(i, col_white, text_string);
	return 1;
}

cmd:ask(playerid)
{
    if(PlayerInfo[playerid][mute]) return SendError(playerid, "Shoma be dastrasi be chat  mahrum shodid baraye didan time biron omadan az mahrumiat: "c_server"/time");

    show_dialog(playerid, d_ask_request, DIALOG_STYLE_INPUT, !""scm_dialog"Contact Support", !"\
    "c_server"You are about to ask support.\n\
    "c_white"Lotfan soal khod ra sahih va vazeh bayan konid.\n\
    \n\
    "c_server"> Ghabl az ersal sovaleton motmaen beshid ke dorost neveshtid.", !"Send", !"Cancel");
    return 1;
}

alias:asks("helpme");
cmd:asks(playerid, params[])
{
    if(PlyayerIsGang && !PlayerInfo[playerid][helper]) return 1;

	new dialog_string[17 + (MAX_PLAYER_NAME -4) * 2 + 9 + 16],
	string[19 + MAX_PLAYER_NAME -3];
	global_string[0] = EOS;

	for(new i = 0; i < max_ask; i++)
	{
		if(ask_player[i] == -1) continue;
		if(isnull(global_string)) global_string = ""c_white"#\t"c_white"Sender\t"c_white"Status\n";
		if(ask_slot[i] != -1) string = ""c_yellow"Checks: ", strcat(string, PlayerInfo[ask_slot[i]][name]);

		format(dialog_string, sizeof dialog_string, ""c_white"%d.\t%s\t%s\n", i, PlayerInfo[ask_player[i]][name], (ask_slot[i] == -1) ?
		""c_green"Awaiting processing" : string);
		strcat(global_string, dialog_string);
		string[0] = EOS;
	}

	if(!isnull(global_string)) show_dialog(playerid, d_asks, DIALOG_STYLE_TABLIST_HEADERS, !""scm_dialog"List of ask", global_string, !"Process", !"Bastan");
    else SendError(playerid, "The ask is currently empty.");

	return 1;
}