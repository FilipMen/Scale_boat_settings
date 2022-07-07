ISR(TIMER1_COMPA_vect) { //timer1 interrupt
  if (state == 0){
    IMU_read();
    NRF24_transmit();
  }
}
