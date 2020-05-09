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
Task ntpsync(NTP_UPDATE_INTERVAL_MINS * 60 * 1000, TASK_FOREVER, &updateNtpClient, &runner, true);
Task updateTime(1000, TASK_FOREVER, &timeToStripe , &runner, true );

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
  setupNtpClient();

  //blankscreen(true);
//  EEPROM_read(0, conf);
//  current_mode = conf.default_mode;
  //blankscreen();
  //FastLED.show();
  Serial.println("Setup done.");
}

void loop() {

  ArduinoOTA.handle();

  // if ota is in progress, skip the rest
  if (OTA_in_progress)
		return;

  // otaStartDelay();
  Debug.handle();
  runner.execute();
  
  // keep esp WDT alive?
  yield();


  blankscreen();                    // all pixels to black
  // timeToStripe();    // calculate time and fill leds array
  //FastLED.show();                   // show it on the matix
  //delay(500);                       // wait half a second
}