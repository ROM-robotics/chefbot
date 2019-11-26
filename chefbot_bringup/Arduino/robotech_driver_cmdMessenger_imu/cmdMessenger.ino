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
   
    //cmdMessenger.sendCmdArg(PWM_val1);
    //cmdMessenger.sendCmdArg(PWM_val2);
    cmdMessenger.sendCmdArg(y,3);       // Seconds
    cmdMessenger.sendCmdArg(degree);    // Anguglar Displacement
    cmdMessenger.sendCmdArg(end_bit);
    cmdMessenger.sendCmdEnd();

}
