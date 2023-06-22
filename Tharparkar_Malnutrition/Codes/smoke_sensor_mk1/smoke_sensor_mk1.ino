// https://deepbluembedded.com/esp32-esp8266-i2c-lcd-arduino-ide/
// Custom Character -> https://omerk.github.io/lcdchargen/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// i2C address for LCD 0x27
//#include <LiquidCrystal_I2C.h>

// set the Number of columns and rows for the LCD
int lcd_columns = 20;
int lcd_rows = 4;
float temperature;
float temperature_2;
float temp_sp;
float humidity;
float pressure;
int BUZZER = 32;
int ss_1 = A1;
int ss_2 = A2;
int ss_3 = A3;
int ss_4 = A4;
int pressure_1;
// int ss_5 = 26;
// int ss_6 = 25;

int smo_1 = 1000;
int smo_2 = 1000;
int smo_3 = 1000;
int smo_4 = 1000;
int smo_5 = 1000;
int smo_6 = 1000;;

Adafruit_BME280 bme;



// set LCD address by calling the LIBRARY
LiquidCrystal_I2C lcd(0x27, lcd_columns, lcd_rows);

void setup() {
  Serial.begin(9600);
  Serial.println("Let's go!");
  delay(1000);
  
  // put your setup code here, to run once:
  // initialize the LCD and turn on LCD Backlight
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("V-WORLD ClOUD NCBC");
  delay(1000);

  unsigned status;
  status = bme.begin(0x76);
  if(!status){
    Serial.println("Could not find a valid sensor!");
    Serial.println("SensorID was: 0x");
    delay(10);
  }
  pinMode(BUZZER, OUTPUT);
}

void loop() {

  // lcd.clear();
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  Serial.println(temperature);
  Serial.println(humidity);
  Serial.println(pressure);
  Serial.println();

  smo_1 = analogRead(ss_1);
  smo_2 = analogRead(ss_2);
  smo_3 = analogRead(ss_3);
  smo_4 = analogRead(ss_4);
  /*smo_5 = analogRead(ss_5);
  smo_6 = analogRead(ss_6);*/

  delay(400);

  if (smo_1 > 1200) {
    digitalWrite(BUZZER, HIGH);
  }
  if (smo_2 > 1200) {
    digitalWrite(BUZZER, HIGH);
  }
  if (smo_3 > 1200) {
    digitalWrite(BUZZER, HIGH);
  }
  
  if (smo_4 > 1200) {
    digitalWrite(BUZZER, HIGH);
  }
  /*
  if (smo_5 > 1200) {
    digitalWrite(BUZZER, HIGH);
  }
  if (smo_6 > 1200) {
    digitalWrite(BUZZER, HIGH);
  }
*/
  // write some logic for detecting spikes in temperature
  delay(2000);
  temperature_2 = bme.readTemperature();

  temp_sp = temperature_2 + temperature;
  if (temp_sp > 2.5*temperature) {
    Serial.print("Too HOT!!");
    lcd.clear();
    lcd.setCursor(5, 2);
    lcd.print("TOO HOT!");
    lcd.setCursor(0, 3);
    lcd.print("Take precautionary measures!");
    delay(5000);
  }
  Serial.println(temp_sp);

  
  // put your main code here, to run repeatedly:
  // set the cursor to first column, second row
  lcd.setCursor(4, 1);
  lcd.print("Temp: ");
  lcd.setCursor(10, 1);
  lcd.print(temperature);
  lcd.setCursor(16, 1);
  lcd.print("C");
  delay(1000);
  // lcd.clear();

  // set cursor to first column, third row
  lcd.setCursor(0, 2);
  lcd.print("Humi:");
  lcd.setCursor(5, 2);
  lcd.print(humidity);
  lcd.setCursor(10, 2);
  lcd.print("%");


  pressure_1 = int(pressure);
  lcd.setCursor(13, 2);
  lcd.print("Pr:");
  lcd.setCursor(16, 2);
  lcd.print(pressure_1);
  /*lcd.setCursor(18, 2);
  lcd.print("  ");*/
 

  // set cursor to first column, fourth row
  lcd.setCursor(0, 3);
  lcd.print("SS1: ");
  lcd.print(smo_1);
  delay(2000);
  lcd.setCursor(0, 3);
  lcd.print("SS2: ");
  lcd.print(smo_2);
  delay(2000);
  lcd.setCursor(0, 3);
  lcd.print("SS3: ");
  lcd.print(smo_3);
  delay(2000);
  lcd.setCursor(0, 3);
  lcd.print("SS4: ");
  lcd.print(smo_4);
  delay(2000);
  lcd.setCursor(0, 3);
  /*lcd.print("SS5: ");
  lcd.print(smo_5);
  delay(2000);
  lcd.setCursor(0, 3);
  lcd.print("SS6: ");
  lcd.print(smo_6);
  delay(2000);*/
  lcd.setCursor(0,3);
  lcd.print("           ");
  delay(200);
}
