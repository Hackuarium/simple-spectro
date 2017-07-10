#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

void setup() {
  Serial.begin(115200);
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_A), eventA, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventP, FALLING);
}

int counter=0;
long lastEvent=millis();

void loop() {
  Serial.println(counter);
  delay(500);
}

void eventA() {
  long current=millis();
  if (current-lastEvent<2) return;
  int increment=digitalRead(ROT_B)*2-1;
  if ((current-lastEvent)<10) {
    counter-=increment*5;
  } else {
     counter-=increment;
  }
 
  lastEvent=current;
}

void eventP() {
  Serial.println("P");
}
