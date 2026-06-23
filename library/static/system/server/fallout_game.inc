#define MAX_OBJECT_SLOTS        54
#define MAX_OBJECT_SLOTS2       96
#define PLAYERS_FOR_REAL_START  2
#define FALLOUT_EVENT_INT       0
#define FALLOUT_EVENT_VW        26

#define FALL_EXP_RANDOM         2
#define MIN_REWARD_FALL         20000
#define MAX_REWARD_FALL         30000

#define FALLOUT_USE_STREAMER_TYPE_0 true
#define FALLOUT_USE_STREAMER_TYPE_1 false
//========================================================//

static Fallout_Started;
static bool:Fallout_RealStart;
static Fallout_CountDown;
static FallEvent_CDown_Timer = -1;
static FE_Set_Objects_Timer = -1;
static bool:Fallout_Player[MAX_PLAYERS];
static Fallout_Type;
static FE_StartTimeEx;

//========================================================//

static Objects_slot[MAX_OBJECT_SLOTS][2];
static Float:FallOutObject_Coords[MAX_OBJECT_SLOTS][3] =
{
	{-5309.198120,-199.052383,22.593704},
	{-5309.198120,-195.786071,22.593704},
	{-5309.198120,-192.510620,22.593704},
	{-5309.198120,-189.250564,22.593704},
	{-5309.198120,-185.987960,22.593704},
	{-5309.198120,-182.727081,22.593704},
	{-5309.198120,-179.463394,22.593704},
	{-5309.198120,-176.205261,22.593704},
	{-5304.841796,-176.205261,22.593704},
	{-5304.841796,-179.468795,22.593704},
	{-5304.841796,-182.737884,22.593704},
	{-5304.841796,-185.989654,22.593704},
	{-5304.841796,-189.259185,22.593704},
	{-5304.841796,-192.518615,22.593704},
	{-5304.841796,-195.785491,22.593704},
	{-5304.841796,-199.054733,22.593704},
	{-5300.489990,-199.054733,22.593704},
	{-5300.489990,-195.782165,22.593704},
	{-5300.489990,-192.531250,22.593704},
	{-5300.489990,-189.274765,22.593704},
	{-5300.489990,-186.003005,22.593704},
	{-5300.489990,-182.735229,22.593704},
	{-5300.489990,-179.471069,22.593704},
	{-5300.489990,-176.208007,22.593704},
	{-5296.138061,-176.208007,22.593704},
	{-5296.138061,-179.479248,22.593704},
	{-5296.138061,-182.744735,22.593704},
	{-5296.138061,-186.002944,22.593704},
	{-5296.138061,-189.274505,22.593704},
	{-5296.138061,-192.533691,22.593704},
	{-5296.138061,-195.788970,22.593704},
	{-5296.138061,-199.048782,22.593704},
	{-5291.776000,-199.050140,22.593704},
	{-5291.776000,-195.790634,22.593704},
	{-5291.776000,-192.542922,22.593704},
	{-5291.776000,-189.277542,22.593704},
	{-5291.776000,-186.013275,22.593704},
	{-5291.776000,-182.742355,22.593704},
	{-5291.776000,-179.475021,22.593704},
	{-5291.776000,-176.215805,22.593704},
	{-5287.432250,-176.215805,22.593704},
	{-5287.432250,-179.485168,22.593704},
	{-5287.432250,-182.739608,22.593704},
	{-5287.432250,-186.016723,22.593704},
	{-5287.432250,-189.277816,22.593704},
	{-5287.432250,-192.539001,22.593704},
	{-5287.432250,-195.796325,22.593704},
	{-5287.432250,-199.053771,22.593704},
	{-5287.431274,-202.320648,22.593704},
	{-5291.781616,-202.320648,22.593704},
	{-5296.136718,-202.320648,22.593704},
	{-5300.493652,-202.320648,22.593704},
	{-5304.848876,-202.320648,22.593704},
	{-5309.201660,-202.320648,22.593704}
};

