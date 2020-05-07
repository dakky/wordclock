#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "globals.h"

#define NUM_LEDS 114
#define DATA_PIN 3

#define HEARTBEAT_ENABLED true
#define HEARTBEAT_PIN 2

#define WIFI_WORDCLOCK_HOSTNAME "wordclock"

#define NTP_SERVER_NAME "europe.pool.ntp.org"
#define NTP_UPDATE_INTERVAL_MINS 60
#define NTP_LOCAL_PORT 8888

// time windows for OTA before actual clocklogic is starting
// just in case the clock needs to be rescued from faulty firmware
#define OTA_STARTUP_DELAY 2500


#endif /* CONFIG_H_ */