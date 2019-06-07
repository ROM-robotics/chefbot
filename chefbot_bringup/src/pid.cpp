#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#include <ros/ros.h>
#include <chefbot_bringup/rpm_req.h>
#include <chefbot_bringup/rpm_act.h>
#include <chefbot_bringup/rpm_pid.h>
#include <chefbot_bringup/pwm.h>
#include "robot_specs.h"

int request_rpm = 0;
int actual_rpm = 0;
int pwm_value=0;
float Kp = 0.5;
float Ki = 0;
float Kd = 0;

int updatePid(int pwm_value,int request_rpm,int actual_rpm);

void getReqCallback(const chefbot::rpm_req::ConstPtr &req)
{
	request_rpm = (int)req->data;
}

void getActCallback(const chefbot::rpm_act::ConstPtr &act)
{
	actual_rpm = (int)act->data;
}

int main(int argc,char** argv)
{
	ros::init(argc,argv,"pid_node");
	ros::NodeHandle nh;
	ros::Subscriber req_sub = nh.subscribe("rpm_req",50,getReqCallback);
	ros::Subscriber act_sub = nh.subscribe("act_rpm",50,getActCallback);
	ros::Publisher pub = nh.advertise<chefbot::pwm>("pwm",50);

	chefbot::rpm_pid PWM;
	ros::Rate r(10);

	while(ros::ok())
	{
		pwm_value = updatePid(pwm_value,request_rpm,actual_rpm);
		PWM.data = pwm_value;
		pub.publish(PWM);
		ros::spinOnce();
		r.sleep();
	}

	return 0;
}


int updatePid(int old_pwm_value, int targetValue, int currentValue) {
  double pidTerm = 0;                            // PID correction
  double error = 0;
  double new_rpm = 0;
  double new_pwm = 0;
  static double last_error = 0;
  static double int_error = 0;

  error = targetValue-currentValue;

    int_error += error;
    pidTerm = Kp*error + Kd*(error-last_error) + Ki*int_error;
    last_error = error;

  new_rpm = constrain(double(old_pwm_value)*MAX_RPM/255.0 + pidTerm, -MAX_RPM, MAX_RPM);
  new_pwm = 255.0*new_rpm/MAX_RPM;
  return int(new_pwm);
}
