// ================================================================
// ===                    Variables GPS                         ===
// ================================================================
union myFloat {
  uint8_t mybyte[4];
  float myFloat;
} cLat, cLon;

String inputString = "";         // a String to hold incoming data
int timeStamp; // GPS time stamp
//cLat.myFloat = 0.0; // GPS latitud
String NS = ""; // GPS North or Sur
//cLon.myFloat = 0.0; // GPS  Longitud
String EW = ""; // GPS East or Weast


void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

}

void loop() {
}

void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      Serial.print(inputString);
      if (inputString.substring(0, 6) == "$GPGLL") {
        if (getValue(inputString, ',', 6) == "A") {
          // Get Latitude from the GPS
          cLat.myFloat = getValue(inputString, ',', 1).toFloat();
          NS = getValue(inputString, ',', 2);
          if (NS == "S") {
            cLat.myFloat = -cLat.myFloat;
          }
          // Get Longitud from the GPS
          cLon.myFloat = getValue(inputString, ',', 3).toFloat();
          EW = getValue(inputString, ',', 4);
          if (EW == "W") {
            cLon.myFloat = -cLon.myFloat;
          }
          Serial.print("Latitude: ");
          Serial.print(cLat.myFloat);
          Serial.print("\tLongitud: ");
          Serial.print(cLon.myFloat);
          timeStamp = getValue(inputString, ',', 5).toInt();
        }
        else if (getValue(inputString, ',', 6) == "V") {
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
