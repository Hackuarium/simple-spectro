#include <LiquidCrystal.h>

#define LCD_E   12
#define LCD_RS  A6
#define LCD_D4  6
#define LCD_D5  8
#define LCD_D6  9
#define LCD_D7  10
#define LCD_BL  11  // back light
#define LCD_VO  13  // contrast

byte pins[] = {LCD_E, LCD_RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_VO};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  // testPins(); // just to test connections with oscilloscope
  testPWM();
  // set up the LCD's number of columns and rows:
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH); // backlight
  pinMode(MOSI, INPUT); // LCD on / off
  pinMode(13, INPUT); // contrash control

  delay(1000);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}


void testPins() {
  for (byte i = 0; i < sizeof(pins); i++) {
    pinMode(pins[i], OUTPUT);
  }
  while (true) {
    for (byte i = 0; i < sizeof(pins); i++) {
      digitalWrite(pins[i], HIGH);
    }
    delay(10);
    for (byte i = 0; i < sizeof(pins); i++) {
      digitalWrite(pins[i], LOW);
    }
    delay(10);
  }
}

void testPWM() {
  pinMode(LCD_VO, OUTPUT);
  while (true) {
    for (byte i = 0; i < 254; i++) {
      analogWrite(LCD_VO, i);
      delay(50);
    }
  }
}


