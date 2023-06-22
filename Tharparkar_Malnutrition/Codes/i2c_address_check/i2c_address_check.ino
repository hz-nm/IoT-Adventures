// Source --> https://randomnerdtutorials.com/esp32-esp8266-i2c-lcd-arduino-ide/

#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}

void loop() {
  // put your main code here, to run repeatedly:
  byte error, address;
  int nDevices;
  Serial.println("Scanning");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C Device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C Devices found \n");
  }
  else {
    Serial.println("done\n");
  }
  delay(5000);
}
