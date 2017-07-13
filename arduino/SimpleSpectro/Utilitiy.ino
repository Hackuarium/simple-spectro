

void testRGB() {
  for (byte i = 0; i < sizeof(LEDS); i++) {
    pinMode(LEDS[i], OUTPUT);
  }

  for (byte j = 0; j < 5; j++) {
    for (byte i = 0; i < sizeof(LEDS); i++) {
      digitalWrite(LEDS[i], HIGH);
      nilThdSleepMilliseconds(500);
      digitalWrite(LEDS[i], LOW);
    }
  }
}

void  runExperiment() {

  for (byte i = 0; i < sizeof(LEDS)); i++) {

  }

  FreqCount.begin(1000);
  nilThdSleepMilliseconds(1100);
  unsigned long countFrequency = FreqCount.read();
}

