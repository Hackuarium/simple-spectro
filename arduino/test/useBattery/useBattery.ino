#include <LiquidCrystal.h>

#define RED    A0
#define GREEN  A1
#define BLUE   A2
#define UV1   A3
#define UV2   A4

byte leds[] = {RED, GREEN, BLUE, UV1, UV2};


#define LCD_E   12
#define LCD_RS  A6
#define LCD_D4  6
#define LCD_D5  8
#define LCD_D6  9
#define LCD_D7  10
#define LCD_BL  11    // back light
#define LCD_VO  13    // contrast (on / off to spare energy)
#define LCD_ON  MOSI  // power on LCD

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);



void setup() {
  for (byte i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
  }

    // testPins(); // just to test connections with oscilloscope
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH); // backlight
  pinMode(LCD_ON, HIGH); // LCD on / off
  digitalWrite(LCD_ON, HIGH); // backlight
  pinMode(13, INPUT); // contrast control / turned off in this version
  delay(10);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  
}

void loop() {
   lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

