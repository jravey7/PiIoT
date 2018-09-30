#include "ESPWebServer.h"

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

bool ESPWebServer::handleClientRequest(bool &buttonClicked, String appendToHTML)
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
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();
            
                        // checks if the client clicked the button
                        if (header.indexOf("GET /toggle") >= 0) 
                        {
                            buttonClicked = true;
                        } 
            
                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<link rel=\"icon\" href=\"data:,\">");

                        // CSS to style the button
                        // Feel free to change the background-color and font-size attributes to fit your preferences
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");

                        // Web Page Heading
                        client.println("<body><h1>ESP8266 Web Server</h1>");
                        client.println("<p><a href=\"/toggle\"><button class=\"button\">Toggle GPIO 2</button></a></p>");

                        // append any user defined string to the html
                        client.println(appendToHTML);
                        
                        client.println("</body></html>");

                        // The HTTP response ends with another blank line
                        client.println();

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
