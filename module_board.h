// Define I2C Lines
// Define MOSI Lines
#pragma once


namespace I2C {
  uint8_t write_byte_data(byte index, byte addr, byte val){
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

