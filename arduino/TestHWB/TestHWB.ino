void setup() {
  DDRE |= 0x04; // pinMode PE2 OUTPUT
}

// the loop function runs over and over again forever
void loop() {
  delay(4000);
  PORTE |= 0x04; // Set PE2
  delay(4000);
  PORTE &= 0xFB; // Clear PE2

}
