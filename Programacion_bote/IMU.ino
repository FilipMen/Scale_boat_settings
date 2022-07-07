/*
    obtener_inclinacion.ino
  Con el código se leen datos de la MPU-6050, este código
  es modificado de la web:
  http://robologs.net/2014/10/15/tutorial-de-arduino-y-mpu-6050/

  Descrito muy bien en el vídeo:
  https://www.youtube.com/watch?v=uN8SYfGwYVw&t=164s

   El factor de conversión: w= Lectura*(250/32768) = lectura*(1/131)
*/
void IMU_read()
{
  //Leer los valores del Acelerometro de la IMU
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); //A partir del 0x3B, se piden 6 registros
  AcX.myInt16 = Wire.read() << 8 | Wire.read();
  AcY.myInt16 = Wire.read() << 8 | Wire.read();
  AcZ.myInt16 = Wire.read() << 8 | Wire.read();
  //Leer los valores del Giroscopio
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); //A partir del 0x43, se piden 6 registros
  GyX.myInt16 = Wire.read() << 8 | Wire.read();
  GyY.myInt16 = Wire.read() << 8 | Wire.read();
  GyZ.myInt16 = Wire.read() << 8 | Wire.read();
  //Mostrar las lecturas separadas por un [tab]

//    Serial.print("a[x y z] g[x y z]:\t");
//    Serial.print(AcX.myInt16); Serial.print("\t");
//    Serial.print(AcY.myInt16); Serial.print("\t");
//    Serial.print(AcZ.myInt16); Serial.print("\t");
//    Serial.print(GyX.myInt16); Serial.print("\t");
//    Serial.print(GyY.myInt16); Serial.print("\t");
//    Serial.println(GyZ.myInt16);
}
