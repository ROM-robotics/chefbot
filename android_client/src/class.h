#ifndef ROS_CLASS_H
#define ROS_CLASS_H

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <jsk_gui_msgs/VoiceMessage.h>

class RosClass
{
	public:
		RosClass(ros::NodeHandle *nodeHandle);
	private:
		ros::NodeHandle n;
		ros::Subscriber sub;
		ros::Publisher pub;
		//ros::ServiceServer server;

		void init_subscriber();
		void init_publisher();
		//void init_server();

		void callback(const jsk_gui_msgs::VoiceMessageConstPtr &p);
		
	};

#endif