#define MAX_ANTI_DM_ZONE    320
enum
{
    STATUS_ANTIDM_NONE = 200500,
    STATUS_ANTIDM_POS1,
    STATUS_ANTIDM_POS2,
    STATUS_ANTIDM_GO_OBJECT,
    STATUS_ANTIDM_OBJECT
}
enum e_DMInfo
{
    dmMysqlID,
    dmType,
Float:dmX1,
Float:dmY1,
Float:dmZ1,
Float:dmX2,
Float:dmY2,
Float:dmZ2,
Float:dmInfoX,
Float:dmInfoY,
Float:dmInfoZ,
Float:dmInfoRZ,
Text3D:dm3DLabel,
    dmRadius,
    dmObject,
    dmArea,
    dmVW,
    dmInt,
    dmFlag[max_fraction],
};
new AntiDMInfo[MAX_ANTI_DM_ZONE][e_DMInfo],
    count_antidm;


CMD:greenzone(playerid, params[])
{
    if(PlayerInfo[playerid][admin] < 8) return 1;
    show_dialog(playerid, D_ANTIDM_MENU, DIALOG_STYLE_LIST,""scm_dialog"GREEN ZONE",""c_green"[1]"c_white" Create\n"c_green"[2]"c_white" Delete\n"c_green"[3]"c_white" Settings","Next","Close");
    return 1;
}

CMD:dmpos(playerid, params[])
{
    new Float:playerPos_x, Float:playerPos_y, Float:playerPos_z;
    GetPlayerPos(playerid, playerPos_x, playerPos_y, playerPos_z);
    if(p_t_info[playerid][p_listitem_int] == STATUS_ANTIDM_GO_OBJECT)
    {
        if(!IsPlayerToSquare(playerid, AntiDMInfo[count_antidm][dmX1], AntiDMInfo[count_antidm][dmY1], AntiDMInfo[count_antidm][dmX2], AntiDMInfo[count_antidm][dmY2]))
        return SendError(playerid, "You can only place a sign in the Anti-DM zone square. Roma, don't be stupid.");
        new object_anti_dm = CreateDynamicObject(19973, playerPos_x+(random(1)), playerPos_y+random(1), playerPos_z-1.2, 0.0, 0.0, 0.0);
        EditDynamicObject(playerid, object_anti_dm);
        p_t_info[playerid][p_listitem_int] = STATUS_ANTIDM_OBJECT;
        return 1;
    }
    if(p_t_info[playerid][p_listitem_int] == STATUS_ANTIDM_POS1)
    {
        AntiDMInfo[count_antidm][dmX1] = playerPos_x;
        AntiDMInfo[count_antidm][dmY1] = playerPos_y;
        AntiDMInfo[count_antidm][dmZ1] = playerPos_z;
        SendInfo(playerid, "Mokhtasat aval tanzim shod hala mokhtasad dovom ra ba zavie 45 darage ba /dmpos tanzim konid");
        p_t_info[playerid][p_listitem_int] = STATUS_ANTIDM_POS2;
        return 1;
    }
    if(p_t_info[playerid][p_listitem_int] == STATUS_ANTIDM_POS2)
    {
        AntiDMInfo[count_antidm][dmX2] = playerPos_x;
        AntiDMInfo[count_antidm][dmY2] = playerPos_y;
        AntiDMInfo[count_antidm][dmZ2] = playerPos_z;
        SendInfo(playerid, "Mokhtasat dovom tanzim shod");
        p_t_info[playerid][p_listitem_int] = STATUS_ANTIDM_GO_OBJECT;
    }
    new Float:tmp_coord;
    if(AntiDMInfo[count_antidm][dmX1] > AntiDMInfo[count_antidm][dmX2])
    {
        tmp_coord = AntiDMInfo[count_antidm][dmX1];
        AntiDMInfo[count_antidm][dmX1] = AntiDMInfo[count_antidm][dmX2];
        AntiDMInfo[count_antidm][dmX2] = tmp_coord;
    }
    if(AntiDMInfo[count_antidm][dmY1] > AntiDMInfo[count_antidm][dmY2])
    {
        tmp_coord = AntiDMInfo[count_antidm][dmY1];
        AntiDMInfo[count_antidm][dmY1] = AntiDMInfo[count_antidm][dmY2];
        AntiDMInfo[count_antidm][dmY2] = tmp_coord;
    }
    if(AntiDMInfo[count_antidm][dmZ1] > AntiDMInfo[count_antidm][dmZ2])
    {
        tmp_coord = AntiDMInfo[count_antidm][dmZ1];
        AntiDMInfo[count_antidm][dmZ1] = AntiDMInfo[count_antidm][dmZ2];
        AntiDMInfo[count_antidm][dmZ2] = tmp_coord;
    }
    return 1;
}

