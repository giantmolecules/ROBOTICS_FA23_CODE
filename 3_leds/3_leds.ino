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

int time_now_1 = 0;
int time_then_1 = 0;
int interval_1 = 1000;

int time_now_2 = 0;
int time_then_2 = 0;
int interval_2 = 2500;

int time_now_3 = 0;
int time_then_3 = 0;
int interval_3 = 4500;

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

  time_now_1 = millis();

  if (time_now_1 - time_then_1 >= interval_1) {

    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);

     time_then_1 = millis();
  }

  
  time_now_2 = millis();

  if (time_now_2 - time_then_2 >= interval_2) {

    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED2, LOW);

    time_then_2 = millis();

  }
    time_now_3 = millis();

  if (time_now_3 - time_then_3 >= interval_3) {
    digitalWrite(LED3, HIGH);
    delay(100);
    digitalWrite(LED3, LOW);

    time_then_3 = millis();
  }
}

//----{END}------------------------------------------------------//
