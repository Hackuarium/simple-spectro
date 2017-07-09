
#ifdef KEYBOARD


#define WAIT_TIME 50

void printKeyboard(unsigned int intArray[]) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    delay(WAIT_TIME);
    if (i % 16 == 0) {
      Keyboard.print(intArray[i]);
    }
    else {
      // we will store the difference
      long diff = intArray[i] - intArray[i - 1];
      // need to get the first digit with the sign
      compress(&Keyboard, diff);
    }
    if (i % 16 == 15) {
      Keyboard.println("");
    }
  }
}

#endif
