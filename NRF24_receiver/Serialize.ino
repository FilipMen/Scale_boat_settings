void SerializeObject()
{
    String json;
    StaticJsonDocument<300> doc;
    doc["lat"] = cLat.myInt32;
    doc["lon"] = cLon.myInt32;
    doc["vel"] = velocity.myInt16;
    doc["ax"] = ax.myInt16; // 
    doc["ay"] = ay.myInt16; // 
    doc["az"] = az.myInt16; // 
    
    doc["gx"] = gx.myInt16; // 
    doc["gy"] = gy.myInt16; // 
    doc["gz"] = gz.myInt16; // 
    
    doc["mx"] = mx.myInt16; // 
    doc["my"] = my.myInt16; // 
    doc["mz"] = mz.myInt16; // 
      
    doc["bC"] = batCurr.myInt16; 
    doc["bV"] = batVol; // /10
    serializeJson(doc, json);
    Serial.println(json);
}
