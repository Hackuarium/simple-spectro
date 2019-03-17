void printColor(Print* output, byte parameter) {
  switch (parameter) {
    case 0:
      output->print(F(TEXT_RED));
      break;
    case 1:
      output->print(F(TEXT_GREEN));
      break;
    case 2:
      output->print(F(TEXT_BLUE));
      break;
    case 3:
      output->print(F(TEXT_UV1));
      break;
    case 4:
      output->print(F("Temperature"));
      break;
    case 5:
      output->print(F("Battery level"));
      break;
  }
}

void printColorOne(Print* output, byte parameter) {
  switch (parameter) {
    case 0:
      output->print("R");
      break;
    case 1:
      output->print("G");
      break;
    case 2:
      output->print("B");
      break;
    case 3:
      output->print("UV");
      break;
    case 4:
      output->print("T");
      break;
    case 5:
      output->print("BAT");
      break;
  }
}
