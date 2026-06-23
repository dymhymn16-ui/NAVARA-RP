#if !defined ADV_MUTE_TIME_STR
	#define ADV_MUTE_TIME_STR "1:00"
#endif

#if !defined ADV_MUTE_MINUTE
	#define ADV_MUTE_MINUTE 60
#endif

#if !defined INSULT_MUTE_TIME_STR
	#define INSULT_MUTE_TIME_STR "0:30"
#endif

#if !defined INSULT_MUTE_MINUTE
	#define INSULT_MUTE_MINUTE 30
#endif

// ------------------------------------------------------------------

static 
	enum Insult_Texts_Enum {
		Text[20]
	};

static
	Insult_Texts[][Insult_Texts_Enum] = {

		{"kosnane"},
		{"madarjende"},
		{"kosmadar"},
		{"haromi"},
		{"mader"},
		{"Namos"}

	};

// ------------------------------------------------------------------

static 
	enum Adv_Texts_Enum {
		Text[20],
		Max_Attempts
	};

static
	Adv_Texts[][Adv_Texts_Enum] = {

		{"Gaming", 5},
		{"iranrp", 2},
		{"rgta", 2},
		{"alpha", 2},
		{"oxin", 2},
		{"iranroleplay", 2},
		{"rgtarp", 2},

		{"185.", 1},

		{"7777", 1},
		{":7777", 1},
		{"7.7.7.7", 1},
		{"7 7 7 7", 1},

		{"8888", 1},
		{":8888", 1},
		{"8.8.8.8", 1},

		{"7788", 1},
		{":7788", 1},

		{".ir", 1},
		{".com", 1},
		{"www.", 1},

		{"arsacia", 1},
		{"alpha", 2},

		{"iran roleplay", 2},

		{"TGSAMP", 1},

		{"5.57", 1},
		{"39.11", 1},

		{"suncity", 1},

		{"morix", 2},
		{"45.", 1},
		{".18.75", 1},

		{"3.14.25", 1},
		{"Rbt RolePlay", 1},

		{"Gotham", 1},
		{"Gatham", 1}
	},

	Player_Adv_Texts_Attempts[MAX_PLAYERS][sizeof Adv_Texts];

// ------------------------------------------------------------------

stock IsTextContainsADS(const text[]) {

	for(new a; a < sizeof Adv_Texts; a++) {
		if (strfind(text, Adv_Texts[a][Text], true) != -1) {
			return a;
		}
	}

    return -1;
}

// ------------------------------------------------------------------

stock IsTextContainsInsult(const text[]) {

	for(new a; a < sizeof Insult_Texts; a++) {
		if (strfind(text, Insult_Texts[a][Text], true) != -1) {
			return a;
		}
	}

    return -1;
}

// ------------------------------------------------------------------

static IsStringContainsIP(const szStr[], bool:fixedSeparation = false, bool:ignoreNegatives = false, bool:ranges = true) 
{
    new 
        i = 0, ch_b, lastCh, len = strlen(szStr), trueIPInts = 0, bool:isNumNegative = false, bool:numIsValid = true,
        numberFound = -1, numLen = 0, numStr[5], numSize = sizeof(numStr),
        lastSpacingPos = -1, numSpacingDiff, numLastSpacingDiff, numSpacingDiffCount
    ;
    while(i <= len)
    {
        lastCh = ch_b;
        ch_b = szStr[i];
        if(ch_b >= '0' && ch_b <= '9' || (ranges == true && ch_b == '*')) {
            if(numIsValid && numLen < numSize) {
                if(lastCh == '-') {
                    if(numLen == 0 && ignoreNegatives == false) {
                        isNumNegative = true;
                    }
                    else if(numLen > 0) {
                        numIsValid = false;
                    }
                }
                numberFound = strval(numStr);
                if(numLen == (3 + _:isNumNegative) && !(numberFound >= -255 && numberFound <= 255)) { // IP Num is valid up to 4 characters.. -255
                    for(numLen = 3; numLen > 0; numLen--) {
                        numStr[numLen] = EOS;
                    }
                }
                else if(lastCh == '-' && ignoreNegatives) {
                    i++;
                    continue;
                } else {
                    if(numLen == 0 && numIsValid == true && isNumNegative == true && lastCh == '-') {
                        numStr[numLen++] = lastCh;
                    }
                    numStr[numLen++] = ch_b;
                }
            }
        } else {
            if(numLen && numIsValid) {
                numberFound = strval(numStr);
                if(numberFound >= -255 && numberFound <= 255) {
                    if(fixedSeparation) {
                        if(lastSpacingPos != -1) {
                            numLastSpacingDiff = numSpacingDiff;
                            numSpacingDiff = i - lastSpacingPos - numLen;
                            if(trueIPInts == 1 || numSpacingDiff == numLastSpacingDiff) {
                                ++numSpacingDiffCount;
                            }
                        }
                        lastSpacingPos = i;
                    }
                    if(++trueIPInts >= 4) {
                        break;
                    }
                }
                for(numLen = 3; numLen > 0; numLen--) {
                    numStr[numLen] = EOS;
                }
                isNumNegative = false;
            } else {
                numIsValid = true;
            }
        }
        i++;
    }
    if(fixedSeparation == true && numSpacingDiffCount < 3) {
        return 0;
    }
    return (trueIPInts >= 4);
}

