/* FreqCount - Example with serial output
   http://www.pjrc.com/teensy/td_libs_FreqCount.html

   This example code is in the public domain.
*/
#include <FreqCount.h>

void setup() {
  Serial.begin(57600);
}

unsigned long total = 0;

void loop() {
  FreqCount.begin(1000);
  delay(1000);
  if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    Serial.println(count);
  }

// We check that 1000 short acquisitions yield the same result as one long

  total = 0;
  for (int i = 0; i < 1000; i++) {
    FreqCount.begin(1);
    delay(1);
    if (FreqCount.available()) {
      total += FreqCount.read();
    }
  }
  Serial.println(total);

  Serial.println("");



}

