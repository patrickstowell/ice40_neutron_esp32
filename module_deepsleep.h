#pragma once
#include <Wire.h>
#include "module_board.h"
#include "module_config.h"


namespace DEEPSLEEP {
  #define uS_TO_S_FACTOR 1000000 

  bool begin(){
    if (!CONFIG::DEEPSLEEP_ENABLED) return true;
    Serial.println("DeepSleep::begin()");
    return true;
  }

  bool handle(){
    if (!CONFIG::DEEPSLEEP_ENABLED) return true;
    Serial.println("DeepSleep::handle()");
    
    long sleeptime = CONFIG::SLEEP_SEC; 
    if (sleeptime > 21600) sleeptime = 21600;
    if (sleeptime <= 0) sleeptime = 900;
    
    Serial.print("DeepSleep : Sleeping for : ");
    Serial.println(sleeptime);

    if (CONFIG::BOOT_COUNT < 10) {    
      esp_sleep_enable_timer_wakeup(((uint64_t)sleeptime) * uS_TO_S_FACTOR);
      esp_deep_sleep_start();
    }

    return true;
  }
  
}