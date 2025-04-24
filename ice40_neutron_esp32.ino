#include "module_watchdog.h"
#include "module_ota.h"
#include "module_memory.h"
#include "module_deepsleep.h"
#include "module_server.h"
#include "module_sdcard.h"
#include "module_iridium.h"


  // EACH HANDLE NEEDS TO CHECK SYSTEM TIME
  // IF IT HAS BEEN THEN IT RUNS THE JOB USING TASK
  // IF IT ISN'T THEN IT JUST RETURNS TRUE.

  // CONFIG
  // - MEMORY X
  // - SERVER X

  // DATA
  // - NEUTRON X
  // - BME280
  // - SDI12
  // - I2C
  // - GPS

  // QUEUE

  // TRANSMIT
  // - SDCARD X
  // - SIM800
  // - IRIDIUM X

  // DEEPSLEEP (OPTIONAL) X
  // process();

void begin_all() {

  WD( MEMORY::begin() );
  WD( OTA::begin() );
  WD( SERVER::begin() );
  WD( DEEPSLEEP::begin() );

}

void handle_all() {

  WD( MEMORY::handle() );
  WD( OTA::handle() );
  WD( SERVER::handle() );
  WD( DEEPSLEEP::handle() );
  
}


void setup() {
  WD_START();

  delay(1000);

  Serial.begin(115200);
  Serial.println("ESP32: Booting");

  begin_all();
  handle_all();
}

void loop() {
  handle_all();
}


