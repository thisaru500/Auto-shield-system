#include <SoftwareSerial.h>
#include<Servo.h>
Servo yakada; 
SoftwareSerial sim900(7, 8);  // RX, TX

void setup() {
   int servo = 9;
  yakada.attach(servo);
  Serial.begin(9600);  
  sim900.begin(9600);  
  delay(1000);

   int smoke_sensor =A0;
   int safety_lim = 60;
   int ledset = 9;
   int relay = 10;
   
  
}

void Sim900a() {
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
   
  

  
}
