//==============================================================================
#define MAX_INVENTORY   		20
#define MAX_ITEMS_LIST          1
#define MAX_ACCESSORIES_LIST    1
//==============================================================================
new Text:InventoryOther[36];
new Text:InventoryButton[10];
new PlayerText:InventoryInfo[MAX_PLAYERS][3];
new PlayerText:InventoryItems[MAX_PLAYERS][15];
new PlayerText:InventoryAccessories[MAX_PLAYERS][15];

new InventoryTextDrawUse[MAX_PLAYERS];
new InventoryTextDrawUseType[MAX_PLAYERS];
new InventoryTextDrawItems[MAX_PLAYERS][15];
new InventoryTextDrawAccessories[MAX_PLAYERS][15];
new InventoryTextDrawList[MAX_PLAYERS][2];
new InventoryTextDrawItemsCnt[MAX_PLAYERS][MAX_ITEMS_LIST + 1];
new InventoryTextDrawAccessoriesCnt[MAX_PLAYERS][MAX_ACCESSORIES_LIST + 1];
//==============================================================================
enum
{
	TYPE_MATERIALS, // Movad;
	TYPE_SEED, // Bazr;
	TYPE_DRUGS, // Drug;
	TYPE_MASK, // Mask;
	TYPE_MEDICINE, // Kit Komak Haye Avalie;
	TYPE_REPAIR_KIT, // Repair Kit;
	TYPE_CANISTER, // Canister;
	TYPE_BOOMBOX, // BoomBox;
	TYPE_FISHING_ROD, // Chob Mahigiri;
	TYPE_FISHING_LINE, // Khat Mahigiri;
	TYPE_FISHING_COIL, // Coil;
	TYPE_FISHING_HOOK, // Gholab;
	TYPE_FISHING_WORM, // Kerm Mahigiri;
	TYPE_FISH, // Mahi;
	TYPE_DEER, // Gosht Gavazn;
    TYPE_HOTDOG, // hotdog;
    TYPE_LINEN, // Ketan;
    TYPE_METAL, // Metal;
    TYPE_WOOD, // Chob;
    TYPE_STONE // Sang;
}
//==============================================================================
enum E_INVENTORY
{
    InvType,
    InvName[32],
    InvStringName[32],
    InvUnitName[12],
    InvMax,
    InvObject,
    Float:InvObjectPos[4]
}
//==============================================================================
new Inventory[MAX_INVENTORY][E_INVENTORY] = {
    {TYPE_MATERIALS, "Movad", "Movad", "Tedad", 500, 2358, {0.0000, -34.0000, 180.0000, 1.0000}},
    {TYPE_SEED, "Bazr", "Bazr", "Tedad", 25, 1313, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_DRUGS, "Drug", "Drug", "Tedad", 1000, 1279, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_MASK, "Mask", "Mask", "Tedad", 5, 19801, {0.0000, 0.0000, 90.0000, 0.7716}},
    {TYPE_MEDICINE, "Kit Komak Haye Avalie", "Kit Komak Haye Avalie", "Tedad", 5, 11738, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_REPAIR_KIT, "Repair Kit", "Repair Kit", "Tedad", 5, 19627, {90.0000, 0.0000, 45.0000, 1.0000}},
    {TYPE_CANISTER, "Canister", "Canister", "Tedad", 5, 1650, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_BOOMBOX, "BoomBoox", "BoomBoox", "Tedad", 1, 2226, {0.0000, 0.0000, 180.0000, 1.0000}},
    {TYPE_FISHING_ROD, "Chob Mahigiri", "Chob Mahigiri", "Tedad", 1, 18632, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_FISHING_LINE, "Khat Mahigiri", "Khat Mahigiri", "Tedad", 50, 19087, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_FISHING_COIL, "Coil", "Coil", "Tedad", 50, 933, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_FISHING_HOOK, "Gholab", "Gholab", "Tedad", 50, 18633, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_FISHING_WORM, "Kerm Mahigiri", "Kerm Mahigiri", "Tedad", 50, 1603, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_FISH, "Mahi", "Mahi", "KG", 50, 1604, {0.0000, 0.0000, 45.0000, 1.0000}},
    {TYPE_DEER, "Gosht Gavazn", "Gosht Gavazn", "KG", 50, 19847, {0.0000, -45.0000, -35.0000, 0.6999}},
    {TYPE_HOTDOG, "HotDog", "HotDog", "Tedad", 10, 2768, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_LINEN, "Ketan", "Ketan", "Tedad", 250, 857, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_METAL, "Metal", "Metal", "Tedad", 250, 2937, {0.0000, 0.0000, 0.0000, 0.6999}},
    {TYPE_WOOD, "Chob", "Chob", "Tedad", 250, 1463, {0.0000, 0.0000, 0.0000, 1.0000}},
    {TYPE_STONE, "Sang", "Sang", "Tedad", 250, 3929, {0.0000, 0.0000, 0.0000, 1.2999}}
};
//==============================================================================
ShowPlayerInventory(playerid)
{
	for(new i = 0; i < 36; i++) TextDrawShowForPlayer(playerid, InventoryOther[i]);
    for(new i = 0; i < 10; i++) TextDrawShowForPlayer(playerid, InventoryButton[i]);
    PlayerTextDrawSetPreviewModel(playerid, InventoryInfo[playerid][0], GetPlayerSkin(playerid));
    for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, InventoryInfo[playerid][i]);
    new str[24];
    format(str, sizeof(str), "%d/%d", InventoryTextDrawList[playerid][0] + 1, MAX_ITEMS_LIST + 1);
    PlayerTextDrawSetString(playerid, InventoryInfo[playerid][2], str);
    format(str, sizeof(str), "%d/%d", InventoryTextDrawList[playerid][1] + 1, MAX_ACCESSORIES_LIST + 1);
    PlayerTextDrawSetString(playerid, InventoryInfo[playerid][1], str);
    LoadPlayerItemsList(playerid, 0);
    LoadPlayerAccessoriesList(playerid, 0);
    InventoryTextDraw[playerid] = true;
    SelectTextDraw(playerid, 0x0DF690AA);

    return 1;
}
//==============================================================================
ShowPlayerInventoryInfo(playerid, idx)
{
    new max_value;
    GetPlayerMaxInventoryItems(idx, max_value);
	new bigstring[2048];
    bigstring = "";
    format(bigstring, sizeof(bigstring), "{ffffff}\
    Item Inventory: {ffffff}%s.{ffffff}\
    Tedad-e Item: {ffffff}%d ta.{ffffff} az {ffffff}%d ta.{ffffff}", Inventory[idx][InvName], PlayerInfo[playerid][pInventoryItems][idx], max_value);
    show_dialog(playerid, did_inventory_items, DIALOG_STYLE_MSGBOX, "{"#DC_MAIN"}Mohtava", bigstring, "Ba'adi", "Laghv Konid");
    InventoryUseItems[playerid] = idx;
    return 1;
}
//==============================================================================
UsePlayerInventoryItems(playerid, idx)
{
    if(PlayerInfo[playerid][pInventoryItems][idx] == 0) return SendMes(playerid, -1, "Shoma Nadarid %s.", Inventory[idx][InvStringName]);
    
	switch(Inventory[idx][InvType])
    {
        case TYPE_MATERIALS, TYPE_FISHING_ROD, TYPE_FISHING_LINE, TYPE_FISHING_COIL, TYPE_FISHING_HOOK, TYPE_FISHING_WORM, TYPE_FISH, TYPE_DEER, TYPE_LINEN, TYPE_METAL, TYPE_WOOD, TYPE_STONE: return SendError(playerid, "In item gabel estefade nist.");
        //case TYPE_SEED: return cmd_plant(playerid, "/0");
        case TYPE_DRUGS: return pc_cmd_usedrugs(playerid, "/0");
        case TYPE_MASK: return pc_cmd_mask(playerid);
		case TYPE_HOTDOG: return pc_cmd_eathotdog(playerid);
        case TYPE_MEDICINE: return pc_cmd_healme(playerid);
        case TYPE_REPAIR_KIT: return pc_cmd_repairkit(playerid);
        case TYPE_CANISTER: return pc_cmd_usecanister(playerid);
        case TYPE_BOOMBOX: return pc_cmd_boombox(playerid);
        default: return SendError(playerid, "In item gabel estefade nist.");
    }
	
    return 1;
}
//==============================================================================

SellPlayerInventoryItems(playerid, idx)
{
    if(PlayerInfo[playerid][pInventoryItems][idx] == 0) return SendMes(playerid, -1, "Shoma Nadarid %s.", Inventory[idx][InvStringName]);
	new bigstring[2048];
    bigstring = "";
    format(bigstring, sizeof(bigstring), "\
    ID player, va meghdar %s, %s ra vared konid.\n\
	Baray mesal: 5,1,10000\n\
	5 = ID player\n\
	1 = Meghdar Item\n\
	10000 = Gheymat", Inventory[idx][InvUnitName], Inventory[idx][InvStringName]);
    show_dialog(playerid, did_inventory_sell, DIALOG_STYLE_INPUT, "Hand Over", bigstring, "Ba'adi", "Laghv Konid");
	InventorySellItems[playerid] = idx;
    return 1;
}

//==============================================================================
DropPlayerInventoryItems(playerid, idx)
{
    if(PlayerInfo[playerid][pInventoryItems][idx] == 0) return SendMes(playerid, -1, "Shoma Nadarid %s.", Inventory[idx][InvStringName]);
	new __t_string[72];
	format(__t_string, sizeof(__t_string), ""scm_sucess"Shoma %d adad %s dor andakhti", PlayerInfo[playerid][pInventoryItems][idx], Inventory[idx][InvStringName]);
	SendClientMessage(playerid, col_white, __t_string);
	PlayerInfo[playerid][pInventoryItems][idx] = 0;
	GiveInventoryRealItem(playerid,idx);
    SavePlayerInventoryItems(playerid, idx);
    return 1;
}

GiveInventoryRealItem(playerid,idx)
{
    switch(idx)
	{
	    case TYPE_DRUGS:
		{
		    PlayerInfo[playerid][drugs] = PlayerInfo[playerid][pInventoryItems][TYPE_DRUGS];
			update_int_sql(playerid, "u_drugs", PlayerInfo[playerid][drugs]);
		}
	    case TYPE_MASK:
		{
		    PlayerInfo[playerid][mask] = PlayerInfo[playerid][pInventoryItems][TYPE_MASK];
			update_int_sql(playerid, "u_mask", PlayerInfo[playerid][mask]);
		}
	    case TYPE_BOOMBOX:
		{
		    PlayerInfo[playerid][boombox] = PlayerInfo[playerid][pInventoryItems][TYPE_BOOMBOX];
			update_int_sql(playerid,"u_boombox", PlayerInfo[playerid][boombox]);
		}
		case TYPE_HOTDOG:
		{
			PlayerInfo[playerid][hotdog] = PlayerInfo[playerid][pInventoryItems][TYPE_HOTDOG];
			update_int_sql(playerid,"u_hotdog", PlayerInfo[playerid][hotdog]);
		}
	    case TYPE_MEDICINE:
		{
		    PlayerInfo[playerid][aidkit] = PlayerInfo[playerid][pInventoryItems][TYPE_MEDICINE];
			update_int_sql(playerid, "u_aidkit", PlayerInfo[playerid][aidkit]);
		}
	    case TYPE_REPAIR_KIT:
		{
		    PlayerInfo[playerid][repairkit] = PlayerInfo[playerid][pInventoryItems][TYPE_REPAIR_KIT];
			update_int_sql(playerid, "u_repairkit", PlayerInfo[playerid][repairkit]);
		}
		case TYPE_CANISTER:
		{
		    PlayerInfo[playerid][canister] = PlayerInfo[playerid][pInventoryItems][TYPE_CANISTER];
			update_int_sql(playerid, "u_canister", PlayerInfo[playerid][canister]);
		}
	}
}

//==============================================================================
SavePlayerInventoryItems(playerid, idx)
{
    CheckPlayerInventoryColor(playerid);
    HidePlayerInventoryTextDraw(playerid);
	new strings[256];
    format(strings, sizeof(strings), "inventory_items_%d", idx);

	RunQuery("UPDATE `users` SET `%e` = '%d' WHERE u_id = '%d' LIMIT 1", strings, PlayerInfo[playerid][pInventoryItems][idx], PlayerInfo[playerid][id]);
    
	return 1;
}
//==============================================================================
GetPlayerMaxInventoryItems(idx, &value)
{
    value = Inventory[idx][InvMax];
    return 1;
}
//==============================================================================
LoadInventoryTextDraw()
{
    InventoryOther[0] = TextDrawCreate(403.466400, 428.318206, " ");
	TextDrawLetterSize(InventoryOther[0], 0.184400, 1.247400);
	TextDrawAlignment(InventoryOther[0], 1);
	TextDrawColor(InventoryOther[0], -1);
	TextDrawSetShadow(InventoryOther[0], 0);
	TextDrawSetOutline(InventoryOther[0], 0);
	TextDrawBackgroundColor(InventoryOther[0], 255);
	TextDrawFont(InventoryOther[0], 2);
	TextDrawSetProportional(InventoryOther[0], 1);
	TextDrawSetShadow(InventoryOther[0], 0);

	InventoryOther[1] = TextDrawCreate(338.199493, 82.362785, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[1], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[1], 161.000000, 266.310302);
	TextDrawAlignment(InventoryOther[1], 1);
	TextDrawColor(InventoryOther[1], 673720575);
	TextDrawSetShadow(InventoryOther[1], 0);
	TextDrawSetOutline(InventoryOther[1], 0);
	TextDrawBackgroundColor(InventoryOther[1], 255);
	TextDrawFont(InventoryOther[1], 4);
	TextDrawSetProportional(InventoryOther[1], 0);
	TextDrawSetShadow(InventoryOther[1], 0);

	InventoryOther[2] = TextDrawCreate(340.199493, 345.937194, "PARTICLE:headlight");
	TextDrawLetterSize(InventoryOther[2], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[2], 157.000000, -258.000000);
	TextDrawAlignment(InventoryOther[2], 1);
	TextDrawColor(InventoryOther[2], 1684300900);
	TextDrawSetShadow(InventoryOther[2], 0);
	TextDrawSetOutline(InventoryOther[2], 0);
	TextDrawBackgroundColor(InventoryOther[2], 255);
	TextDrawFont(InventoryOther[2], 4);
	TextDrawSetProportional(InventoryOther[2], 0);
	TextDrawSetShadow(InventoryOther[2], 0);

	InventoryOther[3] = TextDrawCreate(131.333099, 82.362785, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[3], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[3], 204.000000, 129.740692);
	TextDrawAlignment(InventoryOther[3], 1);
	TextDrawColor(InventoryOther[3], 673720575);
	TextDrawSetShadow(InventoryOther[3], 0);
	TextDrawSetOutline(InventoryOther[3], 0);
	TextDrawBackgroundColor(InventoryOther[3], 255);
	TextDrawFont(InventoryOther[3], 4);
	TextDrawSetProportional(InventoryOther[3], 0);
	TextDrawSetShadow(InventoryOther[3], 0);

	InventoryOther[4] = TextDrawCreate(133.266098, 209.881607, "PARTICLE:headlight");
	TextDrawLetterSize(InventoryOther[4], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[4], 200.000000, -119.000000);
	TextDrawAlignment(InventoryOther[4], 1);
	TextDrawColor(InventoryOther[4], 1684300900);
	TextDrawSetShadow(InventoryOther[4], 0);
	TextDrawSetOutline(InventoryOther[4], 0);
	TextDrawBackgroundColor(InventoryOther[4], 255);
	TextDrawFont(InventoryOther[4], 4);
	TextDrawSetProportional(InventoryOther[4], 0);
	TextDrawSetShadow(InventoryOther[4], 0);

	InventoryOther[5] = TextDrawCreate(131.432891, 82.407203, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[5], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[5], 204.070404, 17.000000);
	TextDrawAlignment(InventoryOther[5], 1);
	TextDrawColor(InventoryOther[5], 0x0DF690AA);
	TextDrawSetShadow(InventoryOther[5], 0);
	TextDrawSetOutline(InventoryOther[5], 0);
	TextDrawBackgroundColor(InventoryOther[5], 255);
	TextDrawFont(InventoryOther[5], 4);
	TextDrawSetProportional(InventoryOther[5], 0);
	TextDrawSetShadow(InventoryOther[5], 0);

	InventoryOther[6] = TextDrawCreate(130.633300, 94.436096, "PARTICLE:shad_car");
	TextDrawLetterSize(InventoryOther[6], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[6], 206.070404, 7.000000);
	TextDrawAlignment(InventoryOther[6], 1);
	TextDrawColor(InventoryOther[6], 106);
	TextDrawSetShadow(InventoryOther[6], 0);
	TextDrawSetOutline(InventoryOther[6], 0);
	TextDrawBackgroundColor(InventoryOther[6], 255);
	TextDrawFont(InventoryOther[6], 4);
	TextDrawSetProportional(InventoryOther[6], 0);
	TextDrawSetShadow(InventoryOther[6], 0);

	InventoryOther[7] = TextDrawCreate(338.332794, 82.407096, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[7], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[7], 160.970001, 17.000000);
	TextDrawAlignment(InventoryOther[7], 1);
	TextDrawColor(InventoryOther[7], 0x0DF690AA);
	TextDrawSetShadow(InventoryOther[7], 0);
	TextDrawSetOutline(InventoryOther[7], 0);
	TextDrawBackgroundColor(InventoryOther[7], 255);
	TextDrawFont(InventoryOther[7], 4);
	TextDrawSetProportional(InventoryOther[7], 0);
	TextDrawSetShadow(InventoryOther[7], 0);

	InventoryOther[8] = TextDrawCreate(337.632995, 94.436096, "PARTICLE:shad_car");
	TextDrawLetterSize(InventoryOther[8], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[8], 164.000000, 7.000000);
	TextDrawAlignment(InventoryOther[8], 1);
	TextDrawColor(InventoryOther[8], 106);
	TextDrawSetShadow(InventoryOther[8], 0);
	TextDrawSetOutline(InventoryOther[8], 0);
	TextDrawBackgroundColor(InventoryOther[8], 255);
	TextDrawFont(InventoryOther[8], 4);
	TextDrawSetProportional(InventoryOther[8], 0);
	TextDrawSetShadow(InventoryOther[8], 0);

	InventoryOther[9] = TextDrawCreate(131.332901, 215.562805, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[9], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[9], 204.000000, 133.070404);
	TextDrawAlignment(InventoryOther[9], 1);
	TextDrawColor(InventoryOther[9], 673720575);
	TextDrawSetShadow(InventoryOther[9], 0);
	TextDrawSetOutline(InventoryOther[9], 0);
	TextDrawBackgroundColor(InventoryOther[9], 255);
	TextDrawFont(InventoryOther[9], 4);
	TextDrawSetProportional(InventoryOther[9], 0);
	TextDrawSetShadow(InventoryOther[9], 0);

	InventoryOther[10] = TextDrawCreate(133.132705, 346.007385, "PARTICLE:headlight1");
	TextDrawLetterSize(InventoryOther[10], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[10], 200.000000, -128.179901);
	TextDrawAlignment(InventoryOther[10], 1);
	TextDrawColor(InventoryOther[10], 1684300900);
	TextDrawSetShadow(InventoryOther[10], 0);
	TextDrawSetOutline(InventoryOther[10], 0);
	TextDrawBackgroundColor(InventoryOther[10], 255);
	TextDrawFont(InventoryOther[10], 4);
	TextDrawSetProportional(InventoryOther[10], 0);
	TextDrawSetShadow(InventoryOther[10], 0);

	InventoryOther[11] = TextDrawCreate(137.132705, 105.292297, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[11], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[11], 17.000000, 19.000000);
	TextDrawAlignment(InventoryOther[11], 1);
	TextDrawColor(InventoryOther[11], 0x0DF690AA);
	TextDrawSetShadow(InventoryOther[11], 0);
	TextDrawSetOutline(InventoryOther[11], 0);
	TextDrawBackgroundColor(InventoryOther[11], 255);
	TextDrawFont(InventoryOther[11], 4);
	TextDrawSetProportional(InventoryOther[11], 0);
	TextDrawSetShadow(InventoryOther[11], 0);

	InventoryOther[12] = TextDrawCreate(185.766098, 106.836898, "Box");
	TextDrawLetterSize(InventoryOther[12], 0.000000, 10.726400);
	TextDrawTextSize(InventoryOther[12], 0.000000, 53.000000);
	TextDrawAlignment(InventoryOther[12], 2);
	TextDrawColor(InventoryOther[12], -1);
	TextDrawUseBox(InventoryOther[12], 1);
	TextDrawBoxColor(InventoryOther[12], 84);
	TextDrawSetShadow(InventoryOther[12], 0);
	TextDrawSetOutline(InventoryOther[12], 0);
	TextDrawBackgroundColor(InventoryOther[12], 255);
	TextDrawFont(InventoryOther[12], 1);
	TextDrawSetProportional(InventoryOther[12], 1);
	TextDrawSetShadow(InventoryOther[12], 0);

	InventoryOther[13] = TextDrawCreate(241.899002, 107.198699, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[13], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[13], 64.499801, 14.189900);
	TextDrawAlignment(InventoryOther[13], 1);
	TextDrawColor(InventoryOther[13], 842150655);
	TextDrawSetShadow(InventoryOther[13], 0);
	TextDrawSetOutline(InventoryOther[13], 0);
	TextDrawBackgroundColor(InventoryOther[13], 255);
	TextDrawFont(InventoryOther[13], 4);
	TextDrawSetProportional(InventoryOther[13], 0);
	TextDrawSetShadow(InventoryOther[13], 0);

	InventoryOther[14] = TextDrawCreate(241.899002, 123.350402, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[14], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[14], 64.499801, 14.189900);
	TextDrawAlignment(InventoryOther[14], 1);
	TextDrawColor(InventoryOther[14], 842150655);
	TextDrawSetShadow(InventoryOther[14], 0);
	TextDrawSetOutline(InventoryOther[14], 0);
	TextDrawBackgroundColor(InventoryOther[14], 255);
	TextDrawFont(InventoryOther[14], 4);
	TextDrawSetProportional(InventoryOther[14], 0);
	TextDrawSetShadow(InventoryOther[14], 0);

	InventoryOther[15] = TextDrawCreate(241.899002, 139.502304, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[15], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[15], 64.499801, 14.189900);
	TextDrawAlignment(InventoryOther[15], 1);
	TextDrawColor(InventoryOther[15], 842150655);
	TextDrawSetShadow(InventoryOther[15], 0);
	TextDrawSetOutline(InventoryOther[15], 0);
	TextDrawBackgroundColor(InventoryOther[15], 255);
	TextDrawFont(InventoryOther[15], 4);
	TextDrawSetProportional(InventoryOther[15], 0);
	TextDrawSetShadow(InventoryOther[15], 0);

	InventoryOther[16] = TextDrawCreate(241.899002, 155.653900, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[16], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[16], 64.499801, 14.189900);
	TextDrawAlignment(InventoryOther[16], 1);
	TextDrawColor(InventoryOther[16], 842150655);
	TextDrawSetShadow(InventoryOther[16], 0);
	TextDrawSetOutline(InventoryOther[16], 0);
	TextDrawBackgroundColor(InventoryOther[16], 255);
	TextDrawFont(InventoryOther[16], 4);
	TextDrawSetProportional(InventoryOther[16], 0);
	TextDrawSetShadow(InventoryOther[16], 0);

	InventoryOther[17] = TextDrawCreate(241.899002, 171.676193, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[17], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[17], 64.499801, 14.189900);
	TextDrawAlignment(InventoryOther[17], 1);
	TextDrawColor(InventoryOther[17], 842150655);
	TextDrawSetShadow(InventoryOther[17], 0);
	TextDrawSetOutline(InventoryOther[17], 0);
	TextDrawBackgroundColor(InventoryOther[17], 255);
	TextDrawFont(InventoryOther[17], 4);
	TextDrawSetProportional(InventoryOther[17], 0);
	TextDrawSetShadow(InventoryOther[17], 0);

	InventoryOther[18] = TextDrawCreate(241.899002, 188.212905, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[18], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[18], 64.499801, 14.189900);
	TextDrawAlignment(InventoryOther[18], 1);
	TextDrawColor(InventoryOther[18], 842150655);
	TextDrawSetShadow(InventoryOther[18], 0);
	TextDrawSetOutline(InventoryOther[18], 0);
	TextDrawBackgroundColor(InventoryOther[18], 255);
	TextDrawFont(InventoryOther[18], 4);
	TextDrawSetProportional(InventoryOther[18], 0);
	TextDrawSetShadow(InventoryOther[18], 0);

	InventoryOther[19] = TextDrawCreate(131.333206, 82.407203, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[19], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[19], 204.000000, 6.000000);
	TextDrawAlignment(InventoryOther[19], 1);
	TextDrawColor(InventoryOther[19], -2468722);
	TextDrawSetShadow(InventoryOther[19], 0);
	TextDrawSetOutline(InventoryOther[19], 0);
	TextDrawBackgroundColor(InventoryOther[19], 255);
	TextDrawFont(InventoryOther[19], 4);
	TextDrawSetProportional(InventoryOther[19], 0);
	TextDrawSetShadow(InventoryOther[19], 0);

	InventoryOther[20] = TextDrawCreate(338.166198, 82.407203, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[20], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[20], 161.000000, 6.000000);
	TextDrawAlignment(InventoryOther[20], 1);
	TextDrawColor(InventoryOther[20], -2468722);
	TextDrawSetShadow(InventoryOther[20], 0);
	TextDrawSetOutline(InventoryOther[20], 0);
	TextDrawBackgroundColor(InventoryOther[20], 255);
	TextDrawFont(InventoryOther[20], 4);
	TextDrawSetProportional(InventoryOther[20], 0);
	TextDrawSetShadow(InventoryOther[20], 0);

	InventoryOther[19] = TextDrawCreate(135.566497, 91.507003, "PARTICLE:lamp_shad_64");
	TextDrawLetterSize(InventoryOther[19], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[19], 124.000000, -8.979900);
	TextDrawAlignment(InventoryOther[19], 1);
	TextDrawColor(InventoryOther[19], -25601);
	TextDrawSetShadow(InventoryOther[19], 0);
	TextDrawSetOutline(InventoryOther[19], 0);
	TextDrawBackgroundColor(InventoryOther[19], 255);
	TextDrawFont(InventoryOther[19], 4);
	TextDrawSetProportional(InventoryOther[19], 0);
	TextDrawSetShadow(InventoryOther[19], 0);

	InventoryOther[20] = TextDrawCreate(374.566192, 96.484596, "PARTICLE:lamp_shad_64");
	TextDrawLetterSize(InventoryOther[20], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[20], 122.000000, -13.000000);
	TextDrawAlignment(InventoryOther[20], 1);
	TextDrawColor(InventoryOther[20], -25708);
	TextDrawSetShadow(InventoryOther[20], 0);
	TextDrawSetOutline(InventoryOther[20], 0);
	TextDrawBackgroundColor(InventoryOther[20], 255);
	TextDrawFont(InventoryOther[20], 4);
	TextDrawSetProportional(InventoryOther[20], 0);
	TextDrawSetShadow(InventoryOther[20], 0);

	InventoryOther[21] = TextDrawCreate(139.965805, 110.644096, "");
	TextDrawLetterSize(InventoryOther[21], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[21], 11.000000, 11.000000);
	TextDrawAlignment(InventoryOther[21], 1);
	TextDrawColor(InventoryOther[21], 505290495);
	TextDrawSetShadow(InventoryOther[21], 0);
	TextDrawSetOutline(InventoryOther[21], 0);
	TextDrawBackgroundColor(InventoryOther[21], 0);
	TextDrawFont(InventoryOther[21], 5);
	TextDrawSetProportional(InventoryOther[21], 0);
	TextDrawSetShadow(InventoryOther[21], 0);
	TextDrawSetPreviewModel(InventoryOther[21], 19177);
	TextDrawSetPreviewRot(InventoryOther[21], 346.000000, 0.000000, 0.000000, 0.172000);

	InventoryOther[22] = TextDrawCreate(140.833099, 107.040603, "LD_BEAT:chit");
	TextDrawLetterSize(InventoryOther[22], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[22], 9.000000, 10.000000);
	TextDrawAlignment(InventoryOther[22], 1);
	TextDrawColor(InventoryOther[22], 505290495);
	TextDrawSetShadow(InventoryOther[22], 0);
	TextDrawSetOutline(InventoryOther[22], 0);
	TextDrawBackgroundColor(InventoryOther[22], 255);
	TextDrawFont(InventoryOther[22], 4);
	TextDrawSetProportional(InventoryOther[22], 0);
	TextDrawSetShadow(InventoryOther[22], 0);

	InventoryOther[23] = TextDrawCreate(137.132705, 226.073806, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[23], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[23], 17.000000, 19.000000);
	TextDrawAlignment(InventoryOther[23], 1);
	TextDrawColor(InventoryOther[23], 0x0DF690AA);
	TextDrawSetShadow(InventoryOther[23], 0);
	TextDrawSetOutline(InventoryOther[23], 0);
	TextDrawBackgroundColor(InventoryOther[23], 255);
	TextDrawFont(InventoryOther[23], 4);
	TextDrawSetProportional(InventoryOther[23], 0);
	TextDrawSetShadow(InventoryOther[23], 0);

	InventoryOther[24] = TextDrawCreate(136.333206, 239.261993, "PARTICLE:shad_car");
	TextDrawLetterSize(InventoryOther[24], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[24], 18.889900, 8.010000);
	TextDrawAlignment(InventoryOther[24], 1);
	TextDrawColor(InventoryOther[24], 106);
	TextDrawSetShadow(InventoryOther[24], 0);
	TextDrawSetOutline(InventoryOther[24], 0);
	TextDrawBackgroundColor(InventoryOther[24], 255);
	TextDrawFont(InventoryOther[24], 4);
	TextDrawSetProportional(InventoryOther[24], 0);
	TextDrawSetShadow(InventoryOther[24], 0);

	InventoryOther[25] = TextDrawCreate(136.333206, 118.480499, "PARTICLE:shad_car");
	TextDrawLetterSize(InventoryOther[25], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[25], 18.889900, 8.010000);
	TextDrawAlignment(InventoryOther[25], 1);
	TextDrawColor(InventoryOther[25], 106);
	TextDrawSetShadow(InventoryOther[25], 0);
	TextDrawSetOutline(InventoryOther[25], 0);
	TextDrawBackgroundColor(InventoryOther[25], 255);
	TextDrawFont(InventoryOther[25], 4);
	TextDrawSetProportional(InventoryOther[25], 0);
	TextDrawSetShadow(InventoryOther[25], 0);

	InventoryOther[26] = TextDrawCreate(136.999694, 105.236701, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[26], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[26], 17.000000, 6.000000);
	TextDrawAlignment(InventoryOther[26], 1);
	TextDrawColor(InventoryOther[26], -2468749);
	TextDrawSetShadow(InventoryOther[26], 0);
	TextDrawSetOutline(InventoryOther[26], 0);
	TextDrawBackgroundColor(InventoryOther[26], 255);
	TextDrawFont(InventoryOther[26], 4);
	TextDrawSetProportional(InventoryOther[26], 0);
	TextDrawSetShadow(InventoryOther[26], 0);

	InventoryOther[27] = TextDrawCreate(146.199707, 232.248306, "OO");
	TextDrawLetterSize(InventoryOther[27], 0.250200, 0.881900);
	TextDrawAlignment(InventoryOther[27], 2);
	TextDrawColor(InventoryOther[27], 505290495);
	TextDrawSetShadow(InventoryOther[27], 0);
	TextDrawSetOutline(InventoryOther[27], 0);
	TextDrawBackgroundColor(InventoryOther[27], 72);
	TextDrawFont(InventoryOther[27], 2);
	TextDrawSetProportional(InventoryOther[27], 1);
	TextDrawSetShadow(InventoryOther[27], 0);

	InventoryOther[28] = TextDrawCreate(146.199707, 229.177505, "-");
	TextDrawLetterSize(InventoryOther[28], 0.337900, 1.445798);
	TextDrawAlignment(InventoryOther[28], 2);
	TextDrawColor(InventoryOther[28], 505290495);
	TextDrawSetShadow(InventoryOther[28], 1);
	TextDrawSetOutline(InventoryOther[28], 0);
	TextDrawBackgroundColor(InventoryOther[28], 0);
	TextDrawFont(InventoryOther[28], 2);
	TextDrawSetProportional(InventoryOther[28], 1);
	TextDrawSetShadow(InventoryOther[28], 1);

	InventoryOther[29] = TextDrawCreate(146.033096, 228.966094, "/");
	TextDrawLetterSize(InventoryOther[29], 0.939400, 0.794300);
	TextDrawAlignment(InventoryOther[29], 2);
	TextDrawColor(InventoryOther[29], 505290495);
	TextDrawSetShadow(InventoryOther[29], 0);
	TextDrawSetOutline(InventoryOther[29], 0);
	TextDrawBackgroundColor(InventoryOther[29], 72);
	TextDrawFont(InventoryOther[29], 2);
	TextDrawSetProportional(InventoryOther[29], 1);
	TextDrawSetShadow(InventoryOther[29], 0);

	InventoryOther[30] = TextDrawCreate(146.033096, 228.966094, "/");
	TextDrawLetterSize(InventoryOther[30], -0.770900, 0.757200);
	TextDrawAlignment(InventoryOther[30], 2);
	TextDrawColor(InventoryOther[30], 505290495);
	TextDrawSetShadow(InventoryOther[30], 0);
	TextDrawSetOutline(InventoryOther[30], 0);
	TextDrawBackgroundColor(InventoryOther[30], 72);
	TextDrawFont(InventoryOther[30], 2);
	TextDrawSetProportional(InventoryOther[30], 1);
	TextDrawSetShadow(InventoryOther[30], 0);

	InventoryOther[31] = TextDrawCreate(136.999694, 225.862594, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[31], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[31], 17.000000, 6.000000);
	TextDrawAlignment(InventoryOther[31], 1);
	TextDrawColor(InventoryOther[31], -2468689);
	TextDrawSetShadow(InventoryOther[31], 0);
	TextDrawSetOutline(InventoryOther[31], 0);
	TextDrawBackgroundColor(InventoryOther[31], 255);
	TextDrawFont(InventoryOther[31], 4);
	TextDrawSetProportional(InventoryOther[31], 0);
	TextDrawSetShadow(InventoryOther[31], 0);

	InventoryOther[32] = TextDrawCreate(344.465911, 105.262603, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[32], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[32], 17.000000, 19.000000);
	TextDrawAlignment(InventoryOther[32], 1);
	TextDrawColor(InventoryOther[32], 0x0DF690AA);
	TextDrawSetShadow(InventoryOther[32], 0);
	TextDrawSetOutline(InventoryOther[32], 0);
	TextDrawBackgroundColor(InventoryOther[32], 255);
	TextDrawFont(InventoryOther[32], 4);
	TextDrawSetProportional(InventoryOther[32], 0);
	TextDrawSetShadow(InventoryOther[32], 0);

	InventoryOther[33] = TextDrawCreate(343.666412, 118.450897, "PARTICLE:shad_car");
	TextDrawLetterSize(InventoryOther[33], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[33], 18.889900, 8.010000);
	TextDrawAlignment(InventoryOther[33], 1);
	TextDrawColor(InventoryOther[33], 106);
	TextDrawSetShadow(InventoryOther[33], 0);
	TextDrawSetOutline(InventoryOther[33], 0);
	TextDrawBackgroundColor(InventoryOther[33], 255);
	TextDrawFont(InventoryOther[33], 4);
	TextDrawSetProportional(InventoryOther[33], 0);
	TextDrawSetShadow(InventoryOther[33], 0);

	InventoryOther[34] = TextDrawCreate(344.333007, 105.236701, "LD_SPAC:white");
	TextDrawLetterSize(InventoryOther[34], 0.000000, 0.000000);
	TextDrawTextSize(InventoryOther[34], 17.000000, 6.000000);
	TextDrawAlignment(InventoryOther[34], 1);
	TextDrawColor(InventoryOther[34], -2468749);
	TextDrawSetShadow(InventoryOther[34], 0);
	TextDrawSetOutline(InventoryOther[34], 0);
	TextDrawBackgroundColor(InventoryOther[34], 255);
	TextDrawFont(InventoryOther[34], 4);
	TextDrawSetProportional(InventoryOther[34], 0);
	TextDrawSetShadow(InventoryOther[34], 0);

	InventoryOther[35] = TextDrawCreate(353.966491, 101.443901, "::");
	TextDrawLetterSize(InventoryOther[35], 0.542100, 2.383300);
	TextDrawAlignment(InventoryOther[35], 2);
	TextDrawColor(InventoryOther[35], 505290495);
	TextDrawSetShadow(InventoryOther[35], 0);
	TextDrawSetOutline(InventoryOther[35], 0);
	TextDrawBackgroundColor(InventoryOther[35], 72);
	TextDrawFont(InventoryOther[35], 2);
	TextDrawSetProportional(InventoryOther[35], 1);
	TextDrawSetShadow(InventoryOther[35], 0);

	InventoryButton[0] = TextDrawCreate(275.099792, 107.406600, "USE");
	TextDrawLetterSize(InventoryButton[0], 0.313600, 1.412700);
	TextDrawTextSize(InventoryButton[0], 12.00000, 65.000000);
	TextDrawAlignment(InventoryButton[0], 2);
	TextDrawColor(InventoryButton[0], -1);
	TextDrawSetShadow(InventoryButton[0], 0);
	TextDrawSetOutline(InventoryButton[0], 0);
	TextDrawBackgroundColor(InventoryButton[0], 255);
	TextDrawFont(InventoryButton[0], 1);
	TextDrawSetProportional(InventoryButton[0], 1);
	TextDrawSetShadow(InventoryButton[0], 0);
	TextDrawSetSelectable(InventoryButton[0], true);

	InventoryButton[1] = TextDrawCreate(275.099792, 123.799697, "INFO");
	TextDrawLetterSize(InventoryButton[1], 0.313600, 1.412700);
	TextDrawTextSize(InventoryButton[1], 12.30000, 65.000000);
	TextDrawAlignment(InventoryButton[1], 2);
	TextDrawColor(InventoryButton[1], -1);
	TextDrawSetShadow(InventoryButton[1], 0);
	TextDrawSetOutline(InventoryButton[1], 0);
	TextDrawBackgroundColor(InventoryButton[1], 255);
	TextDrawFont(InventoryButton[1], 1);
	TextDrawSetProportional(InventoryButton[1], 1);
	TextDrawSetShadow(InventoryButton[1], 0);
	TextDrawSetSelectable(InventoryButton[1], true);

	InventoryButton[2] = TextDrawCreate(275.099792, 140.106994, "SELL / GIVE");
	TextDrawLetterSize(InventoryButton[2], 0.313600, 1.412700);
	TextDrawTextSize(InventoryButton[2], 12.60000, 65.000000);
	TextDrawAlignment(InventoryButton[2], 2);
	TextDrawColor(InventoryButton[2], -1);
	TextDrawSetShadow(InventoryButton[2], 0);
	TextDrawSetOutline(InventoryButton[2], 0);
	TextDrawBackgroundColor(InventoryButton[2], 255);
	TextDrawFont(InventoryButton[2], 1);
	TextDrawSetProportional(InventoryButton[2], 1);
	TextDrawSetShadow(InventoryButton[2], 0);
	TextDrawSetSelectable(InventoryButton[2], true);

	InventoryButton[3] = TextDrawCreate(275.099792, 156.314300, "DROP");
	TextDrawLetterSize(InventoryButton[3], 0.313600, 1.412700);
	TextDrawTextSize(InventoryButton[3], 12.90000, 65.000000);
	TextDrawAlignment(InventoryButton[3], 2);
	TextDrawColor(InventoryButton[3], -1);
	TextDrawSetShadow(InventoryButton[3], 0);
	TextDrawSetOutline(InventoryButton[3], 0);
	TextDrawBackgroundColor(InventoryButton[3], 255);
	TextDrawFont(InventoryButton[3], 1);
	TextDrawSetProportional(InventoryButton[3], 1);
	TextDrawSetShadow(InventoryButton[3], 0);
	TextDrawSetSelectable(InventoryButton[3], true);

	InventoryButton[4] = TextDrawCreate(275.099792, 172.022003, "CLOTHES");
	TextDrawLetterSize(InventoryButton[4], 0.313600, 1.412700);
	TextDrawTextSize(InventoryButton[4], 13.30000, 65.000000);
	TextDrawAlignment(InventoryButton[4], 2);
	TextDrawColor(InventoryButton[4], -1);
	TextDrawSetShadow(InventoryButton[4], 0);
	TextDrawSetOutline(InventoryButton[4], 0);
	TextDrawBackgroundColor(InventoryButton[4], 255);
	TextDrawFont(InventoryButton[4], 1);
	TextDrawSetProportional(InventoryButton[4], 1);
	TextDrawSetShadow(InventoryButton[4], 0);
	TextDrawSetSelectable(InventoryButton[4], true);

	InventoryButton[5] = TextDrawCreate(275.099792, 188.458892, "EXIT");
	TextDrawLetterSize(InventoryButton[5], 0.313600, 1.412700);
	TextDrawTextSize(InventoryButton[5], 13.60000, 65.000000);
	TextDrawAlignment(InventoryButton[5], 2);
	TextDrawColor(InventoryButton[5], -1);
	TextDrawSetShadow(InventoryButton[5], 0);
	TextDrawSetOutline(InventoryButton[5], 0);
	TextDrawBackgroundColor(InventoryButton[5], 255);
	TextDrawFont(InventoryButton[5], 1);
	TextDrawSetProportional(InventoryButton[5], 1);
	TextDrawSetShadow(InventoryButton[5], 0);
	TextDrawSetSelectable(InventoryButton[5], true);

	InventoryButton[6] = TextDrawCreate(139.932708, 248.517913, "");
	TextDrawLetterSize(InventoryButton[6], 0.000000, 0.000000);
	TextDrawTextSize(InventoryButton[6], 11.000000, 23.000000);
	TextDrawAlignment(InventoryButton[6], 1);
	TextDrawColor(InventoryButton[6], -1);
	TextDrawSetShadow(InventoryButton[6], 0);
	TextDrawSetOutline(InventoryButton[6], 0);
	TextDrawBackgroundColor(InventoryButton[6], 0);
	TextDrawFont(InventoryButton[6], 5);
	TextDrawSetProportional(InventoryButton[6], 0);
	TextDrawSetShadow(InventoryButton[6], 0);
	TextDrawSetPreviewModel(InventoryButton[6], 19177);
	TextDrawSetPreviewRot(InventoryButton[6], 15.000000, 0.000000, 0.000000, 0.172054);
	TextDrawSetSelectable(InventoryButton[6], true);

	InventoryButton[7] = TextDrawCreate(139.932708, 309.095703, "");
	TextDrawLetterSize(InventoryButton[7], 0.000000, 0.000000);
	TextDrawTextSize(InventoryButton[7], 11.000000, 23.000000);
	TextDrawAlignment(InventoryButton[7], 1);
	TextDrawColor(InventoryButton[7], -1);
	TextDrawSetShadow(InventoryButton[7], 0);
	TextDrawSetOutline(InventoryButton[7], 0);
	TextDrawBackgroundColor(InventoryButton[7], 0);
	TextDrawFont(InventoryButton[7], 5);
	TextDrawSetProportional(InventoryButton[7], 0);
	TextDrawSetShadow(InventoryButton[7], 0);
	TextDrawSetPreviewModel(InventoryButton[7], 19177);
	TextDrawSetPreviewRot(InventoryButton[7], 163.000000, 0.000000, 0.000000, 0.172054);
	TextDrawSetSelectable(InventoryButton[7], true);

	InventoryButton[8] = TextDrawCreate(347.999359, 304.995452, "");
	TextDrawLetterSize(InventoryButton[8], 0.000000, 0.000000);
	TextDrawTextSize(InventoryButton[8], 11.000000, 23.000000);
	TextDrawAlignment(InventoryButton[8], 1);
	TextDrawColor(InventoryButton[8], -1);
	TextDrawSetShadow(InventoryButton[8], 0);
	TextDrawSetOutline(InventoryButton[8], 0);
	TextDrawBackgroundColor(InventoryButton[8], 0);
	TextDrawFont(InventoryButton[8], 5);
	TextDrawSetProportional(InventoryButton[8], 0);
	TextDrawSetShadow(InventoryButton[8], 0);
	TextDrawSetPreviewModel(InventoryButton[8], 19177);
	TextDrawSetPreviewRot(InventoryButton[8], 163.000000, 0.000000, 0.000000, 0.172054);
	TextDrawSetSelectable(InventoryButton[8], true);

	InventoryButton[9] = TextDrawCreate(347.932800, 126.977180, "");
	TextDrawLetterSize(InventoryButton[9], 0.000000, 0.000000);
	TextDrawTextSize(InventoryButton[9], 11.000000, 23.000000);
	TextDrawAlignment(InventoryButton[9], 1);
	TextDrawColor(InventoryButton[9], -1);
	TextDrawSetShadow(InventoryButton[9], 0);
	TextDrawSetOutline(InventoryButton[9], 0);
	TextDrawBackgroundColor(InventoryButton[9], 0);
	TextDrawFont(InventoryButton[9], 5);
	TextDrawSetProportional(InventoryButton[9], 0);
	TextDrawSetShadow(InventoryButton[9], 0);
	TextDrawSetPreviewModel(InventoryButton[9], 19177);
	TextDrawSetPreviewRot(InventoryButton[9], 15.000000, 0.000000, 0.000000, 0.172054);
	TextDrawSetSelectable(InventoryButton[9], true);
    return 1;
}
//==============================================================================
LoadPlayerInventoryTextDraw(playerid)
{
	InventoryInfo[playerid][0] = CreatePlayerTextDraw(playerid, 140.666198, 107.939796, "");
	PlayerTextDrawLetterSize(playerid, InventoryInfo[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryInfo[playerid][0], 88.000000, 96.000000);
	PlayerTextDrawAlignment(playerid, InventoryInfo[playerid][0], 1);
	PlayerTextDrawColor(playerid, InventoryInfo[playerid][0], -1061109505);
	PlayerTextDrawSetShadow(playerid, InventoryInfo[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, InventoryInfo[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryInfo[playerid][0], 0);
	PlayerTextDrawFont(playerid, InventoryInfo[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, InventoryInfo[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, InventoryInfo[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryInfo[playerid][0], 0);
	PlayerTextDrawSetPreviewRot(playerid, InventoryInfo[playerid][0], 352.000000, 0.000000, 336.000000, 0.969600);

	InventoryInfo[playerid][1] = CreatePlayerTextDraw(playerid, 145.266601, 282.074005, "1");
	PlayerTextDrawLetterSize(playerid, InventoryInfo[playerid][1], 0.317600, 1.541900);
	PlayerTextDrawAlignment(playerid, InventoryInfo[playerid][1], 2);
	PlayerTextDrawColor(playerid, InventoryInfo[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, InventoryInfo[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, InventoryInfo[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryInfo[playerid][1], 255);
	PlayerTextDrawFont(playerid, InventoryInfo[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, InventoryInfo[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, InventoryInfo[playerid][1], 0);

	InventoryInfo[playerid][2] = CreatePlayerTextDraw(playerid, 353.566711, 215.918395, "2");
	PlayerTextDrawLetterSize(playerid, InventoryInfo[playerid][2], 0.317600, 1.541900);
	PlayerTextDrawAlignment(playerid, InventoryInfo[playerid][2], 2);
	PlayerTextDrawColor(playerid, InventoryInfo[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, InventoryInfo[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, InventoryInfo[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryInfo[playerid][2], 255);
	PlayerTextDrawFont(playerid, InventoryInfo[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, InventoryInfo[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, InventoryInfo[playerid][2], 0);

	InventoryItems[playerid][0] = CreatePlayerTextDraw(playerid, 365.464904, 105.054901, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][0], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][0], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][0], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][0], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][0], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][0], true);

	InventoryItems[playerid][1] = CreatePlayerTextDraw(playerid, 365.464904, 151.902694, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][1], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][1], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][1], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][1], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][1], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][1], true);

	InventoryItems[playerid][2] = CreatePlayerTextDraw(playerid, 365.464904, 199.436004, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][2], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][2], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][2], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][2], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][2], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][2], true);

	InventoryItems[playerid][3] = CreatePlayerTextDraw(playerid, 365.798187, 246.987594, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][3], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][3], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][3], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][3], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][3], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][3], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][3], true);

	InventoryItems[playerid][4] = CreatePlayerTextDraw(playerid, 365.798187, 294.435607, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][4], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][4], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][4], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][4], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][4], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][4], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][4], true);

	InventoryItems[playerid][5] = CreatePlayerTextDraw(playerid, 407.764801, 105.054901, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][5], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][5], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][5], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][5], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][5], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][5], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][5], true);

	InventoryItems[playerid][6] = CreatePlayerTextDraw(playerid, 407.764801, 151.902694, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][6], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][6], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][6], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][6], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][6], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][6], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][6], true);

	InventoryItems[playerid][7] = CreatePlayerTextDraw(playerid, 407.764801, 199.436004, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][7], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][7], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][7], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][7], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][7], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][7], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][7], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][7], true);

	InventoryItems[playerid][8] = CreatePlayerTextDraw(playerid, 408.098205, 246.987594, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][8], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][8], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][8], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][8], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][8], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][8], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][8], true);

	InventoryItems[playerid][9] = CreatePlayerTextDraw(playerid, 408.098205, 294.435607, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][9], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][9], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][9], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][9], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][9], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][9], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][9], true);

	InventoryItems[playerid][10] = CreatePlayerTextDraw(playerid, 450.331512, 105.054901, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][10], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][10], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][10], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][10], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][10], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][10], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][10], true);

	InventoryItems[playerid][11] = CreatePlayerTextDraw(playerid, 450.331512, 151.902694, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][11], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][11], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][11], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][11], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][11], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][11], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][11], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][11], true);

	InventoryItems[playerid][12] = CreatePlayerTextDraw(playerid, 450.331512, 199.436004, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][12], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][12], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][12], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][12], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][12], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][12], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][12], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][12], true);

	InventoryItems[playerid][13] = CreatePlayerTextDraw(playerid, 450.664794, 246.987594, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][13], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][13], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][13], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][13], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][13], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][13], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][13], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][13], true);

	InventoryItems[playerid][14] = CreatePlayerTextDraw(playerid, 450.664794, 294.435607, "");
	PlayerTextDrawLetterSize(playerid, InventoryItems[playerid][14], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryItems[playerid][14], 38.520000, 42.590000);
	PlayerTextDrawAlignment(playerid, InventoryItems[playerid][14], 1);
	PlayerTextDrawColor(playerid, InventoryItems[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, InventoryItems[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryItems[playerid][14], 76);
	PlayerTextDrawFont(playerid, InventoryItems[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, InventoryItems[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, InventoryItems[playerid][14], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][14], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][14], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryItems[playerid][14], true);

	InventoryAccessories[playerid][0] = CreatePlayerTextDraw(playerid, 157.932693, 225.617904, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][0], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][0], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][0], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][0], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][0], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][0], true);

	InventoryAccessories[playerid][1] = CreatePlayerTextDraw(playerid, 191.766098, 225.617904, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][1], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][1], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][1], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][1], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][1], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][1], true);

	InventoryAccessories[playerid][2] = CreatePlayerTextDraw(playerid, 225.765701, 225.617904, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][2], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][2], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][2], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][2], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][2], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][2], true);

	InventoryAccessories[playerid][3] = CreatePlayerTextDraw(playerid, 259.732086, 225.617904, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][3], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][3], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][3], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][3], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][3], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][3], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][3], true);

	InventoryAccessories[playerid][4] = CreatePlayerTextDraw(playerid, 293.731903, 225.617904, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][4], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][4], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][4], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][4], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][4], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][4], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][4], true);

	InventoryAccessories[playerid][5] = CreatePlayerTextDraw(playerid, 157.932693, 264.195709, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][5], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][5], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][5], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][5], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][5], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][5], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][5], true);

	InventoryAccessories[playerid][6] = CreatePlayerTextDraw(playerid, 191.766098, 264.195709, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][6], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][6], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][6], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][6], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][6], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][6], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][6], true);

	InventoryAccessories[playerid][7] = CreatePlayerTextDraw(playerid, 225.765701, 264.195709, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][7], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][7], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][7], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][7], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][7], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][7], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][7], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][7], true);

	InventoryAccessories[playerid][8] = CreatePlayerTextDraw(playerid, 259.732086, 264.195709, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][8], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][8], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][8], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][8], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][8], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][8], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][8], true);

	InventoryAccessories[playerid][9] = CreatePlayerTextDraw(playerid, 293.731903, 264.195709, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][9], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][9], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][9], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][9], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][9], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][9], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][9], true);

	InventoryAccessories[playerid][10] = CreatePlayerTextDraw(playerid, 157.832702, 303.188385, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][10], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][10], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][10], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][10], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][10], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][10], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][10], true);

	InventoryAccessories[playerid][11] = CreatePlayerTextDraw(playerid, 191.666107, 303.188385, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][11], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][11], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][11], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][11], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][11], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][11], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][11], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][11], true);

	InventoryAccessories[playerid][12] = CreatePlayerTextDraw(playerid, 225.665603, 303.188385, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][12], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][12], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][12], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][12], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][12], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][12], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][12], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][12], true);

	InventoryAccessories[playerid][13] = CreatePlayerTextDraw(playerid, 259.631988, 303.188385, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][13], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][13], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][13], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][13], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][13], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][13], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][13], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][13], true);

	InventoryAccessories[playerid][14] = CreatePlayerTextDraw(playerid, 293.631805, 303.188385, "");
	PlayerTextDrawLetterSize(playerid, InventoryAccessories[playerid][14], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryAccessories[playerid][14], 30.000000, 34.000000);
	PlayerTextDrawAlignment(playerid, InventoryAccessories[playerid][14], 1);
	PlayerTextDrawColor(playerid, InventoryAccessories[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, InventoryAccessories[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, InventoryAccessories[playerid][14], 76);
	PlayerTextDrawFont(playerid, InventoryAccessories[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, InventoryAccessories[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, InventoryAccessories[playerid][14], 0);
	PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][14], 18631);
	PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][14], 0.000000, 0.000000, 0.000000, 0.813300);
	PlayerTextDrawSetSelectable(playerid, InventoryAccessories[playerid][14], true);
	return 1;
}
//==============================================================================
HidePlayerInventoryTextDraw(playerid)
{
    if(InventoryTextDraw[playerid] == false) return 1;
    for(new i = 0; i < 36; i++) TextDrawHideForPlayer(playerid, InventoryOther[i]);
    for(new i = 0; i < 10; i++) TextDrawHideForPlayer(playerid, InventoryButton[i]);
    for(new i = 0; i < 3; i++) PlayerTextDrawHide(playerid, InventoryInfo[playerid][i]);
    for(new i = 0; i < 15; i++) PlayerTextDrawHide(playerid, InventoryItems[playerid][i]);
    for(new i = 0; i < 15; i++) PlayerTextDrawHide(playerid, InventoryAccessories[playerid][i]);
    ClearPlayerInventoryTextDraw(playerid);
    CancelSelectTextDraw(playerid);
    return 1;
}
//==============================================================================
DestroyPlayerInventoryTextDraw(playerid)
{
    for(new i = 0; i < 3; i++) PlayerTextDrawDestroy(playerid, InventoryInfo[playerid][i]);
    for(new i = 0; i < 15; i++) PlayerTextDrawDestroy(playerid, InventoryItems[playerid][i]);
    for(new i = 0; i < 15; i++) PlayerTextDrawDestroy(playerid, InventoryAccessories[playerid][i]);
    return 1;
}
//==============================================================================
ClearPlayerInventoryTextDraw(playerid, type = 0)
{
    if(type == 0) InventoryTextDraw[playerid] = false;
    InventoryTextDrawUse[playerid] = -1;
    InventoryTextDrawUseType[playerid] = -1;
    for(new i = 0; i < 15; i++) InventoryTextDrawItems[playerid][i] = -1;
    for(new i = 0; i < 15; i++) InventoryTextDrawAccessories[playerid][i] = -1;
    for(new i = 0; i < 2; i++) InventoryTextDrawList[playerid][i] = 0;
    for(new i = 0 ; i < MAX_ITEMS_LIST + 1; i++) InventoryTextDrawItemsCnt[playerid][i] = -1;
    for(new i = 0 ; i < MAX_ACCESSORIES_LIST + 1; i++) InventoryTextDrawAccessoriesCnt[playerid][i] = -1;
    return 1;
}
//==============================================================================
CheckPlayerInventoryColor(playerid)
{
    if(InventoryTextDraw[playerid] == false) return 1;
    if(InventoryTextDrawUse[playerid] != -1 && InventoryTextDrawUseType[playerid] != -1)
    {
        new idx = InventoryTextDrawUse[playerid];
        if(InventoryTextDrawUseType[playerid] == 1) UpdatePlayerInventoryColor(playerid, InventoryItems[playerid][idx], false);
        else UpdatePlayerInventoryColor(playerid, InventoryAccessories[playerid][idx], false);
    }
    return 1;
}
//==============================================================================
UpdatePlayerInventoryColor(playerid, PlayerText:textdraw, bool:status)
{
    if(InventoryTextDraw[playerid] == false) return 1;
    PlayerTextDrawHide(playerid, textdraw);
    if(status == false) PlayerTextDrawBackgroundColor(playerid, textdraw, 76);
    else PlayerTextDrawBackgroundColor(playerid, textdraw, 0x0DF690AA);
    PlayerTextDrawShow(playerid, textdraw);
    return 1;
}
//==============================================================================
LoadPlayerItemsList(playerid, idx, type = 0)
{
    if(type == 1)
    {
        CheckPlayerInventoryColor(playerid);
        InventoryTextDrawUse[playerid] = -1;
        InventoryTextDrawUseType[playerid] = -1;
        for(new i = 0; i < 15; i++) PlayerTextDrawHide(playerid, InventoryItems[playerid][i]);
        for(new i = 0; i < 15; i++) InventoryTextDrawItems[playerid][i] = -1;
    }
    new count, max_value;


	PlayerInfo[playerid][pInventoryItems][TYPE_DRUGS] = PlayerInfo[playerid][drugs];
	PlayerInfo[playerid][pInventoryItems][TYPE_MASK] = PlayerInfo[playerid][mask];
	PlayerInfo[playerid][pInventoryItems][TYPE_HOTDOG] = PlayerInfo[playerid][hotdog];
	PlayerInfo[playerid][pInventoryItems][TYPE_BOOMBOX] = PlayerInfo[playerid][boombox];
	PlayerInfo[playerid][pInventoryItems][TYPE_MEDICINE] = PlayerInfo[playerid][aidkit];
	PlayerInfo[playerid][pInventoryItems][TYPE_REPAIR_KIT] = PlayerInfo[playerid][repairkit];
    PlayerInfo[playerid][pInventoryItems][TYPE_CANISTER] = PlayerInfo[playerid][canister];
    

	for(new i = idx; i < MAX_INVENTORY; i++)
    {
        if(PlayerInfo[playerid][pInventoryItems][i] == 0) continue;
        GetPlayerMaxInventoryItems(i, max_value);
        if(PlayerInfo[playerid][pInventoryItems][i] > max_value)
        {
            PlayerInfo[playerid][pInventoryItems][i] = max_value;
            SavePlayerInventoryItems(playerid, i);
            SendError(playerid, "Meghdar item \"%s\" bishtar az hade mojaz ast, meghdar mazad hazf shod.", Inventory[i][InvStringName]);
			
			switch(Inventory[i][InvType])
			{
				case TYPE_DRUGS:
				{
					PlayerInfo[playerid][drugs] = max_value;
					update_int_sql(playerid, "u_drugs", PlayerInfo[playerid][drugs]);
				}
				case TYPE_MASK:
				{
					PlayerInfo[playerid][mask] = max_value;
					update_int_sql(playerid, "u_mask", PlayerInfo[playerid][mask]);
				}
				case TYPE_BOOMBOX:
				{
					PlayerInfo[playerid][boombox] = max_value;
					update_int_sql(playerid, "u_boombox", PlayerInfo[playerid][boombox]);
				}
				case TYPE_HOTDOG:
				{
					PlayerInfo[playerid][hotdog] = max_value;
					update_int_sql(playerid, "u_hotdog", PlayerInfo[playerid][hotdog]);
				}
				case TYPE_MEDICINE:
				{
					PlayerInfo[playerid][aidkit] = max_value;
					update_int_sql(playerid, "u_aidkit", PlayerInfo[playerid][aidkit]);
				}
				case TYPE_REPAIR_KIT:
				{
					PlayerInfo[playerid][repairkit] = max_value;
					update_int_sql(playerid, "u_repairkit", PlayerInfo[playerid][repairkit]);
				}
				case TYPE_CANISTER:
				{
					PlayerInfo[playerid][canister] = max_value;
					update_int_sql(playerid, "u_canister", PlayerInfo[playerid][canister]);
				}
			}
        }
        PlayerTextDrawSetPreviewModel(playerid, InventoryItems[playerid][count], Inventory[i][InvObject]);
        PlayerTextDrawSetPreviewRot(playerid, InventoryItems[playerid][count], Inventory[i][InvObjectPos][0], Inventory[i][InvObjectPos][1], Inventory[i][InvObjectPos][2], Inventory[i][InvObjectPos][3]);
        PlayerTextDrawShow(playerid, InventoryItems[playerid][count]);
        InventoryTextDrawItems[playerid][count] = i;
        count++;
        if(count == 15) break;
    }
    if(type == 1)
    {
        InventoryTextDrawItemsCnt[playerid][InventoryTextDrawList[playerid][0]] = InventoryTextDrawItems[playerid][0];
    }
    return 1;
}
//==============================================================================
LoadPlayerAccessoriesList(playerid, idx, type = 0)
{
    if(type == 1)
    {
        CheckPlayerInventoryColor(playerid);
        InventoryTextDrawUse[playerid] = -1;
        InventoryTextDrawUseType[playerid] = -1;
        for(new i = 0; i < 15; i++) PlayerTextDrawHide(playerid, InventoryAccessories[playerid][i]);
        for(new i = 0; i < 15; i++) InventoryTextDrawAccessories[playerid][i] = -1;
    }
    new count;
    for(new i = idx; i < MAX_PLAYER_ACCESSORIES; i++)
    {
        if(PlayerInfo[playerid][accessories][i] == 0) continue;
        PlayerTextDrawSetPreviewModel(playerid, InventoryAccessories[playerid][count], AccessoriesInfo[PlayerInfo[playerid][accessories][i]-1][aModel]);
        PlayerTextDrawSetPreviewRot(playerid, InventoryAccessories[playerid][count], AccessoriesInfo[PlayerInfo[playerid][accessories][i]-1][aModelPos][0], AccessoriesInfo[PlayerInfo[playerid][accessories][i]-1][aModelPos][1], AccessoriesInfo[PlayerInfo[playerid][accessories][i]-1][aModelPos][2], AccessoriesInfo[PlayerInfo[playerid][accessories][i]-1][aModelPos][3]);
        PlayerTextDrawShow(playerid, InventoryAccessories[playerid][count]);
        InventoryTextDrawAccessories[playerid][count] = i;
        count++;
        if(count == 15) break;
    }
    if(type == 1)
    {
        InventoryTextDrawAccessoriesCnt[playerid][InventoryTextDrawList[playerid][1]] = InventoryTextDrawAccessories[playerid][0];
    }
    return 1;
}
//==============================================================================