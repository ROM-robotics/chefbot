void setupEncoders() {

  right_count = 0;
  left_count = 0;
  countAnt1 = 0;
  countAnt2 = 0;

  pinMode(right_encoderA, INPUT);
  pinMode(right_encoderB, INPUT);
  pinMode(left_encoderA, INPUT);
  pinMode(left_encoderB, INPUT);

  digitalWrite(right_encoderA, LOW);
  digitalWrite(right_encoderB, LOW);
  digitalWrite(left_encoderA, LOW);
  digitalWrite(left_encoderB, LOW);

  attachInterrupt(0, encoder1A, CHANGE);
  attachInterrupt(1, encoder1B, CHANGE);
  attachInterrupt(5, encoder2A, CHANGE);
  attachInterrupt(4, encoder2B, CHANGE);
}

void encoder1A() {
  if (digitalRead(right_encoderA) == digitalRead(right_encoderB)) {
    right_count = right_count - 1;
  }
  else                                                     {
    right_count = right_count + 1;
  }
}
void encoder1B() {
  if (digitalRead(right_encoderA) == digitalRead(right_encoderB)) {
    right_count = right_count + 1;
  }
  else                                                     {
    right_count = right_count - 1;
  }
}

void encoder2A() {
  if (digitalRead(left_encoderA) == digitalRead(left_encoderB)) {
    left_count = left_count - 1;
  }
  else                                                     {
    left_count = left_count + 1;
  }
}
void encoder2B() {
  if (digitalRead(left_encoderA) == digitalRead(left_encoderB)) {
    left_count = left_count + 1;
  }
  else                                                     {
    left_count = left_count - 1;
  }
}
