// Maximum number of MarJoana plants that can exist
#define MAX_MARJOANA  1000

// 3D text labels for MarJoana plants
new Text3D:MarJoana3D[MAX_MARJOANA];

// Dynamic object IDs for MarJoana plants
new MarJoana[MAX_MARJOANA][9];

// Boolean array to check if a MarJoana plant is ready for harvest
new bool:MarJoanaDis[MAX_MARJOANA];

// Player IDs associated with each MarJoana plant
new MarJoanaPl[MAX_MARJOANA];

// Positions of each MarJoana plant
new Float:MarJoanaPos[MAX_MARJOANA][3];

// Forward declaration of the MarJoana timer
forward MarijoanaTimer(playerid, mariID, percent);

// MarJoana growth timer function
callback: MarJoanaTimer(playerid, mariID, percent) {
    new sstring[300];
    
    // If growth is complete
    if (percent == 600) {
        format(sstring, sizeof(sstring), c_server"Bote Marijoana\n"c_white"Create by : %s\n"c_white"Roshd karde: "c_server"600/600\n\n"c_white"Amade Bardasht ("c_server"/harvest"c_white")", Name(playerid));
        UpdateDynamic3DTextLabelText(MarJoana3D[mariID], -1, sstring);
        MarJoanaDis[mariID] = true; // Mark plant as ready for harvest
        return 1;
    } else {
        // Update growth progress
        format(sstring, sizeof(sstring), c_server"Bote Marijoana\n"c_white"Create by : %s\n"c_white"Darhall roshd: "c_server"%d/600", Name(playerid), percent);
        UpdateDynamic3DTextLabelText(MarJoana3D[mariID], -1, sstring);
        return SetTimerEx("MarJoanaTimer", 1000, false, "iii", playerid, mariID, percent + 1);
    }
}

// Command: /harvest
cmd:harvest(playerid) {
    if(!gang_player(playerid)) return SendError(playerid, "Shoma dastresi be in dastor nadarid.");

    if(gz_info[GetGangZoneID(playerid)][gz_owner] != PlayerInfo[playerid][member]) return SendError(playerid, "Shoma nmitavanid dar in mantaghe bote bardasht konid.");

    for (new i = 0; i < MAX_MARJOANA; i++) {
        // Check if the player is near the plant
        if(GetDistanceBetweenPlayerAndPos(playerid, MarJoanaPos[i][0], MarJoanaPos[i][1], MarJoanaPos[i][2]) > 5.0) continue;

        // Check if the plant is ready for harvest
        if(MarJoanaDis[i] == false) return SendError(playerid, "Bote be tor kamel roshd nakarde ast.");

        // Add drugs to the player's inventory
        PlayerInfo[playerid][drugs] += 40;
        update_int_sql(playerid, "u_drugs", PlayerInfo[playerid][drugs]);

        SendAccess(playerid, "Shoma drug az bote marijuana bardasht kardid!");

        ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 2000);

        // Destroy the plant's objects and 3D label
        DestroyDynamic3DTextLabel(MarJoana3D[i]);
        for (new xx = 0; xx < 9; xx++) DestroyDynamicObject(MarJoana[i][xx]);

        MarJoanaDis[i] = false; // Mark plant as harvested
        p_t_info[MarJoanaPl[i]][list_player_marjoana]--; // Decrement player's active plant count

        break;
    }

    return false;
}

// Command: /plant
cmd:plant(playerid) {
    if(!gang_player(playerid)) return SendError(playerid, "Shoma dastresi be in dastor nadarid.");

    if(gz_info[GetGangZoneID(playerid)][gz_owner] != PlayerInfo[playerid][member]) return SendError(playerid, "Shoma nmitavanid dar in mantaghe bote bekarid.");

    // Check if the player has the required weapon (Bill)
    if(GetPlayerWeapon(playerid) != 6) return SendError(playerid, "Baraye kasht bote Marijuana be bill niyaz darid.");

    if(PlayerInfo[playerid][seed] < 40) return SendError(playerid, "Shoma be andazi kafi daneh marijvana be hamrah nadarid, 40 gr.");

    // Check if the player has reached the plant limit
    if(p_t_info[playerid][list_player_marjoana] >= 5) return SendError(playerid, "Shoma nemitavanid bishtar az 5 bote Marijuana bekarid.");

    // Find the first empty slot
    new mariID = -1;
    for (new i = 0; i < MAX_MARJOANA; i++) {
        if (MarJoanaPl[i] == 0) {
            mariID = i;
            break;
        }
    }

    if (mariID == -1) return SendError(playerid, "Hame mantaghe Marijoana por shodeh ast.");

    // Get the player's position
    new Float:ppos[3];
    GetPlayerPos(playerid, ppos[0], ppos[1], ppos[2]);

    // Save the plant's position and owner
    MarJoanaPos[mariID][0] = ppos[0];
    MarJoanaPos[mariID][1] = ppos[1];
    MarJoanaPos[mariID][2] = ppos[2];
    MarJoanaPl[mariID] = playerid;

    p_t_info[playerid][list_player_marjoana]++;

    // Play planting animation
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 2000);
    me_action(playerid, "dar hal kasht bote marijoana");

    PlayerInfo[playerid][seed] -= 40;
    update_int_sql(playerid, "u_seed", PlayerInfo[playerid][seed]);

    // Create the plant's objects
    MarJoana[mariID][0] = CreateDynamicObject(19473, ppos[0], ppos[1], ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][1] = CreateDynamicObject(19473, ppos[0] + 1.0, ppos[1], ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][2] = CreateDynamicObject(19473, ppos[0] + 1.0, ppos[1] + 1.0, ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][3] = CreateDynamicObject(19473, ppos[0] + 1.0, ppos[1] - 1.0, ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][4] = CreateDynamicObject(19473, ppos[0], ppos[1] + 1.0, ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][5] = CreateDynamicObject(19473, ppos[0], ppos[1] - 1.0, ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][6] = CreateDynamicObject(19473, ppos[0] - 1.0, ppos[1], ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][7] = CreateDynamicObject(19473, ppos[0] - 1.0, ppos[1] - 1.0, ppos[2] - 2.0, 0.0, 0.0, 0.0);
    MarJoana[mariID][8] = CreateDynamicObject(19473, ppos[0] - 1.0, ppos[1] + 1.0, ppos[2] - 2.0, 0.0, 0.0, 0.0);

    // Create a 3D text label for the plant
    new sstring[100];
    format(sstring, sizeof(sstring), c_server"Bote Marijoana\n"c_white"Create by : %s\n"c_white"Darhall roshd: "c_server"%d/600", Name(playerid), 0);
    new world_ = GetPlayerVirtualWorld(playerid), interior_ = GetPlayerInterior(playerid);
    MarJoana3D[mariID] = CreateDynamic3DTextLabel(sstring, -1, ppos[0], ppos[1], ppos[2], .drawdistance = 15.0, .testlos = 1, .worldid = world_, .interiorid = interior_);

    // Update streamer and start growth timer
    Streamer_Update(playerid);
    SetTimerEx("MarJoanaTimer", 1000, false, "iii", playerid, mariID, 1);

    return 1;
}
