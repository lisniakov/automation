# My Project Journey: Building a Smart Monitoring System

## Introduction

Embarking on this project, my aim was to create a sophisticated environmental monitoring system using an ESP8266 microcontroller, various sensors, and a web server interface. This system would provide real-time data on temperature, humidity, and particulate matter levels while offering warnings if any parameter exceeded predefined limits.

## Initial Setup

I began by setting up the ESP8266 microcontroller, ensuring it could connect to Wi-Fi and communicate with the necessary sensors. Integration of the BME280 sensor for temperature and humidity readings, along with the PMS5003 sensor for particulate matter measurements, laid the foundation for the project.

```cpp
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
```

## Displaying Data

Once the sensors were integrated, my focus shifted to displaying the collected data on a web interface. I configured the ESP8266 to host a web server and designed a simple webpage to showcase temperature, humidity, and particle counts for different sizes. This initial setup provided a basic overview of environmental conditions but lacked the sophistication needed for comprehensive monitoring.

```cpp
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
```

## Setting Limits

To enhance the monitoring system, I introduced predefined limits for temperature, humidity, and particle counts. Establishing normal ranges (e.g., 19°C - 23°C for temperature) allowed for proactive monitoring and timely interventions if conditions deviated from the expected range.

```cpp
const float MIN_TEMP = 19.0;
const float MAX_TEMP = 23.0;
const float MIN_HUMIDITY = 55.0;
const float MAX_HUMIDITY = 65.0;
const float MAX_PM05 = 352000;
const float MAX_PM1 = 83200;
const float MAX_PM5 = 2930;
```

## Implementing Warnings

The final touch to my project involved implementing a warning system. If any sensor reading exceeded its predefined limit, the system would display a warning message on the web interface, alerting users to the issue. These warnings served as valuable indicators, prompting users to take corrective action or investigate further as needed.

```cpp
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
```

## Conclusion

In conclusion, my journey to build a smart environmental monitoring system was both challenging and rewarding. The advantages of my device include ease of installation and use, as well as low cost of parts.

I believe that my device does not have enough data recording in the device memory, so in the future I plan to add data recording, after which it will be possible to conduct statistical analyzes from this data, build graphs, and so on.

Thank you for your attention, stay tuned for updates on the project!
