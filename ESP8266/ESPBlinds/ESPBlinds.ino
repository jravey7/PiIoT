#include <Servo.h>

#include "ESPWebServer.h"
#include "NTPTimeRequester.h"

#include "htmlPage.h"
#include "ServoControl.h"

// the ESP server
#include "WiFiCredentials.h" // put your WiFi ssid and passwords in this file
ESPWebServer espServer(wiFiSSID, wiFiPassword);

// time
NTPTimeRequester ntpRequester;
char formattedHtmlPage[10000]; 

// Available GPIO pins
const int gpio2Pin = 2;

// Servo
Servo blindServo;
ServoInfo servoInfo;

void setup() 
{
    Serial.begin(115200);

    // Initialize the output
    //pinMode(gpio2Pin, OUTPUT);
    //digitalWrite(gpio2Pin, gpio2State);

    // start server
    espServer.startServer();

    // start time requests
    ntpRequester.start();

    // attach servo
    blindServo.attach(gpio2Pin);
}

int lastServoSettting;
void loop()
{
    // get the current time
    uint32_t unixTimeLocal = NTPTimeRequester::convertUTCToLocal(ntpRequester.requestUnixTimeUTC());
    sprintf(formattedHtmlPage, htmlPage, 
        lastServoSettting,
        lastServoSettting,
        servoInfo.openSetting,
        servoInfo.closeSetting,
        NTPTimeRequester::getHour(unixTimeLocal), 
        NTPTimeRequester::getMin(unixTimeLocal), 
        NTPTimeRequester::getSec(unixTimeLocal) );
  
    ServoControl curServoInteraction;
    if(espServer.handleClientRequest(curServoInteraction, formattedHtmlPage))
    {
        // a client request was processed

        if(curServoInteraction.type != NONE)
        {
            switch(curServoInteraction.type)
            {
                case OPEN_BLINDS:
                    openBlinds();
                    break;
                case CLOSE_BLINDS:
                    closeBlinds();
                    break;
                case SET_OPEN:
                    lastServoSettting = curServoInteraction.setting;
                    servoInfo.openSetting = curServoInteraction.setting;
                    openBlinds();
                    break;
                case SET_CLOSE:
                    lastServoSettting = curServoInteraction.setting;
                    servoInfo.closeSetting = curServoInteraction.setting;
                    closeBlinds();
                    break;
            }
        }
    }
}

void openBlinds()
{
    if(servoInfo.curState != SERVO_OPEN)
    {
      blindServo.attach(gpio2Pin);
      blindServo.write(servoInfo.openSetting);
      delay(3000); // wait three seconds for servo to rotate
      blindServo.detach();
      servoInfo.curState = SERVO_OPEN;
    }
}

void closeBlinds()
{
    if(servoInfo.curState != SERVO_CLOSED)
    {
      blindServo.attach(gpio2Pin);
      blindServo.write(servoInfo.closeSetting);
      delay(3000); // wait three seconds for servo to rotate
      blindServo.detach();
      servoInfo.curState = SERVO_CLOSED;
    }
}
