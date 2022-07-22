void SerializeObject()
{
    String json;
    StaticJsonDocument<300> doc;
    doc["cLat"] = cLat.myInt32;
    doc["cLon"] = cLon.myInt32;
    doc["yaw"] = yaw.myInt16/182.0;
    doc["roll"] = roll.myInt16/182.0;
    doc["pitch"] = pitch.myInt16/182.0;
    doc["accX"] = accX.myInt16/182.0;
    doc["accY"] = accY.myInt16/182.0;
    doc["bCurr"] = batCurr.myInt16;
    doc["bVol"] = batVol.myInt16*0.1875*3.03763;
    serializeJson(doc, json);
    Serial.println(json);
}
