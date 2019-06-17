#define constrain(value,min,max) ( (value)< (min) ? (min) : ( (value)>(max)? (max) : (value) ) )

#include "controller.h"
#include <ros/ros.h>
#include <chefbot_facedetection/centroid.h>
#include <geometry_msgs/Twist.h>

float old_angular_z = 0.0;
float angular_z = 0.0;// 0.23
int leftMargin = 295;
int rightMargin= 345;
float maxAngularVelocity = 1.0;
float minAngularVelocity = -1.0;
float Kp =   0.7;
float Ki =   0.01;
float Kd =   0.6;


int main(int argc,char** argv)
{
  ros::init(argc,argv,"face_tracker_contrller_node");
  ros::NodeHandle n;

  ControlClass cc(&n);
  ros::spin();
  return 0;

}

//---------IMPLEMENT--------------//
ControlClass::ControlClass(ros::NodeHandle *nh) : n(*nh)
{
  initAll();
}


void ControlClass::initAll()
{
  sub = n.subscribe("/face_centroid",50,&ControlClass::callback,this);
  pub = n.advertise<geometry_msgs::Twist>("cmd_navigation",50,true);
}


float::ControlClass::tunePID(float old_angular_z, int req_x, int act_x)
{
  float new_angular_z = 0.0;
  float new_x = 0.0;
  double err=0.0;
  double last_err = 0.0;
  double pidTerm = 0.0;
  double int_err = 0.0;
  err = req_x - act_x;

  int_err += err;
  pidTerm = Kp * err + Kd * (err - last_err) + Ki * int_err;

  new_x = constrain(double(old_angular_z)*2/640.0 + pidTerm, minAngularVelocity,maxAngularVelocity);
  new_angular_z = 2/640 * new_x;
  
  return new_angular_z;
}


void::ControlClass::callback(const chefbot_facedetection::centroid::ConstPtr& msg)
{
  geometry_msgs::Twist tt;
  int act_x = msg->x;
  int req_x = 320;

  if(act_x <= 300 || act_x >= 340)
  {
      angular_z = tunePID(old_angular_z,req_x, act_x);
      old_angular_z = angular_z;
      tt.angular.z = angular_z;
  }
  else{
    tt.angular.z = 0.0;
  }
  pub.publish(tt);

}
