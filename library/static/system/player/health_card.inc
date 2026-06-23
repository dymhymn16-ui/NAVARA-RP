#define DATE_JALALI 	false

// ------------------------------------------------------------------

#define DIALOG_GET_HEALTH_CARD 19590

#define PRICE_MONEY_GET_CART 6000

// ------------------------------------------------------------------

#if DATE_JALALI
	#if !defined _INC_JALALI_DATE
    	#include <Jalali_Date>
	#endif
#endif

// ------------------------------------------------------------------

static 
	Text: TextDrawHealthCard[7],
	PlayerText: TextDrawHealthCardPlayer[MAX_PLAYERS][3],
	bool: PlayerTextdrawsLoaded[MAX_PLAYERS],
	bool: PlayerHealthCardTextdrawOpen[MAX_PLAYERS];

static 
	BloodTypes[8][11] = {
		{"AB+"},
		{"AB-"},
		{"A+"},
		{"A-"},
		{"B+"},
		{"B-"},
		{"O+"},
		{"O-"}
	};

// static AreaSphereGetHealthCard;

// ------------------------------------------------------------------

static LoadHealthCardTextdraws() {
	TextDrawHealthCard[0] = TextDrawCreate(223.249893, 161.349960, "box");
	TextDrawLetterSize(TextDrawHealthCard[0], 0.000000, 11.500000);
	TextDrawTextSize(TextDrawHealthCard[0], 416.679016, 0.000000);
	TextDrawAlignment(TextDrawHealthCard[0], 1);
	TextDrawColor(TextDrawHealthCard[0], -1);
	TextDrawUseBox(TextDrawHealthCard[0], 1);
	TextDrawBoxColor(TextDrawHealthCard[0], 48);
	TextDrawSetShadow(TextDrawHealthCard[0], 0);
	TextDrawBackgroundColor(TextDrawHealthCard[0], 255);
	TextDrawFont(TextDrawHealthCard[0], 1);
	TextDrawSetProportional(TextDrawHealthCard[0], 1);

	TextDrawHealthCard[1] = TextDrawCreate(224.199951, 162.200012, "box");
	TextDrawLetterSize(TextDrawHealthCard[1], 0.000000, 11.299998);
	TextDrawTextSize(TextDrawHealthCard[1], 415.529296, 0.000000);
	TextDrawAlignment(TextDrawHealthCard[1], 1);
	TextDrawColor(TextDrawHealthCard[1], -1);
	TextDrawUseBox(TextDrawHealthCard[1], 1);
	TextDrawBoxColor(TextDrawHealthCard[1], -11579518);
	TextDrawSetShadow(TextDrawHealthCard[1], 0);
	TextDrawBackgroundColor(TextDrawHealthCard[1], 255);
	TextDrawFont(TextDrawHealthCard[1], 1);
	TextDrawSetProportional(TextDrawHealthCard[1], 1);

	TextDrawHealthCard[2] = TextDrawCreate(227.000000, 159.375000, "");
	TextDrawTextSize(TextDrawHealthCard[2], 34.000000, 34.000000);
	TextDrawAlignment(TextDrawHealthCard[2], 1);
	TextDrawColor(TextDrawHealthCard[2], -1);
	TextDrawSetShadow(TextDrawHealthCard[2], 0);
	TextDrawBackgroundColor(TextDrawHealthCard[2], 0);
	TextDrawFont(TextDrawHealthCard[2], 5);
	TextDrawSetProportional(TextDrawHealthCard[2], 0);
	TextDrawSetPreviewModel(TextDrawHealthCard[2], 1240);
	TextDrawSetPreviewRot(TextDrawHealthCard[2], 0.000000, 0.000000, 0.000000, 1.000000);

	TextDrawHealthCard[3] = TextDrawCreate(270.700073, 169.524978, "Cart Salamat");
	TextDrawLetterSize(TextDrawHealthCard[3], 0.400000, 1.600000);
	TextDrawTextSize(TextDrawHealthCard[3], 408.000000, 0.000000);
	TextDrawAlignment(TextDrawHealthCard[3], 1);
	TextDrawColor(TextDrawHealthCard[3], -14934785);
	TextDrawSetShadow(TextDrawHealthCard[3], 0);
	TextDrawSetOutline(TextDrawHealthCard[3], 1);
	TextDrawBackgroundColor(TextDrawHealthCard[3], 80);
	TextDrawFont(TextDrawHealthCard[3], 3);
	TextDrawSetProportional(TextDrawHealthCard[3], 1);

	TextDrawHealthCard[4] = TextDrawCreate(382.700042, 165.800018, "HUD:radar_hostpital");
	TextDrawTextSize(TextDrawHealthCard[4], 24.000000, 21.000000);
	TextDrawAlignment(TextDrawHealthCard[4], 1);
	TextDrawColor(TextDrawHealthCard[4], -1);
	TextDrawSetShadow(TextDrawHealthCard[4], 0);
	TextDrawBackgroundColor(TextDrawHealthCard[4], 255);
	TextDrawFont(TextDrawHealthCard[4], 4);
	TextDrawSetProportional(TextDrawHealthCard[4], 0);

	TextDrawHealthCard[5] = TextDrawCreate(214.850173, 249.074981, "-");
	TextDrawLetterSize(TextDrawHealthCard[5], 14.273497, 1.376250);
	TextDrawAlignment(TextDrawHealthCard[5], 1);
	TextDrawColor(TextDrawHealthCard[5], -8947713);
	TextDrawSetShadow(TextDrawHealthCard[5], 0);
	TextDrawSetOutline(TextDrawHealthCard[5], 1);
	TextDrawBackgroundColor(TextDrawHealthCard[5], 101);
	TextDrawFont(TextDrawHealthCard[5], 1);
	TextDrawSetProportional(TextDrawHealthCard[5], 1);

	TextDrawHealthCard[6] = TextDrawCreate(319.000000, 272.250000, "X Close X");
	TextDrawLetterSize(TextDrawHealthCard[6], 0.222000, 1.334999);
	TextDrawTextSize(TextDrawHealthCard[6], 13.000000, 71.000000);
	TextDrawAlignment(TextDrawHealthCard[6], 2);
	TextDrawColor(TextDrawHealthCard[6], -8355585);
	TextDrawSetShadow(TextDrawHealthCard[6], 0);
	TextDrawSetOutline(TextDrawHealthCard[6], 1);
	TextDrawBackgroundColor(TextDrawHealthCard[6], 255);
	TextDrawFont(TextDrawHealthCard[6], 2);
	TextDrawSetProportional(TextDrawHealthCard[6], 1);
	TextDrawSetSelectable(TextDrawHealthCard[6], true);
	//Total textdraws exported: 9 (6 global textdraws / 3 player textdraws) ~ 30/6/2023 ~ 3:56:58
}

