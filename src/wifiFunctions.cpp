#include "wifiFunctions.h"

//---------------------------------------------------------------------------------------
// setupWifi
//
//  Setup of Wifi with WifiManager
//
// ->
// <- --
//---------------------------------------------------------------------------------------
void setupWifi() {
    // WiFi Setup 
	Serial.println("Wifi: Initializing ...");
    wifi_station_set_hostname(WIFI_WORDCLOCK_HOSTNAME);
	WiFiManager wifiManager;
	wifiManager.setAPCallback(wifimanagerConfigModeCallback);
	if (!wifiManager.autoConnect("WordClock"))
	{
		Serial.println("Wifi: Failed to connect, timeout");
		word2stripe(word_WIFIMANAGER,sizeof(word_WIFIMANAGER)/sizeof(int), CRGB::Red);
		delay(3000);
		ESP.reset();
	}
    Serial.println("Wifi: Connected successfully.");
    word2stripe(word_WIFIMANAGER,sizeof(word_WIFIMANAGER)/sizeof(int), CRGB::Green);
    FastLED.show();
	delay(3000); // this function is called in setup only => delay is okay imho
	blankscreen(true);
}

//---------------------------------------------------------------------------------------
// wifimanagerConfigModeCallback
//
//  callback that gets called when connecting to previous WiFi fails
//  and WIFIManager enters Access Point mode
//
// ->
// <- --
//---------------------------------------------------------------------------------------
void wifimanagerConfigModeCallback(WiFiManager *myWiFiManager)
{
    // show "wifimanager word (words.h)"
    word2stripe(word_WIFIMANAGER,sizeof(word_WIFIMANAGER)/sizeof(int), CRGB::Yellow);
    FastLED.show();
	Serial.println("Entered WIFIManager config mode");
	Serial.println(WiFi.softAPIP());
	Serial.println(myWiFiManager->getConfigPortalSSID());
}