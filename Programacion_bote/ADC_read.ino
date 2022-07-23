void ADC_read() {
  ADS.setGain(2);
  batCurr.myInt16 = ADS.readADC_Differential_0_1();
  ADS.setGain(0);
  int16_t val_2 = ADS.readADC(2);
  float f = ADS.toVoltage(1);  // voltage factor
  batVol = int(val_2*f*3.6935*10);
  
#if (false)
  Serial.print(batCurr.myInt16*0.0625*0.0182-0.8094);
  Serial.print('\t');
  Serial.println(batVol);
#endif
}
