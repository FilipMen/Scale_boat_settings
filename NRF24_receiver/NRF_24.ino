<<<<<<< HEAD
=======
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
      ax.myByte[0] = receiveData.ax1;
      ax.myByte[1] = receiveData.ax2;
      ay.myByte[0] = receiveData.ay1;
      ay.myByte[1] = receiveData.ay2;
      az.myByte[0] = receiveData.az1;
      az.myByte[1] = receiveData.az2;
      gx.myByte[0] = receiveData.gx1;
      gx.myByte[1] = receiveData.gx2;
      gy.myByte[0] = receiveData.gy1;
      gy.myByte[1] = receiveData.gy2;
      gz.myByte[0] = receiveData.gz1;
      gz.myByte[1] = receiveData.gz2;
      mx.myByte[0] = receiveData.mx1;
      mx.myByte[1] = receiveData.mx2;
      my.myByte[0] = receiveData.my1;
      my.myByte[1] = receiveData.my2;
      mz.myByte[0] = receiveData.mz1;
      mz.myByte[1] = receiveData.mz2;
      
      batCurr.myByte[0] = receiveData.batCurr1;
      batCurr.myByte[1] = receiveData.batCurr2;
      batVol.myByte[0] = receiveData.batVol1;
      batVol.myByte[1] = receiveData.batVol2;
      SerializeObject();
    }
  }

}

>>>>>>> parent of 02768ef (IMU_ok)
void NRF24_transmit() {
  sendData.ch1 = rudder_angle;
  sendData.ch2 = PMW_motor1;
  sendData.ch3 = PMW_motor2;
  sendData.Mode = controlMode;
<<<<<<< HEAD
  radio.stopListening();
  unsigned long time = micros();                          // Record the current microsecond count
  if (radio.write(&sendData, sizeof(TXData))) {
    if (!radio.available()) {                           // If nothing in the buffer, we got an ack but it is blank
      Serial.print(F("Got blank response. round-trip delay: "));
      Serial.print(micros() - time);
      Serial.println(F(" microseconds"));
    }
    else {
      NRF24_receive();
    }
  }
  else {
    Serial.println(F("Sending failed."));
=======
  radio.stopListening(); 
  unsigned long start_timer = micros();                    // start the timer
  for (int i = 0; i < NUMSEND; i++) {
    report = radio.write(&sendData, sizeof(TXData));
  }
  unsigned long end_timer = micros();                      // end the timer
#if (false)
  if (report) {
    Serial.print(F("Transmission successful! "));          // payload was delivered
    Serial.print(F("Time to transmit = "));
    Serial.print(end_timer - start_timer);                 // print the timer result
    Serial.println(F(" us. Sent: "));
  } else {
    Serial.println(F("Transmission failed or timed out")); // payload was not delivered
>>>>>>> parent of 02768ef (IMU_ok)
  }
  radio.startListening();
}

void NRF24_receive() {
  while ( radio.available() ) {
    radio.read(&receiveData, sizeof(RXData));
    // Verify the message
    cLat.myByte[0] = receiveData.cLat1;
    cLat.myByte[1] = receiveData.cLat2;
    cLat.myByte[2] = receiveData.cLat3;
    cLat.myByte[3] = receiveData.cLat4;
    cLon.myByte[0] = receiveData.cLon1;
    cLon.myByte[1] = receiveData.cLon2;
    cLon.myByte[2] = receiveData.cLon3;
    cLon.myByte[3] = receiveData.cLon4;

    ax.myByte[0] = receiveData.ax1;
    ax.myByte[1] = receiveData.ax2;
    ay.myByte[0] = receiveData.ay1;
    ay.myByte[1] = receiveData.ay2;
    az.myByte[0] = receiveData.az1;
    az.myByte[1] = receiveData.az2;

    gx.myByte[0] = receiveData.gx1;
    gx.myByte[1] = receiveData.gx2;
    gy.myByte[0] = receiveData.gy1;
    gy.myByte[1] = receiveData.gy2;
    gz.myByte[0] = receiveData.gz1;
    gz.myByte[1] = receiveData.gz2;

    mx.myByte[0] = receiveData.mx1;
    mx.myByte[1] = receiveData.mx2;
    my.myByte[0] = receiveData.my1;
    my.myByte[1] = receiveData.my2;
    mz.myByte[0] = receiveData.mz1;
    mz.myByte[1] = receiveData.mz2;

    batCurr.myByte[0] = receiveData.batCurr1;
    batCurr.myByte[1] = receiveData.batCurr2;
    batVol.myByte[0] = receiveData.batVol1;
    batVol.myByte[1] = receiveData.batVol2;
    SerializeObject();
  }

}
