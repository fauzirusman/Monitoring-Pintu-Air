#include <ESP8266WiFi.h>
#include <Servo.h>
#define triggerPin  D3
#define echoPin     D5
int sense_Pin = 0;
int value = 0;
Servo servo;


void setup() {

  
  
  Serial.begin (9600);
  servo.attach(13); //D7
  servo.write(0);
  delay(2000);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(5, OUTPUT);

    servo.attach(13); //D7
  servo.write(0);
  delay(2000);
}


void loop() {

  
  
  long duration, jarak;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = (duration/2) / 29.1;
  Serial.print("jarak benda: ");
  Serial.print(jarak);
  Serial.println(" cm");
  delay(1000);

  Serial.print("Moisture Level: ");
  value= analogRead(sense_Pin);
  value= value/10;
  Serial.println(value);
  delay(1000);

  if(jarak<10)
  {
    servo.write(270 );
    delay(1000);
    servo.write(0);
    delay(1000);
    }

  else
  {
    digitalWrite(5, HIGH);
    }


 
  
 
  
}
