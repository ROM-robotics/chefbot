#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <chefbot_3/rpm_req.h>
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
	ros::init(argc,argv,"twist_to_motor");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("cmd_vel", 50, twistCallback);
	ros::Publisher  right_pub = nh.advertise<chefbot_3::rpm_req>("right_rpm_req", 50);
	ros::Publisher  left_pub = nh.advertise<chefbot_3::rpm_req>("left_rpm_req", 50);

	
	chefbot_3::rpm_req right_cmd;
	chefbot_3::rpm_req left_cmd;
	ros::Rate r(10);

	while(ros::ok())
	{
		right_cmd.data = req_right;
		left_cmd.data  = req_left;
		
		right_pub.publish(right_cmd);
		left_pub.publish(left_cmd);

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