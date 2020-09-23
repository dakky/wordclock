#include "webserver.h"
#include "configuration.h"
#include "ntpFunctions.h"
#include "wifiFunctions.h"

//---------------------------------------------------------------------------------------
// setupWebserver
//
//  Setup of webserver
//
//---------------------------------------------------------------------------------------
void setupWebserver()
{
    //Initialize File System
    Serial.println("Setup Webserver: Initializing ...");
    if (!SPIFFS.begin())
    {
        Serial.println("SPIFFS Initialisierung ... Error!");
    }
    Serial.println("File System Initialized");

    // register routes
    // index.html
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.printf("webserver: / GET request hit me.");
        request->send(SPIFFS, "/index.html", String(), false, webserverProcessHtmlTemplate);
    });

    // milligram.min.css.gz
    webServer.on("/milligram.min.css.gz", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/milligram.min.css.gz", "text/css");
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    // config.json
    webServer.on("/config.json", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.printf("webserver: /config GET request hit me.");
        request->send(SPIFFS, "/config.json", "text/plain");
    });

    // configurations data of th wordclock/LEDs (POST)
    webServer.on("/config", HTTP_POST, [](AsyncWebServerRequest *request) {
        Serial.printf("webserver: /config POST request hit me.");
        // parse parameter
        String message = "Changed configuration:\n";
        int params = request->params();
        Serial.printf("webserver: %d params sent in", params);
        for (int i = 0; i < params; i++)
        {
            AsyncWebParameter *p = request->getParam(i);
            if (p->isFile())
            {
                Serial.printf("_FILE[%s]: %s, size: %u", p->name().c_str(), p->value().c_str(), p->size());
            }
            else if (p->isPost())
            {
                // handling of post params
                Serial.printf("_POST[%s]: %s", p->name().c_str(), p->value().c_str());
            }
            else
            {
                Serial.printf("_GET[%s]: %s", p->name().c_str(), p->value().c_str());
            }
        }

        if (request->hasParam("brightness", true))
        {
            Config.setLedBrightness(request->getParam("brightness", true)->value().toInt());
        }
        if (request->hasParam("color", true))
        {
            String color = request->getParam("color", true)->value().c_str();
            color.replace("#", "0x"); // make a "valid" HEX string

            int str_len = color.length() + 1;
            char buf[str_len];
            color.toCharArray(buf, str_len);
            Config.setLedSimpleColor(buf, str_len);
        }
        if (request->hasParam("ledMode", true))
        {
            Config.setLedMode(request->getParam("ledMode", true)->value().toInt());
        }
        if (request->hasParam("rainbow_speed", true))
        {
            Config.setLedRainbowSpeed(request->getParam("rainbow_speed", true)->value().toInt());
        }
        if (request->hasParam("hostname", true))
        {
            String hostname = request->getParam("hostname", true)->value().c_str();
            int str_len = hostname.length() + 1;
            char buf[str_len];
            hostname.toCharArray(buf, str_len);
            Config.setHostname(buf, str_len);
        }
        if (request->hasParam("ntpServername", true))
        {
            String timezone = request->getParam("ntpServername", true)->value().c_str();
            int str_len = timezone.length() + 1;
            char buf[str_len];
            timezone.toCharArray(buf, str_len);
            Config.setNtpServername(buf, str_len);
        }
        if (request->hasParam("ntpTimezone", true))
        {
            String timezone = request->getParam("ntpTimezone", true)->value().c_str();
            int str_len = timezone.length() + 1;
            char buf[str_len];
            timezone.toCharArray(buf, str_len);
            Config.setNtpTimezone(buf, str_len);
        }
        if (request->hasParam("resetConfig", true))
        {
            Config.reset();
        }
        if (request->hasParam("resetWifiEeprom", true))
        {
            resetWifi();
        }
        if (request->hasParam("debugDummyTime", true))
        {
            WordclockTime.timeToStripe(23, 12);
        }
        if (request->hasParam("debugDummyTimeNow", true))
        {
            WordclockTime.timeToStripe();
        }
        // request->send(200, "text/plain", message);
        request->redirect("/");
        Config.save();
    });

    webServer.onNotFound(webserverNotFound);
    webServer.begin();
    Serial.println("Setup Webserver: Done ...");
}

//---------------------------------------------------------------------------------------
// webserverProcessHtmlTemplate
//
// handles / requests of webserver
// simple redirect to index.html
//---------------------------------------------------------------------------------------
String webserverProcessHtmlTemplate(const String &var)
{
    if (var == "CLOCK_BRIGHTNESS")
    {
        return String(Config.getLedBrightness());
    }
    if (var == "CLOCK_RAINBOW_SPEED")
    {
        return String(Config.getLedRainbowSpeed());
    }
    if (var == "CLOCK_COLOR")
    {
        // as the chararray comes in the form 0xFFFFFF we need to replace 0x with #
        String color = Config.getLedSimpleColor();
        color.replace("0x", "#");
        return color;
    }
    if (var == "NTP_SERVERNAME")
    {
        return Config.getNtpServername();
    }
    if (var == "NTP_TIMEZONE")
    {
        return Config.getNtpTimezone();
    }
    if (var == "NTP_TIME")
    {
        return clockTimezoned.dateTime();
    }
    if (var == "NTP_TIMESTATUS")
    {
        return String(timeStatus());
    }
    if (var == "HOSTNAME")
    {
        return String(Config.getHostname());
    }
    // for any message i need to debug without serial connected
    if (var == "ANY_DEBUGMESSAGE")
    {
        return String("Anymessage: ");
    }
    return String();
}

//---------------------------------------------------------------------------------------
// webserverNotFound
//
// handles not found URIs (404)
//
//---------------------------------------------------------------------------------------
void webserverNotFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}