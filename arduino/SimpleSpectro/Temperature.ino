#ifdef TEMPERATURE_ADDRESS

// NCT75 temperature sensorce

NIL_WORKING_AREA(waThreadTemperature, 128);

NIL_THREAD(ThreadTemperature, arg) {
  writeConfig(TEMPERATURE_ADDRESS, 1 << 5); // use use oneshot mode to consume 3ua
  while (true) {
    setParameter(PARAM_TEMPERATURE, readTemperature(TEMPERATURE_ADDRESS));
    nilThdSleepMilliseconds(1000);
  }
}


// we have a good reproductivity if we average on 50 values ...

int readTemperature(uint8_t address) {
  float temperature = 0;
  for (byte i = 0; i < 50; i++) {
    oneShot(address);
    nilThdSleepMilliseconds(50); // one shot should take max 48.5 ms
    WireM.requestFrom(address, (uint8_t)2);
    temperature += (((WireM.read() << 8) | WireM.read()) >> 4) * 6.25;
  }
  return (int)(temperature / 50);
}

void writeConfig(byte address, byte value) {
  WireM.beginTransmission(address);
  WireM.write(0x01);               // Address the Configuration register
  WireM.write(value);         // configuration
  WireM.endTransmission();
  WireM.beginTransmission(address);
  WireM.write(0x00);   // go back o the address to read tempearture
  WireM.endTransmission();
}

void oneShot(byte address) {
  WireM.beginTransmission(address);
  WireM.write(0x04);
  WireM.write(0); // need to write whatever value
  WireM.endTransmission();
  WireM.beginTransmission(address);
  WireM.write(0x00);   // go back o the address to read temperature
  WireM.endTransmission();
}


void sleepTemperature() {

}

void wakeUpTemperature() {

}

#endif
