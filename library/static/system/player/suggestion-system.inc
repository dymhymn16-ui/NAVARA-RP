stock createSuggestion(playerid, targetid, price, sug_title[], call_back, no_call_back)
{
    if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_gray,""scm_error"Bazikon Yaft Nashod.");
    if(!IsPlayerInRangeOfPoint(targetid, 5, p_t_info[playerid][p_pos][0],
							                 p_t_info[playerid][p_pos][1],
							                 p_t_info[playerid][p_pos][2])) return SendClientMessage(playerid, col_gray,""scm_error"Bazikon Kheyli door ast.");

    if(targetid == playerid) return SendClientMessage(playerid, col_gray,""scm_error"Shoma nemitavanid be khodetan pishnehad bedid.");
    if(check_suggestion(targetid)) return SendClientMessage(playerid, col_gray,""scm_error"In bazikon darhal hazer yek pishnehad dard.");

    new string[300];

    p_t_info[playerid][suggestion] = 1;
    p_t_info[playerid][suggestion_playerid] = playerid;

    p_t_info[targetid][suggestion] = 1;
    p_t_info[targetid][suggestion_price] = price;
    p_t_info[targetid][suggestion_change] = 0;
    p_t_info[targetid][suggestion_callback] = call_back;
    p_t_info[targetid][suggestion_no_callback] = no_call_back;
    format(p_t_info[targetid][suggestion_title], 150, "%s", sug_title);

    fmt(string, "{568db4}Player "c_yellow"%s {568db4}be shoma pishnehad "c_yellow"\"%s\"{568db4} midahad. Gheymat: "c_yellow"$%s", PlayerInfo[playerid][name], sug_title, convert_money(price));
    SendClientMessage(targetid, col_white, string);
    SendClientMessage(targetid, col_white, c_white"Baraye movafeghat "c_green"/yes"c_white" ya baraye rad kardan "c_orange_red"/no"c_white" vared konid");

    fmt(string ,c_white"\nPishnehad shoma be player %s "c_white"ersal shod.\n\
    "c_white"Noe Pishnahad: "c_server"Forosh Kala\n\
    "c_white"Pishnahad Shoma: "c_yellow"%s\n\
    "c_white"Gheymat: "c_green"$%s",
	PlayerInfo[targetid][name],
	sug_title,
    convert_money(price));

	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""scm_dialog"Pishnehad", string, "bastan", "");

    return 1;
}

stock createSuggestionEx(playerid, targetid, price, sug_title[], sug_title2[], call_back[], no_call_back[])
{
    if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, col_gray,""scm_error"Bazikon Yaft Nashod.");
    if(!IsPlayerInRangeOfPoint(targetid, 5, p_t_info[playerid][p_pos][0],
							                 p_t_info[playerid][p_pos][1],
							                 p_t_info[playerid][p_pos][2])) return SendClientMessage(playerid, col_gray,""scm_error"Bazikon Kheyli door ast.");

    if(targetid == playerid) return SendClientMessage(playerid, col_gray,""scm_error"Shoma nemitavanid be khodetan pishnehad bedid.");
    if(check_suggestion(targetid)) return SendClientMessage(playerid, col_gray,""scm_error"In bazikon darhal hazer yek pishnehad dard.");

    new string[300];

    p_t_info[playerid][suggestion] = 1;
    p_t_info[playerid][suggestion_playerid] = playerid;

    p_t_info[targetid][suggestion] = 1;
    p_t_info[targetid][suggestion_price] = price;
    p_t_info[targetid][suggestion_change] = 1;
	p_t_info[targetid][suggestion_callback] = call_back;
    p_t_info[targetid][suggestion_no_callback] = no_call_back;
    format(p_t_info[targetid][suggestion_title], 150, "%s", sug_title);
    format(p_t_info[targetid][suggestion_title2], 150, "%s", sug_title2);


    fmt(string, "{568db4}Player "c_yellow"%s {568db4}be shoma pishnehad mobadele "c_yellow"\"%s\" {568db4}ba "c_yellow"\"%s\" {568db4}dad", PlayerInfo[playerid][name], sug_title, sug_title2);
    SendClientMessage(targetid, col_white, string);
    fmt(string, "{568db4}Hazine ezafi az taraf shoma: "c_yellow"$%s", convert_money(price));
    SendClientMessage(targetid, col_white, string);
    SendClientMessage(targetid, col_white, c_white"Baraye movafeghat "c_green"/yes"c_white" ya baraye rad kardan "c_orange_red"/no"c_white" vared konid");

    fmt(string ,c_white"\nPishnehad shoma be player %s "c_white"ersal shod.\n\
    "c_white"Noe Pishnahad: "c_server"Mobadele Kala\n\
    "c_white"Kalay-e Shoma: "c_yellow"%s\n\
    "c_white"Kalay-e Moghabel: "c_yellow"%s\n\
    "c_white"Hazineh Ezafi: "c_green"$%s",
	PlayerInfo[targetid][name],
	sug_title,
    sug_title2,
    convert_money(price));

	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, ""scm_dialog"Pishnehad", string, "bastan", "");

    return 1;
}