CreateDMZ(playerid)
{
    AntiDMInfo[count_antidm][dmInt] = GetPlayerInterior(playerid);
    AntiDMInfo[count_antidm][dmVW] = GetPlayerVirtualWorld(playerid);

    if(AntiDMInfo[count_antidm][dmType] == 0)
    {
        AntiDMInfo[count_antidm][dmArea] = CreateDynamicSphere(AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ], AntiDMInfo[count_antidm][dmRadius], AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt] , -1);
        // UpdateAreaInfo(AntiDMInfo[count_antidm][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, count_antidm);
    }
    else
    {
        AntiDMInfo[count_antidm][dmRadius] = 0;
        AntiDMInfo[count_antidm][dmArea] = CreateDynamicCube(AntiDMInfo[count_antidm][dmX1], AntiDMInfo[count_antidm][dmY1], AntiDMInfo[count_antidm][dmZ1]-10.0, AntiDMInfo[count_antidm][dmX2], AntiDMInfo[count_antidm][dmY2], AntiDMInfo[count_antidm][dmZ2]+10.0, AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt] , -1);
        // UpdateAreaInfo(AntiDMInfo[count_antidm][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, count_antidm);
    }

    AntiDMInfo[count_antidm][dm3DLabel] = CreateDynamic3DTextLabel("[ Green Zone ]\ninja dava kardan mamnoe mibashad", 0x6FFF6FFF, AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ]+2.0, 15.0,INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt],-1);
    AntiDMInfo[count_antidm][dmObject] = CreateDynamicObject(19973, AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ], 0.0, 0.0, AntiDMInfo[count_antidm][dmInfoRZ], AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt]);
    for(new i = max_fraction-1; i != -1; i--) AntiDMInfo[count_antidm][dmFlag][i] = 0;

    new string[400];
    mysql_format(sql_connection, string, sizeof string,
        "INSERT INTO `antidm_info` (`X1`, `Y1`, `Z1`, `X2`, `Y2`, `Z2`, `infoX`, `infoY`, `infoZ`, `infoRZ`, `radius`, `type`, `virt`,`int`) VALUES ('%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', %d,%d,%d,%d)",
        AntiDMInfo[count_antidm][dmX1], AntiDMInfo[count_antidm][dmY1], AntiDMInfo[count_antidm][dmZ1],
        AntiDMInfo[count_antidm][dmX2], AntiDMInfo[count_antidm][dmY2], AntiDMInfo[count_antidm][dmZ2],
        AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ], AntiDMInfo[count_antidm][dmInfoRZ],
        AntiDMInfo[count_antidm][dmRadius], AntiDMInfo[count_antidm][dmType], AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt]);
    mysql_tquery(sql_connection, string, "create_antidm", "i", count_antidm);
    return true;
}
forward create_antidm(idx_id);
public create_antidm(idx_id)
{
    AntiDMInfo[idx_id][dmMysqlID] = cache_insert_id();
    count_antidm++;
    return 1;
}

