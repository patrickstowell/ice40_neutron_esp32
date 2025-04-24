// Auto-generated File, do not edit!
#pragma once
#include "utilities.h"
#include "module_config.h"
using namespace CONFIG;

namespace MEMORY {
  Preferences eeprom;
  void Print() {
    Serial.print("APN_NAME : ");
    Serial.println(APN_NAME);
    Serial.print("USER_NAME : ");
    Serial.println(USER_NAME);
    Serial.print("PASS_NAME : ");
    Serial.println(PASS_NAME);
    Serial.print("PMT_HV : ");
    Serial.println(PMT_HV);
    Serial.print("SLEEP_SEC : ");
    Serial.println(SLEEP_SEC);
    Serial.print("WIFI_SSID : ");
    Serial.println(WIFI_SSID);
    Serial.print("WIFI_PSWD : ");
    Serial.println(WIFI_PSWD);
    Serial.print("WIFI_ENABLED : ");
    Serial.println(WIFI_ENABLED);
    Serial.print("OTA_ENABLED : ");
    Serial.println(OTA_ENABLED);
    Serial.print("DEEPSLEEP_ENABLED : ");
    Serial.println(DEEPSLEEP_ENABLED);
    Serial.print("SERVER_ENABLED : ");
    Serial.println(SERVER_ENABLED);
    Serial.print("NEUTRON_ENABLED : ");
    Serial.println(NEUTRON_ENABLED);
    Serial.print("WATCHDOG_ENABLED : ");
    Serial.println(WATCHDOG_ENABLED);
    Serial.print("GPS_ENABLED : ");
    Serial.println(GPS_ENABLED);
  }
  void ReadFromEEPROM() {
    APN_NAME = eeprom.getString(("CyfWYXc"));
    USER_NAME = eeprom.getString(("C0I9gk5"));
    PASS_NAME = eeprom.getString(("CSdCTDg"));
    PMT_HV = eeprom.getInt(("C9VLvyt"));
    SLEEP_SEC = eeprom.getInt(("CsxKDm0"));
    WIFI_SSID = eeprom.getString(("C5fizR0"));
    WIFI_PSWD = eeprom.getString(("CbHxZAh"));
    WIFI_ENABLED = eeprom.getBool(("CHGUwnd"));
    OTA_ENABLED = eeprom.getBool(("CBipS0e"));
    DEEPSLEEP_ENABLED = eeprom.getBool(("CGkzBBF"));
    SERVER_ENABLED = eeprom.getBool(("CBuhskS"));
    NEUTRON_ENABLED = eeprom.getBool(("CN8MXWk"));
    WATCHDOG_ENABLED = eeprom.getBool(("CRZVhbs"));
    GPS_ENABLED = eeprom.getBool(("CY1oBQg"));
  }
  void WriteToEEPROM() {
    eeprom.putString(("CyfWYXc"), APN_NAME);
    eeprom.putString(("C0I9gk5"), USER_NAME);
    eeprom.putString(("CSdCTDg"), PASS_NAME);
    eeprom.putInt(("C9VLvyt"), PMT_HV);
    eeprom.putInt(("CsxKDm0"), SLEEP_SEC);
    eeprom.putString(("C5fizR0"), WIFI_SSID);
    eeprom.putString(("CbHxZAh"), WIFI_PSWD);
    eeprom.putBool(("CHGUwnd"), WIFI_ENABLED);
    eeprom.putBool(("CBipS0e"), OTA_ENABLED);
    eeprom.putBool(("CGkzBBF"), DEEPSLEEP_ENABLED);
    eeprom.putBool(("CBuhskS"), SERVER_ENABLED);
    eeprom.putBool(("CN8MXWk"), NEUTRON_ENABLED);
    eeprom.putBool(("CRZVhbs"), WATCHDOG_ENABLED);
    eeprom.putBool(("CY1oBQg"), GPS_ENABLED);
  }
  void Command(String message) {
    String parts[2];
    splitMessage(message, parts, 2);
    if(parts[0] == F("APN_NAME")) eeprom.putString(("CyfWYXc"), parts[1].toString());
    else if(parts[0] == F("USER_NAME")) eeprom.putString(("C0I9gk5"), parts[1].toString());
    else if(parts[0] == F("PASS_NAME")) eeprom.putString(("CSdCTDg"), parts[1].toString());
    else if(parts[0] == F("PMT_HV")) eeprom.putInt(("C9VLvyt"), parts[1].toInt());
    else if(parts[0] == F("SLEEP_SEC")) eeprom.putInt(("CsxKDm0"), parts[1].toInt());
    else if(parts[0] == F("WIFI_SSID")) eeprom.putString(("C5fizR0"), parts[1].toString());
    else if(parts[0] == F("WIFI_PSWD")) eeprom.putString(("CbHxZAh"), parts[1].toString());
    else if(parts[0] == F("WIFI_ENABLED")) eeprom.putBool(("CHGUwnd"), parts[1].toBool());
    else if(parts[0] == F("OTA_ENABLED")) eeprom.putBool(("CBipS0e"), parts[1].toBool());
    else if(parts[0] == F("DEEPSLEEP_ENABLED")) eeprom.putBool(("CGkzBBF"), parts[1].toBool());
    else if(parts[0] == F("SERVER_ENABLED")) eeprom.putBool(("CBuhskS"), parts[1].toBool());
    else if(parts[0] == F("NEUTRON_ENABLED")) eeprom.putBool(("CN8MXWk"), parts[1].toBool());
    else if(parts[0] == F("WATCHDOG_ENABLED")) eeprom.putBool(("CRZVhbs"), parts[1].toBool());
    else if(parts[0] == F("GPS_ENABLED")) eeprom.putBool(("CY1oBQg"), parts[1].toBool());
  return
}

        
  bool begin() {
    Serial.println("Memory::begin()");
    if (BOOT_COUNT == 0){

        eeprom.begin("config", false);
        eeprom.putUInt("hasconfig", 0);

        if (!eeprom.getUInt("hasconfig", 0)) {
            Serial.println("Memory::CheckEEPROMValid() : Uploading EEPROM Defaults");
            eeprom.clear();
            Print();

            WriteToEEPROM();

            eeprom.putUInt("hasconfig", 1);
        } else {
            Serial.println("Memory::CheckEEPROMValid() : EEPROM Already Present!");

        }

        int value = eeprom.getUInt("hasconfig", 0);
        if (value) ReadFromEEPROM();
        eeprom.end();

    }

    Print();
    BOOT_COUNT += 1;
    return true;
  }

  bool handle() { 
      return true; 
  }

}
}
