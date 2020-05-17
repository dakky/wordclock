#include "ledFunctions.h"
#include "configuration.h"

CRGB leds[NUM_LEDS];

// push word to leds array
void word2stripe(const int word[], int len, CRGB color)
{
    
    FastLED.setBrightness(Config.getLedBrightness());
    for (int letter = 0; letter < len; letter++)
    {
        leds[word[letter]] = color;
    }
}

//push word to leds array, color as hex char array
void word2stripe(const int word[], int len)
{
    
    FastLED.setBrightness(Config.getLedBrightness());
    long color = strtol(Config.getLedSimpleColor(),NULL,0);
    for (int letter = 0; letter < len; letter++)
    {
        leds[word[letter]] = color;
    }
}

// blank screen (to specific color if given, and put it on the matrix if set)
void blankscreen(CRGB color, bool commit)
{
    for (int led = 0; led < NUM_LEDS; led++)
    {
        leds[led] = color;
        if (commit)
        {
            FastLED.show();
        }
    }
}

void setupLeds()
{
    Serial.println("Setup LEDs: Initializing ...");
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    Serial.println("Setup LEDs: Done ...");
}