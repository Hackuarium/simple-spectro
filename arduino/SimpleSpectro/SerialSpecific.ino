void processSpecificCommand(char* data, char* paramValue, Print* output) {

  switch (data[0]) {
    case 'd':
      printData(output);
      break;
    case 'k':
      setParameter(PARAM_STATUS, STATUS_KINETIC);
      setParameter(PARAM_NEXT_EXP, 0);
      break;
    case 'r':
      setParameter(PARAM_STATUS, STATUS_ONE_SPECTRUM);
      setParameter(PARAM_NEXT_EXP, 0);
      break;
    case 't':
    setParameter(PARAM_STATUS, STATUS_TEST_LEDS);;
      break;
  }
}

void printSpecificHelp(Print * output) {
  output->println(F("(d)ata"));
  output->println(F("(k)inetic"));
  output->println(F("(r)un experiment"));
  output->println(F("(t)est"));
}

