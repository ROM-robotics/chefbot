void setupMotors(){
  AFMS.begin();  // create with the default frequency 1.6KHz   
  motor_right->setSpeed(0);
  motor_left->setSpeed(0);
  motor_right->run(FORWARD);
  motor_right->run(RELEASE);
  motor_left->run(FORWARD);
  motor_left->run(RELEASE);
}
