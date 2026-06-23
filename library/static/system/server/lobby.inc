#include "../library/static/system/server/lobby_var.inc"

CreateDefaultLobby(type, capacity, time, subject, weapon, map, device, pass)
{
    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1)
        {
            LobbyInfo[i][LobbyCreateID] = -1;
            LobbyInfo[i][LobbyType] = type;
            LobbyInfo[i][LobbyCapacity] = capacity;
            LobbyInfo[i][LobbyTime] = time;
            LobbyInfo[i][LobbySubject] = subject;
            LobbyInfo[i][LobbyMap] = map;
            LobbyInfo[i][LobbyDevice] = device;
            LobbyInfo[i][LobbyPassword] = pass;
            LobbyInfo[i][LobbyDefault] = true;
            LobbyInfo[i][LobbyDefaultWeapon] = weapon;

            for(new idx = 0; idx < MAX_PLAYERS_LOBBY; idx++)
            {
                LobbyInfo[i][LobbyPlayers][idx] = INVALID_PLAYER_ID;
                LobbyInfo[i][LobbyKills][idx] = 0;
                LobbyInfo[i][LobbyDeaths][idx] = 0;
                LobbyInfo[i][LobbyVehicles][idx] = INVALID_VEHICLE_ID;
            }
            return 1;
        }
    }
    return 1;
}

CreateLobby(playerid, type, capacity, time, subject, map, device, pass)
{
    if(PlayerInfo[playerid][level] < MIN_LEVEL_ENTER_LOBBY) return SendError(playerid, "Shoma level %d ra nadarid.", MIN_LEVEL_CREATE_LOBBY);

    if(player_lobby_status[playerid] != false || player_lobby_idx[playerid] != -1) return SendError(playerid, "Shoma dar hale hazer dar lobby hastid.");

    if(device == 0 && !IsPlayerMobile(playerid)) return SendError(playerid, "Shoma nemitavanid lobby baraye bazi konan [Mobile] besazid.");
    if(device == 1 && IsPlayerMobile(playerid)) return SendError(playerid, "Shoma nemitavanid lobby baraye bazi konan [PC] besazid.");

    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1)
        {
            LobbyInfo[i][LobbyCreateID] = playerid;
            LobbyInfo[i][LobbyType] = type;
            LobbyInfo[i][LobbyCapacity] = capacity;
            LobbyInfo[i][LobbyTime] = time;
            LobbyInfo[i][LobbySubject] = subject;
            LobbyInfo[i][LobbyMap] = map;
            LobbyInfo[i][LobbyDevice] = device;
            LobbyInfo[i][LobbyPassword] = pass;
            LobbyInfo[i][LobbyDefault] = false;


            for(new idx = 0; idx < MAX_PLAYERS_LOBBY; idx++)
            {
                LobbyInfo[i][LobbyPlayers][idx] = INVALID_PLAYER_ID;
                LobbyInfo[i][LobbyKills][idx] = 0;
                LobbyInfo[i][LobbyDeaths][idx] = 0;
                LobbyInfo[i][LobbyVehicles][idx] = INVALID_VEHICLE_ID;
            }

            SendAccess(playerid, "You have created a lobby.");
            SendInfo(playerid, "Type: %s, Capacity: %d, Time: %s, Parameter: %d, Map: %s, Device: %s, Password: %d", LobbyTypeName[type - 1], capacity, ConvertTime(time, 1), subject, LobbyMapName[type - 1][map], LobbyDeviceName[device], pass);

            SetPlayerFreeSlotLobby(playerid, i);
            return 1;
        }
    }
    
    SendError(playerid, "Jaye khali baraye sakhte lobby Jadid mojood nist.");
    return 1;
}

