/* Example of a counting semaphore with three threads. */

#include <NilRTOS.h>

// Declare and initialize a semaphore for limiting access to a region.
SEMAPHORE_DECL(twoSlots, 2);
//------------------------------------------------------------------------------
// Declare the thread function for all threads.
NIL_THREAD(thdFcn, name) {
 while (true) {

  // wait for slot
  nilSemWait(&twoSlots);

    // Only two threads can be in this region at a time.
    Serial.println((char*)name);

    nilThdSleep(1000);

    // Exit region.
    nilSemSignal(&twoSlots);
    
    // Slight delay to allow a lower priority thread to enter above region.
    // Comment out the next line to see the priority effect.
    nilThdSleep(10);
  }
}
//------------------------------------------------------------------------------
/* Declare a stack with 100 bytes beyond context switch and interrupt
 * needs for each thread.
 */
NIL_WORKING_AREA(waTh1, 100);
NIL_WORKING_AREA(waTh2, 100);
NIL_WORKING_AREA(waTh3, 100);
/*
 * Threads static table, one entry per thread.  A thread's priority is
 * determined by its position in the table with highest priority first.
 *
 * These threads start with their name as their argument.  A thread's name
 * is null to save RAM since the name is currently not used.
 */
NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY(NULL, thdFcn, (void*)"Th 1", waTh1, sizeof(waTh1))
NIL_THREADS_TABLE_ENTRY(NULL, thdFcn, (void*)"Th 2", waTh2, sizeof(waTh2))
NIL_THREADS_TABLE_ENTRY(NULL, thdFcn, (void*)"Th 3", waTh3, sizeof(waTh3))
NIL_THREADS_TABLE_END()
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Start NilRTOS
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.
void loop() {
  /* not used */
}
