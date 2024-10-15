#include <SoftwareSerial.h>
SoftwareSerial sim900(7, 8);  // RX, TX

void setup() {
  Serial.begin(9600);  
  sim900.begin(9600);  
  delay(1000);         
}

void Sendmessage() {
  sim900.println("AT");  
  delay(1000);
 
  sim900.println("AT+CPIN?");  
  delay(1000);
  
  sim900.println("AT+CMGF=1");  
  delay(1000);
  
  sim900.println("AT+CMGS=\"+94774254110\"");  
  delay(1000);
  
  sim900.println("Danger! flame sensor is on");
  delay(1000);
  
  sim900.write(26);  
  delay(1000);
  
  Serial.println("Message sent.");
}

void loop() {
  Sendmessage();  
  delay(10000);  
}
