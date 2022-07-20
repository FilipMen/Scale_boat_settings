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

union myInt32 {
  uint8_t myByte[4];
  int32_t myInt32;
} cLat, cLon;

union myInt16 {
  uint8_t myByte[2];
  int16_t myInt16;
} numMessageRX, numMessageTX;

unsigned long sampleT;
bool signalLost;
byte countSignal = 0;
#define DelayTime 20000
#define NUMSEND 20
#define NUMLOST 20
// ================================================================
// ===                    Variables IMU                         ===
// ================================================================
//Direccion I2C de la IMU 9250
MPU9250 mpu;
myInt16 yaw, pitch, roll, accX, accY;



// ================================================================
// ===                    Variables GPS                         ===
// ================================================================
String inputString = "";         // a String to hold incoming data
int timeStamp; // GPS time stamp
String NS = ""; // GPS North or Sur
String EW = ""; // GPS East or Weast

// ================================================================
// ===                    Variables ADS1115                     ===
// ================================================================
ADS1115 ADS(0x48);
myInt16 batCurr;
myInt16 batVol;

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
// To use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = true;  // true = TX role, false = RX role

// The sizeof this struct should not exceed 32 bytes
struct TXData {
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
  byte yaw1;
  byte yaw2;
  byte roll1;
  byte roll2;
  byte pitch1;
  byte pitch2;
  byte accX1;
  byte accX2;
  byte accY1;
  byte accY2;
  byte batCurr1;
  byte batCurr2;
  byte batVol1;
  byte batVol2;
};

struct RXData {
  byte numMessage1;
  byte numMessage2;
  byte ch1;
  byte ch2;
  byte ch3;
  byte Mode;
};

// ================================================================
// ===                    Variables control                     ===
// ================================================================
#define Selector 5 // Pin to select if control or PC mode
#define EnableBoat 8 // Pin to Enable/Disable the output
//#define RudderPin 10 // Pin to connect the servo motor for control the angle
//#define ThMotor1 13 // Pin Motor 1 control
//#define ThMotor2 15 // Pin Motor 2 control

Servo rudder;
Servo motor1;
Servo motor2;
byte PMW_motor1 = 0;
byte PMW_motor2 = 0;
byte PMW_motor1_1 = 0;
byte PMW_motor2_1 = 0;
byte rudder_angle = 0;
int Delayy = 10;

// State machine variables
bool state = 0;
byte controlMode = 0;
bool report = false;

unsigned int servo_counter = 0;
byte rudder_delay = 100;
byte motor1_delay = 100;
byte motor2_delay = 100;

//Create a variable with the structure above and name it sent_data
TXData sendData;
RXData receiveData;
int16_t numMessageRX1 = 0;

void setup() {
  // ================================================================
  // ===                    Pin Setup                             ===
  // ================================================================
  pinMode(Selector, OUTPUT);
  pinMode(EnableBoat, OUTPUT);
  pinMode(RudderPin, OUTPUT);
  pinMode(ThMotor1, OUTPUT);
  pinMode(ThMotor2, OUTPUT);
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
  NS.reserve(1);
  EW.reserve(1);
  // ================================================================
  // ===                    Variables IMU SETUP                   ===
  // ================================================================
  //IMU_calibration();
  if (!mpu.setup(0x68)) {  // change to your own address
    Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
  }
  else {
    Serial.println("MPU connection ok.");
  }
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
    Serial.println(F("Radio correct!!"));
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
  // ===                    Control Setup                         ===
  // ================================================================
  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 4;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  //TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20); // No prescaling   
  //TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20); // 8 prescaler
  TCCR2B |= (0 << CS22) | (1 << CS21) | (1 << CS20); // 32 prescaler
  //TCCR2B |= (1 << CS22) | (0 << CS21) | (0 << CS20); // 64 prescaler
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  // ================================================================
  // ===                    Program begin                         ===
  // ================================================================
  //rudder.write(1500);
  motor1.write(90);
  //motor2.writeMicroseconds(1000);

  digitalWrite(Selector, HIGH);
  digitalWrite(EnableBoat, LOW);


  sampleT = micros();
}

void loop() {
  // ================================================================
  // ===                    Sample time                           ===
  // ================================================================
  motor1.write(rudder_angle);
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
  }
  IMU_read();
  NRF24_receive();
}