ClearLobby(idx, text[])
{
    for(new i = 0; i < MAX_PLAYERS_LOBBY; i++)
    {
        if(LobbyInfo[idx][LobbyPlayers][i] != INVALID_PLAYER_ID)
        {
            switch(LobbyInfo[idx][LobbyType])
            {
                case LOBBY_TYPE_DEATHMATCH, LOBBY_TYPE_RACE, LOBBY_TYPE_DERBY, LOBBY_TYPE_STUNT, LOBBY_TYPE_PARKOUR:
                {
                    ResetPlayerWeapons(LobbyInfo[idx][LobbyPlayers][i]);
                    for(new a = 0; a < MAX_WEAPONS; a++) GivePlayerWeapon(LobbyInfo[idx][LobbyPlayers][i], PlayerInfo[LobbyInfo[idx][LobbyPlayers][i]][Weapon][a], PlayerInfo[LobbyInfo[idx][LobbyPlayers][i]][Ammo][a]);
                    SetPlayerArmedWeapon(LobbyInfo[idx][LobbyPlayers][i], 0);
                }
            }
            SendInfo(LobbyInfo[idx][LobbyPlayers][i], "Lobby hazf shod. Dalil: %s", text);

            // if(LobbyInfo[idx][LobbyType] == LOBBY_TYPE_PARKOUR) SetPlayerSkinEx(LobbyInfo[idx][LobbyPlayers][i]);
            set_pos(LobbyInfo[idx][LobbyPlayers][i], 2049.470, -1908.065, 13.546, 270.0, 0, 0);
            SetCameraBehindPlayer(LobbyInfo[idx][LobbyPlayers][i]);
            if(is_fraction_duty {LobbyInfo[idx][LobbyPlayers][i]} == 1 && playerFactionStatus(LobbyInfo[idx][LobbyPlayers][i])) SetPlayerColor(LobbyInfo[idx][LobbyPlayers][i], f_info[PlayerInfo[LobbyInfo[idx][LobbyPlayers][i]][member]][f_radar_color]);
            else SetPlayerColor(LobbyInfo[idx][LobbyPlayers][i],  0xFFFFFFFF);
            if(PlayerInfo[LobbyInfo[idx][LobbyPlayers][i]][admin] > 0) SetPlayerColor(LobbyInfo[idx][LobbyPlayers][i], 0xFFFFFF00);
            ClearDeathMessage(LobbyInfo[idx][LobbyPlayers][i]);

            player_lobby_status[LobbyInfo[idx][LobbyPlayers][i]] = false;
            player_lobby_type[LobbyInfo[idx][LobbyPlayers][i]] = -1;
            player_lobby_idx[LobbyInfo[idx][LobbyPlayers][i]] = -1;

        }

        // if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID) DestroyVehicle(LobbyInfo[idx][LobbyVehicles][i]);

        LobbyInfo[idx][LobbyPlayers][i] = INVALID_PLAYER_ID;
        LobbyInfo[idx][LobbyKills][i] = 0;
        LobbyInfo[idx][LobbyDeaths][i] = 0;
        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
    }

    LobbyInfo[idx][LobbyCreateID] = INVALID_PLAYER_ID;
    LobbyInfo[idx][LobbyType] = 0;
    LobbyInfo[idx][LobbyCapacity] = 0;
    LobbyInfo[idx][LobbyTime] = 0;
    LobbyInfo[idx][LobbySubject] = 0;
    LobbyInfo[idx][LobbyMap] = 0;
    LobbyInfo[idx][LobbyDevice] = 0;
    LobbyInfo[idx][LobbyPassword] = 0;
    LobbyInfo[idx][LobbyDefault] = false;
    LobbyInfo[idx][LobbyDefaultWeapon] = -1;

    return 1;
}

CheckLobby()
{
    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1) continue;

        if(LobbyInfo[i][LobbyTime] > 0) LobbyInfo[i][LobbyTime]--;
        if(LobbyInfo[i][LobbyTime] == 0) ClearLobby(i, "Zaman lobby tamom shodeh ast.");
    }
    return 1;
}

GetFreeSlotLobby(idx)
{
    new slot = 0;
    for(new i = 0; i < LobbyInfo[idx][LobbyCapacity]; i++)
    {
        if(LobbyInfo[idx][LobbyPlayers][i] == INVALID_PLAYER_ID)
        {
            slot++;
        }
    }
    return slot;
}

