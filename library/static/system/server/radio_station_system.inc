#if !defined MAX_RADIO_STATIONS
    #define MAX_RADIO_STATIONS 20
#endif

// ------------------------------------------------------------------

new pRadioLinkID[MAX_PLAYERS], 
    RadioLink_Custom_ON[MAX_PLAYERS],
    RadioCustomURL[MAX_PLAYERS][144];

static AddRadioID[MAX_PLAYERS];
static AddRadioName[MAX_PLAYERS][24];

// ------------------------------------------------------------------

enum RadioStationsEnum
{
    RadioID,
    RadioLink[144],
    RadioName[24]
};

new RadioStations[MAX_RADIO_STATIONS][RadioStationsEnum];

Radio_Init() {
    mysql_tquery(sql_connection, "SELECT * FROM `radio_stations`", "LoadRadioStations");
}

forward LoadRadioStations();
public LoadRadioStations()
{
    new rows = cache_num_rows(), idRadio;
    if(!rows) return print("[Radio Stations] 0 links loaded successfully!");
    for(new i; i < rows; i++)
    {
        /*cache_get_value_name_int(i, "id", idRadio);
        RadioStations[idRadio][RadioID] = idRadio;
        cache_get_value_name(i, "link", RadioStations[idRadio][RadioLink], 144);
        cache_get_value_name(i, "name", RadioStations[idRadio][RadioName], 24);*/

        idRadio = cache_get_field_content_int(i, "id", sql_connection);
        RadioStations[idRadio][RadioID] = idRadio;
        cache_get_field_content(i, "link", RadioStations[idRadio][RadioLink], sql_connection, 144);
        cache_get_field_content(i, "name", RadioStations[idRadio][RadioName], sql_connection, 24);
    }
    printf("[SERVER] Loaded radio stations: %d", rows);
    return 1;
}

