// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  This is the heartbeat module. It flashes the onboard LED if enabled
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

#include "heartbeat.h"
#include "configuration.h"
#include "telnetDebugging.h"

//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
HeartbeatClass Heartbeat = HeartbeatClass();

//---------------------------------------------------------------------------------------
// ConfigClass
//
// Constructor
//
//---------------------------------------------------------------------------------------
HeartbeatClass::HeartbeatClass()
{
}

//---------------------------------------------------------------------------------------
// ~ConfigClass
//
// destructor
//
//---------------------------------------------------------------------------------------
HeartbeatClass::~HeartbeatClass()
{
}

//---------------------------------------------------------------------------------------
// begin
//
// configures the LED pinout
//
//---------------------------------------------------------------------------------------
void HeartbeatClass::begin()
{
    if (Config.heartbeatEnabled)
    {
        Serial.println("Heartbeat: Initializing ...");
        pinMode(HEARTBEAT_PIN, OUTPUT);
        Serial.println("Heartbeat: Done ...");
    }
}

void heartbeatCallback()
{
    if (Config.heartbeatEnabled)
    {
        debugD("The ghost in the machine is still alive.");
        digitalWrite(HEARTBEAT_PIN, !digitalRead(HEARTBEAT_PIN));
    }
}