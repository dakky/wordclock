#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "globals.h"

#define NUM_LEDS 114
#define DATA_PIN 15 // D8 on wemos

#define HEARTBEAT_ENABLED true
#define HEARTBEAT_PIN 2

#define WIFI_WORDCLOCK_HOSTNAME "wordclock"

#define NTP_SERVER_NAME "europe.pool.ntp.org"
#define NTP_UPDATE_INTERVAL_MINS 60
#define NTP_LOCAL_PORT 8888

// time window in microseconds for OTA before actual clocklogic is starting
// just in case the clock needs to be rescued from faulty firmware
#define OTA_STARTUP_DELAY 25


#endif /* CONFIG_H_ */