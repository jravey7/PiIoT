
#ifndef ESPWEBSERVER_H
#define ESPWEBSERVER_H

#include <ESP8266WiFi.h>

class ESPWebServer
{
    
    // WiFi AP related
    String m_ssid, m_password;

    // server related
    WiFiServer m_server;
    String m_header;

public:
    //// constructors and initializers
    ESPWebServer(String ssid, String password)
    : m_server(80)
    , m_ssid(ssid)
    , m_password(password)
    {
    }
    ESPWebServer(const char *ssid, const char *password)
    : m_server(80)
    , m_ssid(String(ssid))
    , m_password(String(password))
    {
    }

    // if you use the default constructor, you must also call init()
    // before startServer()
    ESPWebServer();
    void init(const char *ssid, const char *password)
    {
        m_ssid = String(ssid);
        m_password = String(password);
        m_server = WiFiServer(80);
    }
    void init(String ssid, String password)
    {
        m_ssid = ssid;
        m_password = password;
        m_server = WiFiServer(80);
    }

    //// server related

    // connects the web server to access point defined by constructor params
    // and starts the server
    void startServer();

    // returns true if a client request was processed, false otherwise
    bool handleClientRequest(bool &buttonClicked, String appendToHTML = "");
};

#endif // ESPWEBSERVER_H
