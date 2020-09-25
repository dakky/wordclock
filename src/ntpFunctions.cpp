#include "ntpFunctions.h"
#include "configuration.h"

Timezone clockTimezoned;

void setupNtpClock()
{
    Serial.println("setupNtpClock: Initializing ...");

    Serial.printf("setupNtpClock: Settings NTP server to: %s", Config.getNtpServername());
    
    setServer(Config.getNtpServername());

    int attemptCnt = 1;
    while (!waitForSync(10))
    {
        attemptCnt++;
        Serial.println("setupNtpClock: NTP Sync retrying...");
        if (attemptCnt == 3)
        {
            updateNTP();
            break;
        }
    }

    Serial.println("setupNtpClock: UTC: " + UTC.dateTime());
    //TODO: Location will only be set once ... will fix this when the webui is in place
    if (!clockTimezoned.setCache(0))
    {
        clockTimezoned.setLocation(Config.getNtpTimezone());
    }
    Serial.println("setupNtpClock: Local time (" + clockTimezoned.getTimezoneName() + "): " + clockTimezoned.dateTime());

    Serial.println("setupNtpClock: Done ...");
}