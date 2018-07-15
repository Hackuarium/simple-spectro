// Test semaphores.

#include <NilRTOS.h>

// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial to save RAM.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial

SEMAPHORE_DECL(sem, 0);

#define nilAssert1(c) nilAssert2(c, #c)

#define nilAssert2(c, m) {         \                                      
  if (!(c)) {                      \
    Serial.print(F(m));            \
    Serial.print(", at line ");    \
    Serial.println(__LINE__);      \                                                   
    while(1);                      \                                          
  }                                \                                        
}
//------------------------------------------------------------------------------
// Declare a stack with 64 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 64);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {
  
  nilAssert1(NIL_MSG_OK == nilSemWait(&sem));
  nilAssert1(NIL_MSG_RST == nilSemWait(&sem));
  nilAssert1(NIL_MSG_OK == nilSemWaitTimeout(&sem, 100));  
  Serial.println("Thd1 Done");  
  while (TRUE) {
   // Allow lower priority threads to execute.
   nilThdSleep(1);
  }
}
//------------------------------------------------------------------------------
// Declare a stack with 64 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread2, 64);

// Declare thread function for thread 2.
NIL_THREAD(Thread2, arg) {
   uint32_t m = micros();  
   m = micros() - m;
   Serial.print("micros overhead = ");
   Serial.println(m);
   
    nilAssert1(sem.cnt == -1);
    m = micros();
    nilSemSignal(&sem);  
    m = micros() - m;
    Serial.print("sem switch tasks micros = ");
    Serial.println(m);
    nilAssert1(sem.cnt == -1);
    nilSemReset(&sem, 0);
    nilAssert1(sem.cnt == -1);
    nilSemSignal(&sem);  
    nilAssert1(sem.cnt == 0);
    
    m = micros();
    nilAssert1(NIL_MSG_TMO == nilSemWaitTimeout(&sem, TIME_IMMEDIATE));
    m = micros() - m;
    Serial.print("sem immediate timeout = ");
    Serial.println(m);
    nilAssert1(sem.cnt == 0);   
    nilSemSignal(&sem);
    nilAssert1(sem.cnt == 1);
    m = micros();    
    nilAssert1(NIL_MSG_OK == nilSemWaitTimeout(&sem, 100));
    m = micros() - m;
    Serial.print("sem immediate OK = ");
    Serial.println(m);    
    nilAssert1(sem.cnt == 0);
    nilAssert1(NIL_MSG_TMO == nilSemWaitTimeout(&sem, 100)); 
    nilAssert1(sem.cnt == 0);
    
    Serial.println("Thd2 Done");
    while (1);
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
NIL_THREADS_TABLE_ENTRY(NULL, Thread2, NULL, waThread2, sizeof(waThread2))
NIL_THREADS_TABLE_END()
//------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);
  
  nilAssert1(sem.cnt == 0);  
  
  // start kernel
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.
void loop() {
  // not used
}