static RandomPos_Order;
static Float:RandomPos[][] =
{
    {-5291.2603,-199.5996,23.5937,41.3230},
    {-5308.7949,-198.8641,23.5937,301.8505},
    {-5309.7075,-176.0661,23.5937,239.0382},
    {-5300.5713,-202.5533,23.5937,356.2026},
    {-5296.4048,-179.7707,23.5937,175.5759},
    {-5287.3618,-176.1624,23.5937,180.1077},
    {-5287.3193,-192.6549,23.5937,88.9268},
    {-5308.9888,-189.2918,23.5937,271.1435},
    {-5304.8145,-182.7990,23.5937,180.0350},
    {-5300.7739,-195.6152,23.5937,359.0950},
    {-5296.1421,-185.7987,23.5937,180.1309},
    {-5287.8804,-182.6468,23.5937,85.3584},
    {-5296.0698,-192.5185,23.5937,357.6967},
    {-5304.6455,-192.4807,23.5937,357.4067},
    {-5309.5352,-186.0845,23.5937,269.7685},
    {-5300.4175,-176.6228,23.5937,177.8160},
    {-5300.4229,-189.1709,23.5937,351.0676},
    {-5287.7500,-188.5175,23.5937,87.5752},
    {-5287.4561,-202.1432,23.5937,359.9861},
    {-5296.2715,-199.2682,23.5937,357.7927}
};
new Iterator:Fallout_Objects<MAX_OBJECT_SLOTS>;

//---------------------------------------------

static Objects_slot2[MAX_OBJECT_SLOTS2][1];
static Float:FallOutObject_Coords2[MAX_OBJECT_SLOTS2][3] =
{
    {-6225.045898, -344.455596, 219.241500},
    {-6217.047851, -332.447814, 219.241500},
    {-6241.027343, -336.471649, 219.241500},
    {-6213.037109, -340.435028, 219.241500},
    {-6237.010742, -348.471496, 219.241500},
    {-6241.030761, -352.481445, 219.241500},
    {-6241.020996, -332.465545, 219.241500},
    {-6233.025878, -336.455993, 219.241500},
    {-6233.032714, -332.460205, 219.241500},
    {-6229.037109, -332.450408, 219.241500},
    {-6225.041992, -332.452117, 219.241500},
    {-6221.044433, -332.449188, 219.241500},
    {-6205.065429, -332.441192, 219.241500},
    {-6213.055664, -332.445312, 219.241500},
    {-6209.061523, -332.441375, 219.241500},
    {-6201.068847, -332.441131, 219.241500},
    {-6197.079589, -332.440032, 219.241500},
    {-6237.027343, -332.460998, 219.241500},
    {-6237.023437, -336.466369, 219.241500},
    {-6229.031738, -336.452880, 219.241500},
    {-6225.039550, -336.449310, 219.241500},
    {-6221.039062, -336.448181, 219.241500},
    {-6197.080566, -336.428192, 219.241500},
    {-6217.040039, -336.442413, 219.241500},
    {-6213.039062, -336.444183, 219.241500},
    {-6209.046875, -336.439880, 219.241500},
    {-6205.054199, -336.440063, 219.241500},
    {-6201.062011, -336.429687, 219.241500},
    {-6241.021484, -340.466827, 219.241500},
    {-6237.023925, -340.461761, 219.241500},
    {-6233.026855, -340.452697, 219.241500},
    {-6229.026367, -340.455383, 219.241500},
    {-6225.026367, -340.453826, 219.241500},
    {-6221.027343, -340.443725, 219.241500},
    {-6217.034667, -340.440032, 219.241500},
    {-6197.090820, -340.417083, 219.241500},
    {-6209.036621, -340.426879, 219.241500},
    {-6205.040039, -340.420166, 219.241500},
    {-6201.046386, -340.417083, 219.241500},
    {-6241.024414, -344.466674, 219.241500},
    {-6237.030761, -344.461669, 219.241500},
    {-6233.042968, -344.457946, 219.241500},
    {-6229.042480, -344.455932, 219.241500},
    {-6221.054199, -344.443237, 219.241500},
    {-6197.094238, -344.416229, 219.241500},
    {-6217.054199, -344.439117, 219.241500},
    {-6213.063964, -344.433532, 219.241500},
    {-6209.058593, -344.429809, 219.241500},
    {-6205.054199, -344.425720, 219.241500},
    {-6201.059570, -344.420410, 219.241500},
    {-6241.015625, -348.475891, 219.241500},
    {-6233.010253, -348.461456, 219.241500},
    {-6229.011230, -348.456634, 219.241500},
    {-6225.010742, -348.455841, 219.241500},
    {-6221.018066, -348.446655, 219.241500},
    {-6217.030761, -348.444641, 219.241500},
    {-6213.042968, -348.432281, 219.241500},
    {-6209.049316, -348.432159, 219.241500},
    {-6205.045898, -348.426818, 219.241500},
    {-6201.045410, -348.424896, 219.241500},
    {-6197.094726, -348.412353, 219.241500},
    {-6237.031738, -352.472167, 219.241500},
    {-6233.030761, -352.463073, 219.241500},
    {-6229.036621, -352.467437, 219.241500},
    {-6225.033691, -352.459564, 219.241500},
    {-6221.034667, -352.453491, 219.241500},
    {-6217.037597, -352.439971, 219.241500},
    {-6213.041503, -352.433410, 219.241500},
    {-6209.046875, -352.434478, 219.241500},
    {-6205.048339, -352.432067, 219.241500},
    {-6201.057617, -352.420959, 219.241500},
    {-6197.095703, -352.409790, 219.241500},
    {-6241.028320, -356.477539, 219.241500},
    {-6241.023925, -360.471527, 219.241500},
    {-6237.029296, -356.478118, 219.241500},
    {-6233.032226, -356.476989, 219.241500},
    {-6229.032714, -356.474304, 219.241500},
    {-6225.040039, -356.457092, 219.241500},
    {-6221.045898, -356.452087, 219.241500},
    {-6217.049804, -356.446228, 219.241500},
    {-6213.050781, -356.435211, 219.241500},
    {-6209.046875, -356.438323, 219.241500},
    {-6205.043945, -356.438781, 219.241500},
    {-6201.049804, -356.414672, 219.241500},
    {-6197.087890, -356.413146, 219.241500},
    {-6237.020996, -360.468231, 219.241500},
    {-6233.023925, -360.477661, 219.241500},
    {-6229.027832, -360.473754, 219.241500},
    {-6225.025390, -360.466430, 219.241500},
    {-6221.029296, -360.455993, 219.241500},
    {-6217.025390, -360.449859, 219.241500},
    {-6213.028320, -360.438446, 219.241500},
    {-6209.036621, -360.431671, 219.241500},
    {-6205.042968, -360.428619, 219.241500},
    {-6201.047851, -360.426605, 219.241500},
    {-6197.082031, -360.409393, 219.241500}

};

