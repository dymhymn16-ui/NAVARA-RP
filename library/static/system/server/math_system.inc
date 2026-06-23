new mathStatus,
	mathResult,
	moneyMath;


stock clearMath()
{
	if(mathStatus == 1)
	{
		mathStatus = 0;
		mathResult = 0;
		moneyMath = 0;
	}
	return 1;
}


stock check_math(playerid, string[])
{

	if(mathStatus == 1 && strval(string) == mathResult)
	{
		new text_math[250];
		format(text_math,sizeof(text_math), c_server"[Riazi]"c_orange_red" %s "c_yellow"Soal Riazi Ro Hall Kard Va {00a329}$%s"c_yellow" Jayeze Gereft. Javabesh: %d.", PlayerInfo[playerid][name], convert_money(moneyMath), mathResult);

		
 		foreach(new i: logged_players)
		{
			SendClientMessage(i, col_gray, text_math);
		}

		give_money(playerid,moneyMath);
		mathStatus = 0;
		mathResult = 0;
		moneyMath = 0;

		return 1;
	}

	return 0;
}


cmd:math(playerid) 
{
	if(check_admin_rank(playerid , 3)) return 1;

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

	return 1;
}