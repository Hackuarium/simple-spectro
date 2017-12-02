


byte pins[] = {13, 5, 10, 9, 8, 6, A6, A0, A1, A2, A3, A4, A5, 12, 7, 0, 1};

void setup() {}

void loop() {
  testPins(); // just to test connections with oscilloscope
}


void testPins() {
  long counter = 0;
  for (byte i = 0; i < sizeof(pins); i++) {
    pinMode(pins[i], OUTPUT);
  }

  while (true) {
    for (byte i = 0; i < sizeof(pins); i++) {
      if (counter % (i + 1) == 0) {
        if (digitalRead(pins[i]) == HIGH) {
          digitalWrite(pins[i], LOW);
        } else {
          digitalWrite(pins[i], HIGH);
        }
      }
    }
    counter++;
    delay(1);
  }
}



