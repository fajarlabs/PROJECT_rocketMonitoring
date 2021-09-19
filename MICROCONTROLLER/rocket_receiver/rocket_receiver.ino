#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("<<MSG:The receiver is running>>");

  if (!LoRa.begin(915E6)) {
    Serial.println("<<ERR:Starting LoRa failed>>");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  String str = "";
  if (packetSize) {
    while (LoRa.available()) {
      str += String((char)LoRa.read());
    }
    str.replace(">>", ",");
    str += LoRa.packetRssi();
    str += ">>";
    Serial.println(str);
  }
}
