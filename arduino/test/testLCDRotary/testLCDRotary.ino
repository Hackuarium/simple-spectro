#include <LiquidCrystal.h>

#define LCD_E      12
#define LCD_RS     A6
#define LCD_D4     6
#define LCD_D5     8
#define LCD_D6     9
#define LCD_D7     10
#define LCD_BL     11    // back light
#define LCD_VO     13    // contrast (on / off to spare energy)
#define LCD_ON     MOSI  // power on LCD
byte pins[] = {LCD_E, LCD_RS, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_VO};

#define LCD_NB_ROWS     2
#define LCD_NB_COLUMNS  16

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

boolean rotaryPressed = false;
int rotaryCounter = 0;
int currentMenu = 0;
boolean lastMenu;
boolean captureCounter = false; // use when you need to setup a parameter from the menu
long lastRotaryEvent = millis();

void setup() {
  setupRotary();
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH); // backlight
  pinMode(LCD_ON, HIGH); // LCD on / off
  digitalWrite(LCD_ON, HIGH); // LCD on
  delay(10);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
}

void loop() {
  currentMenu += rotaryCounter;
  rotaryCounter = 0;
  if ((millis() - lastRotaryEvent) > 10000) {
    currentMenu = 0;
    captureCounter = false;
    rotaryPressed = false;
  } else {
    if (currentMenu < 1) currentMenu = 1;
  }
  lcdMenu();
  delay(20);
}

void lcdMenu() {
  if (currentMenu == 0) {
    lcdDefault();
  } else {
    lastMenu = false;
    for (byte line = 0; line < LCD_NB_ROWS; line++) {
      if (line == 0 && rotaryPressed) {
        lcdMenu0(line, true);
        rotaryPressed = false;
      } else {
        lcdMenu0(line, false);
      }
      if (lastMenu) return;
    }
  }
}

void lcdDefault() {
  lcd.setCursor(0, 0);
  lcd.print("R:      ");
  lcd.setCursor(8, 0);
  lcd.print("G:      ");
  lcd.setCursor(0, 1);
  lcd.print("B:      ");
  lcd.setCursor(8, 1);
  lcd.print("U:      ");
}

void lcdMenu0(byte line, boolean doAction) {
  currentMenu = min(currentMenu, 4); // need to put the max number of items in the menu
  lcd.setCursor(0, line);

  switch (currentMenu + line) {
    case 1:
      lcd.print(F("1. Reset"));
      break;
    case 2:
      lcd.print(F("2. Settings"));
      if (doAction) {

      }
      break;
    case 3:
      lcd.print(F("3. Acquire"));
      break;
    case 4:
      lcd.print(F("4. Backlight"));
      if (doAction) {
        digitalWrite(LCD_BL, !digitalRead(LCD_BL));
      }
  }
  lcd.print(F("                "));
}



