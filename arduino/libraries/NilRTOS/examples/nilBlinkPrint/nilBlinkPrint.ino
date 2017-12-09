/*
 * Example to demonstrate thread definition, thread sleep, the idle
 * thread, concurrent access to a variable, and NilSerial.
 */
#include <NilRTOS.h>

// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial

// LED is attached to pin 13 on Arduino.
const uint8_t LED_PIN = 13;

// Shared idle thread counter.
volatile uint32_t loopCount = 0;
//------------------------------------------------------------------------------
/*
 * Thread 1, blink the LED.
 */
// Declare a stack with 16 bytes beyond context switch and interrupt needs. 
NIL_WORKING_AREA(waThread1, 16);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {

  pinMode(LED_PIN, OUTPUT);
  
  // Flash led every 200 ms.
  while (TRUE) {
  
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);
    
    // Sleep for 50 milliseconds.
    nilThdSleepMilliseconds(50);
    
    // Turn LED off.
    digitalWrite(LED_PIN, LOW);
    
    // Sleep for 150 milliseconds.
    nilThdSleepMilliseconds(150);
  }
}
//------------------------------------------------------------------------------
/*
 * Thread 2, print thread.
 */
// Declare a stack with 100 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread2, 100);

// Declare thread function for thread 2.
NIL_THREAD(Thread2, arg) {
  // Wake time for thread sleep.
  systime_t wakeTime = nilTimeNow();
  
  Serial.begin(9600);
  
  while (TRUE) {   
    
    // Add ticks for one second.  The MS2ST macro converts ms to system ticks.
    wakeTime += MS2ST(1000);
    
    // Sleep until next second.
    nilThdSleepUntil(wakeTime);
    
    // Print loopCount for previous second.
    Serial.print(F("Count: "));
    Serial.print(loopCount);
    Serial.print(", ");
    
    // Print unused stack for thread 1, thread 2, and idle thread.
    nilPrintUnusedStack(&Serial);
    
    // Zero loopCount at start of each second.
    loopCount = 0;
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

  // Use of while loop is not required but increases loopCount increment rate. 
  while (TRUE) {
    
    // Enter kernel lock mode to prevent access to loopCount by thread 2.
    nilSysLock();
    
    // Increment of loopCount is atomic in kernel lock mode.
    loopCount++;
    
    // Leave kernel lock mode.
    nilSysUnlock();
  }
}

