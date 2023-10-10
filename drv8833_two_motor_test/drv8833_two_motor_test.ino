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

  // Motor 1 Forward
  ledcWrite(0, 0);
  for (int i = minPWM; i <= maxPWM; i++) {
    ledcWrite(1, i);
    tftPrint(i,0,0,0);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    ledcWrite(1, i);
    tftPrint(i,0,0,0);
    delay(1);
  }

  // Motor 1 Reverse
  ledcWrite(1, 0);
  for (int i = minPWM; i <= maxPWM; i++) {
    ledcWrite(0, i);
    tftPrint(0,i,0,0);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    ledcWrite(0, i);
    tftPrint(0,i,0,0);
    delay(1);
  }

  // Motor 2 Forward
  ledcWrite(2, 0);
  for (int i = minPWM; i <= maxPWM; i++) {
    ledcWrite(3, i);
    tftPrint(0,0,i,0);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    ledcWrite(3, i);
    tftPrint(0,0,i,0);
    delay(1);
  }

  // Motor 2 Reverse
  ledcWrite(3, 0);
  for (int i = minPWM; i <= maxPWM; i++) {
    ledcWrite(2, i);
    tftPrint(0,0,0,i);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    ledcWrite(2, i);
    tftPrint(0,0,0,i);
    delay(1);
  }



}

void tftPrint(int in1, int in2, int in3, int in4) {
  tft.setCursor(0, 0);
  tft.println("IN1    IN3");
  tft.print(in1);
  tft.print("      ");
  tft.print(in3);
  tft.print(" ");
  tft.println(" ");
  tft.println(" ");
  tft.println("IN2    IN4");
  tft.print(in2);
  tft.print("      ");
  tft.print(in4);
  tft.print(" ");
  tft.println(" ");
}

//----{END}------------------------------------------------------//
