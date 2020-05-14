// ESP8266 Wordclock
// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  See ledFunction.cpp for description.
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

#ifndef _LEDFUNCTION_H_
#define _LEDFUNCTION_H_

#include <FastLED.h>
#include "configuration.h"

#define NUM_LEDS 114

class LedFunctionClass {
    public:
        LedFunctionClass();
        ~LedFunctionClass();
        void begin();
        void word2stripe(const int word[], CRGB color = Config.ledSimpleColor, bool commit=true);
        void blankscreen(bool commit = true);
        void showWords();
    
    private:
        CRGB leds[NUM_LEDS];
        int dataPin;
};

extern LedFunctionClass LED;

// push word to leds array
// void word2stripe(const int[],int, CRGB color = CRGB::DeepPink);
// switching all led off
// void blankscreen(CRGB color, bool commit);

//void setupLeds();
//void setBrightness();

#endif