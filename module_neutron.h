#pragma once
#include <Wire.h>
#include "module_memory.h"
#include "module_iridium.h"
#include "module_board.h"
#include "esp_timer.h"


namespace NEUTRON {

  #define I2C_SCL 21
  #define I2C_SDA 22
  #define I2C_SPEED 40000L
  #define FPGA_I2C_ADDRESS 0x55

  void ConfigureFPGA(){
    Serial.println("Starting NEUTRON CHECKS");
    // Enter Configure
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x20, 1);

    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x01, MEMORY::NEUTRON_I2C_BYTE01);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x02, MEMORY::NEUTRON_I2C_BYTE02);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x03, MEMORY::NEUTRON_I2C_BYTE03);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x04, MEMORY::NEUTRON_I2C_BYTE04);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x05, MEMORY::NEUTRON_I2C_BYTE05);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x06, MEMORY::NEUTRON_I2C_BYTE06);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x07, MEMORY::NEUTRON_I2C_BYTE07);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x08, MEMORY::NEUTRON_I2C_BYTE08);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x09, MEMORY::NEUTRON_I2C_BYTE09);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0A, MEMORY::NEUTRON_I2C_BYTE0A);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0B, MEMORY::NEUTRON_I2C_BYTE0B);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0C, MEMORY::NEUTRON_I2C_BYTE0C);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0D, MEMORY::NEUTRON_I2C_BYTE0D);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0E, MEMORY::NEUTRON_I2C_BYTE0E);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0F, MEMORY::NEUTRON_I2C_BYTE0F);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x10, MEMORY::NEUTRON_I2C_BYTE10);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x11, MEMORY::NEUTRON_I2C_BYTE11);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x12, MEMORY::NEUTRON_I2C_BYTE12);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x13, MEMORY::NEUTRON_I2C_BYTE13);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x14, MEMORY::NEUTRON_I2C_BYTE14);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x15, MEMORY::NEUTRON_I2C_BYTE15);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x16, MEMORY::NEUTRON_I2C_BYTE16);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x17, MEMORY::NEUTRON_I2C_BYTE17);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x18, MEMORY::NEUTRON_I2C_BYTE18);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x19, MEMORY::NEUTRON_I2C_BYTE19);

    Serial.println("NEUTRON CONFIG");
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x01));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x02));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x03));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x04));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x05));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x06));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x07));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x08));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x09));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0A));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0B));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0C));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0D));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0E));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0F));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x10));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x11));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x12));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x13));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x14));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x15));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x16));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x17));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x18));
    Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x19));

    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x20, 0);


  }

  bool begin() {
    if (!MEMORY::NEUTRON_ENABLED) return true;

    // Setup I2C
    Wire.begin(I2C_SCL, I2C_SDA);
    // Wire.setSpeed(I2C_SPEED);

    // Set FPGA Settings
    return true;
  }


  bool handle() {
    if (!MEMORY::NEUTRON_ENABLED) return true;
    
    // Check Current Exposure
    int64_t time_since_startup = esp_timer_get_time();

    double exposure = time_since_startup - MEMORY::NEUTRON_START;

    // Serial.println("EXPOSURE");
    // Serial.println(exposure);
    // Serial.println(MEMORY::NEUTRON_EXPOSURE);

    // Check Exposure or Run End Break
    if (exposure < MEMORY::NEUTRON_EXPOSURE*1000000 && !MEMORY::NEUTRON_STOP){
      return true;
    }

    // Register STOP
    MEMORY::NEUTRON_STOP = false;
    int64_t stop_time = time_since_startup;
    
    // Get N Neutrons
    // Get Histogram
    // Get LIVE DATA
    // Register data

    // Build Message
    String message = "D:300,N:1000,T:3600,B:30";

    // Queue the Message
    SDC::queue(message);
    // SIM::queue(message);
    // SAT::queue(message);

    // Upload FPGA Settings

    // Clear Buffers

    // Start a RUN
    Serial.println("NEUTRON::handle() - Starting run.");
    MEMORY::NEUTRON_START = esp_timer_get_time();
    Serial.println("NEUTRON::handle() - Finished.");

    return true;
  }
  








}










// class fpga_signal_input : public fpga_module  {
// public:
//   void upload(){
//     uint8_t val = 0;
//     val |= enable_ch1 << 0;
//     val |= enable_ch2 << 1;
//     val |= invertlogic_ch1 << 2;
//     val |= invertlogic_ch2 << 3;
//     val |= edgeonly_ch1 << 4;
//     val |= edgeonly_ch2 << 5;
//     val |= pulser_ch1 << 6;
//     val |= pulser_ch2 << 7;
//     set8(I2C_REG_SIGNAL_INPUT_CONFIG, val);
//   }

//   void download(){
//     uint8_t val = get8(I2C_REG_SIGNAL_INPUT_CONFIG);
//     enable_ch1 = (val >> 0) & 0x01;
//     enable_ch2 = (val >> 1) & 0x01;
//     invertlogic_ch1 = (val >> 2) & 0x01;
//     invertlogic_ch2 = (val >> 3) & 0x01;
//     edgeonly_ch1 = (val >> 4) & 0x01;
//     edgeonly_ch2 = (val >> 5) & 0x01;
//     pulser_ch1 = (val >> 6) & 0x01;
//     pulser_ch2 = (val >> 7) & 0x01;
//   }

//   void print() {
//     uint8_t val = get8(I2C_REG_SIGNAL_INPUT_CONFIG);
//     compare("Enable CH1 : ", enable_ch1, (val >> 0) & 0x01);
//     compare("Enable CH2 : ", enable_ch2, (val >> 1) & 0x01);
//     compare("Invert CH1 : ", invertlogic_ch1, (val >> 2) & 0x01);
//     compare("Invert CH2 : ", invertlogic_ch2, (val >> 3) & 0x01);
//     compare("EdgeOnly CH1 : ", edgeonly_ch1, (val >> 4) & 0x01);
//     compare("EdgeOnly CH2 : ", edgeonly_ch2, (val >> 5) & 0x01);
//     compare("Pulser CH2 : ", pulser_ch1, (val >> 6) & 0x01);
//     compare("Pulser CH2 : ", pulser_ch2, (val >> 7) & 0x01);
//   }

//   bool enable_ch1; // - 0 enable 1
//   bool enable_ch2; // - 1 enable 2
//   bool invertlogic_ch1; // - 2 invert logic 1
//   bool invertlogic_ch2; // - 3 invert logic 2
//   bool edgeonly_ch1; // - 4 edge only
//   bool edgeonly_ch2; // - 5 edge only
//   bool pulser_ch1; // - 6 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
//   bool pulser_ch2; // - 7 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
// };

// fpga_signal_input sigin;