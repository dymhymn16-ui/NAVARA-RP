#define MAX_BINDER  30

new arrayBinderCMD[MAX_PLAYERS][MAX_BINDER][32],
    arrayBinderTEXT[MAX_PLAYERS][MAX_BINDER][128];

public OnPlayerConnect(playerid)
{
    for(new i = MAX_BINDER-1; i != -1; i--)
    {
        arrayBinderCMD[playerid][i] = "";
        arrayBinderTEXT[playerid][i] = "";
    }

    p_t_info[playerid][BinderNoCommand] = 0;

    #if defined bind_OnPlayerConnect
        return bind_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#if defined bind_OnPlayerConnect
    forward bind_OnPlayerConnect(playerid);
#endif
#define    OnPlayerConnect bind_OnPlayerConnect


LoadPlayerBinder(playerid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `enb`, `cmd`, `text` FROM `binder` WHERE `user_id` = %d LIMIT %i",
    PlayerInfo[playerid][id], MAX_BINDER);
    mysql_tquery(con_bd, STRING_GLOBAL, "LoadPlayerBinderCallBack", "i", playerid);
}

forward LoadPlayerBinderCallBack(playerid);
public LoadPlayerBinderCallBack(playerid)
{
	new rows,
		fields;
	cache_get_data(rows, fields);

    for(new i; i < rows; i++)
    {
        new idx;
        idx = cache_get_field_content_int(i, "id", sql_connection);
        PlayerInfo[playerid][BinderStatus][idx] = cache_get_field_content_int(i, "enb", sql_connection);
		cache_get_field_content(i, "cmd", arrayBinderCMD[playerid][idx], sql_connection, 32);
		cache_get_field_content(i, "text", arrayBinderTEXT[playerid][idx], sql_connection, 128);
    }
    return 1;
}

cmd:bind(playerid, params[])
{
    p_t_info[playerid][BinderList] = 0;
    return ShowBinderList(playerid);
}
alias:bind("binder");

ShowBinderList(playerid)
{
    STRING_GLOBAL = "[#] Status\tCommand\tText\n";
    strcat(STRING_GLOBAL, ""c_server""c_white"Next page\t»\t»\n");
    strcat(STRING_GLOBAL, ""c_server"<< "c_white"Previous page\t«\t«\n");
    strcat(STRING_GLOBAL, ""c_server"- "c_white"Add command\t+\t+\n");
    strcat(STRING_GLOBAL, "-----------------\t-\t-\n");

    new line_string[150];

    new tmp, page = p_t_info[playerid][BinderList];
    for(new i = ((page + 1) * 20) - 1; i >= (page * 20); i--) if(i < MAX_BINDER && arrayBinderCMD[playerid][i][0])
    {
        if(tmp >= 20) break;
        p_t_info[playerid][BufferBinderID][tmp++] = i;
        format(line_string, sizeof(line_string), arrayBinderTEXT[playerid][i]);
        if(strlen(line_string) > 30)
        {
            strdel(line_string, 28, strlen(line_string));
            strcat(line_string, "...");
        }
        fmt(STRING_GLOBAL, "%s"c_server"[%d]"c_white" %s\t%s\t%s\n", STRING_GLOBAL,
            i,
            PlayerInfo[playerid][BinderStatus][i] ? (c_green"Actively") : (c_red"Disabled"),
            arrayBinderCMD[playerid][i], line_string);
    }

    if(!tmp && page) {
        for(new i = ((page) * 20) - 1; i >= (page * 20); i--) if(i < MAX_BINDER && arrayBinderCMD[playerid][i][0])
        {
            if(tmp >= 20) break;
            p_t_info[playerid][BufferBinderID][tmp++] = i;
            format(line_string, sizeof(line_string), arrayBinderTEXT[playerid][i]);
            if(strlen(line_string) > 30)
            {
                strdel(line_string, 28, strlen(line_string));
                strcat(line_string, "...");
            }
            fmt(STRING_GLOBAL, "%s%s"c_server"\t"c_white"%s\t"c_white"%s\n", STRING_GLOBAL,
            PlayerInfo[playerid][BinderStatus][i] ? (c_green"Actively") : (c_red"Disabled"),
            arrayBinderCMD[playerid][i], line_string);
        }
    }
    new count = !tmp && page ? 0 : 1;
    format(line_string, sizeof(line_string), ""c_server"Binder, page: %i", page + count);

    return show_dialog(playerid, d_binder_show, DIALOG_STYLE_TABLIST_HEADERS, line_string, STRING_GLOBAL, "Next", "Cancel");
}

