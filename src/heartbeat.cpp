#include "heartbeat.h"

void setupHeartbeat() {
    #if HEARTBEAT_ENABLED
    Serial.println("Heartbeat: Initializing ...");
    pinMode(HEARTBEAT_PIN, OUTPUT);
    Serial.println("Heartbeat: Done ...");
    #endif
}

void heartbeatCallback() {
    #if HEARTBEAT_ENABLED
    debugD("The ghost in the machine is still alive.");
    digitalWrite(HEARTBEAT_PIN, !digitalRead(HEARTBEAT_PIN));
    #endif
}