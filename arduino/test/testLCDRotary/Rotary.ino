#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

void setupRotary() {
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_A), eventRotaryA, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventRotaryPressed, FALLING);
}

boolean accelerationMode = false;

void eventRotaryA() {
  int increment = digitalRead(ROT_B) * 2 - 1;
  long current = millis();
  if (current - lastRotaryEvent < 5) return;
  if ((current - lastRotaryEvent) < 25) {
    if (accelerationMode) {
      rotaryCounter -= (increment * 5);
    } else {
      accelerationMode = true;
      rotaryCounter -= increment;
    }
  } else {
    accelerationMode = false;
    rotaryCounter -= increment;
  }
  lastRotaryEvent = current;
}

void eventRotaryPressed() {
  rotaryPressed = true;
  lastRotaryEvent = millis();
}
