#include "ntpFunctions.h"
#include "configuration.h"

Timezone clockTimezoned;

void setupNtpClock()
{
    Serial.println("Setup NTPClock: Initializing ...");

    debugI("Settings NTP server to: %s", Config.getNtpServername());
    setServer(Config.getNtpServername());

    int attemptCnt = 1;
    while (!waitForSync(10))
    {
        attemptCnt++;
        Serial.println("NTP Sync: retrying...");
        LED.blankscreen();
        LED.word2stripe(word_OTAERROR, sizeof(word_OTAERROR) / sizeof(int), CRGB::Red);
        FastLED.show();
        if (attemptCnt == 3)
        {
            updateNTP();
            break;
        }
    }

    Serial.println("UTC: " + UTC.dateTime());
    //TODO: Location will only be set once ... will fix this when the webui is in place
    if (!clockTimezoned.setCache(0))
    {
        clockTimezoned.setLocation(Config.getNtpTimezone());
    }
    Serial.println("Local time (" + clockTimezoned.getTimezoneName() + "): " + clockTimezoned.dateTime());

    Serial.println("Setup NTPClock: Done ...");
}