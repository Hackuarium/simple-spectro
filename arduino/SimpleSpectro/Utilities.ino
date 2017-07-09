

void clearArray(unsigned int intArray[]) {
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    intArray[i] = 0;
  }
}

int getMax(int unsigned intArray[], byte smoothing) {
  byte shift = floor(smoothing / 2);
  int currentPoint = 0;
  long currentMax = 0;
  for (int i = shift; i < (ARRAY_SIZE - shift - 1); i++) {
    long currentValue = 0;
    for (int j = i - shift; j <= i + shift; j++) {
      currentValue += intArray[j];
    }
    if (currentValue > currentMax) {
      currentMax = currentValue;
      currentPoint = i;
    }
  }
  return currentPoint;
}

Print* getOutput() {
  return &Serial;
}


