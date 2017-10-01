NIL_THREADS_TABLE_BEGIN()

  // the count should be exact, Acquisition has the higher priority ...
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAcquisition, NULL, waThreadAcquisition, sizeof(waThreadAcquisition))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadLcd, NULL, waThreadLcd, sizeof(waThreadLcd))

NIL_THREADS_TABLE_END()