new Iterator:FE_Player<MAX_PLAYERS>;
static RandomPos_Order2;
static Float:RandomPos2[][] =
{
    {-6240.106445, -360.593444, 221.747528, 93.005577},
    {-6227.013671, -356.394195, 221.747528, 236.876144},
    {-6240.950195, -344.309295, 221.747528, 69.409500},
    {-6235.064453, -336.241729, 221.747528, 261.533630},
    {-6223.256347, -348.313934, 221.747528, 270.307006},
    {-6215.216796, -360.165008, 221.747528, 354.426055},
    {-6232.684570, -348.584808, 221.747528, 92.018630},
    {-6226.890136, -333.003204, 221.747528, 178.667770},
    {-6227.029785, -340.148956, 221.747528, 180.088485},
    {-6219.210449, -336.386505, 221.747528, 176.883712},
    {-6215.175781, -332.198547, 221.747528, 179.149566},
    {-6202.977539, -332.235900, 221.747528, 177.582885},
    {-6214.953613, -340.580566, 221.747528, 86.088668},
    {-6219.277343, -356.400482, 221.747528, 358.209533},
    {-6210.854980, -356.487518, 221.747528, 356.715332},
    {-6217.025878, -348.535156, 221.747528, 267.992095},
    {-6222.986328, -340.272583, 221.747528, 271.270385},
    {-6211.296875, -347.993591, 221.747528, 234.610076},
    {-6203.024414, -352.373504, 221.747528, 264.136230},
    {-6203.121093, -360.620330, 221.747528, 38.148227},
    {-6207.013183, -336.448852, 221.747528, 181.005813},
    {-6198.887207, -340.325927, 221.747528, 89.752769},
    {-6199.245605, -348.465545, 221.747528, 88.885276},
    {-6207.019531, -344.398345, 221.747528, 93.031196},
    {-6210.346191, -340.553588, 221.747528, 177.606231},
    {-6197.223632, -332.645446, 221.747528, 135.474182},
    {-6196.546386, -356.494873, 221.747528, 88.305397},
    {-6214.745605, -351.766784, 221.747528, 87.678718},
    {-6240.192382, -351.198974, 221.747528, 280.670440},
    {-6233.046875, -357.548980, 221.747528, 342.710998},
    {-6232.804687, -342.689422, 221.747528, 233.646682}
};

//========================================================//

