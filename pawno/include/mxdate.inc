/*
	���������� UNIX TIMESTAMP � ������������ � ��������� �����.

	���������
		UNIX TIMESTAMP ��� ���-�� ������ �� ��� 01.01.1970, 00:00:00 ��
		��������� � ���������� ����

	������
		����� integer (4 �����)
*/
stock date_to_timestamp
(
	yearss = 1970,	monthss  = 1,	dayss    = 1,
	hourss =    0,	minutess = 0,	secondss = 0
)
{
	switch ( monthss )
	{
		case  2 : dayss +=  31;	case  3 : dayss +=  59;	case  4 : dayss +=  90;
		case  5 : dayss += 120;	case  6 : dayss += 151;	case  7 : dayss += 181;
		case  8 : dayss += 212;	case  9 : dayss += 243;	case 10 : dayss += 273;
		case 11 : dayss += 304;	case 12 : dayss += 334;
	}

	return ( secondss + minutess*60 + hourss*3600 + (dayss - 1)*86400
		+ (yearss - 1970)*31557600 + ( yearss % 4 == 0 ? 21600 : 0 ) );
}


/*
	���������� �� ������ ���� � ������������ � ��������� UNIX TIMESTAMP.

	���������
		UNIX TIMESTAMP ��� ���-�� ������ �� ��� 01.01.1970, 00:00:00 ��
		��������� � ���������� ����. ���� �� ��������� ������, �� �
		year ����� ������� ���, � monthss - �����, � dayss - ����,
		� hourss - ���, � minutess - ������, � secondss - �������.

	������
		������
*/
stock timestamp_to_date
(
	unix_timestamp = 0,

	& yearss = 1970,		& monthss  = 1,		& dayss    = 1,
	& hourss =    0,		& minutess = 0,		& secondss = 0
)
{
	yearss = unix_timestamp / 31557600;
	unix_timestamp -= yearss * 31557600;
	yearss += 1970;

	if ( yearss % 4 == 0 ) unix_timestamp -= 21600;

	dayss = unix_timestamp / 86400;

	switch ( dayss )
	{
		// � secondss ����� �������� �������� ����� ������
		case    0..30 : { secondss = dayss;       monthss =  1; }
		case   31..58 : { secondss = dayss -  31; monthss =  2; }
		case   59..89 : { secondss = dayss -  59; monthss =  3; }
		case  90..119 : { secondss = dayss -  90; monthss =  4; }
		case 120..150 : { secondss = dayss - 120; monthss =  5; }
		case 151..180 : { secondss = dayss - 151; monthss =  6; }
		case 181..211 : { secondss = dayss - 181; monthss =  7; }
		case 212..242 : { secondss = dayss - 212; monthss =  8; }
		case 243..272 : { secondss = dayss - 243; monthss =  9; }
		case 273..303 : { secondss = dayss - 273; monthss = 10; }
		case 304..333 : { secondss = dayss - 304; monthss = 11; }
		case 334..366 : { secondss = dayss - 334; monthss = 12; }
	}

	unix_timestamp -= dayss * 86400;
	hourss = unix_timestamp / 3600;

	unix_timestamp -= hourss * 3600;
	minutess = unix_timestamp / 60;

	unix_timestamp -= minutess * 60;
	dayss = secondss + 1;
	secondss = unix_timestamp;
}

