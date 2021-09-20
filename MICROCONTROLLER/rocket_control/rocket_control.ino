#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <QMC5883LCompass.h>
#include <LoRa.h>
#include <TinyGPS++.h> 
#include <SoftwareSerial.h> 

// Choose two Arduino pins to use for software serial
const int RXPin = 4; //Connect ke TX GPS
const int TXPin = 3; //Connect ke RX GPS
const long GPSBaud = 9600; // gps baudrate

// relay
int const RELAY = A3;
bool is_relay_on = false;

// init timing
const long interval = 333; 
unsigned long previousMillis_QMC5883LCompass = 0;
unsigned long previousMillis_Adafruit_BMP280 = 0;
// unsigned long previousMillis_ADXL345 = 0;
unsigned long previousMillis_Lora = 0;
unsigned long previousMillis_GpsNeo7 = 0;
unsigned long previousMillis_Relay = 0;

// init data state
int state_x = 0;
int state_y = 0;
int state_z = 0;
int state_azimuth = 0;
int state_bearing = 0;
float state_temperature = 0;
float state_pressure = 0;
float state_altitude = 0;
/*
float state_aclx = 0;
float state_acly = 0;
float state_aclz = 0;
*/
String directional = "";

double state_gps_latitude = 0;
double state_gps_longitude = 0;
float state_gps_altitude = 0;
int state_gps_age = 0;
int state_gps_sat_value = 0;
float state_gps_course = 0;
float state_gps_speed = 0;


// init Compas
QMC5883LCompass compass;

// BMP280 module
Adafruit_BMP280 bmp; // I2C

// ADXL345 module
// int ADXL345 = 0x53; // The ADXL345 sensor I2C address

// Baudrate Serial
const long baudrateSerial = 115200;

// Init GPS++
 TinyGPSPlus gps;

// Mmebuat koneksi serial dengan nama "gpsSerial"
 SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  Serial.begin(baudrateSerial); // connect serial
  Serial.println("<<MSG:Serial has been successfully set to "+String(baudrateSerial)+">>");

  //relay 
  pinMode(RELAY, OUTPUT);
  
  // gps serial baudrate
  gpsSerial.begin(GPSBaud);

  // Initializing & check GY-270
  compass.init();
  Serial.println("<<MSG:Compass initialization was successful>>");

  // Check BMP280
  if (!bmp.begin()) {
    Serial.println(F("<<MSG:Could not find a valid BMP280 sensor, check wiring or try a different address>>"));
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  Serial.println("<<MSG:BMP280 initialization was successful>>");

  /*
  // Check ADXL345 & Set high measuring
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  Serial.println("<<MSG:The sensor accelerator has been successfully activated>>");
  delay(10);
  */

  // Check lora connectifity
  if (!LoRa.begin(915E6)) {
    Serial.println("<<ERR:Starting LoRa failed>>");
    while (1);
  }
  Serial.println("<<MSG:The Lora transmitter has been successfully activated>>");
}

void readCompass() {
  int x, y, z, a, b;
  char myArray[3];
  String direct;
  
  compass.read();
  
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();
  a = compass.getAzimuth();
  b = compass.getBearing(a);

  compass.getDirection(myArray, a);
  direct = String(myArray[0])+""+String(myArray[1])+""+String(myArray[2]);

  state_x = x;
  state_y = y;
  state_z = z;
  state_azimuth = a;
  state_bearing = b;
  directional = direct;

  /*
  Serial.print("X: ");
  Serial.print(x);

  Serial.print(" Y: ");
  Serial.print(y);

  Serial.print(" Z: ");
  Serial.print(z);

  Serial.print(" Azimuth: ");
  Serial.print(a);

  Serial.print(" Bearing: ");
  Serial.print(b);

  Serial.print(" Direction: ");
  Serial.print(direct);

  Serial.println();
  */
}

void readBarometricSensor() {
    // === Read barometric data === //
    float temperature = bmp.readTemperature();  // in *C
    float pressure = bmp.readPressure();        // in Pa
    float altitude = bmp.readAltitude(1013.25); // in m, Adjusted to local forecast!

    state_temperature = temperature;
    state_pressure = pressure;
    state_altitude = altitude;

    /*
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" Pressure:");
    Serial.print(pressure);
    Serial.print(" Altitude:");
    Serial.println(altitude);
    */
}

