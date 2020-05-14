// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  This is the ntp module. It basically only sets up the ntp client
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
#include "ntpFunctions.h"
#include "configuration.h"


//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
NtpFunctionsClass NTP = NtpFunctionsClass();

//---------------------------------------------------------------------------------------
// NtpFunctionsClass
//
// Constructor,
//
//---------------------------------------------------------------------------------------
NtpFunctionsClass::NtpFunctionsClass()
{
    Timezone clockTimezoned;
}

//---------------------------------------------------------------------------------------
// ~NtpFunctionsClass
//
// destructor
//
//---------------------------------------------------------------------------------------
NtpFunctionsClass::~NtpFunctionsClass()
{
}

//---------------------------------------------------------------------------------------
// begin
//
// Initializes the class and loads current configuration from config.json into class 
// members.
//
//---------------------------------------------------------------------------------------
void NtpFunctionsClass::begin()
{
    Serial.println("Setup NTPClock: Initializing ...");
    
    setInterval(60 * Config.ntpUpdateIntervalMinutes);
    setServer(Config.ntpServername);

    waitForSync();

    Serial.println("UTC: " + UTC.dateTime());
    //TODO: Location will only be set once ... will fix this when the webui is in place
    if (!this->clockTimezoned.setCache(0))
    {
        this->clockTimezoned.setLocation(Config.ntpTimezone);
    }
    Serial.println("Local time (" + this->clockTimezoned.getTimezoneName() + "): " + this->clockTimezoned.dateTime());

    Serial.println("Setup NTPClock: Done ...");
}

//---------------------------------------------------------------------------------------
// getHours
//
// Return hours of NTP clock
//
//---------------------------------------------------------------------------------------
uint8_t NtpFunctionsClass::getHours() 
{
    return this->clockTimezoned.hour();
}
//---------------------------------------------------------------------------------------
// getMinutes
//
// Return minutes of NTP clock
//
//---------------------------------------------------------------------------------------
uint8_t NtpFunctionsClass::getMinutes() 
{
    return this->clockTimezoned.minute();
}