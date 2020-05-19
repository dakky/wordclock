// ESP8266 Wordclock
// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  Controls LED stripe
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or// (at your option) any later version.//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "ledFunctions.h"
#include "telnetDebugging.h"

//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
LedFunctionsClass LED = LedFunctionsClass();

//---------------------------------------------------------------------------------------
// LedFunctionsClass
//
// Constructor
//
//---------------------------------------------------------------------------------------

LedFunctionsClass::LedFunctionsClass()
{
}

//---------------------------------------------------------------------------------------
// ~LedFunctionsClass
//
// destructor
//
//---------------------------------------------------------------------------------------
LedFunctionsClass::~LedFunctionsClass()
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
void LedFunctionsClass::begin()
{
    Serial.println("Setup LEDs: Initializing ...");
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    Serial.println("Setup LEDs: Done ...");
}

//---------------------------------------------------------------------------------------
// word2stripe
//
// Pushes words to stripe array, with static color
// will be used mostly for special words (see words*.h)
//
// Params:
// 1. words to light up
// 2. length of word array
// 2. should the display be updated immediately (true/false)
// 3. color, which should ne used (optional)
//---------------------------------------------------------------------------------------
void LedFunctionsClass::word2stripe(const int word[], int len, CRGB color)
{
    FastLED.setBrightness(Config.getLedBrightness());

    for (int letter = 0; letter < len; letter++)
    {
        this->leds[word[letter]] = color;
    }
}

void LedFunctionsClass::word2stripe(const int word[], int len)
{

    // detect mode:
    // Singlecolor = 1
    // Rainbow = 2
    FastLED.setBrightness(Config.getLedBrightness());

    long currentSimpleColor;

    if (Config.getLedMode() == 2)
    {
        currentPalette = RainbowColors_p;
        currentBlending = LINEARBLEND;
    } else {
        currentSimpleColor = strtol(Config.getLedSimpleColor(),NULL,0);
    }


    for (int letter = 0; letter < len; letter++)
    {
        this->leds[word[letter]] = currentSimpleColor;
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
void LedFunctionsClass::blankscreen()
{
    CRGB color = CRGB::Black;

    for (int led = 0; led < NUM_LEDS; led++)
    {
        leds[led] = color;
    }
}

//---------------------------------------------------------------------------------------
// showWords
//
// simply show all words
//
//---------------------------------------------------------------------------------------
void LedFunctionsClass::showWords()
{
    FastLED.show();
}