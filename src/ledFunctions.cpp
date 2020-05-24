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
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds_live, NUM_LEDS);
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
    // in case the update of die LED Stripe is blocked, quit here
    if (this->updatesBlocked())
        return;

    FastLED.setBrightness(Config.getLedBrightness());

    for (int letter = 0; letter < len; letter++)
    {
        this->leds_target[word[letter]] = color;
    }
}

void LedFunctionsClass::word2stripe(const int word[], int len)
{
    CRGB color;

    if (Config.getLedMode() == 1)
    {
        color = strtol(Config.getLedSimpleColor(), NULL, 0);
    }
    else if (Config.getLedMode() == 2)
    {
        color = ColorFromPalette(RainbowColors_p, this->paletteColorIndex);
        if (millis() - this->lastAutoColorChange > 5000)
        {
            // calculate index. it should bounce between 0 and 255
            if (this->paletteColorIndex >= 256)
            {
                this->paletteColorIndexStepper = -2;
            }
            if (this->paletteColorIndex <= 0)
            {
                this->paletteColorIndexStepper = 2;
            }
            this->paletteColorIndex = this->paletteColorIndex + this->paletteColorIndexStepper;
            this->lastAutoColorChange = millis();
        }
    }

    this->word2stripe(word, len, color);
}

//---------------------------------------------------------------------------------------
// blankscreen
//
// set all LEDs on the target array to black
//
// Params:
// . should the display be updated immediately (true/false)
//---------------------------------------------------------------------------------------
void LedFunctionsClass::blankscreen()
{
    // in case the update of die LED Stripe is blocked, quit here
    if (this->updatesBlocked())
        return;

    for (int pixel = 0; pixel < NUM_LEDS; pixel++)
    {
        this->leds_target[pixel] = CRGB::Black;
    }
}

//---------------------------------------------------------------------------------------
// switchTargetToLive
//
// copies die targetArray to the LiveArray => display at once
//---------------------------------------------------------------------------------------
void LedFunctionsClass::switchTargetToLive()
{
    for (int pixel = 0; pixel < NUM_LEDS; pixel++)
    {
        leds_live[pixel] = leds_target[pixel];
    }
    FastLED.show();
}
//---------------------------------------------------------------------------------------
// fadeTargetToLive
//
// compares the array with the information which LEDs too light up (target)
// with the array which is actually preseting the LEDs (live)
// and fills up the brightness array with the information, which LEDs to switch off
// and which LEDs to switch off
//---------------------------------------------------------------------------------------
void LedFunctionsClass::fadeTargetToLive(uint8_t amount)
{
    while (memcmp(this->leds_live, this->leds_target, sizeof(this->leds_live)) != 0)
    {
        for (int pixel = 0; pixel < NUM_LEDS; pixel++)
        {
            blendIntToInt(this->leds_live[pixel].red, this->leds_target[pixel].red, amount);
            blendIntToInt(this->leds_live[pixel].green, this->leds_target[pixel].green, amount);
            blendIntToInt(this->leds_live[pixel].blue, this->leds_target[pixel].blue, amount);
        }
        FastLED.delay(10);
    }
}

//---------------------------------------------------------------------------------------
// blendIntToInt
//
// Uses FastLED to blend over to the target color. It updates the new value directly
// in the array with the live pixels
//
//---------------------------------------------------------------------------------------
void LedFunctionsClass::blendIntToInt(uint8_t &cur, const uint8_t target, uint8_t amount)
{
    // LED already has requested color => do nothing
    if (cur == target)
        return;

    if (cur < target)
    {
        uint8_t delta = target - cur;
        delta = scale8_video(delta, amount);
        cur += delta;
    }
    else
    {
        uint8_t delta = cur - target;
        delta = scale8_video(delta, amount);
        cur -= delta;
    }
}

void LedFunctionsClass::printDebugArray()
{
    String debugString1;
    String debugString2;
    for (int pixel = 0; pixel < NUM_LEDS; pixel++)
    {
        if (leds_target[pixel])
        {
            debugString1.concat(1);
        }
        else
        {
            debugString1.concat(0);
        }
        if (leds_live[pixel])
        {
            debugString2.concat(1);
        }
        else
        {
            debugString2.concat(0);
        }
    }
    debugD("TARGET array: %s", debugString1.c_str());
    debugD("LIVE array:   %s", debugString2.c_str());
}

bool LedFunctionsClass::updatesBlocked()
{
    return this->blockUpdates;
}

void LedFunctionsClass::updatesBlocked(bool enable)
{
    this->blockUpdates = enable;
}