#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

#include "RotaryEncoder.h"

RotaryEncoder encoder(ROT_A, ROT_B);

void setup() {
  delay(2000);
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_A), tick, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROT_B), tick, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventRotaryPressed, CHANGE);
}
boolean rotaryPressed = false;
boolean rotaryMayPressed = true;

void tick() {
  encoder.tick();
}

int lastCounter=0;
int rotaryCounter=0;

void loop() {
  rotaryCounter = encoder.getPosition();
  if (lastCounter != rotaryCounter) {
    Serial.println(rotaryCounter);
  }
  lastCounter = rotaryCounter;
  delay(20);
}


void eventRotaryPressed() {
  byte state = digitalRead(ROT_PUSH);
  if (state == 0) {
    if (rotaryMayPressed) {
      rotaryPressed = true;
      rotaryMayPressed = false;
      Serial.println("P");
    }
  } else {
    rotaryMayPressed = true;
  }
}
