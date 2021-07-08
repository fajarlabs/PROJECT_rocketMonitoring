# project03-rocketMonitoring
Riset penelitian pergerakan roket

# Wiring Diagram
<a href="https://ibb.co/6s905ZT"><img src="https://i.ibb.co/5cphV9S/rocket-launcher-1.png" alt="rocket-launcher-1" border="0"></a><br />

# Components
- Atmega / STM TX & RX module <Br />
- FPV TX-RX 5.8Ghz 600mW Range 1-3KM estimated <br />
- RF - SX1278 LoRa Module <br />
- Video Capture to USB <Br />
- BMP280 (altitude, temperature, pressure) <br />
- ADXL345 (three axis accelation gravity) + GY-271 HMC58831 (magnetometer compas) for azimuth <br />
- GPS Module <br />

# How it Works
Untuk transmisi video terpisah karena dibutuhkan data berupa video stream setelah itu video akan di terima dalam bentuk audio video analog dan di konversi agar audio video tersebut bisa di gunakan / digabungkan kedalam program, jarak transmisi video +-1-3KM. <br /><br />
Untuk transmisi data menggunakan LoRa dengan jarak +-1-3KM tanpa ada halangan. Diterima oleh module Lora Receiver Module atau menggunakan Gateway (jika dimungkinkan transmisi jarak jauh dengan menggunakan protocol MQTT) Data akan dibuat sedemikian rupa agar berbentuk kecil sehingga data yang di transmit lebih ringan. Data akan diparsing setelah itu data akan di masukkan kedalam program untuk di analisa dan dimasukkan kedalam dashboard.

# Code
Bahasa pemrograman yang digunakan : <br />
- C/C++ untuk minsys & sensor<Br />
- Python untuk proses parsing data & analisis<br />
- Javascript / Nodejs untuk membuat web interaktif<br />
- GUI desktop/mobile apps/ komputasi berat, bisa menggunakan Java / Go untuk proses yang bersifat konkuren.<Br />
- DB MySQL/SQLite/Postgre<br />
