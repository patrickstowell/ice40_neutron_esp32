#pragma once
#include "module_config.h"

#include <SPI.h>
#include <SdFat.h>

namespace SDC {

  SdFat sd;
  FsFile dataFile;
  SPIClass spi = SPIClass(VSPI);

  #define SD_CS 5
  #define SPI_SPEED SD_SCK_MHZ(20)

  bool begin() {
    if (!CONFIG::SD_ENABLED) return true;

    if (!sd.begin(SD_CS, spi, SPI_SPEED)) {
      STATUS::SD_FOUND = false;
      return false;
    }

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
    return true;
  }

}