forward SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid);
public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    if (keyid == 0x42) 
    {
        if (VoiceMuted[playerid]) 
        {
            new _t_string[38];
            format(_t_string, sizeof(_t_string),"Shoma az voice mahrum hastid | %d saniye", CallRemoteFunction("ReturnPlayerMuteTime", "d", playerid));
            SendClientMessage(playerid, col_light_red, _t_string);
        } 
        else 
        {
            if(PlayerHaveStreamKey[playerid] != SV_GSTREAM:-1) 
            {
                SvAttachSpeakerToStream(PlayerHaveStreamKey[playerid], playerid);
            }
            else 
            {
                if (lstream[playerid]) SvAttachSpeakerToStream(lstream[playerid], playerid);            
            }
        }
    }
}

forward SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid);
public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    if (keyid == 0x42) 
    {
        if(PlayerHaveStreamKey[playerid] != SV_GSTREAM:-1) 
        {
            SvDetachSpeakerFromStream(PlayerHaveStreamKey[playerid], playerid);
        }
        else 
        {
            if (lstream[playerid]) SvDetachSpeakerFromStream(lstream[playerid], playerid);
        }
    }
}

forward SV_AddVoice(playerid);
public SV_AddVoice(playerid)
{
    // if(lstream[playerid]) SvAddKey(playerid, 0x42);
    VoiceMuted[playerid] = false;
}

forward SV_RemoveVoice(playerid);
public SV_RemoveVoice(playerid)
{
    // if(lstream[playerid]) SvRemoveKey(playerid, 0x42);
    VoiceMuted[playerid] = true;
}

forward IsPlayerHaveSampVoice(playerid);
public IsPlayerHaveSampVoice(playerid)
{
    return SvGetVersion(playerid) != SV_NULL;
}

forward CreateStreamForPhoneCall(playerid, targetid);
public CreateStreamForPhoneCall(playerid, targetid)
{
    new 
        SV_GSTREAM: stream_call = SvCreateGStream(0x32CD7800, "Mobile");

    if(stream_call == SV_NULL)
        return -1;

    SvAttachListenerToStream(stream_call, playerid);
    SvAttachListenerToStream(stream_call, targetid);

    PlayerHaveStreamKey[playerid] = stream_call;
    PlayerHaveStreamKey[targetid] = stream_call;
    return stream_call;
}

forward DeleteStreamPhoneCall(SV_GSTREAM: stream_id);
public DeleteStreamPhoneCall(SV_GSTREAM: stream_id)
{
    if(stream_id) {
        // Temporary Comment
        // SvDeleteStream(stream_id);

        /*
            [20:25:07] Server crashed while executing voicechat.amx
            [20:25:07] AMX backtrace:
            [20:25:07] #0 native SvDeleteStream () in sampvoice.DLL
            [20:25:07] #1 00001048 in public DeleteStreamPhoneCall (stream_id=212690016) at filterscripts\voicechat.pwn:335
        */
    }
}

forward ResetPlayerStreamPhoneCall(playerid, SV_GSTREAM: stream_id);
public ResetPlayerStreamPhoneCall(playerid, SV_GSTREAM: stream_id)
{
    SvDetachSpeakerFromStream(stream_id, playerid);
    SvDetachListenerFromStream(stream_id, playerid);
    PlayerHaveStreamKey[playerid] = SV_GSTREAM:-1;
}


stock VC_OnPlayerConnect(playerid)
{
    VoiceMuted[playerid] = false;
    PlayerHaveStreamKey[playerid] = SV_GSTREAM:-1;
}

stock VC_OnPlayerDisconnect(playerid)
{
    if (lstream[playerid])
    {
        SvDeleteStream(lstream[playerid]);
        lstream[playerid] = SV_NULL;
    }

    PlayerHaveStreamKey[playerid] = SV_GSTREAM:-1;
}