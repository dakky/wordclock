#define FASTLED_ESP8266_RAW_PIN_ORDER
#define _TASK_SLEEP_ON_IDLE_RUN

// no idea, why this cant be moved to globals.h :shrug:
#include <TaskScheduler.h>
#include "config.h"

/*
int current_mode;
struct config_t
{
    char wlan_essid[32];
    char wlan_key[64];
    char update_ip[15];
    int default_mode;
} conf;
*/

// Background Tasks and Scheduler
// ntp and updateTime are disabled, until OTA delay is finished ... just in case
Scheduler runner;
Task heartbeat(5000, TASK_FOREVER, &heartbeatCallback, &runner, true);

void setup() {
	// serial port
	Serial.begin(115200);
	Serial.println();
	Serial.println();
	Serial.println("ESP8266 WordClock setup() begin");

  setupWifi();
  setupTelnetDebugging();
  setupLeds();
  setupOTA();
  setupHeartbeat();
  setupNtpClock();

  //blankscreen(true);
//  EEPROM_read(0, conf);
//  current_mode = conf.default_mode;
  //blankscreen();
  //FastLED.show();
  Serial.println("Setup done.");
}

void loop() {
  ArduinoOTA.handle();        // Doing OTA stuff
  if (OTA_in_progress)        // if ota is in progress, skip the rest
		return;
  // otaStartDelay();

  Debug.handle();             // handle telnet connection
  events();                   // from ezTime.h: gets ntp time if nessesary
  runner.execute();           // run additionals tasks (heartbeat)
  timeToStripe();             // update LEDs
  yield();                    // keep esp WDT alive?
}