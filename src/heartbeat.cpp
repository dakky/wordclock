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
    digitalWrite(HEARTBEAT_PIN, !digitalRead(HEARTBEAT_PIN));
    #endif
}