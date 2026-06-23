//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=| Mihan Role Play|=-=-=-=-=-=-=-=-=-=-=-=-=//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

/* 
    System Information 
    ----------------
    Developer: Abolfazl Hosseini (Github : @inj3ct0r & Tel: @inject3r)
    Version: 1.0.0
    File Type: pwn

    All rights to this file are reserved by Developer. Unauthorized use, reproduction, or modification of this file is strictly prohibited. 

    Copyright © 2024 Abolfazl Hosseini. All rights reserved. 
*/


// Bots System

#include "../library/static/system/server/bots.inc"

// House System
// --------------------
#include "../library/static/system/server/house/index.inc"

// Family System
// --------------------
// Implements a family system for creating and managing in-game families.
#include "../library/static/system/server/family/index.inc"

// Name Date Ping TextDraw
// --------------------
// Displays player name, date, and ping information via TextDraws.
#include "../library/static/system/player/name_date_ping_textdraws.inc"

// Prevent Join With Same Account
// --------------------
// Prevents players from joining with duplicate accounts.
#include "../library/static/system/server/prevent_join_with_same_account.inc"

// Damage Info
// --------------------
#include "../library/static/system/player/damage_info.inc"

// Damage Info
// --------------------
#include "../library/static/system/player/player_damages.inc"

// Factions System
// --------------------
#include "../library/static/system/server/factions/index.inc"

// Work Book System
// --------------------
#include "../library/static/system/server/work_book.inc"

// Inventory System
// --------------------
// Manages player inventories, item pickups, and storage systems.
#include "../library/static/system/player/inventory/index.inc"

// Ghetto System
// --------------------
#include "../library/static/system/server/ghetto/index.inc"

// Top War System
// --------------------
// Manages top war-related statistics and rankings for players.
#include "../library/static/system/server/top_war/index.inc"

// Seatbelt Helmet
// --------------------
// Implements seatbelt and helmet systems for player safety in vehicles.
#include "../library/static/system/server/seatbelt_helmet.inc"

// Math System
// --------------------
// Provides mathematical utilities or mini-games for players.
#include "../library/static/system/server/math_system.inc"

// Counter Strike
// --------------------
// Implements a Counter-Strike-style mini-game or mode.
#include "../library/static/system/server/counter_strike.inc"

// DMZ System
// --------------------
// Implements deathmatch zones where players can freely engage in combat.
#include "../library/static/system/server/lobby.inc"

// Map Icon System
// --------------------
// Adds dynamic map icons for various server locations or events.
#include "../library/static/system/server/mapicons.inc"

// Gate System
// --------------------
// Handles the creation and control of dynamic gates.
#include "../library/static/system/server/gate/index.inc"

// Premium System
// --------------------
// Provides functionality for managing premium features for players, 
// including subscriptions, perks, and related logic.
#include "../library/static/system/player/premium/index.inc"

// BoomBox
// --------------------
// Adds functionality for players to use BoomBoxes to play music in-game.
#include "../library/static/system/player/boombox.inc"

// Benchs System
// --------------------
// Adds interactable benches for player interactions.
#include "../library/static/system/server/benchs.inc"

// SMS System
// --------------------
// Provides an in-game SMS system for communication between players.
#include "../library/static/system/server/sms/index.inc"

// Debug Mode
// --------------------
// Enables debugging tools and commands for server administrators.
#include "../library/static/system/server/debug_mode.inc"

// Helper System
// --------------------
// Provides tools and features for in-game helpers and their tasks.
#include "../library/static/system/server/helper_system.inc"

// Anti Insult ADV
// --------------------
// Prevents players from using offensive language in advertisements.
#include "../library/static/system/server/anti_insult_adv.inc"

// Radio Station System
// --------------------
#include "../library/static/system/server/radio_station_system.inc"

// Drop Gun
// --------------------
// Handles the logic for players dropping weapons upon death.
#include "../library/static/system/player/death_drop_guns.inc"

// Health Card
// --------------------
// Implements a health card system for managing player health recovery.
#include "../library/static/system/player/health_card.inc"

// Fallout Game
// --------------------
// Adds a Fallout-inspired mini-game or functionality.
#include "../library/static/system/server/fallout_game.inc"

// Voice Phone Call
// --------------------
// Provides a voice-based phone call system between players.
#include "../library/static/system/player/voice_phone_call.inc"

// Ist Bazresi System
// --------------------
// Manages inspection zones for specific areas like LV and LS.
#include "../library/static/system/server/ist_bazresi_lv_ls.inc"

// Vote System
// --------------------
// Adds a voting system for events, polls, or decisions.
#include "../library/static/system/server/vote/index.inc"

// Color Match System
// --------------------
// Implements a color-matching mini-game or functionality.
#include "../library/static/system/server/color_match/index.inc"

// Player Anims
// --------------------
// Manages custom player animations for enhanced gameplay.
#include "../library/static/system/player/player_anims.inc"

// Auto Message
// --------------------
// Sends periodic automated messages in the server.
#include "../library/static/system/server/auto_message.inc"

// Event System
// --------------------
// Manages server events, including registration and rewards.
#include "../library/static/system/server/event.inc"

// Voice Chat System
// --------------------
// Enables voice chat functionality for players.
#include "../library/static/system/server/voicechat.inc"

// ZoneName System
// --------------------
// Displays the current zone name for players.
#include "../library/static/system/server/zonename.inc"

// Binder System
// --------------------
#include "../library/static/system/player/binder.inc"

// Rent System
// --------------------
#include "../library/static/system/server/rent_vehicle.inc"

// Suggetion System
// --------------------
#include "../library/static/system/player/suggestion-system.inc"

// PIN System
// --------------------
#include "../library/static/system/player/pin.inc"

// Prison social services
// --------------------
#include "../library/static/system/server/csjail.inc"

// Metro System
// --------------------
#include "../library/static/system/server/metro.inc"

// Parking System
// --------------------
#include "../library/static/system/server/parkings.inc"

// Jail System
// --------------------
#include "../library/static/system/server/player_jail.inc"

// Job System
// --------------------
#include "../library/static/system/server/jobs/index.inc"

// Gun License Exam
// --------------------
#include "../library/static/system/server/license_gun.inc"

// Admin System
// --------------------
#include "../library/static/system/server/admin/index.inc"

// Marjoana System
// --------------------
#include "../library/static/system/server/marjoana.inc"

// Donate CMD && Dialog's
// --------------------
#include "../library/static/system/server/donate.inc"

// Rcon System
// --------------------
#include "../library/static/system/server/rcon.inc"