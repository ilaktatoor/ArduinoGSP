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
  }
  
  // Example to send data (AT command)
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    
  }
}




