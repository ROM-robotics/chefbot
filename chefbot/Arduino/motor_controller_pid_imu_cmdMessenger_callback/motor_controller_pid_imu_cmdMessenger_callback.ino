/* Author: Pyae Soan Aung (Ghostman @ greenhackers)
 *  Credits:
 *    Sung Jik Cha      http://forum.arduino.cc/index.php?topic=8652.0
 *    Dallaby           http://letsmakerobots.com/node/19558#comment-49685
 *    Bill Porter       http://www.billporter.info/?p=286
 *    bobbyorr(nice connection diagram) http://forum.pololu.com/viewtopic.php?f=15&t=1923
 */
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#define right_encoderA      2     // (interrupt numbers 0)
#define right_encoderB      3     // (interrupt numbers 1)
#define left_encoderA      18     // (interrupt numbers 5)
#define left_encoderB      19     // (interrupt numbers 4)
#define SMOOTH      10
#define sign(x) (x > 0) - (x < 0) // if x>0 --> 1 , if x<0 --> -1, if x=0 --> 0



//Motor Shield headers
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"   //re uncomment this one
#include "robot_specs.h"
#include <CmdMessenger.h>

/* -----------IMU------------- */
long accelX,accelY,accelZ;
volatile float gForceX,gForceY,gForceZ;

long gyroX,gyroY,gyroZ;
volatile float rotX,rotY,rotZ;

//--------------------new-------------------/
int end_bit = 0;
char field_separator   = ',';
char command_separator = ' ';
char escape_separator  = '/';
float frequency=0;
enum
{
  Start,      // 0
  Rpm_request,// 1
  Rate,       // 2
  Actual,     // 3,
};

//------------------------------------------

CmdMessenger cmdMessenger = CmdMessenger(Serial,field_separator,command_separator,escape_separator);

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor_right = AFMS.getMotor(1); // 1 --> right, 2 --> left
Adafruit_DCMotor *motor_left = AFMS.getMotor(2);

#define LOOPTIME  100   // PID loop time(ms)

unsigned long lastMilli = 0;       // loop timing 
unsigned long lastMilliPub = 0;

double rpm_req1 = 0;
double rpm_req2 = 0;
double rpm_act1 = 0;
double rpm_act2 = 0;

int direction1 = FORWARD;  // right
int direction2 = FORWARD;  // left
int prev_direction1 = RELEASE; // right
int prev_direction2 = RELEASE; // left
int PWM_val1 = 0; // right
int PWM_val2 = 0; // left

volatile long right_count = 0;          
volatile long left_count = 0;
volatile bool right_EncoderBSet; // helper variable for interrupt
volatile bool left_EncoderBSet;  // helper variable for interrupt
long countAnt1 = 0;
long countAnt2 = 0;
float Kp =   0.7;
float Ki =   0.01;
float Kd =   0.6;


////////////////////////////// callback ////////////////////////////////////////

void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(Rpm_request,setRPM);
}

void setRPM()
{
  rpm_req1 = cmdMessenger.readInt16Arg();
  rpm_req2 = cmdMessenger.readInt16Arg();

    
    cmdMessenger.sendCmdStart(Actual);
    cmdMessenger.sendCmdArg(rpm_act1);
    cmdMessenger.sendCmdArg(rpm_act2);
    cmdMessenger.sendCmdArg(x); //((time-lastMilli)/1000); // millis to seconds
    cmdMessenger.sendCmdArg(rotX,6);
    cmdMessenger.sendCmdArg(rotY,6);
    cmdMessenger.sendCmdArg(rotZ,6);
    cmdMessenger.sendCmdArg(gForceX,6);
    cmdMessenger.sendCmdArg(gForceY,6);
    cmdMessenger.sendCmdArg(gForceZ,6);
    cmdMessenger.sendCmdArg(end_bit);
    cmdMessenger.sendCmdEnd();
   

}

//void setRate()
//{
//  int r = cmdMessenger.readInt16Arg();
//  frequency = 1/r;
//}

////////////////////////////////////////////////////////////////////////////

void setup() { 
 //setupMessenger();
   Serial.begin(115200); 
  cmdMessenger.printLfCr();  
  attachCommandCallbacks();
  cmdMessenger.sendCmd(Start,"Arduino has started!");  
 setupMotors();
 setupIMU();
 setupEncoders(); 
}

void loop() {
  cmdMessenger.feedinSerialData();
  
  unsigned long time = millis();  
  if(time-lastMilli>= LOOPTIME)   {      // enter timed loop ( 100 ms or greater)

    
    getMotorData(time-lastMilli);

    PWM_val1 = 55;///updatePid(1, PWM_val1, rpm_req1, rpm_act1);
    PWM_val2 = 55;///updatePid(2, PWM_val2, rpm_req2, rpm_act2);

    if(PWM_val1 > 0) direction1 = FORWARD;
    else if(PWM_val1 < 0) direction1 = BACKWARD;
    if (rpm_req1 == 0) direction1 = RELEASE;
    if(PWM_val2 > 0) direction2 = FORWARD;
    else if(PWM_val2 < 0) direction2 = BACKWARD;
    if (rpm_req2 == 0) direction2 = RELEASE;
    motor_right->run(direction1);
    motor_left->run(direction2);

    motor_right->setSpeed(abs(PWM_val1));
    motor_left->setSpeed(abs(PWM_val2));
    
    updateIMU();
   
    lastMilli = time;
    
    
  }
  if(time-lastMilliPub >= LOOPTIME) {
    //publishAll(time-lastMilli);
    lastMilliPub = time;
  }
  
}
