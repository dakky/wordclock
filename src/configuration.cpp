#include "configuration.h"

const char *filename = "/config.json";
Config config;

void loadConfiguration(const char *filename, Config &config)
{
    File file = SPIFFS.open(filename, "r");

    // Allocate a temporary JsonDocument
    //  Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.println("Failed to read file, using default configuration");
        resetConfiguration(filename);
        deserializeJson(doc, file);
    }

    // Copy values from the JsonDocument to the Config
    config.ledBrightness = doc["ledBrightness"] | 152;
    config.ledSimpleColor = doc["ledSimpleColor"] | 152;

    // example of string to deseralize
    // strlcpy(config.hostname,                  // <- destination
    //  doc["hostname"] | "example.com",  // <- source
    //  sizeof(config.hostname));         // <- destination's capacity

    file.close();
}

// Saves the configuration to a file
void saveConfiguration(const char *filename, const Config &config)
{
    // Open file for writing
    File file = SPIFFS.open(filename, "w+");
    if (!file)
    {
        Serial.println("Failed to create file");
        return;
    }

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Set the values in the document
    doc["ledBrightness"] = config.ledBrightness;
    doc["ledSimpleColor"] = config.ledSimpleColor;

    // Serialize JSON to file
    if (serializeJson(doc, file) == 0)
    {
        Serial.println(F("Failed to write to file"));
    }

    // Close the file
    file.close();
}

// Prints the content of a file to the Serial
void printConfigFile(const char *filename) {
  // Open file for reading
  File file = SPIFFS.open(filename,"r");
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Close the file
  file.close();
}