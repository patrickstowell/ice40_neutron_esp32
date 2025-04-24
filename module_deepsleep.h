#pragma once
#include <Wire.h>
#include "module_board.h"
#include "module_memory.h"

namespace DEEPSLEEP {

  // TwoWire I2CPower = TwoWire(0);
  // #define IP5306_ADDR          0x75
  // #define IP5306_REG_SYS_CTL0  0x00
  #define uS_TO_S_FACTOR 1000000 

  // bool setPowerBoostKeepOn(int en){
  //   Serial.println("DeepSleep::setPowerBoostKeepOn()");
  //   I2CPower.beginTransmission(IP5306_ADDR);
  //   I2CPower.write(IP5306_REG_SYS_CTL0);
    
  //   if (en) { I2CPower.write(0x37); } // Set bit1: 1 enable 0 disable boost keep on           
  //   else { I2CPower.write(0x35); } // 0x37 is default reg value     
    
  //   return I2CPower.endTransmission() == 0;
  // }

  bool begin(){
    if (!MEMORY::DEEPSLEEP_ENABLED) return true;
    Serial.println("DeepSleep::begin()");
    // I2CPower.begin(I2C_SDA, I2C_SCL, 400000);
    // setPowerBoostKeepOn(1);
    return true;
  }

  bool handle(){
    if (!MEMORY::DEEPSLEEP_ENABLED) return true;
    Serial.println("DeepSleep::handle()");
    
    long sleeptime = MEMORY::SLEEP_SEC; // Memory.GetIntSetting(EE_SLEEPTIME_INDEX);
    if (sleeptime > 21600) sleeptime = 21600;
    if (sleeptime <= 0) sleeptime = 900;
    // if (gBootCount < 10) sleeptime = 120;
    
    Serial.print("DeepSleep : Sleeping for : ");
    Serial.println(sleeptime);
    
    esp_sleep_enable_timer_wakeup(((uint64_t)sleeptime) * uS_TO_S_FACTOR);
    Serial.flush(); 
    esp_deep_sleep_start();
    return true;
  }
  
}