void SerializeObject()
{
    String json;
    StaticJsonDocument<300> doc;
    doc["cLat"] = cLat.myInt32;
    doc["cLon"] = cLon.myInt32;
    doc["ax"] = ax.myInt16; // /182
    doc["ay"] = ay.myInt16; // /182
    doc["az"] = az.myInt16; // /182
    
    doc["gx"] = gx.myInt16; // /182
    doc["gy"] = gy.myInt16; // /182
    doc["gz"] = gz.myInt16; // /182
    
    doc["mx"] = mx.myInt16; // /182
    doc["my"] = my.myInt16; // /182
    doc["mz"] = mz.myInt16; // /182
    
    
    doc["bCurr"] = batCurr.myInt16; 
    doc["bVol"] = batVol.myInt16; // *0.1875*3.03763
    serializeJson(doc, json);
    Serial.println(json);
}
