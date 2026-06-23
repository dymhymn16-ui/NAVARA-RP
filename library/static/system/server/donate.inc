cmd:donate(playerid)
{
    show_donate(playerid);
    SendInfo(playerid, "Baraye kharid {FFD700}M-Coin{FFFFFF} mitavanid be website {3EF27D}MihanRP.IR{FFFFFF} morajee konid");
}

stock show_donate(playerid)
{
	global_string[0] = EOS;
	format(global_string, sizeof global_string,
	""c_white"Service Name:\t"c_white"Price:\n\
	"c_server"1 | "c_white"Tabdil Be Pool (Convert to Money)\t"c_green"1 M-Coin = $25,000\n\
	"c_server"2 | "c_white"Taghir Esm (Change Name)\t"c_green"30 M-Coin\n\
	"c_server"3 | "c_white"Pak Kardan Warn (Remove Warnings)\t"c_green"200 M-Coin\n\
	"c_server"4 | "c_white"Taghir Sen (Change Age)\t"c_green"50 M-Coin\n\
	"c_server"5 | "c_white"Skin Haye Kamyab (Rare Skins)\t"c_green"200 M-Coin\n\
	"c_server"6 | "c_white"Gereftan Work Book Jadid (New Work Book)\t"c_green"50 M-Coin\n\
	"c_server"7 | "c_white"Account VIP "c_server"'Gold'\t"c_green"150 M-Coin\n\
	"c_server"8 | "c_white"Roulette of Luck\t"c_green"50 M-Coin\n\
	"c_server"9 | "c_white"Kharid Accessories (Buy Accessories)\t"c_green">>\n\
	"c_server"10 | "c_white"Additional Car Slot\t"c_green"200 M-Coin\n\
	"c_server"11 | "c_white"Siri Binahayat (Infinite Hunger)\t"c_green"75 M-Coin\n\
	"c_server"12 | "c_white"Account "c_gold"Premium\t"c_green"350 M-Coin\n\
	"c_server"13 | "c_white"Sakht Family (Create Family)\t"c_green"500 M-Coin\n\
	"c_server"14 | "c_white"Taghir Jensiyat (Change Gender)\t"c_green"50 M-Coin\n\
	"c_server"15 | "c_white"Pelak Custom (Custom License Plate)\t"c_green">>\n\
	"c_server"16 | "c_white"Kharid EXP (Buy Experience)\t"c_green"20 M-Coin\n\
	"c_server"17 | "c_white"Pak Kardan Faction Punish\t"c_green"50 M-Coin\n\
	"c_server"18 | "c_white"Azad Shodan Az Zendan (Get Out of Jail)\t"c_green"100 M-Coin\n\
	"c_server"19 | "c_white"Unmute Shodan (Get Unmuted)\t"c_green"50 M-Coin\n\
	"c_server" \n\
	"c_grey"Tedad M-Coin Shoma: "c_white"%d"c_grey" M-Coin", get_player_donate(playerid));
	show_dialog(playerid, d_donate, DIALOG_STYLE_TABLIST_HEADERS, !""scm_dialog"Donate Services", global_string, !"Entekhab", !"Bastan");
	return 1;
}

stock get_player_donate(playerid)
{
	new donate_count_money = 0,
		query_string[78];
	format(query_string, sizeof(query_string),"SELECT `u_donate` FROM users WHERE u_id = '%d'", PlayerInfo[playerid][id]);
	new Cache:result = mysql_query(sql_connection, query_string);
	donate_count_money = cache_get_field_content_int(0, "u_donate", sql_connection);
	cache_delete(result);
	return donate_count_money;
}

