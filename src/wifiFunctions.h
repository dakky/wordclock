#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>  
#include <Arduino.h>

#ifndef _WIFIFUNCTIONS_H_
#define _WIFIFUNCTIONS_H_

#include "config.h"
#include "ledFunctions.h"
#include "words.h"

void setupWifi();
void wifimanagerConfigModeCallback(WiFiManager *myWiFiManager);

#endif