#include <FreqCount.h>

void testRGB() {
  for (byte i = 0; i < nbLeds; i++) {
    pinMode(CURRENT_PARAMETERS[i], OUTPUT);
  }
  while (true) {
    for (byte i = 0; i < nbLeds; i++) {
      digitalWrite(CURRENT_PARAMETERS[i], HIGH);
      nilThdSleepMilliseconds(500);
      digitalWrite(CURRENT_PARAMETERS[i], LOW);
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
  nbParameters = 0;
  for (byte i = 0; i < sizeof(ALL_PARAMETERS); i++) {
    if (active & (1 << i)) {
      CURRENT_PARAMETERS[nbParameters] = ALL_PARAMETERS[i];
      if (ALL_PARAMETERS[i] < 128) {
        nbLeds++;
      }
      nbParameters++;
    }
  }
  dataRowSize = nbParameters + 1;
  maxNbRows = DATA_SIZE / dataRowSize;
}

NIL_WORKING_AREA(waThreadAcquisition, 64);
NIL_THREAD(ThreadAcquisition, arg) {
  setParameter(PARAM_NEXT_EXP, -1);
  while (true) {
    if (getParameter(PARAM_NEXT_EXP) == 0) {
      setActiveLeds();
      byte numberExperiments = min(maxNbRows, getParameter(PARAM_NUMPER_EXP));
      switch (getParameter(PARAM_STATUS)) {
        case STATUS_ONE_SPECTRUM:
          runExperiment();
          break;
        case STATUS_KINETIC:
          runExperiment(numberExperiments);
          break;
        case STATUS_SEQUENCE:
          runSequence(numberExperiments);
          break;
      }
    }
    if (getParameter(PARAM_STATUS) == STATUS_TEST_LEDS) {
      testRGB();
    }
    nilThdSleepMilliseconds(100);
  }
}

void setAcquisitionMenu() {
   if (getParameter(PARAM_NEXT_EXP) == 0) {
    setParameter(PARAM_MENU, 30);
  } else {
    setParameter(PARAM_MENU, 31);
  }
}

void waitExperiment() {
  long wait = 0;
  if (getParameter(PARAM_NEXT_EXP) == 0) {
    wait = getParameter(PARAM_BEFORE_DELAY);
  } else if (getParameter(PARAM_NEXT_EXP) == 1) {
    wait = getParameter(PARAM_FIRST_DELAY);
  } else if (getParameter(PARAM_NEXT_EXP) > 1) {
    wait = getParameter(PARAM_INTER_DELAY);
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
    setAcquisitionMenu();
    waitExperiment();
    if (i == 0) {
      clearData();
    }
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    acquire();
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    if (i > 0) calculateResult(i);
  }
  setParameter(PARAM_MENU, 20);// status menu
  setParameter(PARAM_STATUS, 0);
  setParameter(PARAM_NEXT_EXP, -1);
}

void runSequence(byte nbExperiments) { // TODO update this code
  for (byte i = 0; i <= nbExperiments; i++) {
    setParameter(PARAM_NEXT_EXP, i);
    setAcquisitionMenu();
    setParameter(PARAM_WAIT, INT_MAX_VALUE);
    // Need to wait for a validation
    while (getParameter(PARAM_WAIT)!=0 && getParameter(PARAM_NEXT_EXP) >= 0) {
      nilThdSleepMilliseconds(100);
    }
    if (i == 0) {
      clearData();
    }
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    acquire();
    if (getParameter(PARAM_NEXT_EXP) < 0) return;
    if (i > 0) calculateResult(i);
  }
  setParameter(PARAM_MENU, 20); // status menu
  setParameter(PARAM_STATUS, 0);
  setParameter(PARAM_NEXT_EXP, -1);
}

void calculateResult(byte experimentNumber) {
  // we calculate the difference with blank
  for (byte i = 0; i < nbLeds; i++) {
    if (getDataLong(experimentNumber * dataRowSize + i + 1) == LONG_MAX_VALUE) {
      setParameter(i, INT_MAX_VALUE); // current experiment
    } else {
      setParameter(i, getDataLong(experimentNumber * dataRowSize + i + 1) / 16); // current experiment
    }
    if (getDataLong(i + 1) == LONG_MAX_VALUE) {
      setParameter(i + 5, INT_MAX_VALUE); // blank saturation
    } else {
      setParameter(i + 5, getDataLong(i + 1) / 16); // blank value
    }
  }
}

void acquire() {
  setParameter(PARAM_MENU, 32);
  byte target = getParameter(PARAM_NEXT_EXP) * dataRowSize;
  if (target < 0) return;
  setDataLong(target, millis());
  for (byte i = 0; i < nbParameters; i++) {
    long newValue = 0;
    if (CURRENT_PARAMETERS[i] < 128) {
      pinMode(CURRENT_PARAMETERS[i], OUTPUT);
      for (byte j = 0; j <  getParameter(PARAM_NUMBER_ACQ); j++) {
        digitalWrite(CURRENT_PARAMETERS[i], HIGH);
        FreqCount.begin(100);
        nilThdSleepMilliseconds(105);
        long currentCount = FreqCount.read();
        newValue += currentCount;
        digitalWrite(CURRENT_PARAMETERS[i], LOW);
        if (currentCount > 50000) {
          // there is an error, the frequency was too high for the detector
          // this means we should either work in a darker environnement (at least close the box)
          // or that the LED is too strong !
          setDataLong(target + i + 1, LONG_MAX_VALUE);
          break;
        }
        FreqCount.begin(100);
        nilThdSleepMilliseconds(105);
        currentCount = FreqCount.read();
        if (currentCount > 10000) {
          // there is an error, the frequency was too high without led on
          // this means we should work in a darker environnement (at least close the box)
          setDataLong(target + i + 1, LONG_MAX_VALUE);
          break;
        }
        newValue -= currentCount;
        if (getParameter(PARAM_NEXT_EXP) < 0) return;
      }
    } else {
      switch (CURRENT_PARAMETERS[i]) {
        case BATTERY_LEVEL:
          newValue = getParameter(PARAM_BATTERY);
          break;
        case TEMPERATURE:
          newValue = getParameter(PARAM_TEMPERATURE);
          break;
      }
    }
    setDataLong(target + i + 1, newValue);
  }
}

void printData(Print* output) {
  output->print("E ");
  for (byte i = 0; i < nbParameters; i++) {
    printColorOne(output, CURRENT_PARAMETERS[i]);
    output->print(" ");
  }
  output->println("");
  for (byte i = 0; i < maxNbRows; i++) {
    for (byte j = 0; j < dataRowSize; j++) {
      if (getDataLong(i * dataRowSize + j) == LONG_MAX_VALUE) {
        output->print("OVER");
      } else {
        output->print(getDataLong(i * dataRowSize + j));
      }
      output->print(" ");
    }
    output->println("");
  }
}

void clearData() {
  for (byte i = 0; i < DATA_SIZE; i++) {
    if (getDataLong(i) != 0) {
      setDataLong(i, 0);
    }
  }
}
