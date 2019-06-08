#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#define pi 3.147


int main(int argc,char** argv)
{
	float linear_vel;float goal_dist;float angular_vel;float goal_angle;
	float linear_time_duration;float angular_time_duration;

	ros::init(argc,argv, "forward" );
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_navigation",100);

	linear_vel = 0.2;
	goal_dist = 1.0;
	linear_time_duration = goal_dist / linear_vel;

	angular_vel = 0.2; // radian
	goal_angle  = pi;
	angular_time_duration = goal_angle / angular_vel;

	int ticks;

	geometry_msgs::Twist cmd;

	int rate = 10;
	ros::Rate r(rate);

	for(int i=0;i<2;i++)
	{
		ticks = rate * linear_time_duration;
		cmd.linear.x = linear_vel;
		cmd.angular.z= 0;
		for(int j=0;j<ticks;j++)
		{
			pub.publish(cmd);
			r.sleep();
		}
		cmd.linear.x = 0.0;
		cmd.angular.z= 0.0;
		pub.publish(cmd);
		ros::Duration(1).sleep();

		ticks = rate * angular_time_duration;
		cmd.linear.x = 0.0;
		cmd.angular.z= angular_vel;
		for(int k=0;k<ticks;k++)
		{
			pub.publish(cmd);
			r.sleep();
		}

		cmd.linear.x = 0.0;
		cmd.angular.z= 0.0;
		pub.publish(cmd);
		ros::Duration(1).sleep();
	}








	ros::shutdown();

	return 0;
}
