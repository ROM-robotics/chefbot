#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Vector3.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include "robot_specs.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

bool publish_tf = false;
bool use_imu = false;

double right_act_rpm = 0.0;
double left_act_rpm = 0.0;
double rpm_req1 = 0.0;
double rpm_req2 = 0.0;
double gyro_x = 0.0;
double gyro_y = 0.0;
double gyro_z = 0.0;
double rpm_dt = 0.0;
double x_pos = 0.0;
double y_pos = 0.0;
double theta = 0.0;
double delta_x = 0.0;
double delta_y = 0.0;
double delta_theta = 0.0;
//float roll = 0.0;
//float pitch= 0.0;
//float yaw = 0.0;

ros::Time current_time;
ros::Time rpm_time(0.0);
ros::Time last_time(0.0);


void handle_rpm( const geometry_msgs::Vector3Stamped& rpm) {
  right_act_rpm = rpm.vector.x;
  left_act_rpm = rpm.vector.y;
  rpm_dt = rpm.vector.z;
  rpm_time = rpm.header.stamp;
}
// void handle_quat( const geometry_msgs::Vector3 gyro) {
//   //roll = imu.vector.x;
//   //pitch= imu.vector.y;
//   //yaw  = imu.vector.z;
//   gyro_z = gyro.z;
// }

int main(int argc, char** argv){
  ros::init(argc, argv, "base_controller");

  ros::NodeHandle n;
  ros::NodeHandle nh_private_("~");
  ros::Subscriber sub = n.subscribe("rpm_act_msg", 50, handle_rpm);
  //ros::Subscriber imu_sub = n.subscribe("android_gyro", 50, handle_quat);
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster broadcaster;

  double rate = 10.0;
  double linear_scale_positive = 1.0;
  double linear_scale_negative = 1.0;
  double angular_scale_positive = 1.0;
  double angular_scale_negative = 1.0;
  double angular_scale_accel = 1.0;

  double acc_theta = 0.0;
  double acc_x = 0.0;
  double acc_max_theta = 0.0;
  double acc_max_x = 0.0;
  double alpha = 0.0;

  double dt = 0.0;
  double x = 0.0;
  double y = 0.0;

  double angular_displacement = 0.0;
  double dth_gyro = 0.0;
  double dth = 0.0;

  double dth_prev = 0.0;
  double dth_curr = 0.0;
  double dxy_prev = 0.0;
  double linear_displacement = 0.0;
  double vx = 0.0;
  double vy = 0.0;
  double vth = 0.0;

  char base_link[] = "base_link";
  char odom[] = "/odom";
  ros::Duration d(1.0);
  nh_private_.getParam("publish_rate", rate);
  nh_private_.getParam("publish_tf", publish_tf);
  nh_private_.getParam("linear_scale_positive", linear_scale_positive);
  nh_private_.getParam("linear_scale_negative", linear_scale_negative);
  nh_private_.getParam("angular_scale_positive", angular_scale_positive);
  nh_private_.getParam("angular_scale_negative", angular_scale_negative);
  nh_private_.getParam("angular_scale_accel", angular_scale_accel);
  nh_private_.getParam("alpha", alpha);
  nh_private_.getParam("use_imu", use_imu);

  ros::Rate r(rate);
  while(n.ok()){
    ros::spinOnce();
    // ros::topic::waitForMessage<geometry_msgs::Vector3Stamped>("rpm", n, d);
    current_time = ros::Time::now();
    dt = rpm_dt;
    // linear_displacement = (right_act_rpm+left_act_rpm) / 2;
    // rpm to wheel velocity
    // (X rev/1 min) x (1 min/60s) x (pi*d/1 rev)
    //  velocity to distance
    //  linear_displacement = v * dt
    // 
    // s=r * theta , theta = s/r , theta is always radian
    
    
    linear_displacement = (right_act_rpm+left_act_rpm)*dt*wheel_diameter*pi/(60*2);
    //angular_velocity = (right_act_rpm-left_act_rpm)/track_width;          
    //angular_displacement = angular_velocity*dt*wheel_diameter*pi/60;     // rad per sec * sec per one = radian
    angular_displacement = (right_act_rpm-left_act_rpm)*dt*wheel_diameter*pi/(60*track_width);

    if (use_imu) dth_gyro = dt*gyro_z;
    dth = alpha*angular_displacement + (1-alpha)*dth_gyro;
    dth = alpha*angular_displacement;

    if (dth > 0) dth *= angular_scale_positive;
    if (dth < 0) dth *= angular_scale_negative;
    if (linear_displacement > 0) linear_displacement *= linear_scale_positive;
    if (linear_displacement < 0) linear_displacement *= linear_scale_negative;
//-----------------------------------------------------------------//
    x = cos(dth) * linear_displacement;
    y = -sin(dth) * linear_displacement; 

    delta_x = (cos(theta) * x - sin(theta) * y);
    delta_y = (sin(theta) * x + cos(theta) * y);
    delta_theta = dth;

    x_pos += delta_x;
    y_pos += delta_y;
    theta += delta_theta;

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


    if (right_act_rpm == 0 && left_act_rpm == 0){
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
    vx = (dt == 0)?  0 : linear_displacement/dt;
    vth = (dt == 0)? 0 : dth/dt;
    odom_msg.child_frame_id = base_link;
    odom_msg.twist.twist.linear.x = vx;
    odom_msg.twist.twist.linear.y = 0.0;
    odom_msg.twist.twist.angular.z = dth;

    odom_pub.publish(odom_msg);
    last_time = current_time;
    r.sleep();
  }
}
/*
msg.pose.covariance = {cov_x, 0, 0, 0, 0, 0,
                        0, cov_y, 0, 0, 0, 0,
                        0, 0, 99999, 0, 0, 0,
                        0, 0, 0, 99999, 0, 0,
                        0, 0, 0, 0, 99999, 0,
                        0, 0, 0, 0, 0, rcov_z}

*/