stock clear_suggestion(playerid)
{
    p_t_info[playerid][suggestion] = -1;
    p_t_info[playerid][suggestion_price] = -1;
    p_t_info[playerid][suggestion_playerid] = -1;
    p_t_info[playerid][suggestion_change] = -1;
    p_t_info[playerid][suggestion_callback] = -1;
    p_t_info[playerid][suggestion_no_callback] = -1;
    format(p_t_info[playerid][suggestion_title], 150, "None");
    format(p_t_info[playerid][suggestion_title2], 150, "None");

    return 1;
}

stock check_suggestion(playerid)
{
    if(p_t_info[playerid][suggestion] != -1)
        return true;
    else
        return false;
}

cmd:yes(playerid)
{
    if(CMD_Vote_Yes(playerid)) return 1;

	new targetid;

	// if(PlayerInfo[playerid][pSINVSeller] != INVALID_PLAYER_ID)
	// {
	// 	new scdplayerid = PlayerInfo[playerid][pSINVSeller], numbers = PlayerInfo[playerid][pSINVNumber], numberIDx = PlayerInfo[playerid][pSINVNumberIDx], price = PlayerInfo[playerid][pSINVPrice];
	// 	if(PlayerInfo[playerid][pSINVSIDx] != PlayerInfo[scdplayerid][id] || !IsPlayerConnected(scdplayerid))
	// 	{
	// 		PlayerInfo[playerid][pSINVSeller] = INVALID_PLAYER_ID;
	// 		PlayerInfo[playerid][pSINVSIDx] = 0;
	// 		PlayerInfo[playerid][pSINVPrice] = 0;
	// 		PlayerInfo[playerid][pSINVNumber] = 0;
	// 		PlayerInfo[playerid][pSINVNumberIDx] = 0;
    //         return SendMes(playerid, COLOR_RED, "* Foroshande Peyda Nashod");
	// 	}
	// 	if(PlayerInfo[scdplayerid][pInventoryItems][numbers] < numberIDx)
	// 	{
	// 	 	SendMes(playerid, COLOR_RED, "* Foroshande Be In Tedad Item Nadarad.");
	// 		PlayerInfo[playerid][pSINVSeller] = INVALID_PLAYER_ID;
	// 		PlayerInfo[playerid][pSINVSIDx] = 0;
	// 		PlayerInfo[playerid][pSINVPrice] = 0;
	// 		PlayerInfo[playerid][pSINVNumber] = 0;
	// 		PlayerInfo[playerid][pSINVNumberIDx] = 0;
    //         return SendMes(scdplayerid, COLOR_RED, "Shoma In Tedad Item Nadarid.");
	// 	}
	// 	new max_value;
	// 	GetPlayerMaxInventoryItems(playerid, numbers, max_value);
	// 	if(PlayerInfo[playerid][pInventoryItems][numbers] + numberIDx > max_value)
	// 	{
	// 	    SendMes(playerid, COLOR_RED, "Meghdar Ja Bara Item Nadarid Hadeaksar Jay Shoma Baray %s %s %d Ast.", Inventory[numbers][InvUnitName],Inventory[numbers][InvStringName],max_value);
	// 		PlayerInfo[playerid][pSINVSeller] = INVALID_PLAYER_ID;
	// 		PlayerInfo[playerid][pSINVSIDx] = 0;
	// 		PlayerInfo[playerid][pSINVPrice] = 0;
	// 		PlayerInfo[playerid][pSINVNumber] = 0;
	// 		PlayerInfo[playerid][pSINVNumberIDx] = 0;
	// 	    return SendMes(scdplayerid, COLOR_RED, "Player Ja Bara Item Nadarad Hadeaksar Jay Player Baray %s %s %d Ast.", Inventory[numbers][InvUnitName],Inventory[numbers][InvStringName],max_value);
	// 	}
	// 	if (PlayerInfo[playerid][money] < price)
	// 	{
	// 		SendClientMessage(scdplayerid, col_gray, ""c_orange_red"* "c_grey"Bazikon pol kafi baraye kharid in ro ndarad.");
	// 		SendClientMessage(playerid, col_gray, ""c_orange_red"* "c_grey"Shoma Pol Kafi ndarid.");
	// 		PlayerInfo[playerid][pSINVSeller] = INVALID_PLAYER_ID;
	// 		PlayerInfo[playerid][pSINVSIDx] = 0;
	// 		PlayerInfo[playerid][pSINVPrice] = 0;
	// 		PlayerInfo[playerid][pSINVNumber] = 0;
	// 		PlayerInfo[playerid][pSINVNumberIDx] = 0;
	// 		return 1;
	// 	}
	// 	give_money(playerid, -price);
	// 	give_money(scdplayerid, price);
	// 	PlayerInfo[scdplayerid][pInventoryItems][numbers] -= numberIDx;
	// 	GiveInventoryRealItem(scdplayerid,numbers);
	// 	SavePlayerInventoryItems(scdplayerid, numbers);
	// 	PlayerInfo[playerid][pInventoryItems][numbers] += numberIDx;
	// 	GiveInventoryRealItem(playerid,numbers);
	// 	SavePlayerInventoryItems(playerid, numbers);
	// 	PlayerInfo[playerid][pSINVSeller] = INVALID_PLAYER_ID;
	// 	PlayerInfo[playerid][pSINVSIDx] = 0;
	// 	PlayerInfo[playerid][pSINVPrice] = 0;
	// 	PlayerInfo[playerid][pSINVNumber] = 0;
	// 	PlayerInfo[playerid][pSINVNumberIDx] = 0;
	// 	new strings[512];
	// 	format(strings, sizeof(strings), "Shoma %d %s %s Az %s Ba %d$ Kharidid", numberIDx, Inventory[numbers][InvUnitName],Inventory[numbers][InvStringName], PlayerInfo[scdplayerid][name],price);
	// 	SendMes(playerid, COLOR_MAIN, strings);
	// 	format(strings, sizeof(strings), "Shoma %d %s %s Ra Be %s Ba Gheymat %d$ Forokhtid", numberIDx, Inventory[numbers][InvUnitName],Inventory[numbers][InvStringName], PlayerInfo[playerid][name],price);
	// 	SendMes(scdplayerid, COLOR_WHITE, strings);
	// 	return 1;
	// }

	//Work Book
	if(GetPVarInt(playerid, "WBOOK_Status")) {
		targetid = GetPVarInt(playerid, "WBOOK_Target");

		SendAction(playerid, "dare sabeghe kari %s negah mikone", PlayerInfo[targetid][name]);
		ShowWBook(targetid, playerid);

		return 1;
	}

	//PTS
	if(GetPVarInt(playerid, !"PTS_Status")) {
		targetid = GetPVarInt(playerid, !"PTS_Target");
		
		new scm_string[100];
		if(targetid != playerid) format(scm_string, sizeof(scm_string), "Gozargah vasile naghlie be %s neshan dad", PlayerInfo[playerid][name]);
		else format(scm_string, sizeof(scm_string), "Be gozargah vasile naghlie khod negah kard.");
		me_action(targetid, scm_string);

		new PTS_Vehicle = GetPVarInt(playerid, !"PTS_Vehicle"),
			PTS_Model = GetVehicleModel(PTS_Vehicle);

		format(global_string, sizeof global_string, "\n\
		"c_white"Saheb: "c_white"%s\n\
		"c_white"Model: "c_white"%s(%d)\n\
		"c_white"Pelak: "c_grey"[%s]\n\
		"c_white"Vaziyat VIP: %s\n\
		"c_white"Hadaksar sarat: "c_white"%d KM/H\n\
		"c_white"Masaft peymodeh shode: "c_white"%.1f KM\n\
		"c_white"Hajm-e Bak-e Benzin: "c_white"%d L\n\
		"c_white"GPS Tracker: "c_white"%s\n\n\
		"c_white"Engine Tune:\n\
		"c_server"[1]"c_white"Chip tuning: %s\n\
		"c_server"[2]"c_white"Removal of catalysts: %s\n\
		"c_server"[3]"c_white"Zero resistance air filter: %s\n\
		"c_server"[4]"c_white"Oversized throttle body: %s\n\
		"c_server"[5]"c_white"Forged engine pistons: %s\n\n\
		"c_white"Brake Tune:\n\
		"c_server"[1]"c_white"Ceramic pads: %s\n\
		"c_server"[2]"c_white"Sport brake discs: %s\n\
		"c_server"[3]"c_white"Extended calipers: %s\n\
		"c_server"[4]"c_white"Brake cylinder: %s\n\
		"c_server"[5]"c_white"Vacuum brake booster: %s\n\n\
		"c_white"Stability Tune:\n\
		"c_server"[1]"c_white"Spacers for posts: %s\n\
		"c_server"[2]"c_white"Shock absorbers: %s\n\
		"c_server"[3]"c_white"Reinforced springs: %s\n\
		"c_server"[4]"c_white"Anti-roll bars: %s\n\
		"c_server"[5]"c_white"Suspension joints: %s",

		PlayerInfo[targetid][name], 
		vehicle_name[PTS_Model -400], 
		PTS_Model,  
		veh_info[PTS_Vehicle -1][v_plate],
		veh_info[PTS_Vehicle -1][v_special_car] != 0 ? c_server"Bale" : c_red"Kheyr",
		max_veh_speed[PTS_Model-400],
		veh_info[PTS_Vehicle -1][v_millage],
		max_fuel_capacity[PTS_Model-400],
		veh_info[PTS_Vehicle -1][v_gps_tracker] == 1 ? c_server"Bale" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_engine][0] ? c_server"Bale $250,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_engine][1] ? c_server"Bale $165,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_engine][2] ? c_server"Bale $150,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_engine][3] ? c_server"Bale $200,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_engine][4] ? c_server"Bale $215,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_brake][0] ? c_server"Bale $135,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_brake][1] ? c_server"Bale $155,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_brake][2] ? c_server"Bale $115,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_brake][3] ? c_server"Bale $190,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_brake][4] ? c_server"Bale $220,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_stability][0] ? c_server"Bale $25,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_stability][1] ? c_server"Bale $70,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_stability][2] ? c_server"Bale $50,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_stability][3] ? c_server"Bale $85,000" : c_red"Kheyr",
		veh_info[PTS_Vehicle -1][v_pt_stability][4] ? c_server"Bale $65,000" : c_red"Kheyr");

		show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, !""scm_dialog"Gozargah Vasile Naghlie", global_string, !"Bastan", !"");
		
		if(targetid != playerid) me_action(playerid, "Be gozargah vasile naghlie negah kard");
		
		DeletePVar(playerid, "PTS_Status");
		DeletePVar(playerid, "PTS_Target");
		DeletePVar(playerid, "PTS_Vehicle");
		
		return 1;
	}

	// Ezdevaj
	if(GetPVarInt(playerid, !"married_request")) {
		targetid = GetPVarInt(playerid, !"married_request_target");
		DeletePVar(playerid, "married_request");

		if(!IsPlayerConnected(targetid)) {
			return 1;
		}

	    if(!IsPlayerInRangeOfPoint(playerid, 5.0, p_t_info[targetid][p_pos][0], p_t_info[targetid][p_pos][1], p_t_info[targetid][p_pos][2]) || GetPlayerVirtualWorld(targetid) != GetPlayerVirtualWorld(playerid)) {
	    	return 1;
	    }

		new string[128];

		format(string, sizeof(string), "Ezdevaj "c_white"%s {C8154A}va "c_white"%s {C8154A}ra tabrik migoyam.", Name(targetid), Name(playerid));
		SendClientMessageToAll(0xC8154AFF, string);

		PlayerInfo[targetid][married_account_id] = PlayerInfo[playerid][id];
		PlayerInfo[playerid][married_account_id] = PlayerInfo[targetid][id];

		update_int_sql(playerid, "u_married_account_id", PlayerInfo[playerid][married_account_id]);
		update_int_sql(targetid, "u_married_account_id", PlayerInfo[targetid][married_account_id]);
		return 1;
	}

	// Sex
	if(GetPVarInt(playerid, !"anim_sex")) {
		targetid = GetPVarInt(playerid, !"anim_sex_target");
		DeletePVar(playerid, "anim_sex");

		if(!IsPlayerConnected(targetid)) {
			return 1;
		}

	    if(!IsPlayerInRangeOfPoint(playerid, 5.0, p_t_info[targetid][p_pos][0], p_t_info[targetid][p_pos][1], p_t_info[targetid][p_pos][2]) || GetPlayerVirtualWorld(targetid) != GetPlayerVirtualWorld(playerid)) {
	    	return 1;
	    }

		ApplyAnimation(playerid, "SNM", "SPANKING_ENDW", 4.1, 0, 1, 1, 1, 1, 1);
		ApplyAnimation(targetid, "PAULNMAC", "wank_loop", 4.1, 0, 0, 0, 0, 2000, 1);

		new string[64];
		format(string, sizeof(string), "ba %s sex kard", Name(playerid));
		me_action(targetid, string);
		return 1;
	}

	// Kiss
	if(GetPVarInt(playerid, !"anim_kiss")) {
		targetid = GetPVarInt(playerid, !"anim_kiss_target");
		DeletePVar(playerid, "anim_kiss");

		if(!IsPlayerConnected(targetid)) {
			return 1;
		}
 
	    if(!IsPlayerInRangeOfPoint(playerid, 5.0, p_t_info[targetid][p_pos][0], p_t_info[targetid][p_pos][1], p_t_info[targetid][p_pos][2]) || GetPlayerVirtualWorld(targetid) != GetPlayerVirtualWorld(playerid)) {
	    	return 1;
	    }

	    SetPlayerToFacePlayer(targetid, playerid);

		// new rand = random(2);
	    // if(rand == 0) 
	    // 	ApplyAnimation(targetid,"KISSING","Grlfrd_Kiss_01",4.0,0,0,0,0,0,true);
	    // else
	    ApplyAnimation(targetid,"KISSING","Grlfrd_Kiss_02",4.0,0,0,0,0,0,true);

		new string[64];
		format(string, sizeof(string), "player %s ra boosid", Name(playerid));
		me_action(targetid, string);
		return 1;
	}

    if(!check_suggestion(playerid)) return SendError(playerid, "Shoma darhal hazer hich pishnehadi nadarid.");

    if(!IsPlayerInRangeOfPoint(playerid, 5.00, p_t_info[p_t_info[playerid][suggestion_playerid]][p_pos][0], p_t_info[p_t_info[playerid][suggestion_playerid]][p_pos][1], p_t_info[p_t_info[playerid][suggestion_playerid]][p_pos][2]) || p_t_info[playerid][p_data][1] != p_t_info[p_t_info[playerid][suggestion_playerid]][p_data][1])
	{
        clear_suggestion(p_t_info[playerid][suggestion_playerid]);
        clear_suggestion(playerid);
        pc_cmd_no(playerid);
		return SendError(playerid , "Bazikon kheyli door ast.");
	}

	switch(p_t_info[playerid][suggestion_callback])
	{
		case 0: return sellSkinSuggestion(playerid), 0;
	}

    return 1;
}

