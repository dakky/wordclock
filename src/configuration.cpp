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
        Serial.println("initilializing SPIFFS ... Error!");
    }
    Serial.println("File System Initialized");
	this->load();
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
	Serial.println("Reading config.json");

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
        this->reset();
        this->save();
    }

    // Copy values from the JsonDocument to the Config
    this->config->ledBrightness = doc["ledBrightness"];
    this->config->ledSimpleColor = doc["ledSimpleColor"];
    this->config->heartbeatEnabled = doc["heartbeatEnabled"];

    // example of string to deseralize
    // strlcpy(config.hostname,                  // <- destination
    //  doc["hostname"] | "example.com",  // <- source
    //  sizeof(config.hostname));         // <- destination's capacity

    file.close();
}

//---------------------------------------------------------------------------------------
// reset
//
// Sets default values in member variables.
//
//---------------------------------------------------------------------------------------
void ConfigClass::reset()
{
	this->config->ledBrightness = 152;          // middle of 0..254
    this->config->ledSimpleColor = 0x7FFF00;    // light green
    this->config->heartbeatEnabled = true;
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

    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<512> doc;

    // Set the values in the document
    doc["ledBrightness"] = this->config->ledBrightness;
    doc["ledSimpleColor"] = this->config->ledSimpleColor;
    doc["heartbeatEnabled"] = this->config->heartbeatEnabled;
    

    // Serialize JSON to file
    if (serializeJson(doc, file) == 0)
    {
        Serial.println("Failed to write to file");
    }

    // Close the file
    file.close();
}

// Prints the content of a file to the Serial
void ConfigClass::print() {
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