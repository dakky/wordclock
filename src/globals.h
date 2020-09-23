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
#include <ArduinoOTA.h>


// project deps
#include "words_layout.h"

#include "ledFunctions.h"
#include "timeFunctions.h"
#include "ntpFunctions.h"
#include "wifiFunctions.h"
#include "otaFunctions.h"
#include "webserver.h"


extern int updateCountdown;
extern Timezone clockTimezoned;
extern AsyncWebServer webServer;

#endif