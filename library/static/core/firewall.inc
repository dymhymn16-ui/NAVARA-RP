new IncomingRequests[MAX_PLAYERS];
new PlayerIPs[MAX_PLAYERS][16];
new bool:HasJoined[MAX_PLAYERS];
new PlayerIncomingRequestsTimer[MAX_PLAYERS];

public OnIncomingConnection(playerid, ip_address[], port)
{
    IncomingRequests[playerid] = GetTickCount();

    format(PlayerIPs[playerid], 16, "%s", ip_address);

    HasJoined[playerid] = false;

    PlayerIncomingRequestsTimer[playerid] = SetTimerEx("CheckConnection", 10000, false, "d", playerid);

    return 1;
}

public OnPlayerConnect(playerid)
{
    ClearPlayerConnectionData(playerid);

    #if defined Firewall_OnPlayerConnect
        return Firewall_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect Firewall_OnPlayerConnect
#if defined Firewall_OnPlayerConnect
    forward Firewall_OnPlayerConnect(playerid);
#endif

callback: CheckConnection(playerid)
{
    if (playerid < 0 || playerid >= MAX_PLAYERS) return;

    if (!HasJoined[playerid] && PlayerIPs[playerid][0] != '\0')
    {

        if(!isBotPlayer(playerid)) {
            // BlockIpAddress(PlayerIPs[playerid], 7000);
            // printf("Blocking %s for not joining after connection request.", PlayerIPs[playerid]);
            AdminMes(""c_server"* A.INFO:"c_grey" %s not joining after connection request.", PlayerIPs[playerid]);
        }
    }

    ClearPlayerConnectionData(playerid);
}

public OnPlayerDisconnect(playerid, reason)
{
    ClearPlayerConnectionData(playerid);
    
    #if defined Firewall_OnPlayerDisconnect
        return Firewall_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect Firewall_OnPlayerDisconnect
#if defined Firewall_OnPlayerDisconnect
    forward Firewall_OnPlayerDisconnect(playerid, reason);
#endif

stock ClearPlayerConnectionData(playerid)
{
    IncomingRequests[playerid] = 0;
    PlayerIPs[playerid][0] = '\0';
    HasJoined[playerid] = false;

    KillTimer(PlayerIncomingRequestsTimer[playerid]);
}