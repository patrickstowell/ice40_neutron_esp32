#include "SPI.h"
#include "fw.h"
#include "Wire.h"

#include "fpga_defs.h"


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


int Scanner ()
{
  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  for (byte i = 0; i < 120; i++)
  {
    // Serial.println(i, HEX);
    Wire.beginTransmission (i);          // Begin I2C transmission Address (i)
    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response) 
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);     // PCF8574 7 bit address
      Serial.println (")");
      count++;
    }
  }
  Serial.print ("Found ");      
  Serial.print (count, DEC);        // numbers of devices
  Serial.println (" device(s).");
  return count;
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





class devbus {
public:
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

devbus bus;

void set_hv(int val){
  // bus.write_byte_data(FPGA_I2C_ADDRESS, 0, val >> 8 & 0xFF);
  // bus.write_byte_data(FPGA_I2C_ADDRESS, 1, val >> 0 & 0xFF);
  // bus.write_byte_data(FPGA_I2C_ADDRESS, 36, val & 0xFF);
  bus.write_byte_data(FPGA_I2C_ADDRESS, 36, val & 0xFF);


}

uint16_t get16(uint8_t addr){
  uint8_t val_msb = bus.read_byte_data(FPGA_I2C_ADDRESS, addr);
  uint8_t val_lsb = bus.read_byte_data(FPGA_I2C_ADDRESS, addr+1);
  int val = val_msb << 8 | val_lsb;
  return val;
}

uint16_t get8(uint8_t addr){
  uint8_t val = bus.read_byte_data(FPGA_I2C_ADDRESS, addr);
  return val;
}


uint16_t set16(uint8_t addr, uint16_t val, bool check=0){
  bus.write_byte_data(FPGA_I2C_ADDRESS, addr+0, (val >> 8) & 0xFF);
  bus.write_byte_data(FPGA_I2C_ADDRESS, addr+1, (val >> 0) & 0xFF);
  if (check) return get16(addr);
  return 0;
}

uint16_t set8(uint8_t addr, uint8_t val, bool check=0){
  bus.write_byte_data(FPGA_I2C_ADDRESS, addr, val & 0xFF);
  if (check) return get8(addr);
  return 0;
}


// void set_hv_limit(int val){
//   bus.write_byte_data(FPGA_I2C_ADDRESS, 37, val & 0xFF);
//   // bus.write_byte_data(FPGA_I2C_ADDRESS, 9, val >> 0 & 0xFF);
// }

// int read_hv(){
//   uint8_t val2 = bus.read_byte_data(FPGA_I2C_ADDRESS, 36);
  
//   // uint8_t val1 = bus.read_byte_data(FPGA_I2C_ADDRESS, 1);

//   // // delay(50);
  

//   // // Serial.print("D1 : ");
//   // // Serial.println(val1);
//   // // Serial.print("D2 : ");
//   // // Serial.println(val2);

//   // int val = val1 << 8 | val2;
//   return val2;
// }

// int read_hvt(){
//   uint8_t val1 = bus.read_byte_data(FPGA_I2C_ADDRESS, 6);
//   uint8_t val2 = bus.read_byte_data(FPGA_I2C_ADDRESS, 7);
//   int val = val1 << 8 | val2;
//   return val;
// }

// void enable_hv(){
//   bus.write_byte_data(FPGA_I2C_ADDRESS, 10, 1);
// }

// void disable_hv(){
//   bus.write_byte_data(FPGA_I2C_ADDRESS, 10, 0);
// }

// void set_gate0(uint16_t val){
//   bus.write_byte_data(FPGA_I2C_ADDRESS, FPGA_I2C_GATE0_LSB, val >> 0 & 0xFF);
//   bus.write_byte_data(FPGA_I2C_ADDRESS, FPGA_I2C_GATE0_MSB, val >> 8 & 0xFF);
// }

// uint16_t get_gate0(){
//   return (uint16_t(bus.read_byte_data(FPGA_I2C_ADDRESS, FPGA_I2C_GATE0_LSB)) << 0| 
//           uint16_t(bus.read_byte_data(FPGA_I2C_ADDRESS, FPGA_I2C_GATE0_MSB)) << 8);
// }

void setup(){
  delay(5000);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  digitalWrite(34, 1);
  digitalWrite(35, 1);
  
  Serial.begin(115200);
  delay(2000);
  Serial.println("STARTING");

  // ice40_setup();
  flash_fpga();
  // ice40_setup();
  // ice40_release_flashbitbang();

  digitalWrite(CFG_RST, LOW);
  delayMicroseconds(5000);
  digitalWrite(CFG_RST, HIGH);
  delayMicroseconds(10000);

  Wire.begin(21, 22);
  // Wire.setClock(40000L);
}


class fpga_module {
public:
  fpga_module(){};
  ~fpga_module(){};

