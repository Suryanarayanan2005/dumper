#include <RCSwitch.h>

#define RF_RECEIVER_PIN 16 // Change to your actual pin

RCSwitch mySwitch = RCSwitch();

void setup() {
    Serial.begin(9600); // Initialize serial communication
    mySwitch.enableReceive(RF_RECEIVER_PIN); // Receiver on pin 2
}

void loop() {
    if (mySwitch.available()) {
        unsigned long value = mySwitch.getReceivedValue();
        if (value == 0) {
            Serial.println("Unknown encoding");
        } else {
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
        }
        mySwitch.resetAvailable();
    }

    delay(2000); // Wait a bit between checks
}
