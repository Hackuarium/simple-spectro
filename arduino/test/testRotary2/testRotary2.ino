/*
 * Example using the Rotary library, dumping integers to the serial
 * port. The integers increment or decrement depending on the direction
 * of rotation.
 *
 * This example uses interrupts rather than polling.
 */

#define ENABLE_PULLUPS 1

#include "Rotary.h"

// Rotary encoder is wired with the common to ground and the two
// outputs to pins 2 and 3.
 Rotary rotary = Rotary(0, 1);

// Counter that will be incremented or decremented by rotation.
int counter = 0;

void setup() {
  delay(4000);
  Serial.begin(9600);
  
  attachInterrupt(2, rotate, CHANGE);
  attachInterrupt(3, rotate, CHANGE);
  Serial.println("Hello");
}

void loop() {

//Serial.println(counter);
delay(250);
    Serial.println(counter);
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
 // counter++;
  
  unsigned char result = rotary.process();
  if (result == DIR_CW) {
    counter++;
  } else if (result == DIR_CCW) {
    counter--;
  }
  
}

