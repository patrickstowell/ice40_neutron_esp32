#pragma once
#include "module_config.h"
#include "module_memory.h"
#include "utilities.h"

namespace MSERIAL {

RTC_DATA_ATTR uint64_t local_time;
check_timer local_timer(10000000, &local_time);

bool begin() {
  Serial.begin(115200);
  delay(1000);
  return true;
}

bool handle() {

  if (local_timer.check()) {
  String message = "APN_NAME,MYAPNVALUE";
  MEMORY::PrintEEPROM();
  Serial.println("UPDATING");
  MEMORY::Command(message);
  MEMORY::PrintEEPROM();

  }
  return true;
}

}

