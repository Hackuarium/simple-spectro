#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

void setupRotary() {
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_A), eventRotaryA, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventRotaryPressed, CHANGE);
}

boolean accelerationMode = false;

void eventRotaryA() {
  int increment = digitalRead(ROT_B) * 2 - 1;
  long current = millis();
  long diff = current - lastRotaryEvent;
  lastRotaryEvent = current;
  if (diff < 5) return;
  if (diff < 25) {
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

}


void eventRotaryPressed() {
  long current = millis();
  long diff = current - lastRotaryEvent;
  lastRotaryEvent = current;
  if (diff < 5 || digitalRead(ROT_PUSH) == HIGH) return;
  rotaryPressed = true;
  lastRotaryEvent = current;
}
