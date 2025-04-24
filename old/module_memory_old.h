// #pragma once
// #include <Preferences.h>
// #define ID(x) #x
// Preferences eeprom;

// namespace MEMORY {

// RTC_DATA_ATTR int BOOT_COUNT = 0;
// RTC_DATA_ATTR String APN_NAME;
// RTC_DATA_ATTR String USER_NAME;
// RTC_DATA_ATTR String PASS_NAME;
// RTC_DATA_ATTR int PMT_HV = 1200;
// RTC_DATA_ATTR int SLEEP_SEC = 20;
// RTC_DATA_ATTR String WIFI_SSID = "ESP32_NEUTRON";
// RTC_DATA_ATTR String WIFI_PSWD = "neutrons2025";
// RTC_DATA_ATTR bool WIFI_ENABLED = true;
// RTC_DATA_ATTR bool OTA_ENABLED = true;
// RTC_DATA_ATTR bool DEEPSLEEP_ENABLED = true;
// RTC_DATA_ATTR bool SERVER_ENABLED = true;

// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE01 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE02 = 24;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE03 = 48;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE04 = 96;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE05 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE06 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE07 = 12;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE08 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE09 = 34;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE0A = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE0B = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE0C = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE0D = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE0E = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE0F = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE10 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE11 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE12 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE13 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE14 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE15 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE16 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE17 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE18 = 0;
// RTC_DATA_ATTR uint8_t NEUTRON_I2C_BYTE19 = 0;
// RTC_DATA_ATTR bool NEUTRON_ENABLED = 1;
// RTC_DATA_ATTR int64_t NEUTRON_START = 0;
// RTC_DATA_ATTR bool NEUTRON_RUNNING = 0;
// RTC_DATA_ATTR bool NEUTRON_STOP = 1; // Set this to 1 to force a run on boot
// RTC_DATA_ATTR int64_t NEUTRON_EXPOSURE = 10;

// RTC_DATA_ATTR bool WATCHDOG_ENABLED = 0;

// RTC_DATA_ATTR bool I2C_ON = 0;
// RTC_DATA_ATTR bool UART_ON = 0;
// RTC_DATA_ATTR bool SDI12_ON = 0;
// RTC_DATA_ATTR bool SPI_ON = 0;

// // BIT MASKS SHOULD JUST BE 
// // RTC_DATA_ATTR bool FSIGIN_ENCH1 = true;
// // RTC_DATA_ATTR bool FSIGIN_ENCH2 = true;
// // RTC_DATA_ATTR bool FSIGIN_IVCH1 = true;
// // RTC_DATA_ATTR bool FSIGIN_IVCH2 = true;
// //  bool enable_ch1; // - 0 enable 1
// //   bool enable_ch2; // - 1 enable 2
// //   bool invertlogic_ch1; // - 2 invert logic 1
// //   bool invertlogic_ch2; // - 3 invert logic 2
// //   bool edgeonly_ch1; // - 4 edge only
// //   bool edgeonly_ch2; // - 5 edge only
// //   bool pulser_ch1; // - 6 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
// //   bool pulser_ch2; // - 7 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]




// // Access Point credentials
// // const char* ssid = "ESP32_NEUTRON";
// // const char* password = "neutrons2025";

// void Print() {
//     Serial.print("APN_NAME : "); Serial.println(APN_NAME);
//     Serial.print("USER_NAME : "); Serial.println(USER_NAME);
//     Serial.print("PASS_NAME : "); Serial.println(PASS_NAME);
//     Serial.print("PMT_HV : "); Serial.println(PMT_HV);
//     Serial.print("SLEEP_SEC : "); Serial.println(SLEEP_SEC);
//     Serial.print("WIFI_SSID : "); Serial.println(WIFI_SSID);
//     Serial.print("WIFI_PSWD : "); Serial.println(WIFI_PSWD);
//     Serial.print("WIFI_ENABLED : "); Serial.println(WIFI_ENABLED);
//     Serial.print("OTA_ENABLED : "); Serial.println(OTA_ENABLED);
//     Serial.print("DEEPSLEEP_ENABLED : "); Serial.println(DEEPSLEEP_ENABLED);
//     Serial.print("SERVER_ENABLED : "); Serial.println(SERVER_ENABLED);