SetPlayerFreeSlotLobby(playerid, idx)
{
    if(PlayerInfo[playerid][level] < MIN_LEVEL_ENTER_LOBBY) return SendError(playerid, "Shoma level %d ra nadarid.", MIN_LEVEL_ENTER_LOBBY);

    if(player_lobby_status[playerid] != false || player_lobby_idx[playerid] != -1) return SendError(playerid, "Shoma az ghabl dar in lobby hastid.");

    if(LobbyInfo[idx][LobbyDevice] == 0 && !IsPlayerMobile(playerid)) return SendError(playerid, "In lobby faghat baraye [Mobile] dar dastres ast.");
    if(LobbyInfo[idx][LobbyDevice] == 1 && IsPlayerMobile(playerid)) return SendError(playerid, "In lobby faghat baraye [PC] dar dastres ast.");

    for(new i = 0; i < LobbyInfo[idx][LobbyCapacity]; i++)
    {
        if(LobbyInfo[idx][LobbyPlayers][i] == INVALID_PLAYER_ID)
        {
            switch(LobbyInfo[idx][LobbyType])
            {
                case LOBBY_TYPE_DEATHMATCH:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Shoma vared lobby %s [%d] shodid.", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Shoma vared lobby standard shodid.");
                    SendInfo(playerid, "Noe: %s, Zarfiyat: %d, Zaman: %s, Parameter: %d, Kart: %s, Dastgah: %s, Ramz: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Baraye moshahedeh amar: /lobbystats");
                    SendInfo(playerid, "Baraye khorooj az lobby: /lobbyexit");

                    ResetPlayerWeapons(playerid);
                    new sidx = random(20), type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[5] = {1, 1, 0, 0, 0};
                    set_pos(playerid, LobbyPos[type][map][sidx][0], LobbyPos[type][map][sidx][1], LobbyPos[type][map][sidx][2], LobbyPos[type][map][sidx][3], interior_map[map], idx + 1);
                    SetCameraBehindPlayer(playerid);
                    set_health(playerid, 100.0);
                    set_armour(playerid, 0.0);
                    SetPlayerColor(playerid, 0xFF0000FF);
                    GivePlayerWeapon(playerid, LobbyInfo[idx][LobbySubject], 9999);
                    if(LobbyInfo[idx][LobbyDefault]) GivePlayerWeapon(playerid, LobbyInfo[idx][LobbyDefaultWeapon], 9999);

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_DEATHMATCH;
                    player_lobby_idx[playerid] = idx;

                    return 1;
                }
                case LOBBY_TYPE_RACE:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID)
                    {
                        DestroyVehicle(LobbyInfo[idx][LobbyVehicles][i]);
                        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
                    }

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Shoma vared lobby %s [%d] shodid.", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Shoma vared lobby standard shodid.");
                    SendInfo(playerid, "Noe: %s, Zarfiyat: %d, Zaman: %s, Parameter: %d, Kart: %s, Dastgah: %s, Ramz: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Baraye khorooj az lobby: /lobbyexit");

                    new type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[3] = {7, 4, 1};

                    new vehicleid = CreateVehicle(LobbyInfo[idx][LobbySubject], LobbyPos[type][map][i][0], LobbyPos[type][map][i][1], LobbyPos[type][map][i][2], LobbyPos[type][map][i][3], 1, 1, 120);

                    ResetPlayerWeapons(playerid);
                    set_health(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    LinkVehicleToInterior(vehicleid, interior_map[map]);
                    SetVehicleVirtualWorld(vehicleid, idx);

                    SetPlayerInterior(playerid, interior_map[map]);
                    SetPlayerVirtualWorld(playerid, idx);

                    veh_info[vehicleid][v_locked] = 1;
                    veh_info[vehicleid][v_color] = 1;
                    veh_info[vehicleid][v_model] = LobbyInfo[idx][LobbySubject];
                    veh_info[vehicleid][v_fuel] = 100.0;

                    PutPlayerInVehicle(playerid, vehicleid, 0);

                    LobbyInfo[idx][LobbyVehicles][i] = vehicleid;

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_RACE;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                case LOBBY_TYPE_DERBY:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID)
                    {
                        DestroyVehicle(LobbyInfo[idx][LobbyVehicles][i]);
                        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
                    }

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Shoma vared lobby %s [%d] shodid.", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Shoma vared lobby standard shodid.");
                    SendInfo(playerid, "Noe: %s, Zarfiyat: %d, Zaman: %s, Parameter: %d, Kart: %s, Dastgah: %s, Ramz: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Baraye khorooj az lobby: /lobbyexit");

                    new type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[3] = {15, 0, 0};

                    new vehicleid = CreateVehicle(LobbyInfo[idx][LobbySubject], LobbyPos[type][map][i][0], LobbyPos[type][map][i][1], LobbyPos[type][map][i][2], LobbyPos[type][map][i][3], 1, 1, 120);

                    ResetPlayerWeapons(playerid);
                    set_health(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    LinkVehicleToInterior(vehicleid, interior_map[map]);
                    SetVehicleVirtualWorld(vehicleid, idx);

                    SetPlayerInterior(playerid, interior_map[map]);
                    SetPlayerVirtualWorld(playerid, idx);

                    veh_info[vehicleid][v_locked] = 1;
                    veh_info[vehicleid][v_color] = 1;
                    veh_info[vehicleid][v_model] = LobbyInfo[idx][LobbySubject];
                    veh_info[vehicleid][v_fuel] = 100.0;

                    PutPlayerInVehicle(playerid, vehicleid, 0);

                    LobbyInfo[idx][LobbyVehicles][i] = vehicleid;

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_DERBY;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                case LOBBY_TYPE_STUNT:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID)
                    {
                        DestroyVehicle(LobbyInfo[idx][LobbyVehicles][i]);
                        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
                    }

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Shoma vared lobby %s [%d] shodid.", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Shoma vared lobby standard shodid.");
                    SendInfo(playerid, "Noe: %s, Zarfiyat: %d, Zaman: %s, Parameter: %d, Kart: %s, Dastgah: %s, Ramz: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Baraye khorooj az lobby: /lobbyexit");

                    new type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[3] = {14, 0, 0};

                    new vehicleid = CreateVehicle(LobbyInfo[idx][LobbySubject], LobbyPos[type][map][i][0], LobbyPos[type][map][i][1], LobbyPos[type][map][i][2], LobbyPos[type][map][i][3], 1, 1, 120);

                    ResetPlayerWeapons(playerid);
                    set_health(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    LinkVehicleToInterior(vehicleid, interior_map[map]);
                    SetVehicleVirtualWorld(vehicleid, idx);

                    SetPlayerInterior(playerid, interior_map[map]);
                    SetPlayerVirtualWorld(playerid, idx);

                    veh_info[vehicleid][v_locked] = 1;
                    veh_info[vehicleid][v_color] = 1;
                    veh_info[vehicleid][v_model] = LobbyInfo[idx][LobbySubject];
                    veh_info[vehicleid][v_fuel] = 100.0;

                    PutPlayerInVehicle(playerid, vehicleid, 0);

                    LobbyInfo[idx][LobbyVehicles][i] = vehicleid;

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_STUNT;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                case LOBBY_TYPE_PARKOUR:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Shoma vared lobby %s [%d] shodid.", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Shoma vared lobby standard shodid.");
                    SendInfo(playerid, "Noe: %s, Zarfiyat: %d, Zaman: %s, Parameter: %d, Kart: %s, Dastgah: %s, Ramz: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Baraye khorooj az lobby: /lobbyexit");

                    ResetPlayerWeapons(playerid);
                    new sidx = random(20), type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap];
                    SetPlayerSkin(playerid, LobbyInfo[idx][LobbySubject]);
                    set_pos(playerid, LobbyPos[type][map][sidx][0], LobbyPos[type][map][sidx][1], LobbyPos[type][map][sidx][2], LobbyPos[type][map][sidx][3], 0, idx);
                    SetCameraBehindPlayer(playerid);
                    set_health(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_PARKOUR;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                default: return 1;
            }
        }
    }
    SendError(playerid, "Dar in lobby jaye khali mojood nist.");
    return 1;
}

