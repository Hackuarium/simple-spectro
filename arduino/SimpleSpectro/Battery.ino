#ifdef BATTERY

NIL_WORKING_AREA(waThreadBattery, 0);

NIL_THREAD(ThreadBattery, arg) {
  pinMode(BATTERY, INPUT);
  analogReference(INTERNAL); // internal reference is 2.56V
  while (true) {
    setParameter(PARAM_BATTERY, analogRead(BATTERY) * 5 ); // in mv
    nilThdSleepMilliseconds(1000);
  }
}

#endif

