void NRF24_receive() {
  while ( radio.available() ) {
    radio.read(&receiveData, sizeof(RXData));
    // Verify the message
    numMessageRX.myByte[0] = receiveData.numMessage1;
    numMessageRX.myByte[1] = receiveData.numMessage2;
    if (numMessageRX1 != numMessageRX.myInt16) {
      if(numMessageRX.myInt16 - numMessageRX1 >1){
        Serial.println("¡¡¡¡ MESSAGE LOST !!!!!");
      }
      numMessageRX1 = numMessageRX.myInt16;
      cLat.myByte[0] = receiveData.cLat1;
      cLat.myByte[1] = receiveData.cLat2;
      cLat.myByte[2] = receiveData.cLat3;
      cLat.myByte[3] = receiveData.cLat4;
      cLon.myByte[0] = receiveData.cLon1;
      cLon.myByte[1] = receiveData.cLon2;
      cLon.myByte[2] = receiveData.cLon3;
      cLon.myByte[3] = receiveData.cLon4;
      yaw.myByte[0] = receiveData.yaw1;
      yaw.myByte[1] = receiveData.yaw2;
      roll.myByte[0] = receiveData.roll1;
      roll.myByte[1] = receiveData.roll2;
      pitch.myByte[0] = receiveData.pitch1;
      pitch.myByte[1] = receiveData.pitch2;
      accX.myByte[0] = receiveData.accX1;
      accX.myByte[1] = receiveData.accX2;
      accY.myByte[0] = receiveData.accY1;
      accY.myByte[1] = receiveData.accY2;
      batCurr.myByte[0] = receiveData.batCurr1;
      batCurr.myByte[1] = receiveData.batCurr2;
      batVol.myByte[0] = receiveData.batVol1;
      batVol.myByte[1] = receiveData.batVol2;
      SerializeObject();
    }
  }

}

void NRF24_transmit() {
  numMessageTX.myInt16 ++;
  // This device is a TX node
  sendData.numMessage1 = numMessageTX.myByte[0];
  sendData.numMessage2 = numMessageTX.myByte[0];
  sendData.ch1 = rudder_angle;
  sendData.ch2 = PMW_motor1;
  sendData.ch3 = PMW_motor2;
  sendData.Mode = controlMode;
  radio.stopListening(); 
  unsigned long start_timer = micros();                    // start the timer
  for (int i = 0; i < NUMSEND; i++) {
    report = radio.write(&sendData, sizeof(TXData));
  }
  unsigned long end_timer = micros();                      // end the timer
#if (Debugging)
  if (report) {
    Serial.print(F("Transmission successful! "));          // payload was delivered
    Serial.print(F("Time to transmit = "));
    Serial.print(end_timer - start_timer);                 // print the timer result
    Serial.println(F(" us. Sent: "));
  } else {
    Serial.println(F("Transmission failed or timed out")); // payload was not delivered
  }
#endif
  radio.startListening();
}
