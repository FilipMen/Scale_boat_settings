void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      DeserializeObject(inputString);
      String json;
      StaticJsonDocument<300> doc;
      doc["1"] = rudder_angle;
      doc["2"] = PMW_motor1;
      doc["3"] = PMW_motor2;
      doc["m"] = controlMode;
      serializeJson(doc, json);
      Serial.println(json);
      NRF24_transmit();
      inputString = "";
    }
  }
}

void DeserializeObject(String json)
{
  StaticJsonDocument<50> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    return;
  }
  rudder_angle = doc["1"];
  PMW_motor1 = doc["2"];
  PMW_motor2 = doc["3"];
  controlMode = doc["m"];
}
