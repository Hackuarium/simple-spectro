
void mcp4728(byte led, int intensity) {
  nilSemWait(&lockTimeCriticalZone);
  WireM.beginTransmission(0x60);
  WireM.write(0b01000000 | led << 1);
  WireM.write(0b10010000 | highByte(intensity));
  WireM.write(lowByte(intensity));
  WireM.endTransmission();
  nilSemSignal(&lockTimeCriticalZone);
}

