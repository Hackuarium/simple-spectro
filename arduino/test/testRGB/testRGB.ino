
#define RED    A0
#define GREEN  A1
#define BLUE   A2


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);


}

  int counter = 0;
void loop() {
  switch (counter % 3) {
    case 0:
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      break;
    case 1:
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
      break;
    case 2:
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);
      break;
  }

  counter++;
  delay(500);
}
