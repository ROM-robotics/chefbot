#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <chefbot_bringup/rpm.h>
#include "robot_specs.h"

int req_right = 0;
int req_left  = 0;

int subscribe_count;
int publish_count;

void twistCallback( const geometry_msgs::Twist& cmd_msg) {
 double x = cmd_msg.linear.x;
 double theta = cmd_msg.angular.z;

 // Velocity to left velocity and right velocity(wheel velocity)
 double right = 1.0 * x + (theta * track_width / 2);
 double left  = 1.0 * x - (theta * track_width / 2);

 // ms to rpm
 right = right *60 / (pi * wheel_diameter);
 left  = left  *60 / (pi * wheel_diameter);

 req_right = right;
 req_left = left;
 //ROS_INFO_STREAM("Count : "<< subscribe_count);
 //ROS_INFO_STREAM("right: "<< right << " left: "<< left);
 subscribe_count++;

}

int main(int argc,char** argv)
{
	ros::init(argc,argv,"twist_to_motors");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("cmd_vel", 50, twistCallback);
	ros::Publisher  pub = nh.advertise<chefbot_bringup::rpm>("rpm_req_msg", 50);


	// bool status = ros::param::has("love");
	// while(!status)
	// {
	// 	// This is blocking function for waiting arduino_node.py (Written by ko su san)
	// 	ROS_INFO_STREAM("Set paremtert : name=love value=yes");
	// 	ROS_INFO_STREAM(";P");
	// 	ROS_INFO_STREAM(";P");

	// 	status = ros::param::has("love");
	// }


	chefbot_bringup::rpm RPM;
	ros::Rate r(10);

	while(ros::ok())
	{
		RPM.req_right = req_right;
		RPM.req_left  = req_left;

		pub.publish(RPM);

		ros::spinOnce();
		r.sleep();
		//ROS_INFO_STREAM("Publish"<< publish_count);
		//publish_count++;
	}


	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////
// void twistCallback( const geometry_msgs::Twist& cmd_msg) {
//   double x = cmd_msg.linear.x;
//   double theta = cmd_msg.angular.z;
//   if (theta == 0) {     // go straight
//     // convert m/s to rpm
//     req_right = x*60/(pi*wheel_diameter);
//     req_left = req_right;
//   }
//   else if (x == 0) {
//     // convert rad/s to rpm
//     req_left = theta*track_width*60/(wheel_diameter*pi*2);
//     req_right = -req_left;
//   }
//   else {
//     req_right = x*60/(pi*wheel_diameter)-theta*track_width*60/(wheel_diameter*pi*2);
//     req_left = x*60/(pi*wheel_diameter)+theta*track_width*60/(wheel_diameter*pi*2);
//   }
// }
