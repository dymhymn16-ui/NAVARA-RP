static
	PlayerPhoneCallStreamVC[MAX_PLAYERS] = {-1, ...};

stock bool: CreateVoicePhoneCallChannel(playerid, targetid) {
	new 
		stream_call = CallRemoteFunction("CreateStreamForPhoneCall", "dd", playerid, targetid);

	if(stream_call == -1) 
		return false;

	PlayerPhoneCallStreamVC[playerid] = stream_call;
	PlayerPhoneCallStreamVC[targetid] = stream_call;
	return true;
}

stock bool: DeleteVoicePhoneCallChannel(stream_call) {
	if(stream_call == -1)
		return false;

	CallRemoteFunction("DeleteStreamPhoneCall", "d", stream_call);
	return true;
}

/*stock bool: DeleteVoicePhoneCallChannel(playerid) {
	if(PlayerPhoneCallStreamVC[playerid] == -1)
		return false;

	CallRemoteFunction("DeleteStreamPhoneCall", "d", PlayerPhoneCallStreamVC[playerid]);
	return true;
}*/

stock bool: ResetVoicePhoneCallChannel(playerid) {
	CallRemoteFunction("ResetPlayerStreamPhoneCall", "dd", playerid, PlayerPhoneCallStreamVC[playerid]);
	PlayerPhoneCallStreamVC[playerid] = -1;
	return true;
}

stock GetPlayerPhoneCallStreamVC(playerid) {
	return PlayerPhoneCallStreamVC[playerid];
}
