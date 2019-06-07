#include <ros/ros.h>
#include <chefbot_bringup/vect6.h>
#include <sensor_msgs/Imu.h>

float gyroZ,gyroX,gyroY,accelX,accelY,accelZ;

void callback(const chefbot_bringup::vect6::ConstPtr &msg)
{
	ROS_INFO("GYRO Z = %f", msg->gyroZ);

	gyroX = msg->gyroX;
	gyroY = msg->gyroY;
	gyroZ = msg->gyroZ;

	accelX= msg->accelX;
	accelY= msg->accelY;
	accelZ= msg->accelZ;
}
int main(int argc,char**argv)
{
	ros::init(argc,argv,"velToImuRaw");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("/imu_raw",1000,callback);
	ros::Publisher pub = nh.advertise<sensor_msgs::Imu>("/imu/data_raw",1000);

	ros::Rate r(10);
	sensor_msgs::Imu imu;
	imu.header.frame_id = "gyro_link";
	imu.orientation_covariance[0] = 1e6;
	imu.orientation_covariance[1] = 0;
	imu.orientation_covariance[2] = 0;
	imu.orientation_covariance[3] = 0;
	imu.orientation_covariance[4] = 1e6;
	imu.orientation_covariance[5] = 0;
	imu.orientation_covariance[6] = 0;
	imu.orientation_covariance[7] = 0;
	imu.orientation_covariance[8] = 1e-6;

	imu.angular_velocity_covariance[0] = 1e6;
	imu.angular_velocity_covariance[1] = 0;
	imu.angular_velocity_covariance[2] = 0;
	imu.angular_velocity_covariance[3] = 0;
	imu.angular_velocity_covariance[4] = 1e6;
	imu.angular_velocity_covariance[5] = 0;
	imu.angular_velocity_covariance[6] = 0;
	imu.angular_velocity_covariance[7] = 0;
	imu.angular_velocity_covariance[8] = 1e-6;

	imu.linear_acceleration_covariance[0] = -1;
	imu.linear_acceleration_covariance[1] = 0;
	imu.linear_acceleration_covariance[2] = 0;
	imu.linear_acceleration_covariance[3] = 0;
	imu.linear_acceleration_covariance[4] = 0;
	imu.linear_acceleration_covariance[5] = 0;
	imu.linear_acceleration_covariance[6] = 0;
	imu.linear_acceleration_covariance[7] = 0;
	imu.linear_acceleration_covariance[8] = 0;

	while(ros::ok())
	{
		imu.header.stamp = ros::Time::now();
		imu.angular_velocity.x = gyroX;
		imu.angular_velocity.y = gyroY;
		imu.angular_velocity.z = gyroZ;

		imu.linear_acceleration.x = accelX;
		imu.linear_acceleration.y = accelY;
		imu.linear_acceleration.z = accelZ;

		pub.publish(imu);
		ros::spinOnce();
		r.sleep();
	}

	return 0;





}
