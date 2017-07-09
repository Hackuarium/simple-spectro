
void writeLog(int a, int b) {

}

#ifdef LOGGER

/*
We have the way to log some event.
 We will keep in memory the last 32 events
 The events are stored in EEPROM to be sure ...
 * a timestamp in epoch (long)
 * an eventID 
 * a value
 */

/* EEPROM IS LIMITED TO 100000 WRITES !!!! LOG EVENT WRITE TO EEPROM SO TAKE CARE !!!!!!!
 If the MAX_NUMBER_EVENTS change you need to change the pointer in the EEPROM
 */


#define MAX_NUMBER_EVENTS 16

#define LOGGER_NOEVENT 0
#define LOGGER_I2C_CAPACITY_EXCEEDED 1



#define FLOAT_MIN_VALUE  -3.4028235E+38

// Variable are defined in the main class !!!!




byte eventTypes[MAX_NUMBER_EVENTS];
unsigned long eventTimestamps[MAX_NUMBER_EVENTS];
float eventParameters[MAX_NUMBER_EVENTS];



void logger(byte eventType) {
  logger(eventType, FLOAT_MIN_VALUE);
}

void logger(byte eventType, float parameter) {

  // in order to space the EEPROM we only log event if
  // the eventType is different
  // or the elapse time since the last event is > 900s
  // Boot event are still taken into account
  // We however always log the Boot event
  if ((eventType==eventTypes[MAX_NUMBER_EVENTS]) && (eventType>1)) {
    if ((eventTimestamps[MAX_NUMBER_EVENTS]-now())<900) {
      return;
    }
  }

  for (int i=0; i<(MAX_NUMBER_EVENTS-1); i++) {
    eventTypes[i]=eventTypes[i+1];
    eventTimestamps[i]=eventTimestamps[i+1];
    eventParameters[i]=eventParameters[i+1];
  }
  eventTypes[MAX_NUMBER_EVENTS-1]=eventType;
  eventTimestamps[MAX_NUMBER_EVENTS-1]=now();
  eventParameters[MAX_NUMBER_EVENTS-1]=parameter;

  EXROM.write(EE_TARGET_EVENT_TYPES, eventTypes, MAX_NUMBER_EVENTS);
  EXROM.write(EE_TARGET_EVENT_TIMES, eventTimestamps, MAX_NUMBER_EVENTS*4);
  EXROM.write(EE_TARGET_EVENT_PARAMS, eventParameters, MAX_NUMBER_EVENTS*4);
}


void setupLogger() {
  // We should load from EEPROM all the events

  EXROM.read(EE_TARGET_EVENT_TYPES, eventTypes, MAX_NUMBER_EVENTS);
  EXROM.read(EE_TARGET_EVENT_TIMES, eventTimestamps, MAX_NUMBER_EVENTS*4);
  EXROM.read(EE_TARGET_EVENT_PARAMS, eventParameters, MAX_NUMBER_EVENTS*4);
}

void getLoggerLog(Print* output) {
  for (int i=0; i<MAX_NUMBER_EVENTS; i++) {
    output->print(i);
    output->print(" ");
    epochToString(eventTimestamps[i],output);


    if (eventParameters[i]!=FLOAT_MIN_VALUE) {
      output->print(": ");
      output->print(eventParameters[i]);
    }
    output->println("");

  }
}

void epochToString(time_t time, Print* output) {
  // digital clock display of the time
  output->print(year(time)); 
  output->print("-");
  print2Digits(output,month(time));
  output->print("-");
  print2Digits(output,day(time));
  output->print(" ");
  print2Digits(output,hour(time));
  output->print(":");
  print2Digits(output,minute(time));
  output->print(":");
  print2Digits(output,second(time));
  output->print(" ");
}

void print2Digits(Print* output, int number) {
  // utility function for digital clock display: prints preceding colon and leading 0
  if(number < 10) output->print('0');
  output->print(number);
}

#endif


