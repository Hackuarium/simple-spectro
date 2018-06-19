// nilSdLogger.ino is a cleaner version of this
// example using new Nil RTOS features.

/* Data logger based on a FIFO to decouple SD write latency from data
 * acquisition timing.
 *
 * The FIFO uses two semaphores to synchronize between threads.
 */
#include <NilRTOS.h>
// Use NilAnalog to allow the sensor read thread to sleep during ADC conversion.
#include <NilAnalog.h>
#include <SdFat.h>

// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial to save RAM.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial

// SD chip select pin.
const uint8_t sdChipSelect = SS;

// Period between points in units of 1024 usec.
#define PERIOD_TICKS 2

// Number of ADC chanels to log.
const uint8_t NUM_ADC = 3;

// Size of fifo in bytes.
// Adjust so the idle thread has about 100 free bytes.
const size_t FIFO_SIZE_BYTES = 900;
//------------------------------------------------------------------------------
// SD file system.
SdFat sd;

// Log file.
SdFile file;

// Maximum overrun count.
uint16_t maxOverrunCount = 0;
//------------------------------------------------------------------------------
// Fifo definitions.

#if PERIOD_TICKS < 50
typedef uint16_t period_t;
#else  // PERIOD_TICKS
typedef uint32_t period_t;
#endif  // PERIOD_TICKS

// Type for data record.
struct FifoItem_t {
  period_t usec;   // Point start time in usec.

  uint16_t value[NUM_ADC];  // ADC values.

  uint16_t overruns;  // Count of data overruns since last point.
};

const uint16_t FIFO_SIZE = FIFO_SIZE_BYTES/sizeof(FifoItem_t);

// Array of fifo data records.
FifoItem_t fifoArray[FIFO_SIZE];

// Count of data records in the fifo.
SEMAPHORE_DECL(fifoData, 0);

// Count of free records in the fifo.
SEMAPHORE_DECL(fifoSpace, FIFO_SIZE);
//------------------------------------------------------------------------------
// Sensor read thread.

// Declare a stack with 16 bytes beyond context switch and interrupt needs.
NIL_WORKING_AREA(waThread1, 16);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {

  // Index of record to be filled.
  size_t fifoHead = 0;

  // Count of overrun errors.
  int overrunCount = 0;

  // Time for next read.
  systime_t wakeTime = nilTimeNow();

  while (1) {
    wakeTime += PERIOD_TICKS;

    // Sleep until time for next data point
    nilThdSleepUntil(wakeTime);

    // Get an empty record.
    if (nilSemWaitTimeout(&fifoSpace, TIME_IMMEDIATE) != NIL_MSG_OK) {
      // Don't count overrun if at end of run.
      if (Serial.available()) continue;

      // Fifo full, count missed point.
      if (++overrunCount > maxOverrunCount) {
        maxOverrunCount = overrunCount;
      }
      continue;
    }
    // Pointer to empty record.
    FifoItem_t* p = &fifoArray[fifoHead];

      // Start time in usec.
      p->usec = micros();

    // Read ADC data.
    for (int i = 0; i < NUM_ADC; i++) {
      // nilAnalogRead() sleeps during ADC conversion.
      p->value[i] = nilAnalogRead(i);
    }

    p->overruns = overrunCount;
    overrunCount = 0;
    
    // Signal new data for SD write thread.
    nilSemSignal(&fifoData);

    // Advance FIFO index.
    fifoHead = fifoHead < (FIFO_SIZE - 1) ? fifoHead + 1 : 0;
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

  Serial.println(F("type any character to begin"));
  while (Serial.read() < 0);

  // Can read maximum of six ADC values per tick.
  if (6*PERIOD_TICKS < NUM_ADC) {
    Serial.println(F("Halting, too many ADC reads per tick."));
    while (1) {}
  }

  // Initialize SD and create or open and truncate data file.
  if (!sd.begin(sdChipSelect)
    || !file.open("DATA.CSV", O_CREAT | O_WRITE | O_TRUNC)) {
    Serial.println(F("SD problem"));
    sd.errorHalt();
  }
  file.print(F("Period,"));
  for (int i = 0;i < NUM_ADC; i++) {
    file.print(F("ADC"));
    file.print(i);
    file.print(',');
  }
  file.println(F("overruns"));

  // Throw away serial input.
  while (Serial.read() >= 0) {
    delay(10);
  }
  Serial.println(F("type any character to end"));

  // Start kernel.
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Write SD in loop.
//
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.

// FIFO index for record to be written.
size_t fifoTail = 0;

// Time in micros for last point.
period_t last = 0;

// Maximum SD write latency for a record.
uint32_t maxLatency = 0;

// Minimum free record count.
cnt_t minFreeCount = FIFO_SIZE;

// Don't write interval for first point.
bool first = true;

void loop() {

  // Check for end run.
  if (Serial.available()) {

    // Close file, print memory stats, possible error message, and stop.
    file.close();
    Serial.println(F("Done"));
    Serial.print(F("FIFO record count: "));
    Serial.println(FIFO_SIZE);
    Serial.print(F("Minimum free record count: "));
    Serial.println(minFreeCount);
    Serial.print(F("Maximum SD write latency: "));
    Serial.print(maxLatency);
    Serial.println(F(" usec"));
    nilPrintUnusedStack(&Serial);
    if (maxOverrunCount) {
      Serial.println();
      Serial.println(F("** overrun errors **"));
      Serial.print(F("Maximum overrun count: "));
      Serial.println(maxOverrunCount);
    }
    // Done!
    while(1);
  }

  // Try to access yhe next data point. The idle thread must not block.
  // Use TIME_IMMEDIATE so nilWaitSemTimeout will not block.
  if (nilSemWaitTimeout(&fifoData, TIME_IMMEDIATE ) != NIL_MSG_OK) {
    return;
  }

  FifoItem_t* p = &fifoArray[fifoTail];

  // Measure write latency for record.
  uint32_t latency = micros();

    // Print interval between points.
    if (first) {
      first = false;
      file.write("NA,");
    }
    else {
      file.printField(p->usec - last, ',');
    }
    // Remember time of last data point.
    last = p->usec;

  // Print ADC values.
  for (int i = 0; i < NUM_ADC; i++) {
    file.printField(p->value[i],',');
  }
  file.printField(p->overruns, '\n');

  // Check latency.
  latency = micros() - latency;
  if (latency > maxLatency) maxLatency = latency;

  // Check number of free records
  cnt_t cnt = nilSemGetCounter(&fifoSpace);
  if (cnt < minFreeCount) minFreeCount = cnt;

  // Release free data record.
  nilSemSignal(&fifoSpace);

  // Advance FIFO index.
  fifoTail = fifoTail < (FIFO_SIZE - 1) ? fifoTail + 1 : 0;
}