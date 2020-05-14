#ifndef _HEARTBEAT_H_
#define _HEARTBEAT_H_

#include "config.h"
#include <ArduinoJson.h>

// Oject keeping the configuration
struct Config {
  int ledBrightness;
  int ledSimpleColor;
};

void loadConfiguration(const char *filename, Config &config);
void resetConfiguration(const char *filename);

#endif