#pragma once

#include "fw.h"

namespace FLASH {

#define OP_BYTE_OR_PAGE_PROGRAM (0x02)
#define OP_READ_ARRAY_03 (0x03)
#define OP_READ_ARRAY_0B (0x0b)
#define OP_WRITE_ENABLE (0x06)
#define OP_WRITE_DISABLE (0x04)
#define OP_BLOCK_ERASE_4KB (0x20)
#define OP_BLOCK_ERASE_32KB (0x52)
#define OP_BLOCK_ERASE_64KB (0xd8)
#define OP_CHIP_ERASE_60 (0x60)
#define OP_CHIP_ERASE_C7 (0xc7)
#define OP_READ_STATUS_REGISTER_BYTE_1 (0x05)
#define OP_READ_STATUS_REGISTER_BYTE_2 (0x35)
#define OP_READ_MANUFACTURER_AND_DEVICE_ID (0x9f)
#define OP_READ_DEVICE_ID (0x90)

#define MANUFACTURER_ID (0x1f)
#define DEVICE_ID_PART_1 (0x85)
#define DEVICE_ID_PART_2 (0x01)
#define DEVICE_CODE (0x13)
#define STATUS_REGISTER_WEL_MASK (1U << 1)


#define MAX_FREQUENCY (1200000)

#define CFG_SS   15 // WAS PIN 5 //26 // PIN 32, GPIO.26
#define CFG_SCK  18 //27 // PIN 36, GPIO.27
#define CFG_SI   19 // PIN 31, GPIO.22
#define CFG_SO   23 //23 // PIN 33, GPIO.23
#define CFG_RST  0 //25 // PIN 37, GPIO.25
#define CFG_DONE 4 //21 // PIN 29, GPIO.21
#define CFG_HOLD 21 //
#define CFG_ENABLE 15

const int  CS_AT25SF081   = 10;             // Flash Memory Chip Select - Active Low
const int  holdPin        = 9;              // HOLD Pin - Active Low
 
SPISettings AT25SF081(80000, MSBFIRST, SPI_MODE0);
SPISettings AT25SF081_readonly(1600000, MSBFIRST, SPI_MODE0);

bool spi_readonly = true;

SPIClass * hspi = NULL;

void flash_spi_start();
void flash_spi_end();

void flash_spi_read_to_buffer();
void flash_spi_operation(byte val);
void flash_spi_read_to_buffer(char* buffer, uint32_t custom_length);
void flash_spi_address(int writeAddress);
void ice40_setup(){

  pinMode(CFG_SS,   OUTPUT);
  pinMode(CFG_SCK,  OUTPUT);
  pinMode(CFG_SI,   INPUT);
  pinMode(CFG_SO,   OUTPUT);
  pinMode(CFG_RST,  OUTPUT);
  pinMode(CFG_DONE, INPUT);
  
  digitalWrite(CFG_SS,  HIGH);
  digitalWrite(CFG_SCK, LOW);
  digitalWrite(CFG_SO,  LOW);
  digitalWrite(CFG_RST, LOW);
  delay(500);

  hspi = new SPIClass(VSPI);
  hspi->begin(CFG_SCK, CFG_SO, CFG_SI, CFG_SS); //SCLK, MISO, MOSI, SS
  pinMode(hspi->pinSS(), OUTPUT); 

  digitalWrite         (CFG_SS, LOW);
  delay(500);
  digitalWrite         (CFG_SS, HIGH); 

  delayMicroseconds(10000);

  flash_spi_start();
  flash_spi_operation(0xAB);
  flash_spi_end();
  delay(2000);

  char ids[3];
  flash_spi_start();
  flash_spi_operation(OP_READ_MANUFACTURER_AND_DEVICE_ID); //#hspi->transfer(0xFF);
  flash_spi_read_to_buffer(ids, 3);
  flash_spi_end();
  Serial.print(ids[0], HEX);
  Serial.print(ids[1], HEX);
  Serial.println(ids[2], HEX);
  delay(500);

}

void flash_spi_start(){
  if (spi_readonly) { hspi->beginTransaction(AT25SF081_readonly); }
  else { hspi->beginTransaction(AT25SF081); }
  digitalWrite(CFG_SS, LOW);
  // delayMicroseconds(50);
}

void flash_spi_operation(byte val){
  hspi->transfer(val);
}

void flash_spi_address(int writeAddress){
  hspi->transfer ((writeAddress & 0xFF0000) >> 16);  // Byte address - MSB Sig Byte
  hspi->transfer ((writeAddress & 0x00FF00) >>  8);  // Byte address - MID Sig Byte
  hspi->transfer ((writeAddress & 0x0000FF) >>  0);  // Byte address - LSB Sig Byte 
}

char flash_spi_read(){
  // delayMicroseconds(1);
  return hspi->transfer(0xFF);
}


void flash_spi_read_to_buffer(char* buffer, uint32_t custom_length){
  for (uint32_t i = 0; i < custom_length; i++){
    buffer[i] = flash_spi_read();
  }
}

char flash_spi_write(byte c){
  return hspi->transfer(c);
}

void flash_spi_write_from_buffer(char* buffer, uint32_t custom_length){
  for (uint32_t i = 0; i < custom_length; i++){
    flash_spi_write(buffer[i]);
  }
}

void flash_spi_end(){
  // delayMicroseconds(50);
  digitalWrite(CFG_SS, HIGH);
  hspi->endTransaction();
}


void ice40_release_flashbitbang(){
	pinMode(CFG_SCK,  INPUT);
	pinMode(CFG_SO,   INPUT);
	pinMode(CFG_SI,   INPUT);
  pinMode(CFG_SS,  INPUT);

	digitalWrite(CFG_RST, LOW);
  delay(100);

  digitalWrite(CFG_RST, HIGH);
  delay(100);

	// Wait for FPGA to start reading the SROM
	int i;
	for (i = 0; i < 100; i++) {
    delay(10);
    Serial.println(digitalRead(CFG_DONE));
	  if (digitalRead(CFG_DONE) == HIGH) {
	    break;
    }
  }

	if (digitalRead(CFG_DONE) != HIGH) {
		Serial.printf("WARNING: cdone is low, FPGA did probably not SROM input\n");
	} else {
    pinMode(CFG_DONE,OUTPUT);
    digitalWrite(CFG_DONE, 1);
  }
  delay(1000);
}



