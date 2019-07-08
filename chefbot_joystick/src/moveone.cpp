#include <ros/ros.h>
#include <std_msgs/String.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib_msgs/GoalStatus.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseGoal.h>
//#include <visualization_msgs/Marker.h>
#include <math.h>
#include <stdio.h>
//#include "class.h"

#define pi 3.1417

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> move_base;

static geometry_msgs::Quaternion createQuaternionFromRPY(double roll, double pitch, double yaw);


	void moveforward()
		{
			ROS_INFO("ha hah a");
			geometry_msgs::Quaternion quaternions[4];
			double euler_angles[4]={0,0,0,0};

			for(int i=0;i<4;i++)
			{
				quaternions[i]=createQuaternionFromRPY(0,0,euler_angles[i]);
			}

			move_base move_base("move_base",true);
			move_base.waitForServer(ros::Duration(60));

			geometry_msgs::Pose waypoints[4];	
			
			waypoints[0].position.x=1.0;
			waypoints[0].position.y=0.0;//0.0
			waypoints[0].position.z=0.0;//0.0
			waypoints[0].orientation.x=quaternions[0].x;
			waypoints[0].orientation.y=quaternions[0].y;
			waypoints[0].orientation.z=quaternions[0].z;
			waypoints[0].orientation.w=quaternions[0].w;
			move_base_msgs::MoveBaseGoal goal;
			goal.target_pose.header.frame_id="map";
			goal.target_pose.header.stamp=ros::Time::now();
			goal.target_pose.pose=waypoints[0];
			move_base.sendGoal(goal);
		
		}
	void movebackward()
		{
			geometry_msgs::Quaternion quaternions[4];
			double euler_angles[4]={0,0,0,0};

			for(int i=0;i<4;i++)
			{
				quaternions[i]=createQuaternionFromRPY(0,0,euler_angles[i]);
			}

			move_base move_base("move_base",true);
			move_base.waitForServer(ros::Duration(60));

			geometry_msgs::Pose waypoints[4];	
			
			waypoints[0].position.x=-1.0;
			waypoints[0].position.y=0.0;//0.0
			waypoints[0].position.z=0.0;//0.0
			waypoints[0].orientation.x=quaternions[0].x;
			waypoints[0].orientation.y=quaternions[0].y;
			waypoints[0].orientation.z=quaternions[0].z;
			waypoints[0].orientation.w=quaternions[0].w;
			move_base_msgs::MoveBaseGoal goal;
			goal.target_pose.header.frame_id="map";
			goal.target_pose.header.stamp=ros::Time::now();
			goal.target_pose.pose=waypoints[0];
			move_base.sendGoal(goal);
		
		}
	void moveleft()
		{
			geometry_msgs::Quaternion quaternions[4];
			double euler_angles[4]={0,0,0,0};

			for(int i=0;i<4;i++)
			{
				quaternions[i]=createQuaternionFromRPY(0,0,euler_angles[i]);
			}

			move_base move_base("move_base",true);
			move_base.waitForServer(ros::Duration(60));

			geometry_msgs::Pose waypoints[4];	
			
			waypoints[0].position.x=0.0;
			waypoints[0].position.y=1.0;//0.0
			waypoints[0].position.z=0.0;//0.0
			waypoints[0].orientation.x=quaternions[0].x;
			waypoints[0].orientation.y=quaternions[0].y;
			waypoints[0].orientation.z=quaternions[0].z;
			waypoints[0].orientation.w=quaternions[0].w;
			move_base_msgs::MoveBaseGoal goal;
			goal.target_pose.header.frame_id="map";
			goal.target_pose.header.stamp=ros::Time::now();
			goal.target_pose.pose=waypoints[0];
			move_base.sendGoal(goal);
		
		}
	void moveright()
		{
			geometry_msgs::Quaternion quaternions[4];
			double euler_angles[4]={0,0,0,0};

			for(int i=0;i<4;i++)
			{
				quaternions[i]=createQuaternionFromRPY(0,0,euler_angles[i]);
			}

			move_base move_base("move_base",true);
			move_base.waitForServer(ros::Duration(60));

			geometry_msgs::Pose waypoints[4];	
			
			waypoints[0].position.x=0.0;
			waypoints[0].position.y=-1.0;//0.0
			waypoints[0].position.z=0.0;//0.0
			waypoints[0].orientation.x=quaternions[0].x;
			waypoints[0].orientation.y=quaternions[0].y;
			waypoints[0].orientation.z=quaternions[0].z;
			waypoints[0].orientation.w=quaternions[0].w;
			move_base_msgs::MoveBaseGoal goal;
			goal.target_pose.header.frame_id="map";
			goal.target_pose.header.stamp=ros::Time::now();
			goal.target_pose.pose=waypoints[0];
			move_base.sendGoal(goal);
		
		}

void callback(const std_msgs::String::ConstPtr& p)
{

	ros::NodeHandle n;
	ROS_INFO("i got %s",p->data.c_str());
	std_msgs::String dd;
	dd.data= p->data.c_str();
	

	if(dd.data == "Plese wait 60 seconds, I am Moving Forward")
		{
			//ROS_INFO("OK");
			moveforward();
		}
	else if (dd.data == "Plese wait 60 seconds, I am Moving Backward")
		{
			//ROS_INFO("OK");
			movebackward();
		}
	else if(dd.data == "Plese wait 60 seconds, I am Moving Left")
		{
			moveleft();
		}
	else if(dd.data == "Plese wait 60 seconds, I am Moving Right")
		{
			moveright();
		}
	else 
		{
			ROS_INFO("ERROR_MSG");
		}
}
	

int main(int argc,char** argv)
{
	ros::init(argc,argv,"nav_test");
	ros::NodeHandle n;
	int rate=10;
	ros::Subscriber sub= n.subscribe ("response",50,callback);
	move_base_msgs::MoveBaseGoal goal;
	move_base move_base("move_base",true);
	move_base.waitForServer(ros::Duration(60));

	move_base.sendGoal(goal);
	ros::spin();
}

static geometry_msgs::Quaternion createQuaternionFromRPY(double roll, double pitch, double yaw) 
{   
    geometry_msgs::Quaternion q;
    double t0 = cos(yaw * 0.5);
    double t1 = sin(yaw * 0.5);
    double t2 = cos(roll * 0.5);
    double t3 = sin(roll * 0.5);
    double t4 = cos(pitch * 0.5);
    double t5 = sin(pitch * 0.5);
    q.w = t0 * t2 * t4 + t1 * t3 * t5;
    q.x = t0 * t3 * t4 - t1 * t2 * t5;
    q.y = t0 * t2 * t5 + t1 * t3 * t4;
    q.z = t1 * t2 * t4 - t0 * t3 * t5;
    return q;
}