ShowLobby(playerid)
{
    show_dialog(playerid, d_lobby, DIALOG_STYLE_LIST, c_server"Lobby", c_server"[1]"c_white" Lobby list\n"c_server"[2]"c_white" Sakhtan lobby", "Next", "Cancel");
    return 1;
}

ShowLobbyList(playerid)
{
    STRING_GLOBAL[0] = EOS;
    for(new i = 0; i < sizeof(LobbyTypeName); i++)
    {
        new line_string[100];
        format(line_string, sizeof(line_string), c_server"[%d]"c_white" %s\n", i + 1, LobbyTypeName[i]);
        strcat(STRING_GLOBAL, line_string);
    }
    show_dialog(playerid, d_lobby_list, DIALOG_STYLE_LIST, c_server"Lobby List", STRING_GLOBAL, "Next", "Cancel");
    return 1;
}

ShowLobbyCreatedList(playerid, type)
{
    new count;
    STRING_GLOBAL[0] = EOS;

    new line_string[150];

    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1) continue;
        if(LobbyInfo[i][LobbyType] != type) continue;

        switch(type)
        {
            case LOBBY_TYPE_DEATHMATCH:
            {
                if(count == 0) STRING_GLOBAL = "[#] Creator [ID] - Map\tWeapon Name\tFree Slot\tTime\n";
                if(LobbyInfo[i][LobbyCreateID] != -1) format(line_string, sizeof(line_string), c_server"[%d]"c_white" %s [%d] - %s\t%s\t%d\t%s\n", count + 1, get_name(LobbyInfo[i][LobbyCreateID]), LobbyInfo[i][LobbyCreateID], LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], WEAPON_Name[LobbyInfo[i][LobbySubject]], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                else format(line_string, sizeof(line_string), c_server"[%d]"c_white" Server - %s\t%s\t%d\t%s\n", count + 1, LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], WEAPON_Name[LobbyInfo[i][LobbySubject]], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                strcat(STRING_GLOBAL, line_string);
                p_t_info[playerid][p_listitem][count] = i;
                count++;
            }
            case LOBBY_TYPE_RACE, LOBBY_TYPE_DERBY, LOBBY_TYPE_STUNT:
            {
                if(count == 0) STRING_GLOBAL = "[#] Creator [ID] - Map\tVehicle Name\tFree Slot\tTime\n";
                if(LobbyInfo[i][LobbyCreateID] != -1) format(line_string, sizeof(line_string), c_server"[%d]"c_white" %s [%d] - %s\t%s\t%d\t%s\n", count + 1, get_name(LobbyInfo[i][LobbyCreateID]), LobbyInfo[i][LobbyCreateID], LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], vehicle_name[LobbyInfo[i][LobbySubject] -400], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                else format(line_string, sizeof(line_string), c_server"[%d]"c_white" Server - %s\t%s\t%d\t%s\n", count + 1, LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], vehicle_name[LobbyInfo[i][LobbySubject] -400], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                strcat(STRING_GLOBAL, line_string);
                p_t_info[playerid][p_listitem][count] = i;
                count++;
            }
            case LOBBY_TYPE_PARKOUR:
            {
                if(count == 0) STRING_GLOBAL = "[#] Creator [ID] - Map]\tSkin\tFree Slot\tTime\n";
                if(LobbyInfo[i][LobbyCreateID] != -1) format(line_string, sizeof(line_string), c_server"[%d]"c_white" %s [%d] - %s\t%d\t%d\t%s\n", count + 1, get_name(LobbyInfo[i][LobbyCreateID]), LobbyInfo[i][LobbyCreateID], LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], LobbyInfo[i][LobbySubject], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                else format(line_string, sizeof(line_string), c_server"[%d]"c_white" Server - %s\t%d\t%d\t%s\n", count + 1, LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], LobbyInfo[i][LobbySubject], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                strcat(STRING_GLOBAL, line_string);
                p_t_info[playerid][p_listitem][count] = i;
                count++;
            }
        }
    }
    if(!count) return ShowLobbyList(playerid), SendError(playerid, "Hich lobby az in no sakhteh nashode ast.");
    format(line_string, sizeof(line_string), c_server"%s", LobbyTypeName[type - 1]);
    show_dialog(playerid, d_lobby_created_list, DIALOG_STYLE_TABLIST_HEADERS, line_string, STRING_GLOBAL, "Next", "Cancel");
    return 1;
}

