stock SendAutoMessage()
{
	if(!decreasedPropertiesDays) {
		if(timestamp_hour == 0 && timestamp_minute == 0)
		{
			decreasedPropertiesDays = true;
			new string[70];

			// house
			for(new h = 0; h < house_count; h ++)
			{
				if(h_info[h][h_owner] == -1) continue;

				h_info[h][h_days]--;
				if(h_info[h][h_days] <= 0) {
					SellHouse(h);
					continue;
				}
				else if(1 <= h_info[h][h_days] <= 2) {
					new h_owner_id = GetPlayerID(h_info[h][h_owner_name]);

					if(IsPlayerConnected(h_owner_id))
					{
						SendClientMessage(h_owner_id, col_light_red, "[Tavajoh] Khane Khod Ra Tamdid Konid.");
					}
				}

				format(string, sizeof string, "UPDATE `houses` SET `h_days`=%d WHERE `h_id`=%d", h_info[h][h_days], h_info[h][h_id]);
				mysql_tquery(sql_connection, string);
			}

			// bussines
			for(new b = 0; b < b_count; b ++)
			{
				if(b_info[b][b_owner_inc] == -1) continue;

				b_info[b][b_days]--;
				if(b_info[b][b_days] <= 0) {
					SellBussiness(b+1);
					continue;
				}
				else if(1 <= b_info[b][b_days] <= 2) {
					new b_owner = GetPlayerID(b_info[b][b_owner_name]);

					if(IsPlayerConnected(b_owner))
					{
						SendClientMessage(b_owner, col_light_red, "[Tavajoh] Business Khod Ra Tamdid Konid.");
					}
				}

				format(string, sizeof string, "UPDATE `businesses` SET `b_days`=%d WHERE `b_id`=%d", b_info[b][b_days], b_info[b][b_id]);
				mysql_tquery(sql_connection, string);
			}

			// Bans Day
			mysql_tquery(sql_connection, "UPDATE `users_bans` SET `u_b_days`=`u_b_days`-1 WHERE `u_b_days` > 0", "", "");

			// Activity Reset End Day
			foreach(new i: logged_players) {
				PlayerInfo[i][activity_jails] = 0;
				PlayerInfo[i][activity_killed_and_jails] = 0;
				PlayerInfo[i][activity_cuffs] = 0;
				PlayerInfo[i][activity_wanted_give_players] = 0;
				PlayerInfo[i][activity_frisk] = 0;
				PlayerInfo[i][activity_uncuff] = 0;
				PlayerInfo[i][activity_wanted_give_count] = 0;
				PlayerInfo[i][activity_unwanted] = 0;
				PlayerInfo[i][activity_take_drive_license] = 0;
				PlayerInfo[i][activity_take_gun_license] = 0;
				PlayerInfo[i][activity_take_materials] = 0;
				PlayerInfo[i][activity_take_drugs] = 0;
				PlayerInfo[i][activity_heals] = 0;
				PlayerInfo[i][activity_drug_heals] = 0;
				PlayerInfo[i][activity_give_heal_cart] = 0;
				PlayerInfo[i][activity_afrad_kick_shode] = 0;
				PlayerInfo[i][activity_give_free] = 0;
				PlayerInfo[i][activity_give_free_money] = 0;
				PlayerInfo[i][activity_taked_guns_faction] = 0;
			}
			mysql_tquery(sql_connection, "UPDATE `users` SET \
				`u_activity_jails` = 0, \
				`u_activity_killed_and_jails` = 0, \
				`u_activity_cuffs` = 0, \
				`u_activity_wanted_give_players` = 0, \
				`u_activity_frisk` = 0, \
				`u_activity_uncuff` = 0, \
				`u_activity_wanted_give_count` = 0, \
				`u_activity_unwanted` = 0, \
				`u_activity_take_drive_license` = 0, \
				`u_activity_take_gun_license` = 0, \
				`u_activity_take_materials` = 0, \
				`u_activity_take_drugs` = 0, \
				`u_activity_heals` = 0, \
				`u_activity_drug_heals` = 0, \
				`u_activity_give_heal_cart` = 0, \
				`u_activity_afrad_kick_shode` = 0, \
				`u_activity_give_free` = 0, \
				`u_activity_give_free_money` = 0, \
				`u_activity_taked_guns_faction` = 0 \
				");
			printf("[SERVER] Faction Activities Reseted");
		}
	}
	else
	{
		if(timestamp_hour == 0 && timestamp_minute == 2)
		{
			decreasedPropertiesDays = false;
		}
	}

	if(timestamp_minute == 0 && timestamp_second == 0 )
	{
		new text_math[250];
		new num1 = random(100);
		new num2 = random(100);

		moneyMath = 4500+(random(100)*random(100));

 		switch(random(2))
		{
			case 0:
			{
				mathResult = num1 - num2;
				format(text_math,sizeof(text_math), c_server"[Riazi]"c_white" Javab "c_yellow"%d - %d"c_white" Dakhel Chat Type Konid Va Jayeze Begirid.", num1, num2);
			}
			case 1:
			{
				mathResult = num1 + num2;
				format(text_math,sizeof(text_math), c_server"[Riazi]"c_white" Javab "c_yellow"%d + %d"c_white" Dakhel Chat Type Konid Va Jayeze Begirid.", num1, num2);
			}
			case 2:
			{
				mathResult = num1 * num2;
				format(text_math,sizeof(text_math), c_server"[Riazi]"c_white" Javab "c_yellow"%d * %d"c_white" Dakhel Chat Type Konid Va Jayeze Begirid.", num1, num2);
			}
		} 

 		foreach(new i: logged_players)
		{
			SendClientMessage(i, col_gray, text_math);
		}

		mathStatus = 1;
		SetTimer("clearMath", 10000, 0);
	}

	if(timestamp_minute == 7 && timestamp_second == 0 || timestamp_minute == 15 && timestamp_second == 0 || timestamp_minute == 20  && timestamp_second == 0 || timestamp_minute == 25  && timestamp_second == 0 || timestamp_minute == 30  && timestamp_second == 0 || timestamp_minute == 35  && timestamp_second == 0 || timestamp_minute == 40  && timestamp_second == 0 || timestamp_minute == 45  && timestamp_second == 0 || timestamp_minute == 50  && timestamp_second == 0 || timestamp_minute == 55  && timestamp_second == 0)
	{
		
 		foreach(new i: logged_players)
		{
			new text_help[300];

			switch(random(12))
			{
				case 0:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Poshtibani Telegram Server: "c_server"@MihanRPBot");
				}
				case 1:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Bug Peyda Kardi? Benevis "c_server"/report");
				}
				case 2:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Chanel Telegram Server: "c_green"@"c_white"Mihan"c_red"RP");
				}
				case 3:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Jahat Didan Leader Haye Online Bezan "c_server"/leaders");
				}
				case 4:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Ba Davat Kardan Doostan Khod Be Server Az Javayez Arzande Bahremand Shavid!");
				}
				case 5:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Dost Dari Bedoni Chand Nafaro Be Server Davat Kardi? Benevis "c_server"/referral");
				}
				case 6:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Aya Midonestid Ba Raftan Be Casino Mitavanid Pool Khod Ra Chand Barabar Konid? : /gps > Beghiye Mavared > Casino");
				}
				case 7:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Donbal Kar Migardi? Benevis "c_server"/jobs");
				}
				case 8:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Mikhay Tablo Tablighati Bekhari Vali Nemidoni Chetori? : /gps > 3 > 10");
				}
				case 9:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Be Komak Lazem Dari? Benevis "c_server"/helpme");
				}
				case 10:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Admin Ha Hichvaght Ramz Account Shoma Ra Nemiporsand.");
				}
				case 11:
				{
					format(text_help,sizeof(text_help), ""c_yellow"» "c_white"Cheater Didi? Benevis "c_server"/report");
				}
			}
			SendClientMessage(i, col_white, text_help);
		}
	}

	if(timestamp_minute == 15 && timestamp_second == 0 &&(timestamp_hour == 12 || timestamp_hour == 14 || timestamp_hour == 16 || timestamp_hour == 18 || timestamp_hour == 20 || timestamp_hour == 22 || timestamp_hour == 0 || timestamp_hour == 2 || timestamp_hour == 4 || timestamp_hour == 6 || timestamp_hour == 8 || timestamp_hour == 10) && StartPaintBall == 0)
	{
		TimerPaintBall = 180;
		StartPaintBall = 1;
		RedScore = BlueScore = RedPlayer = BluePlayer = 0;

		if(++ PaintBallMap > 2)PaintBallMap = 1;
		foreach(new i: logged_players)
		{
			if(TeamPaint[i])
			{
				TeamPaint[i] = KillPaint[i] = DeathPaint[i] = 0;
				set_pos(i, 1298.1658, -1360.8027, 35.8113, 21.7293, 0, 5);
			}
		}
		SendClientMessageToAll(col_gray, ""c_server"[PaintBall]"c_white"Mosabeghe "c_yellow"\"PaintBall\""c_white" ta 3 daghighe digar bargozar mishe. Baraye raftan be paintball "c_server"/go"c_white" ra type konid.");
	}

	if(timestamp_minute == 15 && timestamp_second == 0 || timestamp_minute == 30 && timestamp_second == 0 || timestamp_minute == 40 && timestamp_second == 0  || timestamp_minute == 55  && timestamp_second == 0)
	{
 		foreach(new i: logged_players)
		{
			if(playerFactionStatus(i))
			{
				SendClientMessage(i, col_white, ""c_yellow"Hanoz ozv sazmani nisti? Dastor /vacancy, ra baraye didan sazman haye ke ozv giri mikonand vared konif!");
			}
		}
	}


	if(timestamp_minute == 15 && timestamp_second == 0 &&(timestamp_hour == 11 || timestamp_hour == 13 || timestamp_hour == 15 || timestamp_hour == 17 || timestamp_hour == 19 || timestamp_hour == 21 || timestamp_hour == 1 || timestamp_hour == 3 || timestamp_hour == 5 || timestamp_hour == 7 || timestamp_hour == 9) && StartRace == 0)
	{
		TimerRace = 180;
		StartRace = 1;
		RaceCountWinner =
		PlayerRaceCount = 0;

		race_bank = 0;
		RaceVehicle = Race_Car[random(18)];
		if(++RaceMap > 9) RaceMap = 1;
		foreach(new i: logged_players)
		{
			if(is_player_race_regged[i])
			{
				DestroyVehicle(player_race_vehicle[i]);
				player_race_vehicle[i] =
				is_player_race_regged[i] =
				player_race_cp[i] = 0;
				DisableRemoteVehicleCollisions(i, 0);
				set_pos(i, 1298.1658, -1360.8027, 35.8113, 21.7293, 0, 5);
			}
		}
		SendClientMessageToAll(col_gray, ""c_server"[Derby]"c_white"Mosabeghe "c_yellow"\"Derby\""c_white" ta 3 daghighe digar bargozar mishe. Baraye raftan be race "c_server"/go"c_white" ra type konid.");
	}

	if(timestamp_hour == 3 && timestamp_minute == 45 && timestamp_second == 0)SendClientMessageToAll(col_gray, ""c_server"* S.INFO:"c_grey" bad az 15daghighe server restart mishe va shoma mitonid dobare vared shid.");

	if(timestamp_hour == 17 && timestamp_minute == 45 && timestamp_second == 0) SendClientMessageToAll(col_gray, ""c_yellow"bad az 15 daghighe haraj khodro haye kharab anjam mishe! ((/gps -> Forosh Vasile))");
	if(timestamp_hour == 17 && timestamp_minute == 55 && timestamp_second == 0) SendClientMessageToAll(col_gray, ""c_yellow"bad az 5 daghighe haraj khodro haye kharab anjam mishe! ((/gps -> Forosh Vasile))");
	
	if(timestamp_hour == 18 && timestamp_minute == 00 && timestamp_second == 0)
	{
		for(new bureau = 0; bureau < MAX_BUREAU; bureau++)
		{
			for(new vehicle = 0; vehicle < MAX_AUCTION_CARS; vehicle++)
			{
				bureauInfo[bureau][vehicle][bCarModel] = AuctionVehiclesList[random(sizeof AuctionVehiclesList)];
				bureauInfo[bureau][vehicle][bSalonPrice] = GetModelPrice(bureauInfo[bureau][vehicle][bCarModel]);
				bureauInfo[bureau][vehicle][bStrengthPercentage] = 10 + random(41);
				bureauInfo[bureau][vehicle][bMaxSpeed] = max_veh_speed[bureauInfo[bureau][vehicle][bCarModel] -400];
				bureauInfo[bureau][vehicle][bAuctionPrice] = bureauInfo[bureau][vehicle][bSalonPrice] * bureauInfo[bureau][vehicle][bStrengthPercentage] / 100;
				bureauInfo[bureau][vehicle][bMileage] = 30 + random(100);
				bureauInfo[bureau][vehicle][bTuning] = bool:(random(2));
				bureauInfo[bureau][vehicle][bPTuning] = bool:(random(2));
				bureauInfo[bureau][vehicle][bTime] = 60;
				bureauInfo[bureau][vehicle][bColor1] = random(257);
				bureauInfo[bureau][vehicle][bColor2] = random(257);
				bureauInfo[bureau][vehicle][bActive] = true;
			}
		}
		runningAuctionsCount = MAX_BUREAU * MAX_AUCTION_CARS;
		SendClientMessageToAll(col_gray, ""c_yellow"haraj khodro ha dar hal anjame! ((/gps -> Forosh Vasile))");
	}

    return 1;
}