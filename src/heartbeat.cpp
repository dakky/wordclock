#include "heartbeat.h"
#include "configuration.h"

void setupHeartbeat()
{
    if (Config.heartbeatEnabled)
    {
        Serial.println("Heartbeat: Initializing ...");
        pinMode(HEARTBEAT_PIN, OUTPUT);
        Serial.println("Heartbeat: Done ...");
    }
}

void heartbeatCallback()
{
    if (Config.heartbeatEnabled)
    {
        debugD("The ghost in the machine is still alive.");
        digitalWrite(HEARTBEAT_PIN, !digitalRead(HEARTBEAT_PIN));
    }
}