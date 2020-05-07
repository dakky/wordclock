#include "heartbeat.h"

void setupHeartbeat() {
    #if HEARTBEAT_ENABLED
    Serial.println("Setup Heartbeat: Initializing ...");
    pinMode(HEARTBEAT_PIN, OUTPUT);
    Serial.println("Setup Heartbeat: Done ...");
    #endif
}

void heartbeatCallback() {
    #if HEARTBEAT_ENABLED
    Serial.println("Callback Heartbeat: Triggered ...");
    digitalWrite(HEARTBEAT_PIN, !digitalRead(HEARTBEAT_PIN));
    #endif
}