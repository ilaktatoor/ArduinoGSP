#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

SoftwareSerial gpsSerial; // Instancia sin parámetros
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600); // Monitor serie
  gpsSerial.begin(9600,5,4); // RX  GPIO16(D0) y TX  GPIO5(D1) 
}
void loop()
{
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();


  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    delay(1000);
  }
}


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    delay(1000);
    String googleMapsURL = "https://www.google.com/maps?q=" + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    Serial.println("Google Maps URL: ");
    Serial.println(googleMapsURL);

  }
  else
  {
    Serial.print(F("INVALID"));
    delay(1000);

  }
  Serial.println();
}