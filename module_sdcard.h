#pragma once
#include "module_memory.h"

namespace SDC {

  bool begin(){
    // Try to open SD Card, if it doesn't, set the current config to disabled and print warning message
    return true;
  }

  bool handle() {
    // Do nothing
    return true;
  }

  bool queue(String message){
    Serial.print("SDC:");
    Serial.println(message);

    // DUMP Entire thing to disk with current timestamp straight away
  }

}