//     Serial.print("NEUTRON_I2C_BYTE01 : "); Serial.println(NEUTRON_I2C_BYTE01);
//     Serial.print("NEUTRON_I2C_BYTE02 : "); Serial.println(NEUTRON_I2C_BYTE02);
//     Serial.print("NEUTRON_I2C_BYTE03 : "); Serial.println(NEUTRON_I2C_BYTE03);
//     Serial.print("NEUTRON_I2C_BYTE04 : "); Serial.println(NEUTRON_I2C_BYTE04);
//     Serial.print("NEUTRON_I2C_BYTE05 : "); Serial.println(NEUTRON_I2C_BYTE05);
//     Serial.print("NEUTRON_I2C_BYTE06 : "); Serial.println(NEUTRON_I2C_BYTE06);
//     Serial.print("NEUTRON_I2C_BYTE07 : "); Serial.println(NEUTRON_I2C_BYTE07);
//     Serial.print("NEUTRON_I2C_BYTE08 : "); Serial.println(NEUTRON_I2C_BYTE08);
//     Serial.print("NEUTRON_I2C_BYTE09 : "); Serial.println(NEUTRON_I2C_BYTE09);
//     Serial.print("NEUTRON_I2C_BYTE0A : "); Serial.println(NEUTRON_I2C_BYTE0A);
//     Serial.print("NEUTRON_I2C_BYTE0B : "); Serial.println(NEUTRON_I2C_BYTE0B);
//     Serial.print("NEUTRON_I2C_BYTE0C : "); Serial.println(NEUTRON_I2C_BYTE0C);
//     Serial.print("NEUTRON_I2C_BYTE0D : "); Serial.println(NEUTRON_I2C_BYTE0D);
//     Serial.print("NEUTRON_I2C_BYTE0E : "); Serial.println(NEUTRON_I2C_BYTE0E);
//     Serial.print("NEUTRON_I2C_BYTE0F : "); Serial.println(NEUTRON_I2C_BYTE0F);
//     Serial.print("NEUTRON_I2C_BYTE10 : "); Serial.println(NEUTRON_I2C_BYTE10);
//     Serial.print("NEUTRON_I2C_BYTE11 : "); Serial.println(NEUTRON_I2C_BYTE11);
//     Serial.print("NEUTRON_I2C_BYTE12 : "); Serial.println(NEUTRON_I2C_BYTE12);
//     Serial.print("NEUTRON_I2C_BYTE13 : "); Serial.println(NEUTRON_I2C_BYTE13);
//     Serial.print("NEUTRON_I2C_BYTE14 : "); Serial.println(NEUTRON_I2C_BYTE14);
//     Serial.print("NEUTRON_I2C_BYTE15 : "); Serial.println(NEUTRON_I2C_BYTE15);
//     Serial.print("NEUTRON_I2C_BYTE16 : "); Serial.println(NEUTRON_I2C_BYTE16);
//     Serial.print("NEUTRON_I2C_BYTE17 : "); Serial.println(NEUTRON_I2C_BYTE17);
//     Serial.print("NEUTRON_I2C_BYTE18 : "); Serial.println(NEUTRON_I2C_BYTE18);
//     Serial.print("NEUTRON_I2C_BYTE19 : "); Serial.println(NEUTRON_I2C_BYTE19);
// }

// void ReadFromEEPROM() {
//     APN_NAME  = eeprom.getString(ID(APN_NAME));
//     USER_NAME = eeprom.getString(ID(USER_NAME));
//     PASS_NAME = eeprom.getString(ID(PASS_NAME));
//     PMT_HV    = eeprom.getInt(ID(PMT_HV));
//     SLEEP_SEC = eeprom.getInt(ID(SLEEP_SEC));
//     WIFI_SSID = eeprom.getString(ID(WIFI_SSID));
//     WIFI_PSWD = eeprom.getString(ID(WIFI_PSWD));
//     WIFI_ENABLED = eeprom.getBool(ID(WIFI_ENABLED));
//     OTA_ENABLED = eeprom.getBool(ID(OTA_ENABLED));
//     DEEPSLEEP_ENABLED = eeprom.getBool(ID(DEEPSLEEP_ENABLED));
//     SERVER_ENABLED = eeprom.getBool(ID(SERVER_ENABLED));

