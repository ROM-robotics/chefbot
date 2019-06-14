#ifndef CONTROLLER_CLASS_H
#define CONTROLLER_CLASS_H

#include <ros/ros.h>
#include <chefbot_facedetection/centroid.h>
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

  void callback(const chefbot_facedetection::centroid::ConstPtr &msg);
  float tunePID(float angular_z, int req_x, int act_x);
};

#endif
