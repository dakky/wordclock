// Copyright (C) 2020 Robert, https://github.com/dakky
//
//  This is the configuration module. It contains methods to load/save the
//  configuration from/to a json file located on SPIFFS.
// The config variables are public, so they can be used by other modules
// directly
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

#include <ArduinoJson.h>
#include <FS.h>
#include "configuration.h"
#include "telnetDebugging.h"

//---------------------------------------------------------------------------------------
// global instance
//---------------------------------------------------------------------------------------
ConfigClass Config = ConfigClass();

//---------------------------------------------------------------------------------------
// ConfigClass
//
// Constructor, loads default values
//
//---------------------------------------------------------------------------------------
ConfigClass::ConfigClass()
{
    this->reset();
}

//---------------------------------------------------------------------------------------
// ~ConfigClass
//
// destructor
//
//---------------------------------------------------------------------------------------
ConfigClass::~ConfigClass()
{
}

//---------------------------------------------------------------------------------------
// begin
//
// Initializes the class and loads current configuration from config.json into class
// members.
//
//---------------------------------------------------------------------------------------
void ConfigClass::begin()
{
    if (!SPIFFS.begin())
    {
        Serial.println("Configuration: Initilializing SPIFFS ... Error!");
    }
    Serial.println("Configuration: File System Initialized");
    // for debugging purposes: create file every startup with default values
    // this->reset();
    // this->save();

    this->load();
    this->print();
}

//---------------------------------------------------------------------------------------
// load
//
// Reads the content of the config.json ,Resets (and saves) the values to their defaults
// if the file is not readable or can't be deserialized.
//
//---------------------------------------------------------------------------------------
void ConfigClass::load()
{
    Serial.println("Configuration: Reading config.json");

    File file = SPIFFS.open(filename, "r");

    // Allocate a temporary JsonDocument
    //  Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.println("Configuration: Failed to read file, using default configuration");
        this->reset();
    }

    // Copy values from the JsonDocument to the Config
    this->config->ledBrightness = doc["ledBrightness"];
    strlcpy(this->config->ledSimpleColor, doc["ledSimpleColor"], sizeof(this->config->ledSimpleColor));
    this->config->heartbeatEnabled = doc["heartbeatEnabled"];
    this->config->dataPin = doc["dataPin"];
    strlcpy(this->config->ntpServername, doc["ntpServername"], sizeof(this->config->ntpServername));
    strlcpy(this->config->ntpTimezone, doc["ntpTimezone"], sizeof(this->config->ntpTimezone));
    this->config->ntpUpdateIntervalMinutes = doc["ntpUpdateIntervalMinutes"];
    strlcpy(this->config->hostname, doc["hostname"], sizeof(this->config->hostname));

    file.close();

    // now load the config struct members into the public class members
    this->heartbeatEnabled = this->config->heartbeatEnabled;
    this->dataPin = this->config->dataPin;
    memcpy(this->ntpServername, this->config->ntpServername, sizeof(this->config->ntpServername));
    memcpy(this->ntpTimezone, this->config->ntpTimezone, sizeof(this->config->ntpTimezone));
    this->ntpUpdateIntervalMinutes = this->config->ntpUpdateIntervalMinutes;
    memcpy(this->hostname, this->config->hostname, sizeof(this->config->hostname));
}

//---------------------------------------------------------------------------------------
// reset
//
// Sets default values in member variables.
//
//---------------------------------------------------------------------------------------
void ConfigClass::reset()
{
    Serial.println("Configuration: Resetting to default values.");
    this->config->ledBrightness = 153;       // middle of 0..254
    strlcpy(this->config->ledSimpleColor, "0x7FFF00", sizeof(this->config->ledSimpleColor)); //light green
    this->config->heartbeatEnabled = true;
    this->config->dataPin = 15; // D8 on Wemos Mini
    strlcpy(this->config->ntpServername, "europe.pool.ntp.org", sizeof(this->config->ntpServername));
    strlcpy(this->config->ntpTimezone, "Europe/Berlin", sizeof(this->config->ntpTimezone));
    this->config->ntpUpdateIntervalMinutes = 60;
    strlcpy(this->config->hostname, "wordclock", sizeof(this->config->hostname));

    this->save();

    Serial.println("Configuration: Reset Done");
}

