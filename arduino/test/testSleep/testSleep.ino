
#include <avr/sleep.h>

// https://www.nongnu.org/avr-libc/user-manual/group__avr__sleep.html

byte wakeUpPin = 1;

void setup() {
  // put your setup code here, to run once:
for (byte i=0; i<30; i++) {
  pinMode(i, INPUT);
  digitalWrite(i, LOW);
}

  
  Serial.begin(9600);
  for (byte i = 15; i != 0; i--) {
    Serial.print("Going to sleep in ");
    Serial.print(i);
    Serial.println("s");
    delay(1000);
  }
}

void loop() {
  Serial.println("Going to sleep");
  delay(100);
  sleepNow();
  Serial.println("Awake");
  for (byte i = 5; i != 0; i--) {
    Serial.print("Going to sleep in ");
    Serial.print(i);
    Serial.println("s");
    delay(1000);
  }
}


// interrupt service routine in sleep mode
void wake ()
{
  sleep_disable ();         // first thing after waking from sleep:
  detachInterrupt (digitalPinToInterrupt (2));      // stop LOW interrupt on D2
}  // end of wake

void sleepNow () {
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  noInterrupts ();          // make sure we don't get interrupted before we sleep
  sleep_enable ();          // enables the sleep bit in the mcucr register
  //  attachInterrupt (digitalPinToInterrupt (wakeUpPin), wake, CHANGE);
  // interrupts ();           // interrupts allowed now, next instruction WILL be executed
  sleep_cpu ();            // here the device is put to sleep
}