// ------------------------------------------------------------------

stock CheckForAdvTexts(playerid, text[])
{
	/* String Length Check */
	if (isnull(text)) return false;
	if (strlen(text) < 1) return false;

	/* Admin */
	if (PlayerInfo[playerid][admin] > 7) return false;

	new 
		advertisement = IsTextContainsADS(text);

	if(advertisement != -1) 
	{
		/* Allowed */
		if (
			!strcmp(text, "Gaming") ||

			!strcmp(text, "7777") ||
			!strcmp(text, "77777") ||
			!strcmp(text, "777777") ||

			!strcmp(text, "7788") ||

			!strcmp(text, "8888") ||
			!strcmp(text, "88888") ||
			!strcmp(text, "888888") ||

			strfind(text, "mihanrp.ir", true) != -1
			) 
			return false;

		Player_Adv_Texts_Attempts[playerid][advertisement]++;

		if(Player_Adv_Texts_Attempts[playerid][advertisement] >= Adv_Texts[advertisement][Max_Attempts])
		{

			new 
				string[200],
				str[64];

			PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);

			texture_load_mode(playerid, 5000);

			format(string, 144, "AdmBot issued a chat mute to player %s for %d minutes. Reason: Advertising", 
				GetName(playerid), ADV_MUTE_MINUTE);

			foreach(new i: logged_players)
			{
				SendClientMessage(i, 0xFF4F4FFF, string);
			}

			GameTextForPlayer(playerid, "~r~~h~Tabligh Nakonid!", 5000, 3);
			SendClientMessage(playerid, 0xC0C0C0FF, " ");
			SendClientMessage(playerid, 0xC0C0C0FF, "You are muted for {FF9B9B}"#ADV_MUTE_TIME_STR" {C0C0C0}hour due to {FF6464}advertisement text{C0C0C0}!"); //{E46663}+1 Warning
			SendClientMessage(playerid, 0xC0C0C0FF, " ");
			
			PlayerInfo[playerid][mute] = 60 * ADV_MUTE_MINUTE;
			CallRemoteFunction("SV_RemoveVoice", "d", playerid);
			
			format(string, 144, "[ADVERTISEMENT] {DA302C}%s(%d) {E46663}muted for say {FFFFFF}: {FFBFBF}%s", 
				GetName(playerid), 
				playerid, 
				text);

			format(str, sizeof str, "[WORD] {DA302C}%s", 
				Adv_Texts[advertisement][Text]);

			foreach(new i: admin_players)
			{
				SendClientMessage(i, 0xE46663FF, string);
				SendClientMessage(i, 0xE46663FF, str);
			}

			// -----------------------
			// log

			new File:lFile;

			new year, month, day;
		    getdate(year, month, day);

			format(string, sizeof(string), "[%i-%02d-%02d | %02d:%02d]: \"%s\": %s [%s]\r\n", 
				year, month, day, timestamp_hour, timestamp_minute, 
				GetName(playerid), 
				text, 
				Adv_Texts[advertisement][Text]);

		    lFile = fopen("tablighat.txt", io_append);
		    fwrite(lFile, string);
		    fclose(lFile);

			return true;
		}
	}
	else
	{
		/* IP Address Search */
		if(IsStringContainsIP(text)) 
		{
			/* Allowed */
			if(strfind(text, "mihanrp.ir", true) != -1 || 
				strfind(text, "5.57.32.20") != -1)
				return false;

			new 
				string[200];

			PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);

			texture_load_mode(playerid, 5000);

			format(string, 144, "AdmBot issued a chat mute to player %s for %d minutes. Reason: Advertising", 
				GetName(playerid), ADV_MUTE_MINUTE);

			foreach(new i: logged_players)
			{
				SendClientMessage(i, 0xFF4F4FFF, string);
			}

			GameTextForPlayer(playerid, "~r~~h~Tabligh Nakonid!", 5000, 3);
			SendClientMessage(playerid, 0xC0C0C0FF, " ");
			SendClientMessage(playerid, 0xC0C0C0FF, "You are muted for {FF9B9B}"#ADV_MUTE_TIME_STR" {C0C0C0}hour due to {FF6464}advertisement text{C0C0C0}!"); //{E46663}+1 Warning
			SendClientMessage(playerid, 0xC0C0C0FF, " ");
			
			PlayerInfo[playerid][mute] = 60 * ADV_MUTE_MINUTE;
			CallRemoteFunction("SV_RemoveVoice", "d", playerid);

			format(string, 144, "[ADVERTISEMENT] {DA302C}%s(%d) {E46663}muted for say {FFFFFF}: {FFBFBF}%s", 
				GetName(playerid), 
				playerid, 
				text);

			foreach(new i: admin_players)
			{
				SendClientMessage(i, 0xE46663FF, string);
				SendClientMessage(i, 0xE46663FF, "[WORD] {DA302C}IP Address Detected");
			}

			// -----------------------
			// log

			new File:lFile;

			new year, month, day;
		    getdate(year, month, day);

			format(string, sizeof(string), "[%i-%02d-%02d | %02d:%02d]: \"%s\": %s [IP Address Detected]\r\n", 
				year, month, day, timestamp_hour, timestamp_minute, 
				GetName(playerid), text);

		    lFile = fopen("tablighat.txt", io_append);
		    fwrite(lFile, string);
		    fclose(lFile);

			return true;
		}

		/* Insult */
		new 
			insult = IsTextContainsInsult(text);

		if(insult != -1) {

			new 
				string[200],
				str[64];

			PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);

			texture_load_mode(playerid, 5000);

			format(string, 144, "AdmBot issued a chat mute to player %s for %d minutes. Reason: Insult (Fohsh)", 
				GetName(playerid), INSULT_MUTE_MINUTE);

			foreach(new i: logged_players)
			{
				SendClientMessage(i, 0xFF4F4FFF, string);
			}

			GameTextForPlayer(playerid, "~r~~h~Tabligh Nakonid!", 5000, 3);
			SendClientMessage(playerid, 0xC0C0C0FF, " ");
			SendClientMessage(playerid, 0xC0C0C0FF, "You are muted for {FF9B9B}"#INSULT_MUTE_TIME_STR" {C0C0C0}hour due to {FF6464}insult text{C0C0C0}!"); //{E46663}+1 Warning
			SendClientMessage(playerid, 0xC0C0C0FF, " ");
			
			PlayerInfo[playerid][mute] = 60 * INSULT_MUTE_MINUTE;
			CallRemoteFunction("SV_RemoveVoice", "d", playerid);

			format(string, 144, "[INSULT] {DA302C}%s(%d) {E46663}muted for say {FFFFFF}: {FFBFBF}%s", 
				GetName(playerid), 
				playerid, 
				text);

			format(str, sizeof str, "[WORD] {DA302C}%s", 
				Insult_Texts[insult][Text]);

			foreach(new i: admin_players)
			{
				SendClientMessage(i, 0xE46663FF, string);
				SendClientMessage(i, 0xE46663FF, str);
			}

			// -----------------------
			// log

			new File:lFile;

			new year, month, day;
		    getdate(year, month, day);

			format(string, sizeof(string), "[%i-%02d-%02d | %02d:%02d]: \"%s\": %s [%s]\r\n", 
				year, month, day, timestamp_hour, timestamp_minute, 
				GetName(playerid), text, Insult_Texts[insult][Text]);

		    lFile = fopen("insult.txt", io_append);
		    fwrite(lFile, string);
		    fclose(lFile);

			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------

public OnPlayerDisconnect(playerid, reason)
{
	/* Reset AdvText Player Attempts */
	for(new i = 0; i < sizeof Adv_Texts; i++) {
		Player_Adv_Texts_Attempts[playerid][i] = 0;
	}

	#if defined AntiInsultAdv_OnPlayerDisconnec
		return AntiInsultAdv_OnPlayerDisconnec(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect AntiInsultAdv_OnPlayerDisconnec
#if defined AntiInsultAdv_OnPlayerDisconnec
	forward AntiInsultAdv_OnPlayerDisconnec(playerid, reason);
#endif