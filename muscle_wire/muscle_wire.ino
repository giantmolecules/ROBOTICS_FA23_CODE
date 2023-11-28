//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// muscle_wire.ino
//
// PWM muscle wire.
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


//----{SETUP}-----------------------------------------------------//

void setup() {

  // Configure PWM: channel, frequency, resolution
  ledcSetup(0, freq, resolution);
  // Attach pin, channel
  ledcAttachPin(5, 0);

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

}

//----{LOOP}------------------------------------------------------//

void loop() {

  // Fade In
  for (int i = 0; i < 1024; i++) {
    //write channel, value
    tft.setCursor(0, 0);
    tft.print(i);
    tft.print("    ");
    delay(20);
  }

  //Fade Outgitgit
  for (int i = 1024; i > 0; i--) {
    //write channel, value
    tft.setCursor(0, 0);
    tft.print(i);
    tft.print("    ");
    delay(20);
  }

}

//----{END}------------------------------------------------------//
