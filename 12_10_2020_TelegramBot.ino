#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "hyperchaos";
const char* password = "hyperchaos";

//Initialise Telegram Bot
#define BotToken "1338257876:AAEAT1xFBJiCQt30zJFN5kO2o3l6truPsn8"
#define CHAT_ID "1301245043"

WiFiClientSecure client;
UniversalTelegramBot bot(BotToken, client);

//Check for new messages every one second
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin = 2;
bool ledState = LOW;

//Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {

  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    //chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    //Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/led_on to turn GPIO ON \n";
      welcome += "/led_off to turn GPIO OFF \n";
      welcome += "/state to request current GPIO state \n";
      bot.sendMessage(chat_id, welcome, "");

    }

    if (text == "/led_on") {
      bot.sendMessage(chat_id, " LED state set to ON", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);

    }

    if (text == "/led_off") {
      bot.sendMessage(chat_id, " LED state set to OFF", "");
      ledState = LOW;
      digitalWrite(ledPin, ledState);

    }

    if (text == "/state") {
      if (digitalRead(ledPin)) {
      bot.sendMessage(chat_id, "LED is ON", "");

      }
      else {
        bot.sendMessage(chat_id, "LED is OFF", "");
      }
    }
  }

}

void setup() {
  Serial.begin(115200);

#ifdef ESP8266
  client.setInsecure();
#endif

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  //Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");

  }
  //Print ESP32 local IP Address
  Serial.println(WiFi.localIP());

}

void loop() {
  if (millis() > (lastTimeBotRan + botRequestDelay)) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    }
    lastTimeBotRan = millis();
  }
}
