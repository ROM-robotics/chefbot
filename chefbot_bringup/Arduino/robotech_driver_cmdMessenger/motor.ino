void setupMotors() {
  rpm_req1 = 0;
  rpm_req2 = 0;
  rpm_act1 = 0;
  rpm_act2 = 0;

  PWM_val1 = 0;
  PWM_val2 = 0;
  //setPWM();
  Release();
}
void getMotorData(unsigned long time)  {
  rpm_act1 = double((right_count - countAnt1) * 60000) / double(time * new_enc_ticks);
  rpm_act2 = double((left_count - countAnt2) * 60000) / double(time * new_enc_ticks);

  countAnt1 = right_count;
  countAnt2 = left_count;
}
int updatePid(int id, int old_pwm, double targetValue, double currentValue) {
  double pidTerm = 0; 
  double error = 0;
  double new_rpm = 0;
  double new_pwm = 0;
  static double last_error1 = 0;
  static double last_error2 = 0;
  static double int_error1 = 0;
  static double int_error2 = 0;

  float Kp = 0.47;    // Left
  float Ki =  0.00052;
  float Kd =   1.9;

  float p = 0.45;     //Right 
  float i =  0.00049;
  float d = 1.9;

  error = targetValue - currentValue;
  
  if (id == 1) { // Right
    int_error1 += error;
    pidTerm = p * error + d * (error - last_error1) + i * int_error1;
    last_error1 = error;
  }
  if (id == 2) { // Left
    int_error2 += error;
    pidTerm = Kp * error + Kd * (error - last_error2) + Ki * int_error2;
    last_error2 = error;
  }
  new_rpm = constrain(double(old_pwm) * MAX_RPM / 255.0 + pidTerm, -MAX_RPM, MAX_RPM);
  new_pwm = 255.0 * new_rpm / MAX_RPM;
  return int(new_pwm);
}

void Forward() {
  digitalWrite(Right_in1, LOW);
  digitalWrite(Right_in2, HIGH);
  digitalWrite(Left_in1, LOW);
  digitalWrite(Left_in2, HIGH);
  analogWrite(ENA1, abs(PWM_val1));
  analogWrite(ENA2, abs(PWM_val2));
}

void Backward() {
  digitalWrite(Right_in1, HIGH);
  digitalWrite(Right_in2, LOW);
  digitalWrite(Left_in1, HIGH);
  digitalWrite(Left_in2, LOW);
  analogWrite(ENA1, abs(PWM_val1));
  analogWrite(ENA2, abs(PWM_val2));
}

void Left() {
  digitalWrite(Right_in1, HIGH);
  digitalWrite(Right_in2, LOW);
  digitalWrite(Left_in1, LOW);
  digitalWrite(Left_in2, HIGH);
  analogWrite(ENA1, abs(PWM_val1));
  analogWrite(ENA2, abs(PWM_val2));
}

void Right() {
  digitalWrite(Right_in1, LOW);
  digitalWrite(Right_in2, HIGH);
  digitalWrite(Left_in1, HIGH);
  digitalWrite(Left_in2, LOW);
  analogWrite(ENA1, abs(PWM_val1));
  analogWrite(ENA2, abs(PWM_val2));
}

void Release() {
  digitalWrite(Right_in1, LOW);
  digitalWrite(Right_in2, LOW);
  digitalWrite(Left_in1, LOW);
  digitalWrite(Left_in2, LOW);
  analogWrite(ENA1, 0);
  analogWrite(ENA2, 0);
}
//void setPWM() {
  //analogWrite(ENA1, abs(PWM_val1));
  //analogWrite(ENA2, abs(PWM_val2));
//}
