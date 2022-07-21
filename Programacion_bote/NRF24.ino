void NRF24_transmit() {
  numMessageTX.myInt16 ++;
  // This device is a TX node
  sendData.numMessage1 = numMessageTX.myByte[0];
  sendData.numMessage2 = numMessageTX.myByte[1];
  sendData.cLat1 = cLat.myByte[0];
  sendData.cLat2 = cLat.myByte[1];
  sendData.cLat3 = cLat.myByte[2];
  sendData.cLat4 = cLat.myByte[3];
  sendData.cLon1 = cLon.myByte[0];
  sendData.cLon2 = cLon.myByte[1];
  sendData.cLon3 = cLon.myByte[2];
  sendData.cLon4 = cLon.myByte[3];
  sendData.yaw1 = yaw.myByte[0];
  sendData.yaw2 = yaw.myByte[1];
  sendData.roll1 = roll.myByte[0];
  sendData.roll2 = roll.myByte[1];
  sendData.pitch1 = pitch.myByte[0];
  sendData.pitch2 = pitch.myByte[1];
  sendData.accX1 = accX.myByte[0];
  sendData.accX2 = accX.myByte[1];
  sendData.accY1 = accY.myByte[0];
  sendData.accY2 = accY.myByte[1];
  sendData.batCurr1 = batCurr.myByte[0];
  sendData.batCurr2 = batCurr.myByte[1];
  sendData.batVol1 = batVol.myByte[0];
  sendData.batVol2 = batVol.myByte[1];
  unsigned long start_timer = micros();                    // start the timer
  radio.stopListening();
  for (int i = 0; i < NUMSEND; i++) {
    report = radio.write(&sendData, sizeof(TXData));
  }
  unsigned long end_timer = micros();                      // end the timer
#if (Debugging)
  if (report) {
    Serial.print(F("Transmission successful! "));          // payload was delivered
    Serial.print(F("Time to transmit = "));
    Serial.print(end_timer - start_timer);                 // print the timer result
    Serial.println(F(" us. "));
  } else {
    Serial.println(F("Transmission failed or timed out")); // payload was not delivered
  }
#endif
  radio.startListening();
  //SerializeObject();
}


void NRF24_receive() {
  while ( radio.available() ) {
    radio.read(&receiveData, sizeof(RXData));
    // Verify the message
    numMessageRX.myByte[0] = receiveData.numMessage1;
    numMessageRX.myByte[1] = receiveData.numMessage2;
    if (numMessageRX1 != numMessageRX.myInt16) {
      countSignal = 0;
      numMessageRX1 = numMessageRX.myInt16;
      rudder_angle = receiveData.ch1;
      PMW_motor1 = receiveData.ch2;
      PMW_motor2 = receiveData.ch3;
      controlMode = receiveData.Mode;
      
#if (!Debugging)
      String json;
      StaticJsonDocument<300> doc;
      doc["1"] = rudder_angle;
      doc["2"] = PMW_motor1;
      doc["3"] = PMW_motor2;
      doc["m"] = controlMode;
      serializeJson(doc, json);
      Serial.println(json);
#endif
      if (controlMode == 10) { // Disable
        digitalWrite(Selector, HIGH); // Selector in Radio mode
        digitalWrite(EnableBoat, HIGH); // Boat is disabled
        colorWipe(strip1.Color(0,   0,   255), 0);    // Blue
      }
      else if (controlMode == 20) { // Radio control - Telemetry on
        digitalWrite(Selector, HIGH); // Selector in Radio mode
        digitalWrite(EnableBoat, LOW); // Boat is enable
        colorWipe(strip1.Color(255,   0,   255), 0);    // Purple
      }
      else if (controlMode == 30) { // Computer control mode
        digitalWrite(Selector, LOW); // Selector in computer mode
        digitalWrite(EnableBoat, LOW); // Boat is enable
        colorWipe(strip1.Color(0,   255,   0), 0);    // Green
        Control_boat();
      }
      else{
        colorWipe(strip1.Color(255,   255,   255), 0);    // Green
      }
      ADC_read();
      delay(15);
      NRF24_transmit();
#if(Debugging)
      SerializeObject();
#endif
    }
  }
}
