#include <FreqCount.h>

void testRGB() {
  for (byte i = 0; i < sizeof(LEDS); i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  for (byte j = 0; j < 5; j++) {
    for (byte i = 0; i < sizeof(LEDS); i++) {
      digitalWrite(LEDS[i], HIGH);
      nilThdSleepMilliseconds(500);
      digitalWrite(LEDS[i], LOW);
    }
  }
}



NIL_WORKING_AREA(waThreadAcquisition, 128);
NIL_THREAD(ThreadAcquisition, arg) {
  setParameter(PARAM_NEXT_EXP, -1);
  while (true) {
    if (getParameter(PARAM_NEXT_EXP) == 0) {
      if (getParameter(PARAM_STATUS) == STATUS_ONE_SPECTRUM) {
        runExperiment();
      } else if (getParameter(PARAM_STATUS) == STATUS_KINETIC) {
        runExperiment(getParameter(PARAM_NUMPER_EXP));
      }

    }
    nilThdSleepMilliseconds(100);
  }
}

void waitExperiment() {
  long wait = 0;
  if (getParameter(PARAM_NEXT_EXP) == 0) {
    wait = getParameter(PARAM_BEFORE_DELAY);
    currentMenu = 30;
  } else if (getParameter(PARAM_NEXT_EXP) > 1) {
    wait = getParameter(PARAM_INTER_DELAY);
    currentMenu = 31;
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
    if (getParameter(PARAM_NEXT_EXP)<0) return;
    acquire();
    if (getParameter(PARAM_NEXT_EXP)<0) return;
    if (i > 0) calculateResult(i);
  }
  currentMenu = 20;
  setParameter(PARAM_STATUS, 0);
  setParameter(PARAM_NEXT_EXP, -1);

}

void calculateResult(byte experimentNumber) {
  // we calculate the difference with blank
  for (byte i = 0; i < sizeof(LEDS); i++) {
    setParameter(i, (data[experimentNumber * 6 + i + 1] - data[i + 1]) / 16);
  }
}

void acquire() {
  currentMenu = 32;
  byte target = getParameter(PARAM_NEXT_EXP) * 6;
  if (target < 0) return;
  data[target] = millis();
  for (byte i = 0; i < sizeof(LEDS); i++) {
    pinMode(LEDS[i], OUTPUT);
    data[target + i + 1] = 0;
    for (byte j = 0; j < 10; j++) {
      digitalWrite(LEDS[i], HIGH);
      FreqCount.begin(100);
      nilThdSleepMilliseconds(105);
      data[target + i + 1] += FreqCount.read();
      digitalWrite(LEDS[i], LOW);
      FreqCount.begin(100);
      nilThdSleepMilliseconds(105);
      data[target + i + 1] -= FreqCount.read();
      if (getParameter(PARAM_NEXT_EXP)<0) return;
    }
  }
}



void printData(Print* output) {
  for (byte i = 0; i < MAX_EXPERIMENTS; i++) {
    for (byte j = 0; j <= sizeof(LEDS); j++) {
      output->print(data[i * (sizeof(LEDS) + 1) + j]);
      output->print(" ");
    }
    output->println("");
  }
}






