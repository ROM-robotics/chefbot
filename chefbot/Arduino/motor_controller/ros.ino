
void setupROS(){
  nh.initNode();
  nh.getHardware()->setBaud(57600);
  nh.subscribe(sub);
  nh.advertise(rpm_pub);
}



//void handle_cmd( const geometry_msgs::Twist& cmd_msg) {
//  double x = cmd_msg.linear.x;
//  double z = cmd_msg.angular.z;
//
//  // Velocity to left velocity and right velocity(wheel velocity)
//  double right = 1.0 * x + (z * track_width / 2); 
//  double left  = 1.0 * x - (z * track_width / 2);
//
//  // ms to rpm
//  right = right *60 / (pi * wheel_diameter);
//  left  = left  *60 / (pi * wheel_diameter);
//
//  rpm_req1 = right;
//  rpm_req2 = left;  
// 
//}

void publishRPM(unsigned long time) {
  rpm_msg.header.stamp = nh.now();
  rpm_msg.vector.x = rpm_act1;
  rpm_msg.vector.y = rpm_act2;
  rpm_msg.vector.z = double(time)/1000; // millis to seconds
  rpm_pub.publish(&rpm_msg);
  nh.spinOnce();
}



void handle_cmd( const geometry_msgs::Twist& cmd_msg) {
  double x = cmd_msg.linear.x;
  double z = cmd_msg.angular.z;
  if (z == 0) {     // go straight
    // convert m/s to rpm
    rpm_req1 = x*60/(pi*wheel_diameter);
    rpm_req2 = rpm_req1;
  }
  else if (x == 0) {
    // convert rad/s to rpm
    rpm_req2 = z*track_width*60/(wheel_diameter*pi*2);
    rpm_req1 = -rpm_req2;
  }
  else {
    rpm_req1 = x*60/(pi*wheel_diameter)-z*track_width*60/(wheel_diameter*pi*2);
    rpm_req2 = x*60/(pi*wheel_diameter)+z*track_width*60/(wheel_diameter*pi*2);
  }
}