//     NEUTRON_I2C_BYTE01 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE01));
//     NEUTRON_I2C_BYTE02 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE02));
//     NEUTRON_I2C_BYTE03 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE03));
//     NEUTRON_I2C_BYTE04 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE04));
//     NEUTRON_I2C_BYTE05 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE05));
//     NEUTRON_I2C_BYTE06 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE06));
//     NEUTRON_I2C_BYTE07 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE07));
//     NEUTRON_I2C_BYTE08 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE08));
//     NEUTRON_I2C_BYTE09 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE09));
//     NEUTRON_I2C_BYTE0A = eeprom.getUInt(ID(NEUTRON_I2C_BYTE0A));
//     NEUTRON_I2C_BYTE0B = eeprom.getUInt(ID(NEUTRON_I2C_BYTE0B));
//     NEUTRON_I2C_BYTE0C = eeprom.getUInt(ID(NEUTRON_I2C_BYTE0C));
//     NEUTRON_I2C_BYTE0D = eeprom.getUInt(ID(NEUTRON_I2C_BYTE0D));
//     NEUTRON_I2C_BYTE0E = eeprom.getUInt(ID(NEUTRON_I2C_BYTE0E));
//     NEUTRON_I2C_BYTE0F = eeprom.getUInt(ID(NEUTRON_I2C_BYTE0F));
//     NEUTRON_I2C_BYTE10 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE10));
//     NEUTRON_I2C_BYTE11 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE11));
//     NEUTRON_I2C_BYTE12 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE12));
//     NEUTRON_I2C_BYTE13 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE13));
//     NEUTRON_I2C_BYTE14 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE14));
//     NEUTRON_I2C_BYTE15 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE15));
//     NEUTRON_I2C_BYTE16 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE16));
//     NEUTRON_I2C_BYTE17 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE17));
//     NEUTRON_I2C_BYTE18 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE18));
//     NEUTRON_I2C_BYTE19 = eeprom.getUInt(ID(NEUTRON_I2C_BYTE19));

// }

// void WriteToEEPROM() {
//     eeprom.putString(ID(APN_NAME),  APN_NAME);
//     eeprom.putString(ID(USER_NAME), USER_NAME);
//     eeprom.putString(ID(PASS_NAME), PASS_NAME);
//     eeprom.putInt(ID(PMT_HV),       PMT_HV);
//     eeprom.putInt(ID(SLEEP_SEC),    SLEEP_SEC);
//     eeprom.putString(ID(WIFI_SSID),    WIFI_SSID);
//     eeprom.putString(ID(WIFI_PSWD),    WIFI_PSWD);
//     eeprom.putBool(ID(WIFI_ENABLED),    WIFI_ENABLED);
//     eeprom.putBool(ID(OTA_ENABLED),    OTA_ENABLED);
//     eeprom.putBool(ID(DEEPSLEEP_ENABLED),    DEEPSLEEP_ENABLED);
//     eeprom.putBool(ID(SERVER_ENABLED),    SERVER_ENABLED);

//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE01),    NEUTRON_I2C_BYTE01);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE02),    NEUTRON_I2C_BYTE02);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE03),    NEUTRON_I2C_BYTE03);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE04),    NEUTRON_I2C_BYTE04);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE05),    NEUTRON_I2C_BYTE05);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE06),    NEUTRON_I2C_BYTE06);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE07),    NEUTRON_I2C_BYTE07);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE08),    NEUTRON_I2C_BYTE08);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE09),    NEUTRON_I2C_BYTE09);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE0A),    NEUTRON_I2C_BYTE0A);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE0B),    NEUTRON_I2C_BYTE0B);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE0C),    NEUTRON_I2C_BYTE0C);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE0D),    NEUTRON_I2C_BYTE0D);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE0E),    NEUTRON_I2C_BYTE0E);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE0F),    NEUTRON_I2C_BYTE0F);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE10),    NEUTRON_I2C_BYTE10);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE11),    NEUTRON_I2C_BYTE11);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE12),    NEUTRON_I2C_BYTE12);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE13),    NEUTRON_I2C_BYTE13);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE14),    NEUTRON_I2C_BYTE14);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE15),    NEUTRON_I2C_BYTE15);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE16),    NEUTRON_I2C_BYTE16);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE17),    NEUTRON_I2C_BYTE17);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE18),    NEUTRON_I2C_BYTE18);
//     eeprom.putUInt(ID(NEUTRON_I2C_BYTE19),    NEUTRON_I2C_BYTE19);
// }

// bool begin() {
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
// }

// bool handle() { 
//     return true; 
// }

// }
// // static module_memory MEMORY;