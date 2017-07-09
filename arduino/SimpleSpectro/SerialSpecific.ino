#include <FreqCount.h>

void processSpecificCommand(char* data, char* paramValue, Print* output) {
  switch (data[0]) {
    case 'r':


      FreqCount.begin(1000);
      nilThdSleepMilliseconds(1100);
      unsigned long count = FreqCount.read();
      Serial.println(count);


      break;

  }
}

void printSpecificHelp(Print * output) {
  output->println(F("(r)ed"));
  output->println(F("(g)reen"));
  output->println(F("(b)lue"));
}

