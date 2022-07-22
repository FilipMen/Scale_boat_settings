void NRF24_receive() {
  byte pipeNo;
  while ( radio.available(&pipeNo) ) {
    radio.read(&receiveData, sizeof(RXData));
    radio.writeAckPayload(pipeNo, &sendData, sizeof(TXData));
    Serial.println("Received");
    numMessageRX1 = numMessageRX.myInt16;
    rudder_angle = receiveData.ch1;
    PMW_motor1 = receiveData.ch2;
    PMW_motor2 = receiveData.ch3;
    controlMode = receiveData.Mode;
    Update_variables();
  }
}

void Update_variables() {
  countSignal = 0;
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
  else {
    colorWipe(strip1.Color(255,   255,   255), 0);    // Green
  }
  ADC_read();
  IMU_read();
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
  //SerializeObject();
}
