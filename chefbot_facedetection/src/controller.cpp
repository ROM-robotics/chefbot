#include <ros/ros.h>
#include <chefbot_facedetection/centroid.h>
#include <geometry_msgs/Twist.h>

int x;
float angularZ = 0.5;
int leftMargin=295;
int rightMargin=345;

void callback(const chefbot_facedetection::centroid::ConstPtr& msg){

x = msg->x;
ROS_INFO("The result x [%d]",msg->x);

}

int main(int argc,char ** argv){


ros::init(argc, argv,"controller");
ros::NodeHandle nh ;
ros::Subscriber sub = nh.subscribe("face_centroid",100,callback);

ros::Publisher pub = nh.advertise<geometry_msgs::Twist> ("cmd_vel",100);

 nh.getParam("angularSpeed", angularZ);

geometry_msgs::Twist tw;
ros::Rate r(10);

while (ros::ok()){
	if(x<=leftMargin){
	tw.angular.z=angularZ;
	
	
	}
	else if(x>=rightMargin){
	tw.angular.z= -angularZ;
	}
	else{

		tw.angular.z=0.0;

	}
pub.publish(tw);
ros::spinOnce();
r.sleep();

}

//ros::spin();

}

