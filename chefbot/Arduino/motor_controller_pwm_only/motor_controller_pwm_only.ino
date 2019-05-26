// Author: Pyae Soan Aung (Ghostman @ greenhackers)
// Credits:
//   Sung Jik Cha
//   http://forum.arduino.cc/index.php?topic=8652.0
//   Dallaby   http://letsmakerobots.com/node/19558#comment-49685
//   Bill Porter  http://www.billporter.info/?p=286
//   bobbyorr (nice connection diagram) http://forum.pololu.com/viewtopic.php?f=15&t=1923


#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <CmdMessenger.h>

//Motor Shield headers
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"   //re uncomment this one

#define LOOPTIME        100       // PID loop time(ms)
#define sign(x) (x > 0) - (x < 0)

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Select which 'port' M1, M2, M3 or M4. 
Adafruit_DCMotor *motor_right = AFMS.getMotor(1); 
Adafruit_DCMotor *motor_left = AFMS.getMotor(2);

volatile long right_count = 0;          
volatile long left_count = 0;
volatile bool right_EncoderBSet; // helper variable for interrupt
volatile bool left_EncoderBSet;  // helper variable for interrupt
long countAnt1 = 0;
long countAnt2 = 0;
float Kp =   0.5;
float Kd =   0;
float Ki =   0;

int direction1;
int direction2;

int rpm_req1 = 0;
int rpm_req2 = 0;

//--------------------new-------------------/
int end_bit = 0;
char field_separator   = ',';
char command_separator = ' ';
char escape_separator  = '/';
float frequency=0;
enum
{
  Start,          // 0
  rpm_req,        // 1
  right_rpm_req,  // 2
  left_rpm_req,   // 3
  Rate,           // 4
  Actual,         // 5
};
/* -----------IMU------------- */
long accelX,accelY,accelZ;
volatile float gForceX,gForceY,gForceZ;

long gyroX,gyroY,gyroZ;
volatile float rotX,rotY,rotZ;

//------------------------------------------
CmdMessenger cmdMessenger = CmdMessenger(Serial,field_separator,command_separator,escape_separator);

void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(rpm_req,setRPM);
  //cmdMessenger.attach(right_rpm_req,setRight);
  //cmdMessenger.attach(left_rpm_req,setLeft);
}
void setRPM(){
  rpm_req1 = cmdMessenger.readInt16Arg();
  rpm_req2 = cmdMessenger.readInt16Arg();
}
void setRight()
{
  rpm_req1 = cmdMessenger.readInt16Arg();
}
void setLeft()
{
  rpm_req2 = cmdMessenger.readInt16Arg();
}

void setup() { 
 setupMotors();
 setupMessenger();
}

void loop() {
int x = 90;
  cmdMessenger.feedinSerialData();
     cmdMessenger.sendCmdStart(Actual);
    cmdMessenger.sendCmdArg(rpm_req1);
    cmdMessenger.sendCmdArg(rpm_req2);
    cmdMessenger.sendCmdArg(x); //((time-lastMilli)/1000); // millis to seconds
    cmdMessenger.sendCmdArg(rotX,6);
    cmdMessenger.sendCmdArg(rotY,6);
    cmdMessenger.sendCmdArg(rotZ,6);
    cmdMessenger.sendCmdArg(gForceX,6);
    cmdMessenger.sendCmdArg(gForceY,6);
    cmdMessenger.sendCmdArg(gForceZ,6);
    cmdMessenger.sendCmdArg(end_bit);
    cmdMessenger.sendCmdEnd();
    delay(100);
//    int PWM_val1 = 250;
//    int PWM_val2 = 250;
//
//    if(PWM_val1 > 0) direction1 = FORWARD;
//    else if(PWM_val1 < 0) direction1 = BACKWARD;
//    if (rpm_req1 == 0) direction1 = RELEASE;
//    if(PWM_val2 > 0) direction2 = FORWARD;
//    else if(PWM_val2 < 0) direction2 = BACKWARD;
//    if (rpm_req2 == 0) direction2 = RELEASE;
//    motor_right->run(direction1);
//    motor_left->run(direction2);
//
//    motor_right->setSpeed(abs(PWM_val1));
//    motor_left->setSpeed(abs(PWM_val2));
}