forward LoadDynamicAntiDM();
public LoadDynamicAntiDM()
{
    new rows = cache_num_rows();
    if (!rows) return print("[SERVER] Loaded greenzone area: 0");
    new data[128];
    for(new i; i < rows; i++)
    {
        /*cache_get_value_name_int(i, "id", AntiDMInfo[i][dmMysqlID]);
        cache_get_value_name_float(i, "X1", AntiDMInfo[i][dmX1]);
        cache_get_value_name_float(i, "Y1", AntiDMInfo[i][dmY1]);
        cache_get_value_name_float(i, "Z1", AntiDMInfo[i][dmZ1]);
        cache_get_value_name_float(i, "X2", AntiDMInfo[i][dmX2]);
        cache_get_value_name_float(i, "Y2", AntiDMInfo[i][dmY2]);
        cache_get_value_name_float(i, "Z2", AntiDMInfo[i][dmZ2]);
        cache_get_value_name_float(i, "infoX", AntiDMInfo[i][dmInfoX]);
        cache_get_value_name_float(i, "infoY", AntiDMInfo[i][dmInfoY]);
        cache_get_value_name_float(i, "infoZ", AntiDMInfo[i][dmInfoZ]);
        cache_get_value_name_float(i, "infoRZ", AntiDMInfo[i][dmInfoRZ]);
        cache_get_value_name_int(i, "radius", AntiDMInfo[i][dmRadius]);
        cache_get_value_name_int(i, "type", AntiDMInfo[i][dmType]);
        cache_get_value_name_int(i, "int", AntiDMInfo[i][dmInt]);
        cache_get_value_name_int(i, "virt", AntiDMInfo[i][dmVW]);

        cache_get_value_name(i, "flags", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
        sscanf(data, "p<|>a<i>[26]", AntiDMInfo[i][dmFlag]);
        */

        AntiDMInfo[i][dmMysqlID] = cache_get_field_content_int(i, "id", sql_connection);
        AntiDMInfo[i][dmX1] = cache_get_field_content_float(i, "X1", sql_connection);
        AntiDMInfo[i][dmY1] = cache_get_field_content_float(i, "Y1", sql_connection);
        AntiDMInfo[i][dmZ1] = cache_get_field_content_float(i, "Z1", sql_connection);
        AntiDMInfo[i][dmX2] = cache_get_field_content_float(i, "X2", sql_connection);
        AntiDMInfo[i][dmY2] = cache_get_field_content_float(i, "Y2", sql_connection);
        AntiDMInfo[i][dmZ2] = cache_get_field_content_float(i, "Z2", sql_connection);
        AntiDMInfo[i][dmInfoX] = cache_get_field_content_float(i, "infoX", sql_connection);
        AntiDMInfo[i][dmInfoY] = cache_get_field_content_float(i, "infoY", sql_connection);
        AntiDMInfo[i][dmInfoZ] = cache_get_field_content_float(i, "infoZ", sql_connection);
        AntiDMInfo[i][dmInfoRZ] = cache_get_field_content_float(i, "infoRZ", sql_connection);
        AntiDMInfo[i][dmRadius] = cache_get_field_content_int(i, "radius", sql_connection);
        AntiDMInfo[i][dmType] = cache_get_field_content_int(i, "type", sql_connection);
        AntiDMInfo[i][dmInt] = cache_get_field_content_int(i, "int", sql_connection);
        AntiDMInfo[i][dmVW] = cache_get_field_content_int(i, "virt", sql_connection);

        cache_get_field_content(i, "flags", data, sql_connection, 128);
        sscanf(data, "p<|>a<i>[26]", AntiDMInfo[i][dmFlag]);

        if(AntiDMInfo[i][dmType] == 0)
        {
            AntiDMInfo[i][dmArea] = CreateDynamicSphere(AntiDMInfo[i][dmInfoX], AntiDMInfo[i][dmInfoY], AntiDMInfo[i][dmInfoZ], AntiDMInfo[i][dmRadius], AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt] , -1);
            // UpdateAreaInfo(AntiDMInfo[i][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, i);
        }
        else
        {
            AntiDMInfo[i][dmRadius] = 0;
            AntiDMInfo[i][dmArea] = CreateDynamicCube(AntiDMInfo[i][dmX1], AntiDMInfo[i][dmY1], AntiDMInfo[i][dmZ1]-10.0, AntiDMInfo[i][dmX2], AntiDMInfo[i][dmY2], AntiDMInfo[i][dmZ2]+10.0, AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt] , -1);
            // UpdateAreaInfo(AntiDMInfo[i][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, i);
        }

        AntiDMInfo[i][dm3DLabel] = CreateDynamic3DTextLabel("[ Green Zone ]\ninja dava kardan mamnoe mibashad", 0x6FFF6FFF, AntiDMInfo[i][dmInfoX],AntiDMInfo[i][dmInfoY],AntiDMInfo[i][dmInfoZ]+2.0, 15.0,INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt],-1);
        AntiDMInfo[i][dmObject] = CreateDynamicObject(19973, AntiDMInfo[i][dmInfoX], AntiDMInfo[i][dmInfoY], AntiDMInfo[i][dmInfoZ], 0.0, 0.0, AntiDMInfo[i][dmInfoRZ], AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt]);
        count_antidm++;
    }
    printf("[SERVER] Loaded greenzone area: %d", rows);
    return 1;
}

AntiDMZone(playerid, bool:isCop = false)
{
    if(duel_opponent[playerid] != INVALID_PLAYER_ID && GetPlayerVirtualWorld(playerid) != 0)
        return 0;
    if(isCop == true && (cop_player(playerid) || fbi_player(playerid) || army_player(playerid) || gov_player(playerid)) && is_fraction_duty {playerid})
        return 0;
    if(p_t_info[playerid][green_zone] == -1)
    {
        for(new i = count_antidm-1; i != -1; i--)
        {
            if(IsPlayerInDynamicArea(playerid, AntiDMInfo[i][dmArea]))
            {
                p_t_info[playerid][green_zone] = i;
                break;
            }
        }
    }
    if(p_t_info[playerid][green_zone] != -1)
    {
        ResetPlayerWeapons(playerid);
        for (new i; i < MAX_WEAPONS; i++)
        {
            GivePlayerWeapon(playerid, PlayerInfo[playerid][Weapon][i], PlayerInfo[playerid][Ammo][i]);
        }
        
        SetPlayerArmedWeapon(playerid, 0);

        for(new i; i < sizeof(GlobalTextdrawsGreenZone); i++) TextDrawShowForPlayer(playerid, GlobalTextdrawsGreenZone[i]);

        return 1;
    }
    return 0;
}

