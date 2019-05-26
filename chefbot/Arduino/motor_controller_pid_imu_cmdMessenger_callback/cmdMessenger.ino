void setupMessenger(){
  Serial.begin(115200); 
  cmdMessenger.printLfCr();  
  attachCommandCallbacks();
  cmdMessenger.sendCmd(Start,"Arduino has started!");  
}


void publishAll(unsigned long time) {

  
  cmdMessenger.sendCmdStart(Actual);
  cmdMessenger.sendCmdArg(rpm_act1);
  cmdMessenger.sendCmdArg(rpm_act2);
  cmdMessenger.sendCmdArg(double(time)/1000); // millis to seconds
  cmdMessenger.sendCmdArg(rotX);
  cmdMessenger.sendCmdArg(rotY);
  cmdMessenger.sendCmdArg(rotZ);
  cmdMessenger.sendCmdArg(gForceX);
  cmdMessenger.sendCmdArg(gForceY);
  cmdMessenger.sendCmdArg(gForceZ);
  cmdMessenger.sendCmdArg(end_bit);
  cmdMessenger.sendCmdEnd();
  
//  v3_msg.header.stamp = nh.now();
//  v3_msg.vector.x = rpm_act1;
//  v3_msg.vector.y = rpm_act2;
//  v3_msg.vector.z = double(time)/1000; // millis to seconds
  
}
