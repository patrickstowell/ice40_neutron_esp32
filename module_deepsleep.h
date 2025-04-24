#include <Wire.h>

#include "module_memory.hpp"

TwoWire I2CPower = TwoWire(0);
#define IP5306_ADDR          0x75
#define IP5306_REG_SYS_CTL0  0x00

// ----------------------------------
// RTC SLEEP FUNCTIONALITY
// ----------------------------------
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */

class module_deepsleep {
public:

  module_deepsleep(){};
  ~module_deepsleep(){};

  bool setPowerBoostKeepOn(int en){
    Serial.println("TTGO::setPowerBoostKeepOn()");
    I2CPower.beginTransmission(IP5306_ADDR);
    I2CPower.write(IP5306_REG_SYS_CTL0);
    
    if (en) { I2CPower.write(0x37); } // Set bit1: 1 enable 0 disable boost keep on           
    else { I2CPower.write(0x35); } // 0x37 is default reg value     
    
    return I2CPower.endTransmission() == 0;
  }

  void begin(){
    Serial.println("TTGO::Initialize()");
    I2CPower.begin(I2C_SDA, I2C_SCL, 400000);
    setPowerBoostKeepOn(1);
  }

  void handle(){
    
    long sleeptime = Memory.GetIntSetting(EE_SLEEPTIME_INDEX);
    if (sleeptime > 21600) sleeptime = 21600;
    if (sleeptime <= 0) sleeptime = 900;
    if (gBootCount < 10) sleeptime = 120;
    
    Serial.print("Sleeping for : ");
    Serial.println(sleeptime);
    
    esp_sleep_enable_timer_wakeup(((uint64_t)sleeptime) * uS_TO_S_FACTOR);
    Serial.flush(); 
    esp_deep_sleep_start();
  }
  
};
static module_deepsleep DEEPSLEEP;
#endif
