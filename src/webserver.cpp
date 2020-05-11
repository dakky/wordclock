#include "webserver.h"


//---------------------------------------------------------------------------------------
// setupWebserver
//
//  Setup of webserver
//
// ->
// <- --
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
    // routen registrieren
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String(), false, webserverProcessHtmlTemplate);
    });
    
    // Route to load style.css file
    webServer.on("/milligram.min.css.gz", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/milligram.min.css.gz", "text/css");
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
  if(var == "STATE"){
    
    return "ANYTHING";
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