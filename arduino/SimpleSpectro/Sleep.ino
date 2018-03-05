#include <avr/sleep.h>

void wakeUp () {
  sleep_disable ();         // first thing after waking from sleep:
  detachInterrupt (digitalPinToInterrupt (ROT_B));      // stop LOW interrupt on D2
  wdt_enable(WDTO_8S);  //reactivate the watchdog
  wakeUpScreen();
}

void sleepNow () {
  noInterrupts ();          // make sure we don't get interrupted before we sleep
  wdt_disable();
  sleep_enable ();          // enables the sleep bit in the mcucr register
  sleepScreen();
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  attachInterrupt (digitalPinToInterrupt (ROT_B), empty, CHANGE); // there was already and event in the interrupt
  nilThdSleepMilliseconds(2);
  attachInterrupt (digitalPinToInterrupt (ROT_B), wakeUp, CHANGE);
  interrupts ();           // interrupts allowed now, next instruction WILL be executed
  sleep_cpu ();            // here the device is put to sleep
}

void empty() {}

void sleepScreen() {
  for (byte i = 0; i < sizeof(lcdPins); i++) {
    pinMode(lcdPins[i], INPUT);
  }
}

void wakeUpScreen() {
  for (byte i = 0; i < sizeof(lcdPins); i++) {
    pinMode(lcdPins[i], OUTPUT);
  }
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH); // backlight
  pinMode(LCD_ON, HIGH); // LCD on / off
  digitalWrite(LCD_ON, HIGH); // LCD on

  nilThdSleepMilliseconds(10);
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
}

