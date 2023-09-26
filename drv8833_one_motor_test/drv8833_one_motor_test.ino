//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// project_template.ino
//
// This is a template for our code that readies the TFT for use.
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
const int ledChannel = 0;
const int resolution = 10;

int minPWM = 400;
int maxPWM = 1023;

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
  tft.setTextSize(3);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Configure PWM
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);

  // Attach pin
  ledcAttachPin(5, 0);
  ledcAttachPin(6, 1);



}

//----{LOOP}------------------------------------------------------//

void loop() {

  //pinMode(5, OUTPUT);
  //digitalWrite(5, 1);
  ledcWrite(0, 0);
  //ledcAttachPin(6, 0);

  for (int i = minPWM; i <= maxPWM; i++) {
    ledcWrite(1, i);
    tftPrint(0, i);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    ledcWrite(1, i);
    tftPrint(0, i);
    delay(1);
  }
  //ledcDetachPin(6);

  //pinMode(6, OUTPUT);
  //digitalWrite(6, 1);
  ledcWrite(1, 0);
  //ledcAttachPin(5,0);

  for (int i = minPWM; i <= maxPWM; i++) {
    ledcWrite(0, i);
    tftPrint(i, 0);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    ledcWrite(0, i);
    tftPrint(i, 0);
    delay(1);
  }
  //ledcDetachPin(5);
}

void tftPrint(int a, int b) {
  tft.setCursor(0, 0);
  tft.println("IN1    IN2");
  tft.print(a);
  tft.print("      ");
  tft.print(b);
  tft.print(" ");
}

//----{END}------------------------------------------------------//
