// Using Arduino's Example to work out our own details.
// TODO
// Integrate Turbidity Sensor
// Integrate Soil Moisture
// Integrate pH sensor
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SENSOR A0               // pH meter analog input to Arduino
#define OFFSET 0.0              // offset for pH for deviation compensation.
#define SAMPLING_INTERVAL 20
#define ARRAY_LENGTH 40         // times of collection

const int phPin = 34;
float ph_val;
float ph_act;

int PH_ARRAY[ARRAY_LENGTH];
int PH_ARRAY_INDEX=0;

Adafruit_BME280 bme;            // FOR I2C

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
  Serial.begin(115200);
  while(!Serial);
  Serial.println("WiFi Connection TESTING");

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
  Serial.println("--Currently testing BME280 and pH--");
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

            static unsigned long SAMPLING_TIME = millis();
            static unsigned long PRINT_TIME = millis();
            static float VOLTAGE;
            
            if(millis() - SAMPLING_TIME > SAMPLING_INTERVAL) {
              PH_ARRAY[PH_ARRAY_INDEX++] = analogRead(phPin);
              if(PH_ARRAY_INDEX==ARRAY_LENGTH)PH_ARRAY_INDEX=0;
              VOLTAGE = (AVERAGE_ARRAY(PH_ARRAY, ARRAY_LENGTH) * 3.3)/4096;
              SAMPLING_TIME = millis();
            }
            if(millis() - PRINT_TIME > PRINT_INTERVAL) {
              Serial.print("Voltage OUTPUT: ");
              Serial.println(VOLTAGE, 2);
              float ph_val = (float) 1.711 * VOLTAGE;
              float ph_act = (float) VOLTAGE;
              Serial.print("PH: ");
              Serial.println(ph_val);
              
            }

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
            client.print("<p>PH Actual Voltage: ");
            client.print(ph_act);
            client.println(" Volts</p>");

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

double AVERAGE_ARRAY(int*ARR, int NUMBER)
{
    int i;
    int max, min;
    double AVG;
    long AMOUNT=0;
    if(NUMBER<=0){
        Serial.println("ERROR!/n");
        return 0;
    }
    if(NUMBER < 5){
        for(i=0; i<NUMBER;i++){
            AMOUNT += ARR[i];
        }
        AVG = AMOUNT/NUMBER;
        return AVG;
    }else{
        if(ARR[0]<ARR[1]){
            min = ARR[0]; max = ARR[1];
        }
        else{
            min = ARR[1]; max = ARR[0];
        };
        for(i=2;i<NUMBER;i++){
            if(ARR[i]<min){
                AMOUNT += min;
                min = ARR[i];
            }else {
                if(ARR[i] > max){
                    AMOUNT += max;
                    max = AMOUNT+=ARR[i];
                }else{
                    AMOUNT += ARR[i];
                }
            }
        }
        AVG = (double)AMOUNT/(NUMBER-2);
    }
    return AVG;
}
