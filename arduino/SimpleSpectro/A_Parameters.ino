/*********************************************
   This file is used to declare the parameters
   table used by the program.

   We use the EEPROM for saving the parameters
   changed by the user during the functionment
   of the Bioreactor.

   The parameter are loaded during the boot.

   All change to important parameters are saved
   to the EEPROM
 *********************************************/


#define MAX_PARAM 26   // If the MAX_PARAM change you need to change the pointer in the EEPROM


#define PARAM_COLOR_1     0
#define PARAM_COLOR_2     1
#define PARAM_COLOR_3     2
#define PARAM_COLOR_4     3
#define PARAM_COLOR_5     4
#define PARAM_BLANK_1     5
#define PARAM_BLANK_2     6
#define PARAM_BLANK_3     7
#define PARAM_BLANK_4     8
#define PARAM_BLANK_5     9


#define PARAM_BEFORE_DELAY  10  // delay before taking blank
#define PARAM_FIRST_DELAY   11
#define PARAM_INTER_DELAY   12
#define PARAM_NUMPER_EXP    13
#define PARAM_NEXT_EXP      14 // next experiment, 0 blank and then for kinetic
#define PARAM_WAIT          15 // current time to wait
#define PARAM_NUMBER_ACQ    16 // number of acquisition of 100ms that will be taken

#define PARAM_INVERT_ROTARY 17 // invert rotary direction
#define PARAM_BATTERY       18 // invert rotary direction
#define PARAM_TEMPERATURE   19 // invert rotary direction


#define PARAM_ACTIVE_LEDS   21
#define PARAM_ERROR         22 // color used to display the results
#define PARAM_COLOR         23 // color used to display the results
#define PARAM_STATUS        24
#define PARAM_MENU          25 // current menu

#define STATUS_ONE_SPECTRUM 1
#define STATUS_KINETIC      2
#define STATUS_TEST_LEDS    3

#define INT_MAX_VALUE       32767
#define LONG_MAX_VALUE      2147483647


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

void setParameterBit(byte number, byte bitToSet) {
  bitSet(parameters[number], bitToSet);
  // parameters[number]=parameters[number] | (1 << bitToSet);
}

void clearParameterBit(byte number, byte bitToClear) {
  bitClear(parameters[number], bitToClear);
  // parameters[number]=parameters[number] & ( ~ (1 << bitToClear));
}

byte getParameterBit(byte number, byte bitToRead) {
  return bitRead(parameters[number], bitToRead);
  // return (parameters[number] >> bitToRead ) & 1;
}

void setParameter(byte number, int value) {
  parameters[number] = value;
}

void incrementParameter(byte number) {
  parameters[number]++;
}

void saveParameters() {
  for (byte i = 0; i < MAX_PARAM; i++) {
    eeprom_write_word((uint16_t*) EE_START_PARAM + i, parameters[i]);
  }
}

/*
  This will take time, around 4 ms
  This will also use the EEPROM that is limited to 100000 writes
*/
void setAndSaveParameter(byte number, int value) {
  parameters[number] = value;
  //The address of the parameter is given by : EE_START_PARAM+number*2
  eeprom_write_word((uint16_t*) EE_START_PARAM + number, value);
}


void printParameter(Print* output, byte number) {
  output->print(number);
  output->print("-");
  if (number > 25) {
    output->print((char)(floor(number / 26) + 64));
  }
  else {
    output->print(" ");
  }
  output->print((char)(number - floor(number / 26) * 26 + 65));
  output->print(": ");
  output->println(parameters[number]);
}

void printParameters(Print* output) {
  for (int i = 0; i < MAX_PARAM; i++) {
    printParameter(output, i);
  }
}

uint8_t printCompactParameters(Print* output) {
  printCompactParameters(output, MAX_PARAM);
}

uint8_t printCompactParameters(Print* output, byte number) {
  if (number > MAX_PARAM) {
    number = MAX_PARAM;
  }
  byte checkDigit = 0;

  // we first add epoch
  checkDigit ^= toHex(output, (long)now());
  for (int i = 0; i < number; i++) {
    int value = getParameter(i);
    checkDigit ^= toHex(output, value);
  }
  checkDigit ^= toHex(output, (int)getQualifier());
  toHex(output, checkDigit);
  output->println("");
}

/* The qualifier represents the card ID and is stored just after the last parameter */
uint16_t getQualifier() {
  return eeprom_read_word((uint16_t*)(EE_QUALIFIER));
}

void setQualifier(uint16_t value) {
  eeprom_write_word((uint16_t*)(EE_QUALIFIER), value);
}

void resetParameters() {
  for (byte i = 0; i < 10; i++) {
    setAndSaveParameter(i, 0);
  }

  setAndSaveParameter(PARAM_BEFORE_DELAY, 2);
  setAndSaveParameter(PARAM_FIRST_DELAY, 10);
  setAndSaveParameter(PARAM_INTER_DELAY, 20);
  setAndSaveParameter(PARAM_NUMPER_EXP, maxNbRows);
  setAndSaveParameter(PARAM_NEXT_EXP, -1);
  setAndSaveParameter(PARAM_WAIT, 0);
  setAndSaveParameter(PARAM_COLOR, 1);
  setAndSaveParameter(PARAM_ERROR, 0);
  setAndSaveParameter(PARAM_NUMBER_ACQ, 10);
  setAndSaveParameter(PARAM_INVERT_ROTARY, 0);
  setAndSaveParameter(PARAM_ACTIVE_LEDS, pow(2, sizeof(ALL_LEDS)) - 1);

  setQualifier(32767);
}


