//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// motor_control_tip122.ino
//
// Like BLINK sketch, but for motors.
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
