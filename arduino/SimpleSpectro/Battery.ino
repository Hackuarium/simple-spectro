#ifdef BATTERY

NIL_WORKING_AREA(waThreadBattery, 0);

NIL_THREAD(ThreadBattery, arg) {
  pinMode(BATTERY, INPUT);
  analogReference(INTERNAL); // internal reference is 2.56V

#ifdef BATTERY_CHARGING
  pinMode(BATTERY_CHARGING, INPUT);
#endif


  while (true) {
    setParameter(PARAM_BATTERY, analogRead(BATTERY) * 5 ); // in mv
    
#ifdef BATTERY_CHARGING
    setParameter(PARAM_CHARGING, analogRead(BATTERY_CHARGING) );
#endif
    nilThdSleepMilliseconds(1000);
  }
}

#endif

