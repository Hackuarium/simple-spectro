void processUtilitiesCommand(char command, char* paramValue, Print* output) {
  switch (command) {
    case 'c':
      if (paramValue[0] != '\0') {
        printCompactParameters(output, atoi(paramValue));
      } else {
        printCompactParameters(output);
      }
      break;
    case 'e':
      if (paramValue[0] != '\0') {
        setTime(atol(paramValue));
        output->println(now());
      } else {
        output->println(now());
      }
      break;
    case 'f':
      printFreeMemory(output);
      break;
    case 'q':
      if (paramValue[0] != '\0') {
        setQualifier(atoi(paramValue));
      }
      {
        uint16_t a = getQualifier();
        output->println(a);
      }
      break;
    case 'r':
      if (paramValue[0] != '\0') {
        if (atol(paramValue) == 1234) {
          resetParameters();
          output->println(F("Reset done"));
        }
      }
      else {
        output->println(F("To reset enter ur1234"));
      }
      break;
    case 'z':
      getStatusEEPROM(output);
      break;
    default:
      printUtilitiesHelp(output);
  }
}

void printUtilitiesHelp(Print* output) {
  output->println(F("(uc) Compact settings"));
  output->println(F("(ue) Epoch"));
  output->println(F("(uf) Free"));
  output->println(F("(uq) Qualifier"));
  output->println(F("(ur) Reset"));
  output->println(F("(uz) eeprom"));
}


static void printFreeMemory(Print* output)
{
  nilPrintUnusedStack(output);
}

