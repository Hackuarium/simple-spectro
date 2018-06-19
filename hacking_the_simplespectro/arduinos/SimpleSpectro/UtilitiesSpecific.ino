void printColor(Print* output, byte colorPin) {
  switch (colorPin) {
    case RED:
      output->print(F(TEXT_RED));
      break;
    case GREEN:
      output->print(F(TEXT_GREEN));
      break;
    case BLUE:
      output->print(F(TEXT_BLUE));
      break;
    case UV1:
      output->print(F(TEXT_UV1));
      break;
    case TEMPERATURE:
      output->print(F("Temperature"));
      break;
    case BATTERY_LEVEL:
      output->print(F("Battery level"));
      break;
  }
}

void printColorOne(Print* output, byte colorPin) {
  switch (colorPin) {
    case RED:
      output->print("R");
      break;
    case GREEN:
      output->print("G");
      break;
    case BLUE:
      output->print("B");
      break;
    case UV1:
      output->print("UV");
      break;
    case TEMPERATURE:
      output->print("T");
      break;
    case BATTERY_LEVEL:
      output->print("BAT");
      break;
  }
}