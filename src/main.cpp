#define FASTLED_ESP8266_RAW_PIN_ORDER
#define _TASK_SLEEP_ON_IDLE_RUN

// no idea, why this cant be moved to globals.h :shrug:
#include <TaskScheduler.h>
#include <FastLED.h>
#include "userconfig.h"
#include "configuration.h"
#include "timeFunctions.h"

#define FRAMES_PER_SECOND 20

long timercounter=0;

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
    Debug.handle();
    events();         // from ezTime.h: gets ntp time if nessesary
    WordclockTime.timeToStripe(); // update LEDs on the target array to be lighted up
    LED.fadeTargetToLive(25); // has to be done here, if called in i.e. timeToStripe it takes to long and the esp crashes
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    if (millis() - timercounter > 1000) {
        bool result=WordclockTime.isInSleeptime();
        debugI("checked sleep, result is %d", result);
        timercounter=millis();
    }
}