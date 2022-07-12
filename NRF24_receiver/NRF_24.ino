void NRF24_receive() {
  while ( radio.available() ) {
    radio.read(&receiveData, sizeof(RXData));
    lastRecvTime = millis(); //Here we receive the data
  }
  // This device is a TX node
  cLat.myByte[0] = receiveData.cLat1;
  cLat.myByte[1] = receiveData.cLat2;
  cLat.myByte[2] = receiveData.cLat3;
  cLat.myByte[3] = receiveData.cLat4;
  NS = receiveData.NS;
  cLon.myByte[0] = receiveData.cLon1;
  cLon.myByte[1] = receiveData.cLon2;
  cLon.myByte[2] = receiveData.cLon3;
  cLon.myByte[3] = receiveData.cLon4;
  EW = receiveData.EW;
  AcX.myByte[0] = receiveData.AcX1;
  AcY.myByte[0] = receiveData.AcY1;
  AcZ.myByte[0] = receiveData.AcZ1;
  AcX.myByte[1] = receiveData.AcX2;
  AcY.myByte[1] = receiveData.AcY2;
  AcZ.myByte[1] = receiveData.AcZ2;
  GyX.myByte[0] = receiveData.GyX1;
  GyY.myByte[0] = receiveData.GyY1;
  GyZ.myByte[0] = receiveData.GyZ1;
  GyX.myByte[1] = receiveData.GyX2;
  GyY.myByte[1] = receiveData.GyY2;
  GyZ.myByte[1] = receiveData.GyZ2;
  //Serial.print("a[x y z] g[x y z]:\t");
  //Serial.print(AcX.myInt16); Serial.print("\t");
  //Serial.print(AcY.myInt16); Serial.print("\t");
  //Serial.print(AcZ.myInt16); Serial.print("\t");
  //Serial.print(GyX.myInt16); Serial.print("\t");
  //Serial.print(GyY.myInt16); Serial.print("\t");
  //Serial.println(GyZ.myInt16);
}

void NRF24_transmit() {
  // This device is a TX node
  sendData.ch1 = 50;
  sendData.ch2 = 100;
  sendData.ch3 = 150;
  sendData.ch4 = 200;
  unsigned long start_timer = micros();                    // start the timer
  report = radio.write(&sendData, sizeof(TXData));
  unsigned long end_timer = micros();                      // end the timer
  if (Debugging) {
    if (report) {
      Serial.print(F("Transmission successful! "));          // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.print(end_timer - start_timer);                 // print the timer result
      Serial.println(F(" us. Sent: "));
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    }
  }
}