cmd:no(playerid)
{
    if(CMD_Vote_No(playerid)) return 1;

	new targetid;
	if(GetPVarInt(playerid, "WBOOK_Status")) {
		targetid = GetPVarInt(playerid, "WBOOK_Target");

		DeletePVar(playerid, "WBOOK_Status");
		DeletePVar(playerid, "WBOOK_Target");

		if(!IsPlayerConnected(targetid)) return 1;

		new string[100];
		format(string, sizeof(string), "%s pishnehad shoma ra rad kard.", Name(playerid));
		SendClientMessage(targetid, 0xEA5515FF, string);

		return 1;
	}


	// PTS

	if(GetPVarInt(playerid, !"PTS_Status")) {
		targetid = GetPVarInt(playerid, !"PTS_Target");

		DeletePVar(playerid, "PTS_Status");
		DeletePVar(playerid, "PTS_Target");
		DeletePVar(playerid, "PTS_Vehicle");
		
		if(!IsPlayerConnected(targetid)) return 1;

		new string[100];
		format(string, sizeof(string), "%s pishnehad shoma ra rad kard.", Name(playerid));
		SendClientMessage(targetid, 0xEA5515FF, string);
	}

	// Sex
	if(GetPVarInt(playerid, !"anim_sex")) {
		targetid = GetPVarInt(playerid, !"anim_sex_target");
		DeletePVar(playerid, "anim_sex");

		if(!IsPlayerConnected(targetid)) return 1;

		new string[100];
		format(string, sizeof(string), "%s pishnehad shoma ra rad kard.", Name(playerid));
		SendClientMessage(targetid, 0xEA5515FF, string);
		return 1;
	}

	// Kiss
	if(GetPVarInt(playerid, !"anim_kiss")) {
		targetid = GetPVarInt(playerid, !"anim_kiss_target");
		DeletePVar(playerid, "anim_kiss");

		if(!IsPlayerConnected(targetid)) return 1;

		new string[100];
		format(string, sizeof(string), "%s pishnehad shoma ra rad kard.", Name(playerid));
		SendClientMessage(targetid, 0xEA5515FF, string);
		return 1;
	}

	// Ezdevaj
	if(GetPVarInt(playerid, !"married_request")) {
		targetid = GetPVarInt(playerid, !"married_request_target");
		DeletePVar(playerid, "married_request");

		if(!IsPlayerConnected(targetid)) return 1;

		new string[100];
		format(string, sizeof(string), "%s pishnehad ezdevaj shoma ra rad kard.", Name(playerid));
		SendClientMessage(targetid, 0xEA5515FF, string);
		return 1;
	}

    if(!check_suggestion(playerid)) return SendError(playerid, "Shoma darhal hazer hich pishnehadi nadarid.");

    SendMes(p_t_info[playerid][suggestion_playerid], col_white, c_white"%s "c_orange_red"Pishnahad-e Shoma rad kard.", PlayerInfo[playerid][name]);
    SendMes(playerid, col_white, c_orange_red"Shoma pishnahad-e "c_white"%s"c_orange_red" rad kardid.", PlayerInfo[p_t_info[playerid][suggestion_playerid]][name]);

    switch(p_t_info[playerid][suggestion_no_callback])
	{
		case 0: noSkinSuggestion(playerid);
	}

    clear_suggestion(p_t_info[playerid][suggestion_playerid]);
    clear_suggestion(playerid);
	
    return 1;
}


