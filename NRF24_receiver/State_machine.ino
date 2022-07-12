void state_machine() {
  if ( radio.available()) {
    // Variable for the received timestamp
    NRF24_receive();
    Serial_Send();
    // This device is a TX node
    sendData.ch1 = 50;
    sendData.ch2 = 100;
    sendData.ch3 = 150;
    sendData.ch4 = 200;
    byte cont = 0;
    //radio.stopListening();
    //long time1 = millis();
    //while (cont<255) {
    //      cont++;
    //      report = radio.write(&sendData, sizeof(TXData));
    //    }
    //Serial.println((millis() - time1));
    //radio.startListening();
  }
}