//---------------------------------------------------------------------------------------
// save
//
// Saves the current class member values to config.json.
//
//---------------------------------------------------------------------------------------
void ConfigClass::save()
{
    // Open file for writing
    File file = SPIFFS.open(filename, "w+");
    if (!file)
    {
        Serial.println("Failed to create file");
        return;
    }

    // writing public class members to config struct
    // now load the config struct members into the public class members
    this->config->heartbeatEnabled = this->heartbeatEnabled;
    this->config->dataPin = this->dataPin;
    memcpy(this->config->ntpServername, this->ntpServername, sizeof(this->ntpServername));
    memcpy(this->config->ntpTimezone, this->ntpTimezone, sizeof(this->ntpTimezone));
    this->config->ntpUpdateIntervalMinutes = this->ntpUpdateIntervalMinutes;
    memcpy(this->config->hostname, this->hostname, sizeof(this->hostname));

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Set the values in the document
    doc["ledBrightness"] = this->config->ledBrightness;
    doc["ledSimpleColor"] = this->config->ledSimpleColor;
    doc["heartbeatEnabled"] = this->config->heartbeatEnabled;
    doc["dataPin"] = this->config->dataPin;
    doc["ntpServername"] = this->config->ntpServername;
    doc["ntpTimezone"] = this->config->ntpTimezone;
    doc["ntpUpdateIntervalMinutes"] = this->config->ntpUpdateIntervalMinutes;
    doc["hostname"] = this->config->hostname;

    // Serialize JSON to file
    if (serializeJson(doc, file) == 0)
    {
        Serial.println("Failed to write to file");
    }

    // Close the file
    file.close();
}

// Prints the content of a file to the Serial
void ConfigClass::print()
{
    // Open file for reading
    File file = SPIFFS.open(filename, "r");
    if (!file)
    {
        Serial.println(F("Failed to read file"));
        return;
    }

    // Extract each characters by one by one
    while (file.available())
    {
        Serial.print((char)file.read());
    }
    Serial.println();

    // Close the file
    file.close();
}

//---------------------------------------------------------------------------------------
// getLedBrightness
//
// gets the brightness from config struct
//
//---------------------------------------------------------------------------------------
int ConfigClass::getLedBrightness()
{
    return this->config->ledBrightness;
}

//---------------------------------------------------------------------------------------
// setLedBrightness
//
// sets the brightness in config struct
// param1 (int): brightness between 1 and 255
//
//---------------------------------------------------------------------------------------
void ConfigClass::setLedBrightness(int brightness)
{
    if (brightness < 0)
    {
        this->config->ledBrightness = 0;
    }
    else if (brightness > 255)
    {
        this->config->ledBrightness = 255;
    }
    else
    {
        this->config->ledBrightness = brightness;
    }
}

//---------------------------------------------------------------------------------------
// getLedSimpleColor
//
// gets the LedSimpleColor from config struct
//
//---------------------------------------------------------------------------------------
char* ConfigClass::getLedSimpleColor()
{
    return this->config->ledSimpleColor;
}

//---------------------------------------------------------------------------------------
// setLedBrightness
//
// sets the brightness in config struct
// param1 (char): chararray containing the hexvalue of the color in format 0xFFFFFF
// param2 (int): size of chararray (usally `sizeof(arr)`)
//
//---------------------------------------------------------------------------------------
void ConfigClass::setLedSimpleColor(char* color, int buf)
{
    // copy chararray into config struct
    memcpy(this->config->ledSimpleColor, color, buf);
    debugD("color is set to: %s", color);
}
