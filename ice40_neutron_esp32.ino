#include "module_watchdog.h"
#include "module_ota.h"
#include "module_memory.h"
#include "module_deepsleep.h"


void process() {

  WD( MEMORY.begin() );
  WD( OTA.begin() );
  WD( SERVER.begin() );
  WD( DEEPSLEEP.begin() );

  WD( MEMORY.handle() );
  WD( OTA.handle() );
  WD( SERVER.begin() );
  WD( DEEPSLEEP.handle() );
  
}


void setup() {

  Serial.begin(115200);
  Serial.println("Booting");

  WD_START();

  // EACH HANDLE NEEDS TO CHECK SYSTEM TIME
  // IF IT HAS BEEN THEN IT RUNS THE JOB USING TASK
  // IF IT ISN'T THEN IT JUST RETURNS TRUE.

  // CONFIG
  // - MEMORY
  // - SERVER

  // DATA
  // - NEUTRON
  // - BME280
  // - SDI12
  // - I2C
  // - GPS

  // QUEUE

  // TRANSMIT
  // - SDCARD
  // - SIM800
  // - IRIDIUM

  // DEEPSLEEP (OPTIONAL)

}

void loop() {
  process();
}