ShowLobbyCreate(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
    "c_server"[1]"c_white" Type:\t%s\n\
    "c_server"[2]"c_white" Capacity:\t%d\n\
    "c_server"[3]"c_white" Time:\t%s\n\
    "c_server"[4]"c_white" Parameter:\t%d\n\
    "c_server"[5]"c_white" Map:\t%s\n\
    "c_server"[6]"c_white" Device:\t%s\n\
    "c_server"[7]"c_white" Password:\t%d\n\
    "c_server"[8]"c_white" Create",
    LobbyTypeName[player_lobby_settings[playerid][0]],
    player_lobby_settings[playerid][1],
    ConvertTime(player_lobby_settings[playerid][2], 1),
    player_lobby_settings[playerid][3],
    LobbyMapName[player_lobby_settings[playerid][0]][player_lobby_settings[playerid][4]],
    LobbyDeviceName[player_lobby_settings[playerid][5]],
    player_lobby_settings[playerid][6]);
    show_dialog(playerid, d_lobby_create, DIALOG_STYLE_TABLIST, c_server"Create Lobby", STRING_GLOBAL, "Next", "Cancel");
    return 1;
}

OnPlayerLeaveLobby(playerid, idx, text[])
{
    if(LobbyInfo[idx][LobbyCreateID] == playerid) ClearLobby(idx, "Sazandeh lobby ra tark karde ast.");
    else
    {
        for(new i = 0; i < MAX_PLAYERS_LOBBY; i++)
        {
            if(LobbyInfo[idx][LobbyPlayers][i] == playerid)
            {
                LobbyInfo[idx][LobbyPlayers][i] = INVALID_PLAYER_ID;
                LobbyInfo[idx][LobbyKills][i] = 0;
                LobbyInfo[idx][LobbyDeaths][i] = 0;
                if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID) DestroyVehicle(LobbyInfo[idx][LobbyVehicles][i]);
                LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
            }
        }
    }

    // if(LobbyInfo[idx][LobbyType] == LOBBY_TYPE_PARKOUR) SetPlayerSkinEx(playerid);
    set_pos(playerid, 2049.470, -1908.065, 13.546, 270.0, 0, 0);
    SetCameraBehindPlayer(playerid);
    if(is_fraction_duty {playerid} == 1 && playerFactionStatus(playerid)) SetPlayerColor(playerid, f_info[PlayerInfo[playerid][member]][f_radar_color]);
    else SetPlayerColor(playerid,  0xFFFFFFFF);
    if(PlayerInfo[playerid][admin] > 0) SetPlayerColor(playerid, 0xFFFFFF00);
    ClearDeathMessage(playerid);

    SendInfo(playerid, "Shoma az lobby kharj shodid. Dalil: %s", text);

    ResetPlayerWeapons(playerid);
    for(new a = 0; a < MAX_WEAPONS; a++) GivePlayerWeapon(playerid, PlayerInfo[playerid][Weapon][a], PlayerInfo[playerid][Ammo][a]);
    SetPlayerArmedWeapon(playerid, 0);

    player_lobby_status[playerid] = false;
    player_lobby_type[playerid] = -1;
    player_lobby_idx[playerid] = -1;

    return 1;
}

