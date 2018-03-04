#ifdef TEMPERATURE_ADDRESS

#include <Wire.h>        // Wire header file for I2C and 2 wire
// NCT75 temperature sensorce

NIL_WORKING_AREA(waThreadTemperature, 128);

NIL_THREAD(ThreadTemperature, arg) {
  Wire.begin();
  writeConfig(TEMPERATURE_ADDRESS, 1 << 5); // use use oneshot mode to consume 3ua
  while (true) {
    setParameter(PARAM_TEMPERATURE, readTemperature(TEMPERATURE_ADDRESS));
    nilThdSleepMilliseconds(1000);
  }
}


// we have a good reproductivity if we average on 50 values ...

int readTemperature(byte address) {
  float temperature = 0;
  for (byte i = 0; i < 50; i++) {
    oneShot(address);
    nilThdSleepMilliseconds(50); // one shot should take max 48.5 ms
    Wire.requestFrom(address, 2);
    temperature += (((Wire.read() << 8) | Wire.read()) >> 4) * 6.25;
  }
  return (int)(temperature / 50);
}

void writeConfig(byte address, byte value) {
  Wire.beginTransmission(address);
  Wire.write(0x01);               // Address the Configuration register
  Wire.write(value);         // configuration
  Wire.endTransmission();
  Wire.beginTransmission(address);
  Wire.write(0x00);   // go back o the address to read tempearture
  Wire.endTransmission();
}

void oneShot(byte address) {
  Wire.beginTransmission(address);
  Wire.write(0x04);
  Wire.write(0); // need to write whatever value
  Wire.endTransmission();
  Wire.beginTransmission(address);
  Wire.write(0x00);   // go back o the address to read tempearture
  Wire.endTransmission();
}

#endif
