#ifndef UNIT_TEST

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
    delay(1000);   
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
    Debug.handle();
    events();         // from ezTime.h: gets ntp time if nessesary

    if (WordclockTime.isInSleeptime()) {
        LED.blankscreen();
        LED.fadeTargetToLive(); 
    } else {
        // update LEDs on the target array  (wanted state) to be lighted up
        EVERY_N_MILLISECONDS(1000 / FRAMES_PER_SECOND) 
        {
            WordclockTime.timeToStripe(); 
            // dimming to wanted state
            LED.fadeTargetToLive(); 
        }
    }

    // EVERY_N_SECONDS(1) {
    //     int array[] = {min_ONE[0], min_TWO[0], min_THREE[0], min_FOUR[0]};
    //     for (int i=0; i<4; i++) {
    //         debugD("word: %d", array[i]);
    //     }
    // }
}

#endif