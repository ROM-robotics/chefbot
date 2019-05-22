
void setupROS(){
  nh.initNode();
  nh.getHardware()->setBaud(57600);
  nh.subscribe(sub);
  nh.advertise(v3_pub);
  nh.advertise(imu_raw);
}



void handle_rpm_req( const chefbot::rpm& rpm_req ) {

  rpm_req1 = rpm_req.req_right;
  rpm_req2 = rpm_req.req_left;  
 
}

void publishRPM(unsigned long time) {
  v3_msg.header.stamp = nh.now();
  v3_msg.vector.x = rpm_act1;
  v3_msg.vector.y = rpm_act2;
  v3_msg.vector.z = double(time)/1000; // millis to seconds
  v3_pub.publish(&v3_msg);
  nh.spinOnce();
}

void publishIMU()
{
  v.stamp = nh.now();
  v.gyroX = rotX;
  v.gyroY = rotY;
  v.gyroZ = rotZ;
  v.accelX = gForceX;
  v.accelY = gForceY;
  v.accelZ = gForceZ;

  imu_raw.publish(&v);
  nh.spinOnce();
}
