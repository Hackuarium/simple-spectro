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


#define PARAM_R           0
#define PARAM_G           1
#define PARAM_B           2
#define PARAM_UV1         3
#define PARAM_UV2         4


#define PARAM_BEFORE_DELAY  10  // delay before taking blank
#define PARAM_FIRST_DELAY   11
#define PARAM_INTER_DELAY   12
#define PARAM_NUMPER_EXP    13
#define PARAM_NEXT_EXP      14 // next experiment, 0 blank and then for kinetic
// last experiment: MAX_EXPERIMENTS
#define PARAM_WAIT          15 // current time to wait
#define PARAM_COLOR         23 // color used to display the results

#define PARAM_STATUS        24
#define PARAM_MENU          25 // current menu

#define STATUS_ONE_SPECTRUM 1
#define STATUS_KINETIC      2



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
  setAndSaveParameter(PARAM_R, 0);
  setAndSaveParameter(PARAM_G, 0);
  setAndSaveParameter(PARAM_B, 0);
  setAndSaveParameter(PARAM_UV1, 0);
  setAndSaveParameter(PARAM_UV2, 0);

  setAndSaveParameter(PARAM_BEFORE_DELAY, 2);
  setAndSaveParameter(PARAM_FIRST_DELAY, 10);
  setAndSaveParameter(PARAM_INTER_DELAY, 20);
  setAndSaveParameter(PARAM_NUMPER_EXP, MAX_EXPERIMENTS);
  setAndSaveParameter(PARAM_NEXT_EXP, -1);
  setAndSaveParameter(PARAM_WAIT, 0);

  setQualifier(21313);
}


