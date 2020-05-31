#ifndef _WIFIFUNCTIONS_H_
#define _WIFIFUNCTIONS_H_

#include "config.h"

void setupWifi();
void resetWifi();
void wifimanagerConfigModeCallback(AsyncWiFiManager  *myWiFiManager);

#endif