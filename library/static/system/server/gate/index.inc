//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=| Mihan Role Play|=-=-=-=-=-=-=-=-=-=-=-=-=//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

/* 
    Developer: Abolfazl Hosseini (Github : @inj3ct0r & Tel: @inject3r)
    Version: 1.0.0
    File Type: pwn

    All rights to this file are reserved by Developer. Unauthorized use, reproduction, or modification of this file is strictly prohibited. 

    Copyright © 2024 Abolfazl Hosseini. All rights reserved. 
*/


#define TABLE_GATE \
	"gate"

#define MAX_GATES \
	200

#define LOOP_GATE(%0) \
	for(new %0; %0 < MAX_GATES; %0++) if (g_info[%0][exist])

// ------------------------------------------------------------------

static enum _ginfo {
	bool:exist,
	id,
	model,
	Float:position[6],
	Float:speed,
	Float:move_position[6],
	Float:open_position[6],
	back_time,
	password[32],
	Float:range,

	faction,
	family,
	vip,
	vip_status,
	house,
	
	virtual_world,
	interior,

	dynamic_object_id,
	bool:open,
	timer,

	Text3D:label,

	edit_stage
};

static g_info[MAX_GATES][_ginfo];

static s_PlayerCurrentGate[MAX_PLAYERS];

new gateTimer[MAX_PLAYERS][2],
	bool:editing_object[MAX_PLAYERS];

// ------------------------------------------------------------------

GateSystem_Init() {
	mysql_tquery(
		dbHandle, 
		"SELECT * FROM `"TABLE_GATE"`",
		"load_gates");
}

// ------------------------------------------------------------------