stock dialog_donate_money(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];
    format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Tabdil Pool Bazi:\n\n\
	"c_grey"* Nerkh Tabdil: "c_green"1 M-Coin"c_grey" = "c_green"$25,000"c_grey".\n\
	"c_grey"* Meghdare M-Coin ke mikhay tabdil koni be \""c_white"Pool Bazi"c_grey"\" ro vared kon.", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_money, DIALOG_STYLE_INPUT, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_rename(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

    format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Taghir Esm:\n\n\
    "c_grey"* Price: "c_green"30 M-Coin"c_grey".\n\
    "c_grey"* Do you really want to change your \""c_white"Nick-Name"c_grey"\".", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_rename, DIALOG_STYLE_INPUT, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

callback: change_donate_name(playerid, donate_name[])
{
	new rows, fields;
	cache_get_data(rows, fields);

	if(rows)
        return dialog_donate_rename(playerid, "In nickname ghablan estefade shode.");
        
	if(SetPlayerName(playerid, donate_name) == -1)
        return dialog_donate_rename(playerid, "Bazikoni ba in name be server vasl shode.");

	give_donate(playerid, -30);

    ChangePlayerName(playerid, donate_name, "Donate");

	show_donate(playerid);

	SendAccess(playerid, "Your donation service has been successfully purchased.");
	
	return 1;
}

stock dialog_donate_warn(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

    format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Remove warning:\n\n\
	"c_grey"* Price: "c_green"200 M-Coin"c_grey".\n\
	"c_grey"* Are you sure you want to remove \""c_white"Warning"c_grey"\"?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_unwarn, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

callback:donate_unwarns(playerid)
{
	new fields,
		rows;

	cache_get_data(rows, fields);

	if(!rows) return dialog_donate_warn(playerid, "Hich hoshdari vojood nadarad ke betavanid an ra hazf konid.");
	
	new warn_id = cache_get_field_content_int(rows -1, "w_id", sql_connection);

	RunQuery("UPDATE `users_warns` SET `w_end`=NOW() WHERE `w_id`='%d'", warn_id);

	give_donate(playerid, -200);

	show_donate(playerid);

	SendAccess(playerid, "Your donation service has been successfully purchased.");
	return 1;
}

stock dialog_donate_age(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

    format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Age change:\n\n\
	"c_grey"* Price: "c_green"50 M-Coin"c_grey".\n\
	"c_grey"* Do you really want to change your \""c_white"Age"c_grey"\"?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_age, DIALOG_STYLE_INPUT, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_skin(playerid)
{
	show_dialog(playerid, d_donate_skin, DIALOG_STYLE_LIST, ""c_server"Donate Services", "\
	"c_grey"-"c_white"Kent Paul\n\
	"c_grey"-"c_white"Cesar Vialpando\n\
	"c_grey"-"c_white"Og Lock\n\
	"c_grey"-"c_white"Sean 'Sweet' Johnson\n\
	"c_grey"-"c_white"Clown\n\
	"c_grey"-"c_white"Ryder with robbery mask\n\
	"c_grey"-"c_white"Big Smoke Armored\n\
	"c_grey"* Price: "c_green"200 M-Coin", "Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_wbook(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Get a new work book:\n\n\
	"c_grey"-"c_white"Agar shoma ozv sazman haye gheyr ghanoni shodid va\n\
	"c_white"  ejaze vorod ba sazman haye ghanoni ra nadarid mitavanid work book jadid begirid.\n\
	"c_grey"* Price: "c_green"50 M-Coin"c_grey".\n\
	"c_grey"* Aya vaghean mikhay \""c_white"New Work Book"c_grey"\" ro begirid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_jobinfo, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_vipgold(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[650];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"VIP privilege "c_server"'Gold'"c_white" be shoma in fursat-ha ro midahad:\n\n\
	"c_grey"-"c_white"VIP privilege 30 Rooz\n\n\
	"c_grey"-"c_white"Taghir style raftar\n\
	"c_grey"-"c_white"Taghir style goftego\n\
	"c_grey"-"c_white"Hamisha gorsnaki\n\
	"c_grey"-"c_white"Gereftan hoghogh bishtar dar shoghl haye azad\n\
	"c_grey"-"c_white"Limit hesab banki 3 barabar mishavad\n\
	"c_grey"-"c_white"Chat VIP ba /v\n\
	"c_grey"-"c_white"Daryaft EXP Bishtar Har Saeat\n\
	"c_grey"-"c_white"Baste Shodan Khodkar Kamarband\n\
	"c_grey"-"c_white"Sod banki har saat 1.5\% afzayesh migirad\n\
	"c_grey"-"c_white"Be dalil AFK ziad, kick nmishavid\n\n\
	"c_grey"* Price: "c_green"700 M-Coin"c_grey".\n\
	"c_grey"* Aya vaghean mikhay in privilege \""c_white"VIP "c_server"'Gold'"c_grey"\" ro begirid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_vipgold, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_droul(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Cheshmha baraye roulette-e-hadseh:\n\n\
	"c_grey"-"c_white"1 cheshm mitavanad roulette-e-hadseh ro 1 bar run konad.\n\n\
	"c_grey"* Price: "c_green"50 M-Coin"c_grey".\n\
	"c_grey"* Aya vaghean mikhay \""c_white"1 cheshm roulette-e-hadseh"c_grey"\" ro begirid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_droul, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_maxveh(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Additional slot for the vehicle:\n\n\
	"c_grey"-"c_white"Gives you the right to have another vehicle.\n\n\
	"c_grey"* Price: "c_green"200 M-Coin"c_grey".\n\
	"c_grey"* Do you really want to get \""c_white"Additional slot for car"c_grey"\"?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_maxveh, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_premium(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[650];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_gold"Premium"c_white" privilege be shoma in fursat-ha ro midahad:\n\n\
	"c_grey"-"c_white"Premium privilege 30 rooz\n\n\
	"c_grey"-"c_white"Estefade az tamami ghabeliyat haye premium\n\
	"c_grey"-"c_white"Spawn kardan mashin\n\
	"c_grey"-"c_white"Avaz kardan skin khod\n\
	"c_grey"-"c_white"Flip kardan mashin\n\
	"c_grey"-"c_white"Avaz kardan hava bray khod\n\
	"c_grey"-"c_white"Nitro khodkar\n\
	"c_grey"-"c_white"Roshan kardan gabliyat dast atashin\n\
	"c_grey"-"c_white"Va digar gablyat ha... ("c_green"\"/phelp\""c_white")\n\n\
	"c_grey"* Price: "c_green"350 M-Coin"c_grey".\n\
	"c_grey"* Aya vaghean mikhay in account khod ra "c_gold"Premium"c_grey" konid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_premium, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str,"Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_gender(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Taghir Jensiyat:\n\n\
	"c_grey"* Price: "c_green"50 M-Coin"c_grey".\n\
	"c_grey"* Aya motmaen hasti ke mikhay \""c_white"Taghir Jensiyat"c_grey"\" dahid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_gender, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str, "Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_exp(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Kharid 1 EXP:\n\n\
	"c_grey"* Price: "c_green"20 M-Coin"c_grey".\n\
	"c_grey"* Aya motmaen hasti ke mikhay \""c_white"1 EXP"c_grey"\" bekharid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_exp, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str, "Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_clear_fp(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Pak kardan faction punish:\n\n\
	"c_grey"* Price: "c_green"50 M-Coin"c_grey".\n\
	"c_grey"* Aya motmaen hasti ke mikhay \""c_white"Faction Punish"c_grey"\" khod ra pak konid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_clear_fp, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str, "Taeed", "Bargasht");

	return 1;
}

show_custom_plate_dialog(playerid, const error_string[] = "") {
	
	new string[550];
	for (new i = 0; i < sizeof(CustomPelakAllowedCharacters); i++) 
	{
		if(i == 0)
			format(string, 46, "%s", CustomPelakAllowedCharacters[i]);
		else
			format(string, 46, "%s, %s", string, CustomPelakAllowedCharacters[i]);
	}

	format(string, sizeof(string), 
		""c_white"Shomare pelaki ke mikhahid\n\
		bar roye vasile naghliye shakhsi nasb konid ra vared konid\n\
		\n\
		- Estefade az in horof ha mojaz ast: %s\n\
		- Harcheghdar ke horof va addad rond tar bashad gheymat bishtari khahad dasht\n\
		- Shomare pelak shoma bayad dar ghaleb AOOOAA bashad, jayi ke A hast bayad yek harf bashad - jayi ke O hast bayad addad bashad\n\
		\n\
		- Baraye mesal: X333XX\n\
		\n\
		%s", 

	string,
	error_string);

	show_dialog(playerid, d_donate_custom_car_plate, DIALOG_STYLE_INPUT, ""c_server"Shomare pelak custom mored nazar ra vared konid",
		string,
		"Next", "Bargasht");

	return 1;
}

stock dialog_donate_unjail(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Azad shodan az zendan:\n\n\
	"c_grey"* Price: "c_green"100 M-Coin"c_grey".\n\
	"c_grey"* Aya motmaen hasti ke mikhay az \""c_white"Zendan"c_grey"\" azad shavid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_unjail, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str, "Taeed", "Bargasht");

	return 1;
}

stock dialog_donate_unmute(playerid, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Unmute Shodan:\n\n\
	"c_grey"* Price: "c_green"50 M-Coin"c_grey".\n\
	"c_grey"* Aya motmaen hasti ke mikhay \""c_white"Unmute"c_grey"\" shavid?", isnull(error) ? "" : err);

	show_dialog(playerid, d_donate_unmute, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str, "Taeed", "Bargasht");

	return 1;
}

#define ITEMS_PER_PAGE 10

new g_CurrentPage[MAX_PLAYERS];

ShowAccessoriesDialog(playerid, page) {
    new dialogString[1024], line[128];
    new startIndex = page * ITEMS_PER_PAGE;
    new endIndex = startIndex + ITEMS_PER_PAGE;
    
    if(startIndex >= MAX_ACCESSORIES) return 1;

    format(dialogString, sizeof(dialogString), "ID\tName\tPrice\n« Safe badi »\t»\t»\n« Safe gabli »\t»\t»\n");

    for (new i = startIndex; i < endIndex && i < MAX_ACCESSORIES; i++) {
        format(line, sizeof(line), "%d\t"c_white"%s\t"c_gold"%d M-Coin\n", AccessoriesInfo[i][aID], AccessoriesInfo[i][aName], ConvertToDonateCard(AccessoriesInfo[i][aPrice]));
        strcat(dialogString, line, sizeof(dialogString));
    }

    g_CurrentPage[playerid] = page;

	new header_title[50];

	format(header_title, sizeof header_title, "Accessories List (Safe %d)", g_CurrentPage[playerid]);

    show_dialog(playerid, d_donate_accessories, DIALOG_STYLE_TABLIST_HEADERS, header_title, dialogString, "Entekhab", "Bargasht");

	return 1;
}

stock ConvertToDonateCard(price) {
    return floatround(35 * floatpower(price / 1000.0, 0.5));
}

stock dialog_donate_accessories(playerid, aIDX, error[] = "")
{
    new err[150];

    format(err, sizeof err, c_orange_red"* %s\n\n", error);

    new dialog_str[350];

	format(dialog_str, sizeof dialog_str, "%s\
	"c_grey"-"c_white"Kharid Accessories:\n\n\
	"c_grey"* Name: "c_green"%s"c_grey".\n\
	"c_grey"* Price: "c_gold"%d M-Coin"c_grey".\n\
	"c_grey"* Aya motmaen ke mikhay \""c_white"%s"c_grey"\" bekharid?", isnull(error) ? "" : err, AccessoriesInfo[aIDX][aName], ConvertToDonateCard(AccessoriesInfo[aIDX][aPrice]), AccessoriesInfo[aIDX][aName]);

	show_dialog(playerid, d_donate_accessories_buy, DIALOG_STYLE_MSGBOX, ""c_server"Donate Services", dialog_str, "Taeed", "Bargasht");

	return 1;
}