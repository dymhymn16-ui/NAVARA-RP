stock ToHHMMSS(const time, &hours=0, &minutes=0, &seconds=0)
{
    hours = floatround(time / 3600);
    minutes = floatround((time % 3600) / 60);
    seconds = floatround((time % 3600) % 60);
}

stock GetDeliveryTime(percent)
{
	switch(percent)
	{
		case 10..15: return timestamp + 5 * 12;
		case 16..25: return timestamp + 6 * 10;
		case 26..35: return timestamp + 8 * 8;
		case 36..50: return timestamp + 10 * 6;
	}

	return 0;
}

stock GetDay(day, month, year)
{
	if (month <= 2)
	month += 12, --year;
	new j = year % 100;
	new e = year / 100;
	return (day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7;
}

stock MyTimeStamp(timestamp_x, &year, &month, &day, &hour, &minute, &second)
{
    second = timestamp_x % 60;

    minute = timestamp_x / 60;

    hour = minute / 60;

    if(minute > 59) minute %= 60;
    
    day = hour / 24;
    if(hour > 23) hour %= 24;
    
    month = day / 30;
    if(day > 29) hour %= 30;
    
    year = month / 12;
    if(month > 11) month %= 12;
}