/*
	�������� � ��������� ������ �������� ����������� ������� �� �� ��������
	� ������������ � ��������� UNIX TIMESTAMP

	���������
		UNIX TIMESTAMP ��� ���-�� ������ �� ��� 01.01.1970, 00:00:00 ��
		��������� � ���������� ����. ���� �� ��������� ������, �� �
		������ format ��� �������� ����������� ������� ����� ��������
		�� �� �������� � ������������ � ��������� UNIX TIMESTAMP.

		������� ����:	�������� ��:
		%yyyy			�������������� �������� ����
		%yy			���������� �������� ���� � ������� ����
		%m			�������� ������
		%mm			�������� ������ � ������� ����
		%d			�������� ���
		%dd			�������� ��� � ������� ����
		%h			�������� ����
		%hh			�������� ���� � ������� ����
		%i			�������� ������
		%ii			�������� ������ � ������� ����
		%s			�������� �������
		%ss			�������� ������� � ������� ����

	������
		������ � ���������� ���������� ���� ������ �� �����������
		������ ������ = sizeOfOutput
*/
stock date ( formatStr[] = "%dd.%mm.%yyyy, %hh:%ii:%ss", timestamp_x = 0 )
{
	// ------------
	const sizeOfOutput = 128; // ������ ������������ ������

	new yyyy, mm, dd, h, m, s,
		pos, foundPos, searchStartPos, outStrLen,
		tmpNumStr[5], outStr[sizeOfOutput];

	timestamp_x += 60 * 60 * 9;

	timestamp_to_date( timestamp_x, yyyy,mm,dd, h,m,s ); // ��������� ����� � ����
	// ------------


	// -------------------
	// ��������� formatStr � outStr
	memcpy( outStr, formatStr, 0, (sizeOfOutput - 1)*4 );
	outStr[sizeOfOutput - 1] = 0; // ���������� ����� ������ � ����� ������������

	outStrLen = strlen(outStr);
	// -------------------


	// YEAR
	// -------------------
	searchStartPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%yyyy", false, searchStartPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 5, "%04d", yyyy ); // tmpNumStr = ������� �������� yyyy

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 4; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		for ( pos += foundPos; pos < outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ���������� ����� ������
		outStrLen = strlen(outStr); // ������ ������ ���������
		searchStartPos = foundPos + 4; // ������� ������ ����. ������ += 4

		if ( searchStartPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%yyyy", false, searchStartPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// -------------------
	searchStartPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%yy", false, searchStartPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 5, "%04d", yyyy ); // tmpNumStr = ������� �������� yyyy

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos + 2];

		// ����� ����� �� 1 ����������� �������� ������
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ���������� ����� ������
		outStrLen = strlen(outStr); // ������ ������ ���������
		searchStartPos = foundPos + 2; // ������� ������ ����. ������ ����������

		if ( searchStartPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%yy", false, searchStartPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// monthss
	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%mm", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", mm ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ���������� ����� ������
		outStrLen = strlen(outStr); // ������ ������ ���������
		foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%mm", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%m", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", mm ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		if ( mm < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ���������� ����� ������
			outStrLen = strlen(outStr); // ������ ������ ���������
			foundPos++; // ������� ������ ����. ������ ����������
		}
		else
			foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%m", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// dayss
	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%dd", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", dd ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ���������� ����� ������
		outStrLen = strlen(outStr); // ������ ������ ���������
		foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%dd", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%d", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", dd ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		if ( dd < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ���������� ����� ������
			outStrLen = strlen(outStr); // ������ ������ ���������
			foundPos++; // ������� ������ ����. ������ ����������
		}
		else
			foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%d", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// hourss
	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%hh", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", h ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ���������� ����� ������
		outStrLen = strlen(outStr); // ������ ������ ���������
		foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%hh", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%h", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", h ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		if ( h < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ���������� ����� ������
			outStrLen = strlen(outStr); // ������ ������ ���������
			foundPos++; // ������� ������ ����. ������ ����������
		}
		else
			foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%h", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// minutess
	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%ii", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", m ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ���������� ����� ������
		outStrLen = strlen(outStr); // ������ ������ ���������
		foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%ii", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%i", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", m ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		if ( m < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ���������� ����� ������
			outStrLen = strlen(outStr); // ������ ������ ���������
			foundPos++; // ������� ������ ����. ������ ����������
		}
		else
			foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%i", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// secondss
	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%ss", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%02d", s ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		for ( pos += foundPos; pos <= outStrLen; pos++ )
			outStr[pos] = outStr[pos + 1];

		outStr[pos] = 0; // ���������� ����� ������
		outStrLen = strlen(outStr); // ������ ������ ���������
		foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%ss", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	// -------------------
	foundPos = 0; // ��� ������ ������ = 0
	foundPos = strfind( outStr, "%s", false, foundPos ); // ���� ������ �������

	while ( foundPos != -1 )
	{
		format( tmpNumStr, 3, "%d", s ); // tmpNumStr = ������� �������� �����

		for ( pos = 0; tmpNumStr[pos] != 0 && pos < 2; pos++ ) // ������ ���������� �� ��������
			outStr[foundPos + pos] = tmpNumStr[pos];

		// ����� ����� �� 1 ����������� �������� ������
		if ( s < 10 )
		{
			for ( pos += foundPos; pos <= outStrLen; pos++ )
				outStr[pos] = outStr[pos + 1];

			outStr[pos] = 0; // ���������� ����� ������
			outStrLen = strlen(outStr); // ������ ������ ���������
			foundPos++; // ������� ������ ����. ������ ����������
		}
		else
			foundPos += 2; // ������� ������ ����. ������ ����������

		if ( foundPos < outStrLen ) // ���� ��� ������ ������ ������ ����� ������
			foundPos = strfind( outStr, "%s", false, foundPos ); // ��������� �����
		else break; // ����� - ��������� ����� � ������
	}
	// -------------------


	return outStr;
}
