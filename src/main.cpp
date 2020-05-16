#define FASTLED_ESP8266_RAW_PIN_ORDER
#define _TASK_SLEEP_ON_IDLE_RUN

// no idea, why this cant be moved to globals.h :shrug:
#include <TaskScheduler.h>
#include "config.h"
#include "configuration.h"

// Background Tasks and Scheduler
// ntp and updateTime are disabled, until OTA delay is finished ... just in case
Scheduler runner;
Task heartbeat(5000, TASK_FOREVER, &heartbeatCallback, &runner, true);

void setup()
{
    // serial port
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println("ESP8266 WordClock setup() begin");

    setupWifi();
    Config.begin();
    setupTelnetDebugging();
    setupLeds();
    setupOTA();
    setupHeartbeat();
    setupNtpClock();
    setupWebserver();
    Serial.println("Setup done.");
}

void loop()
{
    ArduinoOTA.handle();   // Doing OTA stuff
    if (isOtaInProgress()) // if ota is in progress, skip the rest
        return;
    // otaStartDelay();

    Debug.handle(); // handle telnet connection
    events();         // from ezTime.h: gets ntp time if nessesary
    runner.execute(); // run additionals tasks (heartbeat)
    timeToStripe();   // update LEDs
    yield();          // keep esp WDT alive?
    FastLED.delay(50);
}