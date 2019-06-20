#ifndef CONTROLLER_CLASS_H
#define CONTROLLER_CLASS_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class ControlClass
{
public:
  ControlClass(ros::NodeHandle *nh);
private:
  ros::NodeHandle n;
  ros::Subscriber sub;
  ros::Publisher pub;

  void initAll();

  void callback(const geometry_msgs::Twist::ConstPtr &msg);
};

#endif
