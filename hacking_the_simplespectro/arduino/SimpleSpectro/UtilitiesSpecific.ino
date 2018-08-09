#include "Mode.h"

void printColor(Print* output, byte colorPin) {
  switch (colorPin) {
    case RED:
      output->print(F(TEXT_RED));
      break;
    case GREEN:
      output->print(F(TEXT_GREEN));
      break;

    #if MODE == 'P'                                 ///PLONGEUR
        case LED1:
          output->print(F(TEXT_LED1));
          break;
        case LED2:
          output->print(F(TEXT_LED2));
          break;
    #elif MODE == 'C'
        case BLUE:
          output->print(F(TEXT_BLUE));
          break;
        case UV1:
          output->print(F(TEXT_UV1));
          break;
    #endif
   
    case TEMPERATURE:
      output->print(F("Temperature"));
      break;
    case BATTERY_LEVEL:
      output->print(F("Battery level"));
      break;
  }
}

void printColorOne(Print* output, byte colorPin) {
  switch (colorPin) {
    case RED:
      output->print("R");
      break;
    case GREEN:
      output->print("G");
      break;
      
    #if MODE == 'P'                         ///PLONGEUR
        case LED1:
          output->print("L1");
          break;
        case LED2:
          output->print("L2");
          break;
    #elif MODE == 'C'
        case BLUE:
          output->print("B");
          break;
        case UV1:
          output->print("UV");
          break;
    #endif

    case TEMPERATURE:
      output->print("T");
      break;
    case BATTERY_LEVEL:
      output->print("BAT");
      break;
  }
}
