# Rocket Monitoring
Riset penelitian pergerakan roket

# Wiring Diagram
<a href="https://ibb.co/6s905ZT"><img src="https://i.ibb.co/5cphV9S/rocket-launcher-1.png" alt="rocket-launcher-1" border="0"></a><br />
# Schematic
```shell
Sensor accelerator ADXL345 di lepas, dijadikan satu di sensor kompas
```
<a href="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/Schematic_PERISAI_2021-09-18.png?raw=true"><img width="600" height="400"  src="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/Schematic_PERISAI_2021-09-18.png?raw=true" alt="schematic" border="0"></a><br />
# Desain
<a href="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/VIEW_2D.png?raw=true"><img width="400" height="400" src="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/VIEW_2D.png?raw=true" alt="schematic2d" border="0"></a>
<a href="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/VIEW_3D.png?raw=true"><img width="400" height="400"  src="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/VIEW_3D.png?raw=true" alt="schematic3d" border="0" width="700" height="400" ></a><br />
# Physical
<a href="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/WhatsApp%20Image%202021-09-18%20at%2012.25.23%20PM.jpeg?raw=true" ><img src="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/DESAIN_PCB/WhatsApp%20Image%202021-09-18%20at%2012.25.23%20PM.jpeg?raw=true" width="500" height="400" /></a>
<a href="https://user-images.githubusercontent.com/5867781/134273984-3a0263b5-d8f7-4227-9a46-c7460e715129.png" ><img src="https://user-images.githubusercontent.com/5867781/134273984-3a0263b5-d8f7-4227-9a46-c7460e715129.png" width="300" height="400" /></a>

# Receive Data
Format data : <br />
```shell
<<DATA:compas_x, compas_y, compas_z, azimuth, bearing, direction, temperature, pressure, altitude, gps latitude, gps longitude, gps age, gps altitude, gps sat value, gps course, gps speed, rssi>>

<<DATA:-1428,-393,205,196,8,  S,31.95,100289.39,86.58,-6.367715,106.800340,535,119.80,8,0.00,2.41,-62>>
```
Show sample data <a href="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/receive-data.log">View</a>
<br />
<b> Receive monitor </b><br />
<a href="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/Screenshot%202021-09-20%20030500.jpg?raw=true" ><img src="https://github.com/fajarlabs/PROJECT_rocket_monitoring/blob/main/Screenshot%202021-09-20%20030500.jpg?raw=true" width="700" height="400" /></a><br />
<b> Transmit monitor </b><br/>
![image](https://user-images.githubusercontent.com/5867781/133961623-4fc6a201-7a79-41c7-88d8-905e20c020d2.png)

# Monitoring dashboard
![image](https://user-images.githubusercontent.com/5867781/134752366-1af12d3e-6900-4ee4-85ee-ed9a465d40fd.png)



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
1.) Dev board lora 915 2 Buah : https://www.tokopedia.com/cosmic-iot/lora-arduino-shield-dragino-clone-915mhz-915-mhz-rfm96-rfm95-rfm-95-96?refined=true&src=topads&whid=0 <br />
    Digunakan untuk transmit data command dari bawah ke roket, untuk opsi ini dipakai yang versi shield besar, karena lebih cepat untuk proses development atau bisa juga menggunakan dragino lora mini 915Mhz cuma di toko jarang. <br />
2.) Lora 1276 Transreceiver 1 Buah : https://www.tokopedia.com/hwthinker/modul-sx1276-wireless-transceiver-lora-915mhz-915-mhz-long-range?whid=0 <br />
3.) Antena Lora (tergantung kondisi hanya buat riset atau diganti nanti antena di roketnya) : https://www.tokopedia.com/cosmic-iot/antenna-lora-sigfox-915-mhz-915mhz-sma-male-3db-3-db-omni-directional?src=topads<br />
4.) Lora chip breakout 1 Buah : https://www.tokopedia.com/cosmic-iot/lora-chip-breakout-pcb-untuk-rfm95-rfm96-sx1276-rfm-95-96-tanpa-chip?refined=true&src=topads&whid=0 <br />
5.) Kamera FPV : https://www.tokopedia.com/anekahoby/c4-fpv-ccd-camera-700tvl-mini-cmos-camera-2-8-mm-for-rc-quadcopter?whid=0 <br />
6.) Av TransmitReceive Kamera : https://www.tokopedia.com/anekahoby/ts832-rc832-48ch-fpv-5-8ghz-600mw-wireless-av-transmitter-receiver <br />
7.) BMP280 sensor : https://www.tokopedia.com/greatitacc/bmp280-3-3v-digital-barometric-pressure-altitude-sensor?src=topads <br />
8.) ADXL sensor : https://www.tokopedia.com/greatitacc/gy-291-adxl345-3-axis-sensor-akselerasi-module?src=topads Untuk coba cari pengganti azzimuth sensor<br />
9.) Magnetometer sensor : https://www.tokopedia.com/microlife/gy-271-hmc58831-magnetometer-compass-module?whid=0 <br />
10.) GPS Module neo6mv2 : https://www.tokopedia.com/rajacell/ublox-neo-6m-gps-module-neo6mv2-with-flight-control-for-arduino?refined=true&whid=0 <br />
11.) Mega duino Expansion board : https://www.tokopedia.com/bustan/arduino-mega-breadboard-v3-project-proto-board-prototype-shield?whid=0 <br />
12.) Ardu Mega : https://www.tokopedia.com/bustan/arduino-mega-2560-r3-ch340g-ch340-ch-340-340g-include-usb-data-cable <br />
    module ini dipakai untuk membaca sensor-sensor yang dikirim ke gateway melalui lora. <br />
13.) Arduino untuk dev board command dari bawah dan posisi di roket 2 buah : https://www.tokopedia.com/freelab/arduino-uno-r3-clone-smd?whid=0<br />
ini dipakai untuk dev lora command <br />









