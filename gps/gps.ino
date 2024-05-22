

#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define RXpin 16
#define TXpin 5

SoftwareSerial mySerial(TXpin,RXpin);
SoftwareSerial mySerial_sms(0, 4);//tx/rx

TinyGPS gps;

void printFloat(double f, int digits = 2);

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial_sms.begin(9600);
  delay(200);
  
}

void loop() 
{
  bool newdata = false;
  unsigned long start = millis();

  while(millis() - start < 5000)
  {
    if(mySerial.available())
    {
      char c = mySerial.read();
      if(gps.encode(c))
      {
        newdata = true;
      }
    }
  }
    
  if(newdata)
  {
    Serial.println("Acquired Data: ");
    Serial.println("-------------------------------------------");
    gpsdata(gps);
    Serial.println("\n-------------------------------------------");
    Serial.println();
  }
}
     
void gpsdata(TinyGPS &gps)
{
  long latitude, longitude;
  float flatitude,flongitude;
  unsigned long date, time, chars, age;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  //latitude and longitude in 10^-5deg
  gps.get_position(&latitude, &longitude, &age);
  Serial.print("Lat/Long(float): "); Serial.print(latitude);Serial.print(", "); Serial.print(longitude);
  Serial.print(" Fix age: "); Serial.print(age); Serial.print("ms.");
  Serial.print("\n"); 

  //latitude and longitude in float
  gps.f_get_position(&flatitude, &flongitude, &age);
  Serial.print("Lat/Long(float): "); printFloat(flatitude,5);Serial.print(", "); printFloat(flongitude,5);
  Serial.print(" Fix age: "); Serial.print(age); Serial.print("ms.");
  Serial.print("\n"); 

}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0) 
  {
     Serial.print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) 
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}