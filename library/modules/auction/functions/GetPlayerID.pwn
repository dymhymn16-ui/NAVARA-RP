stock GetPlayerID(const pname[])
{
	if(isnull(pname)) return -1;

	foreach(new i : logged_players) 
	{
		if(!strcmp(PlayerInfo[i][name], pname, false)) return i;
	}
	return -1;
}