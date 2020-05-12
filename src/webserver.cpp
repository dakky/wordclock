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
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String(), false, webserverProcessHtmlTemplate);
    });
    
    // milligram.min.css.gz
    webServer.on("/milligram.min.css.gz", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/milligram.min.css.gz", "text/css");
    });

    // configurations data of th wordclock/LEDs
    webServer.on("/config/wordclock", HTTP_POST, [](AsyncWebServerRequest *request){
        debugD("/config/worclock POST request hit me.");
        // Paramter parsen
        String message;
        int params = request->params();
        debugD("%d params sent in\n", params);
        for (int i = 0; i < params; i++)
        {
            AsyncWebParameter *p = request->getParam(i);
            if (p->isFile())
            {
                debugD("_FILE[%s]: %s, size: %u", p->name().c_str(), p->value().c_str(), p->size());
            }
            else if (p->isPost())
            {
                debugD("_POST[%s]: %s", p->name().c_str(), p->value().c_str());
            }
            else
            {
                debugD("_GET[%s]: %s", p->name().c_str(), p->value().c_str());
            }
        }
        if (request->hasParam("device", true))
        {
            message = request->getParam("device")->value();
        }
        else
        {
            debugE("No known parameter submitted to endpoint.");
            message = "not specified";
        }
        request->send(200, "text/plain", "Off, GET: " + message);
        Serial.print("Device ");
        Serial.println(message);
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
String webserverProcessHtmlTemplate(const String& var){
  Serial.println(var);
  if(var == "brightness"){
    
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
void webserverNotFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

//---------------------------------------------------------------------------------------
// webserverWordclockConfig
//
// handles post for 
//
//---------------------------------------------------------------------------------------
void webserverWordclockConfig(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}