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
  setupParameters();
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH); // backlight
  pinMode(LCD_ON, HIGH); // LCD on / off
  digitalWrite(LCD_ON, HIGH); // LCD on
  delay(10);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
}

void loop() {
  if ((millis() - lastRotaryEvent) > 10000) {
    currentMenu = -1;
    captureCounter = false;
    rotaryPressed = false;
  } else {
    if (! captureCounter) {
      if (rotaryCounter < 0) {
        currentMenu += max(rotaryCounter, - currentMenu % 10);
      } else {
        currentMenu += min(rotaryCounter, 9 - currentMenu % 10);
      }
    }
  }
  rotaryCounter = 0;
  lcdMenu();
  delay(40);
}

void lcdMenu() {
  if (currentMenu == -1) {
    lcdDefault();
  } else {
    lastMenu = false;
    bool doAction = false;
    for (byte line = 0; line < LCD_NB_ROWS; line++) {
      if (line == 0 && rotaryPressed) {
        doAction = true;
        rotaryPressed = false;
      }
      switch (currentMenu - currentMenu % 10) {
        case 0:
          lcdMenuHome(line, doAction);
          break;
        case 10:
          lcdMenuSettings(line, doAction);
          break;
      }
      lcdBlankLine();
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

void lcdMenuHome(byte line, boolean doAction) {
  currentMenu = min(currentMenu, 4); // need to put the max number of items in the menu
  lcd.setCursor(0, line);

  switch (currentMenu + line) {
    case 0:
      lcd.print(F("1. Status"));
      break;
    case 1:
      lcd.print(F("2. Settings"));
      if (doAction) {
        currentMenu = 10;
      }
      break;
    case 2:
      lcd.print(F("3. Acquire"));
      break;
    case 3:
      lcd.print(F("4. Backlight"));
      if (doAction) {
        digitalWrite(LCD_BL, !digitalRead(LCD_BL));
      }
      break;
    case 4:
      lcd.print(F("5. Reset"));
      if (doAction) {
        resetParameters();;
      }
      break;
  }
}

void lcdMenuSettings(byte line, boolean doAction) {
  currentMenu = min(currentMenu, 16); // need to put the max number of items in the menu
  lcd.setCursor(0, line);

  byte currentParameter = 0;
  float currentFactor = 1;
  char currentUnit[4] = "";

  switch (currentMenu % 10 + line) {
    case 0:
      lcd.print(F("Param A"));
      currentParameter = 0;
      currentFactor = 1;
      currentUnit[0] = "°C";
      break;
    case 1:
      lcd.print(F("Param B"));
      currentParameter = 1;
      currentFactor = 10;
      currentUnit[0] = "mmHg";
      break;
    case 2:
      lcd.print(F("Param C"));
      currentParameter = 2;
      currentFactor = 0.1;
      break;
    case 3:
      lcd.print(F("Param D"));
      break;
    case 4:
      lcd.print(F("Param E"));
      break;
    case 5:
      lcd.print(F("Param F"));
      break;
    case 6:
      lcd.print(F("Exit"));
      if (doAction) {
        currentMenu = 1;
        return;
      }
      break;
  }
  lcdBlankLine();
  lastMenu=true;
  lcd.setCursor(0,line+1);
  if (doAction) {
    captureCounter = ! captureCounter;
    
    if (captureCounter) {
      
    } else {
      
      // need to save the parameter
    }
  }
  lcd.print(((float)getParameter(currentParameter))*currentFactor);
  lcd.print(" ");
  lcd.print(currentUnit);
}

void lcdBlankLine() {
  lcd.print(F("                "));
}

