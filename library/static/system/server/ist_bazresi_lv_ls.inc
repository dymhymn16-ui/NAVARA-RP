#define DOOR_STAT_CLOSE 0
#define DOOR_STAT_OPEN 1

new IstBazresiLVLS_Barrier[8];
new IstBazresiLVLS_Stat[sizeof IstBazresiLVLS_Barrier];

static RotateDynamicObject(objectid, Float:rotX, Float:rotY, Float:rotZ, Float:Speed)
{
    new Float:X, Float:Y, Float:Z, Float:SpeedConverted = floatmul(Speed, 0.01);
    GetDynamicObjectPos(objectid, X, Y, Z);
    SetDynamicObjectPos(objectid, X, Y, floatadd(Z, 0.001));
    MoveDynamicObject(objectid, X, Y, floatsub(Z, 0.001), SpeedConverted, rotX, rotY, rotZ);
    return 1;
}

IstBazresiLVLS_Check(playerid)
{
	/* New Avarezi = Ist_Bazresi.pwn */
    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1732.2866, 457.7748, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[0] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[0], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[0] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                0);
        }
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1723.9841, 460.6049, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[1] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[1], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[1] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                1);
        }
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1739.6388, 478.1668, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[2] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[2], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[2] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                2);
        }
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1731.0725, 480.9371, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[3] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[3], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[3] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                3);
        }
        return 1;
    }

    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1714.5151, 495.4459, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[4] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[4], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[4] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                4);
        }
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1723.1865, 492.1856, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[5] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[5], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[5] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                5);
        }
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1707.2780, 476.0080, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[6] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[6], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[6] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                6);
        }
        return 1;
    }
    if(IsPlayerInRangeOfPoint(playerid, 6.0, 1715.9949, 472.1426, 30.6760)) {
            
        if(IstBazresiLVLS_Stat[7] == DOOR_STAT_CLOSE) {
            give_money(playerid, -500);
            PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
            
            RotateDynamicObject(IstBazresiLVLS_Barrier[7], 0.0, 20.0000, -18.84001, 0.7);
            
            IstBazresiLVLS_Stat[7] = DOOR_STAT_OPEN;
            SetTimerEx("IstBazresiLVLSGateClose", 3000, false, "d", 
                7);
        }
        return 1;
    }
    return 1;
}

forward IstBazresiLVLSGateClose(istId);
public IstBazresiLVLSGateClose(istId)
{
    RotateDynamicObject(IstBazresiLVLS_Barrier[istId], 0.0, 90.0000, -18.84001, 0.7);   
    IstBazresiLVLS_Stat[istId] = DOOR_STAT_CLOSE;
}