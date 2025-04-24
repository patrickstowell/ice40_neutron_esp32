#include <WiFi.h>
#include <ArduinoOTA.h>

// Access Point credentials
const char* ssid = "ESP32_NEUTRON";
const char* password = "neutrons2025";

class module_ota {
public:
    bool begin() {

        // Create the Access Point
        WiFi.softAP(ssid, password);
        Serial.println("Access Point Started");
        Serial.print("AP IP address: ");
        Serial.println(WiFi.softAPIP());

        // OTA Setup
        ArduinoOTA
            .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            Serial.println("Start updating " + type);
            })
            .onEnd([]() {
            Serial.println("\nEnd");
            })
            .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
            })
            .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR) Serial.println("End Failed");
            });

        ArduinoOTA.begin();
        Serial.println("OTA Ready");
        return true;
    }


    bool handle() {
        ArduinoOTA.handle();
        return true;
    }

};

module_ota OTA;
