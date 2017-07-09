
unsigned int acquireOne(unsigned int intArray[], boolean append) {
  unsigned int currentMax=0;
  delay(getParameter(PARAM_INTEGRATION_TIME));
  resetClockPulse();
  for(int i = 0; i < ARRAY_SIZE/2; i++)
  {
    unsigned int currentValue=analogRead(AO_PIN1);
    if (currentValue>currentMax) currentMax=currentValue;
    if (append) {
      intArray[i] += currentValue;
    }
    currentValue=analogRead(AO_PIN2);
    if (currentValue>currentMax) currentMax=currentValue;
    if (append) {
      intArray[i+ARRAY_SIZE/2] += currentValue;
    }    
    clockPulse();
  }
  return currentMax;
}

int autoIntensity(int channel) {
  int intensity=256;
  int currentMax;
  do {
    analogWrite(channel, intensity-1);
    acquireOne(NULL, false);
    currentMax=acquireOne(NULL, false);
    if (currentMax>900) {
      intensity/=2;
    }
  } 
  while (currentMax>900 && intensity>15);
  return intensity;
}


void acquire(unsigned int intArray[]) {
  acquire(intArray, getParameter(PARAM_NUMBER_SCAN));
}

void acquire(unsigned int intArray[], byte nbRepeat) {
  clearArray(intArray);
  acquireOne(intArray, false);   // an empty cycle

  for (int counter=0; counter<nbRepeat; counter++) {
    acquireOne(intArray, true);
  }
}

int diffArray(unsigned int signalArray[], unsigned int backgroundArray[]) {
  int maxBackground=0;
  for (int i=0; i<ARRAY_SIZE; i++) {
    if (backgroundArray[i]>maxBackground) {
      maxBackground=backgroundArray[i];
    }
    if (backgroundArray[i]>signalArray[i]) {
      signalArray[i]=0;
    } 
    else {
      signalArray[i]-=backgroundArray[i];
      ;
    }
  }
  return maxBackground;
}

















