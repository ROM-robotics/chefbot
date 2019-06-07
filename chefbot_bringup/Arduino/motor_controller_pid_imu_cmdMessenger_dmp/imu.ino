
void dmpDataReady() {
    mpuInterrupt = true;
}
void setupIMU()
{
  mpu.initialize();

    devStatus = mpu.dmpInitialize();
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
      
          ;
          }

}

void updateIMU() {
    // if programming failed, don't try to do anything
    
    
    
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
          ;
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();


    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x01) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        
            // display quaternion values in easy matrix form: w x y z
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            //mpu.dmpGetGravity(&gravity, &q);
            //mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

            //Assigning YAW,PITCH,ROLL to vector message and publishing the values
            
           // orient.x = ypr[0] * 180/M_PI;
           // orient.y = ypr[1] * 180/M_PI;
           // orient.z = ypr[2] * 180/M_PI;
          //  imu_pub.publish(&orient);

            //Assigning values to TF header and publish the transform
          //  t.header.frame_id = frameid;
           // t.child_frame_id = child;
           // t.transform.translation.x = 1.0; 
           // t.transform.rotation.x = q.x;
           // t.transform.rotation.y = q.y; 
          //  t.transform.rotation.z = q.z; 
          //  t.transform.rotation.w = q.w;  
          //  t.header.stamp = nh.now();
          //  broadcaster.sendTransform(t);



          //  nh.spinOnce();
   

          //  delay(200);
          
  
    }
}
