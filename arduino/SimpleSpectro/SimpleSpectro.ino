
#include <NilRTOS.h>

// Library that allows to start the watch dog allowing automatic reboot in case of crash
// The lowest priority thread should take care of the watch dog
#include <avr/wdt.h>

// git clone https://github.com/PaulStoffregen/Time
#include <TimeLib.h>

#define RED    A0
#define GREEN  A1
#define BLUE   A2
#define UV1   A3
#define UV2   A4

byte LEDS[] = {RED, GREEN, BLUE, UV1, UV2};

#define MAX_EXPERIMENTS 40


// #define THR_MONITORING     13  // will also take care of the watch dog

void setup() {
  setupParameters();
  nilSysBegin();
}

void loop() {}

