#include <avr/sleep.h>
#include <avr/power.h>


#define INTERRUPT_PIN 7
#define INTERRUPT_ID  4



void wakeUpISR(void) {
  Serial.println('xx');
  detachInterrupt(INTERRUPT_ID);
}


void enterSleep(void) {
  attachInterrupt(INTERRUPT_ID, wakeUpISR, CHANGE);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable(); 
}


void setup() {
  Serial.begin(9600);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  Serial.println("Initialisation complete.");
}


int seconds=0;
void loop()
{
  delay(1000);
  seconds++;
  
  Serial.print("Awake for ");
  Serial.print(seconds, DEC);
  Serial.println(" second");
  
  if (seconds == 15) {
    Serial.println("Entering sleep");
    delay(200);
    seconds = 0;
    enterSleep();
  }
}

