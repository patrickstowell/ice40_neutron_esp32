#include <Preferences.h>
#define ID(x) #x
Preferences eeprom;

class module_memory {
public:
    bool begin() {
        eeprom.begin("config", false);
        eeprom.putUInt("hasconfig", 0);

        if (!eeprom.getUInt("hasconfig", 0)) {
            Serial.println("Memory::CheckEEPROMValid() : Uploading EEPROM Defaults");
            eeprom.clear();

            WriteToEEPROM();

            eeprom.putUInt("hasconfig", 1);
        } else {
            Serial.println("Memory::CheckEEPROMValid() : EEPROM Already Present!");
        }

        int value = eeprom.getUInt("hasconfig", 0);
        eeprom.end();

        return true;
    }

    bool handle() { return true; }

    void ReadFromEEPROM() {
        APN_NAME  = eeprom.getString(ID(APN_NAME));
        USER_NAME = eeprom.getString(ID(USER_NAME));
        PASS_NAME = eeprom.getString(ID(PASS_NAME));
        PMT_HV    = eeprom.getInt(ID(PMT_HV));
    }

    void WriteToEEPROM() {
        eeprom.putString(ID(APN_NAME),  APN_NAME);
        eeprom.putString(ID(USER_NAME), USER_NAME);
        eeprom.putString(ID(PASS_NAME), PASS_NAME);
        eeprom.putString(ID(PMT_HV),    PMT_HV);
    }

    void Reset() {
        APN_NAME = "TEST";
        USER_NAME = "TEST2";
        PASS_NAME = "TEST2";
        PMT_HV = 1200;
    }

    String APN_NAME;
    String USER_NAME;
    String PASS_NAME;
    int PMT_HV;
}

static module_memory MEMORY;