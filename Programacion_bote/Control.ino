#define Tau 1
void Control_boat() {
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
