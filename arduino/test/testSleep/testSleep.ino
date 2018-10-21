
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
  cli();
  sleep_enable();
  sei();
  sleep_cpu();
  sleep_disable();


  // turn off brown-out enable in software
  /*
    MCUCR = bit (BODS) | bit (BODSE);
    MCUCR = bit (BODS);

    uint8_t analogStatus = ADCSRA & (1 << ADEN);
    ADCSRA &= ~(1 << ADEN); //Disable ADC: allows to win 80µA

    sleep_mode ();            // here the device is put to sleep
  */


}
