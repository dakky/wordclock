// ESP8266 Wordclock
// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  See configuration.cpp for description.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <ArduinoJson.h>
#include <FS.h>
#include "userconfig.h"

// Oject keeping the configuration
typedef struct _config_struct
{
    int  ledBrightness;
    char ledSimpleColor[9];
    byte ledRainbowSpeed;
    byte ledMode;
    char ntpServername[25];
    char ntpTimezone[25];
    char hostname[25];
    int  startSleeptimeHour;
    int  startSleeptimeMinute;
    int  endSleeptimeHour;
    int  endSleeptimeMinute;
} config_struct;

class ConfigClass
{
public:
    ConfigClass();
    ~ConfigClass();
    void begin();
    void save();
    void load();
    void reset();
    void print();

    // setter and getter
    int   getLedBrightness();
    void  setLedBrightness(int);
    byte  getLedMode();
    void  setLedMode(byte);
    char* getLedSimpleColor();
    void  setLedSimpleColor(char*,int);
    byte  getLedRainbowSpeed();
    void  setLedRainbowSpeed(byte);
    char* getNtpServername();
    void  setNtpServername(char*,int);
    char* getNtpTimezone();
    void  setNtpTimezone(char*,int);
    char* getHostname();
    void  setHostname(char*,int);
    void  setStartSleeptime(char*,int);
    int   getStartSleeptimeHour();
    int   getStartSleeptimeMinute();
    void  setEndSleeptime(char*,int);
    int   getEndSleeptimeHour();
    int   getEndSleeptimeMinute();

private:
    void resetAndRestart();

    // copy of config.json content
    config_struct *config = new config_struct();
    const char *filename = "/config.json";
};

extern ConfigClass Config;

#endif