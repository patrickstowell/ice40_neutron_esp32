#pragma once

#include <Wire.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

SFE_UBLOX_GNSS gps_device;

namespace GPS {
  
  bool begin() {
    if (!CONFIG::GPS_ENABLED) return true;

    if (gps_device.begin(Wire) != false) {
      Serial.print("GPS::begin()");
      Serial.println(" - Failed to find GPS, disabling GPS stream.");
      CONFIG::GPS_FOUND = false;
    }

    return true;
  }

  bool handle() {
    if (!CONFIG::GPS_ENABLED || CONFIG::GPS_NOT_FOUND) return true;

    if (gps_device.begin(Wire) != false) {

      gps_device.setI2COutput(COM_TYPE_UBX);  // UBX only, no NMEA
      gps_device.powerOn();
      gps_device.setNavigationFrequency(1);
      gps_device.setAutoPVT(true);

      while (!gps_device.getPVT()) {
        delay(100);
      }

      gps_device.powerOff();
    }
    return true;
  }




}