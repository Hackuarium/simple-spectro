void processSpecificCommand(char* data, char* paramValue, Print* output) {
  
  switch (data[0]) {
    case 'k':
      runKinetic();
      break;
    
    case 'r':
      runExperiment();
      break;

    case 't':
      testRGB();
      break;
  }
}

void printSpecificHelp(Print * output) {
  output->println(F("(k)inetic"));
  output->println(F("(r)un experiment"));
  output->println(F("(t)est"));
}

