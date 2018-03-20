#include <NilRTOS.h>
#include <avr/wdt.h> // watch dog for automatic reboot in case of crash
#include <TimeLib.h> // git clone https://github.com/PaulStoffregen/Time
#include "lib/Utility.h"
// VERSION
// *******
// version B : temperature sensor and battery indicator
// version C : same as B
// version D : need to enable LCD (pin 13) and temperature / light sensor: PE2

#define VERSION   D

#define LANGUAGE  en  // currently only en or es

#define RED    A0
#define GREEN  A1
#define BLUE   A2
#define UV1    A4 // 5mm

#if VERSION == B || VERSION == C || VERSION == D
#define BATTERY               A3  // if battery we have also the temperature sensor
#define TEMPERATURE_ADDRESS   0b1001000
#endif

#if VERSION == D
#define POWER_ON_DSL237       PORTE |= 1 << PE2; DDRE |= 1 << PE2; nilThdSleepMilliseconds(10);
#define POWER_OFF_DSL237      PORTE &= ~ (1 << PE2);
#define BATTERY_CHARGING      11
#endif

#define DATA_SIZE 240
#define DATA_TYPE 1  // LONG

#define BATTERY_LEVEL 128   // not available in version A
#define TEMPERATURE   129   // not available in version A

#if VERSION != 'A'
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
  checkParameters(); // setup automatically the default parameter after install boot loader
  setActiveLeds();
  nilSysBegin();
}

void loop() {}

