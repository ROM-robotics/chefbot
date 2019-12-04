#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <chefbot_bringup/vect4.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include "robot_specs.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

bool publish_tf = true;
bool use_imu = false;

double prev_right = 0;
double prev_left  = 0;
double right_count= 0;
double left_count = 0;
double delta_r_count = 0;
double delta_l_count = 0;

float delta_time  = 0.0;
float dt = 0.0;

float gyro_theta = 0.0;   // angular displacement

double x_pos = 0; double y_pos = 0;
double theta = 0.0; double delta_theta = 0.0; // or Float
double delta_x = 0.0; double delta_y = 0.0; 

double alpha = 0.0;

ros::Time current_time;
ros::Time last_time(0.0);

void handle_rpm( const chefbot_bringup::vect4& vect) {
  right_count = vect.right_count;
  left_count  = vect.left_count;
  delta_time  = vect.delta_time;
  int degree  = vect.degree;

  gyro_theta = degree * pi / 180.0;  // angular displacement
}


int main(int argc, char** argv){
  ros::init(argc, argv, "base_controller");

  ros::NodeHandle n;
  ros::NodeHandle nh_private_("~");
  ros::Duration(10).sleep();
  ros::Subscriber sub = n.subscribe("rpm_act_msg", 50, handle_rpm);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster broadcaster;

  double rate = 10.0;
  double linear_scale_positive = 1.0;
  double linear_scale_negative = 1.0;
  double angular_scale_positive = 1.0;
  double angular_scale_negative = 1.0;
  double angular_scale_accel = 1.0;
  double x = 0.0;
  double y = 0.0;
  double ang_displacement = 0.0;
  double lin_displacement = 0.0;

  double dth = 0.0;

  char base_link[] = "base_link";
  char odom[] = "odom";

  double vx = 0.0;
  double vy = 0.0;
  double vth = 0.0;

  ros::Duration d(1.0);
  nh_private_.getParam("publish_rate", rate);
  nh_private_.getParam("publish_tf", publish_tf);
  nh_private_.getParam("linear_scale_positive", linear_scale_positive);
  nh_private_.getParam("linear_scale_negative", linear_scale_negative);
  nh_private_.getParam("angular_scale_positive", angular_scale_positive);
  nh_private_.getParam("angular_scale_negative", angular_scale_negative);
  nh_private_.getParam("angular_scale_accel", angular_scale_accel);
  nh_private_.getParam("alpha", alpha);

  ros::Rate r(rate);
  while(n.ok()){
    ros::spinOnce();
    current_time = ros::Time::now();

    dt = delta_time;
    double r_count=0, l_count = 0;
    r_count = right_count; l_count = left_count;


    delta_r_count = r_count - prev_right;
    delta_l_count = l_count - prev_left;

    
    prev_right = r_count;
    prev_left  = l_count;


    double average_count = (delta_r_count + delta_l_count) / 2.0;
    lin_displacement = (average_count * pi * wheel_diameter * dt) / enc_ticks; // dxy_ave

    float step = ( pi * wheel_diameter ) / enc_ticks;
    ang_displacement = (delta_r_count - delta_l_count) * step / track_width;

    dth = alpha * ang_displacement;  
    
    x = cos(dth) * lin_displacement;
    y = -sin(dth) * lin_displacement; // Why minus?

    x_pos += (cos(theta) * x - sin(theta) * y);
    y_pos += (sin(theta) * x + cos(theta) * y);
    theta += dth;
    //theta = current_gyro_theta;

    if(theta >= two_pi) theta -= two_pi;
    if(theta <= -two_pi) theta += two_pi;

    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);

    if(publish_tf) {
      geometry_msgs::TransformStamped t;
      t.header.frame_id = odom;
      t.child_frame_id = base_link;
      t.transform.translation.x = x_pos;
      t.transform.translation.y = y_pos;
      t.transform.translation.z = 0.0;
      t.transform.rotation = odom_quat;
      t.header.stamp = current_time;

      broadcaster.sendTransform(t);
    }

    nav_msgs::Odometry odom_msg;
    odom_msg.header.stamp = current_time;
    odom_msg.header.frame_id = odom;
    odom_msg.pose.pose.position.x = x_pos;
    odom_msg.pose.pose.position.y = y_pos;
    odom_msg.pose.pose.position.z = 0.0;
    odom_msg.pose.pose.orientation = odom_quat;


    if (right_count == prev_right && left_count == prev_left){
      odom_msg.pose.covariance[0] = 1e-9;
      odom_msg.pose.covariance[7] = 1e-3;
      odom_msg.pose.covariance[8] = 1e-9;
      odom_msg.pose.covariance[14] = 1e6;
      odom_msg.pose.covariance[21] = 1e6;
      odom_msg.pose.covariance[28] = 1e6;
      odom_msg.pose.covariance[35] = 1e-9;
      odom_msg.twist.covariance[0] = 1e-9;
      odom_msg.twist.covariance[7] = 1e-3;
      odom_msg.twist.covariance[8] = 1e-9;
      odom_msg.twist.covariance[14] = 1e6;
      odom_msg.twist.covariance[21] = 1e6;
      odom_msg.twist.covariance[28] = 1e6;
      odom_msg.twist.covariance[35] = 1e-9;
    }
    else{
      odom_msg.pose.covariance[0] = 1e-3;
      odom_msg.pose.covariance[7] = 1e-3;
      odom_msg.pose.covariance[8] = 0.0;
      odom_msg.pose.covariance[14] = 1e6;
      odom_msg.pose.covariance[21] = 1e6;
      odom_msg.pose.covariance[28] = 1e6;
      odom_msg.pose.covariance[35] = 1e3;
      odom_msg.twist.covariance[0] = 1e-3;
      odom_msg.twist.covariance[7] = 1e-3;
      odom_msg.twist.covariance[8] = 0.0;
      odom_msg.twist.covariance[14] = 1e6;
      odom_msg.twist.covariance[21] = 1e6;
      odom_msg.twist.covariance[28] = 1e6;
      odom_msg.twist.covariance[35] = 1e3;
    }
    vx = (dt == 0)?  0 : lin_displacement/dt;
    vth = (dt == 0)? 0 : ang_displacement/dt;
    odom_msg.child_frame_id = base_link;
    odom_msg.twist.twist.linear.x = vx;
    odom_msg.twist.twist.linear.y = 0.0;
    odom_msg.twist.twist.angular.z = vth;

    odom_pub.publish(odom_msg);
    last_time = current_time;
    r.sleep();
  }
}