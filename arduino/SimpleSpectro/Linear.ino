// Parallel read of the linear sensor array TSL1402R (= the sensor with 256 photodiodes)
//-------------------------------------------------------------------------------------

// Define various ADC prescaler:
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

void setupLinear() {
    // To set up the ADC, first remove bits set by Arduino library, then choose 
  // a prescaler: PS_16, PS_32, PS_64 or PS_128:
  ADCSRA &= ~PS_128;  
  ADCSRA |= PS_32; // <-- Using PS_32 makes a single ADC conversion take ~30 us
  

  // Initialize two Arduino pins as digital output:
  pinMode(CLKpin, OUTPUT); 
  pinMode(SIpin, OUTPUT);  
}


void clockPulse()
{
  delayMicroseconds(1);
  digitalWrite(CLKpin, HIGH);
  delayMicroseconds(1);
  digitalWrite(CLKpin, LOW);
}

void resetClockPulse() {
  delayMicroseconds(1);
  digitalWrite(SIpin, HIGH);
  delayMicroseconds(1);
  digitalWrite(CLKpin, HIGH);
  delayMicroseconds(1);
  digitalWrite(SIpin, LOW);
  delayMicroseconds(1);
  digitalWrite(CLKpin, LOW);
}


