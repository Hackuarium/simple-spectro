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

#define MAX_PARAM 26 // If the MAX_PARAM change you need to change the pointer in the EEPROM

#define PARAM_COLOR_1 0
#define PARAM_COLOR_2 1
#define PARAM_COLOR_3 2
#define PARAM_COLOR_4 3
#define PARAM_COLOR_5 4
#define PARAM_BLANK_1 5
#define PARAM_BLANK_2 6
#define PARAM_BLANK_3 7
#define PARAM_BLANK_4 8
#define PARAM_BLANK_5 9

#define PARAM_BEFORE_DELAY 10 // delay before taking blank
#define PARAM_FIRST_DELAY 11
#define PARAM_INTER_DELAY 12
#define PARAM_NUMPER_EXP 13
#define PARAM_NEXT_EXP 14   // next experiment, 0 blank and then for kinetic
#define PARAM_WAIT 15       // current time to wait
#define PARAM_NUMBER_ACQ 16 // number of acquisition of 100ms that will be taken

#define PARAM_INVERT_ROTARY 17 // invert rotary direction
#define PARAM_BATTERY 18       // battery voltage (hundredths of volt)
#define PARAM_TEMPERATURE 19   // temperature (hundredths of degree)
#define PARAM_CHARGING 20      // battery charging

#define PARAM_ACTIVE_LEDS 21
#define PARAM_ERROR 22 // color used to display the results
#define PARAM_COLOR 23 // color used to display the results
#define PARAM_STATUS 24
#define PARAM_MENU 25 // current menu

#define STATUS_ONE_SPECTRUM 1
#define STATUS_KINETIC 2
#define STATUS_SEQUENCE 3
#define STATUS_TEST_LEDS 4

#define INT_MAX_VALUE 32767
#define LONG_MAX_VALUE 2147483647

void resetParameters()
{
  for (byte i = 0; i < 10; i++)
  {
    setAndSaveParameter(i, 0);
  }

  setAndSaveParameter(PARAM_BEFORE_DELAY, 2);
  setAndSaveParameter(PARAM_FIRST_DELAY, 10);
  setAndSaveParameter(PARAM_INTER_DELAY, 20);
  setAndSaveParameter(PARAM_NUMPER_EXP, DATA_SIZE / 4);
  setAndSaveParameter(PARAM_NEXT_EXP, -1);
  setAndSaveParameter(PARAM_WAIT, 0);
  setAndSaveParameter(PARAM_COLOR, 1);
  setAndSaveParameter(PARAM_ERROR, 0);
  setAndSaveParameter(PARAM_NUMBER_ACQ, 10);
  setAndSaveParameter(PARAM_STATUS, 0);
  setAndSaveParameter(PARAM_INVERT_ROTARY, 0);
  // setAndSaveParameter(PARAM_ACTIVE_LEDS, pow(2, sizeof(ALL_PARAMETERS)) - 1);
  setAndSaveParameter(PARAM_ACTIVE_LEDS, 7);
  setQualifier(21569); // TA
}

void checkParameters()
{
  if (getParameter(PARAM_BEFORE_DELAY) < 0)
  {
    resetParameters();
  }
}
