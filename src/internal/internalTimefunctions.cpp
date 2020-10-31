// Copyright (C) 2020 Robert, https://github.com/dakky
//
// This is an internal helper function. Its seperated from the arduino code, 
// so i can be tested.
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

#include "internalTimefunctions.h"

//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
InternalTimefunctionsClass InternalTimefunctions = InternalTimefunctionsClass();

//---------------------------------------------------------------------------------------
// InternalTimefunctionsClass
//
// Constructor
//
//---------------------------------------------------------------------------------------
InternalTimefunctionsClass::InternalTimefunctionsClass()
{
}

//---------------------------------------------------------------------------------------
// ~InternalTimefunctionsClass
//
// destructor
//
//---------------------------------------------------------------------------------------
InternalTimefunctionsClass::~InternalTimefunctionsClass()
{
}

//---------------------------------------------------------------------------------------
// isInSleeptime
// returns true, if given time is between start and end sleeptime
//---------------------------------------------------------------------------------------
bool InternalTimefunctionsClass::isInSleeptime(uint8_t hours, uint8_t minutes, uint8_t startHour, uint8_t startMinute, uint8_t endHour, uint8_t endMinute)
{
    bool result = false;

    // over midnight
    if (startHour > endHour) {
        if (hours >= startHour && minutes >= startMinute)
        {
            if (hours <= 23) 
            {
                if (minutes <= 59) {
                    result = true; 
                }
            }
        } 
        else if (hours >= 0 && minutes >= 0)
        {
            if (hours <= endHour) 
            {
                if(minutes <= endMinute){
                    result = true; 
                }
            }
        }
    }
    else
    {
        // same days start and end time
        // if hours between start and end hour
        if (hours > startHour && hours < endHour)
        {
            result = true;
        } 
        // compare minutes if hours match start or end
        else if (hours == startHour)
        {
            if (minutes >= startMinute) {
                result = true; 
            }
        }
        else if (hours == endHour)
        {
            if (minutes <= endMinute) {
                result = true; 
            }
        }
    }

    return result;
}