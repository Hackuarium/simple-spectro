/*
  Events that are not stored in the EEPROM mainly for DEBUG purpose
 */


#define DEBUG_MAX_NUMBER_EVENTS 8


#define INT_MIN_VALUE  -32768

#define DEBUG_MEMORY                  2
#define DEBUG_ONEWIRE_NODEVICE        3
#define DEBUG_WIRE_ADDED_DEVICE       4
#define DEBUG_WIRE_REMOVED_DEVICE     5

byte debugTypes[DEBUG_MAX_NUMBER_EVENTS];
unsigned int debugTime[DEBUG_MAX_NUMBER_EVENTS];
int debugParameters[DEBUG_MAX_NUMBER_EVENTS];

void debugger(byte eventType) {
  debugger(eventType, INT_MIN_VALUE);
}

void debugger(byte eventType, int parameter) {
  for (int i=0; i<(DEBUG_MAX_NUMBER_EVENTS-1); i++) {
    debugTypes[i]=debugTypes[i+1];
    debugTime[i]=debugTime[i+1];
    debugParameters[i]=debugParameters[i+1];
  }
  debugTypes[DEBUG_MAX_NUMBER_EVENTS-1]=eventType;
  debugTime[DEBUG_MAX_NUMBER_EVENTS-1]=millis()/1000;
  debugParameters[DEBUG_MAX_NUMBER_EVENTS-1]=parameter;
}



void setupDebugger() {
  for (int i=0; i<(DEBUG_MAX_NUMBER_EVENTS); i++) {
    debugTypes[i]=0;
    debugTime[i]=0;
    debugParameters[i]=INT_MIN_VALUE;
  }
}

void getDebuggerLog(Print* output) {
  for (int i=0; i<DEBUG_MAX_NUMBER_EVENTS; i++) {
    if (debugTypes[i]>0) {
      output->print(i);
      output->print(" ");
      output->print(debugTime[i]);
      output->print("s - type: ");
      output->print(debugTypes[i]);
      if (debugParameters[i]!=INT_MIN_VALUE) {
        output->print(": ");
        output->print(debugParameters[i]);
      }
    }
  }
}