GreenZone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch (dialogid) {
        case D_ANTIDM_MENU:
        {
            if(!response) return true;
            switch(listitem)
            {
                case 0: show_dialog(playerid, D_ANTIDM_CREATE_TYPE, DIALOG_STYLE_LIST, ""scm_dialog"Create Green Zone",""c_green"[1]"c_white" Sphere\n"c_green"[2]"c_white" Cube","Select","Cancel");
                case 1:
                {
                    for(new i = count_antidm; i != -1; i--)
                    {
                        if(IsPlayerInDynamicArea(playerid, AntiDMInfo[i][dmArea]))
                        {
                            DestroyDynamicObject(AntiDMInfo[i][dmObject]);
                            AntiDMInfo[i][dmObject] = INVALID_OBJECT_ID;
                            DestroyDynamicArea(AntiDMInfo[i][dmArea]);
                            DestroyDynamic3DTextLabel(AntiDMInfo[i][dm3DLabel]);

                            STRING_GLOBAL[0] = EOS;
                            format(STRING_GLOBAL, 100, "DELETE FROM `antidm_info` WHERE `id` = %d", AntiDMInfo[i][dmMysqlID]);
                            mysql_tquery(sql_connection, STRING_GLOBAL);

                            SendAccess(playerid, "Green Zone Deleted.");
                            break;
                        }
                    }
                }
                case 2:
                {
                    for(new i = count_antidm; i != -1; i--)
                    {
                        if(IsPlayerInDynamicArea(playerid, AntiDMInfo[i][dmArea]))
                        {
                            STRING_GLOBAL[0] = EOS;
                            for(new d = 0; d < max_fraction; d++) {
                                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s"c_green"[%d]"c_white" %s [%s]\n",
                                    STRING_GLOBAL, 
                                    d+1, 
                                    GetFractionName(d), 
                                    (AntiDMInfo[i][dmFlag][d] ? ("V") : ("X")));
                            }
                            show_dialog(playerid, D_ANTIDM_SETTING, DIALOG_STYLE_LIST, ""scm_dialog"DM ZONE SETTING", STRING_GLOBAL, "Select", "Cancel");
                            p_t_info[playerid][p_listitem_int] = i;
                            break;
                        }
                    }
                }

            }
            return true;
        }
        case D_ANTIDM_SETTING:
        {
            new idx = p_t_info[playerid][p_listitem_int];
            if(!response || idx < 0) return 1;
            AntiDMInfo[idx][dmFlag][listitem] = !AntiDMInfo[idx][dmFlag][listitem];

            STRING_GLOBAL[0] = EOS;
            for(new i; i < max_fraction; i++)
                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, AntiDMInfo[idx][dmFlag][i], i == max_fraction-1 ? "":"|");
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `antidm_info` SET `flags` = '%s' WHERE `id` = %d", STRING_GLOBAL, AntiDMInfo[idx][dmMysqlID]);
            mysql_tquery(sql_connection, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            for(new i; i < max_fraction; i++) {
                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s"c_green"[%d]"c_white" %s [%s]\n",STRING_GLOBAL, i+1, GetFractionName(i),(AntiDMInfo[idx][dmFlag][i] ? ("V") : ("X")));
            }
            show_dialog(playerid, D_ANTIDM_SETTING, DIALOG_STYLE_LIST, ""scm_dialog"DM ZONE SETTING", STRING_GLOBAL, "Select", "Cancel");

            SendInfo(playerid, "Faction %s GreenZone Area: %s", GetFractionName(listitem), AntiDMInfo[idx][dmFlag][listitem] ? "Faa'l" : "Gheyre Faa'l");

            STRING_GLOBAL[0] = EOS;
            new count;
            for(new i; i < max_fraction; i++)
            {
                if(AntiDMInfo[idx][dmFlag][i] == 1)
                {
                    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s"c_green"[%d]"c_white" %s\n", STRING_GLOBAL, count+1, GetFractionName(i));
                    count++;
                }
            }
            if(!count) strcat(STRING_GLOBAL,"[ Green Zone ]\ninja dava kardan mamnoe mibashad");
            else format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[ Green Zone ]\ninja dava kardan mamnoe mibashad:\n%s", STRING_GLOBAL);
            UpdateDynamic3DTextLabelText(AntiDMInfo[idx][dm3DLabel], COLOR_MAIN, STRING_GLOBAL);
            return true;
        }
        case D_ANTIDM_CREATE_TYPE:
        {
            if(!response) return 1;
            if(count_antidm >= MAX_ANTI_DM_ZONE) {
                return SendError(playerid, "Bishtar Az "#MAX_ANTI_DM_ZONE" Green Zone Nemishe Sakht.");
            }

            // p_t_info[playerid][p_listitem][0] = listitem;

            if(!listitem)
            {
                AntiDMInfo[count_antidm][dmType] = 0;
                show_dialog(playerid, D_ANTIDM_CREATE_RADIUS, DIALOG_STYLE_INPUT, ""scm_dialog"Create Green Zone", "Enter Range/Radius", "Select", "Cancel");
            }
            else
            {
                AntiDMInfo[count_antidm][dmType] = 1;
                p_t_info[playerid][p_listitem_int] = STATUS_ANTIDM_POS1;
                SendInfo(playerid, "Shoma Bayad /dmpos Bezanid.");
            }
            return 1;
        }
        case D_ANTIDM_CREATE_RADIUS:
        {
            if(!response) return 1;
            if(AntiDMZone(playerid) == 1) return SendError(playerid, "Shoma Bayad Az In Green Zone Kharej Shavid.");
            if(!strlen(inputtext)) return show_dialog(playerid, D_ANTIDM_CREATE_RADIUS, DIALOG_STYLE_INPUT, ""scm_dialog"Create Green Zone", "Enter Range/Radius", "Select", "Cancel");
            new radius = strval(inputtext);
            if(!(1 <= radius <= 350))
            {
                return show_dialog(playerid, D_ANTIDM_CREATE_RADIUS, DIALOG_STYLE_INPUT, ""scm_dialog"Create Green Zone", "Enter Range/Radius\n\n"c_red"Range/Radius Should Be 1 to 350", "Select", "Cancel");
            }
            new Float:playerPos_x, Float:playerPos_y, Float:playerPos_z;
            GetPlayerPos(playerid, playerPos_x, playerPos_y, playerPos_z);
            new object_anti_dm = CreateDynamicObject(19973, playerPos_x+(random(1)), playerPos_y+random(1), playerPos_z-1.2, 0.0, 0.0, 0.0);
            EditDynamicObject(playerid, object_anti_dm);
            p_t_info[playerid][p_listitem_int] = STATUS_ANTIDM_OBJECT;
            AntiDMInfo[count_antidm][dmRadius] = radius;
            return 1;
        }
    }

    return 1;
}


