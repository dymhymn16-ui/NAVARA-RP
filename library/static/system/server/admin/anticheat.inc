/*
    General settings for anti-cheat
*/
#define AC_MAX_CODES                    53 // Number of anti-cheat codes (currently 53)
#define AC_MAX_CODE_LENGTH              (3 + 1) // Maximum number of characters in anti-cheat "code" (001/002/003, etc.)
#define AC_MAX_CODE_NAME_LENGTH         (33 + 1) // The maximum number of characters in the full name of the read, for which the answer any code

#define AC_GLOBAL_TRIGGER_TYPE_PLAYER   0
#define AC_GLOBAL_TRIGGER_TYPE_IP       1

// Trigger types are declared as macros to make OnCheatDetected easier to navigate.
#define AC_CODE_TRIGGER_TYPE_DISABLED   0 // AC_CODE_TRIGGER_TYPE_DISABLED - Punishment type: Disabled
#define AC_CODE_TRIGGER_TYPE_WARNING    1 // AC_CODE_TRIGGER_TYPE_WARNING - Punishment Type: Warning
#define AC_CODE_TRIGGER_TYPE_KICK       2 // AC_CODE_TRIGGER_TYPE_KICK - Punishment type: Kick

#define AC_TRIGGER_ANTIFLOOD_TIME       20 // Time for anti-flood triggering (in seconds)


// The AC_CODE_NAME array stores the names of cheats that correspond to anti-cheat codes
static const AC_CODE_NAME[AC_MAX_CODES][AC_MAX_CODE_NAME_LENGTH] =
{
    {"AirBreak (onfoot)"},
    {"AirBreak (in vehicle)"},
    {"Teleport (onfoot)"},
    {"Teleport (in vehicle)"},
    {"Teleport (into/between vehicles)"},
    {"Teleport (vehicle to player)"},
    {"Teleport (pickups)"},
    {"FlyHack (onfoot)"},
    {"FlyHack (in vehicle)"},
    {"SpeedHack (onfoot)"},
    {"SpeedHack (in vehicle)"},
    {"Health hack (in vehicle)"},
    {"Health hack (onfoot)"},
    {"Armour hack"},
    {"Money hack"},
    {"Weapon hack"},
    {"Ammo hack (add)"},
    {"Ammo hack (infinite)"},
    {"Special actions hack"},
    {"GodMode from bullets (onfoot)"},
    {"GodMode from bullets (in vehicle)"},
    {"Invisible hack"},
    {"Lagcomp-spoof"},
    {"Tuning hack"},
    {"Parkour mod"},
    {"Quick turn"},
    {"Rapid fire"},
    {"FakeSpawn"},
    {"FakeKill"},
    {"Pro Aim"},
    {"CJ run"},
    {"CarShot"},
    {"CarJack"},
    {"UnFreeze"},
    {"AFK Ghost"},
    {"Full Aiming"},
    {"Fake NPC"},
    {"Reconnect"},
    {"High ping"},
    {"Dialog hack"},
    {"Sandbox"},
    {"Invalid version"},
    {"Rcon hack"},
    {"Tuning crasher"},
    {"Invalid seat crasher"},
    {"Dialog crasher"},
    {"Attached object crasher"},
    {"Weapon Crasher"},
    {"Connects to one slot"},
    {"Flood callback functions"},
    {"Flood change seat"},
    {"DDos"},
    {"NOP's"}
};

