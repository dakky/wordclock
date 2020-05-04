#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#ifndef _NTPFUNCTIONS_H_
#define _NTPFUNCTIONS_H_

#include "config.h"

void setupNtpClient();
void updateNtpClient();

#endif