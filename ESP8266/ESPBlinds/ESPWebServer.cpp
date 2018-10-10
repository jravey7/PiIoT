#include "ESPWebServer.h"
#include "ServoControl.h"

void ESPWebServer::startServer()
{
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(m_ssid);
    WiFi.begin(m_ssid.c_str(), m_password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    m_server.begin();
}

bool ESPWebServer::handleClientRequest(ServoControl &servoInteraction, String htmlPage)
{ 
    bool clientHandled = false;

    WiFiClient client = m_server.available();   // Listen for incoming clients

    if (client) 
    {                            
        Serial.println("New Client.");
        String header = "";
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected())
        {            
            if (client.available()) 
            {
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                header += c;
                if (c == '\n') 
                {
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) 
                    {
                        // checks if the client signaled an interaction
                        int index;
                        servoInteraction.type = NONE;
                        if ((index = header.indexOf("GET /openBlinds")) >= 0) 
                        {
                            servoInteraction.type = OPEN_BLINDS;
                        }
                        else if ((index = header.indexOf("GET /closeBlinds")) >= 0) 
                        {
                            servoInteraction.type = CLOSE_BLINDS;
                        }
                        else if ((index = header.indexOf("GET /setOpenBlinds")) >= 0) 
                        {
                            String passedValue;
                            index += 20;
                            char newChar = header.charAt(index);
                            while(newChar != '"')
                            {
                              passedValue += newChar;
                              index++;
                              newChar = header.charAt(index);
                            }

                            servoInteraction.type = SET_OPEN;
                            servoInteraction.setting = passedValue.toInt();
                        }
                        else if ((index = header.indexOf("GET /setCloseBlinds")) >= 0) 
                        {
                            String passedValue;
                            index += 21;
                            char newChar = header.charAt(index);
                            while(newChar != '"')
                            {
                              passedValue += newChar;
                              index++;
                              newChar = header.charAt(index);
                            }

                            servoInteraction.type = SET_CLOSE;
                            servoInteraction.setting = passedValue.toInt();
                        }

                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
                        
                        // Display the HTML web page
                        client.println(htmlPage);

                        // Break out of the while loop
                        clientHandled = true;
                        break;
                    } 
                    else
                    { 
                        // if you got a newline, then clear currentLine
                        currentLine = "";
                    }
                } 
                else if (c != '\r')
                {
                    // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println(""); 
    }

    return clientHandled;
}
