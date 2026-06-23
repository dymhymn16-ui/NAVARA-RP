// ---------------------------------Animation commands-----------------------------------
cmd:handsup(playerid, params[]) {
    useanim(playerid, "ROB_BANK","SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 0);
    return true;
}

cmd:sit(playerid, params[]) {
    useanim(playerid,"PED","SEAT_down",4.0,0,0,1,1,0);
    return true;
}

cmd:aim(playerid, params[]) {
    useanim(playerid,"PED","gang_gunstand",3.0,0,1,1,1,0);
    return true;
}

cmd:cellin(playerid, params[]) {
    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
    return true;
}

cmd:cellout(playerid, params[]) {
    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
    return true;
}


cmd:drunk(playerid, params[]) {
    useanim(playerid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
    return true;
}

cmd:bomb(playerid, params[]) {
    useanim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
    return true;
}

cmd:bar(playerid, params[]) {
    useanim(playerid,"BAR","Barserve_bottle",4.0,0,0,0,0,0);
    return true;
}

cmd:stoptaxi(playerid, params[]) {
    useanim(playerid,"PED","IDLE_taxi",4.0,0,0,0,0,0);
    return true;
}

cmd:getarrested(playerid, params[]) {
    useanim(playerid,"ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1);
    return true;
}

cmd:laugh(playerid, params[]) {
    useanim(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
    return true;
}

cmd:lookout(playerid, params[]) {
    useanim(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0);
    return true;
}

cmd:crossarms(playerid, params[]) {
    useanim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
    return true;
}

cmd:hide(playerid, params[]) {
    useanim(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
    return true;
}

cmd:vomit(playerid, params[]) {
    useanim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
    return true;
}

cmd:aeat(playerid, params[]) {
    useanim(playerid, "FOOD", "EAT_Burger", 4.1,1,1,1,1,1);
    return true;
}

cmd:sipdrink(playerid, params[]) {
    useanim(playerid, "GANGS", "drnkbr_prtl", 4.1,1,1,1,1,1);
    return true;
}

cmd:slapass(playerid, params[]) {
    useanim(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
    return true;
}

cmd:chat(playerid, params[]) {
    useanim(playerid,"PED","IDLE_CHAT",4.0,0,0,0,1,1);
    return true;
}

cmd:fucku(playerid, params[]) {
    useanim(playerid,"PED","fucku",4.0,0,0,0,0,0);
    return true;
}

cmd:taichi(playerid, params[]) {
    useanim(playerid,"PARK","Tai_Chi_Loop",4.0,0,0,0,0,0);
    return true;
}

cmd:injured(playerid, params[]) {
    useanim(playerid, "SWEET", "Sweet_injuredloop", 4.0,0,0,1,1,0);
    return true;
}

cmd:ano(playerid, params[]) {
    useanim(playerid,"GANGS","Invite_No",4.0,0,0,0,0,0);
    return true;
}

cmd:ayes(playerid, params[]) {
    useanim(playerid,"GANGS","Invite_Yes",4.0,0,0,0,0,0);
    return true;
}

cmd:crawl(playerid, params[]) {
    useanim(playerid,"PED","CAR_crawloutRHS",4.0,0,0,0,0,0);
    return true;
}

cmd:apush(playerid, params[]) {
    useanim(playerid,"GANGS","shake_cara",4.0,0,0,0,0,0);
    return true;
}

cmd:akick(playerid, params[]) {
    useanim(playerid,"POLICE","Door_Kick",4.0,0,0,0,0,0);
    return true;
}

cmd:facepalm(playerid, params[]) {
    useanim(playerid,"MISC","plyr_shkhead",4.0,0,0,0,0,0);
    return true;
}

cmd:balls(playerid, params[]) {
    useanim(playerid,"MISC","scratchballs_01",4.0,0,0,0,0,0);
    return true;
}

cmd:lowbodypush(playerid, params[]) {
    useanim(playerid,"GANGS","shake_carSH",4.0,0,0,0,0,0);
    return true;
}

cmd:aspray(playerid, params[]) {
    useanim(playerid,"SPRAYCAN","spraycan_full",4.0,0,0,0,0,0);
    return true;
}

cmd:medic(playerid, params[]) {
    useanim(playerid,"MEDIC","CPR",4.0,0,0,0,0,0);
    return true;
}

cmd:koface(playerid, params[]) {
    useanim(playerid,"PED","KO_shot_face",4.0,0,1,1,1,0);
    return true;
}

cmd:kostomach(playerid, params[]) {
    useanim(playerid,"PED","KO_shot_stom",4.0,0,1,1,1,0);
    return true;
}

cmd:lifejump(playerid, params[]) {
    useanim(playerid,"PED","EV_dive",4.0,0,1,1,1,0);
    return true;
}

cmd:rollfall(playerid, params[]) {
    useanim(playerid,"PED","BIKE_fallR",4.0,0,1,1,1,0);
    return true;
}

cmd:hoodfrisked(playerid, params[]) {
    useanim(playerid,"POLICE","crm_drgbst_01",1.0,0,1,1,1,0);
    return true;
}

cmd:aflip(playerid, params[]) {
    useanim(playerid,"PED","KD_left",4.1,0,1,1,1,0);
    return true;
}

cmd:box(playerid, params[]) {
    useanim(playerid,"GYMNASIUM","GYMshadowbox",4.0,0,1,1,1,0);
    return true;
}

cmd:chant(playerid, params[]) {
    useanim(playerid,"RIOT","RIOT_CHANT",4.0,0,1,1,1,0);
    return true;
}

cmd:finger(playerid, params[]) {
    useanim(playerid,"RIOT","RIOT_FUKU",2.0,0,0,0,0,0);
    return true;
}

cmd:gpunch(playerid, params[]) {
    useanim(playerid,"FIGHT_B","FightB_G",4.0,0,0,0,0,0);
    return true;
}

cmd:gkick(playerid, params[]) {
    useanim(playerid,"FIGHT_D","FightD_G",4.0,0,0,0,0,0);
    return true;
}

cmd:lowthrow(playerid, params[]) {
    useanim(playerid,"GRENADE","WEAPON_throwu",3.0,0,0,0,0,0);
    return true;
}

cmd:riot(playerid, params[]) {
    useanim(playerid,"RIOT","RIOT_ANGRY",4.0,0,0,0,0,0);
    return true;
}

cmd:abp(playerid, params[]) {
    useanim(playerid,"benchpress","gym_bp_celebrate",4.0,0,0,0,0,0);
    return true;
}

cmd:cry(playerid, params[]) {
    useanim(playerid,"GRAVEYARD","mrnF_loop",4.0,0,0,0,0,0);
    return true;
}

cmd:taxir(playerid, params[]) {
    useanim(playerid, "MISC","hiker_pose", 3.0,0,1,1,1,0);
    return true;
}

cmd:taxil(playerid, params[]) {
    useanim(playerid, "MISC","hiker_pose_L", 3.0,0,1,1,1,0);
    return true;
}

cmd:gro(playerid, params[]) {
    useanim(playerid,"BEACH", "ParkSit_M_loop", 4.0, 0, 0, 0, 0, 0);
    return true;
}

cmd:seat(playerid, params[]) {
    useanim(playerid,"INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
    return true;
}

cmd:tatto(playerid, params[]) {
    useanim(playerid,"TATTOOS", "TAT_ArmR_Pose_P", 4.1, 0, 1, 1, 1, 0);
    return true;
}

cmd:waiml(playerid, params[])
{
    useanim(playerid,"PED","Driveby_L",4.1,0,1,1,1,1);
    return 1;
}

cmd:waimr(playerid, params[]) {
    useanim(playerid,"PED","Driveby_R",4.1,0,1,1,1,1);
    return true;
}

cmd:caim(playerid, params[]) {
    useanim(playerid,"PED","IDLE_ROCKET",4.1,0,1,1,1,1);
    return true;
}

cmd:creep(playerid, params[]) {
    useanim(playerid,"PED","Player_Sneak",4.1,1,1,1,1,1);
    return true;
}

cmd:sroll(playerid, params[]) {
    useanim(playerid,"SWAT","JMP_Wall1m_180",4.1,0,1,1,1,0);
    return true;
}

cmd:gesture(playerid, params[]) {
    useanim(playerid,"SWAT","swt_lkt",4.0,0,0,0,0,0);
    return true;
}

cmd:lookoutr(playerid, params[]) {
    useanim(playerid,"SWAT","swt_wllpk_L",4.0,0,0,1,1,0);
    return true;
}

cmd:lookoutl(playerid, params[]) {
    useanim(playerid,"SWAT","swt_wllpk_R",4.0,0,0,1,1,0);
    return true;
}

cmd:agreement(playerid, params[]) {
    useanim(playerid,"COP_AMBIENT","Coplook_think",4.0,0,0,0,0,0);
    return true;
}

cmd:bend(playerid, params[]) {
    useanim(playerid,"BAR","Barserve_order",4.0,0,0,0,0,0);
    return true;
}

cmd:rod(playerid, params[]) {
    useanim(playerid,"benchpress","gym_bp_up_A",4.0,0,0,1,1,0);
    return true;
}

cmd:tgro(playerid, params[]) {
    useanim(playerid,"CAMERA","camcrch_cmon",4.0,0,0,1,1,0);
    return true;
}

cmd:cmouth(playerid, params[]) {
    useanim(playerid,"ON_LOOKERS","panic_in",4.0,0,0,1,1,0);
    return true;
}

cmd:gog(playerid, params[]) {
    useanim(playerid,"goggles","goggles_put_on",4.1,0,1,1,1,1);
    return true;
}

cmd:nfall(playerid, params[]) {
    useanim(playerid,"HEIST9","CAS_G2_GasKO",4.1,0,1,1,1,0);
    return true;
}

cmd:hsit(playerid, params[]) {
    useanim(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop",4.0,0,0,1,1,0);
    return true;
}

cmd:csit(playerid, params[]) {
    useanim(playerid,"INT_OFFICE","OFF_Sit_Type_Loop",4.0,0,0,1,1,0);
    return true;
}

cmd:bracing(playerid, params[]) {
    useanim(playerid,"PLAYIDLES","stretch",4.0,0,0,0,0,0);
    return true;
}

cmd:pool(playerid, params[]) {
    useanim(playerid,"POOL","POOL_Long_Start",4.1,0,1,1,1,0);
    return true;
}

cmd:ssearch(playerid, params[]) {
    useanim(playerid,"ROB_BANK","CAT_Safe_Rob",4.0,0,0,0,0,0);
    return true;
}

cmd:daim(playerid, params[]) {
    useanim(playerid,"RYDER","Van_Stand_Crate",3.0,0,1,1,1,0);
    return true;
}

cmd:rhandl(playerid, params[]) {
    useanim(playerid,"SCRATCHING","scdlulp",4.0,0,0,1,1,0);
    return true;
}

cmd:rhandr(playerid, params[]) {
    useanim(playerid,"SCRATCHING","scdrulp",4.0,0,0,1,1,0);
    return true;
}

cmd:hstand(playerid, params[]) {
    useanim(playerid,"SCRATCHING","scdrdlp",4.0,0,0,1,1,0);
    return true;
}

cmd:nlean(playerid, params[]) {
    useanim(playerid,"SHAMAL","SHAMAL_align",4.1,0,1,1,1,0);
    return true;
}

cmd:shelter(playerid, params[]) {
    useanim(playerid,"SHOP","SHP_Duck_Fire",4.0,0,0,1,1,0);
    return true;
}

cmd:lookback(playerid, params[]) {
    useanim(playerid,"PED","flee_lkaround_01",4.0,0,0,0,0,0);
    return true;
}

cmd:wsit(playerid, params[]) {
    useanim(playerid,"SHOP","SHP_Gun_Duck",4.0,0,0,1,1,0);
    return true;
}

cmd:waim(playerid, params[]) {
    useanim(playerid,"TEC","TEC_reload",4.1,0,1,1,1,1);
    return true;
}

cmd:hangon(playerid, params[]) {
    useanim(playerid,"TRAIN","tran_ouch",4.0,0,0,1,1,0);
    return true;
}

cmd:sleepl(playerid, params[]) {
    useanim(playerid,"INT_HOUSE","BED_In_L",4.0,0,0,1,1,0);
    return true;
}

cmd:sleepr(playerid, params[]) {
    useanim(playerid,"INT_HOUSE","BED_In_R",4.0,0,0,1,1,0);
    return true;
}

cmd:blowj(playerid, params[]) {
    useanim(playerid,"BLOWJOBZ", "BJ_COUCH_START_W", 4.1, 0, 1, 1, 1, 0 );
    return true;
}

cmd:rseat(playerid, params[]) {
    useanim(playerid,"BLOWJOBZ", "BJ_COUCH_START_P", 4.1, 0, 1, 1, 1, 0 );
    return true;
}

cmd:polwalk(playerid, params[]) {
    useanim(playerid,"POLICE","Cop_move_FWD",3.0,1,1,1,1,1);
    return true;
}

cmd:nflip(playerid, params[]) {
    useanim(playerid,"PED","BIKE_fall_off",4.1,0,1,1,1,0);
    return true;
}

cmd:csdead(playerid, params[]) {
    useanim(playerid,"WUZI","CS_Dead_Guy",4.1,0,1,1,1,0);
    return true;
}

cmd:follow(playerid, params[]) {
    useanim(playerid,"WUZI","Wuzi_follow",4.1,0,1,1,1,1);
    return true;
}

cmd:grnd(playerid, params[]) {
    useanim(playerid,"WUZI","Wuzi_grnd_chk",4.0,0,0,0,0,0);
    return true;
}

cmd:copa(playerid, params[]) {
    useanim(playerid,"COP_AMBIENT","Copbrowse_in",4.1,0,1,1,1,0);
    return true;
}

cmd:cmon(playerid, params[]) {
    useanim(playerid,"OTB","wtchrace_cmon",4.1,0,1,1,1,0);
    return true;
}

cmd:lose(playerid, params[]) {
    useanim(playerid,"OTB","wtchrace_lose",4.1,0,1,1,1,0);
    return true;
}

cmd:win(playerid, params[]) {
    useanim(playerid,"OTB","wtchrace_win",4.1,0,1,1,1,0);
    return true;
}

cmd:gunthreat(playerid, params[]) {
    useanim(playerid,"SHOP","SHP_Gun_Threat",4.1,0,1,1,1,0);
    return true;
}

cmd:givecash(playerid, params[]) {
    useanim(playerid,"SHOP","SHP_Rob_GiveCash",4.1,0,1,1,1,0);
    return true;
}

cmd:robr(playerid, params[]) {
    useanim(playerid,"SHOP","SHP_Rob_React",4.1,0,1,1,1,0);
    return true;
}

cmd:serend(playerid, params[]) {
    useanim(playerid,"SHOP","SHP_Serve_End",4.1,0,1,1,1,0);
    return true;
}

cmd:heist(playerid, params[]) {
    useanim(playerid,"HEIST9","Use_SwipeCard",4.0,0,0,0,0,0);
    return true;
}

cmd:frontfall(playerid, params[]) {
    useanim(playerid,"PED","FLOOR_hit_f",4.1,0,1,1,1,0);
    return true;
}

cmd:pants(playerid, params[]) {
    useanim(playerid,"BLOWJOBZ","BJ_STAND_END_P",4.0,0,0,0,0,0);
    return true;
}
/////////////////////////////////////////////////////////////////////////
cmd:tired(playerid, params[]) {
    useanim(playerid,"FAT","IDLE_tired",4.0,0,0,1,1,0);
    return true;
}

cmd:climb(playerid, params[]) {
    useanim(playerid,"PED","CLIMB_jump",4.0,0,0,1,1,0);
    return true;
}

cmd:tlean(playerid, params[]) {
    useanim(playerid,"PED","DRIVE_BOAT",4.0,0,0,1,1,0);
    return true;
}

cmd:pushup(playerid, params[]) {
    useanim(playerid,"PED","getup_front",4.0,0,0,1,1,0);
    return true;
}

cmd:protection(playerid, params[]) {
    useanim(playerid,"PED","FightShB",4.0,0,1,1,1,1);
    return true;
}

cmd:swallow(playerid, params[]) {
    useanim(playerid,"PED","gum_eat",4.0,0,0,0,0,0);
    return true;
}

cmd:stand(playerid, params[]) {
    useanim(playerid,"PED","IDLE_HBHB",3.0,0,1,1,1,0);
    return true;
}

cmd:pullhand(playerid, params[]) {
    useanim(playerid,"PED","Jetpack_Idle",3.0,0,1,1,1,0);
    return true;
}

cmd:nlook(playerid, params[]) {
    useanim(playerid,"PED","roadcross_gang",4.0,0,0,0,0,0);
    return true;
}

cmd:extend(playerid, params[]) {
    useanim(playerid,"PED","Shove_Partial",4.1,0,1,1,1,1);
    return true;
}

cmd:stopit(playerid, params[]) {
    useanim(playerid,"PED","Walk_DoorPartial",4.0,0,0,0,0,0);
    return true;
}

cmd:ksit(playerid, params[]) {
    useanim(playerid,"INT_OFFICE","OFF_Sit_Crash",4.0,0,0,1,1,0);
    return true;
}

cmd:esit(playerid, params[]) {
    useanim(playerid,"INT_OFFICE","OFF_Sit_Drink",4.0,0,0,1,1,0);
    return true;
}

cmd:tsit(playerid, params[]) {
    useanim(playerid,"INT_OFFICE","OFF_Sit_Watch",4.0,0,0,1,1,0);
    return true;
}

cmd:rtake(playerid, params[]) {
    useanim(playerid,"BAR","Barserve_give",4.0,0,0,0,0,0);
    return true;
}

cmd:forwardlook(playerid, params[]) {
    useanim(playerid,"BD_FIRE","BD_Panic_02",4.1,0,1,1,1,0);
    return true;
}

cmd:wforwardlook(playerid, params[]) {
    useanim(playerid,"BD_FIRE","BD_Panic_03",4.1,0,1,1,1,0);
    return true;
}

cmd:taction(playerid, params[]) {
    useanim(playerid,"BD_FIRE","wash_up",4.0,0,0,0,0,0);
    return true;
}

cmd:catch(playerid, params[]) {
    useanim(playerid,"MD_CHASE","MD_HANG_Loop",4.1,0,1,1,1,0);
    return true;
}

cmd:despair(playerid, params[]) {
    useanim(playerid,"BSKTBALL","BBALL_react_miss",4.0,0,0,0,0,0);
    return true;
}

cmd:rooting(playerid, params[]) {
    useanim(playerid,"BSKTBALL","BBALL_react_score",4.1,1,1,1,1,0);
    return true;
}

cmd:spyglass(playerid, params[]) {
    useanim(playerid,"CAMERA","picstnd_take",4.1,0,1,1,1,0);
    return true;
}

cmd:looksky(playerid, params[]) {
    useanim(playerid,"ON_LOOKERS","lkup_loop",4.1,0,1,1,1,0);
    return true;
}

cmd:mshow(playerid, params[]) {
    useanim(playerid,"ON_LOOKERS","panic_point",4.1,0,1,1,1,0);
    return true;
}

cmd:wshow(playerid, params[]) {
    useanim(playerid,"ON_LOOKERS","panic_shout",4.1,0,1,1,1,0);
    return true;
}

cmd:hshow(playerid, params[]) {
    useanim(playerid,"ON_LOOKERS","point_loop",4.1,0,1,1,1,0);
    return true;
}

cmd:sh(playerid, params[]) {
    useanim(playerid,"ON_LOOKERS","shout_in",4.0,0,0,0,0,0);
    return true;
}

cmd:crossfingers(playerid, params[]) {
    useanim(playerid,"CASINO","cards_loop",4.1,0,1,1,1,0);
    return true;
}

cmd:delight(playerid, params[]) {
    useanim(playerid,"CASINO","manwinb",4.0,0,0,0,0,0);
    return true;
}

cmd:hdelight(playerid, params[]) {
    useanim(playerid,"CASINO","manwind",4.0,0,0,0,0,0);
    return true;
}

cmd:showtable(playerid, params[]) {
    useanim(playerid,"CASINO","Roulette_bet",4.1,0,1,1,1,0);
    return true;
}

cmd:tfacepalm(playerid, params[]) {
    useanim(playerid,"CASINO","Roulette_lose",4.1,0,1,1,1,0);
    return true;
}

cmd:tpull(playerid, params[]) {
    useanim(playerid,"CASINO","Slot_in",4.1,0,1,1,1,0);
    return true;
}

cmd:fail(playerid, params[]) {
    useanim(playerid,"CASINO","Slot_lose_out",4.0,0,0,0,0,0);
    return true;
}

cmd:joy(playerid, params[]) {
    useanim(playerid,"CASINO","Slot_win_out",4.0,0,0,0,0,0);
    return true;
}

cmd:wear(playerid, params[]) {
    useanim(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
    return true;
}

cmd:fsit(playerid, params[]) {
    useanim(playerid,"JST_BUISNESS","girl_02",4.1,0,1,1,1,0);
    return true;
}

cmd:crushjump(playerid, params[]) {
    useanim(playerid,"DODGE","Crush_Jump",4.1,0,1,1,1,0);
    return true;
}

cmd:scatch(playerid, params[]) {
    useanim(playerid,"FINALE","FIN_LegsUp_Loop",4.1,0,1,1,1,0);
    return true;
}

cmd:lookfloor(playerid, params[]) {
    useanim(playerid,"FINALE","FIN_Cop1_Loop",4.1,0,1,1,1,0);
    return true;
}

cmd:tramplefloor(playerid, params[]) {
    useanim(playerid,"FINALE","FIN_Cop1_Stomp",4.1,1,1,1,1,0);
    return true;
}

cmd:swing(playerid, params[]) {
    useanim(playerid,"Freeweights","gym_free_B",4.1,0,1,1,1,0);
    return true;
}

cmd:nbp(playerid, params[]) {
    useanim(playerid,"Freeweights","gym_free_celebrate",4.0,0,0,0,0,0);
    return true;
}

cmd:takehead(playerid, params[]) {
    useanim(playerid,"HAIRCUTS","BRB_Cut",4.1,0,1,1,1,0);
    return true;
}

cmd:readtable(playerid, params[]) {
    useanim(playerid,"SCRATCHING","sclng_r",4.1,0,1,1,1,0);
    return true;
}

cmd:squat(playerid, params[]) {
    useanim(playerid,"TEC","TEC_crouchfire",4.1,0,1,1,1,0);
    return true;
}

cmd:sprawl(playerid, params[]) {
    useanim(playerid,"TATTOOS","TAT_Idle_Loop_T",4.1,0,1,1,1,0);
    return true;
}

cmd:throwmoney(playerid, params[]) {
    useanim(playerid,"STRIP","PUN_CASH",4.0,0,0,0,0,0);
    return true;
}

cmd:sho(playerid, params[]) {
    useanim(playerid,"STRIP","PUN_HOLLER",4.0,0,0,0,0,0);
    return true;
}

cmd:faim(playerid, params[]) {
    useanim(playerid,"SWORD","sword_IDLE",4.1,0,1,1,1,0);
    return true;
}

cmd:swingback(playerid, params[]) {
    useanim(playerid,"PED","getup",4.1,1,1,1,1,0);
    return true;
}

cmd:onehand(playerid, params[]) {
    useanim(playerid,"PED","CLIMB_jump2fall",4.1,0,1,1,1,0);
    return true;
}

cmd:backwalk(playerid, params[]) {
    useanim( playerid, "PED", "gas_cwr", 4.1, 1, 1, 1, 1, 1 );
    return true;
}

cmd:feettog(playerid, params[]) {
    useanim(playerid,"PED","Idlestance_fat",4.1,0,1,1,1,0);
    return true;
}

cmd:mirro(playerid, params[]) {
    useanim(playerid,"CLOTHES","CLO_Pose_Hat",4.1,0,1,1,1,0);
    return true;
}

cmd:hips(playerid, params[]) {
    useanim(playerid,"COP_AMBIENT","Coplook_shake",4.1,0,1,1,1,0);
    return true;
}

cmd:pullo(playerid, params[]) {
    useanim(playerid,"AIRPORT","thrw_barl_thrw",4.1,0,1,1,1,0);
    return true;
}

cmd:obalance(playerid, params[]) {
    useanim(playerid,"BD_FIRE","BD_Panic_02",4.1,0,1,1,1,0);
    return true;
}

cmd:wobalance(playerid, params[]) {
    useanim(playerid,"BD_FIRE","BD_Panic_03",4.1,0,1,1,1,0);
    return true;
}

cmd:dance(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /dance [1-12]");
    switch(params[0]) {
        case 1 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
        case 2 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
        case 3 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
        case 4 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
        case 5 : useanim(playerid,"DANCING","bd_clap",4.1,1,1,1,1,1);
        case 6 : useanim(playerid,"DANCING","bd_clap1",4.1,1,1,1,1,1);
        case 7 : useanim(playerid,"DANCING","DAN_Down_A",4.1,1,1,1,1,1);
        case 8 : useanim(playerid,"DANCING","DAN_Left_A",4.1,1,1,1,1,1);
        case 9 : useanim(playerid,"DANCING","DAN_Loop_A",4.1,1,1,1,1,1);
        case 10 : useanim(playerid,"DANCING","DAN_Right_A",4.1,1,1,1,1,1);
        case 11 : useanim(playerid,"DANCING","DAN_Up_A",4.1,1,1,1,1,1);
        case 12 : useanim(playerid,"DANCING","dnce_M_a",4.1,1,1,1,1,1);
        default : SendInfo(playerid, "Enter: /dance [1-12]");
    }
    return true;
}

cmd:repcar(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /repcar [1-2]");
    switch(params[0]) {
        case 1 : useanim(playerid,"CAR","Fixn_Car_Loop",3.0,0,1,1,1,0);
        case 2 : useanim(playerid,"CAR","Fixn_Car_Out",3.0,0,1,1,1,0);
        default : SendInfo(playerid, "Enter: /repcar [1-2]");
    }
    return true;
}


cmd:hnds(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /hnds [1-7]");
    switch(params[0]) {
        case 1 : useanim(playerid,"LOWRIDER","prtial_gngtlkB",4.1,0,1,1,1,1);
        case 2 : useanim(playerid,"LOWRIDER","prtial_gngtlkC",4.1,0,1,1,1,1);
        case 3 : useanim(playerid,"LOWRIDER","prtial_gngtlkD",4.1,0,1,1,1,1);
        case 4 : useanim(playerid,"LOWRIDER","prtial_gngtlkE",4.1,0,1,1,1,1);
        case 5 : useanim(playerid,"LOWRIDER","prtial_gngtlkF",4.1,0,1,1,1,1);
        case 6 : useanim(playerid,"LOWRIDER","prtial_gngtlkG",4.1,0,1,1,1,1);
        case 7 : useanim(playerid,"LOWRIDER","prtial_gngtlkH",4.1,0,1,1,1,1);
        default : SendInfo(playerid, "Enter: /hnds [1-7]");
    }
    return true;
}

cmd:strip(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /strip [1-14]");
    switch(params[0]) {
        case 1 : useanim(playerid,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1 );
        case 2 : useanim(playerid,"STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1 );
        case 3 : useanim(playerid,"STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1 );
        case 4 : useanim(playerid,"STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1 );
        case 5 : useanim(playerid,"STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1 );
        case 6 : useanim(playerid,"STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1 );
        case 7 : useanim(playerid,"STRIP", "strip_G", 4.1, 1, 1, 1, 1, 1 );
         case 8: useanim(playerid,"STRIP","STR_A2B",4.1,1,1,1,1,1);
        case 9: useanim(playerid,"STRIP","STR_B2C",4.1,1,1,1,1,1);
        case 10: useanim(playerid,"STRIP","STR_C1",4.1,1,1,1,1,1);
        case 11: useanim(playerid,"STRIP","STR_C2",4.1,1,1,1,1,1);
        case 12: useanim(playerid,"STRIP","STR_Loop_A",4.1,1,1,1,1,1);
        case 13: useanim(playerid,"STRIP","STR_Loop_B",4.1,1,1,1,1,1);
        case 14: useanim(playerid,"STRIP","STR_Loop_C",4.1,1,1,1,1,1);
        default : SendInfo(playerid, "Enter: /strip [1-14]");
    }
    return true;
}


cmd:deal(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /deal [1-3]");
    switch(params[0]) {
        case 1 : useanim(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
        case 2 : useanim(playerid, "DEALER","DEALER_IDLE", 3.0,0,1,1,1,0);
        case 3 : useanim(playerid,"GRAVEYARD","mrnM_loop",3.0,0,1,1,1,0);
        default : SendInfo(playerid, "Enter: /deal [1-3]");
    }
    return true;
}

cmd:asmoke(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /asmoke [1-6]");
    switch(params[0]) {
        case 1 : useanim(playerid, "SMOKING", "M_smklean_loop", 4.0, 0, 0, 0, 0, 0);
        case 2 : useanim(playerid, "SMOKING", "F_smklean_loop", 4.0, 0, 0, 0, 0, 0);
        case 3 : useanim(playerid, "SMOKING","M_smkstnd_loop", 4.0, 0, 0, 0, 0, 0);
        case 4 : useanim(playerid, "SMOKING","M_smk_out", 4.0, 0, 0, 0, 0, 0);
        case 5 : useanim(playerid, "SMOKING","M_smk_in",3.0,0,0,0,0,0);
        case 6 : useanim(playerid, "SMOKING","M_smk_tap",3.0,0,0,0,0,0);
        default : SendInfo(playerid, "Enter: /asmoke [1-6]");
    }
    return true;
}

cmd:rap(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /rap [1-9]");
    switch(params[0]) {
        case 1 : useanim(playerid,"RAPPING","RAP_A_Loop",4.0,0,0,0,0,0);
        case 2 : useanim(playerid,"RAPPING","RAP_C_Loop",4.0,0,0,0,0,0);
        case 3 : useanim(playerid,"GANGS","prtial_gngtlkD",4.0,0,0,0,1,1);
        case 4 : useanim(playerid,"GANGS","prtial_gngtlkH",4.0,0,0,0,1,1);
        case 5 : useanim(playerid,"GANGS","prtial_gngtlkF",4.0,0,0,0,1,1);
        case 6 : useanim(playerid,"GANGS","prtial_gngtlkG",4.0,0,0,0,1,1);
        case 7 : useanim(playerid,"PED","ATM",4.0,0,0,0,0,0);
        case 8 : useanim(playerid,"RAPPING","RAP_B_IN",3.0,0,1,1,1,0);
        case 9 : useanim(playerid,"GYMNASIUM","gym_tread_celebrate",4.1,0,1,1,1,0);
        default : SendInfo(playerid, "Enter: /rap [1-9]");
    }
    return true;
}

cmd:bat(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /bat [1-2]");
    switch(params[0]) {
        case 1 : useanim(playerid,"CRACK","Bbalbat_Idle_02",4.0, 0, 0, 0, 0, 0);
        case 2 : useanim(playerid,"CRACK","Bbalbat_Idle_01",4.0, 0, 0, 0, 0, 0);
        default : SendInfo(playerid, "Enter: /bat [1-2]");
    }
    return true;
}

cmd:basket(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /basket [1-6]");
    switch(params[0]) {
        case 1 : useanim(playerid,"BSKTBALL","BBALL_idleloop",4.0,0,0,0,0,0);
        case 2 : useanim(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
        case 3 : useanim(playerid,"BSKTBALL","BBALL_pickup",4.0,0,0,0,0,0);
        case 4 : useanim(playerid,"BSKTBALL","BBALL_run",4.1,1,1,1,1,1);
        case 5 : useanim(playerid,"BSKTBALL","BBALL_def_loop",4.0,0,0,0,0,0);
        case 6 : useanim(playerid,"BSKTBALL","BBALL_Dnk",4.0,0,0,0,0,0);
        default : SendInfo(playerid, "Enter: /basket [1-6]");
    }
    return true;
}

cmd:lean(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /lean [1-3]");
    switch(params[0]) {
        case 1 : useanim(playerid,"GANGS","leanIDLE",4.0,0,0,1,1,0);
        case 2 : useanim(playerid,"MISC","Plyrlean_loop",4.0,0,1,1,1,0);
        case 3 : useanim(playerid,"CAR_CHAT","car_talkm_loop",4.0,0,1,1,1,0);
        default : SendInfo(playerid, "Enter: /lean [1-3]");
    }
    return true;
}

cmd:lay(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /lay [1-5]");
    switch(params[0]) {
        case 1 : useanim(playerid,"BEACH", "bather", 4.0, 0, 0, 0, 0, 0);
        case 2 : useanim(playerid,"SUNBATHE","Lay_Bac_in",3.0,0,1,1,1,0);
        case 3 : useanim(playerid,"BEACH","ParkSit_W_loop",3.0,0,1,1,1,0);
        case 4 : useanim(playerid,"BEACH","SitnWait_loop_W",4.0, 0, 0, 0, 0, 0);
        case 5 : useanim(playerid,"SUNBATHE","SBATHE_F_LieB2Sit",3.0,0,1,1,1,0);
        default : SendInfo(playerid, "Enter: /lay [1-5]");
    }
    return true;
}

cmd:gsign(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /gsign [1-10]");
    switch(params[0]) {
        case 1 : useanim(playerid,"GHANDS","gsign1",4.1,0,1,1,1,1);
        case 2 : useanim(playerid,"GHANDS","gsign1LH",4.1,0,1,1,1,1);
        case 3 : useanim(playerid,"GHANDS","gsign2",4.1,0,1,1,1,1);
        case 4 : useanim(playerid,"GHANDS","gsign2LH",4.1,0,1,1,1,1);
        case 5 : useanim(playerid,"GHANDS","gsign3",4.1,0,1,1,1,1);
        case 6 : useanim(playerid,"GHANDS","gsign3LH",4.1,0,1,1,1,1);
        case 7 : useanim(playerid,"GHANDS","gsign4",4.1,0,1,1,1,1);
        case 8 : useanim(playerid,"GHANDS","gsign4LH",4.1,0,1,1,1,1);
        case 9 : useanim(playerid,"GHANDS","gsign5",4.1,0,1,1,1,1);
        case 10 : useanim(playerid,"GHANDS","gsign5LH",4.1,0,1,1,1,1);
        default : SendInfo(playerid, "Enter: /gsign [1-10]");
    }
    return true;
}

cmd:wave(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /wave [1-4]");
    switch(params[0]) {
        case 1 : useanim(playerid, "KISSING","gfwave2", 4.1,0,1,1,0,0);
        case 2 : useanim(playerid, "ON_LOOKERS","wave_loop", 4.1,1,1,1,0,0);
        case 3 : useanim(playerid,"CAMERA","camstnd_cmon",4.0,0,0,0,0,0);
        case 4 : useanim(playerid,"PED","endchat_01",4.1,0,1,1,0,0);
        default : SendInfo(playerid, "Enter: /wave [1-4]");
    }
    return true;
}

cmd:police(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /police [1-4]");
    switch(params[0]) {
        case 1 : useanim(playerid,"POLICE","CopTraf_Away",3.0,1,0,0,1,0);
        case 2 : useanim(playerid,"POLICE","CopTraf_Come",3.0,1,0,0,1,0);
        case 3 : useanim(playerid,"POLICE","CopTraf_Left",3.0,1,0,0,1,0);
        case 4 : useanim(playerid,"POLICE","CopTraf_Stop",3.0,1,0,0,1,0);
        default : SendInfo(playerid, "Enter: /police [1-4]");
    }
    return true;
}

cmd:crack(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /crack [1-7]");
    switch(params[0]) {
        case 1 : useanim(playerid,"CRACK","crckdeth2",3.0,1,1,1,1,0);
        case 2 : useanim(playerid,"CRACK","crckdeth4",3.0,0,1,1,1,0);
        case 3 : useanim(playerid,"CRACK","crckidle1",3.0,0,1,1,1,0);
        case 4 : useanim(playerid,"CRACK","crckidle2",3.0,0,1,1,1,0);
        case 5 : useanim(playerid,"CRACK","crckidle3",3.0,0,1,1,1,0);
        case 6 : useanim(playerid,"CRACK","crckdeth1",3.0,0,1,1,1,0);
        case 7 : useanim(playerid,"CRACK","crckdeth3",3.0,0,1,1,1,0);
        default : SendInfo(playerid, "Enter: /crack [1-7]");
    }
    return true;
}

cmd:acar(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /acar [1-11]");
    switch(params[0]) {
        case 1 : useanim(playerid,"LOWRIDER","lrgirl_bdbnce",4.1,0,1,1,1,0);
        case 2 : useanim(playerid,"LOWRIDER","lrgirl_hair",4.1,0,1,1,1,0);
        case 3 : useanim(playerid,"LOWRIDER","lrgirl_idle_to_l0",4.1,0,1,1,1,0);
        case 4 : useanim(playerid,"PED","Tap_hand",4.1,0,1,1,1,0);
        case 5 : useanim(playerid,"PED","Tap_handP",4.1,0,1,1,1,0);
        case 6 : useanim(playerid,"LOWRIDER","lrgirl_l12_to_l0",4.1,0,1,1,1,0);
        case 7 : useanim(playerid,"LOWRIDER","lrgirl_l2_to_l3",4.1,0,1,1,1,0);
        case 8 : useanim(playerid,"PED","CAR_LB",4.1,0,1,1,1,0);
        case 9 : useanim(playerid,"PED","CAR_sitp",4.1,0,1,1,1,0);
        case 10 : useanim(playerid,"PED","CAR_sitpLO",4.1,0,1,1,1,0);
        case 11 : useanim(playerid,"CAR_CHAT","carfone_loopA",4.1,1,1,1,1,0);
        default : SendInfo(playerid, "Enter: /acar [1-11]");
    }
    return true;
}

cmd:wallow(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /wallow [1-2]");
    switch(params[0]) {
        case 1 : useanim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll",4.1,0,1,1,1,0);
        case 2 : useanim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll_F",4.1,0,1,1,1,0);
        default : SendInfo(playerid, "Enter: /wallow [1-2]");
    }
    return true;
}

cmd:beckon(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /beckon [1-3]");
    switch(params[0]) {
        case 1 : useanim(playerid,"RYDER","RYD_Beckon_01",4.1,0,1,1,1,1);
        case 2 : useanim(playerid,"RYDER","RYD_Beckon_02",4.1,0,1,1,1,1);
        case 3 : useanim(playerid,"RYDER","RYD_Beckon_03",4.1,0,1,1,1,1);
        default : SendInfo(playerid, "Enter: /beckon [1-3]");
    }
    return true;
}

cmd:shotgun(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /shotgun [1-3]");
    switch(params[0]) {
        case 1 : useanim(playerid,"SHOTGUN","shotgun_crouchfire",4.1,0,1,1,1,1);
        case 2 : useanim(playerid,"SHOTGUN","shotgun_fire",4.1,0,1,1,1,1);
        case 3 : useanim(playerid,"SHOTGUN","shotgun_fire_poor",4.1,0,1,1,1,1);
        default : SendInfo(playerid, "Enter: /shotgun [1-3]");
    }
    return true;
}

cmd:colt(playerid, params[]) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /colt [1-3]");
    switch(params[0]) {
        case 1 : useanim(playerid,"COLT45","colt45_fire_2hands",4.1,0,1,1,1,1);
        case 2 : useanim(playerid,"COLT45","colt45_reload",4.1,0,1,1,1,1);
        case 3 : useanim(playerid,"COLT45","sawnoff_reload",4.1,0,1,1,1,1);
        default : SendInfo(playerid, "Enter: /colt [1-3]");
    }
    return true;
}

cmd:bj( playerid, params[] ) {
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /bj [1-17]");
    switch (params[0]) {
          case 1: useanim(playerid, "BLOWJOBZ", "BJ_COUCH_START_W", 4.0, 0, 1, 1, 1, 1);
          case 2: useanim(playerid, "BLOWJOBZ", "BJ_COUCH_START_P", 4.0, 0, 1, 1, 1, 1);
          case 3: useanim(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.0, 0, 1, 1, 1, 1);
          case 4: useanim(playerid, "BLOWJOBZ", "BJ_COUCH_END_W", 4.0, 0, 1, 1, 1, 1);
          case 5: useanim(playerid, "BLOWJOBZ", "BJ_COUCH_END_P", 4.0, 0, 1, 1, 1, 1);
          case 6: useanim(playerid, "BLOWJOBZ", "BJ_STAND_START_W", 4.0, 0, 1, 1, 1, 1);
          case 7: useanim(playerid, "BLOWJOBZ", "BJ_STAND_START_P", 4.0, 0, 1, 1, 1, 1);
          case 8: useanim(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.0, 0, 1, 1, 1, 1);
          case 9: useanim(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.0, 0, 1, 1, 1, 1);
          case 10: useanim(playerid, "BLOWJOBZ", "BJ_STAND_END_W", 4.0, 0, 1, 1, 1, 1);
          case 11: useanim(playerid, "BLOWJOBZ", "BJ_STAND_END_P", 4.0, 0, 1, 1, 1, 1);
          case 12: useanim(playerid, "BLOWJOBZ", "BJ_CAR_START_W", 4.0, 0, 1, 1, 1, 1);
          case 13: useanim(playerid, "BLOWJOBZ", "BJ_CAR_START_P", 4.0, 0, 1, 1, 1, 1);
          case 14: useanim(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_W", 4.0, 0, 1, 1, 1, 1);
          case 15: useanim(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_P", 4.0, 0, 1, 1, 1, 1);
          case 16: useanim(playerid, "BLOWJOBZ", "BJ_CAR_END_W", 4.0, 0, 1, 1, 1, 1);
          case 17: useanim(playerid, "BLOWJOBZ", "BJ_CAR_END_P", 4.0, 0, 1, 1, 1, 1);
          default: SendInfo(playerid, "Enter: /bj [1-17]");
    }
    return 1;
}

cmd:spank( playerid, params[] )
{
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Enter: /spank [1-8]");
    switch (params[0]) {
          case 1: useanim(playerid, "SNM", "SPANKING_IDLEW", 4.0, 0, 1, 1, 1, 1);
          case 2: useanim(playerid, "SNM", "SPANKING_IDLEP", 4.0, 0, 1, 1, 1, 1);
          case 3: useanim(playerid, "SNM", "SPANKINGW", 4.0, 0, 1, 1, 1, 1);
          case 4: useanim(playerid, "SNM", "SPANKINGP", 4.0, 0, 1, 1, 1, 1);
          case 5: useanim(playerid, "SNM", "SPANKEDW", 4.0, 0, 1, 1, 1, 1);
          case 6: useanim(playerid, "SNM", "SPANKEDP", 4.0, 0, 1, 1, 1, 1);
          case 7: useanim(playerid, "SNM", "SPANKING_ENDW", 4.0, 0, 1, 1, 1, 1);
          case 8: useanim(playerid, "SNM", "SPANKING_ENDP", 4.0, 0, 1, 1, 1, 1);
          default: SendInfo(playerid, "Enter: /spank [1-8]");
    }
    return 1;
}


alias:piss("pee");
cmd:piss(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		SetPlayerSpecialAction(playerid, 68);
		SetPlayerSpecialAction(playerid, 68);
	}
	return 1;
}

stock useanim(playerid, animlib[], animname[], Float:speed, looping, lockx, locky, lockz, lp, time = 0)
{
    ClearAnimations(playerid);
    
	p_t_info[playerid][p_animation] = true;

    ApplyAnimation(playerid, animlib, animname, speed, looping, lockx, locky, lockz, lp, time);
}

cmd:anim(playerid,params[])
{
	if(GetPlayerState(playerid)!= PLAYER_STATE_ONFOOT) return 1;
	else if(sscanf(params,"i",params[0]))
	{
		show_dialog(playerid, d_animations, DIALOG_STYLE_LIST, ""c_server"Animations", "[1] Render\n[2] Set\n[3] Dance 1\n[4] Dance 2\n[5] Stripe\n[6] Arms Up\n[7] Sest \n[8] Hold\n[9] Freeze\n[10] Calm\n[11] Handshake\n[12] Fist Shake\n[13] Belly to Belly\n[14] Status\n[15] Facepalm\n[16] Kneel\n[17] Crook (sit)\n[18] Sit\n[19] Sit\n[20] Stand on your hands ah\n[21] Dealer\n[22] Gopnik \n[23] Lie down\n[24] Repulse\n[25] Scramble\n[26] Piss", "Entekhab", "Cancel");
        return 1;
	}
	else
	{
		p_t_info[playerid][p_animation] = true;
        SendClientMessage(playerid, col_white, ""c_server"* "c_white"Shoma mitonid animation ro laghv konid ba dokme "c_server"'Space'"c_white" ya cmd [/"c_server"anim 0"c_white"]");
		
        switch(params[0])
		{
			case 0:
			{
				ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 1:
			{
				ApplyAnimation(playerid, "VENDING", "VEND_Drink2_P", 25.5, 0, 1, 0, 1, 1, 1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 2:
			{
				ApplyAnimation(playerid, "PED", "SEAT_down",  4.1,  0,  0,  0,  1,  1 , 1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 3:
			{
				SetPlayerSpecialAction(playerid,  5);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 4:
			{
				ApplyAnimation(playerid,  "DANCING",  "DAN_Loop_A",  4.1,  1,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 5:
			{
				SetPlayerSpecialAction (playerid,  SPECIAL_ACTION_DANCE4);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 6:
			{
				SetPlayerSpecialAction(playerid,  10);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 7:
			{
				ApplyAnimation(playerid,  "Attractors",  "Stepsit_in",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 8:
			{
				ApplyAnimation(playerid,  "Attractors",  "Stepsit_out",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 9:
			{
				ApplyAnimation(playerid,  "FOOD",  "SHP_Tray_Lift_Out",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 10:
			{
				ApplyAnimation(playerid,  "FOOD",  "SHP_Tray_Out",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 11:
			{
				ApplyAnimation(playerid,  "GANGS",  "hndshkca",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 12:
			{
				ApplyAnimation(playerid,  "GANGS",  "hndshkda",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 13:
			{
				ApplyAnimation(playerid,  "GANGS",  "hndshkea",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 14:
			{
				ApplyAnimation(playerid,  "GANGS",  "leanIN",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 15:
			{
				ApplyAnimation(playerid,  "OTB",  "wtchrace_lose",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 16:
			{
				ApplyAnimation(playerid,  "COP_AMBIENT",  "Copbrowse_shake",  4.1,  0,  1,  1,  1,  1, 1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 17:
			{
				ApplyAnimation(playerid,  "CRACK",  "crckidle1",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 18:
			{
				ApplyAnimation(playerid,  "CRACK",  "crckidle2",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 19:
			{
				ApplyAnimation(playerid,  "JST_BUISNESS",  "girl_02",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 20:
			{
				ApplyAnimation(playerid,  "DAM_JUMP",  "DAM_Dive_Loop",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 21:
			{
				ApplyAnimation(playerid,  "DEALER",  "DEALER_IDLE",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 22:
			{
				ApplyAnimation(playerid,  "TATTOOS",  "TAT_ArmL_Out_T",  4.1,  0,  1,  1,  1,  1,  1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 23:
			{
				ApplyAnimation(playerid, "BEACH", "Lay_Bac_Loop", 4.1, 0, 1, 1, 1, 1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 24:
			{
				ApplyAnimation(playerid,  "DEALER",  "DRUGS_BUY",  4.1,  1,  1,  1,  1,  1 , 1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 25:
			{
				ApplyAnimation(playerid,  "RYDER",  "RYD_Die_PT1",  4.1,  1,  1,  1,  1,  1 , 1);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			case 26:
			{
				callcmd::piss(playerid);
				PlayerPlaySound(playerid,  1058,  0.0,  0.0,  0.0);
			}
			default: return 1;
		}
	}
	return 1;
}