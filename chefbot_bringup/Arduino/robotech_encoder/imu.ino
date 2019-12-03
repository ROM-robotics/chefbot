///* 
// *  gyro register 00 is full scale range(+-250 deg per second) that have angular vel rate)--> 41.6 rmp
// *  eg 250/360 * 60 = 41.6 rpm
//
// *  accel AFS_SEL = 0 is full scale range(+-2g) that is least significant bit 16384LSB/s
// *  eg 20000/16384 = 1.2 g
//*/
//void setupIMU()
//{
//  Wire.begin();
//  Wire.beginTransmission(0b1101000);// (AD0 low)slave address  , if AD0 is high address is (0b1101000)
//  Wire.write(0x6B); // power management
//  Wire.write(0b00000000); // sleep-register B6 to zero
//  Wire.endTransmission();
//  Wire.beginTransmission(0b1101000); // Accessing the mpu
//  Wire.write(0x1B); // access the register 1B(gyroscope configrution)
//  Wire.write(0b00000000); // settint the gyro to full scale
//  Wire.endTransmission();
//  Wire.beginTransmission(0b1101000);
//  Wire.write(0x1C);
//  Wire.write(0b00000000); //setting accel to +- 2g
//  Wire.endTransmission();
//}
//
//void updateIMU()
//{
//  recordAccelRegisters();
//  recordGyroRegisters();
//}
//
//void recordGyroRegisters(){
//  Wire.beginTransmission(0b1101000);
//  Wire.write(0x43);
//  Wire.endTransmission();
//  Wire.requestFrom(0b1101000,6);
//  while(Wire.available() < 6);
//  gyroX = Wire.read() << 8 | Wire.read();
//  gyroY = Wire.read() << 8 | Wire.read();
//  gyroZ = Wire.read() << 8 | Wire.read();
//  processGyroData();
//}
//
//void processGyroData(){
//  rotX = gyroX / 131.0;
//  rotY = gyroY / 131.0;
//  rotZ = gyroZ / 131.0;
//
//  // deg to radian
//  rotX = rotX * 0.017453292;
//  rotY = rotY * 0.017453292;
//  rotZ = rotZ * 0.017453292;
//}
//
//
//void recordAccelRegisters(){
//  Wire.beginTransmission(0b1101000);// i2c of mpu
//  Wire.write(0x3B); //Starting reg for accel readings
//  Wire.endTransmission();
//  Wire.requestFrom(0b1101000,6);
//  while(Wire.available()<6);
//  accelX = Wire.read()<<8|Wire.read();// store first two bytes into a
//  accelY = Wire.read()<<8|Wire.read();// store second two bytes into a
//  accelZ = Wire.read()<<8|Wire.read();// store last two bytes into a
//  processAccelData();
//}
//
//void processAccelData(){
//  gForceX = accelX / 16384.0;
//  gForceY = accelY / 16384.0;
//  gForceZ = accelZ / 16384.0;
//}

//void printData(){
//  Serial.print("Gyro (rad)");
//  Serial.print(" X=");
//  Serial.print(rotX);
//  Serial.print(" Y=");
//  Serial.print(rotY);
//  Serial.print(" Z=");
//  Serial.println(rotZ);
//
//  Serial.print(" Accel (g)");
//  Serial.print(" X=");
//  Serial.print(gForceX);
//  Serial.print(" Y=");
//  Serial.print(gForceY);
//  Serial.print(" Z=");
//  Serial.println(gForceZ);
//}
