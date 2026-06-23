#define VOTE_TIME_MIN 15
#define VOTE_TIME_MAX 70

static VoteTime,
    bool:Vote_YES[MAX_PLAYERS],
    bool:Vote_NO[MAX_PLAYERS],
    bool:VotePlayerTD[MAX_PLAYERS],
    last_vote_colorboxes,
    StartVote_Time[MAX_PLAYERS],
    StartVote_Text[MAX_PLAYERS][110];

static Text:TD_Vote[12];

LoadVoteTextdraws() {
	TD_Vote[0] = TextDrawCreate(517.399536, 258.637817, "box");
	TextDrawLetterSize(TD_Vote[0], 0.000000, 5.800000);
	TextDrawTextSize(TD_Vote[0], 627.595214, 0.000000);
	TextDrawAlignment(TD_Vote[0], 1);
	TextDrawColor(TD_Vote[0], -1);
	TextDrawUseBox(TD_Vote[0], 1);
	TextDrawBoxColor(TD_Vote[0], 137);
	TextDrawSetShadow(TD_Vote[0], 0);
	TextDrawBackgroundColor(TD_Vote[0], 255);
	TextDrawFont(TD_Vote[0], 1);
	TextDrawSetProportional(TD_Vote[0], 1);

	TD_Vote[1] = TextDrawCreate(517.500366, 258.774871, "box");
	TextDrawLetterSize(TD_Vote[1], 0.000000, 0.095999);
	TextDrawTextSize(TD_Vote[1], 627.959838, 0.000000);
	TextDrawAlignment(TD_Vote[1], 1);
	TextDrawColor(TD_Vote[1], -1);
	TextDrawUseBox(TD_Vote[1], 1);
	TextDrawBoxColor(TD_Vote[1], 8388863);
	TextDrawSetShadow(TD_Vote[1], 0);
	TextDrawBackgroundColor(TD_Vote[1], 255);
	TextDrawFont(TD_Vote[1], 1);
	TextDrawSetProportional(TD_Vote[1], 1);

	TD_Vote[2] = TextDrawCreate(571.199951, 243.974609, "-");
	TextDrawLetterSize(TD_Vote[2], 5.000000, 2.643124);
	TextDrawAlignment(TD_Vote[2], 2);
	TextDrawColor(TD_Vote[2], 10158335);
	TextDrawSetShadow(TD_Vote[2], 0);
	TextDrawBackgroundColor(TD_Vote[2], 255);
	TextDrawFont(TD_Vote[2], 1);
	TextDrawSetProportional(TD_Vote[2], 1);

	TD_Vote[3] = TextDrawCreate(517.500305, 310.000000, "box");
	TextDrawLetterSize(TD_Vote[3], 0.000000, 0.095999);
	TextDrawTextSize(TD_Vote[3], 627.959777, 0.000000);
	TextDrawAlignment(TD_Vote[3], 1);
	TextDrawColor(TD_Vote[3], -1);
	TextDrawUseBox(TD_Vote[3], 1);
	TextDrawBoxColor(TD_Vote[3], 8388863);
	TextDrawSetShadow(TD_Vote[3], 0);
	TextDrawBackgroundColor(TD_Vote[3], 255);
	TextDrawFont(TD_Vote[3], 1);
	TextDrawSetProportional(TD_Vote[3], 1);

	TD_Vote[4] = TextDrawCreate(571.199951, 295.077728, "-");
	TextDrawLetterSize(TD_Vote[4], 5.000000, 2.643124);
	TextDrawAlignment(TD_Vote[4], 2);
	TextDrawColor(TD_Vote[4], 10158335);
	TextDrawSetShadow(TD_Vote[4], 0);
	TextDrawBackgroundColor(TD_Vote[4], 255);
	TextDrawFont(TD_Vote[4], 1);
	TextDrawSetProportional(TD_Vote[4], 1);

	TD_Vote[5] = TextDrawCreate(519.599975, 262.512573, "Yes");
	TextDrawLetterSize(TD_Vote[5], 0.258499, 1.066250);
	TextDrawAlignment(TD_Vote[5], 1);
	TextDrawColor(TD_Vote[5], 16711935);
	TextDrawSetShadow(TD_Vote[5], 0);
	TextDrawSetOutline(TD_Vote[5], 1);
	TextDrawBackgroundColor(TD_Vote[5], 255);
	TextDrawFont(TD_Vote[5], 2);
	TextDrawSetProportional(TD_Vote[5], 1);

	TD_Vote[6] = TextDrawCreate(610.295043, 262.512573, "No");
	TextDrawLetterSize(TD_Vote[6], 0.258499, 1.066250);
	TextDrawAlignment(TD_Vote[6], 1);
	TextDrawColor(TD_Vote[6], -16776961);
	TextDrawSetShadow(TD_Vote[6], 0);
	TextDrawSetOutline(TD_Vote[6], 1);
	TextDrawBackgroundColor(TD_Vote[6], 255);
	TextDrawFont(TD_Vote[6], 2);
	TextDrawSetProportional(TD_Vote[6], 1);

	TD_Vote[7] = TextDrawCreate(530.197387, 271.813140, "");
	TextDrawLetterSize(TD_Vote[7], 0.286499, 1.016250);
	TextDrawAlignment(TD_Vote[7], 2);
	TextDrawColor(TD_Vote[7], -1);
	TextDrawSetShadow(TD_Vote[7], 0);
	TextDrawSetOutline(TD_Vote[7], 1);
	TextDrawBackgroundColor(TD_Vote[7], 255);
	TextDrawFont(TD_Vote[7], 3);
	TextDrawSetProportional(TD_Vote[7], 1);

	TD_Vote[8] = TextDrawCreate(617.800537, 271.813140, " ");
	TextDrawLetterSize(TD_Vote[8], 0.286499, 1.016250);
	TextDrawAlignment(TD_Vote[8], 2);
	TextDrawColor(TD_Vote[8], -1);
	TextDrawSetShadow(TD_Vote[8], 0);
	TextDrawSetOutline(TD_Vote[8], 1);
	TextDrawBackgroundColor(TD_Vote[8], 255);
	TextDrawFont(TD_Vote[8], 3);
	TextDrawSetProportional(TD_Vote[8], 1);

	TD_Vote[9] = TextDrawCreate(562.099975, 261.850006, "VOTE");
	TextDrawLetterSize(TD_Vote[9], 0.189999, 0.799375);
	TextDrawAlignment(TD_Vote[9], 1);
	TextDrawColor(TD_Vote[9], -1);
	TextDrawSetShadow(TD_Vote[9], 0);
	TextDrawSetOutline(TD_Vote[9], 1);
	TextDrawBackgroundColor(TD_Vote[9], 255);
	TextDrawFont(TD_Vote[9], 2);
	TextDrawSetProportional(TD_Vote[9], 1);

	TD_Vote[10] = TextDrawCreate(574.300292, 281.962585, " "); //Mosabeghe Duel
	TextDrawLetterSize(TD_Vote[10], 0.288000, 1.661249);
	TextDrawTextSize(TD_Vote[10], 0.000000, 1945.000000);
	TextDrawAlignment(TD_Vote[10], 2);
	TextDrawColor(TD_Vote[10], -1);
	TextDrawSetShadow(TD_Vote[10], 0);
	TextDrawSetOutline(TD_Vote[10], 1);
	TextDrawBackgroundColor(TD_Vote[10], 255);
	TextDrawFont(TD_Vote[10], 1);
	TextDrawSetProportional(TD_Vote[10], 1);

	TD_Vote[11] = TextDrawCreate(562.099975, 299.652313, " "); //01:32
	TextDrawLetterSize(TD_Vote[11], 0.189999, 0.799375);
	TextDrawAlignment(TD_Vote[11], 1);
	TextDrawColor(TD_Vote[11], -1);
	TextDrawSetShadow(TD_Vote[11], 0);
	TextDrawSetOutline(TD_Vote[11], 1);
	TextDrawBackgroundColor(TD_Vote[11], 255);
	TextDrawFont(TD_Vote[11], 2);
	TextDrawSetProportional(TD_Vote[11], 1);
}

