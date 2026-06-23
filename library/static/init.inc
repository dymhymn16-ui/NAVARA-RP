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


// include server system
#include "../library/static/system/index.inc"


//include server core
#include "../library/static/core/index.inc"

// ---------------------------------------------------------

MRP_Init() {
    MapIcons_Init();
    Benchs_Init();
    GateSystem_Init();
    Boombox_Init();
    Radio_Init();
    CounterStrikeInit();
    HealthCardInit();
    FalloutGameInit();
    LicenseGunShop_Init();
    bots_OnGameModeInit();
}

MRP_OneSecondTimer() {
    NDP_OneSecondTimer();
    TopWar_OneSecondTimer();
    GateSystem_OneSecTimer();
    DropGun_OneSecTimer();
    CounterStrikeTimer();
    VoteTimer();
    CheckLobby();
}

MRP_OneSecPlayerTimer(playerid) {
    SnowSystemOneSecPlayerTimer(playerid);
    CounterStrikePlayerTimer(playerid);
    LicenseGunShop_PlayerTimer(playerid);

    if(CodeVerifyingPhoneTime[playerid] > 0) CodeVerifyingPhoneTime[playerid]--;
}

MRP_OnPlayerConnect(playerid)
{
    SMS_System_ResetPlayerData(playerid);
    CounterStrikePlayerConnect(playerid);
    VC_OnPlayerConnect(playerid);
}

MRP_OnPlayerDisconnect(playerid)
{
    VC_OnPlayerDisconnect(playerid);
    DestroyPlayerInventoryTextDraw(playerid);
}

MRP_OnPlayerSpawn(playerid) {
    if(IsPlayerInCounterStrike(playerid) || IsPlayerInCounterStrikeLobby(playerid)) 
    {
        CounterStrikePlayerSpawn(playerid);
        return 0;
    }

    FalloutGame_PlayerSpawn(playerid);

    return 1;
}

MRP_OnPlayerDeath(playerid, killerid, reason) {

    premium_OnPlayerDeath(playerid, killerid, reason);

    if(IsPlayerInCounterStrike(playerid) || IsPlayerInCounterStrikeLobby(playerid))
    {
        CounterStrikePlayerDeath(playerid, killerid, reason);
        return 1;
    }

    DropGuns_PlayerDeath(playerid);

    LicenseGunShop_PlayerDeath(playerid);

    FalloutGame_PlayerDeath(playerid, killerid);
    
    return 0;
}

MRP_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid) {
    TopWar_OnPlayerTakeDamage(playerid, issuerid, amount, weaponid);
    
    FalloutGame_PlayerTakeDamage(playerid);

    return 1;
}

MRP_OnPlayerKeyState(playerid, newkeys, oldkeys)
{
    if(TopWar_OnPlayerKeyState(playerid, newkeys, oldkeys)) {
        return 1;
    }

    if(newkeys & KEY_CTRL_BACK) {
        GateSystem_Check(playerid);
    }

    if(newkeys & KEY_CTRL_BACK || newkeys & KEY_CROUCH)
    {
        IstBazresiLVLS_Check(playerid);
    }

    DropGuns_PlayerKeyStateChange(playerid, newkeys);

    return 0;
}

MRP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(Boombox_OnDialogResponse(playerid, dialogid, response, listitem, inputtext)) return 1;

    if(dialogid == DIALOG_VERIFYING) return Dialog_SMS(playerid, response, inputtext);
    if(dialogid == DIALOG_VERIFYING_CODE) return Dialog_SMScode(playerid, response, inputtext);

    if(GateSystem_OnDialogResponse(playerid, dialogid, response, listitem, inputtext)) return 1;

    if(Binder_OnDialogResponse(playerid, dialogid, response, listitem, inputtext)) return 1;

    if(RadioStation_DialogRespone(playerid, dialogid, response, listitem, inputtext)) return 1;

    if(CounterStrikeDialogResponse(playerid, dialogid, response, listitem)) return 1;

    if(HealthCardOnDialogResponse(playerid, dialogid, response, listitem)) return 1;

    if(VoteSystemOnDialogResponse(playerid, dialogid, response, inputtext)) return 1;

    if (LicenseGunShop_DialogResponse(playerid, dialogid, response)) return 1;

    return 0;
}

MRP_OnPlayerPickUpDyn(playerid, pickupid)
{
    if(CounterStrikePickDynamicPickup(playerid, pickupid)) return 1;
    if(LicenseGunShop_OnDynamicPickup(playerid, pickupid)) return 1;

    return 0;
}