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
    cmdMessenger.sendCmdArg(end_bit);
    cmdMessenger.sendCmdEnd();
    
    cmdMessenger.sendCmdStart(imu);
    cmdMessenger.sendCmdArg(q.x,6);
    cmdMessenger.sendCmdArg(q.y,6);
    cmdMessenger.sendCmdArg(q.z,6);
    cmdMessenger.sendCmdArg(q.w,6);
    cmdMessenger.sendCmdArg(end_bit);
    cmdMessenger.sendCmdEnd();
}
