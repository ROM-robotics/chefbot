void setupMotors(){
  AFMS.begin();  // create with the default frequency 1.6KHz 
  
  rpm_req1 = 0;
  rpm_req2 = 0;
  rpm_act1 = 0;
  rpm_act2 = 0;
  PWM_val1 = 0;
  PWM_val2 = 0;
  
  motor_right->setSpeed(0);
  motor_left->setSpeed(0);
  motor_right->run(FORWARD);
  motor_right->run(RELEASE);
  motor_left->run(FORWARD);
  motor_left->run(RELEASE);
}

void getMotorData(unsigned long time)  {
 // rpm_act1 = double(right_count-countAnt1)/double(time) * 181.8181;
 // rpm_act2 = double(left_count-countAnt2)/double(time) * 181.8181;
 
 rpm_act1 = double((right_count-countAnt1)*60*1000)/double(time*encoder_pulse*gear_ratio);
 rpm_act2 = double((left_count-countAnt2)*60*1000)/double(time*encoder_pulse*gear_ratio);
 
 countAnt1 = right_count;
 countAnt2 = left_count;
}


int updatePid(int id, int command, double targetValue, double currentValue) {
  double pidTerm = 0;                            // PID correction
  double error = 0;
  double new_pwm = 0;
  double new_cmd = 0;
  static double last_error1 = 0;
  static double last_error2 = 0;
  static double int_error1 = 0;
  static double int_error2 = 0;
  
  error = targetValue-currentValue;
  if (id == 1) {
    int_error1 += error;
    pidTerm = Kp*error + Kd*(error-last_error1) + Ki*int_error1;
    last_error1 = error;
  }
  else {
    int_error2 += error;
    pidTerm = Kp*error + Kd*(error-last_error2) + Ki*int_error2;
    last_error2 = error;
  }
  new_pwm = constrain(double(command)*MAX_RPM/4095.0 + pidTerm, -MAX_RPM, MAX_RPM);
  new_cmd = 4095.0*new_pwm/MAX_RPM;
  return int(new_cmd);
}