FalloutGameInit()
{
    Fallout_Started = 0;
    Fallout_RealStart = false;
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    Fallout_Player[playerid] = false;

    #if defined FalloutGame_OnPlayerDisconnect
        return FalloutGame_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect FalloutGame_OnPlayerDisconnect
#if defined FalloutGame_OnPlayerDisconnect
    forward FalloutGame_OnPlayerDisconnect(playerid, reason);
#endif

FalloutGame_PlayerTakeDamage(playerid)
{
	if (Fallout_Started == 1)
	{
    	if (Fallout_Player[playerid] == true)
    	{
        	set_health(playerid, 100.0);
        	set_armour(playerid, 100.0);
    	}
	}
	return 1;
}

FalloutGame_PlayerDeath(playerid, killerid)
{
    if (Fallout_Player[playerid] == true)
    {
        Fallout_Player[playerid] = false;
        if (killerid != INVALID_PLAYER_ID)
        {
            ResetPlayer_FalloutEvent(killerid);
            SendClientMessage(killerid, col_gray, "Be Dalil Koshtane Bazikon Dar Fallout Az Event Kick Shodid.");
        }
    }
    return 1;
}

FalloutGame_PlayerSpawn(playerid)
{
    if (Fallout_Player[playerid] == true)
    {
        Fallout_Player[playerid] = false;
    }
}

//========================================================//

CMD:fall(playerid)
{
	if (Fallout_Started == 0) return SendClientMessage(playerid, -1, "Event Fallout Start Nashode.");
    if (IsPlayerInColorMatchEvent(playerid)) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Shoma Dar Event ColorMatch Hastid!");
    if (Fallout_Player[playerid] == true) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Shoma Dar Event Fallout Hastid!");
	if (isPlayerInJail(playerid)) return SendClientMessage(playerid,col_gray,""c_orange_red"* "c_grey"Shoma Dar Jail Hastid.");
    if (GetPVarInt(playerid, "PlayerCuffed")) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Shoma cuff hastid.");
    if (GetPVarInt(playerid, "PlayerTied")) return SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"You are tied.");
	if (Fallout_Started == 1 && Fallout_RealStart == true) return SendClientMessage(playerid, col_red, "Event Fallout Shoroo Shode Ast!");

    if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
    {
        RemovePlayerFromVehicle(playerid);
    }
    
    me_action(playerid, "Ba /fall Raft Mosabeghe!");
    
    JoinPlayer_FalloutEvent(playerid);
    return 1;
}

CMD:startfall(playerid, params[])
{
    if (PlayerInfo[playerid][admin] < 5) return 1; // Optional

	if (Fallout_Started != 0) return SendClientMessage(playerid, col_red, "Event Fallout Ijad Shode.");

	if (PlayerInfo[playerid][admin] >= 5)
	{
        Create_FalloutEvent();
	}
	else
	{
        if (PlayerInfo[playerid][money] < 10_000) {
            SendClientMessage(playerid, col_gray,""c_orange_red"* "c_grey"Shoma $10,000 Pool Baraye Start Fallout Event Nadarid.");
            return 1;
        }
        give_money(playerid, -10_000);
        
        Create_FalloutEvent();
    }

	new string[144];
	format(string, sizeof(string), "{6EF83C}[Start Fallout Event] %s(%i) Event Fallout Start Kard. Join Ba: (/fall)", Name(playerid), playerid);
	SendClientMessageToAll(-1, string);
	return 1;
}

CMD:exitf(playerid)
{
    if (Fallout_Player[playerid] == false) return SendClientMessage(playerid, col_red, "Shoma Dar Event Fallout Nistid.");
    ResetPlayer_FalloutEvent(playerid);
	return 1;
}

CommandExitForFallout(playerid)
{
    if (Fallout_Player[playerid] == true)
    {
        ResetPlayer_FalloutEvent(playerid);
        return 1;
    }
    return 0;
}

//========================================================//

