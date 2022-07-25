void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '$') {
      if (inputString.substring(0, 5) == "GPRMC") {
        //Serial.print(inputString);
        if (getValue(inputString, ',', 2) == "A") {
          // Get Latitude from the GPS
          String auxiliar = getValue(inputString, ',', 3);
          cLat.myInt32 = (auxiliar.substring(0, 4) + auxiliar.substring(5, 10)).toInt();
          if (getValue(inputString, ',', 4) == "S") cLat.myInt32 = -cLat.myInt32;
          // Get Longitud from the GPS
          auxiliar = getValue(inputString, ',', 5);
          cLon.myInt32 = (auxiliar.substring(0, 5) + auxiliar.substring(6, 11)).toInt();
          if (getValue(inputString, ',', 6) == "W") cLon.myInt32 = -cLon.myInt32;
          velocity.myInt16 = getValue(inputString, ',', 7).toFloat()*1000;
#if (false)
          Serial.print(cLat.myInt32);
          Serial.print('\t');
          Serial.println(cLon.myInt32);
#endif
        }
      }
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