CMD:lobby(playerid, params[])
{
    if(check_admin_rank(playerid , 8)) return 1;
    ShowLobby(playerid);
    return 1;
}

CMD:lobbystats(playerid, params[])
{
    if(!IsPlayerInAnyDMZone(playerid)) return SendError(playerid, "Shoma dar lobby nistid.");
    new idx = player_lobby_idx[playerid], count;
    if(player_lobby_type[playerid] != LOBBY_TYPE_DEATHMATCH) return SendError(playerid, "Amar faqat dar Deathmatch mojood ast.");
    STRING_GLOBAL = "[#] Nickname [ID]\tKills\tDeaths\n";
    for(new i = 0; i < MAX_PLAYERS_LOBBY; i++)
    {
        new line_string[150];
        if(LobbyInfo[idx][LobbyPlayers][i] != INVALID_PLAYER_ID)
        {
            format(line_string, sizeof(line_string), c_server"[%d]"c_white" %s [%d]\t%d\t%d\n",
            count + 1, get_name(LobbyInfo[idx][LobbyPlayers][i]), LobbyInfo[idx][LobbyPlayers][i], LobbyInfo[idx][LobbyKills][i], LobbyInfo[idx][LobbyDeaths][i]);
            strcat(STRING_GLOBAL, line_string);
            count++;
        }
    }
    if(count == 0) return SendError(playerid, "There are no players in the lobby.");
    show_dialog(playerid, d_none, DIALOG_STYLE_TABLIST_HEADERS, c_server"Lobby statistics", STRING_GLOBAL, "Cancel", "");
    return 1;
}

CMD:lobbyexit(playerid, params[])
{
    if(!IsPlayerInAnyDMZone(playerid)) return SendError(playerid, "Shoma dar lobby nistid.");
    OnPlayerLeaveLobby(playerid, player_lobby_idx[playerid], "/lobbyexit");
    return 1;
}

CMD:exitdm(playerid, params[])
{
    if(!IsPlayerInAnyDMZone(playerid)) return SendError(playerid, "Shoma dar lobby nistid.");
    OnPlayerLeaveLobby(playerid, player_lobby_idx[playerid], "/exitdm");
    return 1;
}


CMD:dmexit(playerid, params[])
{
    if(!IsPlayerInAnyDMZone(playerid)) return SendError(playerid, "Shoma dar lobby nistid.");
    OnPlayerLeaveLobby(playerid, player_lobby_idx[playerid], "/dmexit");
    return 1;
}

ClearDeathMessage(playerid)
{
    for(new j = 0; j < 5; j++) SendDeathMessageToPlayer(playerid, 1001, 1001, 200);
}

stock IsPlayerInAnyDMZone(playerid) return player_lobby_status[playerid] != false || player_lobby_idx[playerid] != -1 ? true : false;