CheckBinderCommand(playerid, cmd[], type = 1)
{
    if(p_t_info[playerid][BinderNoCommand]) return 0;
    new ecmd[32];
    strcat(ecmd, cmd);
    if(type) strins(ecmd, "/", 0);
    for(new i; i < MAX_BINDER; i++) if(arrayBinderCMD[playerid][i][0] && PlayerInfo[playerid][BinderStatus][i] && !strcmp(ecmd, arrayBinderCMD[playerid][i]))
    {
        p_t_info[playerid][BinderNoCommand] = 1;
        SetTimerEx("CheckBinderCommandText", 0, false, "ii", playerid, i);
        return 1;
    }
    return 0;
}

forward CheckBinderCommandText(playerid, slot);
public CheckBinderCommandText(playerid, slot)
{
    new text[8][144];
    sscanf(arrayBinderTEXT[playerid][slot], "p<>>a<s[144]>[8]", text);
    for(new i; i < 8; i++) if(text[i][0])
    {
        DeletePVar(playerid, "Flood:CMD");
        if(text[i][0] == '/') //PC_EmulateCommand(playerid, text[i]);
        {
            new cmd_text[2][144];
            sscanf(text[i], "s[144]s[144]", cmd_text[0], cmd_text[1]);
            STRING_GLOBAL[0] = EOS;
            fmt(STRING_GLOBAL, "pc_cmd_%s", cmd_text[0][1]);
            CallRemoteFunction(STRING_GLOBAL, "is", playerid, isnull(cmd_text[1]) ? ("\1") : cmd_text[1]);
        }
        else OnPlayerText(playerid, text[i]);
    }
    SetPVarInt(playerid, "Flood:CMD", timestamp+1);
    p_t_info[playerid][BinderNoCommand] = 0;
}


