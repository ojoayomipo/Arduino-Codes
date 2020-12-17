#include "WiFi.h"
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

const char* ssid = "hyperchaos";
const char* password = "hyperchaos";

//Set LED GPIO
const int ledPin = 2;

//Stores led state
String ledState;

//Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//Replaces placeholder with LED state value
String processor(const String& var) {
  Serial.println(var);
  if (var == "STATE") {
    if (digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    Serial.println(ledState);
    return ledState;
  }
  return String();
}
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  //Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFSS");
  }

  //connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting");
  }
  //Print ESP32 Local IP
  Serial.println(WiFi.localIP());

  //Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(ledPin, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Route to set GPIO LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(ledPin, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Start Server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
