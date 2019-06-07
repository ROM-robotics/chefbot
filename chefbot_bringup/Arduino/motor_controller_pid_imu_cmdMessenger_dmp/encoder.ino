void setupEncoders(){

  right_count = 0;
  left_count = 0;
  countAnt1 = 0;
  countAnt2 = 0;
  
  pinMode(right_encoderA, INPUT); 
  pinMode(right_encoderB, INPUT); 
  digitalWrite(right_encoderA, HIGH);                // turn on pullup resistor
  digitalWrite(right_encoderB, HIGH);
  attachInterrupt(digitalPinToInterrupt(right_encoderA), encoder1, RISING);

  pinMode(left_encoderA, INPUT); 
  pinMode(left_encoderB, INPUT); 
  digitalWrite(left_encoderA, HIGH);                // turn on pullup resistor
  digitalWrite(left_encoderB, HIGH);
  attachInterrupt(digitalPinToInterrupt(left_encoderA), encoder2, RISING);
}

void encoder1() {
  right_EncoderBSet = digitalRead(right_encoderB);   // read the input pin
  right_count += right_EncoderBSet ? -1 : +1;
}
void encoder2() {
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  left_EncoderBSet = digitalRead(left_encoderB);   // read the input pin
  left_count -= left_EncoderBSet ? -1 : +1;
}
