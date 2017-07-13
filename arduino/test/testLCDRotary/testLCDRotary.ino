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

#define PARAM_A           0
#define PARAM_B           1
#define PARAM_C           2
#define PARAM_D           3
#define PARAM_E           4
#define PARAM_F           5


boolean rotaryPressed = false;
int rotaryCounter = 0;
int rotaryCaptureCounter = 0;
int currentMenu = 0;
boolean lastMenu;
boolean captureCounter = false; // use when you need to setup a parameter from the menu
long lastRotaryEvent = millis();

void setup() {
  Serial.begin(115200);
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
      } else if (rotaryCounter > 0) {
        currentMenu += min(rotaryCounter, 9 - currentMenu % 10);
      }
    } else {
      rotaryCaptureCounter = rotaryCounter;
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

    for (byte line = 0; line < LCD_NB_ROWS; line++) {
      bool doAction = false;
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
  lcd.print("A:");
  lcd.print(getParameter(PARAM_A));
  lcdBlankLine();
  lcd.setCursor(8, 0);
  lcd.print("B:");
  lcd.print(getParameter(PARAM_B));
  lcdBlankLine();
  lcd.setCursor(0, 1);
  lcd.print("C:");
  lcd.print(getParameter(PARAM_C));
  lcdBlankLine();
  lcd.setCursor(8, 1);
  lcd.print("D:");
  lcd.print(getParameter(PARAM_D));
  lcdBlankLine();
}


void lcdNumberLine(byte line) {
  lcd.print(currentMenu % 10 + line + 1);
  if (line == 0) {
    lcd.print(".*");
  } else {
    lcd.print(". ");
  }
}

void lcdMenuHome(byte line, boolean doAction) {
  currentMenu = min(currentMenu, 4); // need to put the max number of items in the menu
  lcd.setCursor(3, line);
    lcd.setCursor(0, line);
  lcdNumberLine(line);
  
  switch (currentMenu + line) {
    case 0:
      lcd.print(F("Status"));
      break;
    case 1:
      lcd.print(F("Settings"));
      if (doAction) {
        currentMenu = 10;
      }
      break;
    case 2:
      lcd.print(F("Acquire"));
      break;
    case 3:
      lcd.print(F("Backlight"));
      if (doAction) {
        digitalWrite(LCD_BL, !digitalRead(LCD_BL));
      }
      break;
    case 4:
      lcd.print(F("Reset"));
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
  char currentUnit[5] = "\0";

  switch (currentMenu % 10 + line) {
    case 0:
      lcd.print(F("Param A"));
      currentParameter = 0;
      currentFactor = 1;
      strcpy(currentUnit, "\337C\0"); // 337 is in octal (0xDF) !!!
      break;
    case 1:
      lcd.print(F("Param B"));
      currentParameter = 1;
      currentFactor = 10;
      strcpy(currentUnit, "mmHg\0");
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
  lcdBlankLine();
    lcd.setCursor(0, line + 1);
    lcdBlankLine();
      if (doAction) {
        currentMenu = 1;
        return;
      }
      break;
  }
  lcdBlankLine();
  lastMenu = true;
  lcd.setCursor(0, line + 1);
  lcd.print(((float)getParameter(currentParameter))*currentFactor);

  lcd.setCursor(0, line + 1);
  if (doAction) {
    captureCounter = ! captureCounter;

    if (! captureCounter) {
      setAndSaveParameter(currentParameter, getParameter(currentParameter));
    }

  }
  if (captureCounter) {
    if (millis() % 1000 < 500) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
    setParameter(currentParameter, getParameter(currentParameter) + rotaryCaptureCounter);
    rotaryCaptureCounter = 0;
  }
  lcd.print(((float)getParameter(currentParameter))*currentFactor);
  lcd.print(" ");
  lcd.print(currentUnit);
}

void lcdBlankLine() {
  lcd.print(F("                "));
}