///////////////////////////////////////////////////////////////////////////////////

stock sellSkinSuggestion(playerid)
{
	new targetid = p_t_info[playerid][suggestion_playerid];

	new freeSkinSlot = -1;

	for(new j = 0; j < 5; j ++)
	{
		if(PlayerInfo[playerid][temp_skin][j] == 0)
		{
			freeSkinSlot = j;
			break;
		}
	}

	if(freeSkinSlot == -1){
        SendError(playerid, "Shoma slot kafi nadarid");
        SendError(targetid, "In bazikon slot kafi nadard");
        return 1;
    }

	new price = p_t_info[playerid][suggestion_price];

	if(price > PlayerInfo[playerid][money]) {
        SendError(playerid, "Shoma pool kafi nadarid");
        SendError(targetid, "In bazikon pool kafi nadard");
        return 1;
    }

	new tId = GetPVarInt(playerid, !"sell_skin_value");

	PlayerInfo[playerid][temp_skin][freeSkinSlot] = PlayerInfo[targetid][temp_skin][tId];
	set_skin(playerid, PlayerInfo[playerid][temp_skin][freeSkinSlot]);
		
	PlayerInfo[targetid][temp_skin][tId] = 0;
	
	if(PlayerInfo[targetid][gender] == 0) set_skin(playerid, 252);
	else set_skin(targetid, 201);

	give_money(playerid, -price);
	give_money(targetid, price);

	save_temp_skin(playerid);
	save_temp_skin(targetid);

    SendInfo(targetid, "%s[%d] pishnehad "c_yellow"\"%s\""c_white" be gheymat:"c_green"$%s"c_white" ghabol kard", PlayerInfo[playerid][name], playerid,convert_money(price));

    clear_suggestion(p_t_info[playerid][suggestion_playerid]);
    clear_suggestion(playerid);

	return 1;
}

stock noSkinSuggestion(playerid)
{
    DeletePVar(playerid, "sell_skin_value");

    return 1;
}