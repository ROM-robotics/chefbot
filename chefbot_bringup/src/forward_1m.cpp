#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


int main(int argc,char** argv)
{
	float linear_vel;float goal_dist;
	if(argc == 3){
		linear_vel = atoll(argv[1]);
		goal_dist = atoll(argv[2]);
	}
	else{
		ROS_INFO("Usage: rosrun chefbot forward_1m <linear.x> <goal_distance>");
		linear_vel = 0.2;
		goal_dist = 1.0;
	}
	ros::init(argc,argv, "forward" );
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_navigation",100);

	int rate = 10;

	float time_duration;

	int ticks;

	time_duration = goal_dist / linear_vel;
	ticks = rate * time_duration;

	geometry_msgs::Twist cmd;
	cmd.linear.x = linear_vel;

	ros::Rate r(rate);
	for(int i=0;i<ticks;i++)
	{
		pub.publish(cmd);
		r.sleep();
	}

	cmd.linear.x = 0;
	pub.publish(cmd);
	ros::Duration(1).sleep();
	//ros::shutdown();

	return 0;
}
