
#include <NilRTOS.h>

// Library that allows to start the watch dog allowing automatic reboot in case of crash
// The lowest priority thread should take care of the watch dog
#include <avr/wdt.h>

// http://www.arduino.cc/playground/Code/Time
#include <Time.h>


#define ARRAY_SIZE 256

#define AO_PIN1 A1
#define AO_PIN2 A2


#define REPEAT_CALIBRATE     10
#define SMOOTH_CALIBRATE     15
#define RED    11
#define GREEN   6
#define BLUE   13
#define UV     10
#define WHITE   9

#define CLKpin  8    // <-- Arduino pin delivering the clock pulses to pin 3 (CLK) of the TSL1402R 
#define SIpin   7     // <-- Arduino pin delivering the SI (serial-input) pulse to pin 2 of the TSL1402R 


byte RGB[] = {
  RED, GREEN, BLUE
};
byte LEDS[] = {
  RED, GREEN, BLUE, WHITE
};
char INFO[] = {
  'R', 'G', 'B', 'W', 'U', 'Z', 'E', 'A'
}; // E: experiment, Z: reference, A: RGB on


// #define THR_MONITORING     13  // will also take care of the watch dog




void setup() {
  delay(2000);
#ifdef KEYBOARD
  Keyboard.begin();
#endif
#ifdef LOGGER
  setupLogger();
#endif
  setupDebugger();
  setupParameters();
  setupLinear();
  setupActions();

  nilSysBegin();
}

void loop() {
}