CMD:addradio(playerid, params[])
{
    if (PlayerInfo[playerid][admin] < 8) return 1;
    new idRadio, name_[24];

    if (sscanf(params, "ds[24]", idRadio, name_))
        return SendClientMessage(playerid, col_gray, "USAGE: /addradio (id) (radio name)");

    if (idRadio <= 0 || idRadio >= MAX_RADIO_STATIONS)
        return SendClientMessage(playerid, col_gray, ""scm_error"ID Ra Beyne 1 Ta "#MAX_RADIO_STATIONS" Bezanid.");

    if (RadioStations[idRadio][RadioID] != 0)
        return SendClientMessage(playerid, col_gray, ""scm_error"In ID Radio Ghablan Sakhte Shode.");

    AddRadioID[playerid] = idRadio;
    format(AddRadioName[playerid], 24, "%s", name_);

    show_dialog(playerid, DIALOG_ADDRADIO_STATION, DIALOG_STYLE_INPUT, "{FFFFFF}Add Radio Station", "{FFFFFF}Lotfan {FFFF00}Link {ffffff}In Radio Ra Vared Konid:", "Add", "Cancel");
    return 1;
}

RadioStation_DialogRespone(playerid, dialogid, response, listitem, inputtext[]) {
    if (dialogid == DIALOG_ADDRADIO_STATION) {
        if (!response)
            return 1;

        new idRadio = AddRadioID[playerid];

        if (RadioStations[idRadio][RadioID] != 0)
            return SendClientMessage(playerid, col_gray, ""scm_error"In ID Radio Ghablan Sakhte Shode.");

        RadioStations[idRadio][RadioID] = idRadio;
        format(RadioStations[idRadio][RadioLink], 144, "%s", inputtext);
        format(RadioStations[idRadio][RadioName], 24, "%s", AddRadioName[playerid]);

        SendClientMessage(playerid, col_white, ""scm_sucess"Radio Station successfully added.");
        
        new query[230];
        mysql_format(sql_connection, query, sizeof query, "INSERT INTO `radio_stations` (`id`,`link`,`name`) VALUES (%d,'%e','%e')", idRadio, inputtext, AddRadioName[playerid]);
        mysql_tquery(sql_connection, query);
        return 1;
    }

    if (dialogid == DIALOG_RADIO) {
        if (!response)
            return 1;

        if(!strcmp("Add Custom Link", inputtext, true))
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    show_dialog(playerid, DIALOG_RADIO_ADDURL, DIALOG_STYLE_INPUT, "Add Custom Link", "{F27A0D}Linke Moarde Nazar Khod Ra Dar Kader Zir Vared Konid:", "Play", "Cancel");
                    return 1;
                }
                else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Ranandeh Nistid.");
            }
            else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Bayad Dar Yek Mashin Bashid Ta Betevanid Az In Command Estefade Konid!");
        }
        if(!strcmp("Play Custom Link", inputtext, true))
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {


                    if(strlen(RadioCustomURL[playerid]) < 6) return show_dialog(playerid, DIALOG_RADIO_ADDURL, DIALOG_STYLE_INPUT, "Add Custom Link", "{F27A0D}Linke Moarde Nazar Khod Ra Dar Kader Zir Vared Konid:", "Play", "Cancel");
                    new string[286];

                    new URL[286];
                    format(URL, sizeof(URL), "%s", RadioCustomURL[playerid]);
                    for (new w; w < strlen(URL); w++) {
                        if (URL[w] == '%') strdel(URL, w, w+3);
                    }

                    format(string, sizeof(string), "Vehicle Radio Station: {FFFFFF}%s", URL);
                    pRadioLinkID[playerid] = 0;
                    RadioLink_Custom_ON[playerid] = 1;
                    foreach(new i : Player)
                    {
                        if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
                        {
                            PlayAudioStreamForPlayer(i, RadioCustomURL[playerid]);
                            SendClientMessage(i, 0xD98C00FF, string);
                        }
                    }
                    return 1;
                }
                else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Ranandeh Nistid.");
            }
            else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Bayad Dar Yek Mashin Bashid Ta Betevanid Az In Command Estefade Konid!");
        }           
        if(!strcmp("Off Radio", inputtext, true))
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new i : Player)
                    {
                        if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
                        {
                            if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
                            {
                                pRadioLinkID[playerid] = 0;
                                RadioLink_Custom_ON[playerid] = 0;
                                StopAudioStreamForPlayer(i);
                                GameTextForPlayer(playerid, "~p~Radio ~w~Khamosh Shod.", 3000, 3);
                            }
                            else
                            {
                                StopAudioStreamForPlayer(i);
                            }
                        }
                    }
                    return 1;
                }
                else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Ranandeh Nistid.");
            }
            else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Bayad Dar Yek Mashin Bashid!");
        }
        if(listitem >= 0)
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    pRadioLinkID[playerid] = strval(inputtext);
                    new string[286];
                    format(string, sizeof(string), "Vehicle Radio Station: {FFFFFF}%s", RadioStations[pRadioLinkID[playerid]][RadioName]);
                    foreach(new i : Player)
                    {
                        if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
                        {
                            PlayAudioStreamForPlayer(i, RadioStations[pRadioLinkID[playerid]][RadioLink]);
                            SendClientMessage(i, 0xD98C00FF, string);
                        }
                    }
                    RadioLink_Custom_ON[playerid] = 0;
                    return 1;
                }
                else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Ranandeh Nistid.");
            }
            else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Bayad Dar Yek Mashin Bashid Ta Betevanid Az In Command Estefade Konid!");
            
        }
        return 1;
    }

    if(dialogid == DIALOG_RADIO_ADDURL)
    {
        if(!response) return 1;
        if(IsPlayerInAnyVehicle(playerid))
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                if(strlen(inputtext) == 0) return SendClientMessage(playerid, 0xFF0000AA, "Lotfan Link Ra Sahih Vared Konid!"),show_dialog(playerid, DIALOG_RADIO_ADDURL, DIALOG_STYLE_INPUT, "Add Custom Link", "{F27A0D}Linke Moarde Nazar Khod Ra Dar Kader Zir Vared Konid:", "Play", "Cancel");
                if(strfind(inputtext, "http", true) == -1) return SendClientMessage(playerid, 0xFF0000AA, "Link Radio/MP3 Bayad HTTP Bashad."),show_dialog(playerid, DIALOG_RADIO_ADDURL, DIALOG_STYLE_INPUT, "Add Custom Link", "{F27A0D}Linke Moarde Nazar Khod Ra Dar Kader Zir Vared Konid:", "Play", "Cancel");

                format(RadioCustomURL[playerid], 144, "%s", inputtext);
                new string[286];

                new URL[300];
                format(URL, sizeof(URL), "%s", inputtext);
                for (new w; w < strlen(URL); w++) {
                    if (URL[w]=='%') strdel(URL, w, w+3);
                }

                format(string, sizeof(string), "Vehicle Radio Station: {FFFFFF}%s", URL);
                pRadioLinkID[playerid] = 0;
                RadioLink_Custom_ON[playerid] = 1;
                foreach(new i : Player)
                {
                    if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
                    {
                        PlayAudioStreamForPlayer(i, inputtext);
                        SendClientMessage(i, 0xD98C00FF, string);
                    }
                }

                format(string, sizeof string, "UPDATE `users` SET `u_radiocustomurl`='%s' WHERE `u_id` = '%d' LIMIT 1",
                RadioCustomURL[playerid], PlayerInfo[playerid][id]);
                mysql_tquery(sql_connection, string);

                return 1;
            } else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Ranandeh Nistid.");
        } else return SendClientMessage(playerid, 0xBDBDBDFF, "Shoma Bayad Dar Yek Mashin Bashid Ta Betevanid Az In Command Estefade Konid!");
    }
    return 0;
}

