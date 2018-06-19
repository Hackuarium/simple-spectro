#include <LiquidCrystal.h>

#define LCD_E      6
#define LCD_RS     A6
#define LCD_D4     8
#define LCD_D5     9
#define LCD_D6     10
#define LCD_D7     5
#define LCD_BL     13    // back light
#define LCD_VO     11    // contrast (on / off to spare energy)
#define LCD_ON     MOSI  // power on LCD

byte pins[] = {LCD_E, LCD_RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_VO, LCD_BL, LCD_ON};

#define LCD_NB_ROWS     2
#define LCD_NB_COLUMNS  16

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


void setup() {
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH); // backlight
  pinMode(LCD_ON, HIGH); // LCD on / off
  digitalWrite(LCD_ON, HIGH); // LCD on
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Hello world!");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("            ");
  delay(2000);


  for (byte i = 0; i < sizeof(pins); i++) {
    pinMode(pins[i], INPUT);
  }
  delay(4000);

  for (byte i = 0; i < sizeof(pins); i++) {
    pinMode(pins[i], OUTPUT);
  }
  digitalWrite(11, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(MOSI, HIGH);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
  delay(4000);


  
}



