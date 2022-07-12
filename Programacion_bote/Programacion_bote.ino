// ================================================================
// ===                    Libraries                             ===
// ================================================================
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "printf.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// ================================================================
// ===                    Variables IMU                         ===
// ================================================================
//Direccion I2C de la IMU
#define MPU 0x68
#define Debugging true
//MPU-6050 da los valores en enteros de 16 bits
//Valores RAW
//uint8_t AcX1, AcY1, AcZ1, GyX1, GyY1, GyZ1, AcX2, AcY2, AcZ2, GyX2, GyY2, GyZ2;

// ================================================================
// ===                    Variables GPS                         ===
// ================================================================
union myFloat {
  uint8_t myByte[4];
  float myfloat;
} cLat, cLon;

union myInt16 {
  uint8_t myByte[2];
  int16_t myInt16;
} AcX, AcY, AcZ, GyX, GyY, GyZ;

String inputString = "";         // a String to hold incoming data
int timeStamp; // GPS time stamp
//cLat.myfloat = 0.0; // GPS latitud
String NS = ""; // GPS North or Sur
//cLon.myfloat = 0.0; // GPS  Longitud
String EW = ""; // GPS East or Weast


// ================================================================
// ===                    Variables NRF24                       ===
// ================================================================
// Addresses be used for the pair
uint8_t address[][6] = {"BOAT2C", "C2BOAT"};
// Instantiate an object for the nRF24L01 transceiver
RF24 radio(9, 10);  //Set CE and CSN pins
// To use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role

// The sizeof this struct should not exceed 32 bytes
struct TXData {
  byte cLat1;
  byte cLat2;
  byte cLat3;
  byte cLat4;
  byte NS;
  byte cLon1;
  byte cLon2;
  byte cLon3;
  byte cLon4;
  byte EW;
  byte AcX1;
  byte AcY1;
  byte AcZ1;
  byte GyX1;
  byte GyY1;
  byte GyZ1;
  byte AcX2;
  byte AcY2;
  byte AcZ2;
  byte GyX2;
  byte GyY2;
  byte GyZ2;
};

struct RXData {
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
};

// ================================================================
// ===                    Variables ADS1115                     ===
// ================================================================
#include "ADS1X15.h"
ADS1115 ADS(0x48);

// State machine variables
bool state = 0;
bool report = false;

//Create a variable with the structure above and name it sent_data
TXData sendData;
RXData receiveData;

// Timer
unsigned long SampleT = 0;

void setup() {

  Serial.begin(9600);

  // ================================================================
  // ===                    Variables GPS SETUP                   ===
  // ================================================================
  NS.reserve(1);
  EW.reserve(1);
  // ================================================================
  // ===                    Variables IMU SETUP                   ===
  // ================================================================
  //IMU_calibration();
  Wire.begin(); // D2(GPIO4)=SDA / D1(GPIO5)=SCL
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  // ================================================================
  // ===                    Variables NRF24 SETUP                 ===
  // ================================================================
  if (radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }
  else {
    Serial.println(F("Radio correct!!"));
  }
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(TXData));
  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[0]);     // always uses pipe 0
  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[1]); // using pipe 1

  //radio.startListening();


  // ================================================================
  // ===                    Variables ADS1115 SETUP               ===
  // ================================================================
  ADS.begin();
  ADS.setWireClock(400000);
  
  // ================================================================
  // ===                    Timer1 interrupt                      ===
  // ================================================================
  //  cli();//stop interrupts
  //  //set timer1 interrupt at 1Hz
  //  TCCR1A = 0;// set entire TCCR1A register to 0
  //  TCCR1B = 0;// same for TCCR1B
  //  TCNT1  = 0;//initialize counter value to 0
  //  // set compare match register for 1hz increments
  //  OCR1A = 6249;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  //  // turn on CTC mode
  //  TCCR1B |= (1 << WGM12);
  //  // Set CS10 CS11 and CS12 bits
  //  //TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10); // No prescaling
  //  //TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10); // 8 prescaler
  //  //TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10); // 64 prescaler
  //  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10); // 256 prescaler
  //  //TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10); // 1024 prescaler
  //  // enable timer compare interrupt
  //  TIMSK1 |= (1 << OCIE1A);
  //  sei();//allow interrupts
  SampleT = millis();
}

void loop() {
  if (millis() - SampleT > 20) {
    SampleT = millis();
    IMU_read();
    State_machine();
  }
}
