#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 4        // GPIO pin where DHT data is connected
#define DHTTYPE DHT11   // DHT 11 sensor type

const char* ssid = "WellIns";  // Replace with your WiFi name
const char* password = "jadejadejade";  // Replace with your WiFi password
const char* serverUrl = "http://172.20.10.4:3000/data"; // Update with your server IP and endpoint

DHT dht(DHTPIN, DHTTYPE);
WiFiClient wifiClient; // Create a WiFiClient object

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");
  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    HTTPClient http;
    http.begin(wifiClient, serverUrl);  // Updated with WiFiClient parameter
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.print("Data sent. Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data. Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(10000); // Send data every 10 seconds
}
