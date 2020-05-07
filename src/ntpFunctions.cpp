#include "ntpFunctions.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER_NAME, 3600, NTP_UPDATE_INTERVAL_MINS * 60 * 1000);


void setupNtpClient() {
    debugI("NTPClient: Initializing ...");
    timeClient.begin();
    debugI("NTPClient: Done ...");
}

void updateNtpClient() {
    debugD("Getting time from NTP Server %s", NTP_SERVER_NAME);
    timeClient.update();
    // settings system Time
    Serial.print("NTPClient Callback: Setting time to: ");
    Serial.println(timeClient.getEpochTime());
    setTime(timeClient.getEpochTime());
} 