#include <FreqCount.h>

long data[MAX_EXPERIMENTS * 6]; // epoch R G B UV1 UV2


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

void runKinetic() {


}

unsigned long experimentalResults[sizeof(LEDS)];

void  runExperiment() {
  for (byte i = 0; i < sizeof(LEDS); i++) {
    pinMode(LEDS[i], OUTPUT);
    experimentalResults[i] = 0;
  }
  // we will accumulate the blank
  for (byte i = 0; i < sizeof(LEDS); i++) {
    for (byte j = 0; j < 10; j++) {
      digitalWrite(LEDS[i], HIGH);
      accumulate(i, 1);
      digitalWrite(LEDS[i], LOW);
      accumulate(i, -1);
    }
  }
}

void accumulate(byte target, int factor) {
  FreqCount.begin(100);
  nilThdSleepMilliseconds(105);
  experimentalResults[target] += FreqCount.read() * factor;
}

void waitExperiment() {
  int wait = 0;
  if (getParameter(PARAM_NEXT_EXP) == 0) {
    wait = getParameter(PARAM_BEFORE_DELAY);
    currentMenu = 30;
  } else if (getParameter(PARAM_NEXT_EXP) == 1) {
    wait = getParameter(PARAM_FIRST_DELAY);
    currentMenu = 31;
  } else if (getParameter(PARAM_NEXT_EXP) > 1) {
    wait = getParameter(PARAM_INTER_DELAY);
    currentMenu = 32;
  }
  long timeEnd = millis() + wait * 1000;
  while (timeEnd < now() && getParameter(PARAM_NEXT_EXP) > 0) {
    setParameter(PARAM_WAIT, (timeEnd - millis()) / 1000);
    nilThdSleepMilliseconds(1000);
  }
  currentMenu = 0;
}

void acquireExperiment() {
  if (getParameter(PARAM_NEXT_EXP) == 0) {
    currentMenu = 33;
  } else if (getParameter(PARAM_NEXT_EXP) == 1) {
    currentMenu = 34;
  }
  long timeEnd = millis() + wait * 1000;
  while (timeEnd < now() && getParameter(PARAM_NEXT_EXP) > 0) {
    setParameter(PARAM_WAIT, (timeEnd - millis()) / 1000);
    nilThdSleepMilliseconds(1000);
  }
}