new AC_CODE_TRIGGER_TYPE_PC[AC_MAX_CODES] =
{
    AC_CODE_TRIGGER_TYPE_WARNING, // Airbreak (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Airbreak (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (onfoot)
    AC_CODE_TRIGGER_TYPE_KICK, // Teleport (in vehicle)
    AC_CODE_TRIGGER_TYPE_KICK, // Teleport (into/between vehicles)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (vehicle to player)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (pickups)
    AC_CODE_TRIGGER_TYPE_WARNING, // FlyHack (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // FlyHack (in vehicle)
    AC_CODE_TRIGGER_TYPE_KICK, // SpeedHack (onfoot)
    AC_CODE_TRIGGER_TYPE_KICK, // SpeedHack (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Health hack (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Health hack (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Armour hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Money hack
    AC_CODE_TRIGGER_TYPE_KICK, // Weapon hack
    AC_CODE_TRIGGER_TYPE_KICK, // Ammo hack (add)
    AC_CODE_TRIGGER_TYPE_KICK, // Ammo hack (infinite)
    AC_CODE_TRIGGER_TYPE_WARNING, // Special actions hack
    AC_CODE_TRIGGER_TYPE_KICK, // GodMode from bullets (onfoot)
    AC_CODE_TRIGGER_TYPE_KICK, // GodMode from bullets (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Invisible hack
    AC_CODE_TRIGGER_TYPE_KICK, // Lagcomp-spoof
    AC_CODE_TRIGGER_TYPE_WARNING, // Tuning hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Parkour mod
    AC_CODE_TRIGGER_TYPE_KICK, // Quick turn
    AC_CODE_TRIGGER_TYPE_WARNING, // Rapid fire
    AC_CODE_TRIGGER_TYPE_KICK, // FakeSpawn
    AC_CODE_TRIGGER_TYPE_WARNING, // FakeKill
    AC_CODE_TRIGGER_TYPE_KICK, // Pro Aim
    AC_CODE_TRIGGER_TYPE_WARNING, // CJ run
    AC_CODE_TRIGGER_TYPE_WARNING, // CarShot
    AC_CODE_TRIGGER_TYPE_WARNING, // CarJack
    AC_CODE_TRIGGER_TYPE_WARNING, // UnFreeze
    AC_CODE_TRIGGER_TYPE_WARNING, // AFK Ghost
    AC_CODE_TRIGGER_TYPE_WARNING, // Full Aiming
    AC_CODE_TRIGGER_TYPE_KICK, // Fake NPC
    AC_CODE_TRIGGER_TYPE_WARNING, // Reconnect
    AC_CODE_TRIGGER_TYPE_WARNING, // High Ping
    AC_CODE_TRIGGER_TYPE_KICK, // Dialog Hack
    AC_CODE_TRIGGER_TYPE_KICK, // Sandbox
    AC_CODE_TRIGGER_TYPE_WARNING, // Invalid Version
    AC_CODE_TRIGGER_TYPE_KICK, // Rcon hack
    AC_CODE_TRIGGER_TYPE_KICK, // Tuning crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Invalid seat crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Dialog crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Attached object crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Weapon crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Connects to one slot
    AC_CODE_TRIGGER_TYPE_WARNING, // Flood callback functions
    AC_CODE_TRIGGER_TYPE_WARNING, // Flood change seat
    AC_CODE_TRIGGER_TYPE_KICK, // DDos
    AC_CODE_TRIGGER_TYPE_KICK // NOP`s
};

new AC_CODE_TRIGGER_TYPE_MOBILE[AC_MAX_CODES] =
{
    AC_CODE_TRIGGER_TYPE_WARNING, // Airbreak (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Airbreak (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (into/between vehicles)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (vehicle to player)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (pickups)
    AC_CODE_TRIGGER_TYPE_KICK, // FlyHack (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // FlyHack (in vehicle)
    AC_CODE_TRIGGER_TYPE_KICK, // SpeedHack (onfoot)
    AC_CODE_TRIGGER_TYPE_KICK, // SpeedHack (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Health hack (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Health hack (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Armour hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Money hack
    AC_CODE_TRIGGER_TYPE_KICK, // Weapon hack
    AC_CODE_TRIGGER_TYPE_KICK, // Ammo hack (add)
    AC_CODE_TRIGGER_TYPE_KICK, // Ammo hack (infinite)
    AC_CODE_TRIGGER_TYPE_WARNING, // Special actions hack
    AC_CODE_TRIGGER_TYPE_KICK, // GodMode from bullets (onfoot)
    AC_CODE_TRIGGER_TYPE_KICK, // GodMode from bullets (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Invisible hack
    AC_CODE_TRIGGER_TYPE_KICK, // Lagcomp-spoof
    AC_CODE_TRIGGER_TYPE_KICK, // Tuning hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Parkour mod
    AC_CODE_TRIGGER_TYPE_KICK, // Quick turn
    AC_CODE_TRIGGER_TYPE_WARNING, // Rapid fire
    AC_CODE_TRIGGER_TYPE_WARNING, // FakeSpawn
    AC_CODE_TRIGGER_TYPE_WARNING, // FakeKill
    AC_CODE_TRIGGER_TYPE_WARNING, // Pro Aim
    AC_CODE_TRIGGER_TYPE_WARNING, // CJ run
    AC_CODE_TRIGGER_TYPE_WARNING, // CarShot
    AC_CODE_TRIGGER_TYPE_WARNING, // CarJack
    AC_CODE_TRIGGER_TYPE_WARNING, // UnFreeze
    AC_CODE_TRIGGER_TYPE_WARNING, // AFK Ghost
    AC_CODE_TRIGGER_TYPE_WARNING, // Full Aiming
    AC_CODE_TRIGGER_TYPE_WARNING, // Fake NPC
    AC_CODE_TRIGGER_TYPE_WARNING, // Reconnect
    AC_CODE_TRIGGER_TYPE_WARNING, // High Ping
    AC_CODE_TRIGGER_TYPE_WARNING, // Dialog Hack
    AC_CODE_TRIGGER_TYPE_KICK, // Sandbox
    AC_CODE_TRIGGER_TYPE_WARNING, // Invalid Version
    AC_CODE_TRIGGER_TYPE_KICK, // Rcon hack
    AC_CODE_TRIGGER_TYPE_KICK, // Tuning crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Invalid seat crasher
    AC_CODE_TRIGGER_TYPE_KICK, // Dialog crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Attached object crasher
    AC_CODE_TRIGGER_TYPE_KICK, // Weapon crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Connects to one slot
    AC_CODE_TRIGGER_TYPE_WARNING, // Flood callback functions
    AC_CODE_TRIGGER_TYPE_WARNING, // Flood change seat
    AC_CODE_TRIGGER_TYPE_KICK, // DDos
    AC_CODE_TRIGGER_TYPE_KICK // NOP`s
};

