// Using Arduino's Example to work out our own details.


#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// #define BME_SCK 13
// #define BME_MISO 12
// #define BME_MOSI 11
// #define BME_CS 10

Adafruit_BME280 bme;    // FOR I2C

const char* ssid = "ESP32-AP-Test";
const char* password = "123456789";
unsigned long delay_time;
float temp;
float humi;
float pressure;

String header;

WiFiServer server(80);

// Set Static IP Address
IPAddress local_IP(192, 168, 20, 81);
// Set Gateway IP Address
IPAddress gateway(192, 168, 20, 250);

IPAddress subnet(255, 255, 0, 0);
// Optional settings
//IPAddress primaryDNS(8, 8, 8, 8);
//IPAddress secondaryDNS(8, 8, 4, 4);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  // print the IP Address of the ESP32
  Serial.println(WiFi.localIP());
//  Serial.println("");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("WiFi Connection TESTING");
//  WiFi.mode(WIFI_STA);
//  WiFi.disconnect();
//  delay(100);
  // Configure static IP Address
//  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
//  if (!WiFi.config(local_IP, gateway, subnet)) {
//    Serial.println("STA Failed to configure");
//  }
  
//  initWiFi();
  Serial.println("Setting Access Point ...");
  WiFi.softAP(ssid, password);
  
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  Serial.println("Setup Done!");
  Serial.println(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);

  server.begin();

  unsigned status;
  status = bme.begin(0x76);     // status = bme.begin(0x76) --> specifying an I2C address for checking status.
  if (!status){
    Serial.println("Could not find a valid Sensor connected to our System.. Please check connection etc.");
    Serial.println();
    Serial.println("SensorID was: 0x");
    Serial.println(bme.sensorID(),16);
    while(1) delay(10);
  }
  Serial.println("--TESTING HAS BEGUN--");
  delay_time = 1000;
  Serial.println();
}

void loop() {

  // Code for developing a client side application.

  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          // if the current line is black, you get two newline characters
          // that's the end of the client HTTP request, so send a response.
          if (currentLine.length() == 0) {
            // HTTP header always start with a response code (e.g. HTTP/1.1
            // and a content-type so the client knows what's coming.
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Let's check what the GET Does..
            if (header.indexOf("GET /temp") >= 0) {
              Serial.println(bme.readTemperature());
              temp = bme.readTemperature();
            }

            // Check the temperature, humidity as well as Air Pressure
            temp = bme.readTemperature();
            humi = bme.readHumidity();
            pressure = bme.readPressure() / 100.0F;

            // Now we will display the HTML Web Page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\"content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:.\">");
            // Don't forget to use CSS
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4FAF55; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Display the current state, Temperature, humidity etc.
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.print("<p>Temperature: ");
            client.print(temp);
            client.println(" Celsius </p>");
            client.print("<p>Humidity: ");
            client.print(humi);
            client.println(" %</p>");
            client.print("<p>Pressure: ");
            client.print(pressure);
            client.println(" hPa</p>");

            // Display the current state of temperature.
            client.print("<p>Temperature: ");
            client.print("<a href=\"/temp/\">");
            client.print(temp);
            client.println("</a></p>");

            client.println("</body></html>");

            // the HTTP response ends with another blank line
            client.println();
            break;
          } else { // if you got a new line, then clear the current line.
            currentLine = "";
          }
        } else if (c != '\r') { // if we get anything else but a carriage return
          currentLine += c;
        }
      }
    }
    // clear the header variable
    header = "";
    // close the connection
    client.stop();
    Serial.println("Client has been disconnected.");
    Serial.println("");
  }
}
