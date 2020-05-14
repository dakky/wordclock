// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  This is the OTA module. It handles all OTA centric tasks
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

#include <Arduino.h>
#include <ArduinoOTA.h>
#include "otaFunctions.h"
#include "configuration.h"
#include "ledFunction.h"
#include "words_layout2.h"

//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
OtaFunctionsClass OTA = OtaFunctionsClass();

//---------------------------------------------------------------------------------------
// OtaFunctionsClass
//
// Constructor, loads default values
//
//---------------------------------------------------------------------------------------
OtaFunctionsClass::OtaFunctionsClass()
{
}

//---------------------------------------------------------------------------------------
// ~OtaFunctionsClass
//
// destructor
//
//---------------------------------------------------------------------------------------
OtaFunctionsClass::~OtaFunctionsClass()
{
}

//---------------------------------------------------------------------------------------
// begin
//
// Setup of OTA with WifiManager
//
// Telnetserver won't be executed when OTA is set up/running => no telnet debuggung here
// but plain old Serial
//---------------------------------------------------------------------------------------
void OtaFunctionsClass::begin()
{
    // OTA update
    Serial.println("Setup OTA: Initializing ...");
    ArduinoOTA.setPort(8266);
    ArduinoOTA.setHostname(Config.hostname);
    //ArduinoOTA.setPassword((const char *)"123");
    ArduinoOTA.onStart([this]() {
        this->OTAinProgress = true;
        Serial.println("OTA Start");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        LED.blankscreen(false);
        LED.word2stripe(word_OTAPROGRESS, CRGB::Yellow, true);
        //Config.updateProgress = progress * 110 / total;
        Serial.printf("OTA Progress: %u%%\r\n", (progress / (total / 100)));
    });

    ArduinoOTA.onEnd([]() {
        LED.blankscreen(false);
        LED.word2stripe(word_OTASUCCESS, CRGB::Green, true);
        Serial.println("\nOTA End");
    });

    ArduinoOTA.onError([](ota_error_t error) {
        LED.blankscreen(false);
        LED.word2stripe(word_OTAERROR, CRGB::Red, true);
        Serial.printf("OTA Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
            Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
            Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
            Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
            Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR)
            Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("Setup OTA: Done ...");
}

void OtaFunctionsClass::handle()
{
    ArduinoOTA.handle(); // Doing OTA stuff
}

//---------------------------------------------------------------------------------------
// isRunning
//
// Reports if OTA is in progress
//
//---------------------------------------------------------------------------------------
bool OtaFunctionsClass::isRunning()
{
    return this->OTAinProgress;
}