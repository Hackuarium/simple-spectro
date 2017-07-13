#include <avr/eeprom.h>

#define EE_PARAMETERS            140 // 32 bytes

#define EE_TARGET_EVENT_TYPES    224 // 32 bytes
#define EE_TARGET_EVENT_TIMES    256 // 128 bytes
#define EE_TARGET_EVENT_PARAMS   384 // 128 bytes


#define EEPROM_MIN_ADDR            0
#define EEPROM_MAX_ADDR          511

// code from http://www.arduino.cc/playground/Code/EepromUtil
void getStatusEEPROM(Print* output) {
  int bytesPerRow = 16;
  int i;
  int j;
  byte b;
  char buf[4];

  j = 0;

  // go from first to last eeprom address
  for (i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++) {
    if (j == 0) {
      sprintf(buf, "%03X", i);
      output->print(buf);
      output->print(F(": "));
    }

    // read current byte from eeprom
    b = eeprom_read_byte(i);
    sprintf(buf, "%02X ", b);
    j++;
    if (j == bytesPerRow) {
      j = 0;
      output->println(buf);
      nilThdSleepMilliseconds(25);
    }
    else {
      output->print(buf);
    }
  }
}


