#include "wifiFunctions.h"

AsyncWebServer webServer(80);
DNSServer dns;
AsyncWiFiManager wifiManager(&webServer, &dns);


//---------------------------------------------------------------------------------------
// setupWifi
//
//  Setup of Wifi with WifiManager
//
// ->
// <- --
//---------------------------------------------------------------------------------------
void setupWifi()
{
    // WiFi Setup
    Serial.println("Setup Wifi: Initializing ...");
    wifi_station_set_hostname(Config.getHostname());

    wifiManager.setAPCallback(wifimanagerConfigModeCallback);
    wifiManager.setTimeout(60);
    if (!wifiManager.autoConnect("WordClock"))
    {
        Serial.println("Setup Wifi: Failed to connect, timeout");
        LED.updatesBlocked(false);
        LED.word2stripe(word_QUESTIONMARK, sizeof(word_QUESTIONMARK) / sizeof(int), CRGB::Red);
        LED.updatesBlocked(true);
        LED.fadeTargetToLive();
        delay(3000);
        ESP.reset();
    }
    Serial.println("Wifi: Connected successfully.");
    // MDNS Setup
    WiFi.hostname(Config.getHostname());
    if (MDNS.begin(Config.getHostname()))
    {
        Serial.print("MDNS: MDNS responder started. Hostname -> ");
        Serial.println(Config.getHostname());
    }

    LED.updatesBlocked(false);
    LED.word2stripe(word_QUESTIONMARK, sizeof(word_QUESTIONMARK) / sizeof(int), CRGB::Green);
    LED.updatesBlocked(true);
    LED.fadeTargetToLive();
    delay(3000); // this function is called in setup only => delay is okay imho
    LED.updatesBlocked(false);
}

//---------------------------------------------------------------------------------------
// wifimanagerConfigModeCallback
//
//  callback that gets called when connecting to previous WiFi fails
//  and WIFIManager enters Access Point mode
//---------------------------------------------------------------------------------------
void wifimanagerConfigModeCallback(AsyncWiFiManager *myWiFiManager)
{
    LED.updatesBlocked(false);
    LED.blankscreen();
    LED.word2stripe(word_QUESTIONMARK, sizeof(word_QUESTIONMARK) / sizeof(int), CRGB::Yellow);
    LED.updatesBlocked(true);
    LED.fadeTargetToLive();
    Serial.println("Entered WIFIManager config mode");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());
}

void resetWifi() {
    // reset settings - for testing
    wifiManager.resetSettings();
    ESP.reset();
}2