Binder_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem

	switch(dialogid)
	{
        case d_binder_show:
        {
            if(!response || listitem >= 24) return 1;
            switch(listitem)
            {
                case 0:
                {
                    p_t_info[playerid][BinderList]++;
                    return ShowBinderList(playerid);
                }
                case 1:
                {
                    if(p_t_info[playerid][BinderList]) p_t_info[playerid][BinderList]--;
                    return ShowBinderList(playerid);
                }
                case 2:
                {
                    show_dialog(playerid, d_binder_add_command2, DIALOG_STYLE_INPUT, "Binder", ""c_white"Enter the command that will be used for the bind:", "Next", "Cancel");
                    return 1;
                }
                case 3: return ShowBinderList(playerid);
            }
            new text[8][80], idx = p_t_info[playerid][BufferBinderID][listitem - 4];
            sscanf(arrayBinderTEXT[playerid][idx], "p<>>a<s[80]>[8]", text);
            STRING_GLOBAL[0] = EOS;
            for(new i; i < 8; i++) fmt(STRING_GLOBAL, "%s"c_server"%s\n", STRING_GLOBAL, text[i]);
            p_t_info[playerid][p_listitem_int] = (listitem - 4);
            fmt(STRING_GLOBAL, ""c_white"[1] Change command\n[2] Change text\n[3] %s"c_white"\n[4] Delete\n"c_white"Team: "c_server"%s\n"c_white"Text: %s", PlayerInfo[playerid][BinderStatus][id] ? (c_red"Disable") : (c_green"Turn on"), arrayBinderCMD[playerid][id], STRING_GLOBAL);
            return show_dialog(playerid, d_binder_menu, DIALOG_STYLE_LIST, "Binder", STRING_GLOBAL, "Next", "Cancel");
        }
        case d_binder_menu:
        {
            if(!response) return ShowBinderList(playerid);
            switch(listitem)
            {
                case 0: return show_dialog(playerid, d_binder_add_command, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the command that will be used for the bind:", "Accept", "Back");
                case 1: return show_dialog(playerid, d_binder_add_text, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the text that will be displayed when sending the command:", "Accept", "Back");
                case 2:
                {
                    new idx = p_t_info[playerid][BufferBinderID][p_t_info[playerid][p_listitem_int]];
                    PlayerInfo[playerid][BinderStatus][idx] = !PlayerInfo[playerid][BinderStatus][idx];

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `binder` SET `enb` = '%d' WHERE `id` = '%d' AND `user_id` = '%d' LIMIT 1",
                    PlayerInfo[playerid][BinderStatus][idx], idx, PlayerInfo[playerid][id]);
                    mysql_tquery(con_bd, STRING_GLOBAL);
                }
                case 3:
                {
                    new idx = p_t_info[playerid][BufferBinderID][p_t_info[playerid][p_listitem_int]];
                    arrayBinderCMD[playerid][idx] = "";
                    arrayBinderTEXT[playerid][idx] = "";

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `binder` WHERE `id` = '%d' AND `user_id` = '%d' LIMIT 1",
                    idx, PlayerInfo[playerid][id]);
                    mysql_tquery(con_bd, STRING_GLOBAL);
                }
            }
            return ShowBinderList(playerid);
        }
        case d_binder_add_command:
        {
            if(!response) return ShowBinderList(playerid);
            if(!(1 <= strlen(inputtext) <= 30) || !strcmp(inputtext, "/bind")) return show_dialog(playerid, 7241, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the command that will be used for the bind:", "Accept", "Back");

            new idx = p_t_info[playerid][BufferBinderID][p_t_info[playerid][p_listitem_int]];
            format(arrayBinderCMD[playerid][idx], 32, inputtext);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `binder` SET `cmd` = '%e' WHERE `id` = '%d' AND `user_id` = '%d' LIMIT 1", inputtext, idx, PlayerInfo[playerid][id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            return ShowBinderList(playerid);
        }
        case d_binder_add_text:
        {
            if(!response) return ShowBinderList(playerid);
            if(!(1 <= strlen(inputtext) <= 128)) return show_dialog(playerid, d_binder_add_text, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the text that will be displayed when sending the command:", "Accept", "Back");
            if(strfind(inputtext, "returnmarket", true) != -1)
            {
                SendError(playerid, "This command cannot be added to a binder.");
                return show_dialog(playerid, d_binder_add_text, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the text that will be displayed when sending the command:", "Accept", "Back");
            }

            new idx = p_t_info[playerid][BufferBinderID][p_t_info[playerid][p_listitem_int]];
            format(arrayBinderTEXT[playerid][idx], 128, inputtext);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `binder` SET `text` = '%e' WHERE `id` = '%d' AND `user_id` = '%d' LIMIT 1",
            inputtext, idx, PlayerInfo[playerid][id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            return ShowBinderList(playerid);
        }
        case d_binder_add_command2:
        {
            if(!response) return ShowBinderList(playerid);
            if(!(1 <= strlen(inputtext) <= 30) || !strcmp(inputtext, "/bind")) return show_dialog(playerid, d_binder_add_command2, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the command that will be used for the bind:", "Accept", "Back");
            format(p_t_info[playerid][BufferCMDCreate], 32, inputtext);
            return show_dialog(playerid, d_binder_add_command3, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the text that will be displayed when sending the command:\n(You can use multiple commands using the '>' symbol)", "Accept", "Back");
        }
        case d_binder_add_command3:
        {
            if(!response) return ShowBinderList(playerid);
            if(!(1 <= strlen(inputtext) <= 128)) return show_dialog(playerid, d_binder_add_command3, DIALOG_STYLE_INPUT, ""c_server"Binder", ""c_white"Enter the text that will be displayed when sending the command:\n(You can use multiple commands using the '>' symbol)", "Accept", "Back");

            new idx = -1;
            for(new i; i < MAX_BINDER; i++) if(!arrayBinderCMD[playerid][i][0]) { idx = i; break; }
            if(idx == -1)
            {
                ShowBinderList(playerid);
                return SendError(playerid, "You can't create more.");
            }
            PlayerInfo[playerid][BinderStatus][idx] = 1;
            format(arrayBinderCMD[playerid][idx], 32, p_t_info[playerid][BufferCMDCreate]);
            format(arrayBinderTEXT[playerid][idx], 128, inputtext);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `binder` (`id`, `user_id`, `enb`, `cmd`, `text`) VALUES ('%d', '%d', '1', '%e', '%e')",
            idx, PlayerInfo[playerid][id], p_t_info[playerid][BufferCMDCreate], inputtext);
            mysql_tquery(con_bd, STRING_GLOBAL);

            return ShowBinderList(playerid);
        }
    }

    return 0;
}