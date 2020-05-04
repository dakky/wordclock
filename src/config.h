#include <FastLED.h>

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define NUM_LEDS 114
#define DATA_PIN 3

#define HEARTBEAT_ENABLED true
#define HEARTBEAT_PIN 2

#define WIFI_WORDCLOCK_HOSTNAME "wordclock"

#define NTP_SERVER_NAME "europe.pool.ntp.org"
#define NTP_UPDATE_INTERVAL_MINS 60
#define NTP_LOCAL_PORT 8888


#endif /* CONFIG_H_ */