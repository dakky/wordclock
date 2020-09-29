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

    this->print();
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
        this->save();
    }
    else
    {
        Serial.println("Configuration: Loaded file sucessfully.");
    }

    // Test if key exists in json, 
    // if yes: Copy values from the JsonDocument to the config object
    // if no: set bolean for restarting the esp after resetting to default values
    if (doc["ledBrightness"].isNull()) {
        this->resetAndRestart();
    } else {
        this->config->ledBrightness = doc["ledBrightness"];
    }
    if (doc["ledSimpleColor"].isNull()) {
        this->resetAndRestart();
    } else {
        strlcpy(this->config->ledSimpleColor, doc["ledSimpleColor"], sizeof(this->config->ledSimpleColor));
    }
    if (doc["ledRainbowSpeed"].isNull()) {
        this->resetAndRestart();
    } else {
        this->config->ledRainbowSpeed = doc["ledRainbowSpeed"];
    }
    if (doc["ledMode"].isNull()) {
        this->resetAndRestart();
    } else {
        this->config->ledMode = doc["ledMode"];
    }
    if (doc["ntpServername"].isNull()) {
        this->resetAndRestart();
    } else {
        strlcpy(this->config->ntpServername, doc["ntpServername"], sizeof(this->config->ntpServername));
    }
    if (doc["ntpTimezone"].isNull()) {
        this->resetAndRestart();
    } else {
        strlcpy(this->config->ntpTimezone, doc["ntpTimezone"], sizeof(this->config->ntpTimezone));
    }
    if (doc["hostname"].isNull()) {
        this->resetAndRestart();
    } else {
        strlcpy(this->config->hostname, doc["hostname"], sizeof(this->config->hostname));
    }
    if (doc["startSleeptimeHour"].isNull()) {
        this->resetAndRestart();
    } else {
        this->config->startSleeptimeHour = doc["startSleeptimeHour"];
    }
    if (doc["startSleeptimeMinute"].isNull()) {
        this->resetAndRestart();
    } else {
        this->config->startSleeptimeMinute = doc["startSleeptimeMinute"];
    }
    if (doc["endSleeptimeHour"].isNull()) {
        this->resetAndRestart();
    } else {
        this->config->endSleeptimeHour = doc["endSleeptimeHour"];
    }
    if (doc["endSleeptimeMinute"].isNull()) {
        this->resetAndRestart();
    } else {
        this->config->endSleeptimeMinute = doc["endSleeptimeMinute"];
    }

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
    Serial.println("Configuration: Resetting to default values.");
    debugI("Configuration: Resetting to default values.");

    this->config->ledBrightness = 153;       // middle of 0..254
    strlcpy(this->config->ledSimpleColor, "0x7FFF00", sizeof(this->config->ledSimpleColor)); //light green
    this->config->ledRainbowSpeed = 3; // medium speed
    this->config->ledMode = 1; // simple color mode
    strlcpy(this->config->ntpServername, "europe.pool.ntp.org", sizeof(this->config->ntpServername));
    strlcpy(this->config->ntpTimezone, "Europe/Berlin", sizeof(this->config->ntpTimezone));
    strlcpy(this->config->hostname, "wordclock", sizeof(this->config->hostname));
    this->config->startSleeptimeHour = 22;
    this->config->startSleeptimeMinute = 00;
    this->config->endSleeptimeHour = 5;
    this->config->endSleeptimeMinute = 00;

    this->save();

    Serial.println("Configuration: Reset Done");
    debugI("Configuration: Reset Done");
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
    doc["ledRainbowSpeed"] = this->config->ledRainbowSpeed;
    doc["ledMode"] = this->config->ledMode;
    doc["ntpServername"] = this->config->ntpServername;
    doc["ntpTimezone"] = this->config->ntpTimezone;
    doc["hostname"] = this->config->hostname;
    doc["startSleeptimeHour"] = this->config->startSleeptimeHour;
    doc["startSleeptimeMinute"] = this->config->startSleeptimeMinute;
    doc["endSleeptimeHour"] = this->config->endSleeptimeHour;
    doc["endSleeptimeMinute"] = this->config->endSleeptimeMinute;

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
        debugE("Failed to read file");
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
// helper for resetting and restarting die esp module
//---------------------------------------------------------------------------------------
void ConfigClass::resetAndRestart()
{
    this->reset();
    this->save();
    // ESP.restart();
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
    Serial.printf("ConfigClass: brightness is set to: %i", brightness);
    debugI("ConfigClass: brightness is set to: %i", brightness);
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
void ConfigClass::setLedSimpleColor(char* color, int bufsize)
{
    // copy chararray into config struct
    memcpy(this->config->ledSimpleColor, color, bufsize);
    Serial.printf("ConfigClass: color is set to: %s", color);
    debugI("ConfigClass: color is set to: %s", color);
}

//---------------------------------------------------------------------------------------
// getLedMode
//
// gets the LedMode from config struct
//
//---------------------------------------------------------------------------------------
byte ConfigClass::getLedMode()
{
    return this->config->ledMode;
}

//---------------------------------------------------------------------------------------
// setLedMode
// sets the color mode of the clock
// param1 (byte): mode
// Mode 1: simple color
// Mode 2: rainbow changing colors
//
//---------------------------------------------------------------------------------------
void ConfigClass::setLedMode(byte mode)
{
    // validation: if invalid: default to 1
    byte validModes[] = {1,2};
    
    for (int i=0; i<sizeof validModes/sizeof validModes[0]; i++) {
        if (validModes[i] == mode) {
            this->config->ledMode = mode;
            Serial.printf("ConfigClass: Led Mode is set to: %u", mode);
            debugI("ConfigClass: Led Mode is set to: %u", mode);
        }
    }
    // nothing wil happen if invalid mode is passed to method
}

//---------------------------------------------------------------------------------------
// getNtpServername
//
// gets the NtpServername from config struct
//
//---------------------------------------------------------------------------------------
char* ConfigClass::getNtpServername()
{
    return this->config->ntpServername;
}

//---------------------------------------------------------------------------------------
// setLedBrightness
//
// sets the ntp server in config struct
// param1 (char): chararray containing the ntp server
// param2 (int): size of chararray (usally `sizeof(arr)`)
//
//---------------------------------------------------------------------------------------
void ConfigClass::setNtpServername(char* servername, int bufsize)
{
    // copy chararray into config struct
    memcpy(this->config->ntpServername, servername, bufsize);
    Serial.printf("ConfigClass: NTP Server is set to: %s", this->config->ntpServername);
    debugI("ConfigClass: NTP Server is set to: %s", this->config->ntpServername);
}

//---------------------------------------------------------------------------------------
// getNtpTimezone
//
// gets the NtpTimezone from config struct
//
//---------------------------------------------------------------------------------------
char* ConfigClass::getNtpTimezone()
{
    return this->config->ntpTimezone;
}

//---------------------------------------------------------------------------------------
// setLedBrightness
//
// sets the btp timezone in config struct
// param1 (char): chararray containing the ntp timezone
// param2 (int): size of chararray (usally `sizeof(arr)`)
//
//---------------------------------------------------------------------------------------
void ConfigClass::setNtpTimezone(char* timezone, int bufsize)
{
    // copy chararray into config struct
    memcpy(this->config->ntpTimezone, timezone, bufsize);
    Serial.printf("ConfigClass: NTP Timezone is set to: %s", this->config->ntpTimezone);
    debugI("ConfigClass: NTP Timezone is set to: %s", this->config->ntpTimezone);
}

//---------------------------------------------------------------------------------------
// getHostname
//
// gets the hostname from config struct
//
//---------------------------------------------------------------------------------------
char* ConfigClass::getHostname()
{
    return this->config->hostname;
}

//---------------------------------------------------------------------------------------
// setHostname
//
// sets thehostname in config struct
// param1 (char): chararray containing the hostname
// param2 (int): size of chararray (usally `sizeof(arr)`)
//
//---------------------------------------------------------------------------------------
void ConfigClass::setHostname(char* hostname, int bufsize)
{
    // copy chararray into config struct
    memcpy(this->config->hostname, hostname, bufsize);
    Serial.printf("ConfigClass: Hostname is set to: %s", this->config->hostname);
    debugI("ConfigClass: Hostname is set to: %s", this->config->hostname);
}

//---------------------------------------------------------------------------------------
// getRainbowSpeed
//
// gets the RainbowSpeed from config struct
//
//---------------------------------------------------------------------------------------
byte ConfigClass::getLedRainbowSpeed()
{
    return this->config->ledRainbowSpeed;
}

//---------------------------------------------------------------------------------------
// setRainbowSpeed
//
// sets the brightness in config struct
// param1 (char): chararray containing the hexvalue of the color in format 0xFFFFFF
// param2 (int): size of chararray (usally `sizeof(arr)`)
//
//---------------------------------------------------------------------------------------
void ConfigClass::setLedRainbowSpeed(byte speed)
{
    // validate input ;) 4 levels. cap if higher or lower
    if (speed <= 1) speed = 1;
    if (speed >= 4) speed = 4;

    this->config->ledRainbowSpeed = speed;
    Serial.printf("ConfigClass: Led rainbow Speed is set to: %u", speed);
    debugI("ConfigClass: Led rainbow Speed is set to: %u", speed);
}

//---------------------------------------------------------------------------------------
// setStartSleeptime
//
// sets the time when the clock should start  the sleepmode 
// param1 (char): chararray containing the timw
// param2 (int): size of chararray (usally `sizeof(arr)`)
//
//---------------------------------------------------------------------------------------
void ConfigClass::setStartSleeptime(char* startSleeptime, int buffsize)
{
    char* bufferStartHour = new char[2];
    char* bufferStartMinute = new char[2];

    int begin;
    
    begin = 0;
    for (int i = 0; i < 2; i++) {
        bufferStartHour[i] = *(startSleeptime + begin + i);
    }
    
    begin = 3;
    for (int i = 0; i < 2; i++) {
        bufferStartMinute[i] = *(startSleeptime + begin + i);
    }

    this->config->startSleeptimeHour = atoi(bufferStartHour); 
    this->config->startSleeptimeMinute = atoi(bufferStartMinute); 

    Serial.printf("ConfigClass: startSleeptimeHour is set to: %u and startSleeptimeMinute is set to: %u\n", this->config->startSleeptimeHour, this->config->startSleeptimeMinute);
    debugI("startSleeptimeHour is set to: %u and startSleeptimeMinute is set to: %u", this->config->startSleeptimeHour, this->config->startSleeptimeMinute);
}

//---------------------------------------------------------------------------------------
// getStartSleeptimeHour
//
// gets the HOUR, when the clock should start the sleepmode
//
//---------------------------------------------------------------------------------------
int ConfigClass::getStartSleeptimeHour()
{
    return this->config->startSleeptimeHour;
}

//---------------------------------------------------------------------------------------
// getStartSleeptimeMinute
//
// gets the Minute, when the clock should start the sleepmode
//
//---------------------------------------------------------------------------------------
int ConfigClass::getStartSleeptimeMinute()
{
    return this->config->startSleeptimeMinute;
}

//---------------------------------------------------------------------------------------
// setEndSleeptime
//
// sets the time when the clock should end  the sleepmode 
// param1 (char): chararray containing the timw
// param2 (int): size of chararray (usally `sizeof(arr)`)
//
//---------------------------------------------------------------------------------------
void ConfigClass::setEndSleeptime(char* endSleeptime, int bufsize)
{
    char* bufferEndHour = new char[2];
    char* bufferEndMinute = new char[2];

    int begin;
    
    begin = 0;
    for (int i = 0; i < 2; i++) {
        bufferEndHour[i] = *(endSleeptime + begin + i);
    }
    
    begin = 3;
    for (int i = 0; i < 2; i++) {
        bufferEndMinute[i] = *(endSleeptime + begin + i);
    }

    this->config->endSleeptimeHour = atoi(bufferEndHour); 
    this->config->endSleeptimeMinute = atoi(bufferEndMinute); 

    Serial.printf("ConfigClass: endSleeptimeHour is set to: %u and endSleeptimeMinute is set to: %u\n", this->config->endSleeptimeHour, this->config->endSleeptimeMinute);
    debugI("endSleeptimeHour is set to: %u and endSleeptimeMinute is set to: %u", this->config->endSleeptimeHour, this->config->endSleeptimeMinute);
}

//---------------------------------------------------------------------------------------
// getEndSleeptimeHour
//
// gets the HOUR, when the clock should end the sleepmode
//
//---------------------------------------------------------------------------------------
int ConfigClass::getEndSleeptimeHour()
{
    return this->config->endSleeptimeHour;
}

//---------------------------------------------------------------------------------------
// getEndSleeptimeMinute
//
// gets the Minute, when the clock should end the sleepmode
//
//---------------------------------------------------------------------------------------
int ConfigClass::getEndSleeptimeMinute()
{
    return this->config->endSleeptimeMinute;
}
