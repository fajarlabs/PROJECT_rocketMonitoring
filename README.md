# Rocket Monitoring
Riset penelitian pergerakan roket

# Wiring Diagram
<a href="https://ibb.co/6s905ZT"><img src="https://i.ibb.co/5cphV9S/rocket-launcher-1.png" alt="rocket-launcher-1" border="0"></a><br />

# Components
- Atmega / STM TX & RX module <Br />
- FPV TX-RX 5.8Ghz 600mW Range 1-3KM estimated <br />
- RF - SX1276 LoRa Module <br />
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

# Buy Parts
Arduino Lily 2 Buah (RX+TX) : https://www.tokopedia.com/rajacell/arduino-lilypad-lily-pad-328-atmega328-5v-16mhz-development-board?whid=0 <br />
Lora 1276 Transreceiver 3 Buah (1 RX, 1TX command) 1 TX data : https://www.tokopedia.com/hwthinker/modul-sx1276-wireless-transceiver-lora-915mhz-915-mhz-long-range?whid=0 <br />
Antena Lora (tergantung kondisi hanya buat riset atau diganti nanti antena di roketnya) : https://www.tokopedia.com/cosmic-iot/antenna-lora-sigfox-915-mhz-915mhz-sma-male-3db-3-db-omni-directional?src=topads<br />
Lora chip breakout 3 Buah : https://www.tokopedia.com/cosmic-iot/lora-chip-breakout-pcb-untuk-rfm95-rfm96-sx1276-rfm-95-96-tanpa-chip?refined=true&src=topads&whid=0 <br />
Kamera FPV : https://www.tokopedia.com/anekahoby/c4-fpv-ccd-camera-700tvl-mini-cmos-camera-2-8-mm-for-rc-quadcopter?whid=0 <br />
TransmitReceive Kamera : https://www.tokopedia.com/anekahoby/ts832-rc832-48ch-fpv-5-8ghz-600mw-wireless-av-transmitter-receiver <br />
BMP280 sensor : https://www.tokopedia.com/greatitacc/bmp280-3-3v-digital-barometric-pressure-altitude-sensor?src=topads <br />
ADXL sensor : https://www.tokopedia.com/greatitacc/gy-291-adxl345-3-axis-sensor-akselerasi-module?src=topads Untuk coba cari pengganti azzimuth sensor<br />
Magnetometer sensor : https://www.tokopedia.com/microlife/gy-271-hmc58831-magnetometer-compass-module?whid=0 <br />
GPS Module neo6mv2 : https://www.tokopedia.com/rajacell/ublox-neo-6m-gps-module-neo6mv2-with-flight-control-for-arduino?refined=true&whid=0 <br />
Mega duino Expansion board : https://www.tokopedia.com/bustan/arduino-mega-breadboard-v3-project-proto-board-prototype-shield?whid=0 <br />
Ardu Mega : https://www.tokopedia.com/bustan/arduino-mega-2560-r3-ch340g-ch340-ch-340-340g-include-usb-data-cable <br />









