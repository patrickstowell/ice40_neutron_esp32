#pragma once
#include "module_config.h"

namespace SAT {

  bool begin(){
    return true;
  }

  bool handle() {
    return true;
  }

  bool queue(String message){
    Serial.print("SAT:");
    Serial.println(message);
  }

}