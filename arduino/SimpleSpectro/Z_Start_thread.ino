NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  nilThdSleepMilliseconds(1000);
  wdt_enable(WDTO_8S);  //activate the watchdog
  while (TRUE) {
    wdt_reset();//resed avoid the automatic reboot
    nilThdSleepMilliseconds(500);
  }
}

NIL_THREADS_TABLE_BEGIN()
// the count should be exact, Acquisition has the higher priority ...

NIL_THREADS_TABLE_ENTRY(NULL, ThreadAcquisition, NULL, waThreadAcquisition, sizeof(waThreadAcquisition))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadLcd, NULL, waThreadLcd, sizeof(waThreadLcd))


#ifdef TEMPERATURE_ADDRESS
NIL_THREADS_TABLE_ENTRY(NULL, ThreadTemperature, NULL, waThreadTemperature, sizeof(waThreadTemperature))
#endif

#ifdef BATTERY
NIL_THREADS_TABLE_ENTRY(NULL, ThreadBattery, NULL, waThreadBattery, sizeof(waThreadBattery))
#endif

NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))


NIL_THREADS_TABLE_END()

