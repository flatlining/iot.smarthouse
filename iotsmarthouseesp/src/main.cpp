#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "config.h"

#define DHTPIN 4
#define DHTTYPE DHT11

#define LEDPIN 5

DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

long lastRead = 0;
float lastHumidity = 0;
float lastTemperature = 0;

void callback(char* topic, byte* payload, unsigned int length) {
        char pay[length+1];
        for (int i = 0; i < length; i++) {
                pay[i] = (char)payload[i];
        }
        pay[length] = '\0';

        Serial.print("mqtt]\tMessage arrived [");
        Serial.print(topic);
        Serial.print("]: ");
        Serial.print(pay);
        Serial.println();

        StaticJsonBuffer<160> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(pay);
        if (!root.success()) {
                Serial.println("json]\tparseObject() failed");
                return;
        }
        int lightId = atoi(root["messages"][0]["lightId"]);
        Serial.print("led]\tId: ");
        Serial.print(lightId);
        Serial.print(", from ");
        Serial.print(digitalRead(lightId));
        Serial.print(" to ");
        digitalWrite(lightId, !digitalRead(lightId));
        Serial.println(digitalRead(lightId));
}

void setup() {
        delay(500);
        Serial.begin(115200);

        pinMode(LEDPIN, OUTPUT);

        dht.begin();

        WiFi.disconnect(true);
        delay(1000);

        Serial.println();
        Serial.print("esp]\tInitializing, ");
        Serial.println(ESP.getSdkVersion());

        mqttClient.setServer(mqttServer, mqttPort);
        mqttClient.setCallback(callback);
}

void loop() {
        // wifi
        if (WiFi.status() != WL_CONNECTED) {
                // wifi not connected
                Serial.print("wifi]\tConnecting to ");
                Serial.print(wifiSsid);
                WiFi.begin(wifiSsid, wifiPassword);
                while (WiFi.status() != WL_CONNECTED) {
                        delay(500);
                        Serial.print(".");
                }
                Serial.println("");
                Serial.println("wifi]\tConnected!");
                Serial.print("wifi]\tIP address: ");
                Serial.println(WiFi.localIP());
        }

        // mqtt
        if (!mqttClient.connected()) {
                // mqtt not connected
                while (!mqttClient.connected()) {
                        Serial.print("mqtt]\tConnecting to ");
                        Serial.print(mqttServer);
                        Serial.print(" as ");
                        Serial.println(mqqtClient);
                        if (mqttClient.connect(mqqtClient)) {
                                Serial.println("mqtt]\tConnected!");
                                mqttClient.subscribe(topicPush);
                        } else {
                                Serial.print("mqtt]\tfailed, rc=");
                                Serial.print(mqttClient.state());
                                Serial.println(" try again in 5 seconds");
                                delay(5000);
                        }
                }
        }
        mqttClient.loop();

        // dht
        long now = millis();
        if (now - lastRead > 2500) {
                lastRead = now;
                float humidity = dht.readHumidity();
                float temperature = dht.readTemperature();
                if (isnan(humidity) || isnan(temperature)) {
                        Serial.println("dht]\tFailed to read from DHT sensor!");
                        return;
                }
                // Check DHT humidity thresholds (20 - 90)
                if (humidity < 20.0) {
                        humidity = 20.0;
                } else if (humidity > 90.0) {
                        humidity = 90.0;
                }
                // Check DHT temperature thresholds (0 - 50)
                if (temperature < 0.0) {
                        temperature = 0.0;
                } else if (temperature > 50.0) {
                        temperature = 50.0;
                }

                // http://www.hobbytronics.co.uk/arduino-float-vars
                char outstr[15];
                if (humidity != lastHumidity) {
                        // If humidity changed, publish
                        lastHumidity = humidity;
                        dtostrf(lastHumidity, 0, 2, outstr);
                        Serial.print("dht]\tHumidity: ");
                        Serial.print(outstr);
                        Serial.println(" %");

                        StaticJsonBuffer<160> jsonBuffer;
                        JsonObject& root = jsonBuffer.createObject();
                        root["mode"] = "async";
                        root["messageType"] = messageTypeHumidity;
                        JsonObject& message = root.createNestedArray("messages").createNestedObject();
                        message["humidity"] = outstr;
                        char b[root.measureLength() + 1];
                        root.printTo(b, sizeof(b));
                        mqttClient.publish(topicData, b);
                }

                if (temperature != lastTemperature) {
                        // If temperature changed, publish
                        lastTemperature = temperature;
                        dtostrf(lastTemperature, 0, 2, outstr);
                        Serial.print("dht]\tTemperature: ");
                        Serial.print(outstr);
                        Serial.println(" *C");

                        StaticJsonBuffer<160> jsonBuffer;
                        JsonObject& root = jsonBuffer.createObject();
                        root["mode"] = "async";
                        root["messageType"] = messageTypeTemperature;
                        JsonObject& message = root.createNestedArray("messages").createNestedObject();
                        message["temperature"] = outstr;
                        char b[root.measureLength() + 1];
                        root.printTo(b, sizeof(b));
                        mqttClient.publish(topicData, b);
                }
        }
}
