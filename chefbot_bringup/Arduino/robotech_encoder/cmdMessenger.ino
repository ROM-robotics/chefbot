void setupMessenger(){
  Serial.begin(115200); 
  cmdMessenger.printLfCr();  
  attachCommandCallbacks();
  cmdMessenger.sendCmd(Start,"Arduino has started!");  
}


void sendMessage(float y) {

    cmdMessenger.sendCmdStart(actual_rpm);
    cmdMessenger.sendCmdArg(rpm_act1);
    cmdMessenger.sendCmdArg(rpm_act2); 
    cmdMessenger.sendCmdArg(y,3);       // millis to seconds
    cmdMessenger.sendCmdArg(PWM_val1);
    cmdMessenger.sendCmdArg(PWM_val2);
    cmdMessenger.sendCmdArg(end_bit);
    cmdMessenger.sendCmdEnd();
//    
//    cmdMessenger.sendCmdStart(imu);
//    cmdMessenger.sendCmdArg(rotX,6);
//    cmdMessenger.sendCmdArg(rotY,6);
//    cmdMessenger.sendCmdArg(rotZ,6);
//    cmdMessenger.sendCmdArg(gForceX,6);
//    cmdMessenger.sendCmdArg(gForceY,6);
//    cmdMessenger.sendCmdArg(gForceZ,6);
//    cmdMessenger.sendCmdArg(end_bit);
//    cmdMessenger.sendCmdEnd();
}
