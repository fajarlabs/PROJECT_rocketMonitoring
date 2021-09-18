#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <QMC5883LCompass.h>
#include <LoRa.h>
//Connect with pin 18 and 19
#include <TinyGPS.h>
float lat,lon;
TinyGPS gps; // create gps object

// Compas module
QMC5883LCompass compass;

// BMP280 module
Adafruit_BMP280 bmp; // I2C

// ADXL345 module
int ADXL345 = 0x53; // The ADXL345 sensor I2C address

int counter = 0;

void setup() {
  Serial.begin(57600); // connect serial
  Serial.println(F("Serial has been successfully set to 57600!"));

  // Initializing & check GY-270
  compass.init();
  Serial.println(F("Compass initialization was successful!"));

  // Check BMP280
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or try a different address!"));
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  Serial.println(F("BMP280 initialization was successful!"));
  
  // Check ADXL345 & Set high measuring
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  delay(10);

  // Check lora connectifity
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println(F("The sensor accelerator has been successfully activated!"));
}

void loop() {
    // === Read gps data === //
//    while(Serial1.available()){ // check for gps data
//      if(gps.encode(Serial1.read())) { // encode gps data 
//        gps.f_get_position(&lat,&lon); // get latitude and longitude
//        Serial.print("Position: ");
//        //Latitude
//        Serial.print("Latitude: ");
//        Serial.print(lat,6);
//        Serial.print(",");
//        //Longitude
//        Serial.print("Longitude: ");
//        Serial.println(lon,6); 
//      }
//    }
    
    // === Read compass data === //
    compass.read();
    // get azimuth
    byte azimuth = compass.getAzimuth();
    
    Serial.print("Azimuth: ");
    Serial.println(azimuth);
    
    // get direction
    char myArray[3];
    compass.getDirection(myArray, azimuth);
    
    Serial.print("Direction : ");
    Serial.print(myArray[0]);
    Serial.print(myArray[1]);
    Serial.println(myArray[2]);
    
    // get bearing
    byte bearing = compass.getBearing(azimuth);
    
    Serial.print("Bearing: ");
    Serial.println(bearing);
    
    // Return XYZ readings
    int x = compass.getX();
    int y = compass.getY();
    int z = compass.getZ();
    
    Serial.print("XYZ reading: ");
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.print(z);
    Serial.println();    
    
    // === Read barometric data === //
    float temperature = bmp.readTemperature();  // in *C
    float pressure = bmp.readPressure();        // in Pa
    float altitude = bmp.readAltitude(1013.25); // in m, Adjusted to local forecast!

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" Pressure:");
    Serial.print(pressure);
    Serial.print(" Altitude:");
    Serial.println(altitude);
    
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
    
    Serial.print("Xa=");
    Serial.print(X_out);
    Serial.print(" Ya=");
    Serial.print(Y_out);
    Serial.print(" Za=");
    Serial.println(Z_out);

    Serial.print("Sending packet: ");
    Serial.println(counter);
  
    // send packet
    LoRa.beginPacket();
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket();
  
    counter++;

    delay(500);
}
