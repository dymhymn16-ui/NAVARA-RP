/*
 * Fps Include v0.1
 * Author: pxl
 * Licensed under: MIT
*/

#if defined _inc_fps
    #undef _inc_fps
#endif
#if defined _fps_included
    #endinput
#endif

#define _fps_included

static
    Player_g_sCurrentFps[MAX_PLAYERS],
    Player_g_sCurrentDrunk[MAX_PLAYERS],
    bool:Player_g_ToggleFps[MAX_PLAYERS]
;

stock TogglePlayerFpsMonitor(playerid, bool:set)
{
    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }
    
    Player_g_ToggleFps[playerid] = set;
    return 1;
}

stock GetPlayerFps(playerid)
{
    if (!IsPlayerConnected(playerid))
    {
        return cellmin;
    }

    if (!Player_g_ToggleFps[playerid])
    {
        print("FPS Error: Use `ToggleFpsMonitor` first before using this!");
        return cellmax;
    }

    return (Player_g_sCurrentFps[playerid]);
}

// Hooks
public OnPlayerUpdate(playerid)
{
    new ret = 1;
    
#if defined pxl_OnPlayerUpdate
    ret = pxl_OnPlayerUpdate(playerid);
#endif
    
    if (!Player_g_ToggleFps[playerid])
    {
        return ret;
    }    

    new
        oldDrunk = Player_g_sCurrentDrunk[playerid];
        newDrunk = GetPlayerDrunkLevel(playerid);
    
    if (newDrunk < 100)
    {
        SetPlayerDrunkLevel(playerid, 2000);
        newDrunk = 2000;
    }
    
    if (oldDrunk != newDrunk)
    {
        new totalFps = oldDrunk - newDrunk;
        Player_g_sCurrentFps[playerid] = totalFps;
        Player_g_sCurrentDrunk[playerid] = newDrunk;
    }
    return ret;
}

public OnPlayerDisconnect(playerid, reason)
{
    Player_g_sCurrentFps[playerid] = 0;
    Player_g_sCurrentDrunk[playerid] = 0;
    Player_g_ToggleFps[playerid] = false;
    
#if defined pxl_OnPlayerDisconnect
    return pxl_OnPlayerDisconnect(playerid, reason);
#else
    return 1;
#endif
}

// ALS Metadata
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerUpdate pxl_OnPlayerUpdate
#define OnPlayerDisconnect pxl_OnPlayerDisconnect

#if defined pxl_OnPlayerUpdate
forward pxl_OnPlayerUpdate(playerid);
#endif
#if defined pxl_OnPlayerDisconnect
forward pxl_OnPlayerDisconnect(playerid, reason);
#endif
