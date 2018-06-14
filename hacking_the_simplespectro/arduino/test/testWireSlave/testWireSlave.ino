#include <Wire.h>

#define RED    A0
#define GREEN  A1
#define BLUE   A2
#define UV1   A3
#define UV2   A4

byte leds[] = {RED, GREEN, BLUE, UV1, UV2};


void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  for (byte i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  for (byte i = 0; i < sizeof(leds); i++) {
    digitalWrite(leds[i], HIGH);
    delay(500);
    digitalWrite(leds[i], LOW);
  }
}

void requestEvent() {
  Wire.write("hello"); // respond with message of 6 bytes
}
