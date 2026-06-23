#if defined _samp_mobile_checker_included
	#endinput
#endif

#define _samp_mobile_checker_included
#define _samp_mobile_checker_version 10 // 1.0

#if !defined _INC_open_mp
	#if !defined gpci
	    native gpci(playerid, serial[], len);
	#endif
#endif

// -----------------------------------------------------------------------------

// https://play.google.com/store/apps/details?id=ru.unisamp_mobile.launcher

#define IsPlayerUsingSampMobile(%0) 	s_SampMobilePlayer[%0]

// -----------------------------------------------------------------------------

forward OnPlayerConnectViaSampMobile(playerid);

// -----------------------------------------------------------------------------

new 
	bool: s_SampMobilePlayer[MAX_PLAYERS];

// -----------------------------------------------------------------------------

/*stock bool: IsPlayerUsingSampMobile(playerid) {
	return (s_SampMobilePlayer[playerid]);
}*/

// -----------------------------------------------------------------------------

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid) {
	new
        ciSerial[41];

	#if !defined GPCI
    	gpci(playerid, ciSerial, sizeof(ciSerial));
    #else
    	GPCI(playerid, ciSerial, sizeof(ciSerial));
    #endif

    if(strfind(ciSerial, "3952314F524834355456464955525858554F3353") != -1 || strfind(ciSerial, "4458465947454248504B51425156534F4738384F") != -1 || strfind(ciSerial, "ED40ED0E8089CC44C08EE9580F4C8C44EE8EE990") != -1) 
    {
        s_SampMobilePlayer[playerid] = true;
        CallLocalFunction("OnPlayerConnectViaSampMobile", "i", playerid);
    }else
	{
		s_SampMobilePlayer[playerid] = false;
	}

	#if defined _SMC_OnPlayerConnect
		return _SMC_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect _SMC_OnPlayerConnect
#if defined _SMC_OnPlayerConnect
	forward _SMC_OnPlayerConnect(playerid);
#endif

// -----------------------------------------------------------------------------