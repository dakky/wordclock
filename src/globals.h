#ifndef _GLOBALS_H
#define _GLOBALS_H

// 3d party
#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ezTime.h>
#include <RemoteDebug.h>
#include <ArduinoOTA.h>


// project deps
// SETUP: chose frontplate layout here:
//#include "words_layout1.h"
#include "words_layout2.h"

#include "ledFunction.h"
#include "timeFunctions.h"
#include "ntpFunctions.h"
#include "wifiFunctions.h"
#include "heartbeat.h"
#include "telnetDebugging.h"
#include "otaFunctions.h"
#include "webserver.h"
#include "configuration.h"


extern RemoteDebug Debug;
extern int updateCountdown;
extern Timezone clockTimezoned;
extern AsyncWebServer webServer;

#endif