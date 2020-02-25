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

sebenarnya dari tutorial yang saya baca di internet, disitu ditunjukkan bahwa seharusnya sensor ini dihubungkan ke output bertegangan 3,3v dari ESP, hanya saja pada praktek ini hasilnya malah 'null' sehingga saya ubah ke output bertegangan 5v dan Alhamdulillah berjalan dengan baik.

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

## Source code

## Kendala/Galat

## Dokumentasi 
https://photos.app.goo.gl/aiWfRUJMFGHCJBV16