  char buffer[256];

void flash_fpga() {
  // put your setup code here, to run once:
  ice40_setup();
  delay(2000);

  flash_spi_start();
  flash_spi_operation(0xAB);
  flash_spi_end();
  delay(2000);

  char ids[3];
  flash_spi_start();
  flash_spi_operation(OP_READ_MANUFACTURER_AND_DEVICE_ID); //#hspi->transfer(0xFF);
  flash_spi_read_to_buffer(ids, 3);
  flash_spi_end();
  Serial.print(ids[0], HEX);
  Serial.print(ids[1], HEX);
  Serial.println(ids[2], HEX);
  delay(500);

  // Check
  Serial.print("FW Check : [");

  bool change_found = false;
  for (int i = 0; i < 4095; i++){
    if (i*256  > hardware_bin_len) break;

    if (i % 32 == 0){
      Serial.print("#");
    }

    flash_spi_start();
    flash_spi_operation(OP_READ_ARRAY_03);
    flash_spi_address(i*256);
    flash_spi_read_to_buffer(buffer, 256);
    flash_spi_end();

    for (int j = 0; j < 256; j++){
      int index = i*256 + j;
      if (index < hardware_bin_len-24) {
              
        if (buffer[j] != hardware_bin[index]){
          change_found = 1;

          // Serial.print("CHECK : ");
          // Serial.print(index);
          // Serial.print(" -> ");
          // Serial.print(int(buffer[j]));
          // Serial.print(" vs ");
          // Serial.println(hardware_bin[index]);  
          break;
        }
      }
    }
    if (change_found) break;
  }

  Serial.println("]");


  if (!change_found){
    Serial.println("FW Status : Valid");
    ice40_release_flashbitbang();
    return;
  } else {
    Serial.println("FW Status : Changed");
    spi_readonly = false;
  }



  flash_spi_start();
  flash_spi_operation(OP_WRITE_ENABLE);
  flash_spi_end();
  delay(100);

  flash_spi_start();
  flash_spi_operation(OP_CHIP_ERASE_60);
  flash_spi_end();
  Serial.println("Erasing: ...");
  delay(20000);

  flash_spi_start();
  flash_spi_operation(OP_WRITE_ENABLE);
  flash_spi_end();
  delay(100);
  int status;

  flash_spi_start();
  flash_spi_operation(OP_READ_STATUS_REGISTER_BYTE_1);
  status = flash_spi_read();
  flash_spi_end();
  // Serial.print("STATUS - ");
  // Serial.println(status, HEX);

  int errorcounts = 0;
  Serial.print("Flashing : [");
  for (int i = 0; i < 4095; i++){

    flash_spi_start();
    flash_spi_operation(OP_WRITE_ENABLE);
    flash_spi_end();
    delay(10);

    if (i % 32 == 0){
      Serial.print("#");
    }
    // Serial.print("PAGE : ");
    // Serial.print(i);
    // Serial.print(" - ");
    // Serial.println(errorcounts);

    for (int j = 0; j < 256; j++){
      buffer[j] = 0;
    }
    bool buffer_updated = false;
    int size_to_GO =0 ;
    for (int j = 0; j < 256; j++){
      int index = i*256 + j;
      if (index < hardware_bin_len) {
        buffer[j] = hardware_bin[i*256+j];
        buffer_updated = true;
        size_to_GO++;
      } else buffer[j] = 0xFF;
    }

    if (!buffer_updated) break;

    if (size_to_GO < 256) size_to_GO += 1;

    flash_spi_start();
    flash_spi_operation(OP_BYTE_OR_PAGE_PROGRAM);
    flash_spi_address(i*256);
    flash_spi_write_from_buffer(buffer, size_to_GO);
    flash_spi_end();


    flash_spi_start();
    flash_spi_operation(OP_READ_STATUS_REGISTER_BYTE_1);
    status = flash_spi_read();
    flash_spi_end();


    flash_spi_start();
    flash_spi_operation(OP_READ_ARRAY_03);
    flash_spi_address(i*256);
    flash_spi_read_to_buffer(buffer, 256);
    flash_spi_end();

    for (int j = 0; j < 256; j++){
      if (i*256+j > hardware_bin_len) break;
      
      if (hardware_bin[i*256+j] != buffer[j]) {
        if (errorcounts > 2){
        Serial.print(i);
        Serial.print(" ");
        Serial.print("ERROR : ");
        Serial.print(i*256+j);
        Serial.print(" : ");
        Serial.print(hardware_bin[i*256+j], HEX);
        Serial.print(" - ");
        Serial.println(buffer[j], HEX);
        }
        errorcounts++;
      }
    }
    if (errorcounts > 10) {
      while(true){
      }
    }
  }
    spi_readonly = true;

  Serial.print("] - Errors : ");
  Serial.println(errorcounts);
  ice40_release_flashbitbang();
}

}


