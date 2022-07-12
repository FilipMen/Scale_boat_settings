

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
#include <Servo.h>  //To create PWM signals we need this lybrary
#define Debugging true
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

uint8_t address[][6] = {"BOAT2C", "C2BOAT"};
RF24 radio(9, 10);  //CSN and CE pins

// The sizeof this struct should not exceed 32 bytes
struct RXData {
  byte cLat1;
  byte cLat2;
  byte cLat3;
  byte cLat4;
  char NS;
  byte cLon1;
  byte cLon2;
  byte cLon3;
  byte cLon4;
  char EW;
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

struct TXData {
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
};

RXData receiveData;
TXData sendData;

int timeStamp; // GPS time stamp
//cLat.myfloat = 0.0; // GPS latitud
String NS = ""; // GPS North or Sur
//cLon.myfloat = 0.0; // GPS  Longitud
String EW = ""; // GPS East or Weast

union myFloat {
  uint8_t myByte[4];
  float myfloat;
} cLat, cLon;

union myInt16 {
  uint8_t myByte[2];
  int16_t myInt16;
} AcX, AcY, AcZ, GyX, GyY, GyZ;

// State machine variables
byte state = 0;
bool report = false;
/**************************************************/

void setup()
{
  Serial.begin(115200);
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

}

/**************************************************/

unsigned long lastRecvTime = 0;

//We create the function that will read the data each certain time
void receive_the_data()
{


}

/**************************************************/

void loop()
{
  //Receive the radio data
  state_machine();
  //NRF24_receive();
  //NRF24_transmit();
  //////////This small if will reset the data if signal is lost for 1 sec.
  /////////////////////////////////////////////////////////////////////////
  //  unsigned long now = millis();
  //  if ( now - lastRecvTime > 1000 ) {
  //    // signal lost?
  //    //reset_the_Data();
  //    Serial.println("Signal lost");
  //    //Go up and change the initial values if you want depending on
  //    //your aplications. Put 0 for throttle in case of drones so it won't
  //    //fly away
  //  }
  //
  //delay(100);
  //Creathe the PWM signals
  //  channel_1.writeMicroseconds(ch1_value);
  //  channel_2.writeMicroseconds(ch2_value);
  //  channel_3.writeMicroseconds(ch3_value);
  //  channel_4.writeMicroseconds(ch4_value);
  //  channel_5.writeMicroseconds(ch5_value);
  //  channel_6.writeMicroseconds(ch6_value);
  //  channel_7.writeMicroseconds(ch7_value);


}//Loop end
