void setup() {
  pinMode(A3, INPUT);
  analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop() {
  double value = analogRead(A3);
  Serial.println(value * 0.005);
  delay(1000);
}
