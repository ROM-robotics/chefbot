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

//ROS headers
#include <ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>
#include "robot_specs.h"

//Motor Shield headers
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"   //re uncomment this one

#define right_encoderA      2     // (interrupt numbers 0)
#define right_encoderB      3     // (interrupt numbers 1)
#define left_encoderA      18     // (interrupt numbers 5)
#define left_encoderB      19     // (interrupt numbers 4)
#define LOOPTIME        100       // PID loop time(ms)
#define SMOOTH      10

#define sign(x) (x > 0) - (x < 0)

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Select which 'port' M1, M2, M3 or M4. 
Adafruit_DCMotor *motor_right = AFMS.getMotor(1); 
Adafruit_DCMotor *motor_left = AFMS.getMotor(2);

unsigned long lastMilli = 0;       // loop timing 
unsigned long lastMilliPub = 0;

double rpm_req1 = 0;
double rpm_req2 = 0;
double rpm_act1 = 0;
double rpm_act2 = 0;
double rpm_req1_smoothed = 0;
double rpm_req2_smoothed = 0;
int direction1 = FORWARD;
int direction2 = FORWARD;
int prev_direction1 = RELEASE;
int prev_direction2 = RELEASE;
int PWM_val1 = 0;
int PWM_val2 = 0;

volatile long right_count = 0;          
volatile long left_count = 0;
volatile bool right_EncoderBSet; // helper variable for interrupt
volatile bool left_EncoderBSet;  // helper variable for interrupt
long countAnt1 = 0;
long countAnt2 = 0;
float Kp =   0.5;
float Kd =   0;
float Ki =   0;

void publishRPM(unsigned long time);

ros::NodeHandle nh;
void handle_cmd( const geometry_msgs::Twist& cmd_msg);
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", handle_cmd);

geometry_msgs::Vector3Stamped rpm_msg;
ros::Publisher rpm_pub("rpm", &rpm_msg);

ros::Time current_time;
ros::Time last_time;

void setup() { 
 setupMotors();
 setupROS();
 setupEncoders(); 
}

void loop() {
  nh.spinOnce();
  unsigned long time = millis();
  if(time-lastMilli>= LOOPTIME)   {      // enter timed loop
    getMotorData(time-lastMilli);
    PWM_val1 = updatePid(1, PWM_val1, rpm_req1, rpm_act1);
    PWM_val2 = updatePid(2, PWM_val2, rpm_req2, rpm_act2);

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
    
    publishRPM(time-lastMilli);
    lastMilli = time;
  }
  if(time-lastMilliPub >= LOOPTIME) {
  //  publishRPM(time-lastMilliPub);
    lastMilliPub = time;
  }
}
