//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// motion_control_servo_dc.ino
//
// Combine dc motor stuff with servos
//
// pins 5, 6, 9, 10 are for the dc motor
// pins 12 and 13 are for the servos
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
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
// Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33
int servo1Pin = 12;      // GPIO pin used to connect the servo control (digital out)
int servo2Pin = 13;      // GPIO pin used to connect the servo control (digital out)

// using SG90 servo min/max of 500us and 2400us
// for MG995 large servo, use 1000us and 2000us,
// which are the defaults, so this line could be
// "myservo.attach(servoPin);"
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
  
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  servo1.setPeriodHertz(50);// Standard 50hz servo
  servo1.attach(servo1Pin, 500, 2400);   // attaches the servo on pin 18 to the servo object
  servo2.setPeriodHertz(50);// Standard 50hz servo
  servo2.attach(servo2Pin, 500, 2400);   // attaches the servo on pin 18 to the servo object

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

  // move some servos

  // move dc motors

}

void left(int speed) {
  // Motor 1 Fwd
  // ledcWrite(channel, value)
  ledcWrite(0, 0); // set direction
  ledcWrite(1, speed); // set speed
  // Motor 2 Fwd
  // ledcWrite(channel, value)
  ledcWrite(2, 0); // set direction
  ledcWrite(3, speed); // set speed

}

void right(int speed) {
  // Motor 1 Rev
  // ledcWrite(channel, value)
  ledcWrite(1, 0); // set direction
  ledcWrite(0, speed); // set speed
  // Motor 2 Rev
  // ledcWrite(channel, value)
  ledcWrite(3, 0); // set direction
  ledcWrite(2, speed); // set speed
}

void forward(int speed) {
  // Motor 1 Fwd
  // ledcWrite(channel, value)
  ledcWrite(0, 0); // set direction
  ledcWrite(1, speed); // set speed
  // Motor 2 Rev
  // ledcWrite(channel, value)
  ledcWrite(3, 0); // set direction
  ledcWrite(2, speed); // set speed
}

void reverse(int speed) {
  // Motor 1 Rev
  // ledcWrite(channel, value)
  ledcWrite(1, 0); // set direction
  ledcWrite(0, speed); // set speed
  // Motor 2 Fwd
  // ledcWrite(channel, value)
  ledcWrite(2, 0); // set direction
  ledcWrite(3, speed); // set speed
}

//----{END}------------------------------------------------------//
