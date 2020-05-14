#include "webserver.h"

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
        debugD("webserver: / GET request hit me.");
        request->send(SPIFFS, "/index.html", String(), false, webserverProcessHtmlTemplate);
    });

    // milligram.min.css.gz
    webServer.on("/milligram.min.css.gz", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/milligram.min.css.gz", "text/css");
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    // configurations data of th wordclock/LEDs
    webServer.on("/config", HTTP_POST, [](AsyncWebServerRequest *request) {
        debugD("webserver: /config POST request hit me.");
        // parse parameter
        String message = "Changed configuration:\n";
        int params = request->params();
        debugD("webserver: %d params sent in", params);
        for (int i = 0; i < params; i++)
        {
            AsyncWebParameter *p = request->getParam(i);
            if (p->isFile())
            {
                debugD("_FILE[%s]: %s, size: %u", p->name().c_str(), p->value().c_str(), p->size());
            }
            else if (p->isPost())
            {
                // handling of post params
                debugD("_POST[%s]: %s", p->name().c_str(), p->value().c_str());
            }
            else
            {
                debugD("_GET[%s]: %s", p->name().c_str(), p->value().c_str());
            }
        }

        if (request->hasParam("brightness", true))
        {
            debugI("Got POST parameter 'brightness'. Handling it now.");
            // setBrightness(request->getParam("brightness")->value().toInt());
            // message += "brightness: " + request->getParam("brightness")->value();
        }
        if (request->hasParam("color", true))
        {
            debugI("Got POST parameter 'color'. Handling it now.");
            //setBrightness(request->getParam("brightness")->value().toInt());
            setBrightness(50);
            //message += request->getParam("brightness")->value();
        }
        request->send(200, "text/plain", message);
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
    Serial.println(var);
    if (var == "CLOCK_BRIGHTNESS")
    {

        return String(getBrightness());
    }
    if (var == "CLOCK_COLOR")
    {

        return String(getBrightness());
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

//---------------------------------------------------------------------------------------
// webserverWordclockConfig
//
// handles post for
//
//---------------------------------------------------------------------------------------
void webserverWordclockConfig(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}