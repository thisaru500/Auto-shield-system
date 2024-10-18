#include <SoftwareSerial.h>
#include<Servo.h>
Servo yakada; 
SoftwareSerial sim900(7, 8);  // RX, TX

   int smoke_sensor =A0;
   int safety_lim = 60;
   int ledset = 12;
   int relay = 10;
   int servo = 9;
   int flame = 11;
   int pos = 0;
   int buzzer = 3;
   
void setup() {
   
  yakada.attach(servo);
  Serial.begin(9600);  
  sim900.begin(9600);  
  delay(1000);

  pinMode(smoke_sensor , INPUT);
  pinMode(ledset , OUTPUT);
  pinMode(relay , OUTPUT);
  pinMode(flame , INPUT);
  pinMode(buzzer , OUTPUT);
   
  
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

void servo1() {
  for (pos = 0; pos <= 90; pos += 1) { 
  
    yakada.write(pos);             
    delay(20);                    
  }

void loop() {
   
 int sensor_read =  analogRead(smoke_sensor);
 int flame_value = digitalRead(flame);

 if(sensor_read >= safety_lim || flame_value == 1)
 { 
   sim900a();
   servo1();
   digitalWrite(relay , HIGH);//for turn off main switch
   for(int i = 50; i>0 ; i--){

    digitalWrite(buzzer , HIGH);
    delay(1000);
   }
   

   

 

  
}
