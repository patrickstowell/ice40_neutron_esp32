#pragma once
#include "module_memory.h"

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