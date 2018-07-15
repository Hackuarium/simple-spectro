// Simple Example of the FIFO class.

#include <NilRTOS.h>

// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial to save RAM.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial

#include <NilFIFO.h>

// FIFO with ten ints.
NilFIFO<int, 10> fifo;
//------------------------------------------------------------------------------
// Declare a stack with 64 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 64);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {
  int n = 0;
  while (TRUE) {

    // Sleep for 400 ticks (1024 usec per tick).
    nilThdSleep(400);
    
    // Get a free FIFO slot.
    int* p = fifo.waitFree(TIME_IMMEDIATE);
    
    // Continue if no free space.
    if (p == 0) continue;
    
    // Store count in FIFO.
    *p = n++;

    // Signal idle thread data is availabile.
    fifo.signalData();
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

  // Check for data.  Use TIME_IMMEDIATE to prevent sleep in idle thread.
  int* p = fifo.waitData(TIME_IMMEDIATE);
  
  // return if no data
  if (!p) return;
  
  // Fetch and print data.
  int n = *p;
  Serial.println(n);
  
  // Signal FIFO slot is free.
  fifo.signalFree();
}
