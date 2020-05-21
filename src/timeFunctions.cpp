// Copyright (C) 2020 Robert, https://github.com/dakky
//
// This is the wirdclock timelogic module. 
// Its tasks is to assemble the words corresponding the actual time and
// handle them over to the ledFunctions
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

#include "timeFunctions.h"
#include "ledFunctions.h"
#include "telnetDebugging.h"
#include "words_layout2.h"

//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
TimefunctionsClass WordclockTime = TimefunctionsClass();

//---------------------------------------------------------------------------------------
// ConfigClass
//
// Constructor
//
//---------------------------------------------------------------------------------------
TimefunctionsClass::TimefunctionsClass()
{
}

//---------------------------------------------------------------------------------------
// ~ConfigClass
//
// destructor
//
//---------------------------------------------------------------------------------------
TimefunctionsClass::~TimefunctionsClass()
{
}


//---------------------------------------------------------------------------------------
// timeToStripe
//
// assembles the words for the actual time and pushes to the stripe
//
//---------------------------------------------------------------------------------------
void TimefunctionsClass::timeToStripe(){

    uint8_t hours = clockTimezoned.hour();
    uint8_t minutes = clockTimezoned.minute();

    this->timeToStripe(hours, minutes);
}

void TimefunctionsClass::timeToStripe(uint8_t hours, uint8_t minutes)
{
    // clearing stripe
    LED.blankscreen();
    LED.printDebugArray();

    // show "ES IST"
    LED.word2stripe(word_ES, sizeof(word_ES) / sizeof(int));
    LED.word2stripe(word_IST, sizeof(word_IST) / sizeof(int));

    if (minutes >= 5 && minutes < 10)
    {
        LED.word2stripe(word_FUENF1, sizeof(word_FUENF1) / sizeof(int));
        LED.word2stripe(word_NACH, sizeof(word_NACH) / sizeof(int));
    }
    else if (minutes >= 10 && minutes < 15)
    {
        LED.word2stripe(word_ZEHN1, sizeof(word_ZEHN1) / sizeof(int));
        LED.word2stripe(word_NACH, sizeof(word_NACH) / sizeof(int));
    }
    else if (minutes >= 15 && minutes < 20)
    {
        LED.word2stripe(word_VIERTEL, sizeof(word_VIERTEL) / sizeof(int));
        LED.word2stripe(word_NACH, sizeof(word_NACH) / sizeof(int));
    }
    else if (minutes >= 20 && minutes < 25)
    {
        LED.word2stripe(word_ZWANZIG, sizeof(word_ZWANZIG) / sizeof(int));
        LED.word2stripe(word_NACH, sizeof(word_NACH) / sizeof(int));
    }
    else if (minutes >= 25 && minutes < 30)
    {
        LED.word2stripe(word_FUENF1, sizeof(word_FUENF1) / sizeof(int));
        LED.word2stripe(word_VOR, sizeof(word_VOR) / sizeof(int));
        LED.word2stripe(word_HALB, sizeof(word_HALB) / sizeof(int));
    }
    else if (minutes >= 30 && minutes < 35)
    {
        LED.word2stripe(word_HALB, sizeof(word_HALB) / sizeof(int));
    }
    else if (minutes >= 35 && minutes < 40)
    {
        LED.word2stripe(word_FUENF1, sizeof(word_FUENF1) / sizeof(int));
        LED.word2stripe(word_NACH, sizeof(word_NACH) / sizeof(int));
        LED.word2stripe(word_HALB, sizeof(word_HALB) / sizeof(int));
    }
    else if (minutes >= 40 && minutes < 45)
    {
        LED.word2stripe(word_ZWANZIG, sizeof(word_ZWANZIG) / sizeof(int));
        LED.word2stripe(word_VOR, sizeof(word_VOR) / sizeof(int));
    }
    else if (minutes >= 45 && minutes < 50)
    {
        LED.word2stripe(word_VIERTEL, sizeof(word_VIERTEL) / sizeof(int));
        LED.word2stripe(word_VOR, sizeof(word_VOR) / sizeof(int));
    }
    else if (minutes >= 50 && minutes < 55)
    {
        LED.word2stripe(word_ZEHN1, sizeof(word_ZEHN1) / sizeof(int));
        LED.word2stripe(word_VOR, sizeof(word_VOR) / sizeof(int));
    }
    else if (minutes >= 55 && minutes < 60)
    {
        LED.word2stripe(word_FUENF1, sizeof(word_FUENF1) / sizeof(int));
        LED.word2stripe(word_VOR, sizeof(word_VOR) / sizeof(int));
    }

    int singleMinutes = minutes % 5;
    switch (singleMinutes)
    {
    case 1:
        LED.word2stripe(min_ONE, sizeof(min_ONE) / sizeof(int));
        break;
    case 2:
        LED.word2stripe(min_ONE, sizeof(min_ONE) / sizeof(int));
        LED.word2stripe(min_TWO, sizeof(min_TWO) / sizeof(int));
        break;
    case 3:
        LED.word2stripe(min_ONE, sizeof(min_ONE) / sizeof(int));
        LED.word2stripe(min_TWO, sizeof(min_TWO) / sizeof(int));
        LED.word2stripe(min_THREE, sizeof(min_THREE) / sizeof(int));
        break;
    case 4:
        LED.word2stripe(min_ONE, sizeof(min_ONE) / sizeof(int));
        LED.word2stripe(min_TWO, sizeof(min_TWO) / sizeof(int));
        LED.word2stripe(min_THREE, sizeof(min_THREE) / sizeof(int));
        LED.word2stripe(min_FOUR, sizeof(min_FOUR) / sizeof(int));
        break;
    }

    if (minutes >= 25)
    {
        hours++;
    }

    if (hours >= 12)
    {
        hours -= 12;
    }

    switch (hours)
    {
    case 0:
        LED.word2stripe(word_ZWOELF, sizeof(word_ZWOELF) / sizeof(int));
        break;
    case 1:
        if (minutes > 4)
        {
            LED.word2stripe(word_EINS, sizeof(word_EINS) / sizeof(int));
        }
        else
        {
            LED.word2stripe(word_EIN, sizeof(word_EIN) / sizeof(int));
        }
        break;
    case 2:
        LED.word2stripe(word_ZWEI, sizeof(word_ZWEI) / sizeof(int));
        break;
    case 3:
        LED.word2stripe(word_DREI, sizeof(word_DREI) / sizeof(int));
        break;
    case 4:
        LED.word2stripe(word_VIER, sizeof(word_VIER) / sizeof(int));
        break;
    case 5:
        LED.word2stripe(word_FUENF2, sizeof(word_FUENF2) / sizeof(int));
        break;
    case 6:
        LED.word2stripe(word_SECHS, sizeof(word_SECHS) / sizeof(int));
        break;
    case 7:
        LED.word2stripe(word_SIEBEN, sizeof(word_SIEBEN) / sizeof(int));
        break;
    case 8:
        LED.word2stripe(word_ACHT, sizeof(word_ACHT) / sizeof(int));
        break;
    case 9:
        LED.word2stripe(word_NEUN, sizeof(word_NEUN) / sizeof(int));
        break;
    case 10:
        LED.word2stripe(word_ZEHN2, sizeof(word_ZEHN2) / sizeof(int));
        break;
    case 11:
        LED.word2stripe(word_ELF, sizeof(word_ELF) / sizeof(int));
        break;
    }

    // show "UHR" if full hour
    if (minutes < 5)
    {
        LED.word2stripe(word_UHR, sizeof(word_UHR) / sizeof(int));
    }
    LED.printDebugArray();
}