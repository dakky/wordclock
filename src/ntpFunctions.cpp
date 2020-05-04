#include "ntpFunctions.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER_NAME, 3600, NTP_UPDATE_INTERVAL_MINS * 60 * 1000);


void setupNtpClient() {
    Serial.println("NTPClient: Initializing ...");
    timeClient.begin();
    Serial.println("NTPClient: Done ...");
}

void updateNtpClient() {
    timeClient.update();
    // settings system Time
    setTime(timeClient.getEpochTime());
} 