public OnPlayerEnterDynamicArea(playerid, areaid)
{
    for(new i = count_antidm-1; i != -1; i--) {
        if (areaid == AntiDMInfo[i][dmArea]) {
            
            p_t_info[playerid][green_zone] = i;
            
            for(new j; j < sizeof(GlobalTextdrawsGreenZone); j++) TextDrawShowForPlayer(playerid, GlobalTextdrawsGreenZone[j]);

            return 1;
        }
    }
    
    #if defined GreenZone_OnPlayerEnterDynArea
        return GreenZone_OnPlayerEnterDynArea(playerid, areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif

#define OnPlayerEnterDynamicArea GreenZone_OnPlayerEnterDynArea
#if defined GreenZone_OnPlayerEnterDynArea
    forward GreenZone_OnPlayerEnterDynArea(playerid, areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
    for(new i = count_antidm-1; i != -1; i--) {
        if (areaid == AntiDMInfo[i][dmArea]) {

            p_t_info[playerid][green_zone] = -1;

            for(new j; j < sizeof(GlobalTextdrawsGreenZone); j++) TextDrawHideForPlayer(playerid, GlobalTextdrawsGreenZone[j]);

            return 1;
        }
    }

    #if defined GreenZone_OnPlayerLeaveDynArea
        return GreenZone_OnPlayerLeaveDynArea(playerid, areaid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerLeaveDynamicArea
    #undef OnPlayerLeaveDynamicArea
#else
    #define _ALS_OnPlayerLeaveDynamicArea
#endif

#define OnPlayerLeaveDynamicArea GreenZone_OnPlayerLeaveDynArea
#if defined GreenZone_OnPlayerLeaveDynArea
    forward GreenZone_OnPlayerLeaveDynArea(playerid, areaid);
#endif