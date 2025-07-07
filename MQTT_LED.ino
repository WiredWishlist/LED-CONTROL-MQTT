#include <WiFi.h>
#include <PicoMQTT.h>

#define WIFI_SSID "Luminar_Ruckus4"  
#define WIFI_PASSWORD "space_bar"  
#define LED_PIN 2                    

class MyMQTTServer : public PicoMQTT::Server {
protected:

  PicoMQTT::ConnectReturnCode auth(const char *client_id, const char *username, const char *password) override {
    Serial.println("auth() called");
    if (!username || !password) {
      return PicoMQTT::CRC_NOT_AUTHORIZED;
    }

    if ((String(username) == "alice" && String(password) == "secret") ||
        (String(username) == "bob" && String(password) == "password")) {
      Serial.println("MQTT Auth accepted");
      return PicoMQTT::CRC_ACCEPTED;
    }

    Serial.println("MQTT Auth rejected");
    return PicoMQTT::CRC_BAD_USERNAME_OR_PASSWORD;
  }
};

MyMQTTServer mqtt;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.printf("\nWiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());

  mqtt.begin();
  Serial.println("MQTT server started");

  mqtt.subscribe("led", [](char *topic_ptr, PicoMQTT::IncomingPacket& packet) {
    Serial.println("Lambda handleMqttMessage called"); 

    String topic = String(topic_ptr);


    size_t payload_len = packet.get_remaining_size();
    char payload_buffer[payload_len + 1]; 
    packet.read((uint8_t*)payload_buffer, payload_len);
    payload_buffer[payload_len] = '\0';

    String msg = String(payload_buffer); 

    Serial.printf("Received on topic [%s]: %s\n", topic.c_str(), msg.c_str());

    if (topic == "led") {
      if (msg == "on") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED turned ON");
      } else if (msg == "off") {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED turned OFF");
      } else {
        Serial.printf("Unknown command for LED: %s\n", msg.c_str());
      }
    }
  });

  Serial.println("MQTT server subscribed to 'led' topic with lambda callback");
}

void loop() {
  mqtt.loop();
}
