void NRF24_transmit() {
  numMessageTX ++;
  // This device is a TX node
  sendData.numMessage = numMessageTX;
  sendData.cLat1 = cLat.myByte[0];
  sendData.cLat2 = cLat.myByte[1];
  sendData.cLat3 = cLat.myByte[2];
  sendData.cLat4 = cLat.myByte[3];
  sendData.cLon1 = cLon.myByte[0];
  sendData.cLon2 = cLon.myByte[1];
  sendData.cLon3 = cLon.myByte[2];
  sendData.cLon4 = cLon.myByte[3];

  sendData.ax1 = ax.myByte[0];
  sendData.ax2 = ax.myByte[1];
  sendData.ay1 = ay.myByte[0];
  sendData.ay2 = ay.myByte[1];
  sendData.az1 = az.myByte[0];
  sendData.az2 = az.myByte[1];

  sendData.gx1 = gx.myByte[0];
  sendData.gx2 = gx.myByte[1];
  sendData.gy1 = gy.myByte[0];
  sendData.gy2 = gy.myByte[1];
  sendData.gz1 = gz.myByte[0];
  sendData.gz2 = gz.myByte[1];

  sendData.mx1 = mx.myByte[0];
  sendData.mx2 = mx.myByte[1];
  sendData.my1 = my.myByte[0];
  sendData.my2 = my.myByte[1];
  sendData.mz1 = mz.myByte[0];
  sendData.mz2 = mz.myByte[1];


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
    numMessageRX = receiveData.numMessage;
    if (numMessageRX1 != numMessageRX) {
      countSignal = 0;
      numMessageRX1 = numMessageRX;
      rudder_angle = receiveData.ch1;
      PMW_motor1 = receiveData.ch2;
      PMW_motor2 = receiveData.ch3;
      controlMode = receiveData.Mode;
      
#if (false)
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
      IMU_read();
      delay(15);
      NRF24_transmit();
#if(Debugging)
      SerializeObject();
#endif
    }
  }
}
