#define THR_LCD 1

#ifdef THR_LCD

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

#define LCD_NB_ROWS     2
#define LCD_NB_COLUMNS  16

#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


boolean rotaryPressed = false;
int rotaryCounter = 0;
int currentMenu = 0;
boolean captureCounter = false; // use when you need to setup a parameter from the menu
long lastRotaryEvent = millis();



NIL_WORKING_AREA(waThreadLcd, 128);
NIL_THREAD(ThreadLcd, arg) {
  // initialize the library with the numbers of the interface pins

  setupRotary();
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH); // backlight
  pinMode(LCD_ON, HIGH); // LCD on / off
  digitalWrite(LCD_ON, HIGH); // LCD on
  nilThdSleepMilliseconds(10);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);


  while (true) {
    lcdMenu();
    nilThdSleepMilliseconds(40);
  }
}


byte noEventCounter = 0;
void lcdMenu() {
  if (rotaryCounter == 0 && ! rotaryPressed) {
    if (noEventCounter < 255) noEventCounter++;
  } else {
    noEventCounter = 0;
  }
  if (noEventCounter > 250) {
    currentMenu = 20;
    captureCounter = false;
    noEventCounter = 0;
  }
  boolean doAction = rotaryPressed;
  rotaryPressed = false;
  int counter = rotaryCounter;
  rotaryCounter = 0;


  switch (currentMenu - currentMenu % 10) {
    case 0:
      lcdMenuHome(counter, doAction);
      break;
    case 10:
      lcdMenuSettings(counter, doAction);
      break;
    case 20:
      lcdDefault(counter, doAction);
      break;
  }
}

void lcdDefault(int counter, boolean doAction) {
  if (doAction) currentMenu = 0;
  updateCurrentMenu(counter, 1);
  if (noEventCounter < 2) lcd.clear();
  switch (currentMenu % 10) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("A:");
      lcd.print(getParameter(PARAM_A));
      lcdPrintBlank(2);
      lcd.setCursor(8, 0);
      lcd.print("B:");
      lcd.print(getParameter(PARAM_B));
      lcdPrintBlank(2);
      lcd.setCursor(0, 1);
      lcd.print("C:");
      lcd.print(getParameter(PARAM_C));
      lcdPrintBlank(2);
      lcd.setCursor(8, 1);
      lcd.print("D:");
      lcd.print(getParameter(PARAM_D));
      lcdPrintBlank(2);
      break;
    case 1:
      lcd.setCursor(8, 1);
      lcd.print("s:");
      lcd.print(millis() / 1000);
      break;
  }

}


void lcdNumberLine(byte line) {
  lcd.print(currentMenu % 10 + line + 1);
  if (line == 0) {
    lcd.print(".*");
  } else {
    lcd.print(". ");
  }
}

void updateCurrentMenu(int counter, byte maxValue) {
  if (captureCounter) return;
  if (counter < 0) {
    currentMenu += max(counter, - currentMenu % 10);
  } else if (counter > 0) {
    currentMenu += min(counter, maxValue - currentMenu % 10);
  }
}

void lcdMenuHome(int counter, boolean doAction) {
  if (noEventCounter > 2) return;
  lcd.clear();
  byte lastMenu = 5;
  updateCurrentMenu(counter, lastMenu);

  for (byte line = 0; line < LCD_NB_ROWS; line++) {
    lcd.setCursor(0, line);
    if ( currentMenu % 10 + line <= lastMenu) lcdNumberLine(line);

    switch (currentMenu % 10 + line) {
      case 0:
        lcd.print(F("Status"));
        if (doAction) {
          currentMenu = 20;
        }
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
          resetParameters();
          currentMenu = 20;
        }
        break;
        case 5:
        lcd.print(F("Test LED"));
        if (doAction) {
          testRGB();
        }
        break;
    }
    doAction = false;
  }
}

void lcdMenuSettings(int counter, boolean doAction) {

  byte lastMenu = 6;
  if (! captureCounter) updateCurrentMenu(counter, lastMenu);

  byte currentParameter = 0;
  float currentFactor = 1;
  char currentUnit[5] = "\0";

  lcd.clear();

  switch (currentMenu % 10) {
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
      if (doAction) {
        currentMenu = 1;
      }
      return;
  }

  if (doAction) {
    captureCounter = ! captureCounter;
    if (! captureCounter) {
      setAndSaveParameter(currentParameter, getParameter(currentParameter));
    }
  }
  if (captureCounter) {
    setParameter(currentParameter, getParameter(currentParameter) + counter);
  }

  lcd.setCursor(0, 1);
  if (millis() % 1000 < 500 && captureCounter) {
    lcd.print((char)255);
  } else {
    lcd.print(" ");
  }
  lcd.print(((float)getParameter(currentParameter))*currentFactor);
  lcd.print(" ");
  lcd.print(currentUnit);
}

void lcdPrintBlank(byte number) {
  for (byte i = 0; i < number; i++) {
    lcd.print(" ");
  }
}


void setupRotary() {
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_PUSH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROT_A), eventRotaryA, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROT_PUSH), eventRotaryPressed, CHANGE);
}

boolean accelerationMode = false;

void eventRotaryA() {
  int increment = digitalRead(ROT_B) * 2 - 1;
  long current = millis();
  long diff = current - lastRotaryEvent;
  lastRotaryEvent = current;
  if (diff < 15) return;
  if (diff < 50) {
    if (accelerationMode) {
      rotaryCounter -= (increment * 5);
    } else {
      accelerationMode = true;
      rotaryCounter -= increment;
    }
  } else {
    accelerationMode = false;
    rotaryCounter -= increment;
  }
}


boolean rotaryMayPress = true; // be sure to go through release. Seems to allow some deboucing

void eventRotaryPressed() {
  byte state = digitalRead(ROT_PUSH);
  if (state == 0) {
    if (rotaryMayPress) {
      rotaryPressed = true;
      rotaryMayPress = false;
    }
  } else {
    rotaryMayPress = true;
  }
}

#endif



