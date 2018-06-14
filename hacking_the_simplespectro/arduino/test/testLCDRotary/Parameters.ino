
#include <avr/eeprom.h>


#define MAX_PARAM 26



#define EE_START_PARAM           0 // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM            (MAX_PARAM*2-1) // The last parameter is stored at byte 50-51

#define EEPROM_MIN_ADDR            0
#define EEPROM_MAX_ADDR          511

// value that should not be taken into account
// in case of error the parameter is set to this value
#define ERROR_VALUE  -32768

int parameters[MAX_PARAM];

void setupParameters() {
  //We copy all the value in the parameters table
  eeprom_read_block((void*)parameters, (const void*)EE_START_PARAM, MAX_PARAM * 2);
}

int getParameter(byte number) {
  return parameters[number];
}

void setParameter(byte number, int value) {
  parameters[number] = value;
}


void setAndSaveParameter(byte number, int value) {
  parameters[number] = value;
  //The address of the parameter is given by : EE_START_PARAM+number*2
  eeprom_write_word((uint16_t*) EE_START_PARAM + number, value);
}

void resetParameters() {
  setAndSaveParameter(PARAM_A, 0);
  setAndSaveParameter(PARAM_B, 1);
  setAndSaveParameter(PARAM_C, 2);
  setAndSaveParameter(PARAM_D, 3);
  setAndSaveParameter(PARAM_E, 4);
  setAndSaveParameter(PARAM_F, 5);
}

