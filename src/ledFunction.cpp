// ESP8266 Wordclock
// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  Controls LED stripe
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

#include "ledFunction.h"
#include "telnetDebugging.h"


//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
LedFunctionClass LED = LedFunctionClass();

//---------------------------------------------------------------------------------------
// LedFunctionClass
//
// Constructor
//
//---------------------------------------------------------------------------------------
LedFunctionClass::LedFunctionClass()
{
}

//---------------------------------------------------------------------------------------
// ~LedFunctionClass
//
// destructor
//
//---------------------------------------------------------------------------------------
LedFunctionClass::~LedFunctionClass()
{
}

//---------------------------------------------------------------------------------------
// begin
//
// initilizes FastLED and the led stripe
//
// Params:
// 1. words to light up
// 2. should the display be updated immediately (true/false)
//---------------------------------------------------------------------------------------
void LedFunctionClass::begin()
{
    Serial.println("Setup LEDs: Initializing ...");
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    Serial.println("Setup LEDs: Done ...");
}

//---------------------------------------------------------------------------------------
// word2stripe
//
// Pushes words to stripe array
//
// Params:
// 1. words to light up
// 2. color, which should ne used
// 3. should the display be updated immediately (true/false)
//---------------------------------------------------------------------------------------
void LedFunctionClass::word2stripe(const int word[], CRGB color, bool commit)
{
    int len = sizeof(word) / sizeof(int);

    FastLED.setBrightness(Config.ledBrightness);

    for (int letter = 0; letter < len; letter++)
    {
        this->leds[word[letter]] = color;
    }

    if (commit)
    {
        FastLED.show();
    }
}

//---------------------------------------------------------------------------------------
// blankscreen
//
// set all LEDs to black
//
// Params:
// . should the display be updated immediately (true/false)
//---------------------------------------------------------------------------------------
void LedFunctionClass::blankscreen(bool commit)
{
    CRGB color = CRGB::Black;

    for (int led = 0; led < NUM_LEDS; led++)
    {
        leds[led] = color;
        if (commit)
        {
            FastLED.show();
        }
    }
}

//---------------------------------------------------------------------------------------
// showWords
//
// simply show all words
//
//---------------------------------------------------------------------------------------
void LedFunctionClass::showWords()
{
    FastLED.show();
}