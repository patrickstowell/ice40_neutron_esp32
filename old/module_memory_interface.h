// // Auto-generated File, do not edit!
// #pragma once
// #include "module_memory.h"

// namespace MEMORY {
//   void Print() {
//     Serial.print("APN_NAME : ");
//     Serial.println(APN_NAME);
//     Serial.print("USER_NAME : ");
//     Serial.println(USER_NAME);
//     Serial.print("PASS_NAME : ");
//     Serial.println(PASS_NAME);
//     Serial.print("PMT_HV : ");
//     Serial.println(PMT_HV);
//     Serial.print("SLEEP_SEC : ");
//     Serial.println(SLEEP_SEC);
//     Serial.print("WIFI_SSID : ");
//     Serial.println(WIFI_SSID);
//     Serial.print("WIFI_PSWD : ");
//     Serial.println(WIFI_PSWD);
//     Serial.print("WIFI_ENABLED : ");
//     Serial.println(WIFI_ENABLED);
//     Serial.print("OTA_ENABLED : ");
//     Serial.println(OTA_ENABLED);
//     Serial.print("DEEPSLEEP_ENABLED : ");
//     Serial.println(DEEPSLEEP_ENABLED);
//     Serial.print("SERVER_ENABLED : ");
//     Serial.println(SERVER_ENABLED);
//     Serial.print("NEUTRON_ENABLED : ");
//     Serial.println(NEUTRON_ENABLED);
//     Serial.print("WATCHDOG_ENABLED : ");
//     Serial.println(WATCHDOG_ENABLED);
//   }
//   void ReadFromEEPROM() {
//     APN_NAME = eeprom.getString(F("APN_NAME"));
//     USER_NAME = eeprom.getString(F("USER_NAME"));
//     PASS_NAME = eeprom.getString(F("PASS_NAME"));
//     PMT_HV = eeprom.getInt(F("PMT_HV"));
//     SLEEP_SEC = eeprom.getInt(F("SLEEP_SEC"));
//     WIFI_SSID = eeprom.getString(F("WIFI_SSID"));
//     WIFI_PSWD = eeprom.getString(F("WIFI_PSWD"));
//     WIFI_ENABLED = eeprom.getBool(F("WIFI_ENABLED"));
//     OTA_ENABLED = eeprom.getBool(F("OTA_ENABLED"));
//     DEEPSLEEP_ENABLED = eeprom.getBool(F("DEEPSLEEP_ENABLED"));
//     SERVER_ENABLED = eeprom.getBool(F("SERVER_ENABLED"));
//     NEUTRON_ENABLED = eeprom.getBool(F("NEUTRON_ENABLED"));
//     WATCHDOG_ENABLED = eeprom.getBool(F("WATCHDOG_ENABLED"));
//   }
//   void WriteToEEPROM() {
//     eeprom.putString(F("APN_NAME"), "");
//     eeprom.putString(F("USER_NAME"), "");
//     eeprom.putString(F("PASS_NAME"), "");
//     eeprom.putInt(F("PMT_HV"), 1200);
//     eeprom.putInt(F("SLEEP_SEC"), 20);
//     eeprom.putString(F("WIFI_SSID"), "ESP32_NEUTRON");
//     eeprom.putString(F("WIFI_PSWD"), "neutrons2025");
//     eeprom.putBool(F("WIFI_ENABLED"), true);
//     eeprom.putBool(F("OTA_ENABLED"), true);
//     eeprom.putBool(F("DEEPSLEEP_ENABLED"), true);
//     eeprom.putBool(F("SERVER_ENABLED"), true);
//     eeprom.putBool(F("NEUTRON_ENABLED"), 1);
//     eeprom.putBool(F("WATCHDOG_ENABLED"), 0);
//   }

        
//   bool begin() {
//     Serial.println("Memory::begin()");
//     if (BOOT_COUNT == 0){

//         eeprom.begin("config", false);
//         eeprom.putUInt("hasconfig", 0);

//         if (!eeprom.getUInt("hasconfig", 0)) {
//             Serial.println("Memory::CheckEEPROMValid() : Uploading EEPROM Defaults");
//             eeprom.clear();
//             Print();

//             WriteToEEPROM();

//             eeprom.putUInt("hasconfig", 1);
//         } else {
//             Serial.println("Memory::CheckEEPROMValid() : EEPROM Already Present!");

//         }

//         int value = eeprom.getUInt("hasconfig", 0);
//         if (value) ReadFromEEPROM();
//         eeprom.end();

//     }

//     Print();
//     BOOT_COUNT += 1;
//     return true;
//   }

//   bool handle() { 
//       return true; 
//   }

// }
// }
