
void mcp7428(byte led, int intensity) {
  WireM.beginTransmission(0x60);
  WireM.write(0b01000000 | led << 1);
  WireM.write(highByte(intensity));
  WireM.write(lowByte(intensity));
  WireM.endTransmission();
}

