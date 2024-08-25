#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  mySwitch.enableTransmit(17);  // GPIO 17 on ESP32
}

void loop() {
  mySwitch.send("10101010");  // Send a simple binary string
  Serial.println("Data Sent: 10101010");
  delay(1000);  // Send data every second
}