  virtual void upload() = 0;
  virtual void download() = 0;

  void entry(const char* line, uint16_t val){
    Serial.print(line);
    Serial.println(val);
  }

   void compare(const char* line, uint16_t val, uint16_t val2){
    Serial.print(line);
    Serial.print(val);
    Serial.print(" : ");
    Serial.println(val2);
  }

  virtual void print() = 0;
};

class fpga_signal_input : public fpga_module  {
public:
  void upload(){
    uint8_t val = 0;
    val |= enable_ch1 << 0;
    val |= enable_ch2 << 1;
    val |= invertlogic_ch1 << 2;
    val |= invertlogic_ch2 << 3;
    val |= edgeonly_ch1 << 4;
    val |= edgeonly_ch2 << 5;
    val |= pulser_ch1 << 6;
    val |= pulser_ch2 << 7;
    set8(I2C_REG_SIGNAL_INPUT_CONFIG, val);
  }

  void download(){
    uint8_t val = get8(I2C_REG_SIGNAL_INPUT_CONFIG);
    enable_ch1 = (val >> 0) & 0x01;
    enable_ch2 = (val >> 1) & 0x01;
    invertlogic_ch1 = (val >> 2) & 0x01;
    invertlogic_ch2 = (val >> 3) & 0x01;
    edgeonly_ch1 = (val >> 4) & 0x01;
    edgeonly_ch2 = (val >> 5) & 0x01;
    pulser_ch1 = (val >> 6) & 0x01;
    pulser_ch2 = (val >> 7) & 0x01;
  }

  void print() {
    uint8_t val = get8(I2C_REG_SIGNAL_INPUT_CONFIG);
    compare("Enable CH1 : ", enable_ch1, (val >> 0) & 0x01);
    compare("Enable CH2 : ", enable_ch2, (val >> 1) & 0x01);
    compare("Invert CH1 : ", invertlogic_ch1, (val >> 2) & 0x01);
    compare("Invert CH2 : ", invertlogic_ch2, (val >> 3) & 0x01);
    compare("EdgeOnly CH1 : ", edgeonly_ch1, (val >> 4) & 0x01);
    compare("EdgeOnly CH2 : ", edgeonly_ch2, (val >> 5) & 0x01);
    compare("Pulser CH2 : ", pulser_ch1, (val >> 6) & 0x01);
    compare("Pulser CH2 : ", pulser_ch2, (val >> 7) & 0x01);
  }

  bool enable_ch1; // - 0 enable 1
  bool enable_ch2; // - 1 enable 2
  bool invertlogic_ch1; // - 2 invert logic 1
  bool invertlogic_ch2; // - 3 invert logic 2
  bool edgeonly_ch1; // - 4 edge only
  bool edgeonly_ch2; // - 5 edge only
  bool pulser_ch1; // - 6 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
  bool pulser_ch2; // - 7 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
};

fpga_signal_input sigin;

void loop() {
  
  delay(1000);
  delay(1000);
  delay(1000);
  delay(1000);

  sigin.enable_ch1 = true;
  sigin.enable_ch2 = false;
  sigin.upload();
  sigin.print();

  sigin.enable_ch1 = false;
  sigin.enable_ch2 = true;
  sigin.upload();
  sigin.print();

  sigin.enable_ch1 = false;
  sigin.enable_ch2 = true;
  sigin.invertlogic_ch1 = true;
  sigin.upload();
  sigin.print();

  Serial.println("CHECK");

  sigin.print();
  sigin.print();
  sigin.print();

  // set16(I2C_REG_TOT_WINDOW_SHORT_MSB, 96);
  // set16(I2C_REG_TOT_WINDOW_LONG_MSB, 1026);


  // for (int i = 0; i < 40; i++){
  //   uint8_t val1 = bus.read_byte_data(FPGA_I2C_ADDRESS, i);
  //   val1 = bus.read_byte_data(FPGA_I2C_ADDRESS, i);

  //   Serial.print(i);
  //   Serial.print(" : ");
  //   Serial.println(val1);
  //   delay(10);
  // }

}