forward FallEvent_StartTime();
public FallEvent_StartTime()
{
	if (FE_StartTimeEx == 0)
	{
    Fallout_CountDown--;
	switch(Fallout_CountDown)
	{
	   case 30,20:
	   {
		  new string[144];
 		  format(string, sizeof(string), ">> {FF0000}Shoroe Fallout Event Ta %i Sanie. {FFF8DC}Join Ba /fall", Fallout_CountDown);
          SendClientMessageToAll(0xFFF8DCAA, string);
       }

	   case 1..9:
	   {
	      new string[10];
          if (Fallout_CountDown >= 1)
		  {
            foreach(new i : Player)
            {
              if (Fallout_Player[i] == true)
              {
		         format(string, sizeof string, "~y~%i", Fallout_CountDown);
		         GameTextForPlayer(i, string, 1050, 3);
		         PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0);
              }
	        }
	      }

          if (Fallout_CountDown == 4) //Event Shoroo Shode Ast..
          {
            Fallout_Started = 1;
            Fallout_RealStart = true;
          }
       }

 	   case 0:
	   {
          foreach(new i : Player)
          {
             if (Fallout_Player[i] == true)
             {
		        GameTextForPlayer(i, "~p~~h~GO", 1050, 3);
		        PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
		     }
		  }
		  FallEvent_Start();
		  KillTimer(FallEvent_CDown_Timer);
		  Fallout_CountDown = -1;
		  if (Fallout_Type == 1)
		  {
		      FE_StartTimeEx = 1;
		      FallEvent_CDown_Timer = SetTimer("FallEvent_StartTime", 13000, true);
		  }
	   }
    }
    } else if (FE_StartTimeEx == 1)
    {
	   if (Fallout_Type == 1)
       {
		  if (CountFalloutPlayers() >= PLAYERS_FOR_REAL_START)
		  {
          new rand[2];
          rand[0] = Iter_Random(FE_Player);
          GivePlayerWeapon(rand[0], 23, 3);
          PlayerPlaySound(rand[0], 1139, 0.0, 0.0, 0.0);
          
          rand[1] = Iter_Random(FE_Player);
          if (rand[1] == rand[0])
          {
          for(new w; w <= 3; w++)
          {
              rand[1] = Iter_Random(FE_Player);
          }
          }
          GivePlayerWeapon(rand[1], 23, 3);
          PlayerPlaySound(rand[1], 1139, 0.0, 0.0, 0.0);
          } else
		  {
		  if (FallEvent_CDown_Timer != -1)
		  {
		  KillTimer(FallEvent_CDown_Timer);
		  FallEvent_CDown_Timer = -1;
		  }
          }
	   }
    }
	return 1;
}

//========================================================//

forward FallEvent_Start();
public FallEvent_Start()
{
	if (CountFalloutPlayers() >= PLAYERS_FOR_REAL_START)
	{
      foreach(new i : Player)
      {
        if (Fallout_Player[i] == true)
        {
           SetCameraBehindPlayer(i);
           TogglePlayerControllable(i, true);
	       ResetPlayerWeapons(i);
	       if(Fallout_Type == 1) GivePlayerWeapon(i, 1, 1);
        }
      }
   	  if (Fallout_Type == 0)
   	  {
   	  if (FE_Set_Objects_Timer != -1)
   	  {
   	  KillTimer(FE_Set_Objects_Timer);
   	  FE_Set_Objects_Timer = -1;
   	  }
      FE_Set_Objects_Timer = SetTimer("FallEvent_Set_Objects", 2000, true);
      }
      Fallout_Started = 1;
      Fallout_RealStart = true;
	}
	else
	{
	  Reset_FalloutEvent();
	}
	return 1;
}

//========================================================//

