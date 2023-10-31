//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// drv8833_two_motor_photocells.ino
//
// This program is a good illustration of Braitenberg's Vehicles
// Light-Following robot. 
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Set paramaters for PWM peripheral
const int freq = 5000;
const int resolution = 10;

int minPWM = 300;
int maxPWM = 1023;

const int leftEyePin = 18;
const int rightEyePin = 17;

int leftEyeValue = 0;
int rightEyeValue = 0;

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

int leftThreshold = 2800;
int rightThreshold = 2800;

//----{SETUP}-----------------------------------------------------//

void setup() {

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
  tft.setTextSize(2);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Configure PWM
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);
  ledcSetup(3, freq, resolution);

  // Attach pin
  ledcAttachPin(5, 0);
  ledcAttachPin(6, 1);
  ledcAttachPin(9, 2);
  ledcAttachPin(10, 3);

}

//----{LOOP}------------------------------------------------------//

void loop() {


  leftEyeValue = analogRead(leftEyePin);
  tft.setCursor(0, 0);
  tft.print("LE: ");
  tft.print(leftEyeValue);
  tft.print("  ");

  rightEyeValue = analogRead(rightEyePin);
  tft.setCursor(120, 0);
  tft.print("RE: ");
  tft.print(rightEyeValue);
  tft.print("  ");

  if (leftEyeValue < leftThreshold) {
    leftEyeValue = 0;
  }

  if (rightEyeValue < rightThreshold) {
    rightEyeValue = 0;
  }

  leftMotorSpeed = map(leftEyeValue, 0, 4095, minPWM, maxPWM);
  tft.setCursor(0, 20);
  tft.print("LM: ");
  tft.print(leftMotorSpeed);
  tft.print("  ");
  rightMotorSpeed = map(rightEyeValue, 0, 4095, minPWM, maxPWM);
  tft.setCursor(120, 20);
  tft.print("RM: ");
  tft.print(rightMotorSpeed);
  tft.print("  ");

  // Motor 1 Forward
  ledcWrite(0, 0);
  ledcWrite(1, rightMotorSpeed);
  delay(1);


  // Motor 2 Forward
  ledcWrite(2, 0);
  ledcWrite(3, leftMotorSpeed);
  delay(1);

}

//----{END}------------------------------------------------------//
