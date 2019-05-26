
#include <CmdMessenger.h>  // CmdMessenger

char field_separator   = ',';
char command_separator = ' ';
char escape_separator  = '/';

volatile int rpm_req1 = 0;
volatile int rpm_req2 = 0;
volatile int rpm_act1 = 100;
volatile int rpm_act2 = 200;
volatile float time_ = 300.2;
volatile float gyroX = 0.400;
volatile float gyroY = 0.400;
volatile float gyroZ = 0.400;
volatile float accelX = 0.400;
volatile float accelY = 0.400;
volatile float accelZ = 0.400;
int end_bit = 0;
int LOOPTIME = 100;       // PID loop time(ms)


// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial,field_separator,command_separator,escape_separator);

// This is the list of recognized commands. These can be commands that can either be sent or received. 
// In order to receive, attach a callback function to these events
enum
{
  start,      // 0
  rightRPM,   // 1
  leftRPM,    // 2
  Rate,  // 3
  Actual,     // 4 right_actual,left_actual,time_,gyroZ
};

// Callbacks define on which received commands we take action
void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(rightRPM,setRightRPM);
  cmdMessenger.attach(leftRPM,setLeftRPM);
}

void setRightRPM()
{
  //set_righ_rpm_value
  rpm_req1 = cmdMessenger.readInt16Arg();
}
void setLeftRPM()
{
  //set_left_rpm_value
  rpm_req2 = cmdMessenger.readInt16Arg();
}



void setup() 
{
  
  Serial.begin(115200); 
  cmdMessenger.printLfCr();  
  attachCommandCallbacks();
  cmdMessenger.sendCmd(start,"Arduino has started!");

}


void loop() 
{
  // Process incoming serial data, and perform callbacks
  cmdMessenger.feedinSerialData();
  cmdMessenger.sendCmdStart(Actual);
  cmdMessenger.sendCmdArg(rpm_act1);
  cmdMessenger.sendCmdArg(rpm_act2);
  cmdMessenger.sendCmdArg(time_);
  cmdMessenger.sendCmdArg(gyroX);
  cmdMessenger.sendCmdArg(gyroY);
  cmdMessenger.sendCmdArg(gyroZ);
  cmdMessenger.sendCmdArg(accelX);
  cmdMessenger.sendCmdArg(accelY);
  cmdMessenger.sendCmdArg(accelZ);
  cmdMessenger.sendCmdArg(end_bit);
  cmdMessenger.sendCmdEnd();
  
  
  delay(100);
}
