#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpsSerial; // Instancia sin parámetros
TinyGPSPlus gps;
float latitude, longitude;

void setup() {
  Serial.begin(9600); // Monitor serie
  gpsSerial.begin(9600, 16, 5); // RX  GPIO16(D0) y TX  GPIO5(D1) 
}

void loop() {
  while (gpsSerial.available()) {
    int data = gpsSerial.read();
    if (gps.encode(data)) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      Serial.print("Latitude: ");
      Serial.println(latitude, 6);
      Serial.print("Longitude: ");
      Serial.println(longitude, 6);

      // Crear y mostrar el enlace para Google Maps
      String googleMapsURL = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
      Serial.print("Google Maps URL: ");
      Serial.println(googleMapsURL);
    }
  }
}
