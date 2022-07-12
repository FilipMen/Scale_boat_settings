void State_machine() {
  NRF24_transmit();
  //radio.startListening();                                    // Now, continue listening

  unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

  //while ( ! radio.available() ) {                            // While nothing is received
  //  if (micros() - started_waiting_at > 300000 ) {           // If waited longer than 200ms, indicate timeout and exit while loop
  //    timeout = true;
  //    break;
  //  }
  //}

  //if ( timeout ) {                                            // Describe the results
  //    Serial.println(F("Failed, response timed out."));
  //  } else {
  //    radio.read(&receiveData, sizeof(RXData) );
  //    unsigned long time = micros();
  //    Serial.println(receiveData.ch1);
  //  }
  //radio.stopListening();                                    // First, stop listening so we can talk.
  //byte ack = 99;
  //report = radio.write(&ack, sizeof(byte));
}
