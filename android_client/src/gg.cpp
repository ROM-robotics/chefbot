#include <ros/ros.h>
#include <std_msgs/String.h>

	ros::Subscriber sub;
	ros::Publisher pub;
	void callback(const std_msgs::StringConstPtr &p)
{
	std_msgs::String ss;
	ss.data = p->data.c_str();
	ROS_INFO("I receive: [%s]", p->data.c_str());
	
	pub.publish(ss);
}
int main (int argc, char** argv)
{
	ros::init(argc,argv,"android_client");
	ros::NodeHandle n;
	sub = n.subscribe("/android/publish_voice_string/recognizer/output",50,callback);
	pub = n.advertise<std_msgs::String>("chatter",50,true);
	
	ros::spin();
	return 0;
}
