/* Author: Pyae Soan Aung (Ghostman @ greenhackers)
    Credits:
      Sung Jik Cha      http://forum.arduino.cc/index.php?topic=8652.0
      Dallaby           http://letsmakerobots.com/node/19558#comment-49685
      Bill Porter       http://www.billporter.info/?p=286
      bobbyorr(nice connection diagram) http://forum.pololu.com/viewtopic.php?f=15&t=1923
*/
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


#define right_encoderA      2     // (interrupt numbers 1)
#define right_encoderB      3
#define left_encoderA      18     // (interrupt numbers 5)
#define left_encoderB      19     // (interrupt numbers 4)
#define SMOOTH      10
#define sign(x) (x > 0) - (x < 0) // if x>0 --> 1 , if x<0 --> -1, if x=0 --> 0
#define LOOPTIME        100

#define ENA1 10
#define Right_in1 9
#define Right_in2 8

#define ENA2 5
#define Left_in1 7
#define Left_in2 6

#include <Wire.h>
#include "robot_specs.h"
#include <CmdMessenger.h>

/*------------------IMU-------------------- */
//long accelX, accelY, accelZ;
//volatile float gForceX, gForceY, gForceZ;

//long gyroX, gyroY, gyroZ;
//volatile float rotX, rotY, rotZ;

//--------------------new-------------------/
int end_bit = 0;
char field_separator   = ',';
char command_separator = ' ';
char escape_separator  = '/n';
float frequency = 0;
enum
{
  Start,          // 0
  rpm_req,        // 1
  right_rpm_req,  // 2
  left_rpm_req,   // 3
  Rate,           // 4
  actual_rpm     // 5
  //imu,            // 6
};

//------------------------------------------

CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator, escape_separator);

unsigned long lastMilli = 0;       // loop timing
unsigned long lastMilliPub = 0;

double rpm_req1 = 0;
double rpm_req2 = 0;
double rpm_act1 = 0;
double rpm_act2 = 0;

int PWM_val1 = 0; // right
int PWM_val2 = 0; // left

volatile long right_count = 0;
volatile long left_count = 0;
//volatile bool right_EncoderBSet; // helper variable for interrupt
//volatile bool left_EncoderBSet;  // helper variable for interrupt
long countAnt1 = 0;
long countAnt2 = 0;


////////////////////////////// callback ////////////////////////////////////////

void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(rpm_req, setRPM);
  //cmdMessenger.attach(leftRPM,setLeftRPM);
  //cmdMessenger.attach(Rate,setRate);
}

void setRPM()
{
  rpm_req1 = cmdMessenger.readInt16Arg();
  rpm_req2 = cmdMessenger.readInt16Arg();
}

void setup() {
  setupMessenger();
  setupMotors();
  //setupIMU();
  setupEncoders();
}
void loop() {
  unsigned long time = millis();
  if (time - lastMilli >= LOOPTIME)   {  // enter timed loop ( 100 ms or greater)

    cmdMessenger.feedinSerialData();
    int x = time - lastMilli;
    getMotorData(x);

    PWM_val1 = updatePid(1, PWM_val1, rpm_req1, rpm_act1);
    PWM_val2 = updatePid(2, PWM_val2, rpm_req2, rpm_act2);

    if (PWM_val1 > 0 && PWM_val2 > 0) {
      Forward();
    }
    else if (PWM_val1 < 0 && PWM_val2 < 0) {
      Backward();
    }
    else if (PWM_val1 > 0 && PWM_val2 < 0) {
      Right();
    }
    else if (PWM_val1 < 0 && PWM_val2 > 0) {
      Left();
    }
    if (PWM_val1 == 0 && PWM_val2 == 0) {
      Release();
    }
    //setPWM();
    // updateIMU();
    float y = x / 1000.0; // millis to seconds
    sendMessage(y);
    lastMilli = time;
  }
  //if (time - lastMilliPub >= LOOPTIME) {
  //publishAll(time-lastMilli);
  //  lastMilliPub = time;
  //  }
}
