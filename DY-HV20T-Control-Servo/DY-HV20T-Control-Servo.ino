//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// DY-HV20T-Control-Servo.ino
//
// This is for Khushi's robot.
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Include the ESP32 Arduino Servo Library instead of the original Arduino Servo Library
#include <ESP32Servo.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Create a servo object
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo

// Attach servo to pins
int servo1Pin = 12;
int servo2Pin = 13;

boolean playing = 0;

int servo1Positions[] = {75, 10, 43, 130, 110};
int servo2Positions[] = {36, 52, 95, 12, 84};

int counter1 = 0;
//int counter2 = 0;

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Set Up Pins
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  // Attach Interrupts
  attachInterrupt(9, play, FALLING);
  attachInterrupt(10, stop, FALLING);

  // Start Serial COM for debugging
  Serial.begin(115200);

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // default text size
  tft.setTextSize(3);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo1.setPeriodHertz(50);// Standard 50hz servo
  servo2.setPeriodHertz(50);// Standard 50hz servo
  servo1.attach(servo1Pin, 500, 2400);   // attaches the servo on pin 18 to the servo object
  servo2.attach(servo2Pin, 500, 2400);   // attaches the servo on pin 18 to the servo object
}

//----{LOOP}------------------------------------------------------//

void loop() {
  if (playing) {
    servo1.write(servo1Positions[counter1]);
    servo2.write(servo2Positions[counter1]);
    delay(3000);
    counter1++;
    if (counter1 >= 4) {
      counter1 = 0;
    }
  }
}

//----{PLAY}------------------------------------------------------//


void play() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  tft.setCursor(0, 0);
  tft.print("PLAY");
  playing = 1;
}

//----{STOP}------------------------------------------------------//

void stop() {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  tft.setCursor(0, 0);
  tft.print("STOP");
  playing = 0;
}

//----{END}------------------------------------------------------//
