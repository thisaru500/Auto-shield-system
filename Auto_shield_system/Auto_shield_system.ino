#include <SoftwareSerial.h>
#include<Servo.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;
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
   float pixels[64];
   float temp_limit = 50.0;
   
void setup() {
   
  yakada.attach(servo);
  Serial.begin(9600);  
  sim900.begin(9600);
  amg.begin();  
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
}

void loop() {
   
 int sensor_read =  analogRead(smoke_sensor);
 Serial.print(sensor_read);
 int flame_value = digitalRead(flame);
 Serial.print(flame_value);

  amg.readPixels(pixels);
  bool over_temp = false;
  for (int i = 0; i < 64; i++) {
    if (pixels[i] > temp_limit) {
      over_temp = true;
      break;
    }
  }

 if (sensor_read >= safety_lim || flame_value == 1 || over_temp) 
 { 
   Sim900a();
   servo1();
   digitalWrite(relay , HIGH);//for turn off main switch
   for(int i = 50; i>0 ; i--){

    digitalWrite(buzzer , HIGH);
    delay(1000);
    digitalWrite(ledset , HIGH);
   
 }
 }
 

   else {
       Serial.print("No issue continue your work");
    }
   }
   

   

 

  
