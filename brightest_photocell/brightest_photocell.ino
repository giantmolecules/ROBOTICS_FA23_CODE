// Arduino program to determine the brightest light detected by five photocells

int photocellPin1 = 18;  // Analog input pin for photocell 1
int photocellPin2 = 17;  // Analog input pin for photocell 2
int photocellPin3 = 16;  // Analog input pin for photocell 3
int photocellPin4 = 15;  // Analog input pin for photocell 4
int photocellPin5 = 14;  // Analog input pin for photocell 5

int brightestPhotocell = 0;  // Variable to store the number of the brightest photocell
int brightestValue = 0;      // Variable to store the brightest value

int brightnessThreshold = 1000;

void setup() {
  
  // initialize serial communication
  Serial.begin(115200);
}

void loop() {
  
  // Read values from the photocells
  int photocellValue1 = analogRead(photocellPin1);
  int photocellValue2 = analogRead(photocellPin2);
  int photocellValue3 = analogRead(photocellPin3);
  int photocellValue4 = analogRead(photocellPin4);
  int photocellValue5 = analogRead(photocellPin5);

  // Find the brightest photocell
  if (photocellValue1 > brightestValue) {
    brightestValue = photocellValue1;
    brightestPhotocell = 1;
  }
  if (photocellValue2 > brightestValue) {
    brightestValue = photocellValue2;
    brightestPhotocell = 2;
  }
  if (photocellValue3 > brightestValue) {
    brightestValue = photocellValue3;
    brightestPhotocell = 3;
  }
  if (photocellValue4 > brightestValue) {
    brightestValue = photocellValue4;
    brightestPhotocell = 4;
  }
  if (photocellValue5 > brightestValue) {
    brightestValue = photocellValue5;
    brightestPhotocell = 5;
  }

  // Print the result
  Serial.print("The brightest light is detected by photocell ");
  Serial.print(brightestPhotocell);
  Serial.print(", with a value of ");
  Serial.println(brightestValue);
  
  // was it a flash?
  if(brightestValue > brightnessThreshold){
    Serial.println("FLASH!");
  }
  // comment out delay for normal operation
  delay(1000);
}
