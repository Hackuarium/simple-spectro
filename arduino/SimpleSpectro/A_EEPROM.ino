#include <avr/eeprom.h>


#define EE_START_PARAM           0 // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM            (MAX_PARAM*2-1) // The last parameter is stored at byte 50-51

#define EE_QUALIFIER             (MAX_PARAM*2)



#define EEPROM_MIN_ADDR            0
#define EEPROM_MAX_ADDR          1023



#define DATA_SIZE 240
#define DATA_TYPE 0  // LONG

void setDataLong(int index, long value) {
  eeprom_write_dword((uint32_t*) (EEPROM_MAX_ADDR - 4 * index - 3), value);
}

long getDataLong(int index) {
  return eeprom_read_dword((uint32_t*) (EEPROM_MAX_ADDR - 4 * index - 3));
}


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


