#include "ntpFunctions.h"

Timezone clockTimezoned;

void setupNtpClock() {
    Serial.println("Setup NTPClock: Initializing ...");
    
    setInterval(60 * NTP_UPDATE_INTERVAL_MINS);
    setServer(NTP_SERVER_NAME);

    waitForSync();

	Serial.println("UTC: " + UTC.dateTime());
	
    //TODO: Location will only be set once ... will fix this when the webui is in place
	if (!clockTimezoned.setCache(0)) 
    {
        clockTimezoned.setLocation(NTP_TIMEZONE);
    }
    
	Serial.println("Local time (" + clockTimezoned.getTimezoneName() +"): " + clockTimezoned.dateTime());
    
    Serial.println("Setup NTPClock: Done ...");
}