// Test nilAnalogRead to verify execution of idle loop. 

#include <NilRTOS.h>
#include <NilAnalog.h>
// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial to save RAM.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial

volatile uint16_t idleCount;
//------------------------------------------------------------------------------
// Declare a stack with 64 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 64);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {
  Serial.println("         usec val count");
  while (TRUE) {
    idleCount = 0;
    uint32_t usec = micros();
    int val = analogRead(0);
    usec = micros() - usec; 
    Serial.print("Arduino: ");
    Serial.print(usec);
    Serial.print(' ');
    Serial.print(val);
    Serial.print(' ');
    Serial.println(idleCount);

    idleCount = 0;    
    usec = micros();
    val = nilAnalogRead(0);
    usec = micros() - usec;
    Serial.print("NilRTOS: ");
    Serial.print(usec);
    Serial.print(' ');
    Serial.print(val);
    Serial.print(' ');
    Serial.println(idleCount);  

    Serial.println();
    nilThdSleep(1000);
  }
}
//------------------------------------------------------------------------------
/*
 * Threads static table, one entry per thread.  A thread's priority is
 * determined by its position in the table with highest priority first.
 *
 * These threads start with a null argument.  A thread's name is also
 * null to save RAM since the name is currently not used.
 */
NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY(NULL, Thread1, NULL, waThread1, sizeof(waThread1))
NIL_THREADS_TABLE_END()
//------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);
  // start kernel
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.
void loop() {
  while (1) {
    // Disable interrupts to insure increment is atomic.
    nilSysLock();
    idleCount++;
    nilSysUnlock();
  }
}