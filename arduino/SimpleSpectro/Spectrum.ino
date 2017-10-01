#include <FreqCount.h>

void testRGB() {
  for (byte i = 0; i < nbLeds; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  while (true) {
    for (byte i = 0; i < nbLeds; i++) {
      digitalWrite(LEDS[i], HIGH);
      nilThdSleepMilliseconds(500);
      digitalWrite(LEDS[i], LOW);
      nilThdSleepMilliseconds(500);
      if (getParameter(PARAM_STATUS) != STATUS_TEST_LEDS) {
        return;
      }
    }
  }
}

void setActiveLeds() {
  int active = getParameter(PARAM_ACTIVE_LEDS);
  nbLeds = 0;
  for (byte i = 0; i < sizeof(ALL_LEDS); i++) {
    if (active & (1 << i)) {
      LEDS[nbLeds] = ALL_LEDS[i];
      nbLeds++;
    }
  }
  dataRowSize = nbLeds + 1;
  maxNbRows = DATA_SIZE / dataRowSize;
}

NIL_WORKING_AREA(waThreadAcquisition, 128);
NIL_THREAD(ThreadAcquisition, arg) {
  clearData();
  setParameter(PARAM_NEXT_EXP, -1);
  while (true) {
    if (getParameter(PARAM_NEXT_EXP) == 0) {
      setActiveLeds();
      clearData();
      switch (getParameter(PARAM_STATUS)) {
        case STATUS_ONE_SPECTRUM:
          runExperiment();
          break;
        case STATUS_KINETIC:
          runExperiment(getParameter(PARAM_NUMPER_EXP));
          break;
      }
    }
    if (getParameter(PARAM_STATUS) == STATUS_TEST_LEDS) {
      testRGB();
    }
    nilThdSleepMilliseconds(100);
  }
}

void waitExperiment() {
  long wait = 0;
  if (getParameter(PARAM_NEXT_EXP) == 0) {
    wait = getParameter(PARAM_BEFORE_DELAY);
    setParameter(PARAM_MENU, 30);
  } else if (getParameter(PARAM_NEXT_EXP) == 1) {
    wait = getParameter(PARAM_FIRST_DELAY);
    setParameter(PARAM_MENU, 31);
  } else if (getParameter(PARAM_NEXT_EXP) > 1) {
    wait = getParameter(PARAM_INTER_DELAY);
    setParameter(PARAM_MENU, 31);
  }

  long timeEnd = millis() + wait * 1000;
  while (millis() < timeEnd && getParameter(PARAM_NEXT_EXP) >= 0) {
    setParameter(PARAM_WAIT, (timeEnd - millis()) / 1000);
    nilThdSleepMilliseconds(1000);
  }
}

void runExperiment() {
  runExperiment(1);
}

void runExperiment(byte nbExperiments) {
  for (byte i = 0; i <= nbExperiments; i++) {
    setParameter(PARAM_NEXT_EXP, i);
    waitExperiment();
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    acquire();
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    if (i > 0) calculateResult(i);
  }
  setParameter(PARAM_MENU, 20);
  setParameter(PARAM_STATUS, 0);
  setParameter(PARAM_NEXT_EXP, -1);

}

void calculateResult(byte experimentNumber) {
  // we calculate the difference with blank
  for (byte i = 0; i < nbLeds; i++) {
    if (data[experimentNumber * 6 + i + 1] == LONG_MAX_VALUE) {
      setParameter(i, INT_MAX_VALUE); // current experiment
    } else {
      setParameter(i, data[experimentNumber * 6 + i + 1] / 16); // current experiment
    }
    if (data[i + 1] == LONG_MAX_VALUE) {
      setParameter(i + nbLeds, INT_MAX_VALUE); // blank
    } else {
      setParameter(i + nbLeds, data[i + 1] / 16); // blank
    }
  }
}

void acquire() {

  setParameter(PARAM_MENU, 32);
  byte target = getParameter(PARAM_NEXT_EXP) * dataRowSize;
  if (target < 0) return;
  data[target] = millis();
  for (byte i = 0; i < nbLeds; i++) {
    
    pinMode(LEDS[i], OUTPUT);
    data[target + i + 1] = 0;
   
    for (byte j = 0; j <  getParameter(PARAM_NUMBER_ACQ); j++) {
      digitalWrite(LEDS[i], HIGH);
      FreqCount.begin(100);
      nilThdSleepMilliseconds(105);
      long currentCount = FreqCount.read();
      data[target + i + 1] += currentCount;
      digitalWrite(LEDS[i], LOW);
      if (currentCount > 50000) {
        // there is an error, the frequency was too high for the detector
        // this means we should either work in a darker environnement (at least close the box)
        // or that the LED is too strong !
        data[target + i + 1] = LONG_MAX_VALUE;
        break;
      }
      FreqCount.begin(100);
      nilThdSleepMilliseconds(105);
      currentCount = FreqCount.read();
      if (currentCount > 10000) {
        // there is an error, the frequency was too high without led on
        // this means we should work in a darker environnement (at least close the box)
        data[target + i + 1] = LONG_MAX_VALUE;
        break;
      }
      data[target + i + 1] -= currentCount;
      if (getParameter(PARAM_NEXT_EXP) < 0) return;
    }
  }
}

void printData(Print* output) {
  for (byte i = 0; i < maxNbRows; i++) {
    for (byte j = 0; j < dataRowSize; j++) {
      if (data[i * dataRowSize + j] == LONG_MAX_VALUE) {
        output->print("OVER");
      } else {
        output->print(data[i * dataRowSize + j]);
      }
      output->print(" ");
    }
    output->println("");
  }
}

void clearData() {
  for (byte i = 0; i < DATA_SIZE; i++) {
    data[i] = 0;
  }
}

