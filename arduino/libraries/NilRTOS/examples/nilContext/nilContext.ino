/* Example to demonstrate the time require for a semaphore signal plus
 * a thread context switch.
 *
 * Connect a scope to pin 13.
 * Measure the difference in time between the first pulse with no context
 * switch and the second pulse started in thread 2 and ended in thread 1.
 * The difference should be about 12 usec on a 16 MHz 328 Arduino.
 */
#include <NilRTOS.h>

// Arduino LED pin.
const uint8_t LED_PIN = 13;

// Declare the semaphore used to trigger a context switch.
SEMAPHORE_DECL(sem, 0);
//------------------------------------------------------------------------------
/*
 * Thread 1 - high priority thread to set pin low.
 */
// Declare a stack with 128 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 128);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {

  while (TRUE) {
    // Wait for semaphore signal from thread 2.
    nilSemWait(&sem);
    
    // Set LED pin low to end second pulse.
    digitalWrite(LED_PIN, LOW);
  }
}
//------------------------------------------------------------------------------
/*
 * Thread 2 - lower priority thread to toggle LED and trigger thread 1.
 */
// Declare a stack with 128 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread2, 128);

// Declare thread function for thread 2.
NIL_THREAD(Thread2, arg) {

  pinMode(LED_PIN, OUTPUT);
  
  while (TRUE) {
  
    // Generate first pulse to get time with no context switch.
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
    
    // Start second pulse.
    digitalWrite(LED_PIN, HIGH);
    
    // Trigger a context switch to thread 1.
    nilSemSignal(&sem);
    
    // Sleep until next tick, 1024 microseconds tick on Arduino.
    nilThdSleep(1);
  }
}
//------------------------------------------------------------------------------
/*
 * Threads static table, one entry per thread.  A thread's priority is
 * determined by its position in the table with highest priority first.
 *
 * These threads start with a null argument.  A thread's name may also
 * be null to save RAM since the name is currently not used.
 */
NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY("thread1", Thread1, NULL, waThread1, sizeof(waThread1))
NIL_THREADS_TABLE_ENTRY("thread2", Thread2, NULL, waThread2, sizeof(waThread2))
NIL_THREADS_TABLE_END()
//------------------------------------------------------------------------------
void setup() {
  // Start NilRTOS.
  nilSysBegin();
}
//------------------------------------------------------------------------------
void loop() {
  // Not used.
}
