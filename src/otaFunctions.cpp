#include "otaFunctions.h"

int OTA_in_progress = 0;
int updateCountdown = OTA_STARTUP_DELAY;
//---------------------------------------------------------------------------------------
// setupOTA
//
//  Setup of OTA with WifiManager
//
// ->
// Telnetserver won't be executed when OTA is set up/running => no telnet debuggung here
// but plain old Serial
// <- --
//---------------------------------------------------------------------------------------
void setupOTA() {
    // OTA update
    Serial.println("Setup OTA: Initializing ...");
    ArduinoOTA.setPort(8266);
    ArduinoOTA.setHostname(WIFI_WORDCLOCK_HOSTNAME);
    //ArduinoOTA.setPassword((const char *)"123");
    ArduinoOTA.onStart([]()
    {
        // Config.updateProgress = 0;
        OTA_in_progress = 1;
        Serial.println("OTA Start");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        blankscreen();
        word2stripe(word_OTAPROGRESS,sizeof(word_OTAPROGRESS)/sizeof(int), CRGB::Yellow);
        FastLED.show();
        //Config.updateProgress = progress * 110 / total;
        Serial.printf("OTA Progress: %u%%\r\n", (progress / (total / 100)));
    });

    ArduinoOTA.onEnd([]()
    {
        blankscreen();
        word2stripe(word_OTASUCCESS,sizeof(word_OTASUCCESS)/sizeof(int), CRGB::Green);
        FastLED.show();
        Serial.println("\nOTA End");
    });

    ArduinoOTA.onError([](ota_error_t error)
    {
        blankscreen();
        word2stripe(word_OTAERROR,sizeof(word_OTAERROR)/sizeof(int), CRGB::Red);
        FastLED.show();
        Serial.printf("OTA Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("Setup OTA: Done ...");
}
    
void otaStartDelay() {
    // show the hourglass animation with green corners for the first 2.5 seconds
	// after boot to be able to reflash with OTA during that time window if
	// the firmware hangs afterwards
	if(updateCountdown)
	{
		blankscreen();
        word2stripe(word_HOURGLASS,sizeof(word_HOURGLASS)/sizeof(int), CRGB::Green);
		Serial.print(".");
		delay(100);
		updateCountdown--;
		if(updateCountdown == 0)
		{
			// wenn das startdelay fuer OTA vorbei ist, einfach weiter im text
            blankscreen();
		}
		return;
	}
}