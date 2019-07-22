#define constrain(value,min,max) ( (value)< (min) ? (min) : ( (value)>(max)? (max) : (value) ) )

#include "controller.h"
#include <ros/ros.h>
#include <chefbot_facedetection/centroid.h>
#include <geometry_msgs/Twist.h>

float old_angular_z = 0.0;
float angular_z = 0.0;// 0.23
int leftMargin = 300;
int rightMargin= 340;
int centerSetPoint = 320;
float maxAngularVelocity = 0.6;
float minAngularVelocity = -0.6;
float Kp =   0.0;
float Ki =   0.00;
float Kd =   0.0;


int main(int argc,char** argv)
{
  ros::init(argc,argv,"face_tracker_contrller_node");
  ros::NodeHandle n;
  ros::param::get("/Kp", Kp);
  ros::param::get("/Ki", Ki);
  ros::param::get("/Kd", Kd);
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
  pub = n.advertise<geometry_msgs::Twist>("cmd_vel",50,true);
}


float::ControlClass::tunePID(float old_angular_z, int setPoint, int actPoint)
{
	

  float new_angular_z = 0.0;
  float new_x = 0.0;
  double err=0.0;
  double last_err = 0.0;
  double pidTerm = 0.0;
  double int_err = 0.0;
  err = setPoint - actPoint;
  

  int_err += err;
  pidTerm = (float)Kp * err + Kd * (err - last_err) + Ki * int_err;
 last_err = err;
  //ROS_INFO_STREAM("KJDFKSL"<< Kp);

  new_x = constrain(double(old_angular_z) + pidTerm, minAngularVelocity,maxAngularVelocity);
  new_angular_z = new_x;

  ROS_INFO_STREAM("cmd_vel"<< new_angular_z);
  
  return new_angular_z;
}


void::ControlClass::callback(const chefbot_facedetection::centroid::ConstPtr& msg)
{


  geometry_msgs::Twist tt;
  //geometry_msgs::Twist yy; 
  	if(msg->x > 290 && msg->x < 350 )
  {
    tt.angular.z=0.0;
  }
   else 
  {
  tt.angular.z= tunePID(old_angular_z,centerSetPoint,msg->x);
  }
	if(msg->y >130 && msg-> y < 190 ){
  	tt.linear.x = 0.0;
  }
   	else if (msg->y < 130)
  {
  	tt.linear.x = -0.15;
  }
  	else if (msg->y > 190){
  	tt.linear.x = 0.15;
  }
 
  pub.publish(tt);
}