public OnPlayerDisconnect(playerid, reason)
{
	VotePlayerTD[playerid] = false;

	#if defined VoteSystem_OnPlayerDisconnect
		return VoteSystem_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect VoteSystem_OnPlayerDisconnect
#if defined VoteSystem_OnPlayerDisconnect
	forward VoteSystem_OnPlayerDisconnect(playerid, reason);
#endif


public OnPlayerSpawn(playerid)
{
	if(VoteTime > 0 && !VotePlayerTD[playerid])
	{
		VotePlayerTD[playerid] = true;
		for(new TD; TD < sizeof(TD_Vote); TD++) TextDrawShowForPlayer(playerid, TD_Vote[TD]);
	}

	#if defined VoteSystem_OnPlayerSpawn
		return VoteSystem_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn VoteSystem_OnPlayerSpawn
#if defined VoteSystem_OnPlayerSpawn
	forward VoteSystem_OnPlayerSpawn(playerid);
#endif

VoteSystemOnDialogResponse(playerid, dialogid, response, inputtext[])
{
	if (dialogid == DIALOG_START_VOTE) {
		Dialog_StartVote(playerid, response, inputtext);
		return 1;
	}
	return 0;
}

CMD:vote(playerid, params[])
{
    if(VoteTime > 0)
    {
		SendClientMessage(playerid, col_gray, "ERROR: Vote Ghablen Sakhte Shode.");
		return 1;
    }
    new vtime, Text[200];
    if(sscanf(params, "is[200]", vtime, Text))
    {
	    SendClientMessage(playerid, col_white, "USAGE: /Vote ({F3B31D}Zaman"c_white") ({F3B31D}Matn"c_white")");
	    return 1;
    }
    if(vtime < VOTE_TIME_MIN || vtime > VOTE_TIME_MAX)
    {
	    SendClientMessage(playerid, col_gray, "ERROR: Invalid Time. "#VOTE_TIME_MIN" - "#VOTE_TIME_MAX" seconds");
	    return 1;
    }

    format(StartVote_Text[playerid], 110, "%s", Text);
    StartVote_Time[playerid] = vtime;

    show_dialog(playerid, DIALOG_START_VOTE, DIALOG_STYLE_INPUT, "{FFFF00}Start Vote", "{ffffff}Lotfan Kholase In Vote Ra Dar Kader Zir Benevisid.\n{ffffff}Maslan: {FFFF00}\"Event Car War\"", "Start", "Cancel");
    return 1;
}

static Dialog_StartVote(playerid, response, inputtext[]) {
    if (!response)
        return 1;

    if(VoteTime > 0)
    {
        SendClientMessage(playerid, col_gray, "ERROR: Vote Ghablen Sakhte Shode.");
        return 1;
    }

    if(strlen(inputtext) > 14)
        return show_dialog(playerid, DIALOG_START_VOTE, DIALOG_STYLE_INPUT, "{FFFF00}Start Vote", "{ffffff}Lotfan Kholase In Vote Ra Dar Kader Zir Benevisid.\n{ffffff}Maslan: {FFFF00}\"Event Car War\"\n\n{FF0000}Tedade Horof Nabayad Bishtar Az 14 Bashad.", "Start", "Cancel");

    TextDrawSetString(TD_Vote[10], inputtext);
    TextDrawColor(TD_Vote[2], 10158335);
    TextDrawBoxColor(TD_Vote[1], 8388863);
    TextDrawColor(TD_Vote[4], 10158335);
    TextDrawBoxColor(TD_Vote[3], 8388863);

    last_vote_colorboxes = -1;

    TextDrawSetString(TD_Vote[7], "0");
    TextDrawSetString(TD_Vote[8], "0");
    new string[200];
    VoteTime = StartVote_Time[playerid];
    format(string, 15, "%02d:%02d", VoteTime / 60, VoteTime % 60);
    TextDrawSetString(TD_Vote[11], string);
    foreach(new i : Player)
    {
        Vote_YES[i] = false;
        Vote_NO[i] = false;
        if(IsPlayerSpawned(i))
        {
           VotePlayerTD[i] = true;
           for(new TD; TD < sizeof(TD_Vote); TD++)
           {
               TextDrawShowForPlayer(i, TD_Vote[TD]);
           }
        }
    }
    format(string, sizeof string, "[Vote] {FFFFA6}Admin {FF8000}%s(%i) {FFFFA6}Yek Vote Ra Start Kard. Baraye Sherkat Az (/Yes) Ya (/No) Estefade Konid!", Name(playerid), playerid), SendClientMessageToAll(COLOR_YELLOW, string);
    format(string, sizeof string, "[Matn Vote] {FF8000}%s", StartVote_Text[playerid]), SendClientMessageToAll(COLOR_YELLOW, string);
    return 1;
}

CMD_Vote_Yes(playerid)
{
     if(VoteTime < 1)
     {
        return 0;
     }
     if(Vote_YES[playerid] || Vote_NO[playerid])
     {
        return 0;
     }
     GameTextForPlayer(playerid,"Vote Shoma Sabt Shod.~N~~G~(Yes)", 3000, 3);
     Vote_YES[playerid] = true;
     return 1;
}

CMD_Vote_No(playerid)
{
     if(VoteTime < 1)
     {
        return 0;
     }
     if(Vote_YES[playerid] || Vote_NO[playerid])
     {
        return 0;
     }
     GameTextForPlayer(playerid,"Vote Shoma Sabt Shod.~N~~R~(No)", 3000, 3);
     Vote_NO[playerid] = true;
     return 1;
}

VoteTimer()
{
     VoteTime--;
     if(VoteTime > 0)
     {
        new string[48], time = VoteTime, vote_1 = CountVotes(1), vote_0 = CountVotes(0);
        format(string, sizeof string, "%d", vote_1);
        TextDrawSetString(TD_Vote[7], string);
        format(string, sizeof string, "%d", vote_0);
        TextDrawSetString(TD_Vote[8], string);
        format(string, sizeof string, "%02d:%02d", time / 60, time % 60);
        TextDrawSetString(TD_Vote[11], string);

        if (vote_0 > vote_1 && last_vote_colorboxes != 0) {
            last_vote_colorboxes = 0;
            TextDrawBoxColor(TD_Vote[1], -2147483393);
            TextDrawColor(TD_Vote[2], -1476394753);
            TextDrawBoxColor(TD_Vote[3], -2147483393);
            TextDrawColor(TD_Vote[4], -1476394753);

            foreach(new i : Player)
            {
               if(VotePlayerTD[i] != false) {
               
                   TextDrawShowForPlayer(i, TD_Vote[1]);
                   TextDrawShowForPlayer(i, TD_Vote[2]);
                   TextDrawShowForPlayer(i, TD_Vote[3]);
                   TextDrawShowForPlayer(i, TD_Vote[4]);
               }
            }

        }

        if (vote_1 > vote_0 && last_vote_colorboxes != 1) {
            last_vote_colorboxes = 1;
            TextDrawBoxColor(TD_Vote[1], 8388863);
            TextDrawColor(TD_Vote[2], 10158335);
            TextDrawBoxColor(TD_Vote[3], 8388863);
            TextDrawColor(TD_Vote[4], 10158335);

            foreach(new i : Player)
            {
               if(VotePlayerTD[i] != false) {
               
                   TextDrawShowForPlayer(i, TD_Vote[1]);
                   TextDrawShowForPlayer(i, TD_Vote[2]);
                   TextDrawShowForPlayer(i, TD_Vote[3]);
                   TextDrawShowForPlayer(i, TD_Vote[4]);
               }
            }

        }

        if (vote_1 == vote_0 && vote_1 > 0 && vote_0 > 0 && last_vote_colorboxes != 2) {
            last_vote_colorboxes = 2;
            TextDrawBoxColor(TD_Vote[1], 0xFFFF20FF);
            TextDrawColor(TD_Vote[2], 0xFFFF40FF);
            TextDrawBoxColor(TD_Vote[3], 0xFFFF20FF);
            TextDrawColor(TD_Vote[4], 0xFFFF40FF);

            foreach(new i : Player)
            {
               if(VotePlayerTD[i] != false) {
               
                   TextDrawShowForPlayer(i, TD_Vote[1]);
                   TextDrawShowForPlayer(i, TD_Vote[2]);
                   TextDrawShowForPlayer(i, TD_Vote[3]);
                   TextDrawShowForPlayer(i, TD_Vote[4]);
               }
            }

        }

     }
     else if(VoteTime == 0)
     {
        VoteTime = -1;
        
        new string[128], string2[300] = ">> {FF8000}[Yes]: {FFFFCE}", string3[300] = ">> {FF8000}[No]: {FFFFCE}", count_votes[2];
        count_votes[0] = CountVotes(0); //no
        count_votes[1] = CountVotes(1); //yes
        if((count_votes[1] > 0 || count_votes[0] > 0) && (count_votes[1] != count_votes[0])) format(string, sizeof string, "Tedad Vote Yes: {FF8000}%i {FFFF00}| Tedad Vote No: {FF8000}%i {FFFF00} >> {FF8000} Bishtarin Vote: %s", count_votes[1], count_votes[0], (count_votes[0] < count_votes[1]) ? ("Yes") : ("No"));
        if(count_votes[1] == count_votes[0]) format(string, sizeof string, "Tedad Vote Yes: {FF8000}%i {FFFF00}| Tedad Vote No: {FF8000}%i {FFFF00} >> {FF8000} Bishtarin Vote: Mosavi", count_votes[1], count_votes[0]);
        
        new n_count, y_count;
        foreach(new i : Player)
        {
            if(Vote_YES[i]) {

                if (y_count == 0)
                    format(string2, sizeof string2, "%s%s ", string2, Name(i));
                else
                    format(string2, sizeof string2, "%s, %s ", string2, Name(i));

                y_count++;
                
            }
            if(Vote_NO[i]) {

                if(n_count == 0)
                    format(string3, sizeof string3, "%s%s ", string3, Name(i));
                else
                    format(string3, sizeof string3, "%s, %s ", string3, Name(i));

                n_count++;
            }

            VotePlayerTD[i] = false;
            for(new TD; TD < sizeof(TD_Vote); TD++) TextDrawHideForPlayer(i, TD_Vote[TD]);
        }
        SendClientMessageToAll(0xFFFF00FF, " ");
        SendClientMessageToAll(0xFFFF00FF, "====================================================");
        SendClientMessageToAll(0xFFFF00FF, string);
        if(strlen(string2) >= 10) strcat(string2, "Yes <<"), SendClientMessageToAll(0xFFFF00FF, string2);
        if(strlen(string3) >= 9) strcat(string3, "No <<"), SendClientMessageToAll(0xFFFF00FF, string3);
        //SendClientMessageToAll(0xFFFF00FF, "[Vote] {FF8000}Zaman Vote Be Paian Resid.");
        SendClientMessageToAll(0xFFFF00FF, "====================================================");
        SendClientMessageToAll(0xFFFF00FF, " ");
     }
     return 1;
}

stock CountVotes(Vote) //0 = no | 1 = yes
{
     new count;
     foreach(new i : Player)
     {
        if(Vote == 1)
        {
           if(Vote_YES[i])
           {
              count++;
           }
        } 
        else if(Vote == 0)
        {
           if(Vote_NO[i])
           {
              count++;
           }
        }
     }
     return count;
}

stock IsVoteStarted()
{
    return VoteTime > 0 ? true : false;
}