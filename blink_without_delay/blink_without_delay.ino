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

#define LED_PIN 13

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int time_then = 0;
int time_now = 0;
int interval = 500;

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
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  pinMode(LED_PIN, OUTPUT);

}

//----{LOOP}------------------------------------------------------//

void loop() {
 time_now = millis();
 
 tft.setCursor(0,0);
 tft.print("Now: ");
 tft.println(time_now);
 tft.print(" Then: ");
 tft.println(time_then);
 tft.print(" Delta: ");
 tft.println(time_now-time_then);
 
 if(time_now - time_then >= interval){
  digitalWrite(LED_PIN, HIGH);
  //tft.setCursor(0,0);
  tft.fillScreen(ST77XX_BLACK);
  delay(interval);
  time_then = millis();
 }
 else{
  digitalWrite(LED_PIN, LOW);
 }
}

//----{END}------------------------------------------------------//
