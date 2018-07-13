// Example to determine percent CPU time
// saved by sleeping during I2C transfers.
// Requires a DS1307 RTC.
#include <NilRTOS.h>

// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial to save RAM.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial

#include <TwiMaster.h>
TwiMaster twi;

// DS1307 address
#define DS1307ADDR 0XD0

volatile uint32_t loopCount;
//------------------------------------------------------------------------------
// Declare a stack with 64 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 64);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {
uint8_t rtcAdd = 0;
uint8_t buf[8];

  while (TRUE) {

    // Sleep so idle thread can execute.
    loopCount = 0;
    nilThdSleepMilliseconds(1000);

    // Idle loop rate while Thread 1 sleeps.
    uint32_t sleepRate  = loopCount;

    loopCount = 0;
    uint32_t m = micros();

    // Set DDS1307 read address.
    bool wr = twi.transfer(DS1307ADDR | I2C_WRITE, &rtcAdd, 1);

    // Read DS1307 data time registers.
    bool rd = twi.transfer(DS1307ADDR | I2C_READ, buf, 7);

    m = micros() - m;
    
    // Idle loop rate while Thread 1 is active.
    uint32_t activeRate = 1000000*loopCount/m;
    
    // Check for I/O errors.
    if (!rd || !wr) {
      Serial.println("I/O errors");
      continue;
    }

    // Precent time available to idle thread during I2C transfers.
    uint32_t idlePercent = 100*activeRate/sleepRate;

    // print date time
    Serial.print("20");
    for (int i = 6; i >= 0; i--){
      // Skip day of week.
      if (i == 3) continue;
      if (buf[i] < 10) Serial.print('0');
      Serial.print(buf[i], HEX);
      if (i == 6 || i == 5) Serial.print('-');
      if (i == 2 || i == 1) Serial.print(':');
      if (i == 4) Serial.print(' ');
    }
    Serial.print(", Time: ");
    Serial.print(m);
    Serial.print(" usec, Idle Loop: ");
    Serial.print(idlePercent);
    Serial.println('%');
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

  twi.begin(I2C_100KHZ);
//  twi.begin(I2C_400KHZ);

  // start kernel
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.
void loop() {
  noInterrupts();
  loopCount++;
  interrupts();
}