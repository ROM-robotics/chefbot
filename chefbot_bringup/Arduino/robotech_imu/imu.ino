
void setupIMU()
{
    mpu.begin();
    mpu.calcGyroOffsets(true);
  //mpu.setGyroOffsets(0.38,0.02,0.61); // mpu with red male connector
   // mpu.setGyroOffsets(0.02,0.24,-1.01);  // old one
}



void updateIMU()
{
   mpu.update();
   degree = mpu.getAngleZ();
   if(degree > 360) degree = degree%360;
   else if(degree < -360) degree = degree%360;
 
   //radian    = degree * 0.0174532;    // radian = degree * (2*pi / 360.0); 
}
