#include <NilRTOS.h>
// Library that allows to start the watch dog allowing automatic reboot in case of crash
// The lowest priority thread should take care of the watch dog
#include <avr/wdt.h>

// git clone https://github.com/PaulStoffregen/Time
#include <TimeLib.h>

#define LANGUAGE en  // currently only en or es

#define RED    A0
#define GREEN  A1
#define BLUE   A2
#define UV2    A3 // 3mm
#define UV1    A4 // 5mm

#define DATA_SIZE 240
#define DATA_TYPE 1  // LONG



byte ALL_LEDS[] = {RED, GREEN, BLUE, UV1};  // all possible leds
byte LEDS[] = {RED, GREEN, BLUE, UV1};      // will contain th active les
byte nbLeds;                                     // number of active leds
byte dataRowSize;                                // size of a data row (number of entries in data)
byte maxNbRows;                                  // 


void setup() {
  setupParameters();
  setActiveLeds();
  nilSysBegin();
}

void loop() {}