/*
void readAcceleratorMeter() {
    // === Read accelerometer data === //
    Wire.beginTransmission(ADXL345);
    Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
    float X_out = ( Wire.read()| Wire.read() << 8); // X-axis value
    X_out = X_out/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
    float Y_out = ( Wire.read()| Wire.read() << 8); // Y-axis value
    Y_out = Y_out/256;
    float Z_out = ( Wire.read()| Wire.read() << 8); // Z-axis value
    Z_out = Z_out/256;

    state_aclx = X_out;
    state_acly = Y_out;
    state_aclz = Z_out;

    // Serial.print("Xa=");
    // Serial.print(X_out);
    // Serial.print(" Ya=");
    // Serial.print(Y_out);
    // Serial.print(" Za=");
    // Serial.println(Z_out);
}
*/


void loraSendData(String data) {
    // send packet
    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket();
    Serial.println("<<MSG:Package has been sent>>");
}

String getBuildData() {
    // x,y,z,azimuth,bearing,directional, temperature,pressure,altitude,gps latitude,gps longitude,gps age, gps altitude, gps sat value, gps course, gps speed
    String delimiter = ",";
    String result = "<<DATA:";
    result += String(state_x);
    result += delimiter;
    result += String(state_y);
    result += delimiter;
    result += String(state_z);
    result += delimiter;
    result += String(state_azimuth);
    result += delimiter;
    result += String(state_bearing);
    result += delimiter;
    result += directional;
    result += delimiter;
    result += String(state_temperature);
    result += delimiter;
    result += String(state_pressure);
    result += delimiter;
    result += String(state_altitude);
    result += delimiter;
    /*
    result += String(state_aclx);
    result += delimiter;
    result += String(state_acly);
    result += delimiter;
    result += String(state_aclz);
    result += delimiter;
    */
    result += String(state_gps_latitude,6);
    result += delimiter;
    result += String(state_gps_longitude,6);
    result += delimiter;
    result += String(state_gps_age);
    result += delimiter;
    result += String(state_gps_altitude,2);
    result += delimiter;
    result += String(state_gps_sat_value);
    result += delimiter;
    result += String(state_gps_course, 2);
    result += delimiter;
    result += String(state_gps_speed, 2);
    result += ">>";

    return result;
}

void readGPS() {
  // smartdelay
  while (gpsSerial.available() > 0) gps.encode(gpsSerial.read());

  // read data
  if (gps.location.isValid()){
    state_gps_latitude = gps.location.lat();
    state_gps_longitude = gps.location.lng();
    state_gps_age = gps.location.age();
  } else {
    Serial.println("<<ERR:Location not available>>");
  }
      
  if(gps.altitude.isValid()){
    state_gps_altitude = gps.altitude.meters();
  }
  
  if(gps.satellites.isValid()){
    state_gps_sat_value = gps.satellites.value();
  }
  
  if(gps.course.isValid()){
    state_gps_course = gps.course.deg();
  }
  
  if(gps.speed.isValid()){
    state_gps_speed = gps.speed.kmph();
  }
}

void loop() {
    unsigned long currentMillis = millis();

    // timing GPS
    if (currentMillis - previousMillis_Relay >= interval) {
        previousMillis_Relay = currentMillis;
        /*
        if(is_relay_on == false){
          is_relay_on = true;
          digitalWrite(A3, HIGH);
        } else {
          is_relay_on = false;
          digitalWrite(A3, LOW);
        }
        */
    }

    // timing GPS
    if (currentMillis - previousMillis_GpsNeo7 >= interval) {
        previousMillis_GpsNeo7 = currentMillis;
        readGPS();
    }

    // timing compass
    if (currentMillis - previousMillis_QMC5883LCompass >= interval) {
        previousMillis_QMC5883LCompass = currentMillis;
        readCompass();
    }

    // timing barometric sensor
    if (currentMillis - previousMillis_Adafruit_BMP280 >= interval) {
        previousMillis_Adafruit_BMP280 = currentMillis;
        readBarometricSensor();
    }

    /*
    // timing accelerator meter
    if (currentMillis - previousMillis_ADXL345 >= interval) {
        previousMillis_ADXL345 = currentMillis;
        readAcceleratorMeter();
    }
    */

    // timing sending lora
    if (currentMillis - previousMillis_Lora >= interval) {
        previousMillis_Lora = currentMillis;
        loraSendData(getBuildData());
    }
}
