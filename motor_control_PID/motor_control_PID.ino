/* Robot_SimpleMotor_Drive_V0 with encoders
 * 
 * Adafruit Feather M4 using Pololu TB6612FNG motor controller
 * Drives two motors at fixed speed with PI control
 * 
 * Motor Control Table
 * XIN1   XIN2    Effect
 * Low    Low     Brake
 * Low    High    Forward
 * High   Low     Reverse
 * 
 * Free to use for all
 * F Milburn, January 2020
 */
#include <PID_v1.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Output pins used to control motors

//const uint16_t PWMA = 5;   // Motor A PWM control     Orange
const uint16_t AIN1 = 5;  // Motor A input 1         Green
const uint16_t AIN2 = 6;  // Motor A input 2         Brown

const uint16_t BIN1 = 9;   // Motor B input 1         Yellow
const uint16_t BIN2 = 10;  // Motor B input 2         Purple
//const uint16_t PWMB = 12;  // Motor B PWM control     White
const uint16_t STBY = 13;  // Standby                 Brown
// Motor encoder external interrupt pins
const uint16_t ENCA = 11;  // Encoder A input         Yellow
const uint16_t ENCB = 12;  // Encoder B input         Green
// PWM
const uint16_t ANALOG_WRITE_BITS = 8;
const uint16_t MAX_PWM = pow(2, ANALOG_WRITE_BITS) - 1;
const uint16_t MIN_PWM = MAX_PWM / 4;  // Make sure motor turns
// Motor timing
unsigned long nowTime = 0;     // updated on every loop
unsigned long startTimeA = 0;  // start timing A interrupts
unsigned long startTimeB = 0;  // start timing B interrupts
unsigned long countIntA = 0;   // count the A interrupts
unsigned long countIntB = 0;   // count the B interrupts
double periodA = 0;            // motor A period
double periodB = 0;            // motor B period
// PID
const unsigned long SAMPLE_TIME = 100;  // time between PID updates
const unsigned long INT_COUNT = 20;     // sufficient interrupts for accurate timing
double setpointA = 150;                 // setpoint is rotational speed in Hz
double inputA = 0;                      // input is PWM to motors
double outputA = 0;                     // output is rotational speed in Hz
double setpointB = 150;                 // setpoint is rotational speed in Hz
double inputB = 0;                      // input is PWM to motors
double outputB = 0;                     // output is rotational speed in Hz
double KpA = 0.20, KiA = 0.20, KdA = 0;
double KpB = 0.20, KiB = 0.20, KdB = 0;
PID motorA(&inputA, &outputA, &setpointA, KpA, KiA, KdA, DIRECT);
PID motorB(&inputB, &outputB, &setpointB, KpB, KiB, KdB, DIRECT);
double storeB = 0;  // used for debug print
void setup() {
  //initMotors();
  initEncoders();
  initPWM();
  //Serial.begin(115200);
  //while (!Serial) {
  // wait for serial to start
  //}

  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);

  ledcAttachPin(AIN1, 0);
  ledcAttachPin(AIN2, 1);
  ledcAttachPin(BIN1, 2);
  ledcAttachPin(BIN2, 3);

  setpointA = 10;
  setpointB = 10;

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

}
void loop() {

  nowTime = millis();
  motorA.Compute();
  motorB.Compute();
  forwardA((int)outputA);
  forwardB((int)outputB);

  if (storeB != outputB) {
    storeB = outputB;
    tft.setCursor(0,0);
    tft.println("inA, inB, errA, errB");
    tft.print(inputA);
    tft.print("  ");
    tft.print(inputB);
    tft.print("  ");
    tft.print(100 * (setpointA - inputA) / setpointA);
    tft.print("  ");
    tft.print(100 * (setpointB - inputB) / setpointB);
    tft.println("\n");
  }
}
void forwardA(uint16_t pwm) {
  ledcWrite(0, 0);
  ledcWrite(1, pwm);
  //digitalWrite(AIN1, LOW);
  //digitalWrite(AIN2, HIGH);
  //analogWrite(PWMA, pwm);
}
void forwardB(uint16_t pwm) {
  ledcWrite(2, 0);
  ledcWrite(3, pwm);
  // digitalWrite(BIN1, LOW);
  // digitalWrite(BIN2, HIGH);
  // analogWrite(PWMB, pwm);
}
void reverseA(uint16_t pwm) {
  ledcWrite(1, 0);
  ledcWrite(0, pwm);
  // digitalWrite(AIN1, HIGH);
  // digitalWrite(AIN2, LOW);
  // analogWrite(PWMA, pwm);
}
void reverseB(uint16_t pwm) {
  ledcWrite(3, 0);
  ledcWrite(2, pwm);
  // digitalWrite(BIN1, HIGH);
  // digitalWrite(BIN2, LOW);
  // analogWrite(PWMB, pwm);
}
void brakeA() {
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  //digitalWrite(AIN1, LOW);
  //digitalWrite(AIN2, LOW);
}
void brakeB() {
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  //digitalWrite(BIN1, LOW);
  //digitalWrite(BIN2, LOW);
}
void standbyMotors(bool standby) {
  if (standby == true) {
    digitalWrite(STBY, LOW);
  } else {
    digitalWrite(STBY, HIGH);
  }
}
void initMotors() {
  //pinMode(AIN1, OUTPUT);
  //pinMode(AIN2, OUTPUT);
  //pinMode(PWMA, OUTPUT);
  //pinMode(BIN1, OUTPUT);
  //pinMode(BIN2, OUTPUT);
  //pinMode(PWMB, OUTPUT);
  //pinMode(STBY, OUTPUT);
  //analogWriteResolution(ANALOG_WRITE_BITS);
  //standbyMotors(false);
}
void initEncoders() {
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  attachInterrupt(ENCA, isr_A, RISING);
  attachInterrupt(ENCB, isr_B, RISING);
}
void initPWM() {
  startTimeA = millis();
  startTimeB = millis();
  motorA.SetOutputLimits(MIN_PWM, MAX_PWM);
  motorB.SetOutputLimits(MIN_PWM, MAX_PWM);
  motorA.SetSampleTime(SAMPLE_TIME);
  motorB.SetSampleTime(SAMPLE_TIME);
  motorA.SetMode(AUTOMATIC);
  motorB.SetMode(AUTOMATIC);
}
void isr_A() {
  // count sufficient interrupts to get accurate timing
  // inputX is the encoder frequency in Hz
  countIntA++;
  if (countIntA == INT_COUNT) {
    inputA = (double)INT_COUNT * 1000 / (double)(nowTime - startTimeA);
    startTimeA = nowTime;
    countIntA = 0;
  }
}
void isr_B() {
  // count sufficient interrupts to get accurate timing
  // inputX is the encoder frequency in Hz
  countIntB++;
  if (countIntB == INT_COUNT) {
    inputB = (double)INT_COUNT * 1000 / (double)(nowTime - startTimeB);
    startTimeB = nowTime;
    countIntB = 0;
  }
}