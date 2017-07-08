#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7


void setup() {
  Serial.begin(9600);
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_A), eventA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROT_B), eventB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventP, CHANGE);
}

void loop() {
}

void eventA() {
  Serial.println("A");
}

void eventB() {
  Serial.println("B");
}

void eventP() {
  Serial.println("P");
}
