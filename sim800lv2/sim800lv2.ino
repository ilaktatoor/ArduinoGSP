#include <SoftwareSerial.h>

SoftwareSerial sim800l(0, 4);//tx/rx

// Pin definitions
const int resetPin = 9;

// Define the phone number as a variable
String phoneNumber = "+524443939456"; // Replace with the recipient's phone number

void setup() {
  // Set up serial communication to monitor
  Serial.begin(9600);
  
  // Set up software serial for SIM800L communication
  sim800l.begin(9600);
  
  // Configure reset pin
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH); // Deactivate reset
  
  // Initialize SIM800L
  Serial.println("Initializing SIM800L...");
  resetSIM800L();
  delay(1000);
  sendATCommand("AT"); // Basic AT command to check communication
  sendATCommand("AT+CPIN?"); // Check SIM card status
  sendATCommand("AT+CSQ"); // Check signal quality
  sendATCommand("AT+CREG?"); // Check network registration
}

void loop() {
  // Receive and display data from SIM800L
  if (sim800l.available()) {
    String response = sim800l.readString();
    Serial.println("SIM800L Response: " + response);
  }
  
  // Example to send data (AT command)
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    sendATCommand(command);
  }
}

void resetSIM800L() {
  digitalWrite(resetPin, LOW);
  delay(1000);
  digitalWrite(resetPin, HIGH);
  delay(2000); // Allow module to reset
}

void sendATCommand(String command) {
  sim800l.println(command);
  delay(1000); // Wait for response
  while (sim800l.available()) {
    String response = sim800l.readString();
    Serial.println("SIM800L Response: " + response);
  }
}

void sendSMS(String message) {
  sendATCommand("AT+CMGF=1"); // Set SMS text mode
  sendATCommand("AT+CMGS=\"" + phoneNumber + "\""); // Send SMS to the phone number
  sim800l.print(message); // Message content
  sim800l.write(26); // ASCII code for CTRL+Z to send the message
}

void receiveSMS(int index) {
  sendATCommand("AT+CMGR=" + String(index)); // Read SMS from storage position `index`
}
