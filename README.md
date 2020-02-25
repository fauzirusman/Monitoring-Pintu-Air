# Monitoring-Pintu-Air

## Pendahuluan
Alhamdulillah wa syukurillah, sebelumnya terima kasih telah berkenan untuk membaca dokumentasi dari program yang saya kerjaakan secara marathon, ya karena sejujurnya estimasi waktu yang ada hanyalah 6 jam hehehehe. Jadi ceritanya itu projek ini merupakan test praktek buat masuk jadi aslab divisi IoT laboratorium mobile communication, demikianpun alasan ini ditulis hehehe, tapi ga masalah... selamat menikmati

## Story
Dalam kasus skenario ini bayangkan kita berada di daereah dekat sungai. Sebagai petugas yang bertanggung jawab atas kelancaran irigasi anda pastinya harus mengawasi dan memonitoring debit air dan terlebih saat sedang musim hujan karena ditakutkan terjadi banjir/peluapan kanal. Oleh karena itu hal yang kita butuhkan dalam kasus ini adalah alat yang bisa menampilkan kondisi secara realtime untuk keperluan monitoring. Tak sampai disitu, alat tersebut harus terintegrasi dengan server di Internet supaya bisa diakses oleh pusat untuk keperluan pengambilan kebijakan seperti tindakan preventif yang tepat.



## Pemasangan Hardware
Baiklah, untuk hardware yang saya gunakan meliputi berikut
* WeMos D1 Mini based on ESP8266
* Soil Moisture Sensor
* Ultrasonic Sensor
* Motor Servo
* Buzzer
* Breadboard
* Kaki - kaki pin & Kabel jumper

Oke setelah mengetahui Hardware yang digunakan sekarang saya akan coba menjelaskan pemasangan per-bagian.

### WeMos D1 Mini based on ESP8266
Sebenarnya jenis ESP8266 ini sama seperti lainya, hanya saja unik karena memiliki output daya baik **3,3v** seperti NodeMCU dan **5v** seperti arduino. Pada awalnya tidak ada kendala, dan board dengan cepat bisa langsung terdeteksi oleh laptop di Device Manager. Hanya ketika pemasangan kabel jumper agak kompleks akhirnya ada beberapa pin yang kendor dan menyebabkan malfungsi. Nah oleh karena itu akhirnya saya hubungkan dengan beberapa kaki dan di solder. Alhamdulillah setelah hal tersebut untuk alat ini tidak ada kenadala yang berarti.


### Ultrasonic Sensor
Jadi ini adalah sensor yang menggunakan kemampuan ultrasonik dari kelelawar, umumnya digunakan untuk mendeteksi jarak, namun dalam beberapa proyek juga bisa digunakan untuk pemetaan tempat terutama yang minim cahaya.

Nah, untuk proyek ini saya menggunakan sensor ini untuk mengetahui level ketinggian air. 
berikut rangkaian konektivitas Ultrasonic sensor ke ESP8266

| Nama Pin Ultrasonik  | Pin ESP8266 |
| -----                | --- |
| VCC                  | 5v  |
| Gnd                  | Gnd  |
| Echo                 | D5 (GPIO 14)  |
| Trig                 | D3 (GPIO 0)  |

sebenarnya dari tutorial yang saya baca di internet, disitu ditunjukkan bahwa seharusnya sensor ini dihubungkan ke output bertegangan 3,3v dari ESP, hanya saja pada praktek ini hasilnya malah `null` sehingga saya ubah ke output bertegangan 5v dan Alhamdulillah berjalan dengan baik.

### Soil Moisture Sensor
Sensor ini berfungsi untuk mendeteksi parameter kelembapan yang ada di tanah/air. Fungsi ini dalam kasus dimanfaatkan untuk mengetahui apakah air sedang dalam kondisi stabil atau sedang banjir.

sedangkan untuk rangkaian konektivitasnya:
| Nama Pin Soil Moisture  | Pin ESP8266 |
| -----                   | --- |
| VCC                     | 5v  |
| Gnd                     | Gnd |
| Analog                  | A0  |

### Motor Servo
Motor servo adalah aktuator yang digunakan sebagai pembuka pintu air setelah beberapa kondisi yang diputuskan berdasarkan rangsangan dari 2 sensor diatas.

sedangkan untuk rangkaian konektivitasnya:
| Nama Pin Motor Servo    | Pin ESP8266 |
| -----                   | --- |
| VCC                     | 5v  |
| Gnd                     | Gnd |
| Data                    | D7 (GPIO 13)  |


## Instalasi Library yang dibutuhkan
Disini saya hanya akan menjelaskan library tambahan yang tidak ada dalam paket instalasi Arduino IDE.

### ESP8266 by ESP Community
Pertama buka preference, di file -> preference 
atau juga bisa menggunakan shortcut `Ctrl + comma`

setelah itu paste kan link berikut
` http://arduino.esp8266.com/stable/package_esp8266com_index.json ` di kolom Additional Board Manager

setelah itu buka board manager lalu cari ESP8266, setelah ketemu lalu di install

### Antares HTTP
untuk tutorial resmi dari antares bisa dilihat [disini](https://www.antares.id/en/esp-library-example.html)
atau langsung download library nya juga bisa [disini](https://github.com/antaresdocumentation/antares-esp8266-http)
lalu file .zip yang telah di unduh dapat di install melalui library manager


## Source code
Disini ada 2 buah source code yang saya dokumentasikan, yakni yang berhasil dijalankan tanpa menambahkan fungsi atau koneksi dengan antares, dan yang gagal yakni yang saya coba dengan antares

### **Tanpa Antares**

```C
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
```

### **Dengan Antares**
```C
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
```

## Kendala/Galat
Sejauh ini ada 2 galat yang terjadi

1. Pin WeMos
2. Konektivitas dengan antares

untuk kendala dengan pin WeMos Alhamdulillah dapat terselesaikan setelah disolder dengan kaki tambahan, sedangkan untuk kendala yang belum teratasi adalah konektivitas dengan antares. 

## Dokumentasi gambar
https://photos.app.goo.gl/aiWfRUJMFGHCJBV16
