/* Example of a handler thread triggered from an ISR by using a semaphore.
 * The handler message with response time should occur between the
 * "High" and "Low" messages from thread 2.
 */
#include <NilRTOS.h>

// Uncomment the next two lines to save RAM and flash
// with the smaller unbuffered NilSerial library.
// #include <NilSerial.h>
// #define Serial NilSerial

// Pin used to trigger interrupt.
const uint8_t INTERRUPT_PIN = 2;

// Declare and initialize the semaphore.
SEMAPHORE_DECL(isrSem, 0);

// Low bits of ISR entry time in micros.
volatile uint16_t tIsr = 0;
//------------------------------------------------------------------------------
/* Fake ISR, normally void isrFcn()
 * would be replaced by something like
 * NIL_IRQ_HANDLER(INT0_vect).
 */
void isrFcn() {

  /* On AVR this forces compiler to save registers r18-r31.*/
  NIL_IRQ_PROLOGUE();
  
  /* IRQ handling code, preemptable if the architecture supports it.*/
  
  /* Save low bits of micros(). */
  tIsr = micros();
  
  /* Nop on AVR.*/
  nilSysLockFromISR();
  
  /* Invocation of some I-Class system APIs, never preemptable.*/
  
  /* Signal handler thread. */
  nilSemSignalI(&isrSem);
  
  /* Nop on AVR.*/
  nilSysUnlockFromISR();
 
  /* More IRQ handling code, again preemptable.*/
 
  /* Epilogue performs rescheduling if required.*/
  NIL_IRQ_EPILOGUE();
}
//------------------------------------------------------------------------------
// Handler thread for interrupt.

// Declare a stack with 64 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 64);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {
  while (1) {
    // wait for event
    nilSemWait(&isrSem);
    
    // Save time.
    uint16_t t = micros();    
    
    // Print message with elapsed time.

    Serial.print(F("Handler: "));
    Serial.print(t - tIsr);
    Serial.println(F(" usec"));
  }
}
//------------------------------------------------------------------------------
// Task that generates an interrupt by toggling INTERRUPT_PIN.

// Declare a stack with 64 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread2, 64);

// Declare thread function for thread 2.
NIL_THREAD(Thread2, arg) {
  Serial.begin(9600);
  
  pinMode(INTERRUPT_PIN, OUTPUT);
  
  // attach interrupt function
  attachInterrupt(0, isrFcn, RISING);
  
  while (1) {
    // Cause an interrupt.  This is normally done by external event.
    Serial.println(F("High"));
    digitalWrite(INTERRUPT_PIN, HIGH);
    
    // The interrupt should cause thread 1 to run here.
    
    // Set pin LOW.
    Serial.println(F("Low"));
    digitalWrite(INTERRUPT_PIN, LOW);
    
    // Print Stack stats.
    nilPrintUnusedStack(&Serial);
    Serial.println();
    
    // Sleep for a second.
    nilThdSleepMilliseconds(1000);
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
NIL_THREADS_TABLE_ENTRY("Thread1", Thread1, NULL, waThread1, sizeof(waThread1))
NIL_THREADS_TABLE_ENTRY("Thread2", Thread2, NULL, waThread2, sizeof(waThread2))
NIL_THREADS_TABLE_END()
//------------------------------------------------------------------------------
void setup() {
  // Start NilRTOS.
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.
void loop() {
  // Not used.
}
