#define FASTLED_ESP8266_RAW_PIN_ORDER
#define _TASK_SLEEP_ON_IDLE_RUN

#include <FastLED.h>
#include <TimeLib.h>
#include <TaskScheduler.h>
// #include <EEPROM.h>
#include "eeprom.h"
#include "timeFunctions.h"
#include "ntpFunctions.h"
#include "wifiFunctions.h"
#include "heartbeat.h"

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
Scheduler runner;
Task heartbeat(1000, TASK_FOREVER, &heartbeatCallback, &runner, true);
Task ntpsync(6000, TASK_FOREVER, &heartbeatCallback, &runner, true); 


void setup() {
	// serial port
	Serial.begin(115200);
	Serial.println();
	Serial.println();
	Serial.println("ESP8266 WordClock setup() begin");

  setupWifi();
  setupLeds();
  setupHeartbeat();
  setupNtpClient();
  updateNtpClient(); // explizit ntprun here in order to get a recent ntp time

  blankscreen(true);
//  EEPROM_read(0, conf);
//  current_mode = conf.default_mode;
  blankscreen();
  FastLED.show();
  Serial.println("Setup done.");
}

void loop() {
  runner.execute();


  //blankscreen();                    // all pixels to black
  //timeToStripe(hour(),minute());    // calculate time and fill leds array
  //FastLED.show();                   // show it on the matix
  //delay(500);                       // wait half a second
}