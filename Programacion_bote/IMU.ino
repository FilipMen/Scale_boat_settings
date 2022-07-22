/*
    obtener_inclinacion.ino
  Con el código se leen datos de la MPU-6050, este código
  es modificado de la web:
  http://robologs.net/2014/10/15/tutorial-de-arduino-y-mpu-6050/

  Descrito muy bien en el vídeo:
  https://www.youtube.com/watch?v=uN8SYfGwYVw&t=164s

*/

// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}


// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}


void IMU_read()
{
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
//
//  
//  byte ax1 = Buf[0];
//  byte ax2 = Buf[1];
//  
//  byte ay1 = Buf[2];
//  byte ay2 = Buf[3];
//  
//  byte az1 = Buf[4];
//  byte az2 = Buf[5];
//
//
//  byte gx1 = Buf[8];
//  byte gx2 = Buf[9];
//  
//  byte gy1 = Buf[10];
//  byte gy2 = Buf[11];
//  
//  byte gz1 = Buf[12];
//  byte gz2 = Buf[13];
//
//
//  uint8_t ST1;
//  do
//  {
//    I2Cread(MAG_ADDRESS,0x02,1,&ST1);
//  }
//  while (!(ST1&0x01));
//
//
//  uint8_t Mag[7];  
//  I2Cread(MAG_ADDRESS,0x03,7,Mag);
//
//  byte mx1 = Mag[3];
//  byte mx2 = Mag[2];
//  
//  byte my1 = Mag[1];
//  byte my2 = Mag[0];
//  
//  byte mz1 = Mag[5];
//  byte mz2 = Mag[4];
// Read accelerometer and gyroscope
//  uint8_t Buf[14];
//  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
  
  // Create 16 bits values from 8 bits data
  
  // Accelerometer
  ax.myInt16 =-(Buf[0]<<8 | Buf[1]);
  ay.myInt16=-(Buf[2]<<8 | Buf[3]);
  az.myInt16=Buf[4]<<8 | Buf[5];

  // Gyroscope
  gx.myInt16=-(Buf[8]<<8 | Buf[9]);
  gy.myInt16=-(Buf[10]<<8 | Buf[11]);
  gz.myInt16=Buf[12]<<8 | Buf[13];
  
    // Display values
  
  // Accelerometer
  Serial.print (ax.myInt16,DEC); 
  Serial.print ("\t");
  Serial.print (ay.myInt16,DEC);
  Serial.print ("\t");
  Serial.print (az.myInt16,DEC);  
  Serial.print ("\t");
  
  // Gyroscope
  Serial.print (gx.myInt16,DEC); 
  Serial.print ("\t");
  Serial.print (gy.myInt16,DEC);
  Serial.print ("\t");
  Serial.print (gz.myInt16,DEC);  
  Serial.print ("\t");

  
  // _____________________
  // :::  Magnetometer ::: 

  
  // Read register Status 1 and wait for the DRDY: Data Ready
  
  uint8_t ST1;
  do
  {
    I2Cread(MAG_ADDRESS,0x02,1,&ST1);
  }
  while (!(ST1&0x01));

  // Read magnetometer data  
  uint8_t Mag[7];  
  I2Cread(MAG_ADDRESS,0x03,7,Mag);
  

  // Create 16 bits values from 8 bits data
  
  // Magnetometer
  mx.myInt16=-(Mag[3]<<8 | Mag[2]);
  my.myInt16=-(Mag[1]<<8 | Mag[0]);
  mz.myInt16=-(Mag[5]<<8 | Mag[4]);
  
  
  // Magnetometer
  Serial.print (mx.myInt16+200,DEC); 
  Serial.print ("\t");
  Serial.print (my.myInt16-70,DEC);
  Serial.print ("\t");
  Serial.print (mz.myInt16-700,DEC);  
  Serial.print ("\t");
  
  
  
  // End of line
  Serial.println("");
}