CMD:delradio(playerid, params[])
{
    if (PlayerInfo[playerid][admin] < 8) return 1;
    new idRadio;

    if (sscanf(params, "d", idRadio))
        return SendClientMessage(playerid, col_gray, "USAGE: /delradio (id)");

    if (idRadio <= 0 || idRadio >= MAX_RADIO_STATIONS)
        return SendClientMessage(playerid, col_gray, ""scm_error"ID Ra Beyne 1 Ta "#MAX_RADIO_STATIONS" Bezanid.");

    if (RadioStations[idRadio][RadioID] == 0)
        return SendClientMessage(playerid, col_gray, ""scm_error"In ID Radio Sakhte Nashode.");

    RadioStations[idRadio][RadioID] = 0;
    SendClientMessage(playerid, col_white, ""scm_sucess"Radio Station successfully removed.");
    new query[50];
    mysql_format(sql_connection, query, sizeof query, "DELETE FROM `radio_stations` WHERE `id`=%d", idRadio);
    mysql_query(sql_connection, query, false);
    return 1;
}

CMD:radio(playerid, params[])
{
    if(IsPlayerInAnyVehicle(playerid))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            if(bicycles(GetPlayerVehicleID(playerid))) return SendClientMessage(playerid, col_gray, ""scm_error"Nemitavanid Dar Docharkhe Radio Estefade Konid.");
            new DialogString[1000+956], part[100];
            for(new i; i < sizeof(RadioStations); i++) 
            {
                if (RadioStations[i][RadioID] == 0) continue;

                format(part, sizeof(part), "\n{%s}%i: %s%s", (pRadioLinkID[playerid] == RadioStations[i][RadioID]) ? ("E0BA1F") : ("FFFFFF"), i, RadioStations[i][RadioName], (pRadioLinkID[playerid] == i) ? (" - In Playing") : (""));
                strcat(DialogString, part, sizeof(DialogString));
            }
            strcat(DialogString, "\nAdd Custom Link\nPlay Custom Link", sizeof(DialogString));

            if(pRadioLinkID[playerid] != 0 || strlen(RadioCustomURL[playerid]) >= 6) {
                strcat(DialogString, "\n{AA0000}Off Radio", sizeof(DialogString));
            }
            show_dialog(playerid, DIALOG_RADIO, DIALOG_STYLE_LIST,"{E0BA1F}Radio", DialogString, "Entekhab", "Enseraf");
        } else return SendClientMessage(playerid, col_gray, ""scm_error"Shoma Ranandeh Nistid.");
    } else return SendClientMessage(playerid, col_gray, ""scm_error"Shoma Bayad Dar Yek Mashin Bashid.");
    return 1;
}

public OnPlayerConnect(playerid)
{
    RadioLink_Custom_ON[playerid] = 0;
    pRadioLinkID[playerid] = 0;

    #if defined RadioCar_OnPlayerConnect
        return RadioCar_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect RadioCar_OnPlayerConnect
#if defined RadioCar_OnPlayerConnect
    forward RadioCar_OnPlayerConnect(playerid);
#endif