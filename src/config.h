#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "globals.h"

#define NUM_LEDS 114
#define DATA_PIN 15 // D8 on wemos

#define FRAMES_PER_SECOND 20

#define HEARTBEAT_PIN 2

#define WIFI_WORDCLOCK_HOSTNAME "wordclock"

// time window in microseconds for OTA before actual clocklogic is starting
// just in case the clock needs to be rescued from faulty firmware
#define OTA_STARTUP_DELAY 25


#endif /* CONFIG_H_ */