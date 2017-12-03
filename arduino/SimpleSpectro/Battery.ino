#ifdef BATTERY

NIL_WORKING_AREA(waThreadBattery, 0);

NIL_THREAD(ThreadBattery, arg) {
  pinMode(BATTERY, INPUT);
  while (true) {
    setParameter(PARAM_BATTERY, analogRead(BATTERY));
    nilThdSleepMilliseconds(1000);
  }
}

#endif

