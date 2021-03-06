

// ================================================================
// ===                    Libraries                             ===
// ================================================================
#include "I2Cdev.h"
#include "MPU9250.h"
#include "Wire.h"
#include "printf.h"
#include "ADS1X15.h"
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
// ================================================================
// ===                    Variables                             ===
// ================================================================
#define Debugging false
void colorWipe(uint32_t color, int wait);
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);
union myInt32 {
  uint8_t myByte[4];
  int32_t myInt32;
} cLat, cLon;

union myInt16 {
  uint8_t myByte[2];
  int16_t myInt16;
} velocity;

long sampleT;
bool signalLost;
byte countSignal = 0;
byte numMessageRX, numMessageTX;
#define DelayTime 100000
#define NUMSEND 20
#define NUMLOST 20
// ================================================================
// ===                    Variables IMU                         ===
// ================================================================

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

myInt16 ax, ay, az, gx, gy, gz, mx, my, mz;



// ================================================================
// ===                    Variables GPS                         ===
// ================================================================
String inputString = "";         // a String to hold incoming data

// ================================================================
// ===                    Variables ADS1115                     ===
// ================================================================
ADS1115 ADS(0x48);
myInt16 batCurr;
byte batVol;

// ================================================================
// ===                    Variables WX2812                      ===
// ================================================================
Adafruit_NeoPixel strip1(12, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(12, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(12, 11, NEO_GRB + NEO_KHZ800);

// ================================================================
// ===                    Variables NRF24                       ===
// ================================================================
// Addresses be used for the pair
uint8_t address[][6] = {"BOAT2C", "C2BOAT"};
// Instantiate an object for the nRF24L01 transceiver
RF24 radio(49, 53);  //Set CE and CSN pins

// The sizeof this struct should not exceed 32 bytes
struct TXData {
  byte numMessage;
  byte cLat1;
  byte cLat2;
  byte cLat3;
  byte cLat4;
  byte cLon1;
  byte cLon2;
  byte cLon3;
  byte cLon4;
  byte vel1;
  byte vel2;
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
  byte batVol;
};

struct RXData {
  byte numMessage;
  byte ch1;
  byte ch2;
  byte ch3;
  byte Mode;
};

//Create a variable with the structure above and name it sent_data
TXData sendData;
RXData receiveData;
byte numMessageRX1 = 0;

// ================================================================
// ===                    Variables control                     ===
// ================================================================
#define Selector 5 // Pin to select if control or PC mode
#define EnableBoat 8 // Pin to Enable/Disable the output

byte PMW_motor1 = 0;
byte PMW_motor2 = 0;
byte rudder_angle = 0;
byte controlMode = 0;


// ================================================================
// ===                        SETUP                             ===
// ================================================================
void setup() {
  // ================================================================
  // ===                    Pin Setup                             ===
  // ================================================================
  pinMode(Selector, OUTPUT);
  pinMode(EnableBoat, OUTPUT);
  digitalWrite(EnableBoat, HIGH);

  // ================================================================
  // ===                    Variables WX2812 SETUP                ===
  // ================================================================
  strip1.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip1.show();  // Initialize all pixels to 'off'
  strip2.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip2.show();  // Initialize all pixels to 'off'
  strip3.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip3.show();  // Initialize all pixels to 'off'
  colorWipe(strip1.Color(255,   0,   0), 0);    // Red

  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  // ================================================================
  // ===                    Variables GPS SETUP                   ===
  // ================================================================
  Serial1.begin(9600);
  cLat.myInt32 = 0; // GPS latitud
  cLon.myInt32 = 0; // GPS  Longitud
  velocity.myInt16 = 0;
  // ================================================================
  // ===                    Variables IMU SETUP                   ===
  // ================================================================
  // Set accelerometers low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS, 29, 0x06);
  // Set gyroscope low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS, 26, 0x06);
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_1000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_4_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);

  // Request continuous magnetometer measurements in 16 bits
  I2CwriteByte(MAG_ADDRESS, 0x0A, 0x16);

  //Serial.println("MPU connection ok.");

  delay(1000);

  // ================================================================
  // ===                    Variables ADC SETUP                   ===
  // ================================================================
  ADS.begin();
  ADS.setGain(0);

  // ================================================================
  // ===                    Variables NRF24 SETUP                 ===
  // ================================================================
  if (radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }
  else {
    //Serial.println(F("Radio correct!!"));
    colorWipe(strip1.Color(0,   255,   0), 0);    // Red
  }
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(TXData));
  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[0]);     // always uses pipe 0
  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[1]); // using pipe 1
  radio.startListening();


  // ================================================================
  // ===                    Control Setup                         ===
  // ================================================================
  Serial2.begin(115200);

  // ================================================================
  // ===                    Program begin                         ===
  // ================================================================
  digitalWrite(Selector, HIGH);
  digitalWrite(EnableBoat, LOW);


  sampleT = micros();
}

void loop() {
  // ================================================================
  // ===                    Sample time                           ===
  // ================================================================
  if (micros() - sampleT > DelayTime) {
    sampleT = micros();
    if (countSignal > NUMLOST) {
      digitalWrite(Selector, HIGH); // Selector in Radio mode
      digitalWrite(EnableBoat, LOW); // Boat is enabled
      colorWipe(strip1.Color(255,   0,   0), 0);    // Red
    }
    else {
      countSignal ++;
    }
    ADC_read();
  }
  NRF24_receive();
}
