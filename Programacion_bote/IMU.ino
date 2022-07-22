/*
    obtener_inclinacion.ino
  Con el código se leen datos de la MPU-6050, este código
  es modificado de la web:
  http://robologs.net/2014/10/15/tutorial-de-arduino-y-mpu-6050/

  Descrito muy bien en el vídeo:
  https://www.youtube.com/watch?v=uN8SYfGwYVw&t=164s

*/
void IMU_read()
{
  if (mpu.update()) {
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 25) {
      print_roll_pitch_yaw();
      prev_ms = millis();
    }
  }
}



void print_roll_pitch_yaw() {
  // Read pitch, roll, yaw and linear accelerations
  pitch.myInt16 = int(mpu.getPitch() * 182);
  roll.myInt16 = int(mpu.getRoll() * 182);
  yaw.myInt16 = int(mpu.getYaw() * 182);
  accX.myInt16 = int(mpu.getLinearAccX() * 182);
  accY.myInt16 = int(mpu.getLinearAccY() * 182);
}
