//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=| Mihan Role Play|=-=-=-=-=-=-=-=-=-=-=-=-=//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

/* 
    System Information 
    ----------------
    Developer: Abolfazl Hosseini (Github : @inj3ct0r & Tel: @inject3r)
    Version: 1.0.0
    File Type: pwn

    All rights to this file are reserved by Developer. Unauthorized use, reproduction, or modification of this file is strictly prohibited. 

    Copyright © 2024 Abolfazl Hosseini. All rights reserved. 
*/

new bool:InventoryTextDraw[MAX_PLAYERS];
new InventoryUseItems[MAX_PLAYERS];
new InventorySellItems[MAX_PLAYERS];
new InventoryUseAccessories[MAX_PLAYERS];

// accessories System
#include "../library/static/system/player/inventory/accessories.inc"

// inventory System
#include "../library/static/system/player/inventory/inventory.inc"

cmd:inv(playerid, params[])
{
    if(InventoryTextDraw[playerid])
	{
		CheckPlayerInventoryColor(playerid);
		HidePlayerInventoryTextDraw(playerid);
	}

    ShowPlayerInventory(playerid);

    SelectTextDraw(playerid, 0x0DF690AA);
    
    return 1;
}