// Auto-generated File, do not edit!
#pragma once
#include "utilities.h"
#include "module_config.h"
using namespace CONFIG;

namespace MEMORY {
  Preferences eeprom;
  void PrintEEPROM() {
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
    Serial.print("HVTARGET : ");
    Serial.println(HVTARGET);
    Serial.print("HVLIMIT : ");
    Serial.println(HVLIMIT);
    Serial.print("RAMPSPEED : ");
    Serial.println(RAMPSPEED);
    Serial.print("THRESHOLD1 : ");
    Serial.println(THRESHOLD1);
    Serial.print("THRESHOLD2 : ");
    Serial.println(THRESHOLD2);
    Serial.print("EEPROMCHOICE : ");
    Serial.println(EEPROMCHOICE);
    Serial.print("enable_ch1 : ");
    Serial.println(enable_ch1);
    Serial.print("enable_ch2 : ");
    Serial.println(enable_ch2);
    Serial.print("invertlogic_ch1 : ");
    Serial.println(invertlogic_ch1);
    Serial.print("invertlogic_ch2 : ");
    Serial.println(invertlogic_ch2);
    Serial.print("edgeonly_ch1 : ");
    Serial.println(edgeonly_ch1);
    Serial.print("edgeonly_ch2 : ");
    Serial.println(edgeonly_ch2);
    Serial.print("pulser_ch1 : ");
    Serial.println(pulser_ch1);
    Serial.print("pulser_ch2 : ");
    Serial.println(pulser_ch2);
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
    HVTARGET = eeprom.getInt(("CgFw89G"));
    HVLIMIT = eeprom.getInt(("CTxBd7A"));
    RAMPSPEED = eeprom.getInt(("CxMGkcc"));
    THRESHOLD1 = eeprom.getInt(("CpBfHg0"));
    THRESHOLD2 = eeprom.getInt(("CewhgDB"));
    EEPROMCHOICE = eeprom.getInt(("Cjx4rRm"));
    enable_ch1 = eeprom.getBool(("ChsmuDk"));
    enable_ch2 = eeprom.getBool(("C7uz0ne"));
    invertlogic_ch1 = eeprom.getBool(("CTlDtYP"));
    invertlogic_ch2 = eeprom.getBool(("CrAHcNb"));
    edgeonly_ch1 = eeprom.getBool(("CiAK7P9"));
    edgeonly_ch2 = eeprom.getBool(("CICVmUt"));
    pulser_ch1 = eeprom.getBool(("C1L1dLy"));
    pulser_ch2 = eeprom.getBool(("Cv3jlxF"));
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
    eeprom.putInt(("CgFw89G"), HVTARGET);
    eeprom.putInt(("CTxBd7A"), HVLIMIT);
    eeprom.putInt(("CxMGkcc"), RAMPSPEED);
    eeprom.putInt(("CpBfHg0"), THRESHOLD1);
    eeprom.putInt(("CewhgDB"), THRESHOLD2);
    eeprom.putInt(("Cjx4rRm"), EEPROMCHOICE);
    eeprom.putBool(("ChsmuDk"), enable_ch1);
    eeprom.putBool(("C7uz0ne"), enable_ch2);
    eeprom.putBool(("CTlDtYP"), invertlogic_ch1);
    eeprom.putBool(("CrAHcNb"), invertlogic_ch2);
    eeprom.putBool(("CiAK7P9"), edgeonly_ch1);
    eeprom.putBool(("CICVmUt"), edgeonly_ch2);
    eeprom.putBool(("C1L1dLy"), pulser_ch1);
    eeprom.putBool(("Cv3jlxF"), pulser_ch2);
  }
  void Command(String message) {
    String parts[2];
    splitMessage(message, parts, 2);
    if(parts[0] == F("APN_NAME")) APN_NAME = parts[1];
    else if(parts[0] == F("USER_NAME")) USER_NAME = parts[1];
    else if(parts[0] == F("PASS_NAME")) PASS_NAME = parts[1];
    else if(parts[0] == F("PMT_HV")) PMT_HV = parts[1].toInt();
    else if(parts[0] == F("SLEEP_SEC")) SLEEP_SEC = parts[1].toInt();
    else if(parts[0] == F("WIFI_SSID")) WIFI_SSID = parts[1];
    else if(parts[0] == F("WIFI_PSWD")) WIFI_PSWD = parts[1];
    else if(parts[0] == F("WIFI_ENABLED")) WIFI_ENABLED = parts[1].toInt();
    else if(parts[0] == F("OTA_ENABLED")) OTA_ENABLED = parts[1].toInt();
    else if(parts[0] == F("DEEPSLEEP_ENABLED")) DEEPSLEEP_ENABLED = parts[1].toInt();
    else if(parts[0] == F("SERVER_ENABLED")) SERVER_ENABLED = parts[1].toInt();
    else if(parts[0] == F("NEUTRON_ENABLED")) NEUTRON_ENABLED = parts[1].toInt();
    else if(parts[0] == F("WATCHDOG_ENABLED")) WATCHDOG_ENABLED = parts[1].toInt();
    else if(parts[0] == F("GPS_ENABLED")) GPS_ENABLED = parts[1].toInt();
    else if(parts[0] == F("HVTARGET")) HVTARGET = parts[1].toInt();
    else if(parts[0] == F("HVLIMIT")) HVLIMIT = parts[1].toInt();
    else if(parts[0] == F("RAMPSPEED")) RAMPSPEED = parts[1].toInt();
    else if(parts[0] == F("THRESHOLD1")) THRESHOLD1 = parts[1].toInt();
    else if(parts[0] == F("THRESHOLD2")) THRESHOLD2 = parts[1].toInt();
    else if(parts[0] == F("EEPROMCHOICE")) EEPROMCHOICE = parts[1].toInt();
    else if(parts[0] == F("enable_ch1")) enable_ch1 = parts[1].toInt();
    else if(parts[0] == F("enable_ch2")) enable_ch2 = parts[1].toInt();
    else if(parts[0] == F("invertlogic_ch1")) invertlogic_ch1 = parts[1].toInt();
    else if(parts[0] == F("invertlogic_ch2")) invertlogic_ch2 = parts[1].toInt();
    else if(parts[0] == F("edgeonly_ch1")) edgeonly_ch1 = parts[1].toInt();
    else if(parts[0] == F("edgeonly_ch2")) edgeonly_ch2 = parts[1].toInt();
    else if(parts[0] == F("pulser_ch1")) pulser_ch1 = parts[1].toInt();
    else if(parts[0] == F("pulser_ch2")) pulser_ch2 = parts[1].toInt();
  return;
  }

        
  bool begin() {
    Serial.println("Memory::begin()");
    if (BOOT_COUNT == 0){

        eeprom.begin("config", false);
        eeprom.putUInt("hasconfig", 0);

        if (!eeprom.getUInt("hasconfig", 0)) {
            Serial.println("Memory::CheckEEPROMValid() : Uploading EEPROM Defaults");
            eeprom.clear();
            PrintEEPROM();

            WriteToEEPROM();

            eeprom.putUInt("hasconfig", 1);
        } else {
            Serial.println("Memory::CheckEEPROMValid() : EEPROM Already Present!");

        }

        int value = eeprom.getUInt("hasconfig", 0);
        if (value) ReadFromEEPROM();
        eeprom.end();

    }

    PrintEEPROM();
    BOOT_COUNT += 1;
    return true;
  }

  bool handle() { 
      return true; 
  }

}
