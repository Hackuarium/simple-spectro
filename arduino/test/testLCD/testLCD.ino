#define LCD_E   12
#define LCD_RS  A6
#define LCD_D4  6
#define LCD_D5  8
#define LCD_D6  9
#define LCD_D7  10
#define LCD_BL  11    // back light
#define LCD_VO  13    // contrast (on / off to spare energy)
#define LCD_ON  MOSI  // power on LCD

byte pins[] = {LCD_E, LCD_RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_VO};

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



