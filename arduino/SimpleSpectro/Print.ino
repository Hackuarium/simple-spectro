
// &JKLMNOPQR
//  jklmnopqr
void printCompressed(Print* output, unsigned int intArray[], byte compression) {
  long previousValue=0;
  for (int i=0; i<ARRAY_SIZE; i+=compression) {
    long value=0;
    for (int j=i; j<(i+compression); j++) {
      value+=(long)intArray[j]; 
    }
    value/=compression;
    if (i%(32*compression) == 0) {
      output->print(value);
    } 
    else {
      // we will store the difference
      long diff=value-previousValue;
      // need to get the first digit with the sign
      compress(output, diff);
    }
    if (i%(32*compression) == (31*compression)) {
      output->println("");
    }
    previousValue=value;
  }
}

void printNormal(Print* output, unsigned int intArray[]) {
  for(int i = 0; i < ARRAY_SIZE; i++)
  {
    if (intArray[i]<10)  output->print(" ");
    if (intArray[i]<100)  output->print(" ");
    if (intArray[i]<1000)  output->print(" ");
    if (intArray[i]<10000)  output->print(" ");
    if (intArray[i]<100000)  output->print(" ");
    output->print(intArray[i]);

    if (i%16 == 15) {
      output->println("");
    }
  }
}

// %JKLMNOPQR
//  jklmnopqr
char encoding[]={
  'r','q','p','o','n','m','l','k','j','%','J','K','L','M','N','O','P','Q','R'};

void compress(Print* output, long value) {
  byte nbDigits=floor(log10(abs(value)));
  long firstDigit=value/(pow(10,nbDigits));
  long rest=abs(value-firstDigit*pow(10,nbDigits));
  byte nbDigitsRest=log10(abs(rest));
  output->print(encoding[firstDigit+9]);
  if (nbDigits>0) {
    for (byte j=1; j<(nbDigits-nbDigitsRest); j++) {
      output->print("0"); 
    }
    output->print(rest);
  }
}


void printHeader(Print* output, unsigned int backgroundArray[], byte channel, int currentIntensity, boolean background) {
  output->print(">");
  output->print(INFO[channel]);
  output->print(",I");
  output->print(currentIntensity);
  // we will bring min / max background
  output->print(",RGB");
  output->print(getParameter(PARAM_RED_POINT));
  output->print("/");
  output->print(getParameter(PARAM_GREEN_POINT));
  output->print("/");
  output->print(getParameter(PARAM_BLUE_POINT));
  output->print(",REF");
  output->print(getParameter(PARAM_RED_NM));
  output->print("/");
  output->print(getParameter(PARAM_GREEN_NM));
  output->print("/");
  output->print(getParameter(PARAM_BLUE_NM));
// we print epoch
//  output->print(",E");
//  output->print(now());

  if (background) {
    int unsigned minBackground=65535;
    int unsigned maxBackground=0;
    for (int i=0; i<ARRAY_SIZE; i++) {
      if (backgroundArray[i]<minBackground) minBackground=backgroundArray[i];
      if (backgroundArray[i]>maxBackground) maxBackground=backgroundArray[i];
    }
    output->print(",BG");
    output->print(minBackground);
    output->print("/");
    output->print(maxBackground);
  }
  output->println("");
}

void printResult(Print* output, unsigned int intArray[], unsigned int backgroundArray[], byte channel, int currentIntensity) {
  printHeader(output, backgroundArray, channel, currentIntensity, true);
  // Next, send the measurement stored in the array to host computer using serial (rs-232).
  // communication. This takes ~80 ms during whick time no clock pulses reaches the sensor. 
  // No integration is taking place during this time from the photodiodes as the integration 
  // begins first after the 18th clock pulse after a SI pulse is inserted:
  if (getParameter(PARAM_COMPRESSION)>0) {
    printCompressed(output, intArray, getParameter(PARAM_COMPRESSION)); 
  } 
  else {
    printNormal(output, intArray); 
  }
}














