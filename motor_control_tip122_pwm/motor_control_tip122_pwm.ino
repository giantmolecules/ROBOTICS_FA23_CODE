//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// motor_control_tip122_pwm.ino
//
// Speed up and slow down a motor.
//
//----------------------------------------------------------------//
void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5, LOW);
  delay(1000);
  digitalWrite(5, HIGH);
  delay(1000);
}

// Set paramaters for PWM peripheral
const int freq = 5000;
const int resolution = 10; // 10bit = 1024 values
const int channel = 0;

void setup() {
  // Configure PWM: channel, frequency, resolution
  ledcSetup(channel, freq, resolution);
  // Attach pin, channel
  ledcAttachPin(5, 0);
}

void loop() {

  for (int i = 0; i < 1024; i++) {
    ledcWrite(0, i); // channel, value
    delay(10);
  }

  delay(3000);

  for (int i = 1024; i > 0; i--) {
    ledcWrite(0, i); // channel, value
    delay(10);
  }

  delay(3000);

}
