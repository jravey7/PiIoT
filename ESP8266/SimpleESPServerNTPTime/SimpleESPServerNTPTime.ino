#include <Servo.h>

#include "ESPWebServer.h"
#include "NTPTimeRequester.h"

// the server
ESPWebServer espServer("CyFi", "batman11");

// time
NTPTimeRequester ntpRequester;
char timeStr[10]; 
String htmlFormattedTime;

// Assign output variable to GPIO pins
const int gpio2Pin = 2;
int gpio2State = LOW;

void setup() 
{
    Serial.begin(115200);

    // Initialize the output
    pinMode(gpio2Pin, OUTPUT);
    digitalWrite(gpio2Pin, gpio2State);

    // start server
    espServer.startServer();

    // start time requests
    ntpRequester.start();
}

void loop()
{
    // get the current time
    uint32_t unixTimeLocal = NTPTimeRequester::convertUTCToLocal(ntpRequester.requestUnixTimeUTC());
    sprintf(timeStr, "%02d:%02d:%02d", NTPTimeRequester::getHour(unixTimeLocal), NTPTimeRequester::getMin(unixTimeLocal), NTPTimeRequester::getSec(unixTimeLocal) );
    htmlFormattedTime = "<p>Local Time (24hr): " + String(timeStr) + "</p>";
  
    bool buttonClicked;
    if(espServer.handleClientRequest(buttonClicked, htmlFormattedTime))
    {
        // a client request was processed

        if(buttonClicked)
        {
            // toggle GPIO
            gpio2State = (gpio2State == LOW) ? HIGH : LOW;
            digitalWrite(gpio2Pin, gpio2State);
        }
    }
}
