#ifndef _GLOBALS_H
#define _GLOBALS_H

// 3d party
#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ezTime.h>
#include <RemoteDebug.h>
#include <ArduinoOTA.h>
// #include <EEPROM.h>
// #include <ESP8266WebServer.h>
// #include <FS.h>

// project deps
// SETUP: chose frontplate layout here:
//#include "words_layout1.h"
#include "words_layout2.h"

#include "ledFunctions.h"
#include "timeFunctions.h"
#include "ntpFunctions.h"
#include "wifiFunctions.h"
#include "heartbeat.h"
#include "telnetDebugging.h"
#include "otaFunctions.h"
#include "webserver.h"


extern RemoteDebug Debug;
extern int updateCountdown;
extern Timezone clockTimezoned;
extern ESP8266WebServer webServer;

#endif