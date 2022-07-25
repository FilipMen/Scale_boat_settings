void ADC_read(){
  ADS.setGain(2);
  batCurr.myInt16 = ADS.readADC_Differential_0_1();
  ADS.setGain(0);
  batVol.myInt16 = ADS.readADC(2);
}
