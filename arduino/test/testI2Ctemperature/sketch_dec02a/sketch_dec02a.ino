
#include <Wire.h>        // Wire header file for I2C and 2 wire

#define TMP75_Address 0b1001000

void setup() {
  Serial.begin(9600);
  Wire.begin();
  /*
  Wire.beginTransmission(TMP75_Address);
  Wire.write(0x01);               // Address the Configuration register
  Wire.write(0b00000000);         // configuration 
  Wire.endTransmission();
  */
}

// Main Program Infinite loop
void loop() {
  float temp = readTemp(TMP75_Address);
  Serial.println(temp);
  delay(1000);
}


float readTemp(byte address) {
  Wire.requestFrom(address, 2);
  return (((Wire.read() << 8) | Wire.read()) >> 4) * 0.0625;
}
