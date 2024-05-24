#include <SoftwareSerial.h>

SoftwareSerial sim800l(0, 4);//tx/rx


// Define the phone number as a variable
String phoneNumber = "+524443930456"; // Replace with the recipient's phone number

void setup() {
  // Set up serial communication to monitor
  Serial.begin(9600);
  
  // Set up software serial for SIM800L communication
  sim800l.begin(9600);
  
}

void loop() {
  // Receive and display data from SIM800L
  if (sim800l.available()) {
    String response = sim800l.readString();
    Serial.println("SIM800L Response: " + response);
    if(response == "gps"){
      sendSMS(gpsData());

    }
  }
  
  // Example to send data (AT command)
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    
  }
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

String gpsData(){
  Serial.println("gps data");
  return "";
}


