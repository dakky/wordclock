#ifndef _WIFIFUNCTIONS_H_
#define _WIFIFUNCTIONS_H_

#include "userconfig.h"

void setupWifi();
void resetWifi();
void wifimanagerConfigModeCallback(AsyncWiFiManager  *myWiFiManager);

#endif