void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      Serial.print(inputString);
      if (inputString.substring(0, 6) == "$GPGLL") {
        Serial.print(inputString);
        if (getValue(inputString, ',', 6) == "A") {
          cLat.myfloat = getValue(inputString, ',', 1).toFloat();
          NS = getValue(inputString, ',', 2);
          if (NS == "S"){
            cLat.myfloat = -cLat.myfloat;
          }
          
          cLon.myfloat = getValue(inputString, ',', 3).toFloat();
          EW = getValue(inputString, ',', 4);
          timeStamp = getValue(inputString, ',', 5).toInt();
        }
        if (getValue(inputString, ',', 6) == "V") {
          Serial.println("Invalid");
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
