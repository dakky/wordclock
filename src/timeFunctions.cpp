#include "timeFunctions.h"

// push the time (words) to leds array
void timeToStripe()
{
    LED.blankscreen(false);
    uint8_t hours = clockTimezoned.hour();
    uint8_t minutes = clockTimezoned.minute();
    
    if (minuteChanged()) {
        debugI("Setting LEDs to: %u:%u", hours, minutes);
    }

    // show "ES IST"
    LED.word2stripe(word_ES, false);
    LED.word2stripe(word_IST, false);

    if (minutes >= 5 && minutes < 10)
    {
        LED.word2stripe(word_FUENF1, false);
        LED.word2stripe(word_NACH, false);
    }
    else if (minutes >= 10 && minutes < 15)
    {
        LED.word2stripe(word_ZEHN1, false);
        LED.word2stripe(word_NACH, false);
    }
    else if (minutes >= 15 && minutes < 20)
    {
        LED.word2stripe(word_VIERTEL, false);
        LED.word2stripe(word_NACH, false);
    }
    else if (minutes >= 20 && minutes < 25)
    {
        LED.word2stripe(word_ZWANZIG, false);
        LED.word2stripe(word_NACH, false);
    }
    else if (minutes >= 25 && minutes < 30)
    {
        LED.word2stripe(word_FUENF1, false);
        LED.word2stripe(word_VOR, false);
        LED.word2stripe(word_HALB, false);
    }
    else if (minutes >= 30 && minutes < 35)
    {
        LED.word2stripe(word_HALB, false);
    }
    else if (minutes >= 35 && minutes < 40)
    {
        LED.word2stripe(word_FUENF1, false);
        LED.word2stripe(word_NACH, false);
        LED.word2stripe(word_HALB, false);
    }
    else if (minutes >= 40 && minutes < 45)
    {
        LED.word2stripe(word_ZWANZIG, false);
        LED.word2stripe(word_VOR, false);
    }
    else if (minutes >= 45 && minutes < 50)
    {
        LED.word2stripe(word_VIERTEL, false);
        LED.word2stripe(word_VOR, false);
    }
    else if (minutes >= 50 && minutes < 55)
    {
        LED.word2stripe(word_ZEHN1, false);
        LED.word2stripe(word_VOR, false);
    }
    else if (minutes >= 55 && minutes < 60)
    {
        LED.word2stripe(word_FUENF1, false);
        LED.word2stripe(word_VOR, false);
    }

    int singleMinutes = minutes % 5;
    switch (singleMinutes)
    {
    case 1:
        LED.word2stripe(min_ONE, false, CRGB::Blue);
        break;
    case 2:
        LED.word2stripe(min_ONE, false, CRGB::Green);
        LED.word2stripe(min_TWO, false, CRGB::Blue);
        break;
    case 3:
        LED.word2stripe(min_ONE, false, CRGB::Yellow);
        LED.word2stripe(min_TWO, false, CRGB::Green);
        LED.word2stripe(min_THREE, false, CRGB::Blue);
        break;
    case 4:
        LED.word2stripe(min_ONE, false, CRGB::DarkOrange);
        LED.word2stripe(min_TWO, false, CRGB::Yellow);
        LED.word2stripe(min_THREE, false, CRGB::Green);
        LED.word2stripe(min_FOUR, false, CRGB::Blue);
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
        LED.word2stripe(word_ZWOELF, false);
        break;
    case 1:
        if (minutes > 4)
        {
            LED.word2stripe(word_EINS, false);
        }
        else
        {
            LED.word2stripe(word_EIN, false);
        }
        break;
    case 2:
        LED.word2stripe(word_ZWEI, false);
        break;
    case 3:
        LED.word2stripe(word_DREI, false);
        break;
    case 4:
        LED.word2stripe(word_VIER, false);
        break;
    case 5:
        LED.word2stripe(word_FUENF2, false);
        break;
    case 6:
        LED.word2stripe(word_SECHS, false);
        break;
    case 7:
        LED.word2stripe(word_SIEBEN, false);
        break;
    case 8:
        LED.word2stripe(word_ACHT, false);
        break;
    case 9:
        LED.word2stripe(word_NEUN, false);
        break;
    case 10:
        LED.word2stripe(word_ZEHN2, false);
        break;
    case 11:
        LED.word2stripe(word_ELF, false);
        break;
    }

    // show "UHR" if full hour
    if (minutes < 5)
    {
        LED.word2stripe(word_UHR, false);
    }
    LED.showWords();
}
