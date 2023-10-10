//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// project_template.ino
//
// This is a template for our code that readies the TFT for use.
// It also sets up a task that runs on core 0. loop() runs on core 1.
// Does not currently work properly!
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Create a handle for a task
TaskHandle_t Task;

// Create timer for task
int timeThen = 0;
int timeNow = 0;
int interval = 100;


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


  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    tftPrint,   /* Task function. */
    "Task",     /* name of task. */
    20000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */

}

//----{LOOP}------------------------------------------------------//

void loop() {
  timeNow = millis();
  if (timeNow - timeThen > interval) {
    Serial.print("Loop: ");
    Serial.println(xPortGetCoreID());
    delay(100);
  }
}

//----{TASK}------------------------------------------------------//

void tftPrint(void * pvParameters) {
  Serial.print("Task: ");
  Serial.println(xPortGetCoreID());
  tft.setCursor(0, 0);
  tft.print("Hello");
  //delay(100);
}

//----{END}------------------------------------------------------//
