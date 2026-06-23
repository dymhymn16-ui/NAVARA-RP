#if !defined _samp_included
	#include <a_samp>
#endif

#if !defined HTTP
    #include <a_http>
#endif

// ------------------------

#if !defined LOG_SMS
    #define LOG_SMS true
#endif

#define INVALID_PHONE_NUMBER    -1

// ------------------------

#define PANEL_SMS_ADDRESS_PORT  "ippanel.com:8080"

#define PANEL_SMS_API_KEY       "Z0KzXvnhyh48xF9QhgIcWnmEYrluqwGYYA209wxn0SE="

#define SMS_SENDER_FROM_NUMBER  "5000125475"

#define PATTREN_ID              "ziu28wjo57i19wx"
#define PATTREN_VARIABLE_1      "verification-code"

// ------------------------

static Inc_IsNumeric(str[]) {
    new ch, i;
    while ((ch = str[i++])) if (!('0' <= ch <= '9')) return 0;
    return 1;
}

bool: IsValidPhoneNumber(phone[]) {
    if (strlen(phone) != 11 || !Inc_IsNumeric(phone)) 
        return false;
    if (phone[0] != '0' || phone[1] != '9')
        return false;
    return true;
}

// ------------------------

stock SendVerificationSMS(index, phone[], verification_code) {
    if (!IsPlayerConnected(index))
        return INVALID_PLAYER_ID;
    
    if (!IsValidPhoneNumber(phone))
        return INVALID_PHONE_NUMBER;

    new 
        R_STRING[ 200 ], R_NAME[ 24 ];

    GetPlayerName(index, R_NAME, 24);

    format(R_STRING, sizeof R_STRING, ""PANEL_SMS_ADDRESS_PORT"/?apikey="PANEL_SMS_API_KEY"&pid="PATTREN_ID"&fnum="SMS_SENDER_FROM_NUMBER"&tnum=%s&p1="PATTREN_VARIABLE_1"&v1=%d", 
        phone, verification_code);

    HTTP(index, HTTP_GET, R_STRING, "", "OnSMS_Response");

    #if LOG_SMS
        printf("[Info] [Send SMS] Name: %s | Verification Code: %i", R_NAME, verification_code);
    #endif
    
    return 1;
}

forward OnSMS_Response(index, response_code, data[]);
public OnSMS_Response(index, response_code, data[])
{
    if(response_code == 200 || response_code == 0)
    {
        //success
    }
    else
    {
        #if LOG_SMS
            new 
                R_NAME[ 24 ];

            GetPlayerName(index, R_NAME, 24);

            printf("[HTTP] [SMS] Player: %s | [response_code: %d] %s", R_NAME, response_code, data);
        #endif
    }
}

// ------------------------

stock SensorPhoneNumber(phone[]) {
    new tmpPhone[12];
    format(tmpPhone, sizeof tmpPhone, "%s", phone);
    for(new w = 4; w < 7; w++) { tmpPhone[w] = '*'; }
    return tmpPhone;
}

// ------------------------

#undef LOG_SMS

#undef PANEL_SMS_ADDRESS_PORT

#undef PANEL_SMS_API_KEY

#undef SMS_SENDER_FROM_NUMBER

#undef PATTREN_ID
#undef PATTREN_VARIABLE_1