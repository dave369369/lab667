#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "TIPIANS";
const char* password = "";
const char* serverUrl = "http://172.20.8.153:3000/data";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverUrl);

    http.addHeader("Content-Type", "application/json");

    // Example data
    String jsonData = "{\"temperature\":25,\"humidity\":60}";

    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully!");
      Serial.print("Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending data. Response code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  delay(10000); 
}
