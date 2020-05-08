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
#include <NTPClient.h>
#include <TimeLib.h>
#include <RemoteDebug.h>
#include <ArduinoOTA.h>

// project deps
#include "words.h"
#include "ledFunctions.h"
#include "timeFunctions.h"
#include "ntpFunctions.h"
#include "wifiFunctions.h"
#include "heartbeat.h"
#include "telnetDebugging.h"
#include "otaFunctions.h"
// #include <EEPROM.h>
// #include "eeprom.h"

extern RemoteDebug Debug;
extern int OTA_in_progress;
extern int updateCountdown;

#endif