#include "ntpFunctions.h"
#include "configuration.h"

Timezone clockTimezoned;

void setupNtpClock()
{
    Serial.println("Setup NTPClock: Initializing ...");

    setInterval(60 * Config.ntpUpdateIntervalMinutes);
    setServer(Config.ntpServername);

    waitForSync(10);

    Serial.println("UTC: " + UTC.dateTime());
    //TODO: Location will only be set once ... will fix this when the webui is in place
    if (!clockTimezoned.setCache(0))
    {
        clockTimezoned.setLocation(Config.ntpTimezone);
    }
    Serial.println("Local time (" + clockTimezoned.getTimezoneName() + "): " + clockTimezoned.dateTime());

    Serial.println("Setup NTPClock: Done ...");
}