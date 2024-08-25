#include <WiFi.h>
#include "secrets.h"  // Ensure this file contains AWS_CERT_CA, AWS_CERT_CRT, AWS_CERT_PRIVATE, AWS_IOT_ENDPOINT, THINGNAME
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_BMP085_U.h> // Include BMP180 library

// Create an instance of the BMP180 sensor
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

// Define MQTT topics
#define AWS_IOT_PUBLISH_TOPIC   "test_build_3/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "test_build_3/sub"

float temperature;
float pressure;
float altitude;

WiFiClientSecure net;
PubSubClient client(net);

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

  // Create a message handler
  client.setCallback(messageHandler);

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

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<256> doc;  // Adjust size if needed
  doc["temperature"] = String(temperature, 2);
  doc["pressure"] = String(pressure, 2);
  doc["altitude"] = String(altitude, 2);
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

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Incoming message on topic: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload, length);

  if (error)
  {
    Serial.print("DeserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* message = doc["message"];
  Serial.println(message);
}

void setup() {
  Serial.begin(115200);

  // Initialize BMP180 sensor
  if (!bmp.begin()) {
    Serial.println("Couldn't find BMP180 sensor");
    while (1);
  }

  connectAWS();
}

void loop() {
  // Read BMP180 data
  sensors_event_t event;
  bmp.getEvent(&event);
  if (event.pressure) {
    pressure = event.pressure;
    bmp.getTemperature(&temperature);
    altitude = bmp.pressureToAltitude(1013.25, pressure);  // Assuming sea level pressure of 1013.25 hPa
  }

  Serial.println("Temperature: " + String(temperature, 2) + " °C");
  Serial.println("Pressure: " + String(pressure, 2) + " hPa");
  Serial.println("Altitude: " + String(altitude, 2) + " m");
  Serial.println("---");

  publishMessage();
  client.loop();
  delay(5000); // Adjust delay as needed
}