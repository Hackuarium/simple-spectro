#include <NilRTOS.h>
// Library that allows to start the watch dog allowing automatic reboot in case of crash
// The lowest priority thread should take care of the watch dog
#include <avr/wdt.h>

#include <TimeLib.h>
#include "lib/Utility.h"

// git clone https://github.com/PaulStoffregen/Time


#define LANGUAGE  en  // currently only en or es
#define VERSION   B   // version B as temperature sensor and battery indicator

#define RED    A0
#define GREEN  A1
#define BLUE   A2
#define UV1    A4 // 5mm

#if VERSION == B
  #define BATTERY               A3  // if battery we have also the temperature sensor
  #define TEMPERATURE_ADDRESS   0b1001000
#endif

#define DATA_SIZE 240
#define DATA_TYPE 1  // LONG

#define BATTERY_LEVEL 128   // not available in version A
#define TEMPERATURE   129   // not available in version A

#if VERSION == 'A'
  byte ALL_PARAMETERS[] = {RED, GREEN, BLUE, UV1};  // all possible leds
  byte CURRENT_PARAMETERS[] = {RED, GREEN, BLUE, UV1};      // will contain the active les
#else
  byte ALL_PARAMETERS[] = {RED, GREEN, BLUE, UV1, TEMPERATURE, BATTERY_LEVEL};  // all possible leds
  byte CURRENT_PARAMETERS[] = {RED, GREEN, BLUE, UV1, TEMPERATURE, BATTERY_LEVEL};      // will contain the active les
#endif

byte nbLeds;              // number of active leds
byte nbParameters;        // number of parameters to record
byte dataRowSize;         // size of a data row (number of entries in data)
byte maxNbRows;           // calculate value depending the size of EEPROM dedicated to logs


void setup() {
  setupParameters();
  setActiveLeds();
  nilSysBegin();
}

void loop() {}

