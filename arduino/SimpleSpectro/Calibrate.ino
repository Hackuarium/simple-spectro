// we should make the spectrum for red, green, blue
// and get the maximal

void calibrate() {
  fullOff();
  Print* output=getOutput();
  output->println(F("Calibrating ..."));
  for (byte i=0; i<sizeof(RGB); i++) {
    unsigned int signalArray[ARRAY_SIZE]; // <-- the array where the readout of the photodiodes is stored, as integers
    unsigned int backgroundArray[ARRAY_SIZE];
    byte channel=RGB[i];
    int currentIntensity=autoIntensity(channel);
    acquire(signalArray, REPEAT_CALIBRATE);
    analogWrite(channel, 0);
    acquire(backgroundArray, REPEAT_CALIBRATE);
    diffArray(signalArray, backgroundArray);

    int maxPoint=getMax(signalArray, SMOOTH_CALIBRATE);
    switch (i) {
    case 0:
      setAndSaveParameter(PARAM_RED_POINT, maxPoint);
      output->print(F("Red: "));
      output->println(maxPoint);
      break;
    case 1:
      setAndSaveParameter(PARAM_GREEN_POINT, maxPoint);
      output->print(F("Green: "));
      output->println(maxPoint);
      break;
    case 2:
      setAndSaveParameter(PARAM_BLUE_POINT, maxPoint);
      output->print(F("Blue: "));
      output->println(maxPoint);
      break;
    }
  }
}



