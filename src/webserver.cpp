#include "webserver.h"

ESP8266WebServer webServer(80);

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
    webServer.on("/", webserverHandleRoot);
    // webserver.on("/getADC",handleADC); //Reads ADC function is called from out index.html
    webServer.onNotFound(webserverHandleWebRequests);
    webServer.begin();
    Serial.println("Setup Webserver: Done ...");
}

//---------------------------------------------------------------------------------------
// webserverHandleRoot
//
// handles / requests of webserver
// simple redirect to index.html
//
//---------------------------------------------------------------------------------------
void webserverHandleRoot()
{
    webServer.sendHeader("Location", "/index.html", true);
    webServer.send(302, "text/plain", "");
    debugD("Got http request on '/'. Redirecting to /index.html.");
}

//---------------------------------------------------------------------------------------
// webserverHandleRoot
//
// handles any other  requests of webserver
// if there is a matching file in the data folder/SPIFFS,
// deliver it, otherwise return HTTP 404
//
//---------------------------------------------------------------------------------------
void webserverHandleWebRequests()
{
    if (webserverLoadFromSpiffs(webServer.uri()))
        return;
    debugE("File not found in SPIFFS");
    String message = "File Not Detected\n\n";
    message += "URI: ";
    message += webServer.uri();
    message += "\nMethod: ";
    message += (webServer.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += webServer.args();
    message += "\n";
    for (uint8_t i = 0; i < webServer.args(); i++)
    {
        message += " NAME:" + webServer.argName(i) + "\n VALUE:" + webServer.arg(i) + "\n";
    }
    webServer.send(404, "text/plain", message);
}

//---------------------------------------------------------------------------------------
// webserverLoadFromSpiffs
//
// reads files from SPIFFS and configures matching mimeType
//
//---------------------------------------------------------------------------------------
bool webserverLoadFromSpiffs(String path)
{
    String dataType = "text/plain";

    if (path.endsWith("/"))
        path += "index.html";

    if (path.endsWith(".src"))
        path = path.substring(0, path.lastIndexOf("."));
    else if (path.endsWith(".html"))
        dataType = "text/html";
    else if (path.endsWith(".css"))
        dataType = "text/css";
    else if (path.endsWith(".css.gz"))
        dataType = "text/css";
    else if (path.endsWith(".js"))
        dataType = "application/javascript";
    else if (path.endsWith(".png"))
        dataType = "image/png";
    else if (path.endsWith(".gif"))
        dataType = "image/gif";
    else if (path.endsWith(".jpg"))
        dataType = "image/jpeg";
    else if (path.endsWith(".ico"))
        dataType = "image/x-icon";
    else if (path.endsWith(".zip"))
        dataType = "application/zip";

    if (webServer.hasArg("download"))
        dataType = "application/octet-stream";
    
    // in case files are existing in compressed form, use them
    String pathWithGz = path + ".gz";
    if (SPIFFS.exists(pathWithGz)) path = pathWithGz;

    if (SPIFFS.exists(path)) {
        File file = SPIFFS.open(path, "r");
        webServer.streamFile(file, dataType);
        file.close();
        return true;
    }
    debugE("something went wrong with the SPIFFS files ...");
    return false; // file does not exist in spiffs
}
