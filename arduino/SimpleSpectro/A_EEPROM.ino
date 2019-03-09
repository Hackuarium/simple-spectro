#include <avr/eeprom.h>

#define EE_START_PARAM           0 // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM            (MAX_PARAM*2-1) // The last parameter is stored at byte 50-51

#define EE_QUALIFIER             (MAX_PARAM*2)

#define EEPROM_MIN_ADDR            0

#define EEPROM_MAX_ADDR          1023


#define DATA_SIZE 240



