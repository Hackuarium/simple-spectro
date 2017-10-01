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
//#define UV1   A3
#define UV2   A4

#define DATA_SIZE 240
#ifdef UV1
byte LEDS[] = {RED, GREEN, BLUE, UV1, UV2};
#define MAX_EXPERIMENTS 40
#else
byte LEDS[] = {RED, GREEN, BLUE, UV2};
#define MAX_EXPERIMENTS 48
#endif

byte nbLeds=sizeof(LEDS);
byte rowSize=nbLeds+1;
byte nbEntries=DATA_SIZE/rowSize;
long data[DATA_SIZE]; // epoch R G B UV1 UV2



void setup() {
  setupParameters();
  nilSysBegin();
}

void loop() {}

