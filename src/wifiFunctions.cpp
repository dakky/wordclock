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
        word2stripe(word_WIFIMANAGER, sizeof(word_WIFIMANAGER) / sizeof(int), CRGB::Red);
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

    word2stripe(word_WIFIMANAGER, sizeof(word_WIFIMANAGER) / sizeof(int), CRGB::Green);
    FastLED.show();
    delay(3000); // this function is called in setup only => delay is okay imho
    blankscreen(true);
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
    blankscreen();
    word2stripe(word_WIFIMANAGER, sizeof(word_WIFIMANAGER) / sizeof(int), CRGB::Yellow);
    FastLED.show();
    Serial.println("Entered WIFIManager config mode");
    Serial.println(WiFi.softAPIP());
    Serial.println(myWiFiManager->getConfigPortalSSID());
}