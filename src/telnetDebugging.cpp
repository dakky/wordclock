#include "telnetDebugging.h"

RemoteDebug Debug;

void setupTelnetDebugging()
{
    Serial.println("Setup Telnet Debug: Initializing ...");
    MDNS.addService("telnet", "tcp", 23);
    Debug.begin(WIFI_WORDCLOCK_HOSTNAME);
    Debug.setResetCmdEnabled(true); // Enable the reset command
    Debug.showProfiler(false);      // Profiler (Good to measure times, to optimize codes)
    Debug.showColors(true);         // Colors
    // Debug.setSerialEnabled(true);  // if you wants serial echo - only recommended if ESP is plugged in USB

    Serial.println("Setup Telnet Debug: Done ...");
}
