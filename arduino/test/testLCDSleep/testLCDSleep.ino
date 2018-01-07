#include <LiquidCrystal.h>
#include <avr/sleep.h>

byte wakeUpPin = 1;


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
  Serial.begin(9600);
  for (byte i = 15; i != 0; i--) {
    Serial.print("Going to sleep in ");
    Serial.print(i);
    Serial.println("s");
    delay(1000);
  }
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
  delay(1000);

  delay(100);
  sleepNow();
}

void wakeUp () {
  sleep_disable ();         // first thing after waking from sleep:
  detachInterrupt (digitalPinToInterrupt (wakeUpPin));      // stop LOW interrupt on D2
  for (byte i = 0; i < sizeof(pins); i++) {
    pinMode(pins[i], OUTPUT);
  }
  digitalWrite(LCD_BL, HIGH);
  digitalWrite(LCD_ON, HIGH);
  delay(100);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
}

void sleepNow () {
  for (byte i = 0; i < sizeof(pins); i++) {
    pinMode(pins[i], INPUT);
  }
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  noInterrupts ();          // make sure we don't get interrupted before we sleep
  sleep_enable ();          // enables the sleep bit in the mcucr register
  attachInterrupt (digitalPinToInterrupt (wakeUpPin), wakeUp, CHANGE);
  interrupts ();           // interrupts allowed now, next instruction WILL be executed
  sleep_cpu ();            // here the device is put to sleep
}

