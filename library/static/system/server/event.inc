cmd:event(playerid,params[])
{
	if(check_admin_rank(playerid , 7)) return 1;
	if(sscanf(params, "dddd", params[0], params[1], params[3], params[4])) return SendClientMessage(playerid, col_gray, !"Enter: "c_white"/event [min level] [max level] [amount] [type]");

	switch(params[4])
	{
		case 1:
		{
			foreach(new i: logged_players)
			{
				if(PlayerInfo[i][level] < params[0] || PlayerInfo[i][level] > params[1]) continue;

				give_money(i, params[3]);

				new scm_string[144];
				format(scm_string, sizeof(scm_string ), c_yellow_h"[Tavajoh] "c_white"%s"c_server" Be Player haye Level %d Ta %d "c_white"$%s"c_server" Pool Dad!", PlayerInfo[playerid][name], params[0], params[1], convert_money(params[3]));
				SendClientMessage(i, col_gray, scm_string);
			}
		}
		case 2:
		{
			foreach(new i: logged_players)
			{
				if(PlayerInfo[i][level] < params[0] || PlayerInfo[i][level] > params[1]) continue;

				give_donate(i, params[3]);

				GameTextForPlayer(i, "~y~+Donate", 2000, 1);

				new scm_string[144];
				format(scm_string, sizeof(scm_string ), c_yellow_h"[Tavajoh] "c_white"%s"c_server" Be Player haye Level %d Ta %d "c_red"%d"c_server" R-COIN Dad!", PlayerInfo[playerid][name], params[0], params[1], params[3]);
				SendClientMessage(i, col_gray, scm_string);
			}
		}
		case 3:
		{
			foreach(new i: logged_players)
			{
				if(PlayerInfo[i][level] < params[0] || PlayerInfo[i][level] > params[1]) continue;

				PlayerInfo[i][exp] += params[3];

				PlayerLevelUpdateCheck(i);

				GameTextForPlayer(i, "~g~+EXP", 2000, 1);
				
				new scm_string[144];
				format(scm_string, sizeof(scm_string ), c_yellow_h"[Tavajoh] "c_white"%s"c_server" Be Player haye Level %d Ta %d "c_white"%d"c_server" EXP Dad!", PlayerInfo[playerid][name], params[0], params[1], params[3]);
				SendClientMessage(i, col_gray, scm_string);
			}
		}
		case 4:
		{
			foreach(new i: logged_players)
			{
				if(PlayerInfo[i][level] < params[0] || PlayerInfo[i][level] > params[1]) continue;

				PlayerInfo[i][level] += params[3];

				PlayerLevelUpdateCheck(i);

				GameTextForPlayer(i, "~g~+Level", 2000, 1);
				
				new scm_string[144];
				format(scm_string, sizeof(scm_string ), c_yellow_h"[Tavajoh] "c_white"%s"c_server" Be Player haye Level %d Ta %d "c_white"%d"c_server" Level dad!", PlayerInfo[playerid][name], params[0], params[1], params[3]);
				SendClientMessage(i, col_gray, scm_string);
			}
		}
	}

	return 1;
}

////////////////////////////////////////////////////////////////

new fastEventStatus,
	fastEventResult[100],
	fastEventMoney;

cmd:fastevent(playerid, params[])
{
	if(check_admin_rank(playerid , 3)) return 1;

	if(sscanf(params, "s", params[0])) return SendClientMessage(playerid, col_white, !""scm_info"Enter: /fastevent [Matn]");

	fastEventMoney = 4500+(random(100)*random(100));

	new string_fe[200];
	format(string_fe, sizeof string_fe, "{FF0000}[FAST-EVENT]: {FFFF00}Harki Zood Tar Benevise {228B22}%s {FFFF00}Jayeze Migire :D", params[0]);
	SendClientMessageToAll(col_gray, string_fe);

	strmid(fastEventResult, params[0], 0, strlen(params[0]), 100);

	fastEventStatus = 1;
	SetTimer("clearFastEvent", 10000, 0);

	return 1;
}

stock clearFastEvent()
{
	if(fastEventStatus == 1)
	{
		fastEventStatus = 0;
		fastEventMoney = 0;
	}
	
	return 1;
}

stock checkFastEvent(playerid, string[], fecmd = 0)
{
	new ecmd[100];
    strcat(ecmd, string);
    if(fecmd) strins(ecmd, "/", 0);

	if(fastEventStatus == 1 && (!strcmp(string, fastEventResult) || !strcmp(ecmd, fastEventResult)))
	{
		new text_fe[250];

		format(text_fe, sizeof(text_fe), "{FF0000}[FAST-EVENT]: {FF4500}%s{FFFF00} Zod Tar Az Hame Nevesht{228B22} %s {FFFF00}Va{DC143C} $%s {FFFF00}Jayeze Gereft", PlayerInfo[playerid][name], fastEventResult, convert_money(fastEventMoney));
		
 		SendClientMessageToAll(col_gray, text_fe);

		give_money(playerid, fastEventMoney);
		fastEventStatus = 0;
		fastEventMoney = 0;

		return 1;
	}

	return 0;
}