#include "NTPTimeRequester.h"

// you must have the Timezone and the Timelib libraries installed to use this class
// Timezone can be found at: https://github.com/JChristensen/Timezone
// TimeLib can be found at: https://github.com/PaulStoffregen/Time
// See the Arduino documentation for installing libraries
#include <Timezone.h>

#include <ESP8266WiFi.h>

const int NTP_PACKET_SIZE = 48;  // NTP time stamp is in the first 48 bytes of the message
byte g_NTPBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

//// timezone definitions
// eastern
const TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -300}; // UTC - 5 hours
const TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -240}; // UTC - 4 hours

// central
const TimeChangeRule usCST = {"CST", First, Sun, Nov, 2, -360}; // UTC - 6 hours
const TimeChangeRule usCDT = {"CDT", Second, Sun, Mar, 2, -300}; // UTC - 5 hours

// mountain
const TimeChangeRule usMST = {"MST", First, Sun, Nov, 2, -420}; // UTC - 7 hours
const TimeChangeRule usMDT = {"MDT", Second, Sun, Mar, 2, -360}; // UTC - 6 hours

// pacific
const TimeChangeRule usPST = {"PST", First, Sun, Nov, 2, -480}; // UTC - 8 hours
const TimeChangeRule usPDT = {"PDT", Second, Sun, Mar, 2, -420}; // UTC - 7 hours

void NTPTimeRequester::start(bool rebootOnDNSFail)
{
    // set up UDP listening port for NTP messages (time)
    m_UDP.begin(m_NTPPort);

    // query the NTP for the time
    IPAddress timeServerIP;
    if(!WiFi.hostByName(m_NTPServerName, timeServerIP))
    {
        Serial.print("NTP server DNS lookup failed.");
        if( rebootOnDNSFail )
        {
            Serial.println(" Rebooting.");
            Serial.flush();
            ESP.reset();
        }
        Serial.print("\n");
        return;
    }
    m_NTPAddress = timeServerIP;
    Serial.printf("Attempting to request time from %s (%s) ", m_NTPServerName, m_NTPAddress.toString().c_str());
    Serial.print(".");

    sendNTPRequest();
    m_lastNTPRequestMillis = millis();

    while( (m_curUnixTimeUTC = getUnixTimeUTC()) == -1)
    {
        if((millis() - m_lastNTPRequestMillis) > 5000)
        {
            // try request again after 5 seconds
            sendNTPRequest();
            m_lastNTPRequestMillis = millis();
            Serial.print(".");
        }
    }
    Serial.print("done\n");
}

void NTPTimeRequester::sendNTPRequest() {

    memset(g_NTPBuffer, 0, NTP_PACKET_SIZE);  // set all bytes in the buffer to 0

    // Initialize values needed to form NTP request
    g_NTPBuffer[0] = 0b11100011;   // LI, Version, Mode
    // send a packet requesting a timestamp:
    m_UDP.beginPacket(m_NTPAddress, m_NTPPort);
    m_UDP.write(g_NTPBuffer, NTP_PACKET_SIZE);
    m_UDP.endPacket();
}

uint32_t NTPTimeRequester::requestUnixTimeUTC()
{
    // query for the time at max only once a second
    if((millis() - m_lastNTPRequestMillis) > 1000)
    {
        sendNTPRequest();
        m_lastNTPRequestMillis = millis();
    }

    if (m_UDP.parsePacket() != 0) { // If there's an NTP response then update the current time
        m_UDP.read(g_NTPBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
        // Combine the 4 timestamp bytes into one 32-bit number
        uint32_t NTPTime = (g_NTPBuffer[40] << 24) | (g_NTPBuffer[41] << 16) | (g_NTPBuffer[42] << 8) | g_NTPBuffer[43];
        // Convert NTP time to a UNIX timestamp:
        // Unix time starts on Jan 1 1970. That's 2208988800 seconds in NTP time:
        const uint32_t seventyYears = 2208988800UL;
        // subtract seventy years:
        m_curUnixTimeUTC = NTPTime - seventyYears;
    }

    return m_curUnixTimeUTC;
}

uint32_t NTPTimeRequester::getUnixTimeUTC()
{
    // this function does not request the time from NTP server
    // however, it does check to see if we've been sent an update from 
    // the NTP server

    // you can use this function to get the last known time

    if (m_UDP.parsePacket() != 0) { // If there's an NTP response then update the current time
        m_UDP.read(g_NTPBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
        // Combine the 4 timestamp bytes into one 32-bit number
        uint32_t NTPTime = (g_NTPBuffer[40] << 24) | (g_NTPBuffer[41] << 16) | (g_NTPBuffer[42] << 8) | g_NTPBuffer[43];
        // Convert NTP time to a UNIX timestamp:
        // Unix time starts on Jan 1 1970. That's 2208988800 seconds in NTP time:
        const uint32_t seventyYears = 2208988800UL;
        // subtract seventy years:
        m_curUnixTimeUTC = NTPTime - seventyYears;
    }

    return m_curUnixTimeUTC;
}

uint32_t NTPTimeRequester::convertUTCToLocal(uint32_t timeStampUTC, TIMEZONE timezone, bool areaUsesDST)
{
    Timezone localTimezone(usCDT, usCST);

    if(areaUsesDST)
    {
        switch(timezone)
        {
            case US_EASTERN:
                localTimezone.setRules(usEDT, usEST);
                break;
            case US_CENTRAL:
                localTimezone.setRules(usCDT, usCST);
                break;
            case US_MOUNTAIN:
                localTimezone.setRules(usMDT, usMST);
                break;
            case US_PACIFIC:
                localTimezone.setRules(usPDT, usPST);
                break;
        }
    }
    else
    {   
        switch(timezone)
        {
            case US_EASTERN:
                localTimezone.setRules(usEST, usEST);
                break;
            case US_CENTRAL:
                localTimezone.setRules(usCST, usCST);
                break;
            case US_MOUNTAIN:
                localTimezone.setRules(usMST, usMST);
                break;
            case US_PACIFIC:
                localTimezone.setRules(usPST, usPST);
                break;
        }
    }

    return localTimezone.toLocal(timeStampUTC);
}
