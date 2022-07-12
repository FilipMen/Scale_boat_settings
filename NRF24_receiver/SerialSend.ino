void Serial_Send() {
  String json;
  StaticJsonDocument<300> doc;
  doc["AcX"] = AcX.myInt16;
  doc["AcY"] = AcY.myInt16;
  doc["AcZ"] = AcZ.myInt16;
  doc["GyX"] = GyX.myInt16;
  doc["GyY"] = GyY.myInt16;
  doc["GyZ"] = GyZ.myInt16;
  doc["cLat"] = cLat.myfloat;
  doc["NS"] = NS;
  doc["cLon"] = cLon.myfloat;
  doc["EW"] = EW;
  serializeJson(doc, json);
  Serial.println(json);
}
