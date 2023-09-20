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

// Define LED pins
#define  LED1 10
#define  LED2 11
#define  LED3 12

int time_now = 0;
int time_then = 0;
int interval = 3000;

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
  tft.setTextSize(1);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Set mode of pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

}

//----{LOOP}------------------------------------------------------//

void loop() {

  time_now = millis();

  if (time_now - time_then >= interval) {

    // Turn pins ON
    digitalWrite(LED1, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);

    digitalWrite(LED2, HIGH);
    delay(300);
    digitalWrite(LED2, LOW);

    digitalWrite(LED3, HIGH);
    delay(500);
    digitalWrite(LED3, LOW);

    time_then = millis();
  }
}

//----{END}------------------------------------------------------//
