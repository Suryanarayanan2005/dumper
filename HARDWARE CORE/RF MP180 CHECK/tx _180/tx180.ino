#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <RCSwitch.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified();
#define RF_TRANSMITTER_PIN 17

RCSwitch mySwitch = RCSwitch();

void setup() {
    Serial.begin(9600);
    pinMode(RF_TRANSMITTER_PIN, OUTPUT);
    mySwitch.enableTransmit(RF_TRANSMITTER_PIN);

    if (!bmp.begin()) {
        Serial.println("Sensor error: BMP180 not detected");
        while (1);
    }
}

void loop() {
    sensors_event_t event;
    if (!bmp.getEvent(&event)) {
        Serial.println("Sensor error: Unable to read event");
        return;
    }

    if (event.pressure) {
        float temperature;
        bmp.getTemperature(&temperature);

        // Convert values to integers (e.g., multiply to avoid floating point)
        uint16_t pressure = (uint16_t)(event.pressure * 100); // e.g., 1013.25 hPa -> 101325
        uint16_t temp = (uint16_t)(temperature * 10); // e.g., 22.3 C -> 223

        // Combine values into a single 32-bit value if needed, or send separately
        uint32_t data = ((uint32_t)pressure << 16) | temp;

        // Send the data as binary
        mySwitch.send(data, 32);

        Serial.print("Sent pressure: ");
        Serial.print(pressure);
        Serial.print(", temperature: ");
        Serial.println(temp);

        delay(2000); // Wait a bit between measurements
    }
}
