#include "heartbeat.h"

void setupHeartbeat() {
    #if HEARTBEAT_ENABLED
    debugI("Heartbeat: Initializing ...");
    pinMode(HEARTBEAT_PIN, OUTPUT);
    debugI("Heartbeat: Done ...");
    #endif
}

void heartbeatCallback() {
    #if HEARTBEAT_ENABLED
    digitalWrite(HEARTBEAT_PIN, !digitalRead(HEARTBEAT_PIN));
    #endif
}