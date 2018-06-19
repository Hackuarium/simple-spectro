/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <NilRTOS.h>

// The LED is attached to pin 13 on Arduino.
const uint8_t LED_PIN = 13;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(sem, 0);
//------------------------------------------------------------------------------
/*
 * Thread 1, turn the LED off when signalled by thread 2.
 */
// Declare a stack with 128 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 128);

// Declare the thread function for thread 1.
NIL_THREAD(Thread1, arg) {
  while (TRUE) {
    
    // Wait for signal from thread 2.
    nilSemWait(&sem);
    
    // Turn LED off.
    digitalWrite(LED_PIN, LOW);
  }
}
//------------------------------------------------------------------------------
/*
 * Thread 2, turn the LED on and signal thread 1 to turn the LED off.
 */
// Declare a stack with 128 bytes beyond context switch and interrupt needs. 
NIL_WORKING_AREA(waThread2, 128);

// Declare the thread function for thread 2.
NIL_THREAD(Thread2, arg) {

  pinMode(LED_PIN, OUTPUT);
  
  while (TRUE) {
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);
    
    // Sleep for 200 milliseconds.
    nilThdSleepMilliseconds(200);
    
    // Signal thread 1 to turn LED off.
    nilSemSignal(&sem);
    
    // Sleep for 200 milliseconds.   
    nilThdSleepMilliseconds(200);
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
  // Start Nil RTOS.
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Loop is the idle thread.  The idle thread must not invoke any 
// kernel primitive able to change its state to not runnable.
void loop() {
  // Not used.
}
