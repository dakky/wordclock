#define FASTLED_ESP8266_RAW_PIN_ORDER
#define _TASK_SLEEP_ON_IDLE_RUN

// no idea, why this cant be moved to globals.h :shrug:
#include <TaskScheduler.h>
#include <FastLED.h>
#include "config.h"
#include "configuration.h"
#include "timeFunctions.h"

// Background Tasks and Scheduler
// ntp and updateTime are disabled, until OTA delay is finished ... just in case
Scheduler runner;
Task heartbeat(5000, TASK_FOREVER, &heartbeatCallback, &runner, true);

#define FRAMES_PER_SECOND 20

void setup()
{
    // serial port
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println("ESP8266 WordClock setup() begin");

    Config.begin();
    setupWifi();
    setupTelnetDebugging();
    LED.begin();
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

    Debug.handle();   // handle telnet connection
    events();         // from ezTime.h: gets ntp time if nessesary
    runner.execute(); // run additionals tasks (heartbeat)
    WordclockTime.timeToStripe(); // update LEDs on the target array to be lighted up
    // has to be done here, if called in i.e. timeToStripe it takes to long and the esp crashes
    LED.fadeTargetToLive(25); 
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}