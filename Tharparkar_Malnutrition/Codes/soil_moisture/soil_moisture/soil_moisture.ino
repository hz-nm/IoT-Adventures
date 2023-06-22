// Code for connecting and testing the Moisture Sensor
// define sensor pins for power and signal
#define sensorPower 7
#define sensorPin A0

const int AirValue = 520;   //you need to replace this value with the value when the probe is in air
const int WaterValue = 260;  //you need to replace this value with the value when the probe is in the water

/*
 * Values
 * Air: 594
 * Water: 254
 * Dry Sand: 282
 * Wet Sand: 270
 * Max Wet Sand: 276
 * Mud: 270
 */

void setup() {
  // put your setup code here, to run once:
  // Initially keep the sensor off
  pinMode(sensorPower, OUTPUT);

  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Analog Output: ");
  int moisture = readSensor();

  Serial.println(moisture);
  // TODO -- Map the values according to required scale.
  // * Right now we are getting values of 550 for Air and we got to a minimum of 300 for a moist soil.
  // * 
  delay(1000);
}

// function to read sensor values on command.
int readSensor() {
  digitalWrite(sensorPower, HIGH);

  delay(10);

  // Read the sensor Value
  int val = analogRead(sensorPin);

  // Turn off the sensor
  digitalWrite(sensorPower, LOW);
  return val;
}
