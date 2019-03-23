// **** INCLUDES *****
#include "LowPower.h"

#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

byte wakeUpPin = ROT_A;

void wakeUp() {};

void setup() {
  pinMode(13, OUTPUT);
  pinMode(wakeUpPin, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(wakeUpPin), wakeUp, CHANGE);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(10000);

  digitalWrite(13, LOW);
  // Enter power down state with ADC and BOD module disabled.
  // Wake up when wake up pin is low.
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

}
