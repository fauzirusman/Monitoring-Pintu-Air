#include <AntaresESP8266HTTP.h>
#include <ArduinoJson.h>
#define ACCESSKEY "0866a0a548e37d60:b09498fc46b55f18"       // Ganti dengan access key akun Antares anda
#define WIFISSID "Malikkul"         // Ganti dengan SSID WiFi anda
#define PASSWORD "Sektakpikirsek"     // Ganti dengan password WiFi anda

#define projectName "PintuAir"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Ultrasonic" 

AntaresESP8266HTTP antares(ACCESSKEY);    // Buat objek antares

#include <ESP8266WiFi.h>
#include <Servo.h>
#define triggerPin  D3
#define echoPin     D5
int sense_Pin = 0;
int value = 0;
Servo servo;


void setup() {

  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  
  Serial.begin (9600);
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  
  servo.attach(13); //D7
  servo.write(0);
  delay(2000);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);

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

  if(jarak>10)
  {
    servo.write(270 );
    delay(1000);
    servo.write(0);
    delay(1000);
    }

  else
  {
    digitalWrite(BUILTIN_LED, HIGH);
    }

 antares.add("Ultrasonic", jarak);


 antares.send(projectName, deviceName);
  delay(1000);

 
  
 
  
}
