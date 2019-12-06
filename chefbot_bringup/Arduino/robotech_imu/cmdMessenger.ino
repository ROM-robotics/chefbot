void setupMessenger(){
  Serial.begin(115200); 
  cmdMessenger.printLfCr();  
  attachCommandCallbacks();
  cmdMessenger.sendCmd(Start,"Arduino has started!");  
}


void sendMessage(float x) {

    float y = x / 1000.0; // millis to seconds

    cmdMessenger.sendCmdStart(actual_rpm);
    cmdMessenger.sendCmdArg(right_count);
    cmdMessenger.sendCmdArg(left_count); 
    cmdMessenger.sendCmdArg(y,3);       // millis to seconds
    cmdMessenger.sendCmdArg(degree);
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
