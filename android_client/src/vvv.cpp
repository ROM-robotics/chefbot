#include <ros/ros.h>
#include <std_msgs/String.h>
#include <jsk_gui_msgs/VoiceMessage.h>

#include "class.h"


int main (int argc, char** argv)
{
	ros::init(argc,argv,"android_client");
	ros::NodeHandle n;

	RosClass rc(&n);
	ros::spin();
	return 0;
}
//implement
RosClass::RosClass(ros::NodeHandle* nodeHandle) : n (*nodeHandle)  //member initializer
{
	init_subscriber();
	init_publisher();
}

void RosClass::init_subscriber()
{
	sub = n.subscribe("/android/publish_voice_string/recognizer/output",50,&RosClass::callback,this);
}

void RosClass::init_publisher()
{
	pub = n.advertise<std_msgs::String>("chatter",50,true);
}

void RosClass::callback(const jsk_gui_msgs::VoiceMessageConstPtr &p)
{
	std_msgs::String ss;
	ss.data = p->texts.size();
	ROS_INFO("I receive: [%s]", p->texts.size());
	
	pub.publish(ss);
}
