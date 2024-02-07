#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <PMS.h> // Include the library for PMS5003 sensor

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
PMS pms(Serial);

float temperature, humidity;
float pm05, pm1, pm5; // Variables to store particle measurements

const float MIN_TEMP = 19.0;
const float MAX_TEMP = 23.0;
const float MIN_HUMIDITY = 55.0;
const float MAX_HUMIDITY = 65.0;
const float MAX_PM05 = 352000;
const float MAX_PM1 = 83200;
const float MAX_PM5 = 2930;

const char* ssid = "FRITZ!Box 7590";  
const char* password = "7544832138451365"; 

ESP8266WebServer server(80);              
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  bme.begin(0x76);
  pms.passiveMode(); // Set PMS5003 sensor to passive mode
  pms.wakeUp(); // Wake up the PMS5003 sensor

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  
  // Read particle measurements
  if (pms.readUntil(data)) {
    pm05 = data.PM_AE_UG_1_0;
    pm1 = data.PM_AE_UG_2_5;
    pm5 = data.PM_AE_UG_10_0;
  }
  
  String htmlResponse = SendHTML(temperature, humidity, pm05, pm1, pm5);
  
  // Check if temperature and humidity are within specified range
  if (temperature < MIN_TEMP || temperature > MAX_TEMP) {
    htmlResponse += "<p style=\"color:red;\">Temperature is outside normal limits!</p>";
  }
  if (humidity < MIN_HUMIDITY || humidity > MAX_HUMIDITY) {
    htmlResponse += "<p style=\"color:red;\">Humidity is outside normal limits!</p>";
  }
  
  // Check if particle counts are within specified range
  if (pm05 > MAX_PM05) {
    htmlResponse += "<p style=\"color:red;\">Particle count for 0.5µm is too high!</p>";
  }
  if (pm1 > MAX_PM1) {
    htmlResponse += "<p style=\"color:red;\">Particle count for 1µm is too high!</p>";
  }
  if (pm5 > MAX_PM5) {
    htmlResponse += "<p style=\"color:red;\">Particle count for 5µm is too high!</p>";
  }
  
  server.send(200, "text/html", htmlResponse); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float temperature, float humidity, float pm05, float pm1, float pm5){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Monitoring System</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Monitoring System</h1>\n";
  ptr +="<p>Temperature: ";
  ptr +=temperature;
  ptr +="&deg;C</p>";
  ptr +="<p>Humidity: ";
  ptr +=humidity;
  ptr +="%</p>";
  ptr +="<p>PM 0.5µm: ";
  ptr +=pm05;
  ptr +=" particles/m³</p>";
  ptr +="<p>PM 1µm: ";
  ptr +=pm1;
  ptr +=" particles/m³</p>";
  ptr +="<p>PM 5µm: ";
  ptr +=pm5;
  ptr +=" particles/m³</p>";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
