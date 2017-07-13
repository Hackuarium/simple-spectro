
#include <NilRTOS.h>

// Library that allows to start the watch dog allowing automatic reboot in case of crash
// The lowest priority thread should take care of the watch dog
#include <avr/wdt.h>

// http://www.arduino.cc/playground/Code/Time
#include <Time.h>

#define RED    A0
#define GREEN  A1
#define BLUE   A2
#define UV1   A3
#define UV2   A4

byte LEDS[] = {RED, GREEN, BLUE, UV1, UV2};





// #define THR_MONITORING     13  // will also take care of the watch dog




void setup() {
  delay(2000);
#ifdef LOGGER
  setupLogger();
#endif

  setupParameters();


  nilSysBegin();
}

void loop() {
}

