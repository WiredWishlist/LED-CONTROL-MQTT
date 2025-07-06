Project Title:
Control ESP32 Built-in LED using MQTT Explorer messages.


---

Overview

This program allows you to turn ON/OFF the built-in LED of an ESP32 board by sending MQTT messages from MQTT Explorer.
Messages are published to a topic, and the ESP32 subscribes to this topic and reacts based on the message received.


---

Hardware Required

ESP32 Development Board

Micro USB cable

Wi-Fi connection (with internet)



---

Connections

Built-in LED is already connected to GPIO 2 on the ESP32.

No extra wiring is needed.



---

MQTT Broker Configuration

Setting	Value

Host	broker.hivemq.com
Port	1883
Client ID	ESP32Client123 (default in code)
Topic	esp32/led



---

MQTT Explorer Usage

1. Open MQTT Explorer.


2. Click on + (top-left) to create a new connection.


3. Enter these values:

Name: Any name you prefer (e.g., ESP32 LED Control)

Host: broker.hivemq.com

Port: 1883

Leave other settings as default.



4. Click Connect.


5. In the Publish section:

Topic: esp32/led

Payload (Raw):

Type LED ON → to turn ON LED

Type LED OFF → to turn OFF LED


Make sure Retain is checked

Click Publish



## ✍ Project By

*Akash Sasikumar*  
Basic MQTT Project

