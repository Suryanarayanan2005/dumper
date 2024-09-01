#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  // Start the Serial monitor
  Serial.begin(115200);

  // Initialize Bluetooth Serial with a device name
  SerialBT.begin("ESP32_BT_Device"); 
  Serial.println("The device started, now you can pair it with a mobile device.");
}

void loop() {
  // Check if the ESP32 is receiving data from the mobile device
  if (SerialBT.available()) {
    // Read the incoming data
    String incoming = SerialBT.readString();
    
    // Print the received data to the Serial Monitor
    Serial.print("Received via Bluetooth: ");
    Serial.println(incoming);

    // Send a response back to the mobile device
    SerialBT.println("Message received: " + incoming);
  }

  // Optionally send data periodically
  delay(2000);
  SerialBT.println("Hello from ESP32");
}
