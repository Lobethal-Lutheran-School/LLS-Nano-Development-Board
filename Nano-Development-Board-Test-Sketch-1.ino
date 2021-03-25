//
// A simple sketch to test the LLS-Nano-Development-Board hardware v1.0
// 
// Licence GPL v2.0
// Copyright Dr Erich S. Heinzle
//

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sweepDirection = 1;
  while (analogRead(A1) > 500) {
    int sweepSpeed = analogRead(A7);
    int sweepChange = analogRead(A0) < 500;
    if (sweepChange)
      sweepDirection = 1 - sweepDirection;
    if (sweepDirection) {
      for (int i = 2; i < 8; i++) {
        digitalWrite(i, HIGH);
        delay(sweepSpeed);
        digitalWrite(i, LOW);
        delay(sweepSpeed);
      }
    } else {
      for (int i = 7; i > 1; i--) {
        digitalWrite(i, HIGH);
        delay(sweepSpeed);
        digitalWrite(i, LOW);
        delay(sweepSpeed);
      }
    }
  }
}
