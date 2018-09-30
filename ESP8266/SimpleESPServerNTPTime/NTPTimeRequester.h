// you must have the Timezone and the Timelib libraries installed to use this class
// Timezone can be found at: https://github.com/JChristensen/Timezone
// TimeLib can be found at: https://github.com/PaulStoffregen/Time
// See the Arduino documentation for installing libraries

#ifndef NTPTIMEREQUESTER_H
#define NTPTIMEREQUESTER_H

#include <WiFiUdp.h>

enum TIMEZONE 
{
    UTC,
    US_EASTERN,
    US_CENTRAL,
    US_MOUNTAIN,
    US_PACIFIC
};

class NTPTimeRequester
{
private:
    long m_curUnixTimeUTC;
    const char * m_NTPServerName;
    int m_NTPPort;
    IPAddress m_NTPAddress;
    long m_lastNTPRequestMillis;
    WiFiUDP m_UDP;
    void sendNTPRequest();

public:

    NTPTimeRequester(const char *NTPServerName = "time.nist.gov", int portNum = 123)
    : m_curUnixTimeUTC(-1)
    , m_NTPServerName(NTPServerName)
    , m_NTPPort(portNum)
    {}

    // make sure you are connected to the internet before calling this function
    void start(bool rebootOnDNSFail = true);
    uint32_t requestUnixTimeUTC();
    uint32_t getUnixTimeUTC();

    static uint32_t convertUTCToLocal(uint32_t timeStampUTC, TIMEZONE timezone = US_CENTRAL, bool areaUsesDST = true);
    static int getSec(uint32_t timeStampSeconds) { return timeStampSeconds % 60; }
    static int getMin(uint32_t timeStampSeconds) {  return (timeStampSeconds / 60) % 60; }
    static int getHour(uint32_t timeStampSeconds) { return (timeStampSeconds / 3600) % 24; }
    
};

#endif // NTPTIMEREQUESTER_H
