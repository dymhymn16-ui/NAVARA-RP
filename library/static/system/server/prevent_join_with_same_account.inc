public OnPlayerConnect(playerid)
{
	//----------------
    /*new temp_nick_name[MAX_PLAYER_NAME], count_nicknames;
	GetPlayerName(playerid, temp_nick_name, MAX_PLAYER_NAME);
	foreach(new i : Player)
    {
        if (!strcmp(temp_nick_name, PlayerInfo[i][name], true)) {
            count_nicknames++;
        }
    }
	if(count_nicknames >= 2) {
		SendClientMessage(playerid, 0x6AA049FF, "CONNECTION REJECTED: Unacceptable NickName");
		SendClientMessage(playerid, 0x6AA049FF, "Please choose another nick between and 3-20 characters");
		SendClientMessage(playerid, 0x6AA049FF, "Please use only a-z, A-Z, 0-9");
		SendClientMessage(playerid, 0x6AA049FF, "Use /quit to exit or press ESC and select Quit Game");
		kick_player(playerid);
		return 0;
	}*/
	//----------------

	#if defined PJWSA_OnPlayerConnect
		return PJWSA_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect PJWSA_OnPlayerConnect
#if defined PJWSA_OnPlayerConnect
	forward PJWSA_OnPlayerConnect(playerid);
#endif