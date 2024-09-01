#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Define address variables with default values
String addresses[4] = {"FR_Address", "FL_Address", "RL_Address", "RR_Address"};
String pendingCommand = "";
int pendingIndex = -1;

void setup() {
  // Initialize Serial Monitor and Bluetooth Serial
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Device");

  // Initial message
  Serial.println("The device started, now you can pair it with a mobile device.");
  SerialBT.println("Commands: VIEW, REPLACE <index> <new_address>, CLEAR");
}

void loop() {
  // Check if data is available from Bluetooth
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    Serial.print("Received command: ");
    Serial.println(command);

    // Process the command
    if (pendingIndex == -1) {
      // First line of command
      processInitialCommand(command);
    } else {
      // Second line with new address
      replaceAddress(pendingIndex, command);
      pendingIndex = -1; // Reset after processing
    }
  }
}

void processInitialCommand(String command) {
  // Split command into parts
  int firstSpace = command.indexOf(' ');
  String action = command.substring(0, firstSpace);
  String rest = command.substring(firstSpace + 1);

  if (action == "VIEW") {
    viewAddresses();
  } 
  else if (action == "REPLACE") {
    pendingIndex = rest.toInt();
    if (pendingIndex < 1 || pendingIndex > 4) {
      SerialBT.println("Invalid index. Use 1 (FR), 2 (FL), 3 (RL), or 4 (RR).");
      pendingIndex = -1; // Reset invalid index
    } else {
      SerialBT.println("Please send the new address for index " + String(pendingIndex));
    }
  } 
  else if (action == "CLEAR") {
    clearAddresses();
  } 
  else {
    SerialBT.println("Unknown command. Use VIEW, REPLACE <index> <new_address>, or CLEAR");
  }
}

void viewAddresses() {
  SerialBT.println("Stored addresses:");
  SerialBT.println("FR: " + addresses[0]);
  SerialBT.println("FL: " + addresses[1]);
  SerialBT.println("RL: " + addresses[2]);
  SerialBT.println("RR: " + addresses[3]);
}

void replaceAddress(int index, String newAddress) {
  if (index < 1 || index > 4) {
    SerialBT.println("Invalid index. Use 1 (FR), 2 (FL), 3 (RL), or 4 (RR).");
    return;
  }

  if (newAddress.length() > 16) {
    SerialBT.println("Address too long. Max length is 16 characters.");
    return;
  }

  // Update address at the specified index
  addresses[index - 1] = newAddress;
  SerialBT.println("Address replaced successfully.");
}

void clearAddresses() {
  // Clear all addresses by setting them to empty strings
  addresses[0] = "";
  addresses[1] = "";
  addresses[2] = "";
  addresses[3] = "";

  SerialBT.println("All addresses cleared.");
}
