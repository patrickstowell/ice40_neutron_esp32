// Define I2C Lines
// Define MOSI Lines
#pragma once


namespace I2C2 {
  //Set pins for I2C2
  #define I2C2_SDA_PIN 32
  #define I2C2_SCL_PIN 33

  TwoWire bus = TwoWire(1); //I2C2 bus
  int i = 0;
  void onRequest() {
    bus.print(i++);
    bus.print(" Packets.");
    Serial.println("onRequest");
    Serial.println(i);
  }

void onReceive(int len) {
  Serial.printf("onReceive[%d]: ", len);
  while (bus.available()) {
    Serial.print(bus.read(), DEC);
  }
  Serial.println();
}

void begin() {
  Serial.println("Starting TwoWire Interface");
  bus.onReceive(onReceive);
  bus.onRequest(onRequest);
  bus.setPins(I2C2_SDA_PIN, I2C2_SCL_PIN);
  // bus.begin(0x55);
  bus.begin(0x60);
}

}

namespace I2C {


  bool active = false;
  void begin(){
    if (active) return;
    active = true;
    Wire.begin(21,22);

  }

  uint8_t write_byte_data(byte index, byte addr, byte val){
    Serial.print("Sending : ");
    Serial.print(index);
    Serial.print(" : ");
    Serial.print(addr);
    Serial.print(" : ");
    Serial.println(val);

    Wire.beginTransmission(index); // transmit to device #4
    // delay(50);
    Wire.write(addr); // sends five bytes
    // delay(50);
    byte oval = Wire.write(val); // sends five bytes
    Wire.endTransmission(); // stop transmitting
    // delay(50);
    return val;
  }

  uint8_t read_byte_data(byte index, byte addr){
    Wire.beginTransmission(index); // transmit to device #4
    Wire.write(addr); // sends one byte for address
    Wire.endTransmission(true); // stop transmitting
    Wire.requestFrom(index,1);
    // Wire.write(addr); // sends one byte for address
    int oval = Wire.read();
    Wire.endTransmission(); // stop transmitting

    // Wire.requestFrom(index,1);
    // int oval = Wire.read();

    // Wire.beginTransmission(index); // transmit to device #4
    // Wire.write(addr); // sends one byte for address
    // Wire.endTransmission(); // stop transmitting
    // Wire.requestFrom(index,1);
    // oval = Wire.read();

    return oval;
  }


};


namespace BOARD {
namespace SPI1 {

}
}






