void print2Digits(Print* output, int number) {
  // utility function for digital clock display: prints preceding colon and leading 0
  if(number < 10) output->print('0');
  output->print(number);
}

void epochToString(time_t time, Print* output) {
  // digital clock display of the time
  output->print(year(time)); 
  output->print("-");
  print2Digits(output,month(time));
  output->print("-");
  print2Digits(output,day(time));
  output->print(" ");
  print2Digits(output,hour(time));
  output->print(":");
  print2Digits(output,minute(time));
  output->print(":");
  print2Digits(output,second(time));
  output->print(" ");
}


