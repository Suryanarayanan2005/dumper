#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  mySwitch.enableReceive(16);  // GPIO 16 on ESP32
}

void loop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();

    if (value == 0) {
      Serial.println("Unknown encoding");
    } else {
      Serial.print("Received: ");
      Serial.println(value);
    }

    mySwitch.resetAvailable();
  }
}