new pAntiCheatLastCodeTriggerTime[MAX_PLAYERS][AC_MAX_CODES]; // An array storing the last time each anti-cheat code was triggered on a player


forward OnCheatDetected(playerid, const ip_address[], type, code);
public OnCheatDetected(playerid, const ip_address[], type, code)
{
	if(IsPlayerNPC(playerid)) return 1;
    if(isBotPlayer(playerid)) return 1;
	if(IsPlayerMobile(playerid) && code != 1 && code != 3 && code != 10) return 1;

	new bot_ip[16];
	GetPlayerIp(playerid, bot_ip, sizeof(bot_ip));
	if(!strcmp(bot_ip, "255.255.255.255", true)) return 1;

	if(PlayerInfo[playerid][admin] >= 1) return 1;

    if(type == AC_GLOBAL_TRIGGER_TYPE_PLAYER)
    {
        switch(code)
        {
            case 5, 6, 11, 22, 21:
            {
                return 1;
            }
            case 32: // CarJack
            {
                new
                    Float:x,
                    Float:y,
                    Float:z;

                AntiCheatGetPos(playerid, x, y, z);
                return SetPlayerPos(playerid, x, y, z);
            }
            default:
            {
                if(timestamp -pAntiCheatLastCodeTriggerTime[playerid][code] < AC_TRIGGER_ANTIFLOOD_TIME)
                    return 1;

                pAntiCheatLastCodeTriggerTime[playerid][code] = timestamp;

                new trigger_type = IsPlayerMobile(playerid) ? AC_CODE_TRIGGER_TYPE_MOBILE[code] : AC_CODE_TRIGGER_TYPE_PC[code];

				switch(trigger_type)
				{
	                case AC_CODE_TRIGGER_TYPE_WARNING:
	                {
	                    AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] in player mashkok be cheat ast hatman check shavad: %s [code: %03d].", PlayerInfo[playerid][name], playerid, AC_CODE_NAME[code], code);
						AddWarning(playerid, AC_CODE_NAME[code], 0);
	                }
	                case AC_CODE_TRIGGER_TYPE_KICK:
                    {
                        CheatDetectedKick(playerid, code, AC_CODE_NAME[code], true);
                    }
                    case AC_CODE_TRIGGER_TYPE_DISABLED: return 1;
				}
            }
        }
    }
    else // AC_GLOBAL_TRIGGER_TYPE_IP
    {
        AdminMes("<AC-BAN-IP> IP-Address %s has been blocked: %s [code: %03d].", ip_address, AC_CODE_NAME[code], code);

        BlockIpAddress(p_t_info[playerid][p_ip], 60 * 1000);
    }
    return 1;
}

stock CheatDetectedKick(playerid, cheat_code, cheat_name[], nex_ac)
{
	AdminMes(""c_server"* A.INFO:"c_grey" %s[%d] tavasot anticheat kick shod (%s [code: %03d]).", PlayerInfo[playerid][name], playerid, cheat_name, cheat_code);

    global_string = "";
	format(global_string, sizeof(global_string), ""c_orange_red"Shoma be dalil mashkok bodan be Cheat tavasot anticheat disconnect shodid.\n\n\
	"c_white"Esm Shoma: "c_server"%s\n\
	"c_white"Cheat Code: "c_server"%s\n\
	"c_white"Ping: "c_server"%dms\n\
	"c_white"Packet Loss: "c_server"%.2f\n\
	"c_white"Zamani ke disconnect shodid: %02d:%02d:%02d\n\n\
	"c_grey"* Be yad dashte bashid agar az Cheat/Taghalob estefade konid momken ast account shoma masdod shavad.\n", PlayerInfo[playerid][name], cheat_name, GetPlayerPing(playerid), NetStats_PacketLossPercent(playerid), timestamp_hour, timestamp_minute, timestamp_second),
	show_dialog(playerid, d_none, DIALOG_STYLE_MSGBOX, !""scm_dialog"Anti-Cheat", global_string, !"Bastan", !"");

	SendMes(playerid, col_gray, "{ff1a1a}You have been kicked by the anti-cheat system: Reason: %s", cheat_name);

	AddWarning(playerid, cheat_name, 1);

    if(nex_ac)
	    AntiCheatKickWithDesync(playerid, cheat_code);
    else
        kick_player(playerid);
    return 1;
}