forward load_gates();
public load_gates() {
	new rows = cache_num_rows();
	if (!rows) {
		return 1;
	}

	new dest[200];

	for(new i; i < rows; i++) 
	{
		if (i >= (MAX_GATES - 1)) break;

		g_info[i][id] = cache_get_field_content_int(i, "id", sql_connection);
		g_info[i][model] = cache_get_field_content_int(i, "model", sql_connection);
		
		cache_get_field_content(i, "position", dest, sql_connection, sizeof dest);
		sscanf(dest, "p<,>a<f>[6]", g_info[i][position]);

		g_info[i][speed] = cache_get_field_content_float(i, "speed", sql_connection);

		cache_get_field_content(i, "move_position", dest, sql_connection, sizeof dest);
		sscanf(dest, "p<,>a<f>[6]", g_info[i][move_position]);

		cache_get_field_content(i, "open_position", dest, sql_connection, sizeof dest);
		sscanf(dest, "p<,>a<f>[6]", g_info[i][open_position]);

		g_info[i][back_time] = cache_get_field_content_int(i, "back_time", sql_connection);

		cache_get_field_content(i, "password", g_info[i][password], sql_connection, 32);

		g_info[i][range] = cache_get_field_content_float(i, "range", sql_connection);

		g_info[i][faction] = cache_get_field_content_int(i, "faction", sql_connection);

		g_info[i][family] = cache_get_field_content_int(i, "family", sql_connection);

		g_info[i][vip] = cache_get_field_content_int(i, "vip", sql_connection);

		g_info[i][vip_status] = cache_get_field_content_int(i, "vip_status", sql_connection);
	
		g_info[i][house] = cache_get_field_content_int(i, "house", sql_connection);

		g_info[i][virtual_world] = cache_get_field_content_int(i, "virtual_world", sql_connection);
		g_info[i][interior] = cache_get_field_content_int(i, "interior", sql_connection);

		g_info[i][exist] = true;

		g_info[i][open] = false;

		g_info[i][dynamic_object_id] = CreateDynamicObject(
			g_info[i][model], 
			g_info[i][position][0], g_info[i][position][1], g_info[i][position][2], 
			g_info[i][position][3], g_info[i][position][4], g_info[i][position][5], 
			.worldid = g_info[i][virtual_world], 
			.interiorid = g_info[i][interior]);

		g_info[i][label] = CreateDynamic3DTextLabel("Loading...", 0xECF0F1FF,
		g_info[i][position][0], g_info[i][position][1], g_info[i][position][2],
		10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

		UpdateGateLabel(i);
	}

	printf("[SERVER] Loaded gates: %d", rows);
	return 1;
}

stock UpdateGateLabel(g_id)
{
	new enter_label_string[250], vip_str[50];

	if(g_info[g_id][id], g_info[g_id][vip]) format(vip_str, sizeof vip_str, "{FFEC00}[VIP]");

	format(enter_label_string, sizeof enter_label_string, "%s "c_white"Gate #%d\n%s\n{FFFFFF}Dokme {3EF27D}H{FFFFFF} Baraye Baz Kardan", vip_str, g_info[g_id][id], g_info[g_id][open] ? "{2ECC71}Baz" : "{E74C3C}Baste");

	UpdateDynamic3DTextLabelText(g_info[g_id][label], 0xECF0F1FF, enter_label_string);
}

stock check_gate_pos(playerid)
{
	new ix = -1;

	LOOP_GATE(j) {
		if (g_info[j][virtual_world] != GetPlayerVirtualWorld(playerid) ||
			g_info[j][interior] != GetPlayerInterior(playerid)) continue;

		if (GetDistanceBetweenPlayerAndPos(
			playerid,
			g_info[j][open_position][0], 
		 	g_info[j][open_position][1], 
		 	g_info[j][open_position][2]) <= g_info[j][range])
		{
			ix = j;
			break;
		}
	}

	if (ix == -1){
		SendClientMessage(playerid, col_gray, ""scm_error"Bayad Be Kenar Gate Beravid.");
		return -1;
	}


	return ix;
}

// ------------------------------------------------------------------

GateSystem_OneSecTimer() {
	LOOP_GATE(i) {
		if (g_info[i][open]) {
			if (g_info[i][timer] == 1) {
				g_info[i][timer] = 0;

				CloseGate(i);
			}
			if (g_info[i][timer] > 1) {
				g_info[i][timer]--;
			}
		}
	}

	for (new i = 0; i < MAX_PLAYERS; i++) {
		if(gateTimer[i][0] == 1) {
			gateTimer[i][0] = 0;
			gateTimer[i][1] = 0;
		}

		if(gateTimer[i][0] > 1)
		{
			gateTimer[i][0]--;
		}
	}
}

// ------------------------------------------------------------------

static OpenGate(i) {
	if (!g_info[i][open]) {
		g_info[i][open] = true;

		if (g_info[i][move_position][3] != g_info[i][position][3] ||
			g_info[i][move_position][4] != g_info[i][position][4] ||
			g_info[i][move_position][5] != g_info[i][position][5]) 
		{
			RotateDynamicObject(
				g_info[i][dynamic_object_id], 
				g_info[i][move_position][3], 
				g_info[i][move_position][4], 
				g_info[i][move_position][5],
				g_info[i][speed]);
		} 
		else 
		{
			MoveDynamicObject(
				g_info[i][dynamic_object_id], 
				g_info[i][move_position][0], 
				g_info[i][move_position][1], 
				g_info[i][move_position][2], 
				g_info[i][speed], 
				g_info[i][move_position][3], 
				g_info[i][move_position][4], 
				g_info[i][move_position][5]);
		}

		foreach(new j : Player) {
			if (GetDistanceBetweenPlayerAndPos(
				j,
				g_info[i][open_position][0], 
			 	g_info[i][open_position][1], 
			 	g_info[i][open_position][2]) <= (g_info[i][range]+4.0))
			{
				PlayerPlaySound(j, 4203, 0.0, 0.0, 0.0);
			}
		}
	}

	UpdateGateLabel(i);

}

// ------------------------------------------------------------------

static CloseGate(i) {
	if (g_info[i][open]) {
		g_info[i][open] = false;

		if (g_info[i][position][3] != g_info[i][move_position][3] ||
			g_info[i][position][4] != g_info[i][move_position][4] ||
			g_info[i][position][5] != g_info[i][move_position][5]) 
		{
			RotateDynamicObject(
				g_info[i][dynamic_object_id], 
				g_info[i][position][3], 
				g_info[i][position][4], 
				g_info[i][position][5],
				g_info[i][speed]);
		} 
		else 
		{
			MoveDynamicObject(
				g_info[i][dynamic_object_id], 
				g_info[i][position][0], 
				g_info[i][position][1], 
				g_info[i][position][2], 
				g_info[i][speed], 
				g_info[i][position][3], 
				g_info[i][position][4], 
				g_info[i][position][5]);
		}
	}

	UpdateGateLabel(i);
}

// ------------------------------------------------------------------

public OnDynamicObjectMoved(objectid)
{
	LOOP_GATE(i) {
		if (g_info[i][dynamic_object_id] == objectid) {
			if (g_info[i][open]) {
				if(g_info[i][vip_status] && g_info[i][vip])
				{
					g_info[i][timer] = g_info[i][back_time];
				}
			}
			break;
		}
	}

	#if defined GateSystem_OnDynamicObjectMove
		return GateSystem_OnDynamicObjectMove(objectid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnDynamicObjectMoved
	#undef OnDynamicObjectMoved
#else
	#define _ALS_OnDynamicObjectMoved
#endif

#define OnDynamicObjectMoved GateSystem_OnDynamicObjectMove
#if defined GateSystem_OnDynamicObjectMove
	forward GateSystem_OnDynamicObjectMove(objectid);
#endif

// ------------------------------------------------------------------

stock show_gmenu(playerid, g_id)
{
	show_dialog(playerid, d_gate_panel, DIALOG_STYLE_LIST, 
           ""scm_dialog"Gate Management", 
           !""c_server"1 | "c_white"Open / Close\n\
           "c_server"2 | "c_white"Change Password ["c_green"$500,000"c_white"]\n\
           "c_server"3 | {FFEC00}[VIP] "c_white"Gate",
           "Entekhab", "Bastan");

	SetPVarInt(playerid, "gate_id", g_id);
	return 1;
}

stock show_vgmenu(playerid, g_id)
{
	new vgmenu_string[300];

	format(vgmenu_string, sizeof vgmenu_string, "[#]\tSetting\tStatus\n\
           "c_server"1 | \t"c_white"VIP Gate\t%s\n\
           "c_server"2 | \t"c_white"Family\t%s\n\
           "c_server"3 | \t"c_white"Sorat Bastan\t"c_yellow"%.2f\n\
           "c_server"4 | \t"c_white"Zaman Bastan\t"c_yellow"%d", (g_info[g_id][vip_status] ? c_green"Fa'al" : c_red"Ghyre Fa'al"), (g_info[g_id][family] ? c_green"Fa'al" : c_red"Ghyre Fa'al"), g_info[g_id][speed], g_info[g_id][back_time]);
	
	show_dialog(playerid, d_gate_vip_panel, DIALOG_STYLE_TABLIST_HEADERS, ""scm_dialog"{FFEC00}[VIP] "c_white"Gate Panel", vgmenu_string, "Entekhab", "Barghast");

	SetPVarInt(playerid, "gate_id", g_id);
	return 1;
}

stock updateGateData(g_id)
{
	new query[450],
		position_move[200],
		position_gate[200],
		position_open[200];

	format(position_move, sizeof position_move, "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", g_info[g_id][move_position][0], g_info[g_id][move_position][1], g_info[g_id][move_position][2], g_info[g_id][move_position][3], g_info[g_id][move_position][4], g_info[g_id][move_position][5]);
	format(position_gate, sizeof position_gate, "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", g_info[g_id][position][0], g_info[g_id][position][1], g_info[g_id][position][2], g_info[g_id][position][3], g_info[g_id][position][4], g_info[g_id][position][5]);
	format(position_open, sizeof position_open, "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", g_info[g_id][open_position][0], g_info[g_id][open_position][1], g_info[g_id][open_position][2], g_info[g_id][open_position][3], g_info[g_id][open_position][4], g_info[g_id][open_position][5]);

	format( query, sizeof query, "UPDATE `"TABLE_GATE"` SET `house`='%d',`speed`='%f', `back_time`='%d',`password`='%s',`range`='%f',`faction`='%d',`house`='%d',`family`='%d',`vip`='%d', `vip_status`='%d', `move_position`='%s', `position`='%s', `open_position`='%s' WHERE `id`=%d",
			g_info[g_id][house],
			g_info[g_id][speed],
			g_info[g_id][back_time],
			g_info[g_id][password],
			g_info[g_id][range],
			g_info[g_id][faction],
			g_info[g_id][house],
			g_info[g_id][family],
			g_info[g_id][vip],
			g_info[g_id][vip_status],
			position_move,
			position_gate,
			position_open,
			g_info[g_id][id]);
			
	mysql_tquery(dbHandle, query);

	UpdateGateLabel(g_id);

	return 1;
}

/////////////////////////////////////////////////////////////////////

GateSystem_Check(playerid) {

	LOOP_GATE(i) {
		if (g_info[i][virtual_world] != GetPlayerVirtualWorld(playerid) ||
			g_info[i][interior] != GetPlayerInterior(playerid)) continue;

		if (g_info[i][faction] != 0) {
			if (PlayerInfo[playerid][member] != g_info[i][faction]) continue;
		}

		if (GetDistanceBetweenPlayerAndPos(
			playerid,
			g_info[i][open_position][0], 
		 	g_info[i][open_position][1], 
		 	g_info[i][open_position][2]) <= g_info[i][range])
		{
			new fam_status = 0;

			for(new ix = 0; ix < family_count; ix ++)
			{
				if(family_info[ix][fam_house] == g_info[i][house]) 
				{
					if(PlayerInfo[playerid][family]-1 == ix && g_info[i][vip] && g_info[i][vip_status] && g_info[i][family]) fam_status = 1;
					break;
				}
			}

			if((gateTimer[playerid][0] > 0 && gateTimer[playerid][1] == i) || fam_status){

				if(g_info[i][house] == getPlayerHouseID(playerid))
				{
					show_gmenu(playerid, i);
				}else if(!g_info[i][open]){
					OpenGate(i);
				}else{
					CloseGate(i);
				}
				return 1;
			}

			if (!isnull(g_info[i][password])) {
				s_PlayerCurrentGate[playerid] = i;
				show_dialog(
					playerid, 
					d_gate, 
					DIALOG_STYLE_INPUT, 
					""scm_dialog"Gate Password", 
					"{FFFFFF}In Gate {FF0000}Password {FFFFFF}Darad:", 
					"Open", "Cancel");
			}else if(!g_info[i][open]){
				OpenGate(i);
			}else{
				CloseGate(i);
			}

			return 1;
		}
	}

	return 0;
}

// ------------------------------------------------------------------

GateSystem_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem

	switch(dialogid)
	{
		case d_gate:
		{
			if (!response) return 1;

			if(isnull(inputtext)) {
				PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
				show_dialog(playerid, d_gate, DIALOG_STYLE_INPUT, 
							""scm_dialog"Gate Password", 
							"{FFFFFF}In Gate {FF0000}Password {FFFFFF}Darad:\n\n"c_grey"* Ramz vared shode eshtebah ast!",
							"Open", "Cancel");
				return 1;
			}

			new i = s_PlayerCurrentGate[playerid];

			if(!g_info[i][exist]) return SendError(playerid, "In gate vojod nadard.");

			if (strcmp(inputtext, g_info[i][password])) {
				PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
				show_dialog(playerid, d_gate, DIALOG_STYLE_INPUT, 
							""scm_dialog"Gate Password", 
							"{FFFFFF}In Gate {FF0000}Password {FFFFFF}Darad:\n\n"c_grey"* Ramz vared shode eshtebah ast!",
							"Open", "Cancel");
				return 1;
			}

			gateTimer[playerid][0] = 20000;
			gateTimer[playerid][1] = i;

			if(g_info[i][house] == PlayerInfo[playerid][house])
			{
				show_gmenu(playerid, i);
			}else if(!g_info[i][open]){
				OpenGate(i);
			}else{
				CloseGate(i);
			}

			return 1;
		}
		case d_gate_panel:
		{
			if (!response) {
				DeletePVar(playerid, "gate_id");
				return 1;
			}

			new gate_id = GetPVarInt(playerid, "gate_id"),
				gate_string[250];

			switch(listitem)
			{
				case 0:
				{
					if(g_info[gate_id][open]) CloseGate(gate_id);
					else OpenGate(gate_id);

					DeletePVar(playerid, "gate_id");

					return 1;
				}
				case 1:
				{
					format(gate_string,sizeof gate_string, c_white"- Password fa'eli: "c_yellow"%s\n"c_white"Password jadid ra vared konid:", g_info[gate_id][password]);
					show_dialog(playerid, d_gate_password, DIALOG_STYLE_INPUT, ""scm_dialog"Taghir Ramz", gate_string, "Open", "Cancel");
				}
				case 2:
				{
					if(!g_info[gate_id][vip]) return show_dialog(playerid, d_buy_gate_vip, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services","\
						"c_grey"-"c_white"VIP Gate be shoma emkanat zir ra mide:\n\n\
						"c_grey"-"c_white"Baste shodan khodkar gate\n\
						"c_grey"-"c_white"Set kardan dastresi gate baraye 'Family' members\n\
						"c_grey"-"c_white"Tanzim kardan sorat bastane gate\n\
						"c_grey"-"c_white"Set kardan zaman baste shodan gate\n\n\
						"c_grey"* Gheymat: "c_green"500 M-Coin"c_grey".\n\
						"c_grey"* Aaya vaghan mikhahid in privilege ro kharidari konid?\""c_white"VIP Gate"c_grey"\"?", "Kharid", "Barghast");

					DeletePVar(playerid, "gate_id");
					show_vgmenu(playerid, gate_id);

					return 1;
				}
			}
		}
		case d_gate_password:
		{
			new gate_id = GetPVarInt(playerid, "gate_id");

			if (!response) {
				DeletePVar(playerid, "gate_id");
				show_gmenu(playerid, gate_id);
				
				return 1;
			}

			new gate_string[300];

			if(PlayerInfo[playerid][money] < 500000)
			{
				format(gate_string, sizeof gate_string, c_white"- Password fa'eli: "c_yellow"%s\n"c_white"Password jadid ra vared konid:\n\n"c_grey"* Shoma pool kafi nadarid.", g_info[gate_id][password]);
				show_dialog(playerid, d_gate_password, DIALOG_STYLE_INPUT, ""scm_dialog"Taghir Ramz", gate_string, "Open", "Cancel");

				return 1;
			}

			if((strlen(inputtext)< 4 || strlen(inputtext)> 24)|| is_text_invalid(inputtext))
			{
				format(gate_string, sizeof gate_string, c_white"- Password fa'eli: "c_yellow"%s\n"c_white"Password jadid ra vared konid:\n\n"c_grey"* Tool'e ramz bayad bein 4 ta 15 karakter bashad.", g_info[gate_id][password]);
				show_dialog(playerid, d_gate_password, DIALOG_STYLE_INPUT, ""scm_dialog"Taghir Ramz", gate_string, "Open", "Cancel");

				return 1;
			}

            give_money(playerid, -500000);
            insert_money_log(playerid, INVALID_PLAYER_ID, -500000, "Change Gate Password");

			format(g_info[gate_id][password], 32, inputtext);

			format(gate_string,sizeof gate_string, ""scm_sucess"Password'e Gate ba movafaghiyat taghir kard be "c_yellow"%s", g_info[gate_id][password]);
			SendClientMessage(playerid, col_white, gate_string);

			DeletePVar(playerid, "gate_id");

			updateGateData(gate_id);
		}
		case d_buy_gate_vip:
		{
			new gate_id = GetPVarInt(playerid, "gate_id");

			DeletePVar(playerid, "gate_id");

			if (!response) {
				DeletePVar(playerid, "gate_id");
				show_gmenu(playerid, gate_id);
				
				return 1;
			}

			if(get_player_donate(playerid) < 500)
			{
				show_dialog(playerid, d_buy_gate_vip, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services","\
				"c_orange_red"* Shoma donate kafi nadarid.\n\n\
				"c_grey"-"c_white"VIP Gate be shoma emkanat zir ra mide:\n\n\
				"c_grey"-"c_white"Baste shodan khodkar gate\n\
				"c_grey"-"c_white"Set kardan dastresi gate baraye 'Family' members\n\
				"c_grey"-"c_white"Tanzim kardan sorat bastane gate\n\
				"c_grey"-"c_white"Set kardan zaman baste shodan gate\n\n\
				"c_grey"* Gheymat: "c_green"500 M-Coin"c_grey".\n\
				"c_grey"* Aaya vaghan mikhahid in gate ra \""c_white"VIP Gate"c_grey"\" konid?", "Kharid", "Barghast");
				return 1;
			}

			new query_string[148];
			format(query_string, sizeof(query_string),"UPDATE `users` SET `u_donate` = `u_donate`-'500' WHERE `u_id` = '%d' LIMIT 1", PlayerInfo[playerid][id]);
			mysql_query(sql_connection, query_string);

			new gate_string[300];
			format(gate_string,sizeof gate_string, ""scm_sucess"Shoam ba movafaghiyat Gate "c_green"#%d"c_white" ra {FFEC00}[VIP] "c_white"kardid.", g_info[gate_id][id]);
			SendClientMessage(playerid, col_white, gate_string);

			g_info[gate_id][vip] = 1;

			g_info[gate_id][vip_status] = 1;

			show_vgmenu(playerid, gate_id);

			updateGateData(gate_id);
		}
		case d_gate_vip_panel:
		{
			new gate_id = GetPVarInt(playerid, "gate_id");

			if (!response) {
				DeletePVar(playerid, "gate_id");
				show_gmenu(playerid, gate_id);				
				return 1;
			}

			switch(listitem)
			{
				case 0:
				{
					if(g_info[gate_id][vip_status])
					{
						g_info[gate_id][vip_status] = 0;
					}else
					{
						g_info[gate_id][vip_status] = 1;
					}
					
					show_vgmenu(playerid, gate_id);
					updateGateData(gate_id);
				}
				case 1:
				{
					if(g_info[gate_id][family])
					{
						g_info[gate_id][family] = 0;
					}else
					{
						g_info[gate_id][family] = 1;
					}
					
					show_vgmenu(playerid, gate_id);

					updateGateData(gate_id);
				}
				case 2:
				{	
					show_dialog(playerid, da_gate_vip_speed, DIALOG_STYLE_LIST, ""scm_dialog"Sorat Bastan",

					""c_server"1 | "c_white"0.25\n\
					"c_server"2 | "c_white"0.50\n\
					"c_server"3 | "c_white"0.75\n\
					"c_server"4 | "c_white"1.0\n\
					"c_server"5 | "c_white"1.25\n\
					"c_server"6 | "c_white"1.50\n\
					"c_server"7 | "c_white"1.75\n\
					"c_server"8 | "c_white"2.0\n\
					"c_server"9 | "c_white"2.25\n\
					"c_server"10 | "c_white"2.50",

					"Entekhab",
					"Barghast");

					return 1;
				}
				case 3:
				{
					show_dialog(playerid, da_gate_vip_backtime, DIALOG_STYLE_LIST, ""scm_dialog"Zaman Bastan",

					""c_server"1 | "c_white"1 Saniye\n\
					"c_server"2 | "c_white"2 Saniye\n\
					"c_server"3 | "c_white"3 Saniye\n\
					"c_server"4 | "c_white"4 Saniye\n\
					"c_server"5 | "c_white"5 Saniye\n\
					"c_server"6 | "c_white"6 Saniye\n\
					"c_server"7 | "c_white"7 Saniye\n\
					"c_server"8 | "c_white"8 Saniye\n\
					"c_server"9 | "c_white"9 Saniye\n\
					"c_server"10 | "c_white"10 Saniye",

					"Entekhab",
					"Barghast");

					return 1;
				}
			}
		}
		case da_gate_vip_speed:
		{
			new gate_id = GetPVarInt(playerid, "gate_id");
			DeletePVar(playerid, "gate_id");

			if (!response) {
				show_vgmenu(playerid, gate_id);				
				return 1;
			}

			switch(listitem)
			{
				case 0: g_info[gate_id][speed] = 0.25;
				case 1: g_info[gate_id][speed] = 0.50;
				case 2: g_info[gate_id][speed] = 0.75;
				case 3: g_info[gate_id][speed] = 1.0;
				case 4: g_info[gate_id][speed] = 1.25;
				case 5: g_info[gate_id][speed] = 1.50;
				case 6: g_info[gate_id][speed] = 1.75;
				case 7: g_info[gate_id][speed] = 2.0;
				case 8: g_info[gate_id][speed] = 2.25;
				case 9: g_info[gate_id][speed] = 2.50;
			}

			show_vgmenu(playerid, gate_id);
			updateGateData(gate_id);
		}
		case da_gate_vip_backtime:
		{
			new gate_id = GetPVarInt(playerid, "gate_id");
			DeletePVar(playerid, "gate_id");

			if (!response) {
				show_vgmenu(playerid, gate_id);				
				return 1;
			}

			switch(listitem)
			{
				case 0: g_info[gate_id][back_time] = 1;
				case 1: g_info[gate_id][back_time] = 2;
				case 2: g_info[gate_id][back_time] = 3;
				case 3: g_info[gate_id][back_time] = 4;
				case 4: g_info[gate_id][back_time] = 5;
				case 5: g_info[gate_id][back_time] = 6;
				case 6: g_info[gate_id][back_time] = 7;
				case 7: g_info[gate_id][back_time] = 8;
				case 8: g_info[gate_id][back_time] = 9;
				case 9: g_info[gate_id][back_time] = 10;
			}

			show_vgmenu(playerid, gate_id);
			updateGateData(gate_id);
		}
		case d_sellhouse:
		{
			if(!response) return 1;
			
			new s_house_id = PlayerInfo[playerid][house],
				data[48], query[200];

			format(h_info[s_house_id][h_owner_name], MAX_PLAYER_NAME, "State Property");

			new family_id = PlayerInfo[playerid][family];

			if(family_id != 0 && h_info[s_house_id][h_family] != -1){
				family_info[family_id -1][fam_house] = -1;
				format(query, sizeof(query), "UPDATE `family` SET `fam_house`='-1' WHERE `fam_id`='%d' LIMIT 1", getPlayerFamilyID(playerid));
				mysql_query(sql_connection, query);
			}

			h_info[s_house_id][h_family] = -1;
			h_info[s_house_id][h_owner] = -1;
			h_info[s_house_id][h_closed] = 0;

			new house_price;

			if(h_info[s_house_id][h_price] <= 15000)
				house_price = h_info[s_house_id][h_price] * 7000;
			else
				house_price = h_info[s_house_id][h_price]/ 2;

			give_money(playerid, house_price);
			insert_money_log(playerid, INVALID_PLAYER_ID, house_price, "Foshosh khane be dolat");

			UpdateHouseEnterLabel(s_house_id);

			PlayerInfo[playerid][house] = -1;

			if(!h_info[s_house_id][h_vw]) DestroyDynamicMapIcon(h_info[s_house_id][h_icon_id]);
			if(!h_info[s_house_id][h_vw]) h_info[s_house_id][h_icon_id] = CreateDynamicMapIcon(h_info[s_house_id][h_pos][0], h_info[s_house_id][h_pos][1], h_info[s_house_id][h_pos][2], 31, 0, 0, 0, -1, 60.1000);

			update_int_sql(playerid, "u_house", getPlayerHouseID(playerid));
			save_house(s_house_id);

			PlayerInfo[playerid][spawnchange] = 0;
			update_int_sql(playerid, "u_spawnchange", PlayerInfo[playerid][spawnchange]);

			for(new i;i<8;i++)
			{
				h_info[s_house_id][h_improve][i] = 0;
				if(!i) format(data, sizeof(data),"%d", h_info[s_house_id][h_improve][i]);
				else format(data, sizeof(data),"%s|%d", data, h_info[s_house_id][h_improve][i]);
			}

			h_info[s_house_id][h_safe_code] = 0;

			format(query,sizeof(query),"UPDATE `houses` SET `h_ownername`='State Property', `h_owner`='-1', `h_improve` = '%s', `h_safe_code` = '0000', `h_family`='-1' WHERE `h_id` = '%d'", data, h_info[s_house_id][h_id]);
			mysql_tquery(sql_connection, query);

			LOOP_GATE(gate_id) {
				if(g_info[gate_id][house] == h_info[s_house_id][h_id])
				{
					g_info[gate_id][vip_status] = 0;
					g_info[gate_id][family] = 0;
					g_info[gate_id][vip] = 0;
					g_info[gate_id][speed] = 1.5;
					g_info[gate_id][back_time] = 5;

					format(g_info[gate_id][password], 32, "0000");

					updateGateData(gate_id);
				}
			}

			SendClientMessage(playerid, col_white, ""scm_sucess"Shoma ba movafaghiat khane khod ra be dolat forookhtid.");
		}
	}

	return 0;
}

// ------------------------------------------------------------------

static RotateDynamicObject(objectid, Float:rotX, Float:rotY, Float:rotZ, Float:Speed)
{
    new Float:X, Float:Y, Float:Z, Float:SpeedConverted = floatmul(Speed, 0.01);
    GetDynamicObjectPos(objectid, X, Y, Z);
    SetDynamicObjectPos(objectid, X, Y, floatadd(Z, 0.001));
    MoveDynamicObject(objectid, X, Y, floatsub(Z, 0.001), SpeedConverted, rotX, rotY, rotZ);
    return 1;
}

// ------------------------------------------------------------------

CMD:gate(playerid, params[]) 
{
	new 
 		ret_val = GateSystem_Check(playerid);

	if (ret_val == 0) {
		SendClientMessage(playerid, col_gray, ""scm_error"Shoma kenar gate nistid.");
		return 1;
	}
	return 1;
}

// ------------------------------------------------------------------

CMD:creategate(playerid, params[])
{
	if(check_admin_rank(playerid , 8)) return 1;

    new g_objectid, house_id, Float:g_x, Float:g_y, Float:g_z;

    if(sscanf(params, "id", g_objectid, house_id)) return SendInfo(playerid, "Enter: /creategate [objectid] [house id]");

	if(getHouseID(house_id) == -1) return SendClientMessage(playerid, col_gray, c_green"[GATE-SYSTEM] "c_red"[Khata] "c_white"In khane vojod nadard!");

    new gateid = -1;
    for(new i; i < MAX_GATES; i++) {
        if(!g_info[i][exist]) {
            gateid = i;
            break;
        }
    }
    
    if (gateid == -1) return SendClientMessage(playerid, COLOR_RED, c_green"[GATE-SYSTEM] "c_red"[Khata] "c_white"Slot kafi baraye ejad gate jadid vojod nadard.");

    GetPlayerPos(playerid, g_x, g_y, g_z);

    g_info[gateid][dynamic_object_id] = CreateDynamicObject(g_objectid, g_x+(random(4)), g_y+(random(4)), g_z + 1.0, 0.0, 0.0, 0.0);
    g_info[gateid][exist] = true;
    g_info[gateid][model] = g_objectid;
	g_info[gateid][faction] = 0;
    g_info[gateid][family] = 0;
    g_info[gateid][vip] = 0;
    g_info[gateid][vip_status] = 0;
    g_info[gateid][house] = house_id;
    g_info[gateid][speed] = 1.5;
    g_info[gateid][back_time] = 5;
	g_info[gateid][range] = 13;

	format(g_info[gateid][password], 32, "0000");

	g_info[gateid][open] = true;

    editing_object[playerid] = true;

    EditDynamicObject(playerid, g_info[gateid][dynamic_object_id]);
	SetPVarInt(playerid, !"gate_id", gateid);
    
    return 1;
}

stock insert_created_gate(playerid, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	new query[250],
		position_g[200],
		gate_id = GetPVarInt(playerid, !"gate_id");

	format(position_g, sizeof position_g, "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", fX, fY, fZ, fRotX, fRotY, fRotZ);

	if(!GetPVarInt(playerid, "step_two_gate"))
	{
		sscanf(position_g, "p<,>a<f>[6]", g_info[gate_id][position]);
		sscanf(position_g, "p<,>a<f>[3]", g_info[gate_id][open_position]);

		format(query, sizeof query, "INSERT INTO `gate` (`model`, `position`, `open_position`, `virtual_world`, `interior`) VALUES ('%d','%s','%s','%d','%d')", g_info[gate_id][model], position_g, position_g, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
		mysql_tquery(dbHandle, query);

		SendClientMessage(playerid, col_gray, c_green"[GATE-SYSTEM]"c_white" Moghe'iat baz shodan darvaze set shode, alan moghe'iat baste shodan ro set kon.");
		
		SetPVarInt(playerid, !"step_two_gate", true);
		EditDynamicObject(playerid, g_info[gate_id][dynamic_object_id]);
	}else{
		sscanf(position_g, "p<,>a<f>[6]", g_info[gate_id][move_position]);

		new _gate_id = find_last_gate();
    	g_info[gate_id][id] = _gate_id;

		updateGateData(gate_id);

		DeletePVar(playerid, "step_two_gate");

		g_info[gate_id][label] = CreateDynamic3DTextLabel("Loading...", 0xECF0F1FF,
		g_info[gate_id][position][0], g_info[gate_id][position][1], g_info[gate_id][position][2],
		10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);

		UpdateGateLabel(gate_id);

		CloseGate(gate_id);

		DeletePVar(playerid, "gate_id");

		SendClientMessage(playerid, col_gray, c_green"[GATE-SYSTEM]"c_white" Gate ba movafaghiyat ijad shod va dar database zakhire shod.");
	}

	return 1;
}

stock cancel_created_gate(playerid)
{
	new gate_id = GetPVarInt(playerid, !"gate_id");

	DestroyDynamicObject(g_info[gate_id][dynamic_object_id]);
	DestroyDynamic3DTextLabel(g_info[gate_id][label]);
	g_info[gate_id][exist] = false;
	g_info[gate_id][timer] = 0;
	g_info[gate_id][open] = false;
	
	DeletePVar(playerid, "gate_id");

	SendClientMessage(playerid, col_gray, c_green"[GATE-SYSTEM]"c_white" Sakht Gate ba movafaghiyat laghv shod.");

	return 1;
}

stock find_last_gate()
{
    new _gate_count = 0, _gate_id = 0;
    new Cache:result = mysql_query(sql_connection, "SELECT `id` FROM `gate` ORDER BY `gate`.`id` DESC LIMIT 1");
    _gate_count = cache_num_rows();
    if(_gate_count) _gate_id = cache_get_field_content_int(0, "id", sql_connection);
    cache_delete(result);
    return _gate_id;
}

// ------------------------------------------------------------------

CMD:gatespeed(playerid, params[]) {
	if(check_admin_rank(playerid , 8)) return 1;
	
	new i = check_gate_pos(playerid);

	if(i == -1) return 0;
	

	new Float:gateSpeed;
	
	if (sscanf(params, "f", gateSpeed)) 
		return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /gatespeed [speed] - 1.5");

	if (gateSpeed <= 0.0) return SendClientMessage(playerid, col_gray, ""scm_error"Speed Ra Bishtar Az 0.0 Bezanid.");

	new query[144];

	g_info[i][speed] = gateSpeed;

	format(query, 46, ""scm_sucess"Gate %d speed changed to %.2f", 
		g_info[i][id], 
		gateSpeed);

	SendClientMessage(playerid, col_gray, query);

	updateGateData(i);

	return 1;
}

// ------------------------------------------------------------------

CMD:gaterange(playerid, params[]) {
	if(check_admin_rank(playerid , 8)) return 1;
	
	new i = check_gate_pos(playerid);

	if(i == -1) return 0;

	new Float:gateRange;
	
	if (sscanf(params, "f", gateRange)) 
		return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /gaterange [range] - 13.0");

	if (gateRange <= 0.8)
		return SendClientMessage(playerid, col_gray, ""scm_error"Range Ra Bishtar Az 0.8 Bezanid.");

	new query[144];

	g_info[i][range] = gateRange;

	format(query, 46, ""scm_sucess"Gate %d range changed to %.1f", 
		g_info[i][id], 
		gateRange);

	SendClientMessage(playerid, col_gray, query);

	updateGateData(i);

	return 1;
}

// ------------------------------------------------------------------

CMD:gatebacktime(playerid, params[]) {
	
	if(check_admin_rank(playerid , 8)) return 1;
	
	new i = check_gate_pos(playerid);

	if(i == -1) return 0;

	new gateBacktime;
	
	if (sscanf(params, "d", gateBacktime)) 
		return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /gatebacktime [seconds]");

	if (gateBacktime <= 0)
		return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /gatebacktime [seconds]");

	new query[144];

	g_info[i][back_time] = gateBacktime;

	format(query, 46, ""scm_sucess"Gate %d back time changed to %d seconds", 
		g_info[i][id], 
		gateBacktime);

	SendClientMessage(playerid, col_gray, query);

	updateGateData(i);

	return 1;
}

// ------------------------------------------------------------------

CMD:gatehouse(playerid, params[]) {
	
	if(check_admin_rank(playerid , 8)) return 1;
	
	new i = check_gate_pos(playerid);

	if(i == -1) return 0;

	new house_id;
	
	if (sscanf(params, "d", house_id)) return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /gatehouse [house id]");

	if(!(0 < house_id < house_count)) return SendClientMessage(playerid, col_gray, c_green"[GATE-SYSTEM] "c_red"[Khata] "c_white"In khane vojod nadard!");

	new query[144];

	g_info[i][house] = house_id;

	format(query, 46, ""scm_sucess"Gate %d house changed to %d seconds", 
		g_info[i][id], 
		house_id);

	SendClientMessage(playerid, col_gray, query);

	updateGateData(i);

	return 1;
}

// ------------------------------------------------------------------

CMD:gatepassword(playerid, params[]) {

	if(check_admin_rank(playerid , 8)) return 1;

	new i = check_gate_pos(playerid);

	if(i == -1) return 0;

	
	new gatePassword[32];
	
	if (sscanf(params, "s[32]", gatePassword)) 
		return SendClientMessage(playerid, col_gray, ""scm_info"Enter: /gatepassword [password]");

	new query[144];

	if (!strcmp(gatePassword, "0")) 
	{
		g_info[i][password] = EOS;

		format(query, 64, ""scm_sucess"Gate %d password removed", 
			g_info[i][id]);
	}
	else 
	{
		format(g_info[i][password], 32, gatePassword);

		format(query, 64, ""scm_sucess"Gate %d password changed to %s", 
			g_info[i][id], 
			gatePassword);
	}

	SendClientMessage(playerid, col_gray, query);

	updateGateData(i);

	return 1;
}

// ------------------------------------------------------------------

CMD:deletegate(playerid, params[]) {
	if(check_admin_rank(playerid , 8)) return 1;
	
	new i = check_gate_pos(playerid);

	if(i == -1) return 0;
	
	new query[144];

	DestroyDynamicObject(g_info[i][dynamic_object_id]);
	DestroyDynamic3DTextLabel(g_info[i][label]);
	g_info[i][exist] = false;
	g_info[i][timer] = 0;
	g_info[i][open] = false;

	format(query, 46, ""scm_sucess"Gate %d deleted.", g_info[i][id]);
	SendClientMessage(playerid, col_gray, query);

	format(
		query, 
		sizeof query, 
		"DELETE FROM `"TABLE_GATE"` WHERE `id`=%d",
		g_info[i][id]);

	mysql_tquery(dbHandle, query);

	return 1;
}