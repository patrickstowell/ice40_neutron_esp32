#pragma once
#include <Wire.h>
#include "module_config.h"
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

    // Enter Config Mode
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x20, 1);

    // SIGNAL INPUT CONFIG
    uint8_t SIGNAL_INPUT_CONFIG = 0;
    SIGNAL_INPUT_CONFIG |= (CONFIG::enable_ch1 << 0);
    SIGNAL_INPUT_CONFIG |= (CONFIG::enable_ch2 << 1);
    SIGNAL_INPUT_CONFIG |= (CONFIG::invertlogic_ch1 << 2);
    SIGNAL_INPUT_CONFIG |= (CONFIG::invertlogic_ch1 << 3);
    SIGNAL_INPUT_CONFIG |= (CONFIG::edgeonly_ch1 << 4);
    SIGNAL_INPUT_CONFIG |= (CONFIG::edgeonly_ch1 << 5);
    SIGNAL_INPUT_CONFIG |= (CONFIG::pulser_ch1 << 6);
    SIGNAL_INPUT_CONFIG |= (CONFIG::pulser_ch1 << 7);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x01, SIGNAL_INPUT_CONFIG);



    // BUILD DAC MODULE CONFIG
    uint8_t DAC_CONTROL_CONFIG_BYTE0 = ((CONFIG::HVTARGET >> 0) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE1 = ((CONFIG::HVTARGET >> 8) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE2 = ((CONFIG::HVLIMIT  >> 0) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE3 = ((CONFIG::HVLIMIT  >> 8) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE4 = ((CONFIG::RAMPSPEED >> 0) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE5 = ((CONFIG::RAMPSPEED >> 8) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE6 = ((CONFIG::THRESHOLD1 >> 0) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE7 = ((CONFIG::THRESHOLD1 >> 8) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE8 = ((CONFIG::THRESHOLD2 >> 0) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE9 = ((CONFIG::THRESHOLD2 >> 8) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE10 = ((CONFIG::EEPROMCHOICE >> 0) & 0xFF);
    uint8_t DAC_CONTROL_CONFIG_BYTE11 = ((CONFIG::EEPROMCHOICE >> 8) & 0xFF);

    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x19, DAC_CONTROL_CONFIG_BYTE11);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x18, DAC_CONTROL_CONFIG_BYTE10);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x17, DAC_CONTROL_CONFIG_BYTE9);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x16, DAC_CONTROL_CONFIG_BYTE8);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x15, DAC_CONTROL_CONFIG_BYTE7);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x14, DAC_CONTROL_CONFIG_BYTE6);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x13, DAC_CONTROL_CONFIG_BYTE5);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x12, DAC_CONTROL_CONFIG_BYTE4);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x11, DAC_CONTROL_CONFIG_BYTE3);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x10, DAC_CONTROL_CONFIG_BYTE2);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0E, DAC_CONTROL_CONFIG_BYTE1);
    I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0F, DAC_CONTROL_CONFIG_BYTE0);


    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x01, CONFIG::NEUTRON_I2C_BYTE01);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x02, CONFIG::NEUTRON_I2C_BYTE02);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x03, CONFIG::NEUTRON_I2C_BYTE03);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x04, CONFIG::NEUTRON_I2C_BYTE04);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x05, CONFIG::NEUTRON_I2C_BYTE05);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x06, CONFIG::NEUTRON_I2C_BYTE06);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x07, CONFIG::NEUTRON_I2C_BYTE07);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x08, CONFIG::NEUTRON_I2C_BYTE08);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x09, CONFIG::NEUTRON_I2C_BYTE09);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0A, CONFIG::NEUTRON_I2C_BYTE0A);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0B, CONFIG::NEUTRON_I2C_BYTE0B);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0C, CONFIG::NEUTRON_I2C_BYTE0C);
    // I2C::write_byte_data(FPGA_I2C_ADDRESS, 0x0D, CONFIG::NEUTRON_I2C_BYTE0D);
    

    Serial.println("NEUTRON CONFIG");
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x01));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x02));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x03));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x04));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x05));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x06));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x07));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x08));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x09));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0A));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0B));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0C));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0D));
    // Serial.println(I2C::read_byte_data(FPGA_I2C_ADDRESS, 0x0E));
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
    if (!CONFIG::NEUTRON_ENABLED) return true;

    // Setup I2C
    // Wire.begin(I2C_SCL, I2C_SDA);
    I2C::begin();
    // Wire.setSpeed(I2C_SPEED);

    // Set FPGA Settings
    return true;
  }


  bool handle() {
    if (!CONFIG::NEUTRON_ENABLED) return true;
    
    // Check Current Exposure
    int64_t time_since_startup = esp_timer_get_time();

    double exposure = time_since_startup - CONFIG::NEUTRON_START;

    // Serial.println("EXPOSURE");
    // Serial.println(exposure);
    // Serial.println(CONFIG::NEUTRON_EXPOSURE);

    // Check Exposure or Run End Break
    if (exposure < CONFIG::NEUTRON_EXPOSURE*1000000 && !CONFIG::NEUTRON_STOP){
      return true;
    }

    // Register STOP
    CONFIG::NEUTRON_STOP = false;
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
    ConfigureFPGA();

    // Clear Buffers

    // Start a RUN
    Serial.println("NEUTRON::handle() - Starting run.");
    CONFIG::NEUTRON_START = esp_timer_get_time();
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