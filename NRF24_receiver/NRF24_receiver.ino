

/* Receiver code for the Arduino Radio control with PWM output
   Install the NRF24 library to your IDE
   Upload this code to the Arduino UNO, NANO, Pro mini (5V,16MHz)
   Connect a NRF24 module to it:

    Module // Arduino UNO,NANO

    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12

  This code receive 7 channels and create a PWM output for each one on D2, D3, D4, D5, D6, D7and D8
  Please, like share and subscribe : https://www.youtube.com/c/ELECTRONOOBS
*/


#include <SPI.h>
#include <nRF24L01.h>
#include "printf.h"
#include <RF24.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>


// ================================================================
// ===                    Variables                             ===
// ================================================================
#define Debugging false
unsigned long sampleT;
#define DelayTime 50000
#define NUMSEND 15


union myInt32 {
  uint8_t myByte[4];
  int32_t myInt32;
} cLat, cLon;

union myInt16 {
  uint8_t myByte[2];
  int16_t myInt16;
} numMessageRX, numMessageTX;

uint8_t address[][6] = {"BOAT2C", "C2BOAT"};
RF24 radio(9, 10);  //CSN and CE pins

// The sizeof this struct should not exceed 32 bytes
struct RXData {
  byte numMessage1;
  byte numMessage2;
  byte cLat1;
  byte cLat2;
  byte cLat3;
  byte cLat4;
  byte cLon1;
  byte cLon2;
  byte cLon3;
  byte cLon4;
  byte ax1;
  byte ax2;
  byte ay1;
  byte ay2;
  byte az1;
  byte az2;
  byte gx1;
  byte gx2;
  byte gy1;
  byte gy2;
  byte gz1;
  byte gz2;
  byte mx1;
  byte mx2;
  byte my1;
  byte my2;
  byte mz1;
  byte mz2;
  byte batCurr1;
  byte batCurr2;
  byte batVol1;
  byte batVol2;
};
struct TXData {
  byte numMessage1;
  byte numMessage2;
  byte ch1;
  byte ch2;
  byte ch3;
  byte Mode;
};

RXData receiveData;
TXData sendData;
int16_t numMessageRX1 = 0;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool signalLost;
byte countSignal = 0;
#define DelayTime 50000
// ================================================================
// ===                    Variables GPS                         ===
// ================================================================
//cLat.myfloat = 0.0; // GPS latitud
String NS = ""; // GPS North or Sur
//cLon.myfloat = 0.0; // GPS  Longitud
String EW = ""; // GPS East or Weast

// ================================================================
// ===                    Variables IMU                         ===
// ================================================================
//Direccion I2C de la IMU 9250
myInt16 ax,ay,az,gx,gy,gz,mx,my,mz;
byte ax1 = 0;
byte ax2 = 0;
byte ay1 = 0;
byte ay2 = 0;
byte az1 = 0;
byte az2 = 0;
byte gx1 = 0;
byte gx2 = 0;
byte gy1 = 0;
byte gy2 = 0;
byte gz1 = 0;
byte gz2 = 0;
byte mx1 = 0;
byte mx2 = 0;
byte my1 = 0;
byte my2 = 0;
byte mz1 = 0;
byte mz2 = 0;
// ================================================================
// ===                    Variables ADS1115                     ===
// ================================================================
myInt16 batCurr;
myInt16 batVol;


byte PMW_motor1 = 0;
byte PMW_motor2 = 0;
byte rudder_angle = 0;
byte controlMode = 0;
// State machine variables
byte state = 0;
bool report = false;
/**************************************************/

void setup()
{
  Serial.begin(115200);
  inputString.reserve(200);
  //Once again, begin and radio configuration
  if (radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }
  else {
    Serial.println(F("Radio correct!!"));
  }
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(RXData));
  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[1]);     // always uses pipe 0
  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[0]); // using pipe 1
  //We start the radio comunication
  radio.startListening();
  sampleT = micros();
}

unsigned long lastRecvTime = 0;


void loop()
{
    if (micros() - sampleT > DelayTime) {
      sampleT = micros();
      NRF24_transmit();
    }
  //Receive the radio data
  NRF24_receive();
}//Loop end
