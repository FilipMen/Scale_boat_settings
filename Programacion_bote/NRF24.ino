void NRF24_transmit() {
  // This device is a TX node
  sendData.cLat1 = cLat.myByte[0];
  sendData.cLat2 = cLat.myByte[1];
  sendData.cLat3 = cLat.myByte[2];
  sendData.cLat4 = cLat.myByte[3];
  sendData.NS = NS[0];
  sendData.cLon1 = cLon.myByte[0];
  sendData.cLon2 = cLon.myByte[1];
  sendData.cLon3 = cLon.myByte[2];
  sendData.cLon4 = cLon.myByte[3];
  sendData.EW = EW[0];
  sendData.AcX1 = AcX.myByte[0];
  sendData.AcY1 = AcY.myByte[0];
  sendData.AcZ1 = AcZ.myByte[0];
  sendData.GyX1 = GyX.myByte[0];
  sendData.GyY1 = GyY.myByte[0];
  sendData.GyZ1 = GyZ.myByte[0];
  sendData.AcX2 = AcX.myByte[1];
  sendData.AcY2 = AcY.myByte[1];
  sendData.AcZ2 = AcZ.myByte[1];
  sendData.GyX2 = GyX.myByte[1];
  sendData.GyY2 = GyY.myByte[1];
  sendData.GyZ2 = GyZ.myByte[1];

  unsigned long start_timer = micros();                    // start the timer
  report = radio.write(&sendData, sizeof(TXData));
  unsigned long end_timer = micros();                      // end the timer
  if (Debugging) {
    if (report) {
      Serial.print(F("Transmission successful! "));          // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.print(end_timer - start_timer);                 // print the timer result
      Serial.println(F(" us. "));
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    }
  }
}
void NRF24_receive() {
  if (radio.available()) {
    while ( radio.available() ) {
      radio.read(&receiveData, sizeof(RXData));
      //lastRecvTime = millis(); //Here we receive the data
    }
    Serial.println(receiveData.ch2);
  }
}
