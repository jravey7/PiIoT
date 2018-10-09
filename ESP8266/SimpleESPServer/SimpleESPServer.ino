#include "ESPWebServer.h"

// the ESP server
#include "WiFiCredentials.h" // put your WiFi ssid and passwords in this file
ESPWebServer espServer(wiFiSSID, wiFiPassword);

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
}



void loop()
{
    bool buttonClicked;
    if(espServer.handleClientRequest(buttonClicked))
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
