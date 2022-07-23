void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '$') {
#if (true)
      Serial.print(inputString);
#endif
      if (inputString.substring(0, 6) == "$GPGLL") {
        //Serial.print(inputString);
        if (getValue(inputString, ',', 6) == "A") {
          // Get Latitude from the GPS
          cLat.myInt32 = getValue(inputString, ',', 1).toFloat()*100000;
          NS = getValue(inputString, ',', 2);
          if (NS == "S") {
            cLat.myInt32 = -cLat.myInt32;
          }
          // Get Longitud from the GPS
          cLon.myInt32 = getValue(inputString, ',', 3).toFloat()*100000;
          EW = getValue(inputString, ',', 4);
          if (EW == "W") {
            cLon.myInt32 = -cLon.myInt32;
          }
          timeStamp = getValue(inputString, ',', 5).toInt();
        }
        else if (getValue(inputString, ',', 6) == "V") {
#if (false)
          Serial.println("Invalid");
#endif
        }
      }
      // clear the string:
      inputString = "";
    }
  }
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
