
#include "controller.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>



int main(int argc,char** argv)
{
  ros::init(argc,argv,"joystick_controller");
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
  sub = n.subscribe("/cmd_vel",50,&ControlClass::callback,this);
  pub = n.advertise<geometry_msgs::Twist>("/cmd_navigation",50,true);
}

  geometry_msgs::Twist tt;



void::ControlClass::callback(const geometry_msgs::Twist::ConstPtr& msg)
{


  float x = msg->linear.x;
  float z = msg->angular.z;


  tt.linear.x = 0.1 * x;
  tt.angular.z = 0.3* z;

  pub.publish(tt);
}