forward FallEvent_Set_Objects();
public FallEvent_Set_Objects()
{
    if (Fallout_Type == 0)
    {
        new rand = Iter_Random(Fallout_Objects), Float:ObjectPos[3];

        #if !FALLOUT_USE_STREAMER_TYPE_0
            if (((random(10)) & 0x01))
            {
                GetObjectPos(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
                MoveObject(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]-1.5, 0.2); // -
                MoveObject(Objects_slot[rand][1], ObjectPos[0], ObjectPos[1], ObjectPos[2]-1.5, 0.2);
            }
            else
            {
                GetObjectPos(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
                MoveObject(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]+1.5, 0.2); // +
                MoveObject(Objects_slot[rand][1], ObjectPos[0], ObjectPos[1], ObjectPos[2]+1.5, 0.2);
            }

            GetObjectPos(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
            MoveObject(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]-5, 1);
            MoveObject(Objects_slot[rand][1], ObjectPos[0], ObjectPos[1], ObjectPos[2]-5, 1);
        #else
            if (((random(10)) & 0x01))
            {
                GetDynamicObjectPos(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
                MoveDynamicObject(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]-1.5, 0.2); // -
                MoveDynamicObject(Objects_slot[rand][1], ObjectPos[0], ObjectPos[1], ObjectPos[2]-1.5, 0.2);
            }
            else
            {
                GetDynamicObjectPos(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
                MoveDynamicObject(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]+1.5, 0.2); // +
                MoveDynamicObject(Objects_slot[rand][1], ObjectPos[0], ObjectPos[1], ObjectPos[2]+1.5, 0.2);
            }

            GetDynamicObjectPos(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
            MoveDynamicObject(Objects_slot[rand][0], ObjectPos[0], ObjectPos[1], ObjectPos[2]-5, 1);
            MoveDynamicObject(Objects_slot[rand][1], ObjectPos[0], ObjectPos[1], ObjectPos[2]-5, 1);
        #endif
        SetTimerEx("SpeedUpObject", 900, false, "iifff", Objects_slot[rand][0], Objects_slot[rand][1], ObjectPos[0], ObjectPos[1], ObjectPos[2]);
    }
    return 1;
}

//========================================================//

forward SpeedUpObject(objectid, objectid_2, Float:x, Float:y, Float:z);
public SpeedUpObject(objectid, objectid_2, Float:x, Float:y, Float:z)
{
    if (Fallout_Type == 0)
	{
    StopObject(objectid);
	MoveObject(objectid, x, y, z-150, 20);
	MoveObject(objectid_2, x, y, z-150, 20);
	Iter_Remove(Fallout_Objects, objectid);
    foreach(new i : Player)
	{
       if (Fallout_Player[i] == true) PlayerPlaySound(i, 1039, x, y, z);
	}
	}
	return 1;
}

//========================================================//

forward FallEvent_Update_player(i);
public FallEvent_Update_player(i)
{
    if (Fallout_RealStart == true)
    {
    if (Fallout_Player[i] == true)
	{
		new Float:z;
		GetPlayerPos(i, z, z, z);
		if (Fallout_Type == 0)
		{
		
		if (!IsPlayerInRangeOfPoint(i, 40, -5298.3423, -190.7533, 23.5937) || z < 17.6 || pl_afk_time[i] > 2)
		{
            ResetPlayer_FalloutEvent(i);
		}
        if (GetPlayerWeapon(i) != 0)
		{
		    ResetPlayerWeapons(i);
		}

		} else if (Fallout_Type == 1)
		{
            if (GetPlayerWeapon(i) == 0 || GetPlayerWeapon(i) == WEAPON_SNIPER)
            {
			    ResetPlayerWeapons(i);
			    GivePlayerWeapon(i, 1, 1);
			}
		    if (!IsPlayerInRangeOfPoint(i, 45.0, -6219.8071,-346.9035,221.7475) || z < 24 || pl_afk_time[i] > 2)
	    	{
                ResetPlayer_FalloutEvent(i);
		    }
		}
		
		if (GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK)
		{
            ResetPlayer_FalloutEvent(i);
            SetPlayerSpecialAction(i, SPECIAL_ACTION_USEJETPACK);
            SendClientMessage(i, 0xBDBDBDFF, "Be Dalil Estefade Az Jetpack Dar Fallout, Az Event Kick Shodid.");
		}
		
	}
	}
}

//========================================================//

forward Create_FalloutEvent();
public Create_FalloutEvent()
{
    if (Fallout_Started != 1)
    {
		if (Fallout_Type < 0 || Fallout_Type > 1) //if 'Fallout_Type' number bugged
		{
		   Fallout_Type = 1;
		}
		
		if (Fallout_Type == 1)
		{
	    Fallout_Type = 0;
	    for(new i; i < MAX_OBJECT_SLOTS; i++)
		{
           if (Objects_slot[i][0] == 0) continue;
           #if !FALLOUT_USE_STREAMER_TYPE_0
           DestroyObject(Objects_slot[i][0]);
           DestroyObject(Objects_slot[i][1]);
           #else
           DestroyDynamicObject(Objects_slot[i][0]);
           DestroyDynamicObject(Objects_slot[i][1]);
           #endif
           Objects_slot[i][0] = 0;
           Objects_slot[i][1] = 0;
	    }
	    Iter_Clear(Fallout_Objects);
	    for(new i; i < MAX_OBJECT_SLOTS; i++)
		{
           #if !FALLOUT_USE_STREAMER_TYPE_0
           Objects_slot[i][0] = CreateObject(1649, FallOutObject_Coords[i][0], FallOutObject_Coords[i][1], FallOutObject_Coords[i][2], -90.0, 0.0, 0.0);
           Objects_slot[i][1] = CreateObject(1649, FallOutObject_Coords[i][0], FallOutObject_Coords[i][1], FallOutObject_Coords[i][2], 90.0, 0.0, 0.0);
           #else
           Objects_slot[i][0] = CreateDynamicObject(1649, FallOutObject_Coords[i][0], FallOutObject_Coords[i][1], FallOutObject_Coords[i][2], -90.0, 0.0, 0.0);
           Objects_slot[i][1] = CreateDynamicObject(1649, FallOutObject_Coords[i][0], FallOutObject_Coords[i][1], FallOutObject_Coords[i][2], 90.0, 0.0, 0.0);
           #endif
	       Iter_Add(Fallout_Objects, i);
	    }
	    } else if (Fallout_Type == 0)
		{
	    Fallout_Type = 1;
        Iter_Clear(FE_Player);
	    for(new i; i < MAX_OBJECT_SLOTS2; i++)
		{
            if (Objects_slot2[i][0] == 0) continue;
            #if !FALLOUT_USE_STREAMER_TYPE_1
            DestroyObject(Objects_slot2[i][0]);
            #else
            DestroyDynamicObject(Objects_slot2[i][0]);
            #endif
            Objects_slot2[i][0] = 0;
	    }
	    for(new i; i < MAX_OBJECT_SLOTS2; i++)
		{
            #if !FALLOUT_USE_STREAMER_TYPE_1
            Objects_slot2[i][0] = CreateObject(3374, FallOutObject_Coords2[i][0], FallOutObject_Coords2[i][1], FallOutObject_Coords2[i][2], 0.0, 0.0, 90.0);
            #else
            Objects_slot2[i][0] = CreateDynamicObject(3374, FallOutObject_Coords2[i][0], FallOutObject_Coords2[i][1], FallOutObject_Coords2[i][2], 0.0, 0.0, 90.0);
            #endif
	    }
	    }
  	    Fallout_CountDown = 31;
	    Fallout_Started = 1;
	    FE_StartTimeEx = 0;
	    FallEvent_CDown_Timer = SetTimer("FallEvent_StartTime", 1000, true);
	}
    return 1;
}

//========================================================//

stock Reset_FalloutEvent()
{
    Fallout_Started = 0;
    Fallout_RealStart = false;

    foreach(new i : Player)
    {
      if (Fallout_Player[i] == true)
      {
         Fallout_Player[i] = false;
		 ResetPlayerWeapons(i);
         SetCameraBehindPlayer(i);
         texture_load_mode(i, 2000);
         SetPlayerInterior(i, GetPVarInt(i,"Last_Pos_INT"));
	     SetPlayerVirtualWorld(i, GetPVarInt(i,"Last_Pos_VW"));
	     SetPlayerPos(i, GetPVarFloat(i,"Last_Pos_X"), GetPVarFloat(i,"Last_Pos_Y"), GetPVarFloat(i,"Last_Pos_Z"));
	     give_player_save_weapon(i);
	   }
    }
    return 1;
}

//========================================================//

stock GlobalReset_FalloutEvent()
{
    if (Fallout_RealStart == true)
    {
       if (CountFalloutPlayers() == 1 && Fallout_CountDown == -1)
  	   {
       new string[144];
       ResetGFalloutEvent();
       new cash_rand = RandomEx(MIN_REWARD_FALL, MAX_REWARD_FALL);
       new exp_rand = random(FALL_EXP_RANDOM);
       foreach(new i : Player)
       {
          if (Fallout_Player[i] == true)
          {
             if (exp_rand >= 1)
             {
                format(string, sizeof(string), "[Fallout Event] {088A85}%s(%i) {04B4AE}Dar Event Aval Va Barande {088A85}$%s {04B4AE}Shod.[+%i EXP]", Name(i), i, Comma(cash_rand), exp_rand);
                give_exp(i, exp_rand, true);
		 	 }
             else
             {
                format(string, sizeof(string), "[Fallout Event] {088A85}%s(%i) {04B4AE}Dar Event Aval Va Barande {088A85}$%s {04B4AE}Shod.", Name(i), i, Comma(cash_rand));
             }
             SendClientMessageToAll(0x04B4AEFF, string);

		 	 My_GiveCash(i, cash_rand);
             ResetPlayer_FalloutEvent(i);
             if (FE_Set_Objects_Timer != -1)
             {
             KillTimer(FE_Set_Objects_Timer);
             FE_Set_Objects_Timer = -1;
             }
             if (FallEvent_CDown_Timer != -1)
             {
             KillTimer(FallEvent_CDown_Timer);
             FallEvent_CDown_Timer = -1;
             }
	      }
	   }
	   } else if (CountFalloutPlayers() == 0)
   	   {
   	      ResetGFalloutEvent();
   	   }
    }
    return 1;
}

//========================================================//

stock ResetGFalloutEvent()
{
    Fallout_Started = 0;
    Fallout_RealStart = false;
    if (FE_Set_Objects_Timer != -1)
    {
    KillTimer(FE_Set_Objects_Timer);
    FE_Set_Objects_Timer = -1;
    }
    if (FallEvent_CDown_Timer != -1)
    {
    KillTimer(FallEvent_CDown_Timer);
    FallEvent_CDown_Timer = -1;
    }
    if (Fallout_Type == 1)
    {
       Iter_Clear(FE_Player);
    }
    return 1;
}

//========================================================//

stock JoinPlayer_FalloutEvent(playerid)
{
	if (Fallout_Player[playerid] == false)
	{

    SetPVarInt(playerid, "Last_Pos_INT", GetPlayerInterior(playerid));
    SetPVarInt(playerid, "Last_Pos_VW", GetPlayerVirtualWorld(playerid));
    new Float:PlayerPos[3];
    GetPlayerPos(playerid, PlayerPos[0], PlayerPos[1], PlayerPos[2]);
    SetPVarFloat(playerid, "Last_Pos_X", PlayerPos[0]),SetPVarFloat(playerid, "Last_Pos_Y", PlayerPos[1]),SetPVarFloat(playerid, "Last_Pos_Z", PlayerPos[2]);

    SetPlayerInterior(playerid, FALLOUT_EVENT_INT);
    SetPlayerVirtualWorld(playerid, FALLOUT_EVENT_VW);
   	set_health(playerid, 100.0);
	set_armour(playerid, 100.0);
    Fallout_Player[playerid] = true;
    TogglePlayerControllable(playerid, false);

    ResetPlayerWeapons(playerid);
           
    if (Fallout_Type == 0)
    {
	RandomPos_Order++;
	if (RandomPos_Order >= sizeof(RandomPos))
	{
	     RandomPos_Order = 0;
	}

	SetPlayerPos(playerid, RandomPos[RandomPos_Order][0], RandomPos[RandomPos_Order][1], RandomPos[RandomPos_Order][2]);
	SetPlayerFacingAngle(playerid, RandomPos[RandomPos_Order][3]);
	SetPlayerCameraPos(playerid, -5298.4814,-218.4391,42.1386);
	SetPlayerCameraLookAt(playerid, -5298.1616,-189.6903,23.6564);
	} else if (Fallout_Type == 1)
	{
	RandomPos_Order2++;
	if (RandomPos_Order2 >= sizeof(RandomPos2))
	{
	     RandomPos_Order2 = 0;
	}
	Iter_Add(FE_Player, playerid);
	
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, 1, 1);

	SetPlayerPos(playerid, RandomPos2[RandomPos_Order2][0], RandomPos2[RandomPos_Order2][1], RandomPos2[RandomPos_Order2][2]);
	SetPlayerFacingAngle(playerid, RandomPos2[RandomPos_Order2][3]);
    SetPlayerCameraPos(playerid, -6260.0635, -346.4305, 244.0101);
    SetPlayerCameraLookAt(playerid, -6259.0654, -346.4243, 243.3152);
	}
	}
	return 1;
}

//========================================================//

stock ResetPlayer_FalloutEvent(playerid)
{
	if (Fallout_Player[playerid] == true)
	{

    Fallout_Player[playerid] = false;
    texture_load_mode(playerid, 2000);
    SetPlayerPos(playerid, GetPVarFloat(playerid,"Last_Pos_X"), GetPVarFloat(playerid,"Last_Pos_Y"), GetPVarFloat(playerid,"Last_Pos_Z"));
    SetPlayerInterior(playerid, GetPVarInt(playerid,"Last_Pos_INT"));
	SetPlayerVirtualWorld(playerid, GetPVarInt(playerid,"Last_Pos_VW"));
    SetCameraBehindPlayer(playerid);
    
    set_health(playerid, 100.0);
	set_armour(playerid, 100.0);
    
    give_player_save_weapon(playerid);
    
    if (Fallout_Type == 1)
    {
       Iter_Remove(FE_Player, playerid);
    }

    }
    return 1;
}

//========================================================//

stock CountFalloutPlayers()
{
    new count;
    foreach(new i : Player)
    {
       if (Fallout_Player[i] == true) count++;
	}
    return count;
}

//========================================================//

stock IsPlayerInFalloutGame(playerid) return Fallout_Player[playerid];