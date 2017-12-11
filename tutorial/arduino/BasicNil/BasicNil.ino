#include <NilRTOS.h>

void setup() {
  nilSysBegin();
}
void loop() {}

NIL_WORKING_AREA(waThread1, 16);
NIL_THREAD(Thread1, arg) {
  const uint8_t LED_PIN = 10;
  pinMode(LED_PIN, OUTPUT);
  while (TRUE) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
    nilThdSleep(10); // need to use this method otherwise next thread will not be executed
  }
}

NIL_WORKING_AREA(waThread2, 128);
NIL_THREAD(Thread2, arg) {
  Serial.begin(9600);
  while (TRUE) {
    Serial.println(millis()); 
     nilThdSleep(2500);
  }
}

NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY("thread1", Thread1, NULL, waThread1, sizeof(waThread1))
NIL_THREADS_TABLE_ENTRY("thread2", Thread2, NULL, waThread2, sizeof(waThread2))
NIL_THREADS_TABLE_END()

