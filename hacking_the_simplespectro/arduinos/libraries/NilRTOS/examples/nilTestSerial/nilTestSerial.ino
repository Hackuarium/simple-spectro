// Test of NilSerial.  NilSerial can be used as a stand alone library.
#include <NilRTOS.h>

// Use tiny unbuffered NilRTOS NilSerial library.
#include <NilSerial.h>

// Macro to redefine Serial as NilSerial to save RAM.
// Remove definition to use standard Arduino Serial.
#define Serial NilSerial
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Type an input line.");
  while (!Serial.available());
}
//------------------------------------------------------------------------------
void loop() {
  if (Serial.available()) {
    Serial.print((char)Serial.read());
  }
}