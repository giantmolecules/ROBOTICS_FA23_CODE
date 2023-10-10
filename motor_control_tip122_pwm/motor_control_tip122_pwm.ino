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
