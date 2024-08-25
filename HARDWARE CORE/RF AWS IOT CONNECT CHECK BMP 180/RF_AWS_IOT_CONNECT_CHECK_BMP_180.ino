#include <WiFi.h>
#include "secrets.h"  // Ensure this file contains AWS_CERT_CA, AWS_CERT_CRT, AWS_CERT_PRIVATE, AWS_IOT_ENDPOINT, THINGNAME
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <RCSwitch.h>

#define RF_RECEIVER_PIN 16 // Change to your actual pin

RCSwitch mySwitch = RCSwitch();
WiFiClientSecure net;
PubSubClient client(net);

// Define MQTT topics
#define AWS_IOT_PUBLISH_TOPIC   "test_build_3/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "test_build_3/sub"

void connectAWS()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" Connected!");

    // Configure WiFiClientSecure to use the AWS IoT device credentials
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);

    // Connect to the MQTT broker on the AWS endpoint we defined earlier
    client.setServer(AWS_IOT_ENDPOINT, 8883);

    Serial.println("Connecting to AWS IoT");

    while (!client.connect(THINGNAME))
    {
        Serial.print(".");
        delay(1000); // Delay between connection attempts
    }

    if (!client.connected())
    {
        Serial.println("AWS IoT Connection failed!");
        return;
    }

    Serial.println("AWS IoT Connected!");
}

void publishMessage(float temperature, float pressure)
{
    StaticJsonDocument<256> doc;  // Adjust size if needed
    doc["temperature"] = String(temperature, 2);
    doc["pressure"] = String(pressure, 2);
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);

    if (!client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer))
    {
        Serial.println("Publish failed!");
    }
    else
    {
        Serial.println("Message published!");
    }
}

void setup()
{
    Serial.begin(9600); // Initialize serial communication
    mySwitch.enableReceive(RF_RECEIVER_PIN); // Receiver on specified pin
    connectAWS(); // Connect to AWS IoT
}

void loop()
{
    if (mySwitch.available())
    {
        unsigned long value = mySwitch.getReceivedValue();
        if (value == 0)
        {
            Serial.println("Unknown encoding");
        }
        else
        {
            // Extract pressure and temperature from the received data
            uint16_t pressure = (value >> 16) & 0xFFFF; // Extract the upper 16 bits
            uint16_t temperature = value & 0xFFFF; // Extract the lower 16 bits

            // Convert to float values
            float pressure_hPa = pressure / 100.0;
            float temperature_C = temperature / 10.0;

            // Display values
            Serial.print("Pressure: ");
            Serial.print(pressure_hPa);
            Serial.println(" hPa");

            Serial.print("Temperature: ");
            Serial.print(temperature_C);
            Serial.println(" C");

            // Publish the received data to AWS IoT
            publishMessage(temperature_C, pressure_hPa);
        }
        mySwitch.resetAvailable();
    }

    client.loop(); // Ensure the MQTT client keeps the connection alive
    delay(2000); // Wait a bit between checks
}
