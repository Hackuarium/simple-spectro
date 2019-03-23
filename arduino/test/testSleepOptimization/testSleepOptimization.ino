
#include <avr/sleep.h>


#define ROT_A      0
#define ROT_B      1
#define ROT_PUSH   7

byte wakeUpPin = ROT_A;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(wakeUpPin, INPUT_PULLUP);

  Serial.begin(9600);

  attachInterrupt (digitalPinToInterrupt(wakeUpPin), empty, CHANGE);
}

void empty() {};

void loop() {
  digitalWrite(13, HIGH);
  for (byte i = 15; i != 0; i--) {
    Serial.print("Going to sleep in ");
    Serial.print(i);
    Serial.println("s");
    delay(1000);
  }
  digitalWrite(13, LOW);
  sleepNow();
  Serial.println("Awake");
}



void sleepNow () {
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);

  // No optimization: 0.84 mA

  // Disable ADC: 0.73 mA
  ADCSRA &= ~(1 << ADEN);

  cli();
  sleep_enable();
  sei();
  sleep_cpu();
  sleep_disable();

  ADCSRA |= (1 << ADEN); // enable A/D

}
