#define Tau 1
void Control_boat() {
  //byte filter_PWM = LowPassFilter(PMW_motor1, PMW_motor1_1, 1, DelayTime / 1000000.0, Tau);
  //PMW_motor1_1 = filter_PWM;
  //int us_motor = 1000 + filter_PWM / 255.0 * 1000;

  //filter_PWM = LowPassFilter(PMW_motor2, PMW_motor2_1, 1, DelayTime / 1000000.0, Tau);
  //PMW_motor2_1 = filter_PWM;
  //us_motor = 1000 + filter_PWM / 255.0 * 1000;

  String json;
  StaticJsonDocument<30> doc;
  doc["p1"] = rudder_angle;
  doc["p2"] = PMW_motor1;
  doc["p3"] = PMW_motor2;
  serializeJson(doc, json);

  Serial2.println(json);
#if (Debugging)
  Serial.println(json);
#endif

}

byte LowPassFilter(float x, float y1, float K, float Ts, float tau) {
  // First order low pass filter
  // x: Input signal to filter
  // y: Output of the filter
  // y1: Output of the filter in time y[k-1]
  // K: Gain of the filter
  // Ts: Sample time
  // tau: Time constant, 1/tau is the cut frecuency of the filter
  return (tau * y1 + Ts * K * x) / (tau + Ts);
}
