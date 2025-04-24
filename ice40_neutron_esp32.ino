#include "module_watchdog.h"
#include "module_ota.h"
#include "module_memory.h"
#include "module_config.h"
#include "module_deepsleep.h"
#include "module_server.h"
#include "module_sdcard.h"
#include "module_iridium.h"
#include "module_neutron.h"

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
  // - GPS

  // QUEUE

  // TRANSMIT
  // - SDCARD X
  // - SIM800
  // - IRIDIUM X

  // DEEPSLEEP (OPTIONAL) X
  // process();

void begin_all() {

  // Configurations
  WD( MEMORY::begin() );
  WD( OTA::begin() );
  WD( SERVER::begin() );

  // Emitters
  WD( NEUTRON::begin() );
  // WD( BME280::begin() );
  // WD( SDI12::begin() );
  // WD( GPS::begin() );

  // Transmitters
  WD( SDC::begin() );
  // WD( SIM::begin() );
  WD( SAT::begin() );

  // Sleeper
  WD( DEEPSLEEP::begin() );
}


void handle_all() {

  // Configurations
  WD( MEMORY::handle() );
  WD( OTA::handle() );
  WD( SERVER::handle() );

  // Emitters
  WD( NEUTRON::handle() );
  // WD( BME280::handle() );
  // WD( SDI12::handle() );
  // WD( GPS::handle() );

  // Transmitters
  WD( SDC::handle() );
  // WD( SIM::handle() );
  WD( SAT::handle() );

  // Sleeper
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


