#include "wifiFunctions.h"

AsyncWebServer webServer(80);
DNSServer dns;

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
    wifi_station_set_hostname(WIFI_WORDCLOCK_HOSTNAME);
    AsyncWiFiManager wifiManager(&webServer, &dns);
    // reset settings - for testing
    // wifiManager.resetSettings();
    wifiManager.setAPCallback(wifimanagerConfigModeCallback);
    wifiManager.setTimeout(60);
    if (!wifiManager.autoConnect("WordClock"))
    {
        Serial.println("Setup Wifi: Failed to connect, timeout");
        LED.word2stripe(word_WIFIMANAGER, CRGB::Red, true);
        delay(3000);
        ESP.reset();
    }
    Serial.println("Wifi: Connected successfully.");
    // MDNS Setup
    WiFi.hostname(WIFI_WORDCLOCK_HOSTNAME);
    if (MDNS.begin(WIFI_WORDCLOCK_HOSTNAME))
    {
        Serial.print("MDNS: MDNS responder started. Hostname -> ");
        Serial.println(WIFI_WORDCLOCK_HOSTNAME);
    }

    LED.word2stripe(word_WIFIMANAGER, CRGB::Green, true);
    delay(3000); // this function is called in setup only => delay is okay imho
}

//---------------------------------------------------------------------------------------
// wifimanagerConfigModeCallback
//
//  callback that gets called when connecting to previous WiFi fails
//  and WIFIManager enters Access Point mode
//---------------------------------------------------------------------------------------
void wifimanagerConfigModeCallback(AsyncWiFiManager *myWiFiManager)
{
    // show "wifimanager word (words.h)"
    LED.blankscreen(false);
    LED.word2stripe(word_WIFIMANAGER, CRGB::Yellow, true);
    Serial.println("Entered WIFIManager config mode");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());
}