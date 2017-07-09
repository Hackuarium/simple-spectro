#define THR_SERIAL         1

#ifdef THR_SERIAL

#define SERIAL_BUFFER_LENGTH 32
#define SERIAL_MAX_PARAM_VALUE_LENGTH  32
char serialBuffer[SERIAL_BUFFER_LENGTH];
byte serialBufferPosition = 0;

NIL_WORKING_AREA(waThreadSerial, 1700); // minimum 128
NIL_THREAD(ThreadSerial, arg) {

  Serial.begin(115200);
  while (true) {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == 13 || inChar == 10) {
        // this is a carriage return;
        if (serialBufferPosition > 0) {
          printResult(serialBuffer, &Serial);
        }
        serialBufferPosition = 0;
        serialBuffer[0] = '\0';
      }
      else {
        if (serialBufferPosition < SERIAL_BUFFER_LENGTH) {
          serialBuffer[serialBufferPosition] = inChar;
          serialBufferPosition++;
          if (serialBufferPosition < SERIAL_BUFFER_LENGTH) {
            serialBuffer[serialBufferPosition] = '\0';
          }
        }
      }
    }
    nilThdSleepMilliseconds(1);
  }
}

#endif



/* SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.

  This method will mainly set/read the parameters:
  Uppercase + number + CR ((-) and 1 to 5 digit) store a parameter (0 to 25 depending the letter)
  example: A100, A-1
  -> Many parameters may be set at once
  example: C10,20,30,40,50
  Uppercase + CR read the parameter
  example: A
  -> Many parameters may be read at once
  example: A,B,C,D
  s : read all the parameters
  h : help
  l : show the log file
*/

void printResult(char* data, Print* output) {
  boolean theEnd = false;
  byte paramCurrent = 0; // Which parameter are we defining
  char paramValue[SERIAL_MAX_PARAM_VALUE_LENGTH];
  paramValue[0] = '\0';
  byte paramValuePosition = 0;
  byte i = 0;
  boolean inValue = false;

  while (!theEnd) {
    byte inChar = data[i];
    i++;
    if (i == SERIAL_BUFFER_LENGTH) theEnd = true;
    if (inChar == '\0') {
      theEnd = true;
    }
    else if ((inChar > 47 && inChar < 58) || inChar == '-' || inValue) { // a number (could be negative)
      if (paramValuePosition < SERIAL_MAX_PARAM_VALUE_LENGTH) {
        paramValue[paramValuePosition] = inChar;
        paramValuePosition++;
        if (paramValuePosition < SERIAL_MAX_PARAM_VALUE_LENGTH) {
          paramValue[paramValuePosition] = '\0';
        }
      }
    }
    else if (inChar > 64 && inChar < 92) { // an UPPERCASE character so we define the field
      // we extend however the code to allow 2 letters fields !!!
      if (paramCurrent > 0) {
        paramCurrent *= 26;
      }
      paramCurrent += inChar - 64;
      if (paramCurrent > MAX_PARAM) {
        paramCurrent = 0;
      }
    }
    if (inChar == ',' || theEnd) { // store value and increment
      if (paramCurrent > 0) {
        if (paramValuePosition > 0) {
          setAndSaveParameter(paramCurrent - 1, atoi(paramValue));
          output->println(parameters[paramCurrent - 1]);
        }
        else {
          output->println(parameters[paramCurrent - 1]);
        }
        if (paramCurrent <= MAX_PARAM) {
          paramCurrent++;
          paramValuePosition = 0;
          paramValue[0] = '\0';
        }
      }
    }
    if (data[0] > 96 && data[0] < 123 && (i > 1 || data[1] < 97 || data[1] > 122)) { // we may have one or 2 lowercasee
      inValue = true;
    }
  }

  // we will process the commands, it means it starts with lowercase
  switch (data[0]) {
    case 'h':
      printHelp(output);
      break;
    case 's':
      printParameters(output);
      break;
    case 'u':
      processUtilitiesCommand(data[1], paramValue, output);
      break;
    default:
      processSpecificCommand(data, paramValue, output);
  }
  output->println("");
}

void printHelp(Print* output) {
  output->println(F("(h)elp"));
  output->println(F("(s)ettings"));
  output->println(F("(u)tilities"));


  printSpecificHelp(output);
}




void noThread(Print* output) {
  output->println(F("No Thread"));
}


/* Fucntions to convert a number to hexadeciaml */

const char hex[] = "0123456789ABCDEF";

uint8_t toHex(Print* output, byte value) {
  output->print(hex[value >> 4 & 15]);
  output->print(hex[value >> 0 & 15]);
  return value;
}

uint8_t toHex(Print* output, int value) {
  byte checkDigit = toHex(output, (byte)(value >> 8 & 255));
  checkDigit ^= toHex(output, (byte)(value >> 0 & 255));
  return checkDigit;
}

uint8_t toHex(Print* output, long value) {
  byte checkDigit = toHex(output, (int)(value >> 16 & 65535));
  checkDigit ^= toHex(output, (int)(value >> 0 & 65535));
  return checkDigit;
}




