// Turbidity sensor measurement unit --> NTU: Nephelometric Turbidity Units
// Clear water with NTU less than 0.5 gives us a voltage of around 4.1v
// NTU 500 --> 3.27v
// NTU 50 -->  4.10v
// NTU 0.5 --> 4.21v
// check your own sensor's values and map it to the voltage levels.

// Basically, light intensity/sensing will reduce as the Turbidity increases

#include <Wire.h>

int turb_sensor_pin = A0;
float turb_sensor_voltage;
int samples = 100;    // average over 100 samples.
float ntu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(turb_sensor_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  turb_sensor_voltage = 0;
  // averaging over 100 samples.
  // for(int i=0; i<samples; i++) {
  //       turb_sensor_voltage += ((float)analogRead(turb_sensor_pin)/1023) * 5;
  //       delay(10);
  // }
  //turb_sensor_voltage = turb_sensor_voltage/samples;
  int turb_sensor_r = analogRead(turb_sensor_pin);
  turb_sensor_voltage = turb_sensor_r * (5.0 / 512.0);
  
  Serial.println(' ');
  Serial.print("Raw Reading: ");
  Serial.print(analogRead(turb_sensor_pin));
  Serial.println(' ');
  Serial.print("Voltage: ");
  Serial.println(turb_sensor_voltage);
  int turbidity_percent = map(turb_sensor_r, 400, 460, 100, 0); // 0 percent means clear water and 100 percent means unclear
  Serial.print("Percentage Values: ");
  Serial.println(turbidity_percent);
  delay(2000);

  ntu = -1120.4 * square(turb_sensor_voltage) + 5742.3 * turb_sensor_voltage - 4532.9;
  //Serial.println("Turbidity in NTU (averaged over 100 samples): ");
  //Serial.println(ntu);
  delay(10);  
}


// the map function
// float turb_sensor_voltage = analogRead(turb_sensor_pin)
// turb_sensor_voltage = (turb_sensor_voltage/1023) * 5
// int turbidity_percent = map(turb_sensor_voltage, 0, 640, 100, 0)    // replace 640 with the value you get for clear water from the Turbidity sensor.