// ------------------------------------------------------------------

static LoadHealthCardPlayerTextdraws(playerid) {

	PlayerTextdrawsLoaded[playerid] = true;

	TextDrawHealthCardPlayer[playerid][0] = CreatePlayerTextDraw(playerid, 230.000000, 196.125000, "Nam: ~w~Test");
	PlayerTextDrawLetterSize(playerid, TextDrawHealthCardPlayer[playerid][0], 0.352000, 1.451249);
	PlayerTextDrawTextSize(playerid, TextDrawHealthCardPlayer[playerid][0], 410.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TextDrawHealthCardPlayer[playerid][0], 1);
	PlayerTextDrawColor(playerid, TextDrawHealthCardPlayer[playerid][0], -72317697);
	PlayerTextDrawSetShadow(playerid, TextDrawHealthCardPlayer[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawHealthCardPlayer[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, TextDrawHealthCardPlayer[playerid][0], 144);
	PlayerTextDrawFont(playerid, TextDrawHealthCardPlayer[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawHealthCardPlayer[playerid][0], 1);

	TextDrawHealthCardPlayer[playerid][1] = CreatePlayerTextDraw(playerid, 230.000000, 234.625000, "Tarikhe Enghza: ~w~2023/06/30");
	PlayerTextDrawLetterSize(playerid, TextDrawHealthCardPlayer[playerid][1], 0.352000, 1.451249);
	PlayerTextDrawTextSize(playerid, TextDrawHealthCardPlayer[playerid][1], 410.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TextDrawHealthCardPlayer[playerid][1], 1);
	PlayerTextDrawColor(playerid, TextDrawHealthCardPlayer[playerid][1], -72317697);
	PlayerTextDrawSetShadow(playerid, TextDrawHealthCardPlayer[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawHealthCardPlayer[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, TextDrawHealthCardPlayer[playerid][1], 144);
	PlayerTextDrawFont(playerid, TextDrawHealthCardPlayer[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawHealthCardPlayer[playerid][1], 1);

	TextDrawHealthCardPlayer[playerid][2] = CreatePlayerTextDraw(playerid, 230.000000, 215.625000, "Grooh Khoni: ~w~O+");
	PlayerTextDrawLetterSize(playerid, TextDrawHealthCardPlayer[playerid][2], 0.352000, 1.451249);
	PlayerTextDrawTextSize(playerid, TextDrawHealthCardPlayer[playerid][2], 410.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TextDrawHealthCardPlayer[playerid][2], 1);
	PlayerTextDrawColor(playerid, TextDrawHealthCardPlayer[playerid][2], -72317697);
	PlayerTextDrawSetShadow(playerid, TextDrawHealthCardPlayer[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TextDrawHealthCardPlayer[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, TextDrawHealthCardPlayer[playerid][2], 144);
	PlayerTextDrawFont(playerid, TextDrawHealthCardPlayer[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, TextDrawHealthCardPlayer[playerid][2], 1);
	//Total textdraws exported: 9 (6 global textdraws / 3 player textdraws) ~ 30/6/2023 ~ 3:56:58
}

static DestroyHealthCardTextdraws(playerid) {
	if(PlayerTextdrawsLoaded[playerid]) {
		PlayerTextdrawsLoaded[playerid] = false;

		for(new td; td < sizeof(TextDrawHealthCardPlayer[]); td++) {
			PlayerTextDrawDestroy(playerid, TextDrawHealthCardPlayer[playerid][td]);
		}
	}
}

// ------------------------------------------------------------------

ShowPlayerHealthCardToPlayer(playerid, to_player) {
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(to_player)) {
		return 0;
	}

	new 
		string[100],
		unix_timestamp = PlayerInfo[playerid][pHealthCardExpireTime],
		year, month, day, hour, minute, second;

	if(!strcmp(PlayerInfo[playerid][pBloodType], "-")) {
		new random_blood_type = random(sizeof BloodTypes);
		format(PlayerInfo[playerid][pBloodType], 11, "%s", BloodTypes[random_blood_type]);
		format(string, sizeof(string), "UPDATE `users` SET `u_blood_type`='%s' WHERE `u_id`=%d", 
			PlayerInfo[playerid][pBloodType],
			ReturnPlayerAccountID(playerid));
		mysql_tquery(sql_connection, string);
	}

	format(string, sizeof(string), "Nam: ~w~%s", Name(playerid));
	PlayerTextDrawSetString(to_player, TextDrawHealthCardPlayer[to_player][0], string);

	format(string, sizeof(string), "Grooh Khoni: ~w~%s", PlayerInfo[playerid][pBloodType]);
	PlayerTextDrawSetString(to_player, TextDrawHealthCardPlayer[to_player][2], string);

	if(unix_timestamp == 0) {
		strcat(string, "Tarikhe Enghza: ~r~No Cart");
	} else {
		#if DATE_JALALI
		TimestampToJDate(unix_timestamp, year, month, day, hour, minute, second);
		format(string, sizeof(string), "Tarikhe Enghza:%s %d/%02d/%02d", 
			unix_timestamp < timestamp ? "~r~" : "~w~",
			year, month, day);
		#else
		TimestampToDate(unix_timestamp, year, month, day, hour, minute, second, 3);
		format(string, sizeof(string), "Tarikhe Enghza:%s %d-%02d-%02d", 
			unix_timestamp < timestamp ? "~r~" : "~w~",
			year, month, day);
		#endif
	}
	PlayerTextDrawSetString(to_player, TextDrawHealthCardPlayer[to_player][1], string);

	for(new td; td < sizeof TextDrawHealthCard; td++) {
		TextDrawShowForPlayer(to_player, TextDrawHealthCard[td]);
	}

	for(new td; td < sizeof TextDrawHealthCardPlayer[]; td++) {
		PlayerTextDrawShow(to_player, TextDrawHealthCardPlayer[to_player][td]);
	}

	SelectTextDraw(to_player, 0xFF0000FF);

	PlayerHealthCardTextdrawOpen[to_player] = true;
	return 1;
}

// ------------------------------------------------------------------

alias:card("cart");
CMD:card(playerid, params[]) {

	if(PlayerInfo[playerid][pHealthCardExpireTime] == 0) {
		SendClientMessage(playerid, col_gray, ""scm_error"Shoma Cart Salamat Nadarid");
		return 1;
	}

	new 
		targetid;

	#if defined _INC_open_mp
	HidePlayerDialog(playerid);
	#else
	show_dialog(playerid, -1, 0, " ", " ", " ", " "); // Hide dialog
	#endif

	if(sscanf(params, "r", targetid)) {
		ShowPlayerHealthCardToPlayer(playerid, playerid);
		return 1;
	}

	if(targetid == playerid) {
		ShowPlayerHealthCardToPlayer(playerid, playerid);
		return 1;
	}

	if(!IsPlayerConnected(targetid)) {
		SendClientMessage(playerid, col_gray, ""scm_error"Player not found.");
		return 1;
	}

	new 
		Float:player_x_pos, Float:player_y_pos, Float:player_z_pos;

	GetPlayerPos(playerid, player_x_pos, player_y_pos, player_z_pos);

   	if(!IsPlayerInRangeOfPoint(targetid, 3.0, player_x_pos, player_y_pos, player_z_pos)) {
   		SendClientMessage(playerid, col_gray, ""scm_error"In Bazikon Bayad Kenar Shoma Bashad.");
   		return 1;
   	}

	ShowPlayerHealthCardToPlayer(playerid, targetid);

	new string[50];
	format(string, sizeof(string), "showed health card to %s", Name(targetid));
	me_action(playerid, string);

	SetPVarInt(playerid, "pShowHealthCardTime", timestamp + 3);
	return 1;
}

// ------------------------------------------------------------------

public OnPlayerConnect(playerid)
{
	LoadHealthCardPlayerTextdraws(playerid);

	#if defined HealthCard_OnPlayerConnect
		return HealthCard_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect HealthCard_OnPlayerConnect
#if defined HealthCard_OnPlayerConnect
	forward HealthCard_OnPlayerConnect(playerid);
#endif

// ------------------------------------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	DestroyHealthCardTextdraws(playerid);

	PlayerHealthCardTextdrawOpen[playerid] = false;

	#if defined HealthCard_OnPlayerDisconnect
		return HealthCard_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect HealthCard_OnPlayerDisconnect
#if defined HealthCard_OnPlayerDisconnect
	forward HealthCard_OnPlayerDisconnect(playerid, reason);
#endif

// ------------------------------------------------------------------

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(PlayerHealthCardTextdrawOpen[playerid]) {
		if(_:clickedid == INVALID_TEXT_DRAW) {
			PlayerHealthCardTextdrawOpen[playerid] = false;

			for(new td; td < sizeof TextDrawHealthCard; td++) {
				TextDrawHideForPlayer(playerid, TextDrawHealthCard[td]);
			}

			for(new td; td < sizeof TextDrawHealthCardPlayer[]; td++) {
				PlayerTextDrawHide(playerid, TextDrawHealthCardPlayer[playerid][td]);
			}
			return 0;
		}
		if(clickedid == TextDrawHealthCard[6]) {
			PlayerHealthCardTextdrawOpen[playerid] = false;
			CancelSelectTextDraw(playerid);

			for(new td; td < sizeof TextDrawHealthCard; td++) {
				TextDrawHideForPlayer(playerid, TextDrawHealthCard[td]);
			}

			for(new td; td < sizeof TextDrawHealthCardPlayer[]; td++) {
				PlayerTextDrawHide(playerid, TextDrawHealthCardPlayer[playerid][td]);
			}
			return 0;
		}
	}
	
	#if defined HealthCard_OnPlayerClickTextDr
		return HealthCard_OnPlayerClickTextDr(playerid, clickedid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw HealthCard_OnPlayerClickTextDr
#if defined HealthCard_OnPlayerClickTextDr
	forward HealthCard_OnPlayerClickTextDr(playerid, Text:clickedid);
#endif

// ------------------------------------------------------------------

/*public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PlayerHealthCardTextdrawOpen[playerid]) {
		if(newkeys & KEY_CTRL_BACK) {
			PlayerHealthCardTextdrawOpen[playerid] = false;
			CancelSelectTextDraw(playerid);

			for(new td; td < sizeof TextDrawHealthCard; td++) {
				TextDrawHideForPlayer(playerid, TextDrawHealthCard[td]);
			}

			for(new td; td < sizeof TextDrawHealthCardPlayer[]; td++) {
				PlayerTextDrawHide(playerid, TextDrawHealthCardPlayer[playerid][td]);
			}
		}
	}

	#if defined HealthCard_OnPlayerKeyStateCha
		return HealthCard_OnPlayerKeyStateCha(playerid, newkeys, oldkeys);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange HealthCard_OnPlayerKeyStateCha
#if defined HealthCard_OnPlayerKeyStateCha
	forward HealthCard_OnPlayerKeyStateCha(playerid, newkeys, oldkeys);
#endif*/

// ------------------------------------------------------------------

HealthCardOnDialogResponse(playerid, dialogid, response, listitem)
{
	switch(dialogid) {
		case DIALOG_GET_HEALTH_CARD:
	    {
			if(!response) {
				return 1;
			}

			new 
				string[144];

			if(PlayerInfo[playerid][pHealthCardExpireTime] == 0) {
				if(PlayerInfo[playerid][money] < PRICE_MONEY_GET_CART) {
					SendClientMessage(playerid, col_gray, ""scm_error"Shoma "#PRICE_MONEY_GET_CART"$ Nadarid");
					return 1;
				}

				SendClientMessage(playerid, col_white, ""scm_sucess"Shoma Cart Salamat Daryaft Kardid! (/Cart)");
				PlayerInfo[playerid][pHealthCardExpireTime] = timestamp + (3600 * 24 * 5);

				format(string, sizeof(string), "UPDATE `users` SET `u_health_card_expire_time`='%d' WHERE `u_id`=%d", 
					PlayerInfo[playerid][pHealthCardExpireTime],
					ReturnPlayerAccountID(playerid));
				mysql_tquery(sql_connection, string);

				give_money(playerid, -PRICE_MONEY_GET_CART);
				return 1;
			}

			if(listitem == 0) {
				if(PlayerInfo[playerid][money] < 5000) {
					SendClientMessage(playerid, col_gray, ""scm_error"Shoma 5000$ Nadarid");
					return 1;
				}

				SendClientMessage(playerid, col_white, ""scm_sucess"Cart Salamat Shoma 5 Rooz Tamdid Shod.");
				PlayerInfo[playerid][pHealthCardExpireTime] = timestamp + (3600 * 24 * 5);

				format(string, sizeof(string), "UPDATE `users` SET `u_health_card_expire_time`='%d' WHERE `u_id`=%d", 
					PlayerInfo[playerid][pHealthCardExpireTime],
					ReturnPlayerAccountID(playerid));
				mysql_tquery(sql_connection, string);

				give_money(playerid, -5000);
			} 
			else if(listitem == 1) {
				if(PlayerInfo[playerid][money] < 7000) {
					SendClientMessage(playerid, col_gray, ""scm_error"Shoma 7000$ Nadarid");
					return 1;
				}

				SendClientMessage(playerid, col_white, ""scm_sucess"Cart Salamat Shoma 7 Rooz Tamdid Shod.");
				PlayerInfo[playerid][pHealthCardExpireTime] = timestamp + (3600 * 24 * 7);

				format(string, sizeof(string), "UPDATE `users` SET `u_health_card_expire_time`='%d' WHERE `u_id`=%d", 
					PlayerInfo[playerid][pHealthCardExpireTime],
					ReturnPlayerAccountID(playerid));
				mysql_tquery(sql_connection, string);

				give_money(playerid, -7000);
			}
			else if(listitem == 2) {
				if(PlayerInfo[playerid][money] < 10000) {
					SendClientMessage(playerid, col_gray, ""scm_error"Shoma 10000$ Nadarid");
					return 1;
				}

				SendClientMessage(playerid, col_white, ""scm_sucess"Cart Salamat Shoma 10 Rooz Tamdid Shod.");
				PlayerInfo[playerid][pHealthCardExpireTime] = timestamp + (3600 * 24 * 10);

				format(string, sizeof(string), "UPDATE `users` SET `u_health_card_expire_time`='%d' WHERE `u_id`=%d", 
					PlayerInfo[playerid][pHealthCardExpireTime],
					ReturnPlayerAccountID(playerid));
				mysql_tquery(sql_connection, string);

				give_money(playerid, -10000);
			}
	    	return 1;
	    }
	}

	return 0;
}

// ------------------------------------------------------------------

/*HealthCardOnPlayerEnterDynArea(playerid, areaid)
{
	if(areaid == AreaSphereGetHealthCard) {
		if(PlayerInfo[playerid][pHealthCardExpireTime] == 0) {

			show_dialog(playerid, DIALOG_GET_HEALTH_CARD, DIALOG_STYLE_MSGBOX, ""scm_dialog"Cart Salamat", "\
				"c_white"Shoma {FCE3B1}Cart Salamat "c_white"Nadarid.\
				\nAya Mikhahid Cart Daryaft Konid? [+5 Rooz Etebar] "c_light_green"("#PRICE_MONEY_GET_CART"$)", 
				"Bale", "Na");

		} else {

			show_dialog(playerid, DIALOG_GET_HEALTH_CARD, DIALOG_STYLE_TABLIST, ""scm_dialog"Cart Salamat", "\
				"c_server"[01] "c_white"Tamdid {FBD5B3}5 "c_white"Rooz\t5000$\n\
				"c_server"[02] "c_white"Tamdid {FBD5B3}7 "c_white"Rooz\t7000$\n\
				"c_server"[03] "c_white"Tamdid {FBD5B3}10 "c_white"Rooz\t10000$\n", 
				"Select", "Cancel");
		}
		return 1;
	}

	return 0;
}*/

ShowHealthCardBuyDialog(playerid)
{
	if(PlayerInfo[playerid][pHealthCardExpireTime] == 0) {

		show_dialog(playerid, DIALOG_GET_HEALTH_CARD, DIALOG_STYLE_MSGBOX, ""scm_dialog"Cart Salamat", "\
			"c_white"Shoma {FCE3B1}Cart Salamat "c_white"Nadarid.\
			\nAya Mikhahid Cart Daryaft Konid? [+5 Rooz Etebar] "c_light_green"("#PRICE_MONEY_GET_CART"$)", 
			"Bale", "Na");

	} else {

		show_dialog(playerid, DIALOG_GET_HEALTH_CARD, DIALOG_STYLE_TABLIST, ""scm_dialog"Cart Salamat", "\
			"c_server"[01] "c_white"Tamdid {FBD5B3}5 "c_white"Rooz\t5000$\n\
			"c_server"[02] "c_white"Tamdid {FBD5B3}7 "c_white"Rooz\t7000$\n\
			"c_server"[03] "c_white"Tamdid {FBD5B3}10 "c_white"Rooz\t10000$\n", 
			"Select", "Cancel");
	}
}

// ------------------------------------------------------------------

HealthCardInit()
{
	LoadHealthCardTextdraws();

	// CreateDynamic3DTextLabel("** {FBD5B3}Cart Salamat "c_white"**", col_white, -651.8350,-909.5912,1436.1736, 10.0, .testlos = 1, .worldid = -1, .interiorid = -1);
	// CreateDynamicPickup(1240, 1, -651.8350,-909.5912,1436.1736, .worldid = -1, .interiorid = -1);
	// CreateDynamicCP(-651.8350,-909.5912,1436.1736 - 1.0, 1.0, .worldid = -1, .interiorid = -1, .streamdistance = 7.0);
	// AreaSphereGetHealthCard = CreateDynamicSphere(-651.8350,-909.5912,1436.1736, 1.1, .worldid = -1, .interiorid = -1, .priority = 0);
}

// ------------------------------------------------------------------

#undef DATE_JALALI