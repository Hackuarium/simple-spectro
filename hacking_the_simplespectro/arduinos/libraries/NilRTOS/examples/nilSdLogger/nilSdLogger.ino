// Simple ADC data logger that demonstrates NilAnalog, NilFIFO, and NilTimer1.
#include <SdFat.h>
#include <NilRTOS.h>
#include <NilAnalog.h>
#include <NilFIFO.h>
#include <NilTimer1.h>

// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial to save RAM.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial
//------------------------------------------------------------------------------
// Time between points in microseconds.
// Maximum value is 4,194,304 (2^22) usec.
const uint32_t PERIOD_USEC = 1000;

// Number of ADC channels to log
const uint8_t NADC = 2;

// FIFO buffer size. Adjust so unused idle thread stack is about 100 bytes.
const size_t FIFO_SIZE_BYTES = 950;

// Type for a data record.
// Warning: High 6-bits of adc[0] are used for the overrun count.
//          If you use a higher precision sensor, add a separate overrun field.
struct Record_t {
  uint16_t adc[NADC];
};

// Number of data records in the FIFO.
const size_t FIFO_DIM = FIFO_SIZE_BYTES/sizeof(Record_t);

// Declare FIFO with overrun and minimum free space statistics.
NilStatsFIFO<Record_t, FIFO_DIM> fifo;
//------------------------------------------------------------------------------
// SD card chip select pin.
const uint8_t sdChipSelect = SS;

// SD file system.
SdFat sd;

// Log file.
SdFile file;
//------------------------------------------------------------------------------
// Declare a stack with 16 bytes beyond context switch and interrupt needs.
// The highest priority thread requires less stack than other threads.
NIL_WORKING_AREA(waThread1, 16);

// Declare thread function for thread 1.
NIL_THREAD(Thread1, arg) {

  // Check for very fast reads.
  if (NADC*160 > PERIOD_USEC) {
    // Set ADC prescaler to 64 for very fast reads.
    nilAnalogPrescalar(ADC_PS_64);
  }
  // Initialize ADC by doing first read.
  nilAnalogRead(0);

  // Start timer 1 with a period of PERIOD_USEC.
  nilTimer1Start(PERIOD_USEC);

  // Record data until serial input is available.
  while (!Serial.available()) {

    // Sleep until it's time for next data point.
    if (!nilTimer1Wait()) {
      // Took too long so count an overrun.
      fifo.countOverrun();
      continue;
    }

    // Get a free buffer.
    Record_t* p = fifo.waitFree(TIME_IMMEDIATE);

    // Skip the point if no buffer is available , fifo will count overrun.
    if (!p) continue;

    // Read ADCs
    for (int i = 0; i < NADC; i++) {
      p->adc[i] = nilAnalogRead(i);
    }

    // Save count of overruns since last point in high 6-bits of adc[0].
    uint16_t tmp = fifo.overrunCount();
    p->adc[0] |= tmp > 63 ? (63 << 10) : tmp << 10;

    // Signal SD write thread that new data is ready.
    fifo.signalData();
  }
  // Done, sleep forever.
  nilThdSleep(TIME_INFINITE);
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

  // Initialize SD and create or open and truncate the data file.
  if (!sd.begin(sdChipSelect)
    || !file.open("DATA.CSV", O_CREAT | O_WRITE | O_TRUNC)) {
    Serial.println(F("SD problem"));
    sd.errorHalt();
  }
  // Write the file header.
  file.print(F("PERIOD_USEC,"));
  file.println(PERIOD_USEC);
  for (int i = 0; i < NADC; i++) {
    file.print(F("ADC"));
    file.printField(i, ',');
  }
  file.println(F("Overruns"));

  // Throw away serial input.
  while (Serial.read() >= 0) {
    delay(10);
  }
  Serial.println(F("type any character to end"));

  // Start kernel.
  nilSysBegin();
}
//------------------------------------------------------------------------------
// Write data to the SD in the idle loop.
//
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.
void loop() {
  // Maximum SD write latency.
  uint32_t maxLatency = 0;

  // Record data until serial data is available()
  while (!Serial.available()) {

    // Check for an available data record in the FIFO.
    Record_t* p = fifo.waitData(TIME_IMMEDIATE);

    // Continue if no available data records in the FIFO.
    if (!p) continue;

    // Write start time.
    uint32_t u = micros();

    // Overruns are in the high 6-bits of adc[0].
    uint16_t overruns = p->adc[0] >> 10;
    p->adc[0] &= 0X3FF;

    for (int i = 0; i < NADC; i++) {
      // Print ADC value and a comma.
      file.printField(p->adc[i], ',');
    }
    // Print overrun count and CR/LF.
    file.printField(overruns, '\n');

    u = micros() - u;
    if (u > maxLatency) maxLatency = u;

    // Signal the read thread that the record is free.
    fifo.signalFree();
  }
  // Done, close the file and print stats.
  file.close();
  Serial.println(F("Done!"));
  Serial.print(F("Max Write Latency: "));
  Serial.print(maxLatency);
  Serial.println(F(" usec"));
  nilPrintUnusedStack(&Serial);
  fifo.printStats(&Serial);
  while (1) {}
}