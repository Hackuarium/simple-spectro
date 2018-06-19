
#include <avr/sleep.h>

byte wakeUpPin = 1;

void setup() {
  // put your setup code here, to run once:
  for (byte i = 0; i < 30; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, LOW);
  }

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  Serial.begin(9600);
  for (byte i = 15; i != 0; i--) {
    Serial.print("Going to sleep in ");
    Serial.print(i);
    Serial.println("s");
    delay(1000);
  }

 attachInterrupt (digitalPinToInterrupt (2), empty, CHANGE);

}

void empty() {};

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



void sleepNow () {
  cli();

  sleep_enable();
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);

  digitalWrite(13, LOW);
  delay(100);
  sei();
  sleep_cpu();
  sleep_disable();
  digitalWrite(13, HIGH);
}
