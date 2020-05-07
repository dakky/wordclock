#include "ntpFunctions.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER_NAME, 3600, NTP_UPDATE_INTERVAL_MINS * 60 * 1000);


void setupNtpClient() {
    Serial.println("NTPClient: Initializing ...");
    timeClient.begin();
    Serial.println("NTPClient: Done ...");
}

void updateNtpClient() {
    debugD("Getting time from NTP Server %s", NTP_SERVER_NAME);
    timeClient.update();
    // settings system Time
    debugD("NTPClient Callback: Setting time to: %lu", timeClient.getEpochTime());
    setTime(timeClient.getEpochTime());
} 