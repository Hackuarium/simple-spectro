#define THR_ACTION1 1

#ifdef THR_ACTION1

NIL_WORKING_AREA(waThreadAction1, 128);
NIL_THREAD(ThreadAction1, arg) {

  byte action1Step=0;
  while (TRUE) {
    boolean fixed=true;
    for (byte i=0; i<4; i++) {
      if (getParameter(TEST[i])<0 || getParameter(TEST[i])>255) {
        fixed=false;
      }
    }
    if (fixed) {
      for (byte i=0; i<4; i++) {
        analogWrite(LEDS[i], getParameter(TEST[i]));
      }
    } 
    else {
      analogWrite(LEDS[action1Step%4], 0);
      action1Step++;
      analogWrite(LEDS[action1Step%4], 255);
      nilThdSleepMilliseconds(250);
    }
  }
}

#endif










