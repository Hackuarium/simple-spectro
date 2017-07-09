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



void eventRotaryA() {
  long current=millis();
  if (current-lastRotaryEvent<2) return;
  int increment=digitalRead(ROT_B)*2-1;
  if ((current-lastRotaryEvent)<10) {
    rotaryCounter-=increment*5;
  } else {
     rotaryCounter-=increment;
  }
  lastRotaryEvent=current;
}

void eventRotaryPressed() {
  rotaryPressed=true;
  lastRotaryEvent=millis();
}
