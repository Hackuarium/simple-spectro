#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

void setup() {
  Serial.begin(115200);
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_A), eventA, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventRotaryPressed, CHANGE);
}

int rotaryCounter = 0;
int lastCounter = 0;
long lastRotaryEvent = millis();
boolean accelerationMode=true;
boolean rotaryPressed=false;
boolean rotaryMayPressed=true;

void loop() {
  if (lastCounter != rotaryCounter) {
  //  Serial.println(rotaryCounter);
  }
 // Serial.println(rotaryPressed);
  lastCounter = rotaryCounter;
  delay(500);
}

void eventA() {
  int increment = digitalRead(ROT_B) * 2 - 1;
  long current = millis();
  long diff = current - lastRotaryEvent;
  lastRotaryEvent = current;
  if (diff < 15) return;
  if (diff < 50) {
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
    byte state= digitalRead(ROT_PUSH);
if (state==0) {
   if (rotaryMayPressed) {
    rotaryPressed=true;
    rotaryMayPressed=false;
    Serial.println("P");
   }
} else {
  rotaryMayPressed=true;
}


/*
  byte state= digitalRead(ROT_PUSH);
  long current = millis();
  long diff = current - lastRotaryEvent;
  lastRotaryEvent = current;
  if (diff < 15 || state==HIGH) {
      Serial.print(current);
  Serial.print(" ");
    Serial.println(state);
    return;
  }
  Serial.print(current);
  Serial.print(" ");
  Serial.println("P");
  rotaryPressed = true;
 */
}
